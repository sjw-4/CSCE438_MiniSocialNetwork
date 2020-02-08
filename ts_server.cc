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
using tinysocial::TinySocial;

struct UserInfo {
    User userMsg;
    std::string name;
    std::vector <std::string> following;
    std::vector <std::string> followers;
    std::vector <Post> posts;
};

class TinySocialImpl final : public TinySocial::Service {
private:
    std::vector<UserInfo> allUsers;
    std::string fileName = "userdata.txt";
    bool dataLoaded = false;

    //Finds a user from the passed name, returns false if not found
    bool getUser(std::string _name, UserInfo& user) {
        for(int i = 0; i < allUsers.size(); i++) {
            if(allUsers.at(i).name == _name) {
                user = allUsers.at(i);
                return true;
            }
        }
        return false;
    }
    
    //Finds the users index from the passed name, returns -1 if not found
    int getUserIndex(std::string _name) {
        for(int i = 0; i < allUsers.size(); i++) {
            if(allUsers.at(i).name == _name)
                return i;
        }
        return -1;
    }

    //Finds a string in a passed list
    int getIndexInVector(std::string _name, std::vector<std::string>& _list) {
        for(int i = 0; i < _list.size(); i++) {
            if(_list.at(i) == _name)
                return i;
        }
        return -1;
    }

    //Save the data to a file
    void saveData(std::string fName) {
        std::ofstream f(fName);
        if (f.is_open()) {
            for (int i = 0; i < allUsers.size(); i++) {
                UserInfo u = allUsers.at(i);
            //Handle line 1: Users name
                f << u.name << std::endl;
            //Handle line 2: List of Users follows
                if(u.following.size() == 0) {
                    f << "<NO_FOLLOWING>";
                }
                for (int j = 0; j < u.following.size(); j++) {
                    f << u.following.at(j) << "|";
                }
                f << std::endl;
            //Handle line 3: List of Users followers
                if(u.followers.size() == 0) {
                    f << "<NO_FOLLOWERS>";
                }
                for (int j = 0; j < u.followers.size(); j++) {
                    f << u.followers.at(j) << "|";
                }
                f << std::endl;
            //Loop through to handle the post info
                if (u.posts.size() > 0)
                    f << "<Post>" << std::endl;
                for (int j = 0; j < u.posts.size(); j++) {
                    f << u.posts.at(j).name() << std::endl
                        << u.posts.at(j).posttext() << std::endl
                        << std::to_string(u.posts.at(j).time()) << std::endl;
                }
                if (u.posts.size() > 0)
                    f << "</Post>" << std::endl;
            }
            f << "</EOF>" << std::endl;
        }
        else {
            std::cout << "Error saving data" << std::endl;
        }
    }

