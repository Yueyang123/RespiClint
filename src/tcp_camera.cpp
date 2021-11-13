/*
 * @Author: your name
 * @Date: 2021-11-04 06:26:41
 * @LastEditTime: 2021-11-07 04:06:52
 * @LastEditors: Once day
 * @Description: In User Settings Edit
 * @FilePath: /ResPiClint/src/tcpcamera.cpp
 */
#include <pthread.h>
#include <assert.h>
#include <opencv2/opencv.hpp>
#include "tcp_camera.h"
#include "tcp_net_socket.h"
#include <unistd.h>
using namespace cv;

//图像线程
/*********************************/
//向摄像头节点请求图像数据
tcp_camera::tcp_camera(int sfd1,int sfd2){
	this->sfd1=sfd1;
	this->sfd2=sfd2;
	this->pen_data.new_data=0;
	this->pen_data.A=1.20668f;
}
int tcp_camera::RecvLength()
{
	char lengthBuf[16];
	memset(lengthBuf,0,16);
    recv(sfd1,lengthBuf,16,0);
	return atoi(lengthBuf);
}

Mat tcp_camera::RecvImg(int length)
{
	int newlength;
	Mat res = cv::Mat(500, 500, CV_8UC3);
	memset(data,0,sizeof(data));
	char *p=data;
    while(length>0){
        newlength = recv(sfd1,p,length,0);
        if (newlength<0)break;
        p+=newlength;
        length-=newlength;
	}
	vector<char> imgdata((char*)data,p);
	//std::cout<< p-data << std::endl;
	if(p-data>1000)
		res= cv::imdecode(imgdata,CV_LOAD_IMAGE_COLOR);
	return res;
}

Mat tcp_camera::ReadImg()
{
	char SUBSCRIBE[]={0xA1,0XA2};
	send(sfd1,SUBSCRIBE,2,0);
	int length=RecvLength();
	Mat res= RecvImg(length);
	return res;
}

//命令收发线程
/*********************************/

void tcp_camera::HeartSend(){
	char HEART[]="syn";
	send(sfd2,HEART,3,0);
}

void tcp_camera::StartTest(int index){
	char cmd[6] ="test0";
	switch (index)
	{
		case 1:
			cmd[4] ='1';
			send(sfd2,cmd,5,0);
			break;
		case 2:
			cmd[4] ='2';
			send(sfd2,cmd,5,0);
			break;
		case 3:
			cmd[4] ='3';
			send(sfd2,cmd,5,0);
			break;

		default:
			break;
	}
}

void tcp_camera::getsysinfo(){
	memset(data_info,0,sizeof(data_info));
	int ret=0;
	int sum=14;
	char *rdata=data_info;
	int max_amount=0;
	int min_amount=0;
	while (ret<14)
	{
		ret+=recv(sfd2,data_info+ret,14,0);
	}
	//std::cout << data_info << std::endl;
	rdata+=3;//第一个数据
	char temp[6];
	memset(temp,0,6);
	memcpy(temp ,rdata,4);
	this->pen_data.line=atoi(temp)/1000.0f;
	rdata+=4+1;
	memset(temp,0,6);
	memcpy(temp ,rdata,2);
	this->pen_data.min_pnum=atoi(temp);
	rdata+=2+1;
	memset(temp,0,6);
	memcpy(temp ,rdata,2);
	this->pen_data.max_pnum=atoi(temp);
	rdata+=2+1;
	max_amount=this->pen_data.max_pnum;
	min_amount=this->pen_data.min_pnum;
	sum =max_amount+min_amount;
	sum=sum*(3+10)+2;//每个点包含的数据项数
	ret=0;
	while (ret<sum)
	{
		ret+=recv(sfd2,data_info+ret+14,2000,0);
	}
	std::cout << data_info << std::endl;
	rdata+=1;
	for(int i=0;i<max_amount;i++)//先接受大的数据
	{
		memset(temp,0,6);
		memcpy(temp ,rdata,5);
		this->pen_data.max_point[i].x_coor=(float)(atoi(temp))/100.0f;
		rdata+=5+1;

		memset(temp,0,6);
		memcpy(temp ,rdata,5);
		this->pen_data.max_point[i].r_time=(float)(atoi(temp))/1000.0f;
		rdata+=5+1;
		rdata++;
	}
	for(int i=0;i<min_amount;i++)//先接受大的数据
	{
		memset(temp,0,6);
		memcpy(temp ,rdata,5);
		this->pen_data.min_point[i].x_coor=(float)(atoi(temp))/100.0f;
		rdata+=5+1;

		memset(temp,0,6);
		memcpy(temp ,rdata,5);
		this->pen_data.min_point[i].r_time=(float)(atoi(temp))/1000.0f;
		rdata+=5+1;
		rdata++;
	}
	this->pen_data.new_data=1;
}

