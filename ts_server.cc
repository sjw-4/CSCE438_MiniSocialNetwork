#include <ctime>
#include <unistd.h>
#include <vector>
#include <string>

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
using tinysocial::TinySocial;


/*#include <grpc/grpc.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include "ts.grpc.pb.h"

#include <ctime>
#include <unistd.h>
#include <vector>
#include <string>

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
using tinysocial::NewPost;*/

struct PostInfo {
    std::string post;
    time_t pTime;
};

struct UserInfo {
    std::string username;
    std::vector <std::string> following;
    std::vector <std::string> followers;
    std::vector <PostInfo> posts;
};

class TinySocialImpl final : public TinySocial::Service {
private:
    std::vector<UserInfo> allUsers;

    //TODO: change return val to bool and add &UserInfo to arguments so it can return false if not found
    UserInfo getUser(std::string _username) {
        for(int i = 0; i < allUsers.size(); i++) {
            if(allUsers.at(i).username == _username)
                return allUsers.at(i);
        }
        UserInfo empty;
        return empty;
    }
    int getUserIndex(std::string _username) {
        for(int i = 0; i < allUsers.size(); i++) {
            if(allUsers.at(i).username == _username)
                return i;
        }
        return -1;
    }
public:
    Status GetList(ServerContext* context, const User* user, ServerWriter<User>* writer) override {
        UserInfo curUser = getUser(user->name());
		UserInfo nullCheck;
        User signalUser;
        signalUser.set_name("END_OF_FOLLOWERS");
        if(curUser == nullCheck) {
            signalUser.set_name("2");
            writer->Write(signalUser);
            return Status::OK;
        }
        for(int i = 0; i < curUser.followers.size(); i++) {
            writer->Write(getUser(curUser.followers.at(i)));
        }
        writer->Write(signalUser);
        for(int i = 0; i < allUsers.size(); i++) {
            if(curUser.username != allUsers.at(i).username)
                writer->Write(allUsers.at(i));
        }

        return Status::OK;
    }
    Status Unfollow(ServerContext* context, const User* user, ReplyStatus* replyStat) override {
        std::string bothUsers = user->name();
        std::string curUsername;
        std::string toUnfollow;
        for(int i = 0; i < bothUsers.size(); i++) {
            if(bothUsers.at(i) == '|') {
                curUsername = bothUsers.substr(0, i);
                toUnfollow = bothUsers.substr(i + 1, bothUsers.size() - (i + 1));
                break;
            }
        }
        UserInfo curUser = getUser(curUsername);
        for(int i = 0; i < curUser.following.size(); i++) {
            if(curUser.following.at(i) == toUnfollow) {
                int curIndex = getUserIndex(curUsername);
                if(curIndex == -1) {
                    replyStat->set_stat(2);
                    return Status::OK;
                }
                allUsers.at(curIndex).following.erase(following.begin() + i);
                replyStat->set_stat(0);
                return Status::OK;
            }
        }
    }
    Status Follow(ServerContext* context, const User* user, ReplyStatus* replyStat) override {
        std::string bothUsers = user->name();
        std::string curUsername;
        std::string toFollow;
        for(int i = 0; i < bothUsers.size(); i++) {
            if(bothUsers.at(i) == '|') {
                curUsername = bothUsers.substr(0, i);
                toFollow = bothUsers.substr(i + 1, bothUsers.size() - (i + 1));
                break;
            }
        }
        for(int i = 0; i < allUsers.size(); i++) {
            if(allUsers.at(i).username == toFollow) {
                int curIndex = getUserIndex(curUsername);
                if(curIndex == -1) {
                    replyStat->set_stat(2);
                    return Status::OK;
                }
                allUsers.at(i).following.push_back(toFollow);
                replyStat->set_stat(0);
                return Status::OK;
            }
        }
        replyStat->set_stat(2);
        return Status::OK;
    }
    Status GetTimeline(ServerContext* context, const User* user, ServerWriter<Post>* writer) override {
        //Temporary function to test the program with
        int curUserIndex = getUserIndex(user->name());
        for(int i = 0; i < allUsers.at(i).posts.size(); i++) {
            writer->Write(allUsers.at(i).posts.at(i));
        }
        return Status::OK;
    }
    Status PostTimeline(ServerContext* context, const NewPost* post, ReplyStatus* replyStat) override {
        int curUserIndex = getUserIndex(post->postFrom());
        PostInfo nPost;
        nPost.post = post->postText();
        nPost.pTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        allUsers.at(2).posts.push_back(nPost); //check right here hardcoded the .at
        replyStat->set_stat(0);
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
    int opt = 0;
    while ((opt = getopt(argc, argv, "p")) != -1){
        switch(opt) {
            case 'p':
                port = optarg; break;
            default:
                std::cerr << "Invalid Command Line Argument\n";
        }
    }

    runServer(argv[0]);

    return 0;
}