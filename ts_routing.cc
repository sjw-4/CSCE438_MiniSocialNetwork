#include <ctime>
#include <unistd.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/wait.h>

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
    //Formats IP info from the stub metadata
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
    newIP.idNum = std::to_string(curMaxId);
    return newIP;
}

class TinySocialRouting final : public TinySocial::Service {
private:
    std::vector<IPInfo> servers;
    IPInfo curMaster;
    void selectNewMaster() {
        //Algorithm: selects system with the lowest ID number that is alive
        for(int i = 0; i < servers.size(); i++) {
            if(servers.at(i).alive) {
                curMaster = servers.at(i);
                std::cout << "New available server selected- IP: " << curMaster.ipAddress << ", ID: " << curMaster.idNum << std::endl;
                return;
            }
        }
        std::cout << "No servers available, doing final check. Please wait..." << std::endl;
        usleep(500000); //sleep for half a second
        for(int i = 0; i < servers.size(); i++) {
            std::unique_ptr<TinySocial::Stub> stub_;
            std::shared_ptr<Channel> channel = grpc::CreateChannel(servers.at(i).ipAddress + ":" + servers.at(i).portNo, grpc::InsecureChannelCredentials());
            stub_ = TinySocial::NewStub(channel);
            ClientContext context;
            ServerInfo tsServer;
            ReplyStatus sStat; sStat.set_stat("0");
            ReplyStatus rStat;
            grpc::Status grpc_status = stub_->HeartBeat(&context, sStat, &rStat);
            if(grpc_status.ok()) {
                curMaster = servers.at(i);
                std::cout << "Active server found. Setting as available" << std::endl;
                return;
            }
        }
        std::cout << "No active servers found, big oof. Will wait for new servers to join." << std::endl;
    }
public:
    Status ServerLogin(ServerContext* context, const ReplyStatus* msgStat, ReplyStatus* replyStat) override {
        //All servers connect to the routing server and "log in" so that the routing server knows they are available
        std::string serverInfo = context->peer();
        IPInfo newServer = getIPInfo(serverInfo);
        newServer.portNo = msgStat->stat();
        bool foundServer = false;
        for(int i = 0; i < servers.size(); i++) {
            if(servers.at(i).ipAddress.compare(newServer.ipAddress) == 0 && servers.at(i).portNo.compare(newServer.portNo) == 0) {
                foundServer = true;
                servers.at(i).alive = true;
                std::cout << "Renewed previous server- IP: " << servers.at(i).ipAddress << ", ID: " << servers.at(i).idNum << std::endl;
                break;
            }
        }
        if(!foundServer) {
            curMaxId++;
            servers.push_back(newServer);
            if(servers.size() == 1) {
                selectNewMaster();
            }
            std::cout << "Added new server- IP: " << newServer.ipAddress << ", ID: " << newServer.idNum << std::endl;
        }
        return Status::OK;
    }
    Status GetServerInfo(ServerContext* context, const ReplyStatus* rStat, ServerInfo* si) override {
        //Used by the client to get the information to connect to the proper server

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
        si->set_serverip(curMaster.ipAddress);
        si->set_serverport(curMaster.portNo);
        si->set_serverid(curMaster.idNum);
        return Status::OK;
    }
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
