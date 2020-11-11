#include <Servo.h>//舵机库
const int servoCount = 6;//舵机数量
int PIN[servoCount]; //定义所用到主板的引脚口数组
int servoAngle[servoCount];//舵机当前角度数组
int originalAngle[servoCount];//最初舵机角度数组
int servoMIN[servoCount]; //舵机角度最小值
int servoMAX[servoCount];  //舵机角度最大值
Servo yiLeServo[servoCount];//定义舵机

void setup()
{
   Serial.begin(115200);//电脑串口波特率设置
   pinMode(3, OUTPUT);//设置LED灯为输出模式
   digitalWrite(3, HIGH);//给LED灯控制脚为高电平亮起
   init_Pins();//初始化舵机
}

void loop()
{
   ps2DataRead();//PS2摇杆控制
}

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

  PIN[3] = 8;//板子上引脚5
  originalAngle[3] = 90;//设置初始舵机角度
  servoMIN[3] = 0;//对应舵机最小脚
  servoMAX[3] = 180;//对应舵机最大脚

   PIN[4] = 7;//板子上引脚7
  originalAngle[4] = 90;//设置初始舵机角度
  servoMIN[4] = 0;//对应舵机最小脚
  servoMAX[4] = 180;//对应舵机最大脚
  
   PIN[5] = 6;//板子上引脚6
  originalAngle[5] = 45;//设置初始舵机角度
  servoMIN[5] = 45;//对应舵机最小脚
  servoMAX[5] = 90;//对应舵机最大脚

  
  for (int i = 0; i < servoCount; i++) {//对舵机进行控制
    yiLeServo[i].attach(PIN[i]);//设置舵机控制引脚
    yiLeServo[i].write(originalAngle[i]);//设置舵机初始角度值
  }
}

void ps2DataRead()
{
     
  
        for (int i = 0; i < servoCount; i++) {//控制机械臂中舵机
        
               servoAngle[i] = yiLeServo[i].read();//读取舵机的当前角度
               if ( analogRead(i) > 900) {//判断采集的摇杆模拟值
                  if (servoAngle[i] > servoMIN[i]) //判断是否大于舵机最小值
                     --servoAngle[i];//改变舵机角度
                } else if ( analogRead(i) < 100) {//判断采集的摇杆模拟值
                  if (servoAngle[i] < servoMAX[i])//判断是否大于舵机最大值
                     ++servoAngle[i];//改变舵机角度
                }
       }

      
      for (int i = 0 ; i < servoCount; i++) {//控制机械臂中舵机
            if (!yiLeServo[i].attached())//判断当前舵机是否有控制引脚口
               yiLeServo[i].attach(PIN[i]);//设置对应的舵机控制引脚口
            yiLeServo[i].write(servoAngle[i]);//控制舵机转动到当前的角度
      }
      delay(20);//延时20ms
}


