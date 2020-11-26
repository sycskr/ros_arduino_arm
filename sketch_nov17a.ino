
#include<Servo.h>




const int servoCount = 5;
int PIN[servoCount];
//int servoAngle[servoCount];
int originalAngle[servoCount];//最初舵机角度数组
int servoMIN[servoCount]; //舵机角度最小值
int servoMAX[servoCount];  //舵机角度最大值
Servo rosServo[servoCount];//定义舵机



/**
*fun:初始化控制舵机引脚
**/
void init_Pins() {//初始化对应的控制舵机引脚
  
//  PIN[0] = 11;//板子上引脚11 /joint0
//  originalAngle[0] = 90;//设置初始舵机角度
//  servoMIN[0] = 0;//对应舵机最小脚
//  servoMAX[0] = 180;//对应舵机最大脚
//  
//  PIN[1] = 10;//板子上引脚10 /joint1
//  originalAngle[1] = 90;//设置初始舵机角度
//  servoMIN[1] = 45;//对应舵机最小脚
//  servoMAX[1] = 135;//对应舵机最大脚
//  
//  PIN[2] = 9;//板子上引脚9 /joint2
//  originalAngle[2] = 90;//设置初始舵机角度
//  servoMIN[2] = 0;//对应舵机最小脚
//  servoMAX[2] = 360;//对应舵机最大脚
//
//  PIN[3] = 8;//板子上引脚8 /joint3
//  originalAngle[3] = 90;//设置初始舵机角度
//  servoMIN[3] = 0;//对应舵机最小脚
//  servoMAX[3] = 360;//对应舵机最大脚

  PIN[4] = 10;//板子上引脚7 /joint4
  originalAngle[2] = 0;//设置初始舵机角度
  servoMIN[2] = 15;//对应舵机最小脚
  servoMAX[2] = 180;//对应舵机最大脚


  
  for (int i = 0; i < servoCount; i++) {//对舵机进行控制
    rosServo[i].attach(PIN[i]);//设置舵机控制引脚
    rosServo[i].write(originalAngle[i]);//设置舵机初始角度值
  }
}











void setup() {
   
   pinMode(13, OUTPUT);//设置LED灯为输出模式
   digitalWrite(13, HIGH);//给LED灯控制脚为高电平亮起
   
   init_Pins();//初始化舵机
}

void loop() {
  
  delay(1);
}
