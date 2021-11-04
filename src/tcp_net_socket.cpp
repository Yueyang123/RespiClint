/*
 * @Descripttion: 
 * @version: 
 * @Author: Yueyang
 * @email: 1700695611@qq.com
 * @Date: 2021-04-11 12:39:23
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2021-11-04 04:48:56
 */
#include "tcp_net_socket.h"
Socket::Socket()
{
    
}
Socket::Socket(const char* ip, int port)
{
    this->ip=ip;
    this->port=port;
    oldfd = socket(AF_INET, SOCK_STREAM, 0);//首先创建一个socket，向系统申请
    if(oldfd == -1)
    {
        perror("socket");
        exit(-1);
    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(struct sockaddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(ip);//或INADDR_ANY
    if(bind(oldfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        close(oldfd);
        exit(-1);
    }
    if(listen(oldfd, 10) == -1)//监听它，并设置其允许最大的连接数为10个
    {
        perror("listen");
        close(oldfd);
        exit(-1);
    }
}

 Socket::~Socket()
 {
     close(oldfd);
     close(newfd);
 }

int Socket::Accept()
 {
    struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(struct sockaddr));
    socklen_t addrlen = sizeof(struct sockaddr);
    newfd = accept(oldfd, (struct sockaddr*)&clientaddr, &addrlen);
    //sfd接受客户端连接，并创建新的socket为new_fd，将请求连接的客户端的ip、port保存在结构体clientaddr中
    if(newfd == -1)
    {
        perror("accept");
        close(newfd);
        exit(-1);
    }
    printf("%s %d success connect...\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
    return newfd;
 }

 int Socket::Connect(const char* ipt, int portt)   //用于客户端的连接
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);//向系统注册申请新的socket
    if(sfd == -1)
    {
        perror("socket");
        return sfd;
    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(struct sockaddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(portt);
    serveraddr.sin_addr.s_addr = inet_addr(ipt);
        if(connect(sfd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr)) == -1)
        //将sfd连接至制定的服务器网络地址serveraddr
        {
        perror("connect");
        close(sfd);
        return sfd;
        }
    return sfd;
}