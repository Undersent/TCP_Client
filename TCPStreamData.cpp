//
// Created by rafal on 01.09.17.
//

#include <zconf.h>
#include <array>
#include <sys/socket.h>
#include "TCPStreamData.h"
#include <arpa/inet.h>

TCPStreamData::~TCPStreamData() {
    close(socketDescriptor);
}

TCPStreamData::TCPStreamData(int socketDescriptor, sockaddr_in* address)
        : socketDescriptor(socketDescriptor)
{
    //std::array<char, 30> ipAddress{};
    char ipAddress[50];
    inet_ntop(PF_INET,(struct in_addr*)&(address->sin_addr.s_addr),
            ipAddress, sizeof(ipAddress)-1);
    peerIP = ipAddress;
    peerPort = ntohs(address->sin_port);
}

ssize_t TCPStreamData::send(const char *buffer, size_t length) {
    return write(socketDescriptor, buffer, length);
}

ssize_t TCPStreamData::receive(char *buffer, size_t length) {
    read(socketDescriptor, buffer, length);
}


std::string TCPStreamData::getPeerIP() const {
    return peerIP;
}

int TCPStreamData::getPeerPort() const {
    return peerPort;
}
