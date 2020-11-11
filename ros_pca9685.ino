/* 
 * rosserial Subscriber Example
 * turn a Servo on callback
 * Burn the following sketch to a Arduino 2560 board with a servo connected on Pin6.  
 * Enter a command of "rosrun rosserial_python serial_node.py /dev/ttyUSB__" to create a rosserial node communicating with the Arduino board.  
 * The node subsrcibes Topic 'JointStates' and the arduino board, turns the servo on Pin6 to the joint angle of the topic. 
 */

#include <ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  545 // this is the 'maximum' pulse length count (out of 4096)
#define SERVONUM 5
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

ros::NodeHandle  nh;

float angle[6] = {0,0,0,0,0,0};

void messageCb0(const std_msgs::Float64& msg){
  angle[0] = msg.data;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  uint16_t pulselength;
  pulselength = map(msg.data * 1000, -1.57 * 1000, 1.57 * 1000, SERVOMIN, SERVOMAX);
  pwm.setPWM(0, 0, pulselength);
}

void messageCb1(const std_msgs::Float64& msg){
  angle[1] = msg.data;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  uint16_t pulselength;
  pulselength = map(msg.data * 1000, -1.57 * 1000, 1.57 * 1000, SERVOMIN, SERVOMAX);
  pwm.setPWM(1, 0, pulselength);
}

void messageCb2(const std_msgs::Float64& msg){
  angle[2] = msg.data;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  uint16_t pulselength;
  pulselength = map(msg.data * 1000, -1.57 * 1000, 1.57 * 1000, SERVOMIN, SERVOMAX);
  pwm.setPWM(2, 0, pulselength);
}

void messageCb3(const std_msgs::Float64& msg){
  angle[3] = msg.data;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  uint16_t pulselength;
  pulselength = map(msg.data * 1000, -1.57 * 1000, 1.57 * 1000, SERVOMIN, SERVOMAX);
  pwm.setPWM(3, 0, pulselength);
}


void messageCb4(const std_msgs::Float64& msg){
  angle[4] = msg.data;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  uint16_t pulselength;
  pulselength = map(msg.data * 1000, -1.57 * 1000, 1.57 * 1000, SERVOMIN, SERVOMAX);
  pwm.setPWM(4, 0, pulselength);
}

std_msgs::Float64 mydata;

ros::Subscriber<std_msgs::Float64> sub0("/joint0_position/command",&messageCb0);
ros::Subscriber<std_msgs::Float64> sub1("/joint1_position/command",&messageCb1);
ros::Subscriber<std_msgs::Float64> sub2("/joint2_position/command",&messageCb2);
ros::Subscriber<std_msgs::Float64> sub3("/joint3_position/command",&messageCb3);
ros::Subscriber<std_msgs::Float64> sub4("/joint4_position/command",&messageCb4);

ros::Publisher chatter("chatter",&mydata);

void setup()
{ 
  nh.getHardware()->setBaud(57600);
  pinMode(13, OUTPUT);
  nh.initNode();

  nh.subscribe(sub0);
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  
  nh.advertise(chatter);
  
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  delay(10);

  digitalWrite(13, 1);
  uint16_t pulselength[SERVONUM];
  for(int i = 0; i < SERVONUM; i++){
    pwm.setPWM(i, 0, (SERVOMIN+SERVOMAX)/2);
  }

}

void loop()
{ 
  mydata.data = angle[0];
  chatter.publish( &mydata );
  nh.spinOnce();
  delay(1);
}
