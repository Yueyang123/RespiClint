/*
 * @Author: your name
 * @Date: 2021-11-04 06:27:58
 * @LastEditTime: 2021-11-04 06:48:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ResPiClint/include/tcp_camera.h
 */
 #ifndef TCP_CAMERA_H
 #define TCP_CAMERA_H
 
 #include <string>
 using namespace std;
 using namespace cv;
 class tcp_camera
 {
 public:
     tcp_camera(int sfd);
    Mat ReadImg();
 private:
    int sfd;
    int RecvLength();
    Mat RecvImg(int length);
 };

 #endif // !TCP_CAMERA_H

 
