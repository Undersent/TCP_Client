//
// Created by rafal on 01.09.17.
//
#include <string>
#include <netinet/in.h>

#ifndef TCP_SERVER_TCPSTREAMDATA_H
#define TCP_SERVER_TCPSTREAMDATA_H


class TCPStreamData {
private:
    int socketDescriptor{};
    std::string peerIP{};
    int peerPort{};

public:

    virtual ~TCPStreamData();

    friend class AcceptorToTCPServer;
    friend class ConnectorToTCPServer;

    ssize_t send(const char *buffer, size_t length);
    ssize_t receive(char* buffer, size_t length);
    std::string getPeerIP() const;
    int getPeerPort() const;

private:
    TCPStreamData() = default;
    TCPStreamData(int socketDescriptor, struct sockaddr_in* address);
    TCPStreamData(const TCPStreamData& stream);


};


#endif //TCP_SERVER_TCPSTREAMDATA_H
