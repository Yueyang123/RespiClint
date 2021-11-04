/*
 * @Author: your name
 * @Date: 2021-11-04 09:03:07
 * @LastEditTime: 2021-11-04 09:14:57
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ResPiClint/src/gpio.cpp
 */

#include <wiringPi.h>
int main(void)
{
  wiringPiSetup() ;
  pinMode (0, OUTPUT) ;
  for(;;) 
  {
    digitalWrite(0, HIGH) ; delay (1000) ;
    digitalWrite(0,  LOW) ; delay (1000) ;
  }
}

