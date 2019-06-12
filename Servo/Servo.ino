#include <Servo.h>  
 
int servoPin1 =11;
int servoPin2 =12; 
Servo servo1;  
Servo servo2; 
int pos=0;
void setup()
{
  Serial.begin(9600);  
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
}
 
 
void loop()
{
   servo2.write(0);
   
   servo1.write(0);     
   delay(10000);
   for (pos = 0; pos <= 90; pos += 1) { 
    servo1.write(pos);             
    delay(100);                       
   }
   servo1.write(90);     
   delay(10000); 
   for (pos = 90; pos <= 180; pos += 1) { 
    servo1.write(pos);             
    delay(100);                       
   }   
   servo1.write(180);      
   delay(10000);     
   for (pos = 0; pos <= 90; pos += 1) { 
    servo2.write(pos);             
    delay(100);                       
   }             
   servo2.write(65);     
   delay(10000);
   for (pos = 65; pos >= 0; pos -= 1) { 
    servo2.write(pos);             
    delay(35);                       
   }
   for (pos = 180; pos >= 0; pos -= 1) { 
    servo1.write(pos);             
    delay(35);                       
   }     
}
