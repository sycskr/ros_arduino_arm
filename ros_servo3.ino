#include <ros.h>
#include<Servo.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int8.h>


ros::NodeHandle  nh;//创建了一个节点的句柄，它允许我们用来创建发布者和订阅者。这个节点的句柄同样与串口通信有关。

const int servoCount = 3;
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
  
  PIN[0] = 11;//板子上引脚11 /gripper  爪子
  originalAngle[0] = 55;//设置初始舵机角度
  servoMIN[0] = 15;//对应舵机最小脚
  servoMAX[0] = 180;//对应舵机最大脚
  
  PIN[1] = 9;//板子上引脚9 /joint1 腕关节
  originalAngle[1] = 90;//设置初始舵机角度
  servoMIN[1] = 45;//对应舵机最小脚
  servoMAX[1] = 135;//对应舵机最大脚
  
  PIN[2] = 8;//板子上引脚8 /joint2 臂关节
  originalAngle[2] = 45;//设置初始舵机角度
  servoMIN[2] = 0;//对应舵机最小脚
  servoMAX[2] = 180;//对应舵机最大脚
  
  for (int i = 0; i < servoCount; i++) {//对舵机进行控制
    rosServo[i].attach(PIN[i]);//设置舵机控制引脚
    rosServo[i].write(originalAngle[i]);//设置舵机初始角度值
  }
}




/**
*fun:rosmessage
**/
//爪子
void messageCb0(const std_msgs::Int8& msg){
  angle[0] = msg.data;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led

  rosServo[0].attach(PIN[0]);//设置舵机控制引脚
  rosServo[1].attach(PIN[1]);//设置舵机控制引脚
  rosServo[2].attach(PIN[2]);//设置舵机控制引脚
  
  if(msg.data==0){//初始位置
    rosServo[0].write(55);//爪子
    for(int i=152;i>=45;i--){//臂关节152-45
      rosServo[2].write(i);      
      delay(10);
      }
    for(int i=45;i<=90;i++){//腕关节45-90
      rosServo[1].write(i);      
      delay(10);
      }
    //rosServo[1].write(90);//腕关节
    }
  else if(msg.data==1){//预备夹持
    rosServo[0].write(45);//爪子
    for(int i=45;i<=152;i++){//臂关节45-152
      rosServo[2].write(i);
      if(i<=90){
        rosServo[1].write(135-i);//腕关节90-45
        }
      delay(5);
      }
    }
  else if(msg.data==2){//夹持
    rosServo[2].write(152);//臂关节
    rosServo[1].write(45);//腕关节
    rosServo[0].write(105);//爪子
    }
  else if(msg.data==3){//抬起

    for(int i=152;i>=45;i--){//臂关节152-45
      rosServo[2].write(i);
      if(i<=125 && i>=45){//腕关节45-125
        rosServo[1].write(170-i);
        }
      delay(10);
      }
    
    rosServo[0].write(105);//爪子
    }
  else if(msg.data==4){//放下
    
    for(int i=45;i<=152;i++){//臂关节45-152
      rosServo[2].write(i);
      if(i<=90){
        rosServo[1].write(135-i);//腕关节90-45
        }
      delay(10);
      }
   
    rosServo[0].write(105);//爪子
    }
  else if(msg.data==5){//放下张开
    rosServo[2].write(150);//臂关节

    
    rosServo[1].write(45);//腕关节
    rosServo[0].write(45);//爪子
    }
}




std_msgs::Float64 mydata;
ros::Subscriber<std_msgs::Int8> sub0("/gripper",&messageCb0);

ros::Publisher chatter("chatter",&mydata);


void setup() {
   nh.getHardware()->setBaud(57600);//设置固件链接波特率为57600与电脑默认相同
   pinMode(13, OUTPUT);//设置LED灯为输出模式
   digitalWrite(13, HIGH);//给LED灯控制脚为高电平亮起
   
   nh.initNode();//初始化节点句柄
   /*初始化接收者*/
   nh.subscribe(sub0);

   /*初始化发布者*/
   nh.advertise(chatter);
   
   init_Pins();//初始化舵机
}

void loop() {
  mydata.data = angle[0];
  chatter.publish( &mydata );
  nh.spinOnce();
  delay(5);
}
