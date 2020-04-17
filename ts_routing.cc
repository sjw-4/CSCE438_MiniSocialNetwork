#include <ctime>
#include <unistd.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <grpc++/grpc++.h>
#include "ts.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using tinysocial::User;
using tinysocial::ReplyStatus;
using tinysocial::Post;
using tinysocial::NewPost;
using tinysocial::ServerInfo;
using tinysocial::TinySocial;

//Global var
int curMaxId = 0;

struct IPInfo {
    std::string ipAddress;
    std::string portNo;
    std::string idNum;
    bool alive;
};

IPInfo getIPInfo(std::string unformatted) {
    IPInfo newIP;
    int counter = 0;
    std::string curStr = "";
    for(int i = 0; i < unformatted.length(); i++) {
        if(counter == 0) {
            if(unformatted.at(i) == ':')
                counter++;
            continue;
        }
        else if(unformatted.at(i) == ':' && counter == 1) {
            newIP.ipAddress = curStr;
            break;
        }
        else {
            curStr += unformatted.at(i);
        }
    }
    newIP.alive = true;
    newIP.portNo = -1;
    curMaxId++;
    newIP.idNum = std::to_string(curMaxId);
    return newIP;
}

class TinySocialRouting final : public TinySocial::Service {
private:
    std::vector<IPInfo> servers;
    IPInfo curMaster;
    void selectNewMaster() {    //TODO full implimentation
        for(int i = 0; i < servers.size(); i++) {
            if(servers.at(i).alive) {
                curMaster = servers.at(i);
                std::cout << "New master selected: " << curMaster.idNum << std::endl;
                return;
            }
        }
        //if you get here, things are very bad
        std::cout << "NO SERVERS AVAILABLE... OOF" << std::endl;
    }
public:
    Status ServerLogin(ServerContext* context, const ReplyStatus* msgStat, ReplyStatus* replyStat) override {
		//git test
        //TODO add ability for crashed master to retake its spot in the vector
        std::string serverInfo = context->peer();
        IPInfo newServer = getIPInfo(serverInfo);
        newServer.portNo = msgStat->stat();
        servers.push_back(newServer);
        if(servers.size() == 1) {
            selectNewMaster();
        }
        std::cout << "Added server: " << servers.at(servers.size() - 1).idNum << std::endl;
        return Status::OK;
    }
    Status GetServerInfo(ServerContext* context, const ReplyStatus* rStat, ServerInfo* si) override {
        //Check to make sure current master is still alive
        grpc::Status grpc_status;
        do {
            std::unique_ptr<TinySocial::Stub> stub_;
            std::shared_ptr<Channel> channel = grpc::CreateChannel(curMaster.ipAddress + ":" + curMaster.portNo, grpc::InsecureChannelCredentials());
            stub_ = TinySocial::NewStub(channel);
            ClientContext context;
            ServerInfo tsServer;
            ReplyStatus sStat; sStat.set_stat("0");
            ReplyStatus rStat;
            grpc_status = stub_->HeartBeat(&context, sStat, &rStat);
            if(!grpc_status.ok()) {
                for(int i = 0; i < servers.size(); i++) {
                    if(servers.at(i).alive == true && curMaster.idNum.compare(servers.at(i).idNum) == 0) {
                        servers.at(i).alive = false;
                        selectNewMaster();
                        break;
                    }
                }
            }
        } while(!grpc_status.ok());

        //std::string rStatS = rStat->stat();
        //std::cout << "GetServerInfo:rStat is: " << rStatS << std::endl;
        //if(rStatS != "-1") {
        //    for(int i = 0; i < servers.size(); i++) {
        //        if(servers.at(i).alive == true && rStatS.compare(servers.at(i).idNum) == 0) {
        //            servers.at(i).alive = false;
        //            selectNewMaster();
        //            break;
        //        }
        //    }
        //}
        si->set_serverip(curMaster.ipAddress);
        si->set_serverport(curMaster.portNo);
        si->set_serverid(curMaster.idNum);
        return Status::OK;
    }
    /*Status HeartBeat(ServerContext* context, const User* user, ReplyStatus* replyStat) override {
        replyStat->set_stat("0");
        return Status::OK;
    }*/
};

void runServer(std::string serverAddr) {
    TinySocialRouting service;

    ServerBuilder builder;
    builder.AddListeningPort(serverAddr, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    server->Wait();
}

int main(int argc, char** argv) {
    std::string port = "3010";

    if(argc > 1) {
        port = argv[argc - 1];
    }

    runServer("0.0.0.0:" + port);

    return 0;
}
