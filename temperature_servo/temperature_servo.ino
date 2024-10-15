/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  // Read the temp sensor value
  float tempVolts = 5.0*analogRead(tempPin)/1024;

  // Convert volts to Kelvin
  float tempKelvin = tempVolts/0.01;

  // Convert Kelvin to Celcius
  float tempCelsius = tempKelvin - 273;

  // Map Celcius to an angle
  int angle = map(round(tempCelsius), 0, 100, 0, 180);

  for (int pos = 0; pos <= angle; pos++) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (int pos = angle; pos >= 0; pos--) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}