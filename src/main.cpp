/*
 * @Author: your name
 * @Date: 2021-11-04 02:37:38
 * @LastEditTime: 2021-11-07 02:33:48
 * @LastEditors: Once day
 * @Description: In User Settings Edit
 * @FilePath: /ResPiClint/src/main.cpp
 */
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include "tcp_net_socket.h"
#include "tcp_camera.h"
#include "string.h"
#include "gpio.h"
#include "cvui.h"
using namespace cv;
using namespace std;
#define WINDOW_NAME "控制器"
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 800
#define FONT_COLOR  0x32CD32

#define Camera1_IP  "192.168.0.11"
#define Camera1_PORT1 40000
#define Camera1_PORT2 50000
#define Camera2_IP  "192.168.0.12"
#define Camera2_PORT1 40000
#define Camera2_PORT2 50000

tcp_camera *camera1;
tcp_camera *camera2;
pthread_t thread1;
pthread_t thread2;
pthread_t heartthread;
pthread_t gpiothread;
time_t start=0;
int resulttype=0;
volatile int data_flag=0;

void camera1_thread(void);
void camera2_thread(void);
void gpio_thread(void);

void alarm()
{
	gpio gpio7=gpio(7);
	gpio7.open(0);
	gpio7.off();
	sleep(1);
	gpio7.on();
}
void gpio_thread(void){
	gpio resGpio[3]={gpio(0),gpio(2),gpio(3)};
	resGpio[0].open(1);
	resGpio[1].open(1);
	resGpio[2].open(1);
	while (1)
	{
		while (resGpio[0].read()==0&&resGpio[1].read()==0&&resGpio[2].read()==0);
		delay(2);
		if (resGpio[0].read()) {//只计算L
			camera2->testIndex=camera1->testIndex=1;
			camera1->pen_data.line=0;
			camera1->pen_data.theta=0;
			camera1->StartTest(1);
			camera2->StartTest(1);
			pthread_create(&thread1,NULL,(void *)&camera1_thread,NULL);
			pthread_create(&thread2,NULL,(void *)&camera2_thread,NULL);
			start=time(NULL);
		}
		if (resGpio[1].read()) {//计算L,并判断thera
			camera2->testIndex=camera1->testIndex=2;
			camera1->pen_data.line=0;
			camera1->pen_data.theta=0;
			camera1->StartTest(2);
			camera2->StartTest(2);
			pthread_create(&thread1,NULL,(void *)&camera1_thread,NULL);
			pthread_create(&thread2,NULL,(void *)&camera2_thread,NULL);
			start=time(NULL);
		}
		if (resGpio[2].read()) {//计算L,并计算thera			
			camera2->testIndex=camera1->testIndex=3;
			camera1->pen_data.line=0;
			camera1->pen_data.theta=0;
			camera1->StartTest(3);
			camera2->StartTest(3);
			pthread_create(&thread1,NULL,(void *)&camera1_thread,NULL);
			pthread_create(&thread2,NULL,(void *)&camera2_thread,NULL);
			start=time(NULL);
		}
		alarm();	
		delay(2000);
		//std::cout << "gpio" << std::endl;		
	}
	
}
//获取两个节点传过来的信息
void camera1_thread(void){
	if(camera1!=NULL){
		//std::cout << "getinfo start" << std::endl;
		camera1->getsysinfo();
		while(camera2->testIndex!=0);
		//std::cout << "getinfo end" << std::endl;
		camera1->deal_data(*camera2);
		alarm();
		data_flag=1;
		resulttype=camera1->testIndex;
		camera1->testIndex=0;
		//camera2->testIndex=1;
	}	
}
void camera2_thread(void){
	if(camera2!=NULL){
		camera2->getsysinfo();
		camera2->testIndex=0;
	}	
}
void heart_thread(void){
	while(1){
		camera1->HeartSend();
		camera2->HeartSend();
		sleep(1);
	}
}
int main(void)
{
	//sleep(10);
	Mat img1,img2,frame;
    Socket s[2][2]; 
	int key=0;
	float theta=0;
	int sfd[2][2]={-1,-1,-1,-1};
	cv::namedWindow(WINDOW_NAME);
	cv::moveWindow(WINDOW_NAME, 10, 10);
	cvui::init(WINDOW_NAME);
	while(sfd[0][1]-sfd[0][0]!=1||sfd[1][0]-sfd[0][1]!=1){	
		Mat frame = cv::Mat(WINDOW_WIDTH, WINDOW_HEIGHT, CV_8UC3);
		sfd[0][0]=s[0][0].Connect(Camera1_IP, Camera1_PORT1);
		sfd[0][1]=s[0][1].Connect(Camera1_IP, Camera1_PORT2);
		sfd[1][0]=s[1][0].Connect(Camera2_IP, Camera2_PORT1);
		sfd[1][1]=s[1][1].Connect(Camera2_IP, Camera2_PORT2);
		//std::cout<<"[" << sfd[0][0]<<sfd[0][1]<<sfd[1][0]<<sfd[1][1] << "]"<<std::endl;
		frame = cv::Scalar(49, 52, 49);
		cvui::printf(frame, 0, 200, 1, 0xff0000, "CONNECT ERROR(%d%d%d%d)", sfd[0][0],sfd[0][1],sfd[1][0],sfd[1][1]);
		cvui::update();
		cv::imshow(WINDOW_NAME, frame);
		waitKey(10);
	}
	camera1=new tcp_camera(sfd[0][0],sfd[0][1]);
	camera2=new tcp_camera(sfd[1][0],sfd[1][1]);
	camera1->testIndex=camera2->testIndex=0;
	
	pthread_create(&heartthread,NULL,(void *)&heart_thread,NULL);
	pthread_create(&gpiothread,NULL,(void *)&gpio_thread,NULL);
	while(key!='q'){
		// img1=imread("/home/pi/Desktop/WorkSpace/ResPiClint/picture/1.jpg");
		// img2=img1;
		img1= camera1->ReadImg();
		img2= camera2->ReadImg();
		//img2=img1;
		int height = img1.rows;
		int width1 = img1.cols;
		int width2 = img2.cols;
		frame.create(height, width1 + width2, img1.type());
		Mat r1 = frame(Rect(0, 0, width1, height));
		img1.copyTo(r1);
		Mat r2 = frame(Rect(width1, 0, width2, height));
		img2.copyTo(r2);
		resize(frame,frame,Size(WINDOW_WIDTH,WINDOW_HEIGHT));

		if (cvui::button(frame, 20, 20, "TEST 1")) {//只计算L
			camera2->testIndex=camera1->testIndex=1;
			camera1->pen_data.line=0;
			camera1->pen_data.theta=0;
			camera1->StartTest(1);
			camera2->StartTest(1);
			pthread_create(&thread1,NULL,(void *)&camera1_thread,NULL);
			pthread_create(&thread2,NULL,(void *)&camera2_thread,NULL);
			start=time(NULL);
		}
		if (cvui::button(frame, 20, 60, "TEST 2")) {//计算L,并判断thera
			camera2->testIndex=camera1->testIndex=2;
			camera1->pen_data.line=0;
			camera1->pen_data.theta=0;
			camera1->StartTest(2);
			camera2->StartTest(2);
			pthread_create(&thread1,NULL,(void *)&camera1_thread,NULL);
			pthread_create(&thread2,NULL,(void *)&camera2_thread,NULL);
			start=time(NULL);
		}
		if (cvui::button(frame, 20, 100, "TEST 3")) {//计算L,并计算thera
			camera2->testIndex=camera1->testIndex=3;
			camera1->pen_data.line=0;
			camera1->pen_data.theta=0;
			camera1->StartTest(3);
			camera2->StartTest(3);
			pthread_create(&thread1,NULL,(void *)&camera1_thread,NULL);
			pthread_create(&thread2,NULL,(void *)&camera2_thread,NULL);
			start=time(NULL);
		}
		//选择样本点多的显示
		tcp_camera *camera=camera1;
		if(data_flag)
		{
			if(camera1->get_line()<0.50f||camera1->get_line()>1.60f){
				camera=camera2;
				camera1->pen_data.line=camera2->pen_data.line;
			}
			if(camera2->get_line()<0.50f||camera2->get_line()>1.60f) {
				camera=camera1;
			}
			if(camera1->get_line()>=0.50f&&camera1->get_line()<=1.60f&&camera2->get_line()>=0.50f&&camera2->get_line()<=1.60f){
				cout<<"normal"<<endl;
				camera=camera1;
				//float l1=camera1->get_line();
				//float l2=camera2->get_line();
				//if(l1-l2<0.15f&&l1-l2>-0.15f)
				//{
				//	camera1->pen_data.line=(camera1->pen_data.line+camera2->pen_data.line)/2;
				//}
				//else
				//{
				//	camera1->pen_data.line=camera2->pen_data.line;
				//}
				camera1->pen_data.line=(camera1->pen_data.line+camera2->pen_data.line)/2;
			}
			data_flag=0;
		}

		if(resulttype==1){
			theta=0;
		}
		else if(resulttype==2){
			theta= camera1->get_theta()*180/3.14159;
			if(theta<45)theta=0;
			else theta=90;			
		}else if(resulttype==3){
			theta= camera1->get_theta()*180/3.14159;
		}
		char text[20];
		int font_face = FONT_HERSHEY_COMPLEX; 
		double font_scale = 1;
		int thickness = 2;
		memset(text,0,20);
		sprintf(text,"TEST %d", camera->testIndex);
		putText(frame,text, Point(800, 20), font_face, font_scale,Scalar(255,0,0) , thickness, 8, 0);

		memset(text,0,20);
		sprintf(text,"LEN: %2.3f m", camera->get_line() -0.077f);	
		putText(frame,text, Point(800, 80), font_face, font_scale,Scalar(255,0,0), thickness, 8, 0 );
		
		memset(text,0,20);
		sprintf(text,"ANG: %3.2f", theta);		
		putText(frame,text, Point(800, 140), font_face, font_scale,Scalar(255,0,0) , thickness, 8, 0);
		if(camera2->testIndex==0){
			putText(frame, "TIME: 0 s" ,Point(800, 200), font_face, font_scale,Scalar(255,0,0), thickness, 8, 0);
		}
		else{
			memset(text,0,20);
			sprintf(text,"TIME: %d s",time(NULL)-start);	
			putText(frame, text,Point(800, 200), font_face, font_scale, Scalar(255,0,0), thickness, 8, 0);
		}
		cvui::update();
		cv::imshow(WINDOW_NAME, frame);
		key=waitKey(10);
	}

	delete camera1;
	delete camera2;
	return 0;
}
