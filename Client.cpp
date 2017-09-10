#include <iostream>
#include <cstring>
#include "TCPStreamData.h"

#include "ConnectorToTCPServer.h"
#include "RSA/RSA.h"


const int MAXSIZE = 256;
TCPStreamData* stream;
void establishRSA();

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
    stream = connector -> makeConnection(argv[2], atoi(argv[1]));
    establishRSA();
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

void establishRSA() {
    RSA rsa;//RSA rsa1(rsa.get_module(), rsa.get_publicKey());
    std::string rsaKey;
    std::string module{std::to_string(rsa.get_module())};
    std::string publicKey{std::to_string(rsa.get_publicKey())};
    rsaKey = "[" + module + " " + publicKey + "]";
    std::cerr<<rsaKey;
    stream -> send(rsaKey.c_str(), rsaKey.size());
    std::cout<< "trying to establish connection";
    ssize_t length;
    std::string message;
    char line [MAXSIZE];
    length = stream -> receive(line, sizeof(line));
    line[length] = NULL;
    std::cout<< "\nreceived - "<< line << "\n";
    rsa.set_converserPublicKey(atoi(line));
    //length = stream -> receive(line, sizeof(line));
    //line[length] = NULL;
    //std::cout<< "\nreceived - "<< line << "\n";
}

