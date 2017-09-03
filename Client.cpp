#include <iostream>
#include <cstring>
#include "TCPStreamData.h"

#include "ConnectorToTCPServer.h"



const int MAXSIZE = 256;
int main(int argc, char** argv)
{
   if(argc != 3){
       std::cout<<"usage "<< argv[0] << "port\n";
       return 0;
   }

    ssize_t length;
    std::string message;
    //char input[MAXSIZE];
    std::string input;
    char line [MAXSIZE];
    auto* connector = new ConnectorToTCPServer();
    TCPStreamData* stream = connector -> makeConnection(argv[2], atoi(argv[1]));
    while(true) {
        getline(std::cin, input);
        if(input == ":!q") {break;}
        stream -> send(input.c_str(), input.size());
        std::cout<< "sent - "<< input;
        length = stream -> receive(line, sizeof(line));
        line[length] = NULL;
        std::cout<< "\nreceived - "<< line << "\n";

    }
    delete stream;
    return 0;
}

