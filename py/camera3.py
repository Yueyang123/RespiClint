'''
Author: Once day
Date: 2021-11-04 10:02:52
LastEditors: Once day
LastEditTime: 2021-11-06 21:29:34
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
import matplotlib.pyplot as plt


class MYPICTURE():
    HEIGHT=720        #获取的图像的高
    #帧的水平宽度，双目，每个分辨率1280*720
    #帧的竖直高度，720
    WIDTH=1280         #单个摄像头截取图像的高
    HEIGHT_RANGLE=250   #所在背景大概占据1/3的像素
    WIDTH_RANGLE=350    #所在最大的水平查找范围占据1/2像素
    WIDTH_BIAS=30  #width_bias

    PICTURE_HEIGHT_MIN = int(HEIGHT/2-HEIGHT_RANGLE)#确保是整数
    PICTURE_HEIGHT_MAX = int(HEIGHT/2+150)#确保是整数
    PICTURE_WIDTH_MIN  = int(WIDTH/2-WIDTH_RANGLE/2-WIDTH_BIAS)
    PICTURE_WIDTH_MAX  = int(WIDTH/2+WIDTH_RANGLE/2-WIDTH_BIAS)

    PEN_EXLENGTH =0.0825  #单摆重心离线计长处的误差

my_imag=MYPICTURE()#实例化，生成图片处理默认全局信息

ball_color = 'red'
connect_flag=0 #
color_dist = {'red': {'Lower': numpy.array([156, 43, 46]), 'Upper': numpy.array([180, 255, 255])},
              'blue': {'Lower': numpy.array([100, 80, 46]), 'Upper': numpy.array([124, 255, 255])},
              'green': {'Lower': numpy.array([35, 43, 35]), 'Upper': numpy.array([90, 255, 255])},
              }

def recvall(connect,length):
    buf = b''#buf是一个byte类型
    while length:
		#接受TCP套接字的数据。数据以字符串形式返回，count指定要接收的最大数据量.
        newbuf = connect.recv(length)
        if not newbuf:break
        buf += newbuf
        length -= len(newbuf)
    return buf

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
        global connect_flag
        while 1:
            cilent,server=self.mytcp.accept()
            cilent.settimeout(5)#超时限制
            print('ip:{}'.format(cilent))
            connect_flag=1 #
            try:
                while 1:
                    receive = cilent.recv(1024)#指定一次最大接收数据量
                    if len(receive):
                        self.rece_que.put(receive,block=True, timeout=None)
                    else:
                        #print('444')
                        break	
                    data=self.send_que.get(block=True, timeout=None)#获取队列消息,长度
                    #if not data:continue
                    totalsent=0
                    while totalsent<len(data):
                        sent=cilent.send(data)#返回发送数量
                        totalsent = totalsent + sent
                        #print('111')
                    data=self.send_que.get(block=True, timeout=None)#获取队列消息，图片数据
                    #if not data:continue
                    totalsent=0
                    while totalsent<len(data):
                        sent=cilent.send(data)#返回发送数量
                        totalsent = totalsent + sent
                        #print('22')
            except:
                print('try error!')
            cilent.close()
            print('exit imge tcp!')
            connect_flag=0

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

class myThread_3(threading.Thread):
    def __init__(self, threadID, name, send_que,mysock):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.send_que=send_que
        self.mysock=mysock
    def run(self):
        print ("开始线程：" + self.name)
        print(" 接收端口50000")
        while 1:
            data=self.send_que.get(block=True, timeout=None)#获取队列消息，处理数据
            if data==b'stop':
                print("exit ctr send tcp")
                break#退出该线程
            totalsent=0
            while totalsent<len(data):
                sent=self.mysock.send(data)#返回发送数量
                totalsent = totalsent + sent
            print('ctr message had sent')


class myThread_2(threading.Thread):
    def __init__(self, threadID, name,po,send_que,rece_que):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.po=po
        self.send_que=send_que
        self.rece_que=rece_que
    def run(self):
        print ("开始线程：" + self.name)
        print(" 监听端口50000")
        ctrtcp=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        ctrtcp.bind(('',50000))
        ctrtcp.listen(1)
        while 1:
            cilent,server=ctrtcp.accept()
            cilent.settimeout(30)#超时限制
            th3=myThread_3(threadID=3,name='ctr_send',send_que=self.send_que,mysock=cilent)
            th3.setDaemon(True)   #把子进程设置为守护线程，必须在start()之前设置
            th3.start()
            print('ip:{}'.format(cilent))
            try:
                while 1:
                    receive = cilent.recv(1024)#指定一次最大接收数据量
                    if len(receive)>3:
                        self.rece_que.put(receive,block=True, timeout=None)
                    elif len(receive)==0:
                        print('exit ctr tcp')
                        break	
            except:
                print('exit')
            self.send_que.put(b'stop',block=True, timeout=None)
            cilent.close()
            #print('55555')
        print ("退出线程：" + self.name)

def creat_info(flag,leng,amount1,amount2,mydata1,mydata2):
    str1="({:1d},{:04d},{:02d},{:02d})".format(flag,int(leng*1000),amount1,amount2)#数据信息
    for i in mydata1:
        str1=str1+'({:05},{:05})'.format(int(i[0]*100),int(i[1]*1000))
    for i in mydata2:
        str1=str1+'({:05},{:05})'.format(int(i[0]*100),int(i[1]*1000))
    str1=str1+'$$'
    return str1

def calculate_t(data):
    #de=[]
    #data=[]
    #text=[[],[]]
    print(len(data))
    for i in range(1,len(data)-1):
        if (abs(data[i][0]-data[i-1][0])>40 and abs(data[i+1][0]-data[i][0])>40):
            data[i]=(int((data[i-1][0]+data[i+1][0])/2),data[i][1],data[i][2])
        #text[0].append(data[i][2])
        #text[1].append(data[i][0])
    print(len(data))
    #plt.plot(text[0],text[1])
    #plt.show()
    mydata1=[]
    mydata2=[]
    lc=0
    bc=0
    for i in range(1,len(data)):
        bias=data[i][0]-data[i-1][0]
        if(bias>0):
            bc+=1
            lc-=1
            if(lc<0):
                lc=0
        elif bias<=0 :
            lc+=1
            bc-=1
            if(bc<0):
                bc=0
        if(bc>3 and lc>1):
            temp1=(data[i-lc-2][0]+data[i-lc-1][0]+data[i-lc][0]+data[i-lc+1][0]+data[i-lc+2][0])/5
            temp2=(data[i-lc-2][2]+data[i-lc-1][2]+data[i-lc][2]+data[i-lc+1][2]+data[i-lc+2][2])/5
            mydata1.append((temp1,temp2))
            bc=0
        if(lc>3 and bc>1):
            temp1=(data[i-bc-2][0]+data[i-bc-1][0]+data[i-bc][0]+data[i-bc+1][0]+data[i-bc+2][0])/5
            temp2=(data[i-bc-2][2]+data[i-bc-1][2]+data[i-bc][2]+data[i-bc+1][2]+data[i-bc+2][2])/5
            mydata2.append((temp1,temp2))
            #mydata2.append((data[i-bc][0],data[i-bc][2]))
            lc=0
    av_time1=0
    av_time2=0
    avt=0
    #print(mydata1)
    for i in range(1,len(mydata1)):#忽略第一个数据
        av_time1+=mydata1[i][1]-mydata1[i-1][1]
        print(mydata1[i])
    if(len(mydata1)-1):
        avt+=av_time1/(len(mydata1)-1)
    #print(mydata2)
    for i in range(1,len(mydata2)):#忽略第一个数据
        av_time2+=mydata2[i][1]-mydata2[i-1][1]
        print(mydata2[i])
    if(len(mydata2)-1):
        avt+=av_time2/(len(mydata2)-1)
    return avt/2,mydata1,mydata2
    

deal_info=[]#每个对象包含（水平轴，垂直轴，时间戳）  
#text=[[],[]]
measure_flag=0#测量标识
zero_time=0#测量零点
record_time=0
#calibration_flag=0#校准标识
measure_time=24#测量时间
g_gz=9.7833
g_wh=9.7936
myg=g_gz
#gstr='  local g={:.4f}'.format(9.7936)#重力加速度，默认武汉本地

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
    img_send=queue.Queue(10)#限定10帧
    img_recv=queue.Queue(10)
    ctr_send=queue.Queue(10)
    ctr_recv=queue.Queue(10)
    try:
        th1=myThread_1(threadID=1,name='Thread-1',po=40000,send_que=img_send,rece_que=img_recv)
        th1.setDaemon(True)   #把子进程设置为守护线程，必须在start()之前设置
        th1.start()
    except:
        print("网络参数不正确")
    try:
        th2=myThread_2(threadID=2,name='Thread-2',po=50000,send_que=ctr_send,rece_que=ctr_recv)
        th2.setDaemon(True)   #把子进程设置为守护线程，必须在start()之前设置
        th2.start()
    except:
        print("网络参数不正确")
    cv2.namedWindow("camera one",0)
    cv2.moveWindow("camera one",0,0)
    cv2.setWindowProperty("camera one", cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
    while 1:
        ret, frame = cap.read()#读取图像
        #压缩参数，后面cv2.imencode将会用到，对于jpeg来说，15代表图像质量，越高代表图像质量越好为 0-100，默认95
        if ret==True:#获取到新图片后更新，无需翻转
            record_time=time.perf_counter()-zero_time#记录当前时间
            real_img=frame[my_imag.PICTURE_HEIGHT_MIN:my_imag.PICTURE_HEIGHT_MAX,my_imag.PICTURE_WIDTH_MIN:my_imag.PICTURE_WIDTH_MAX]
            #下面是测量代码
            gs_frame = cv2.GaussianBlur(real_img, (5, 5), 0)# 高斯模糊
            hsv = cv2.cvtColor(gs_frame, cv2.COLOR_BGR2HSV)# 转化成HSV图像
            erode_hsv = cv2.erode(hsv, None, iterations=2)# 腐蚀 粗的变细
            inRange_hsv = cv2.inRange(erode_hsv, color_dist[ball_color]['Lower'], color_dist[ball_color]['Upper'])
            cnts = cv2.findContours(inRange_hsv.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
            if len(cnts)>0:
                c = max(cnts, key=cv2.contourArea)           
                M1=cv2.moments(c)#会计算图像的矩，并返回一个字典
                try:
                    center_x=M1['m10']/M1['m00']
                    center_y=M1['m01']/M1['m00']
                    #if(center_x>250 or center_x<100):
                    #    measure_flag=1
                    if(measure_flag):
                        deal_info.append((center_x,center_y,record_time))
                        #text[0].append(record_time)
                        #text[1].append(center_x)
                    #cv2.circle(real_img,(int(center_x),int(center_y)),3,(0, 0, 255),3)
                except:
                    print('中心计算异常-除以0')
                rect = cv2.minAreaRect(c)
                box = cv2.boxPoints(rect)
                #cv2.circle(frame,(center_x,center_y),2,(0, 0, 255),2)
                cv2.drawContours(real_img, [numpy.int0(box)], -1, (0,0,255), 2)
                try:
                    cv2.circle(real_img,(int(center_x),int(center_y)),3,(0, 255,0),3)
                except:
                    print('丢失目标')
                #cv2.imshow("camera one", real_img)
                #cv2.waitKey(1)

            encode_param=[int(cv2.IMWRITE_JPEG_QUALITY),50]
            #cv2.imencode将图片格式转换(编码)成流数据，赋值到内存缓存中;主要用于图像数据格式的压缩，方便网络传输
		    #'.jpg'表示将图片按照jpg格式编码。
            try:
                rece_data=img_recv.get(block=False, timeout=None)
                #上面没有收到数据将报错
                result, imgencode = cv2.imencode('.jpg', real_img, encode_param)
                #建立矩阵
                data = numpy.array(imgencode)
                #将numpy矩阵转换成字符形式，以便在网络中传输
                stringData = data.tobytes()
                st1=str.encode(str(len(stringData)).ljust(16))
                img_send.put(st1, block=True, timeout=None)
                img_send.put(data,block=True, timeout=None)
            except:
                s1=1
                #print("need get signal!!")
            img = cv2.resize(real_img, (600,1024), fx=1, fy=1, interpolation=cv2.INTER_NEAREST)
            cv2.putText(img,'camera 1', (25, 25), cv2.FONT_HERSHEY_COMPLEX, 1.0, (0, 255,0), 2)
            if(connect_flag==1):
                cv2.putText(img,'1 connection established',(25,60),cv2.FONT_HERSHEY_COMPLEX,1.0,(0,255,0),2)
            else:
                cv2.putText(img,'No connection established',(25,60),cv2.FONT_HERSHEY_COMPLEX,1.0,(0,0,255),2)
            if(measure_flag==1):
                info='{:.1f}s'.format(24-(time.perf_counter()-zero_time))#校准剩余时间
                cv2.putText(img,'Aotu mesuring,left time '+info,(25,95),cv2.FONT_HERSHEY_COMPLEX,0.8,(0,255,0),2)
            cv2.imshow("camera one",img)#显示图像
        try:
            ctr_data=ctr_recv.get(block=False,timeout=None)
            #sctr=str(ctr_data)
            #print(sctr)
            if(len(ctr_data)==5 and ctr_data[0:5]==b'test1'):
                measure_flag=1
                if myg==g_wh:
                    myg=g_gz
                    print(myg)
                elif myg==g_gz:
                    myg=g_wh
                    print(myg)
                zero_time=time.perf_counter()#设置当前时间为零点
                record_time=0
            else: 
                measure_flag=1
                #calibration_flag=0
                #measure_time=24  #测量时间
                zero_time=time.perf_counter()#设置当前时间为零点
                record_time=0
            print('start measuring')
        except:
            s2=1
        #截止测量
        if(measure_flag and record_time>measure_time):
            measure_flag=0#测量结束
            avt,mydata1,mydata2=calculate_t(deal_info)
            deal_info.clear()
            print(avt)
            line_len=(avt*avt/3.141592653/3.141592653/4)*myg#-my_imag.PEN_EXLENGTH
            print("当前线长为："+str(line_len-my_imag.PEN_EXLENGTH)+" m")
            send_data=creat_info(2,line_len,len(mydata2),len(mydata1),mydata1,mydata2)
            print(send_data)
            bdata=send_data.encode('utf-8')
            ctr_send.put(bdata,block=True, timeout=None)
        key = cv2.waitKey(5)#这里强制卡为20fps的速率
        if key  == ord('q'):  #判断是哪一个键按下
            break
        #elif key == ord('s'):
        #    measure_flag=1
        #elif key == ord('e'):
        #    measure_flag=0
            #print(deal_info)
        #    avt,mydata1,mydata2=calculate_t(deal_info)
        #    deal_info.clear()
        #    print(avt)
        #    line_len=(avt*avt/3.14159/3.14159/4)*9.7936#-my_imag.PEN_EXLENGTH
        #    print("当前线长为："+str(line_len-my_imag.PEN_EXLENGTH)+" m")
            #send_data=creat_info(2,line_len,len(mydata2)+len(mydata1),mydata1,mydata2)
            #q3.put(send_data,block=True, timeout=None)
            #plt.plot(text[0],text[1])
            #plt.show()
            #text[0].clear()
            #text[1].clear()
            
    print("退出主线程")
    sys.exit(1)