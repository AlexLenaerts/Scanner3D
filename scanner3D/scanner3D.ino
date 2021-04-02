#include <Stepper.h> 
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int angleMin = 0;
int angleMax = 90;
int numberPhotos = 0;

//Steps per Revolution = 360/ step angle <=> (360 / 1.8 ) = 200 Steps Per Revolution
#define STEPS 200
#define motorInterfaceType 1 //Type1 because the motor is connected through the driver module
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver
Stepper stepper(STEPS, 2, 3); // Pin 2 connected to DIRECTION & Pin 3 connected to STEP Pin of Driver
int numberStep = numberPhotos;


void setup() { 
    // Set the maximum speed in steps per second:
    stepper.setSpeed(1000);
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
    myservo.write(angleMin);              //angle 0°
    //set original position of servo 
}
void loop()
{
    myservo.write(angleMax);
    delay(15);
    stepper.step(numberStep);
}
