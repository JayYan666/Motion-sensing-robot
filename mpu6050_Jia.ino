#include<Servo.h>



Servo analogservo;
Servo analogservo1;
Servo analogservo2;

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro;
int ax, ay, az;
int gx, gy, gz;
//int value;//定义一个整形变量用于存放读取到的信号值
//int16_t value;//定义一个整形变量用于存放读取到的信号值
int val2,val3;
unsigned char Re_buf[6],counter=0;
unsigned char sign=0;
int val;
bool blinkState = false;
void setup() {
      Wire.begin();
      Serial.begin(9600);
    //  Serial.println("Initializing I2C devices...");
      accelgyro.initialize();
     // Serial.println("Testing device connections...");
     // Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
      analogservo.attach(7);
      analogservo1.attach(4);
      analogservo2.attach(2);//舵机连接在7号脚
}
void loop() {
     accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); 
   ax/=131; ay/=131; Serial.print(ax);  Serial.print("\t");   
   if(ax>=0){val2=90-(double)ax/128*90; }
   else {ax=-ax; val2=(double)ax/128*90+90;}
   if(ay>=0)val3=90-(double)ay/128*90; 
   else {ay=-ay; val3=(double)ay/128*90+90;}
         //Serial.print("a/g:\t");
         
//      Serial.print(val2); 
//      Serial.print("\t");    
//      Serial.print(val3);// Serial.print(ay/131);   
//      Serial.print("\t"); 
//      Serial.print("\n"); 
     analogservo1.write(val2);
     
     analogservo2.write(val3);
   
   while (Serial.available()) {   
       Re_buf[counter]=(unsigned char)Serial.read(); 
      if(Re_buf[counter]==0x20||Re_buf[counter]==0x2D) counter=0;   // 检查帧头         
  
       counter++;       
    if(counter==6)                //接收到数据
    {    
       counter=0;                 //重新赋值，准备下一帧数据的接收 
       sign=1;
       return;
    } 
 }       
     if(sign==1){ //Serial.print(Re_buf[0]);Serial.print(Re_buf[1]);Serial.print(Re_buf[2]);Serial.print(Re_buf[3]);Serial.print("\n");
                  val=(int)Re_buf[1]*100+(int)Re_buf[2]*10+(int)Re_buf[3];
                   val=val-5328;
                   if(Re_buf[0]==0x20)val=90-(double)val/160*90; 
                   else val=(double)val/160*90+90;
                  analogservo.write(val);
          
                  sign=0;
                 // Serial.print(val);
                  }
  
  
   
//   analogservo.write(0); 
//   delay(1000);
//   analogservo.write(90); 
//   delay(1000);
//   analogservo.write(180); 
//   delay(1000);
//
//   delay(1000);

//      Serial.print(az/131);   
//      Serial.print("\t"); 
 
//      Serial.print(gx/131);   
//      Serial.print("\t");    
//      Serial.print(gy/131);   
//      Serial.print("\t"); 
//      Serial.print(gz/131);   
//      Serial.print("\t"); 
      //value=91+gx/131;  
  //    Serial.println(value);  

//      analogservo.write(value);
//      blinkState = !blinkState;
}
