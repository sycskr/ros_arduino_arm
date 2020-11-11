#include <ros.h>
#include<Servo.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;//创建了一个节点的句柄，它允许我们用来创建发布者和订阅者。这个节点的句柄同样与串口通信有关。

const int servoCount = 5;
int PIN[servoCount];
//int servoAngle[servoCount];
int originalAngle[servoCount];//最初舵机角度数组
int servoMIN[servoCount]; //舵机角度最小值
int servoMAX[servoCount];  //舵机角度最大值
Servo rosServo[servoCount];//定义舵机

float angle[6] = {0,0,0,0,0,0};


/**
*fun:初始化控制舵机引脚
**/
void init_Pins() {//初始化对应的控制舵机引脚
  
  PIN[0] = 11;//板子上引脚11
  originalAngle[0] = 90;//设置初始舵机角度
  servoMIN[0] = 0;//对应舵机最小脚
  servoMAX[0] = 180;//对应舵机最大脚
  
  PIN[1] = 10;//板子上引脚10
  originalAngle[1] = 90;//设置初始舵机角度
  servoMIN[1] = 0;//对应舵机最小脚
  servoMAX[1] = 145;//对应舵机最大脚
  
  PIN[2] = 9;//板子上引脚9
  originalAngle[2] = 90;//设置初始舵机角度
  servoMIN[2] = 0;//对应舵机最小脚
  servoMAX[2] = 180;//对应舵机最大脚

  PIN[3] = 8;//板子上引脚8
  originalAngle[3] = 45;//设置初始舵机角度
  servoMIN[3] = 0;//对应舵机最小脚
  servoMAX[3] = 180;//对应舵机最大脚

  PIN[4] = 7;//板子上引脚7
  originalAngle[2] = 90;//设置初始舵机角度
  servoMIN[2] = 15;//对应舵机最小脚
  servoMAX[2] = 180;//对应舵机最大脚


  
  for (int i = 0; i < servoCount; i++) {//对舵机进行控制
    rosServo[i].attach(PIN[i]);//设置舵机控制引脚
    rosServo[i].write(originalAngle[i]);//设置舵机初始角度值
  }
}




/**
*fun:rosmessage
**/
void messageCb0(const std_msgs::Float64& msg){
  angle[0] = msg.data;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
//  uint16_t pulselength;
//  pulselength = map(msg.data * 1000, -1.57 * 1000, 1.57 * 1000, SERVOMIN, SERVOMAX);
//  pwm.setPWM(0, 0, pulselength);
  float angle=(msg.data/3.1415926535)*90+90;//可能需要转换成int类型
  rosServo[0].attach(PIN[0]);//设置舵机控制引脚
  
  if(angle<servoMIN[0]){
    rosServo[0].write(servoMIN[0]);//设置舵机初始角度值
    }
  else if(angle>servoMAX[0]){
    rosServo[0].write(servoMAX[0]);
    }
  else{
    rosServo[0].write(angle);
    }
}

void messageCb1(const std_msgs::Float64& msg){
  angle[1] = msg.data;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  
  float angle=(msg.data/3.1415926535)*90+90;
  rosServo[1].attach(PIN[1]);//设置舵机控制引脚
  
  if(angle<servoMIN[1]){
    rosServo[1].write(servoMIN[1]);//设置舵机初始角度值
    }
  else if(angle>servoMAX[1]){
    rosServo[1].write(servoMAX[1]);
    }
  else{
    rosServo[1].write(angle);
    }
}

void messageCb2(const std_msgs::Float64& msg){
  angle[2] = msg.data;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  
  float angle=(msg.data/3.1415926535)*90+90;
  rosServo[2].attach(PIN[2]);//设置舵机控制引脚
  
  if(angle<servoMIN[2]){
    rosServo[2].write(servoMIN[2]);//设置舵机初始角度值
    }
  else if(angle>servoMAX[2]){
    rosServo[2].write(servoMAX[2]);
    }
  else{
    rosServo[2].write(angle);
    }
}

void messageCb3(const std_msgs::Float64& msg){
  angle[3] = msg.data;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  
  float angle=(msg.data/3.1415926535)*90+90;
  rosServo[3].attach(PIN[3]);//设置舵机控制引脚
  
  if(angle<servoMIN[3]){
    rosServo[3].write(servoMIN[3]);//设置舵机初始角度值
    }
  else if(angle>servoMAX[3]){
    rosServo[3].write(servoMAX[3]);
    }
  else{
    rosServo[3].write(angle);
    }
}


void messageCb4(const std_msgs::Float64& msg){
  angle[4] = msg.data;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  
  float angle=(msg.data/3.1415926535)*90+90;
  rosServo[4].attach(PIN[4]);//设置舵机控制引脚
  
  if(angle<servoMIN[4]){
    rosServo[4].write(servoMIN[4]);//设置舵机初始角度值
    }
  else if(angle>servoMAX[4]){
    rosServo[4].write(servoMAX[4]);
    }
  else{
    rosServo[4].write(angle);
    }
}





std_msgs::Float64 mydata;
ros::Subscriber<std_msgs::Float64> sub0("/joint0_position/command",&messageCb0);
ros::Subscriber<std_msgs::Float64> sub1("/joint1_position/command",&messageCb1);
ros::Subscriber<std_msgs::Float64> sub2("/joint2_position/command",&messageCb2);
ros::Subscriber<std_msgs::Float64> sub3("/joint3_position/command",&messageCb3);
ros::Subscriber<std_msgs::Float64> sub4("/joint4_position/command",&messageCb4);

ros::Publisher chatter("chatter",&mydata);


void setup() {
   nh.getHardware()->setBaud(57600);//设置固件链接波特率为57600与电脑默认相同
   pinMode(13, OUTPUT);//设置LED灯为输出模式
   digitalWrite(13, HIGH);//给LED灯控制脚为高电平亮起
   
   nh.initNode();//初始化节点句柄
   /*初始化接收者*/
   nh.subscribe(sub0);
   nh.subscribe(sub1);
   nh.subscribe(sub2);
   nh.subscribe(sub3);
   nh.subscribe(sub4);
   /*初始化发布者*/
   nh.advertise(chatter);
   
   init_Pins();//初始化舵机
}

void loop() {
  mydata.data = angle[0];
  chatter.publish( &mydata );
  nh.spinOnce();
  delay(1);
}




