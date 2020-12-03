#include <ros.h>
#include<Servo.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Empty.h>

ros::NodeHandle  nh;//创建了一个节点的句柄，它允许我们用来创建发布者和订阅者。这个节点的句柄同样与串口通信有关。

const int servoCount = 3;
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
  
  PIN[0] = 11;//板子上引脚11 /gripper  爪子80
  originalAngle[0] = 80;//设置初始舵机角度
  servoMIN[0] = 15;//对应舵机最小脚15
  servoMAX[0] = 180;//对应舵机最大脚180
  
  PIN[1] = 9;//板子上引脚9 /joint1 腕100
  originalAngle[1] = 100;//设置初始舵机角度
  servoMIN[1] = 0;//对应舵机最小脚
  servoMAX[1] = 135;//对应舵机最大脚
  
  PIN[2] = 8;//板子上引脚8 /joint2 臂40
  originalAngle[2] = 40;//设置初始舵机角度
  servoMIN[2] = 0;//对应舵机最小脚
  servoMAX[2] = 180;//对应舵机最大脚
  
  for (int i = servoCount-1; i >=0; i--) {//对舵机进行控制
    rosServo[i].attach(PIN[i]);//设置舵机控制引脚
    rosServo[i].write(originalAngle[i]);//设置舵机初始角度值
  }
}



/*4号
爪子：
闭合 +120/
40
张开 -40

腕关节：
水平 80
下 +180
155
上 -90+

臂关节：
上 40
后 -35
下 145
前 +
*/

//爪子
void messageCb0(int & data){
  data -= '0';
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led

  rosServo[0].attach(PIN[0]);//设置舵机控制引脚
  rosServo[1].attach(PIN[1]);//设置舵机控制引脚
  rosServo[2].attach(PIN[2]);//设置舵机控制引脚
  
  if(data==0){//初始位置
    rosServo[0].write(80);//爪子
    for(int i=145;i>=40;i--){//臂关节145-40
      rosServo[2].write(i);      
      delay(10);
      }
    rosServo[1].write(155);//腕关节
    }
  else if(data==1){//预备夹持
    rosServo[0].write(40);//爪子
    for(int i=40;i<=140;i++){//臂关节40-140
      rosServo[2].write(i);
      if(i<=115){
        rosServo[1].write(195-i);//腕关节155-80
        }
      delay(10);
      }
    }
  else if(data==2){//夹持
    for(int j=0;j<=80;j++){
      rosServo[0].write(40+j);
      delay(5);
      }
    //rosServo[0].write(120);//爪子
    for(int i=0;i<=5;i++){
      rosServo[2].write(140-i);
      delay(5);
      }
    //rosServo[2].write(135);//臂关节 145水平
    rosServo[1].write(80);//腕关节
    }
  else if(data==3){//抬起

    rosServo[0].write(120);//爪子
    for(int i=135;i>=40;i--){//臂关节135-40
      rosServo[2].write(i);      
      delay(10);
      }
    rosServo[1].write(155);//腕关节
    }
  else if(data==4){//放下
    
    for(int i=40;i<=145;i++){//臂关节40-145
      rosServo[2].write(i);
      if(i<=100){
        rosServo[1].write(195-i);//腕关节155-95
        }
      delay(10);
      }
   
    rosServo[0].write(120);//爪子
    }
  else if(data==5){//放下张开
    rosServo[2].write(140);//臂关节

    
    rosServo[1].write(80);//腕关节
    rosServo[0].write(40);//爪子
    }
  else if(data==6){//初始闭合
    rosServo[0].write(120);//爪子
    }
}






std_msgs::Float64 mydata;

ros::Publisher chatter("chatter",&mydata);

int data = 0;

void setup() {
   Serial.begin(9600);
   
   pinMode(13, OUTPUT);//设置LED灯为输出模式
   digitalWrite(13, HIGH);//给LED灯控制脚为高电平亮起
   
   
   init_Pins();//初始化舵机
}

void loop() {
  if(Serial.available()>0){
      data=Serial.read();
      messageCb0(data);
      Serial.print("get_data:");
      Serial.println(data);
    }
 
  delay(1);
}