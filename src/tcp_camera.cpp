/*
 * @Author: your name
 * @Date: 2021-11-04 06:26:41
 * @LastEditTime: 2021-11-04 06:54:26
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ResPiClint/src/tcpcamera.cpp
 */
#include <pthread.h>
#include <assert.h>
#include <opencv2/opencv.hpp>
#include "tcp_camera.h"
#include "tcp_net_socket.h"
using namespace cv;
char data[30000];
char SUBSCRIBE[]={0xA1,0XA2};

tcp_camera::tcp_camera(int sfd){
	this->sfd=sfd;
}
int tcp_camera::RecvLength()
{
	char lengthBuf[16];
	int length=16;
	int newlength;
	memset(lengthBuf,0,16);
    newlength = recv(sfd,lengthBuf,16,0);
	return atoi(lengthBuf);
}

Mat tcp_camera::RecvImg(int length)
{
	int newlength;
	memset(data,0,sizeof(data));
	char *p=data;
    while(length>0){
        newlength = recv(sfd,p,length,0);
        if (newlength<0)break;
        p+=newlength;
        length-=newlength;
	}
	vector<char> imgdata((char*)data,p);
	Mat res= cv::imdecode(imgdata,CV_LOAD_IMAGE_COLOR);
	return res;
}

Mat tcp_camera::ReadImg()
{
	send(sfd,SUBSCRIBE,2,0);
	int length=RecvLength();
	Mat res= RecvImg(length);
	return res;
}
