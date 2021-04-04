#include <Servo.h>
#include <SoftwareSerial.h>
#include <Stepper.h>

//pins 
const int StepZ = 4;
const int DirZ = 7;
const int rxpinArduino = 2;
const int txpinArduino = 3;
const int servopin = 11 ;
const int relaispin = 13 ;

int angleMin = 0;
int angleMax = 90;
int numberPhotos = 0;
bool confirm = false;
#define STEPS 200 

Stepper stepper(STEPS, StepZ, DirZ);
Servo myservo;  // create servo object to control a servo
SoftwareSerial ArduinoMaster(rxpinArduino, txpinArduino);
String msg;

void setup() { 
    pinMode(StepZ, OUTPUT);
    pinMode(DirZ, OUTPUT);
    stepper.setSpeed(5);
    myservo.attach(servopin);   //limit Z axis
    pinMode(relaispin, OUTPUT);
    Serial.begin(9600); 
    ArduinoMaster.begin(9600);
}
void loop()
{
    if(!confirm)
    {
        //bluetooth
        numberPhotos = readSerialPort().toInt();
        confirm = true;
    }
    else
    {   
        for (int i = 0; i< numberPhotos; i++)
        {
            stepper.step(STEPS/numberPhotos); 
            delay(500);
            digitalWrite(13, HIGH); 
            myservo.write(angleMax); 
            delay(5000);
            myservo.write(angleMin);
            delay(1000);
            digitalWrite(13, LOW); 
        }
        //fin du programme
        delay(10000000);
    }
}

String readSerialPort() 
{
    while (ArduinoMaster.available()) 
    {
        delay(10);
        if (ArduinoMaster.available() > 0) {
            char c = ArduinoMaster.read();  //gets one byte from serial buffer
            msg += c; //makes the string readString
            return msg;
        }
    }
    ArduinoMaster.flush();
}
