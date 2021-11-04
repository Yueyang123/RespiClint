'''
Author: your name
Date: 2021-11-04 04:06:23
LastEditTime: 2021-11-04 04:06:26
LastEditors: Please set LastEditors
Description: In User Settings Edit
FilePath: /ResPiClint/test.py
'''
import cv2
import socket 
import queue
import numpy
import sys
import time
def recvall(connect,length):
    buf = b''#buf是一个byte类型
    while length:
		#接受TCP套接字的数据。数据以字符串形式返回，count指定要接收的最大数据量.
        newbuf = connect.recv(length)
        if not newbuf:break
        buf += newbuf
        length -= len(newbuf)
    return buf

if __name__ =="__main__": #单文件测试函数
    #建立sock连接
    #address要连接的服务器IP地址和端口号
    address = ('127.0.0.1', 40000)
    try:
    	#建立socket对象
    	#socket.AF_INET：服务器之间网络通信 
    	#socket.SOCK_STREAM：流式socket , for TCP
    	sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		#开启连接
    	sock.connect(address)
    except socket.error as msg:
    	print(msg)
    	sys.exit(1)
    while 1:
        start = time.time()#用于计算帧率信息
        sock.send(b'sssssss')#随机发送数据
        length = recvall(sock,16)#获得图片文件的长度,16代表获取长度
        stringData = recvall(sock, int(length))#根据获得的文件长度，获取图片文件
        data = numpy.frombuffer(stringData, numpy.uint8)#将获取到的字符流数据转换成1维数组
        decimg=cv2.imdecode(data,cv2.IMREAD_COLOR)#将数组解码成图像
        cv2.imshow('SERVER',decimg)#显示图像
        end = time.time()
        seconds = end - start
        fps  = 1/seconds
        sock.send(bytes(str(int(fps)),encoding='utf-8'))
        key = cv2.waitKey(10)#这里强制卡为20fps的速率
        if key  == ord('q'):  #判断是哪一个键按下
            break
    sock.close()
    cv2.destroyAllWindows()