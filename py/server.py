'''
Author: Once day
Date: 2021-11-04 10:02:52
LastEditors: Please set LastEditors
LastEditTime: 2021-11-04 04:36:25
Description: 也信美人终作土，不堪幽梦太匆匆！
Encoder=utf-8,Email:once_day@qq.com
'''

import cv2
import socket 
import threading
import sys
import time
import queue
import numpy

class MYPICTURE():
    HEIGHT=720          #获取的图像的高
    #帧的水平宽度，双目，每个分辨率1280*720
    #帧的竖直高度，720
    ALLWIDTH=2560       #两个摄像头合起来的宽度
    WIDTH=1280          #单个摄像头截取图像的高
    HEIGHT_RANGLE=240   #所在背景大概占据1/3的像素
    WIDTH_RANGLE=640    #所在最大的水平查找范围占据1/2像素

    PICTURE_HEIGHT_MIN = int(HEIGHT/2-HEIGHT_RANGLE/2)#确保是整数
    PICTURE_HEIGHT_MAX = int(HEIGHT/2+HEIGHT_RANGLE/2)#确保是整数
    PICTURE_WIDTH_MIN  = int(WIDTH/2-WIDTH_RANGLE/2)
    PICTURE_WIDTH_MAX  = int(WIDTH/2+WIDTH_RANGLE/2)

my_imag=MYPICTURE()#实例化，生成图片处理默认全局信息

connect_flag=1#判断网络连接是否成立

class mysocket_server():
    def __init__(self,type=socket.SOCK_STREAM,address='',port=0,bufsize=1024):
        self.mytcp=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        #socket.SOCK_DGRAM  数据报式socket , for UDP
        #socket.SOCK_STREAM 流式socket , for TCP
        #socket.AF_INET  服务器之间网络通信
        #服务端地址为自身地址或不需要
        #创建套接字，即端口
        self.mytcp.bind((address,port))
        #绑定IP和端口
    def set_queue(self,send_que,rece_que):
        self.send_que=send_que#提供队列对象
        self.rece_que=rece_que

    def listen(self,backlog=1):
        self.mytcp.listen(backlog)
    
    def setup(self):
        while 1:
            cilent,server=self.mytcp.accept()
            cilent.settimeout(5)#超时限制
            print('ip:{}'.format(cilent))
            try:
                while 1:
                    receive = cilent.recv(1024)#指定一次最大接收数据量
                    if len(receive):self.rece_que.put(receive)
                    data=self.send_que.get(block=True, timeout=None)#获取队列消息,长度
                    #if not data:continue
                    totalsent=0
                    while totalsent<len(data):
                        sent=cilent.send(data)#返回发送数量
                        totalsent = totalsent + sent
                    data=self.send_que.get(block=True, timeout=None)#获取队列消息，图片数据
                    #if not data:continue
                    totalsent=0
                    while totalsent<len(data):
                        sent=cilent.send(data)#返回发送数量
                        totalsent = totalsent + sent
            except:
                cilent.close()

class myThread_1 (threading.Thread):
    def __init__(self, threadID, name,po,send_que,rece_que):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.po=po
        self.send_que=send_que
        self.rece_que=rece_que
    def run(self):
        print ("开始线程：" + self.name)
        print(" 监听端口40000")
        sertcp=mysocket_server(port=self.po)
        sertcp.set_queue(self.send_que,self.rece_que)#传递队列对象
        sertcp.listen(1)
        sertcp.setup()
        print ("退出线程：" + self.name)


if __name__ =="__main__": #单文件测试函数
    cap = cv2.VideoCapture(0)#非默认摄像头
    if not cap.isOpened():
        print('摄像头打开有问题,退出程序！')
        exit()
    print("摄像头已打开")#默认速率是30fps
    #for i in range(47):#测试代码，测试可设置的参数
    #    print("No.={} parameter={}".format(i,cap.get(i)))
    print("摄像头参数已设置！")
    cap.set(cv2.CAP_PROP_FRAME_WIDTH,my_imag.WIDTH)#原始获取的图像的宽度
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT,my_imag.HEIGHT)#原始获取的图像的高度
    q1=queue.Queue(10)#限定10帧
    q2=queue.Queue(10)
    try:
        th1=myThread_1(threadID=1,name='Thread-1',po=40000,send_que=q1,rece_que=q2)
        th1.start()
    except:
        print("网络参数不正确")

    while 1:
        ret, frame = cap.read()#读取图像
        #压缩参数，后面cv2.imencode将会用到，对于jpeg来说，15代表图像质量，越高代表图像质量越好为 0-100，默认95
        encode_param=[int(cv2.IMWRITE_JPEG_QUALITY),15]
        if ret==True:#获取到新图片后更新，无需翻转
            left=frame[my_imag.PICTURE_HEIGHT_MIN:my_imag.PICTURE_HEIGHT_MAX,my_imag.PICTURE_WIDTH_MIN:my_imag.PICTURE_WIDTH_MAX]
            #cv2.imencode将图片格式转换(编码)成流数据，赋值到内存缓存中;主要用于图像数据格式的压缩，方便网络传输
		    #'.jpg'表示将图片按照jpg格式编码。
            rece_data=q2.get(block=True, timeout=None)
            if(len(rece_data)):
                result, imgencode = cv2.imencode('.jpg', frame, encode_param)
                #建立矩阵
                data = numpy.array(imgencode)
                #将numpy矩阵转换成字符形式，以便在网络中传输
                stringData = data.tostring()
                st1=str.encode(str(len(stringData)).ljust(16))
                q1.put(st1, block=True, timeout=None)
                q1.put(data,block=True, timeout=None)
            cv2.imshow('SERVER',left)#显示图像
        key = cv2.waitKey(20)#这里强制卡为20fps的速率
        if key  == ord('q'):  #判断是哪一个键按下
            break
    print("退出主线程")