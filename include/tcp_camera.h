/*
 * @Author: your name
 * @Date: 2021-11-04 06:27:58
 * @LastEditTime: 2021-11-04 22:36:36
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ResPiClint/include/tcp_camera.h
 */
 #ifndef TCP_CAMERA_H
 #define TCP_CAMERA_H
 #include <unistd.h>
 #include <string>
 using namespace std;
 using namespace cv;

 class tcp_camera
 {
 public:
     int testIndex;
         struct _pen_data
         {
            int new_data;
            float line;
            float theta;
            float A;
            int max_pnum;
            int min_pnum;
            struct _point{
               float x_coor;
               float r_time;
            } max_point[100],min_point[100];
         }pen_data;
      tcp_camera(int sfd1,int sfd2);
      tcp_camera(){};
      ~tcp_camera(){close(sfd1);close(sfd2);};
      Mat ReadImg();
      void HeartSend();
      void StartTest(int index);
      void getsysinfo();
      void deal_data(class tcp_camera &ca2);
      float tcp_camera::get_line(void);
      float tcp_camera::get_theta(void);
 private:
    int sfd1;//面向图像流的socket
    int sfd2;//面向命令流的socket

    char data[20000];
    char data_info[4000];
    int RecvLength();
    Mat RecvImg(int length);

   
 };




 #endif // !TCP_CAMERA_H

 
