cmake_minimum_required(VERSION 3.8)
project(TCP_Client)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES ConnectorToTCPServer.h ConnectorToTCPServer.cpp TCPStreamData.h TCPStreamData.cpp
        Client.cpp RSA/RSA.cpp RSA/RSA.h)
add_executable(TCP_Client ${SOURCE_FILES})