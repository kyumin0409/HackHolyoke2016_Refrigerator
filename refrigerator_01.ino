#include <Servo.h>
#include <Wire.h>

Servo servo;



const int motionPin = 3;
const int servoPin = 9;

//int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 5000;

boolean lockLow = true;
boolean takeLowTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motionPin,INPUT);
  //pinMode(servoPin, OUTPUT);
  //servo.attach(servoPin);
  digitalWrite(motionPin, LOW);

  delay(5000);
  Serial.print("calibration done ");
  Serial.println("SENSOR ACTIVE ");
  delay(50);

  //servo.attach(servoPin);
}

void thereIsMotion(){
  Serial.println("***MOTION!!***");
  servo.attach(servoPin);
    servo.writeMicroseconds(2000);
    delay(905);
    //servo.detach();
    if(lockLow){
      Serial.println("---");
      lockLow = false;
      delay(50);
    }
    takeLowTime = true;
    servo.detach();
}

void noMotion(){
  Serial.println("***NO MOTION!!***");
  servo.detach();
    if(takeLowTime){
      lowIn = millis();
      takeLowTime = false;
    }

    if(!lockLow && millis() - lowIn > pause){
      Serial.println(",-,-,");
      lockLow = true;
      delay(50);
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("DETECTING *********");
  if(digitalRead(motionPin) == HIGH){
    thereIsMotion();
    digitalWrite(motionPin, LOW);
    while(1){
      
    }
  }
  else{
    noMotion();
  }
  /*buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
   //servo.attach(servoPin);
   servo.writeMicroseconds(2000);
   delay(2000);
   servo.detach();
  }
  else{
    servo.writeMicroseconds(1000);
    servo.detach();
    //delay(10000);
  }
  //delay(10000);*/
}