#include "math.h"
#include<algorithm>
using namespace std;
void tcp_camera::deal_data(class tcp_camera &ca2)
{
	struct _temp{
		float x_coor;
        float r_time;
	};
	_temp *c1_max=(_temp*)(this->pen_data.max_point);
	_temp *c1_min=(_temp*)(this->pen_data.min_point);
	_temp *c2_max=(_temp*)(ca2.pen_data.max_point);
	_temp *c2_min=(_temp*)(ca2.pen_data.min_point);
	int c1_max_num=this->pen_data.max_pnum;
	int c1_min_num=this->pen_data.min_pnum;
	int c2_max_num=ca2.pen_data.max_pnum;
	int c2_min_num=ca2.pen_data.min_pnum;
	int c1_max_start=0;
	int c1_min_start=0;
	int c2_max_start=0;
	int c2_min_start=0;

	float sum1=0.0;
	// //float sum2=0.0;
	// for(int i=0;i<this->pen_data.max_pnum;i++)
	// 	std::cout <<"("<< this->pen_data.max_point[i].x_coor<<" "<< this->pen_data.max_point[i].r_time<<")"<< std::endl;
	// for(int i=0;i<this->pen_data.min_pnum;i++)
	// 	std::cout <<"("<< this->pen_data.min_point[i].x_coor<<" "<< this->pen_data.min_point[i].r_time<<")" << std::endl;

	if(this->pen_data.line==0)
	{
		this->pen_data.theta=0.0f;
		ca2.pen_data.theta=0.0f;
	}else if(ca2.pen_data.line==0)
	{
		this->pen_data.theta=1.570795f;
		ca2.pen_data.theta=1.570795f;
	}else
	{
		int cal_flag=1;
		int first_flag=0;
		float alen1=0;
		int anum=c1_max_num>c1_min_num ? c1_min_num:c1_max_num;
		for(int i=0;i<anum;i++)
		{
			alen1+=std::abs(this->pen_data.max_point[i].x_coor-this->pen_data.min_point[i].x_coor)/anum;
		}
		std::cout<<"ca1 adl:"<<alen1<<std::endl;
		if(alen1<5.1f)
		{
			first_flag=1;
			this->pen_data.theta=0.0f;
			ca2.pen_data.theta=0.0f;
			//摄像头1死区
			this->pen_data.line=ca2.pen_data.line;
			cal_flag=0;
			std::cout<<"camera 1 dead!"<<std::endl;
		}
		float alen2=0;
		anum=c2_max_num>c2_min_num ? c2_min_num:c2_max_num ;
		for(int i=0;i<anum;i++)
		{
			alen2+=std::abs(ca2.pen_data.max_point[i].x_coor-ca2.pen_data.min_point[i].x_coor)/anum;
		}
		std::cout<<"ca2 adl:"<<alen2<<std::endl;
		if(alen2<5.1f)
		{
			first_flag=1;
			this->pen_data.theta=1.570795f;
			ca2.pen_data.theta=1.570795f;
			//摄像头2死区
			ca2.pen_data.line=this->pen_data.line;
			cal_flag=0;
			std::cout<<"camera 2 dead!"<<std::endl;
		}
		//异常检测只检测第一个摄像头的数据
		int temp1=std::abs(this->pen_data.max_pnum+this->pen_data.min_pnum-ca2.pen_data.max_pnum-ca2.pen_data.min_pnum);
		if((first_flag==0)&&(std::abs(this->pen_data.max_pnum-this->pen_data.min_pnum)>2||temp1>2))
		{
			this->pen_data.theta=0.0f;
			ca2.pen_data.theta=0.0f;
			cal_flag=0;
		}
		if(cal_flag)
		{
			for(int i=0,j=0;i<c1_max_num&&j<c2_min_num;)
			{
				if(c1_max[i].r_time-c2_min[j].r_time>1.0f)
				{
					j++;
				}else if(c1_max[i].r_time-c2_min[j].r_time<-1.0f)
				{
					i++;
				}else
				{
					c1_max_start=i;
					c1_min_start=i;
					c2_max_start=j;
					c2_min_start=j;
					break;
				}
			}
			//std::cout<<"i="<<c1_max_start<<"j="<<c2_min_start<<std::endl;
			/*for(int i=0,j=0;i<c1_min_num&&j<c2_min_num;)
			{
				if(c1_min[i].r_time-c2_min[j].r_time>0.5)
				{
					j++;
				}else if(c1_min[i].r_time-c2_min[j].r_time>0.5)
				{
					i++;
				}else
				{
					c1_min_start=i;
					c2_min_start=j;
					break;
				}
			}*/

			float c1_dx,c2_dx;
			float ata[100]={0.0};
			int count=0;
			for(int i=c1_max_start,j=c2_max_start;i<c1_max_num&&i<c1_min_num&&j<c2_max_num&&j<c2_min_num;i++,j++)
			{
				c1_dx=c1_max[i].x_coor-c1_min[i].x_coor;
				c2_dx=c2_max[j].x_coor-c2_min[j].x_coor;
				std::cout << "["<< c1_dx<<" "<<c2_dx<<"]" << std::endl;
				ata[count]=c1_dx/c2_dx;
				count++;
			}
			sort(ata,ata+count);
			for(int i=1;i<count-1;i++){
				std::cout << ata[i] << " ";
				sum1+=ata[i];
			}
			std::cout << c1_max_start <<" "<< c2_max_start<<" "<<count<<" "<<sum1 << std::endl;
			//std::cout<<"orignal value:"<<sum1/(count-2)<<std::endl;
			std::cout<<"orignal angle:"<<std::atan(sum1/(count-2))*180/3.14159<<std::endl;
			sum1=std::atan(this->pen_data.A*sum1/(count-2));
			std::cout<<"change value:"<<sum1*180/3.14159<<std::endl;
			this->pen_data.theta=sum1;
			ca2.pen_data.theta=sum1;
		}
	}
	//std::cout<<",修正值:"<<this->pen_data.theta*180/3.14159<<",修正系数:"<<this->pen_data.A << std::endl;

}

float tcp_camera::get_line(void)
{
   return this->pen_data.line;
}

float tcp_camera::get_theta(void)
{
	return this->pen_data.theta;
}

/*********************************/