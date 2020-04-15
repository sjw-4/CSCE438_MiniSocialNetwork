#include <ctime>
#include <unistd.h>
#include <vector>
#include <string>
#include <fstream>

#include <grpc++/grpc++.h>
#include "ts.grpc.pb.h"

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

struct IPInfo {
    std::string ipAddress;
    std::string portNo;
    bool alive;
};

IPInfo getIPInfo(std::string unformatted) {
    IPInfo newIP;
    int counter = 0;
    std::string curStr = "";
    for(int i = 0; i < unformatted.length(); i++) {
        if(counter == 0) {
            if(unformatted.at(i) != ":")
                counter++;
            continue;
        }
        else if(unformatted.at(i) == ":" && counter == 1) {
            newIP.ipAddress = curStr;
            curStr = "";
            counter++;
        }
        else {
            curStr += unformatted.at(i);
        }
    }
    newIP.portNo = curStr;
    newIP.alive = true;
    return newIP;
}

class TinySocialRouting final : public TinySocial::Service {
private:
    std::vector<IPInfo> servers;
    IPInfo curMaster;
public:
    Status ServerLogin(ServerContext* context, const ReplyStatus* msgStat, ReplyStatus* replyStat) override {
        /*if(msgStat != "0") {
            std::cout << "routing::ServerLogin::Error" << std::endl;
            return Status::OK;
        }*/
        std::string serverInfo = context->peer();
        IPInfo temp = getIPInfo(serverInfo);
        std::cout << "Testing server info: " << std::endl << temp.ipAddress << std::endl << temp.portNo << std::endl;
        //TODO set curMaster if none is set
        return Status::OK;
    }
    Status GetServerInfo(ServerContext* context, const User* user, ServerInfo* si) override {
        //TODO
        //si = curMaster;
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
