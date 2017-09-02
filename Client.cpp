#include <iostream>
#include "TCPStreamData.h"

#include "ConnectorToTCPServer.h"


using namespace std;
const int MAXSIZE = 256;
int main(int argc, char** argv)
{
   if(argc != 3){
       std::cout<<"usage "<< argv[0] << "port\n";
       return 0;
   }

    int length;
    std::string message;
    char input[MAXSIZE];
    char line [MAXSIZE];
    auto* connector = new ConnectorToTCPServer();
    TCPStreamData* stream = connector -> makeConnection(argv[2], atoi(argv[1]));
    if(stream) {
        //message = "Is there life on Mars?";

        cin.getline(input,sizeof(input));
        stream -> send(input, MAXSIZE);
        std::cout<< "sent - "<< input;
        length = stream -> receive(line, sizeof(line));
        line[length] = NULL;
        std::cout<< "\nreceived - "<< line << "\n";
        delete stream;
    }

    stream = connector -> makeConnection(argv[2], atoi(argv[1]));
    if(stream) {
        message = "Why is there air?";
        stream -> send(message.c_str(), message.size());
        std::cout<< "sent - "<< message.c_str();
        length = stream -> receive(line, sizeof(line));
        line[length] = NULL;
        std::cout<< "\nreceived - "<< line << "\n";
        delete stream;
    }
    return 0;
}