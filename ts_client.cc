#include <iostream>
//#include <memory>
//#include <thread>
#include <vector>
#include <string>
#include <unistd.h>
#include <grpc++/grpc++.h>
#include "client.h"
#include "ts.grpc.pb.h"
/*
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>*/

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using tinysocial::User;
using tinysocial::Post;
using tinysocial::NewPost;
using tinysocial::ReplyStatus;
using tinysocial::ServerInfo;
using tinysocial::TinySocial;

//Global var
long long lastPost = 0;

class Client : public IClient
{
    public:
        Client(const std::string& hname,
               const std::string& uname,
               const std::string& p)
            :hostname(hname), username(uname), port(p)
            {}
    protected:
        virtual int connectTo(bool routingServer);
        virtual IReply processCommand(std::string& input);
        virtual void processTimeline();
        virtual IReply doHeartBeat();
    private:
        std::string hostname;
        std::string username;
        std::string port;

        std::string tss_hostname;   //hostname for the tss server to connect to
        std::string tss_port;       //port for the tss server to connect to
        std::string serverID;       //id num of connected server
        
        // You can have an instance of the client stub
        // as a member variable.
        //std::unique_ptr<NameOfYourStubClass::Stub> stub_;

        std::unique_ptr<TinySocial::Stub> stub_;
};

int main(int argc, char** argv) {

    std::string hostname = "localhost";
    std::string username = "default";
    std::string port = "3010";
    int opt = 0;
    while ((opt = getopt(argc, argv, "h:u:p:")) != -1){
        switch(opt) {
            case 'h':
                hostname = optarg;break;
            case 'u':
                username = optarg;break;
            case 'p':
                port = optarg;break;
            default:
                std::cerr << "Invalid Command Line Argument\n";
        }
    }

    Client myc(hostname, username, port);
    // You MUST invoke "run_client" function to start business logic
    myc.run_client();

    return 0;
}

IStatus checkForError(std::string msg) {
    //Checks for errors in the message. If there is an error then the first string sent by
    //the server in any message will be a number corresponding to the error
    if(msg == "0")
        return SUCCESS;
    else if(msg == "1")
        return FAILURE_ALREADY_EXISTS;
    else if(msg == "2")
        return FAILURE_NOT_EXISTS;
    else if(msg == "3")
        return FAILURE_INVALID_USERNAME;
    else if(msg == "4")
        return FAILURE_INVALID;
    else if(msg == "5")
        return FAILURE_UNKNOWN;
    else    //This will mean if the string passed is a username (such as in the LIST cmd), all is good
        return SUCCESS;
}

int Client::connectTo(bool routingServer)
{
	// ------------------------------------------------------------
    // In this function, you are supposed to create a stub so that
    // you call service methods in the processCommand/porcessTimeline
    // functions. That is, the stub should be accessible when you want
    // to call any service methods in those functions.
    // I recommend you to have the stub as
    // a member variable in your own Client class.
    // Please refer to gRpc tutorial how to create a stub.
	// ------------------------------------------------------------

    if(routingServer) {
        std::shared_ptr<Channel> channel = grpc::CreateChannel(hostname + ":" + port, grpc::InsecureChannelCredentials());
        stub_ = TinySocial::NewStub(channel);
        ClientContext context;
        ServerInfo tsServer;
        ReplyStatus rStat;
        rStat.set_stat("1");
        ServerInfo si;
        Status stat = stub_->GetServerInfo(&context, rStat, &si);
        tss_hostname = si.serverip();
        tss_port = si.serverport();
        serverID = si.serverid();
    }
    else {
        displayReConnectionMessage(tss_hostname, tss_port);
        std::shared_ptr<Channel> channel = grpc::CreateChannel(tss_hostname + ":" + tss_port, grpc::InsecureChannelCredentials());
        stub_ = TinySocial::NewStub(channel);
        ClientContext context;
        User curUser; curUser.set_name(username);
        ReplyStatus rStat;
        Status stat = stub_->SignIn(&context, curUser, &rStat);
        if(rStat.stat() == "1") {
            //User exists, consider writing that they have signed in
        }
        else if(rStat.stat() == "2") {
            //User is new, consider writing a welcom message
        }
        else {
            //Something has gone wrong, exit
            exit(1);
        }
    }

    return 1; // return 1 if success, otherwise return -1
}

