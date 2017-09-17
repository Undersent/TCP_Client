//
// Created by rafal on 01.09.17.
//

#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
#include "ConnectorToTCPServer.h"

TCPStreamData *ConnectorToTCPServer::makeConnection(const char *server, int port) const {
    struct sockaddr_in address;

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (getHostName(server, &(address.sin_addr)) != 0) {
        inet_pton(PF_INET, server, &(address.sin_addr));
    }
    int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (::connect(socketDescriptor, (struct sockaddr *) &address, sizeof(address)) != 0) {
        return nullptr;
    }
    return new TCPStreamData(socketDescriptor, &address);
}

int ConnectorToTCPServer::getHostName(const char *hostname, struct in_addr *addr) const {
    struct addrinfo *res;
    int result = getaddrinfo(hostname, nullptr, nullptr, &res);
    if (result == 0) {
        memcpy(addr, &((struct sockaddr_in *) res->ai_addr)->sin_addr,
               sizeof(struct in_addr));
    }
    return result;
}


