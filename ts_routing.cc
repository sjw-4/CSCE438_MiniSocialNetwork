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
using tinysocial::ServerInfo
using tinysocial::TinySocial;

struct IPInfo {
    std::string ipAddress;
    std::string portNo;
    bool alive;
}

class TinySocialRouting final : public TinySocial::Service {
private:
    std::vector<IPInfo> servers;
    IPInfo curMaster;
public:
    Status ServerLogin(ServerContext* context, const ReplyStatus* msgStat, ReplyStatus* replyStat) override {
        if(msgStat != "0") {
            std::cout << "routing::ServerLogin::Error" << std::endl;
            return Status::OK;
        }
        std::string serverInfo = context->peer();
        std::cout << "Connected peer address is: " << serverInfo << std::endl;
        //TODO set curMaster if none is set
        return Status::OK;
    }
    Status GetServerInfo(ServerCOntext* context, const User* user, ServerInfo* si) override {
        //TODO
        si = curMaster;
        return Status::OK;
    }
};

void runServer(std::string serverAddr) {
    TinySocialImpl service;

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