IReply Client::processCommand(std::string& input)
{
	// ------------------------------------------------------------
	// GUIDE 1:
	// In this function, you are supposed to parse the given input
    // command and create your own message so that you call an 
    // appropriate service method. The input command will be one
    // of the followings:
	//
	// FOLLOW <username>
	// UNFOLLOW <username>
	// LIST
    // TIMELINE
	//
	// - JOIN/LEAVE and "<username>" are separated by one space.
	// ------------------------------------------------------------
	
    ClientContext context;
    IReply myReply;

    if(input == "LIST") {
        User user;                          //User of current user
        User users;                         //User to hold sent usernames
        std::vector<std::string> allUsers;  //Vector to hold all users
        user.set_name(username);
        //Get reader to read all sent usernames
        std::unique_ptr<ClientReader<User> > reader(stub_->GetList(&context, user));
        while(reader->Read(&users)) {
            allUsers.push_back(users.name());
        }
        //begin setting values in IReply
        myReply.grpc_status = reader->Finish();

        //Check to make sure a connection was established
        if(allUsers.size() != 0) {
            myReply.comm_status = checkForError(allUsers.at(0));
            //The server inserts an END_OF_FOLLOWERS string to indicate where the list goes from followers to all other users
            for(int i = 0; i < allUsers.size(); i++) {
                if(allUsers.at(i) == "END_OF_FOLLOWERS") {
                    i++;
                    while(i < allUsers.size()) {
                        myReply.all_users.push_back(allUsers.at(i));
                        i++;
                    }
                    break;
                }
                else
                    myReply.followers.push_back(allUsers.at(i));
            }
        } else {
            myReply.comm_status = checkForError("5");
        }
    }
    else if(strncmp(input.c_str(), "FOLLOW ", 7) == 0) {
        User users;             //Holds the username of the poster and who they want to follow
        ReplyStatus rStatus;    //Holds the response from the server
        //Concatinate the users name with who they want to follow
        users.set_name(username + "|" + input.substr(7, input.size() - 7));
        myReply.grpc_status = stub_->Follow(&context, users, &rStatus);
        myReply.comm_status = checkForError(rStatus.stat());
    }
    else if(strncmp(input.c_str(), "UNFOLLOW ", 9) == 0) {
        User users;
        ReplyStatus rStatus;
        //Concatinate the users name with who they want to unfollow
        users.set_name(username + "|" + input.substr(9, input.size() - 9));
        myReply.grpc_status = stub_->Unfollow(&context, users, &rStatus);
        myReply.comm_status = checkForError(rStatus.stat());
    }
    else if(input == "TIMELINE") {
        User user;
        Post post;
        std::vector<Post> posts;
        user.set_name(username);
        std::unique_ptr<ClientReader<Post> > reader(stub_->GetTimeline(&context, user));
        //Set a default value for comm_status, since this error should never happen for this command
        bool checkedFistMsg = false;
        //Set default val to success, so a user without anything in their timeline (and would thus skip the loop)
        //can still get to the timeline functionality
        myReply.comm_status = SUCCESS;
        int i = 0;
        while(reader->Read(&post)) {
            //If the default value is still set, check the first passed name for errors
            if(!checkedFistMsg) {
                myReply.comm_status = checkForError(post.name());
                checkedFistMsg = true;
            }
            //If all is good, add the posts to the vector for reversing
            if(myReply.comm_status == SUCCESS && i < 20) {
                posts.insert(posts.begin(), post);
                i++;
            }            
        }
        for(int j = 0; j < posts.size(); j++) {
            time_t tempTime = posts.at(j).time();
            displayPostMessage(posts.at(j).name(), posts.at(j).posttext(), tempTime);
            lastPost = posts.at(j).time();
        }
        myReply.grpc_status = reader->Finish();
    }

    return myReply;

    // ------------------------------------------------------------
	// GUIDE 2:
	// Then, you should create a variable of IReply structure
	// provided by the client.h and initialize it according to
	// the result. Finally you can finish this function by returning
    // the IReply.
	// ------------------------------------------------------------
    
	// ------------------------------------------------------------
    // HINT: How to set the IReply?
    // Suppose you have "Join" service method for JOIN command,
    // IReply can be set as follow:
    // 
    //     // some codes for creating/initializing parameters for
    //     // service method
    //     IReply ire;
    //     grpc::Status status = stub_->Join(&context, /* some parameters */);
    //     ire.grpc_status = status;
    //     if (status.ok()) {
    //         ire.comm_status = SUCCESS;
    //     } else {
    //         ire.comm_status = FAILURE_NOT_EXISTS;
    //     }
    //      
    //      return ire;
    // 
    // IMPORTANT: 
    // For the command "LIST", you should set both "all_users" and 
    // "followers" member variable of IReply.
	// ------------------------------------------------------------
}

