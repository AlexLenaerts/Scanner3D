#include <Stepper.h> 
#include <Servo.h>
#include <SoftwareSerial.h>

int angleMin = 0;
int angleMax = 90;
int numberPhotos = 0;
#define STEPS 160000/2
#define motorInterfaceType 1 //Type1 because the motor is connected through the driver module

Stepper stepper(STEPS, 5, 2); // Pin 2 connected to DIRECTION & Pin 3 connected to STEP Pin of Driver
Servo myservo;  // create servo object to control a servo
SoftwareSerial ArduinoMaster(2, 3);

String msg;


void setup() { 
    // Set the maximum speed in steps per second:
    stepper.setSpeed(5);
    myservo.attach(11);  
    pinMode(13, OUTPUT); //relay
    Serial.begin(9600); 
    ArduinoMaster.begin(9600);
}
void loop()
{
    int numberPhotos = readSerialPort().toInt();
    stepper.step(STEPS/numberPhotos);
    delay(500);
    digitalWrite(13, HIGH);
    myservo.write(angleMax);
    delay(5000);
    myservo.write(angleMin);
    delay(1000);
    digitalWrite(13, LOW);
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