    //Load the data from a file
    void loadData(std::string fName) {
        std::ifstream f(fName);
        if (f.is_open()) {
            std::string line;
            std::getline(f, line);
            while (line != "" && line != "</EOF>") {
            //Handle line 1: Users name
                UserInfo uiLoad;
                User uLoad; uLoad.set_name(line);
                uiLoad.userMsg = uLoad;
                uiLoad.name = line;
                std::getline(f, line);
            //Handle line 2: List of Users follows
                if (line != "<NO_FOLLOWS>") {
                    int i = 0;
                    std::string follows;
                    while (i < line.size()) {
                        if (line.at(i) == '|') {
                            uiLoad.following.push_back(follows);
                            follows = "";
                        }
                        else {
                            follows = follows + line.at(i);
                        }
                        i++;
                    }
                }
                std::getline(f, line);
            //Handle line 3: List of Users followers
                if (line != "<NO_FOLLOWERS>") {
                    int i = 0;
                    std::string follower;
                    while (i < line.size()) {
                        if (line.at(i) == '|') {
                            uiLoad.followers.push_back(follower);
                            follower = "";
                        }
                        else {
                            follower = follower + line.at(i);
                        }
                        i++;
                    }
                }
                std::getline(f, line);
            //Loop through the next bit to get the info of the posts
                if (line == "<Post>") {
                    std::getline(f, line);
                    while (line != "</Post>") {
                        Post p;
                        p.set_name(line);
                        std::getline(f, line);
                        p.set_posttext(line);
                        std::getline(f, line);
                        p.set_time(std::stoll(line));
                        uiLoad.posts.push_back(p);
                        std::getline(f, line);
                    }
                }
            //Add the data to the vector of all users, and repeat until EOF flag
                allUsers.push_back(uiLoad);
                std::getline(f, line);
            }
        }
        else {
            std::cout << "Error loading data" << std::endl;
        }
        return;
    }

public:
    Status SignIn(ServerContext* context, const User* user, ReplyStatus* replyStat) {        
        if(!dataLoaded) {
            loadData(fileName);
            dataLoaded = true;
        }
        UserInfo curUser;
        if(getUser(user->name(), curUser)) {
            replyStat->set_stat("1");
        }
        else {
            //Add user to the database
            User newUserMsg; newUserMsg.set_name(user->name());
            curUser.userMsg = newUserMsg; curUser.name = user->name();
            allUsers.push_back(curUser);
            replyStat->set_stat("2");
            saveData(fileName);
        }
        return Status::OK;
    }
    Status GetList(ServerContext* context, const User* user, ServerWriter<User>* writer) override {
        UserInfo curUser;
        //Get the users info, send a not found indicator if not found
        if(!getUser(user->name(), curUser)) {
            User notFound; notFound.set_name("2");
            const User& notFoundR = notFound;
            writer->Write(notFoundR);
            return Status::OK;
        }
        //Send all of the users followers
        User follower;
        for(std::string f : curUser.followers) {
            follower.set_name(f);
            User& followerR = follower;
            writer->Write(followerR);
        }
        //Send the client an indicator that the list of followers has ended
        User signalU; signalU.set_name("END_OF_FOLLOWERS");
        const User& signalUR = signalU;
        writer->Write(signalUR);
        //Send all of the users
        for(UserInfo user : allUsers) {
            if(curUser.name != user.name) {
                User& userR = user.userMsg;
                writer->Write(userR);
            }
        }
        //All done, send status
        return Status::OK;
    }
    Status Unfollow(ServerContext* context, const User* user, ReplyStatus* replyStat) override {
        //The username and user to unfollow were passed together with | between them, this seperates them
        std::string bothUsers = user->name();
        std::string curUsername;
        std::string toUnfollow;
        for(int i = 0; i < bothUsers.size(); i++) {
            if(bothUsers.at(i) == '|') {
                curUsername = bothUsers.substr(0, i);
                //toUnfollow = bothUsers.substr(i + 1, bothUsers.size() - (i + 1));
				toUnfollow = bothUsers.substr(i + 1, bothUsers.size() - (i + 1));
                break;
            }
        }
        //Find the user who wants to unfollow someone
        UserInfo curUser;
        if(!getUser(curUsername, curUser)) {
            replyStat->set_stat("2");
            return Status::OK;
			
        }
        //Find the user to unfollow
        UserInfo unfollowUser;
        if(!getUser(toUnfollow, unfollowUser)) {
            replyStat->set_stat("2");
            return Status::OK;
        }
        //Remove toUnfollow from users following list
        int userFollowingIndex = getIndexInVector(unfollowUser.name, curUser.following);
        if(userFollowingIndex == -1) {  //User wasn't found in follow list
            replyStat->set_stat("2");
            return Status::OK;
        }
        curUser.following.erase(curUser.following.begin() + userFollowingIndex);
        //Remove user from list of toUnfollows followers
        int followersIndex = getIndexInVector(curUser.name, unfollowUser.followers);
        if(followersIndex != -1) {
            unfollowUser.followers.erase(unfollowUser.followers.begin() + followersIndex);
        }
        //Update the users timeline to remove posts from toUnfollow
        int i = 0;
        int postSize = curUser.posts.size();
		
        while(i < postSize) {
            if(curUser.posts.at(i).name() == unfollowUser.name) {
                curUser.posts.erase(curUser.posts.begin() + i);
                postSize--;
            }
            else {
                i++;
            }
        }
        //Remove both users from the vector and add our adjusted versions
        int curUserIndex = getUserIndex(curUser.name);
        allUsers.erase(allUsers.begin() + curUserIndex);
        int unfollowUserIndex = getUserIndex(unfollowUser.name);
        allUsers.erase(allUsers.begin() + unfollowUserIndex);
        allUsers.push_back(curUser);
        allUsers.push_back(unfollowUser);
        //All is done, set and send status
        saveData(fileName);
        replyStat->set_stat("0");
        return Status::OK;
    }
    Status Follow(ServerContext* context, const User* user, ReplyStatus* replyStat) override {
        //The username and user to follow were passed together with | between them, this seperates them
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
		
        //Find the user who wants to follow someone
        UserInfo curUser;
        if(!getUser(curUsername, curUser)) {
            replyStat->set_stat("2");
            return Status::OK;
        }
		
        //Check if they are already folling toFollow
        if(getIndexInVector(toFollow, curUser.following) != -1) {
            replyStat->set_stat("1");
            return Status::OK;
        }
        //Find the user to follow
        UserInfo followUser;
        if(!getUser(toFollow, followUser)) {
            replyStat->set_stat("2");
            return Status::OK;
        }
        //Add the toFollow to users follow list
        curUser.following.push_back(toFollow);
        //Add user to list of toFollows followers, make sure they aren't already there somehow
        if(getIndexInVector(curUser.name, followUser.followers) == -1) {
            followUser.followers.push_back(curUser.name);
        }
        //Remove both users from the vector and add our adjusted versions
        int curUserIndex = getUserIndex(curUser.name);
        allUsers.erase(allUsers.begin() + curUserIndex);
        int followUserIndex = getUserIndex(followUser.name);
        allUsers.erase(allUsers.begin() + followUserIndex);
        allUsers.push_back(curUser);
        allUsers.push_back(followUser);
        //All done, set and return staus
        saveData(fileName);
        replyStat->set_stat("0");
        return Status::OK;
    }
    Status GetTimeline(ServerContext* context, const User* user, ServerWriter<Post>* writer) override {
        //Get the current user info
        UserInfo curUser;
        if(getUser(user->name(), curUser) == -1) {
            Post temp; temp.set_name("2"); temp.set_posttext("2"); temp.set_time(2);
            Post& tempR = temp;
            writer->Write(tempR);
            return Status::OK;
        }
        //Send the most recent 20 posts to the client
        int i = 0;
        for(const Post& p : curUser.posts) {
            if(i == 20)
                break;
            writer->Write(p);
            i++;
        }
        //All done, send status
        return Status::OK;
    }
    Status PostTimeline(ServerContext* context, const NewPost* post, ReplyStatus* replyStat) override {
        UserInfo curUser;
        //Find the user who is posting
        if(getUser(post->postfrom(), curUser) == -1) {
            replyStat->set_stat("2");
            return Status::OK;
        }
        //Create a new Post variable to store the post info
        Post np;
        np.set_name(curUser.name);
        //Remove newline characters from the string
        std::string pText = post->posttext();
        pText.erase(std::remove(pText.begin(), pText.end(), '\n'), pText.end());
        np.set_posttext(pText);
        np.set_time(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
        //Add post to the users list of post
        curUser.posts.insert(curUser.posts.begin(), np);
        //Add new posts to followers lists of posts
        for(std::string f : curUser.followers) {
            int followerIndex = getUserIndex(f);
            if(followerIndex != -1) {
                allUsers.at(followerIndex).posts.insert(allUsers.at(followerIndex).posts.begin(), np);
            }
        }
        //Remove curUser from allUsers and replace with our update version
        int curUserIndex = getUserIndex(curUser.name);
        allUsers.erase(allUsers.begin() + curUserIndex);
        allUsers.push_back(curUser);
        //All done, set and return status
        saveData(fileName);
        replyStat->set_stat("0");
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
    /*int opt = 0;
    while ((opt = getopt(argc, argv, "p")) != -1){
        switch(opt) {
            case 'p':
                port = optarg; break;
            default:
                std::cerr << "Invalid Command Line Argument\n";
        }
    }*/
    std::cout << "Begin cmd line args" << std::endl;
    for(int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    std::cout << "End cmd line args" << std::endl;

    runServer("0.0.0.0:" + port);

    return 0;
}
