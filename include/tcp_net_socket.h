/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2021-04-11 12:39:41
 * @LastEditors: Yueyang
 * @LastEditTime: 2021-04-11 13:21:15
 */
#ifndef __TCP__NET__SOCKET__H
#define __TCP__NET__SOCKET__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

class Socket
{
    public:
    Socket(const char* ip, int port);
    Socket();
    ~Socket();
    int Accept();
    int Connect(const char* ipt, int portt);
    private:
    int oldfd;//Socket后的文件描述
    int newfd;//Accept后的文件描述
    const char* ip;
    int port;
};

#endif
