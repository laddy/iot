#include <Servo.h>
Servo myServo; // create a servo object
 
int potVal = 0; // variable to read the value from the analog pin
 
void setup() {
    myServo.attach(9); // attaches the servo on pin 9 to the servo object
    Serial.begin(9600); // open a serial connection to your computer
}
 
void loop() {
    // set the servo position
    potVal += 3;
    myServo.write(potVal+3);
     
    // wait for the servo to get there
    delay(15);
}
