#include "CytronMotorDriver.h"
#include <Servo.h>
char cmd =0;

CytronMD motorL1(PWM_PWM, 10, 11);
CytronMD motorR1(PWM_PWM, 14, 15);
CytronMD pump1(PWM_PWM, 8, 9);
CytronMD pump2(PWM_PWM, 12, 13);

int speed = 180;

bool pump1Active = false;
bool pump2Active = false;

//SERVOS

Servo base;
Servo Link1;
Servo Link2;
Servo bracket;

// MOTOR FUNC

void forward(int speedVal){
  motorL1.setSpeed(speedVal);
  motorR1.setSpeed(speedVal);
}

void backward(int speedVal){
  motorL1.setSpeed(-speedVal);
  motorR1.setSpeed(-speedVal);
}

void turnRight(int speedVal){
  motorL1.setSpeed(speedVal);
  motorR1.setSpeed(-speedVal);
}

void turnLeft(int speedVal){
  motorL1.setSpeed(-speedVal);
  motorR1.setSpeed(speedVal);
}

void stopMotors(){
  motorL1.setSpeed(0);
  motorR1.setSpeed(0);
}

void readSerial(){
  while(Serial1.available()){
    cmd = Serial1.read();
    Serial.print(cmd);
  }
}

//CAR FUNC

void drive(){
  switch(cmd) {
    case 'F': forward(speed);   break;
    case 'B': backward(speed);  break;
    case 'R': turnRight(speed); break;
    case 'L': turnLeft(speed);  break;
    default:  stopMotors();
  }

} 

void arm_control(){
  switch(cmd)
  {
    case 'a': base.write(0);    pump1Active = true; break;
    case 'b': Link1.write(0);   pump1Active = true; break;
    case 'c': Link2.write(0);   pump1Active = true; break;
    case 'd': bracket.write(0); pump1Active = true; break;

    case 'f': pump2Active = true; break;

    default: 
      base.write(90);
      Link1.write(90);
      Link2.write(90);
      bracket.write(90);
      break;

  }
}

void pump1_control(){

  if (pump1Active) {
    pump1.setSpeed(255);   
  }
  else {
    pump1.setSpeed(0);    
  }
}

void pump2_control(){

  if (pump2Active) {
    pump2.setSpeed(255);  
  }
  else {
    pump2.setSpeed(0);     
  }
}


void setup() {

    Serial.begin(115200);

    // GP28 = TX, GP29 = RX 
    Serial1.begin(115200);

    // Servo attach
    base.attach(0,500, 2500);
    Link1.attach(2,500, 2500);
    Link2.attach(3,500, 2500);
    bracket.attach(4,500, 2500);

    base.write(90);
    Link1.write(0);
    Link2.write(0);
    bracket.write(0);

}


void loop() {

  pump1Active = false;
  pump2Active = false;

  readSerial(); 
  drive();
  arm_control();
  pump1_control(); 
  pump2_control();
  
  delay(50);
}