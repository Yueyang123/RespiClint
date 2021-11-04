/*
 * @Author: your name
 * @Date: 2021-11-04 02:37:38
 * @LastEditTime: 2021-11-04 06:52:06
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ResPiClint/src/main.cpp
 */
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <assert.h>
#include "tcp_net_socket.h"
#include "tcp_camera.h"
#include "string.h"
#include "cvui.h"
using namespace cv;
using namespace std;
#define WINDOW_NAME "控制器"
 
#define Camera1_IP  "192.168.1.106"
#define Camera1_PORT 40000
#define Camera2_IP  "192.168.1.3"
#define Camera2_PORT 8080

int main(void)
{
    cv::namedWindow(WINDOW_NAME);
    Socket s; 
	Mat src;
	int sfd=-1;

    sfd= s.Connect(Camera1_IP, Camera1_PORT);
	tcp_camera c1= tcp_camera(sfd);
	while(1){
		src= c1.ReadImg();
		cv::imshow(WINDOW_NAME, src);
		waitKey(10);
	}
	// cv::Mat frame = cv::Mat(500, 1000, CV_8UC3);
	// int count = 0;
	// // 初始化窗口
	// cv::namedWindow(WINDOW_NAME);
    // cv::setWindowProperty(WINDOW_NAME, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN );
	// cvui::init(WINDOW_NAME);
	// while (cv::waitKey(30)!=27) {
	// 	// 在位置110，80显示按钮
	// 	if (cvui::button(frame, 110, 80, "START")) {
	// 		// 计数
	// 		count++;
	// 	}
	// 	// 在位置（250，90）显示，字号大小为0.4颜色为红色
	// 	cvui::printf(frame, 250, 90, 0.4, 0xff0000, "Button click count: %d", count);
	// 	//刷新
	// 	cvui::update();
	// 	// 显示
	// 	cv::imshow(WINDOW_NAME, frame);
	// }
	return 0;
}
