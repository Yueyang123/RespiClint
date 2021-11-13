/*
 * @Author: your name
 * @Date: 2021-11-04 09:17:42
 * @LastEditTime: 2021-11-05 17:19:13
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ResPiClint/include/gpio.h
 */
 #include <wiringPi.h>

 class gpio{
     public:
        gpio(int index){
            this->index=index;
        }
        void open(int dir)
        {
            if(dir==1)
            {
                wiringPiSetup() ;
                pinMode (index, INPUT) ;                
            }else{
                wiringPiSetup() ;
                pinMode (index, OUTPUT) ;
            }
        }
        int read()
        {
            return digitalRead(index);
        }
        void on()
        {
            digitalWrite(index, HIGH) ; 
        }
        void off()
        {
            digitalWrite(index,  LOW) ;
        }
    private:
        int index;
 };
