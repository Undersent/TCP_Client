#include <iostream>
#include <cstring>
#include <memory>
#include "TCPStreamData.h"

#include "ConnectorToTCPServer.h"
#include "RSA/RSA.h"


const int MAXSIZE = 256;
TCPStreamData* stream;
void establishRSA();
std::unique_ptr<RSA::RSA> rsa;
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
        input = rsa->encryptString(input);
        stream -> send(input.c_str(), input.size());
        //std::cout<< "sent - "<< input<<"NULL\n";
        length = stream -> receive(line, sizeof(line));
        line[length] = NULL;
        std::string decodedText  = rsa->decryptString(line);
        std::cout<< "\nreceived - "<< decodedText << "\n";

    }
    delete stream;
    return 0;
}

void establishRSA() {
    std::string rsaKey;
    rsa = std::make_unique<RSA::RSA>(RSA::RSA());
    std::string module{std::to_string(rsa->get_module())};
    std::string publicKey{std::to_string(rsa->get_publicKey())};
    rsaKey = "[" + module + " " + publicKey + "]";
    stream -> send(rsaKey.c_str(), rsaKey.size());
    std::cout<< "Trying to establish connection with server\n";
    ssize_t length;
    std::string message;
    char line [MAXSIZE];
    length = stream -> receive(line, sizeof(line));
    line[length] = NULL;
    rsa->set_converserPublicKey(atoi(line));
    std::cout<< "Connection established\n";
}