void Client::processTimeline()
{
	// ------------------------------------------------------------
    // In this function, you are supposed to get into timeline mode.
    // You may need to call a service method to communicate with
    // the server. Use getPostMessage/displayPostMessage functions
    // for both getting and displaying messages in timeline mode.
    // You should use them as you did in hw1.
	// ------------------------------------------------------------

    // ------------------------------------------------------------
    // IMPORTANT NOTICE:
    //
    // Once a user enter to timeline mode , there is no way
    // to command mode. You don't have to worry about this situation,
    // and you can terminate the client program by pressing
    // CTRL-C (SIGINT)
	// ------------------------------------------------------------

    for(;;) {
        ClientContext context;
        if(userInputReady(100000)) {
            NewPost post;
            ReplyStatus rStatus;
            post.set_postfrom(username);
            post.set_posttext(getPostMessage());
            Status stat = stub_->PostTimeline(&context, post, &rStatus);
            if(checkForError(rStatus.stat()) != SUCCESS) {
                std::cout << "Debug:tsc:processTimeline:Error from server" << std::endl;
            }
        }
        else {
            IReply checkHeartBeat = doHeartBeat();
            if(!checkHeartBeat.grpc_status.ok())
                return;
            User user;
            Post post;
            enum IStatus stat;
            std::vector<Post> posts;
            user.set_name(username);
            std::unique_ptr<ClientReader<Post> > reader(stub_->GetTimeline(&context, user));
            //Set a default value for comm_status, since this error should never happen for this command
            bool checkedFirstMsg = false;
            //Set default val to success, so a user without anything in their timeline (and would thus skip the loop)
            //can still get to the timeline functionality
            stat = SUCCESS;
            bool newPost = true;
            while(reader->Read(&post)) {
                //If the default value is still set, check the first passed name for errors
                if(!checkedFirstMsg) {
                    stat = checkForError(post.name());
                    checkedFirstMsg = true;
                }
                //If all is good, add the posts to the vector for reversing
                if(newPost && stat == SUCCESS && post.time() > lastPost) {
                    posts.insert(posts.begin(), post);
                }
                else {
                    newPost = false;
                }
            }
	        Status readerStat = reader->Finish();
            for(int j = 0; j < posts.size(); j++) {
                time_t tempTime = posts.at(j).time();
                displayPostMessage(posts.at(j).name(), posts.at(j).posttext(), tempTime);
                lastPost = posts.at(j).time();
            }
            if(!readerStat.ok()) {
                std::cout << "Error in getting update timeline" << std::endl;
                return;
            }
        }
    }
}

IReply Client::doHeartBeat() {
    ClientContext context;
    ReplyStatus sStatus, rStatus;
    sStatus.set_stat("0");
    IReply temp;
    temp.grpc_status = stub_->HeartBeat(&context, sStatus, &rStatus);
    return temp;
}