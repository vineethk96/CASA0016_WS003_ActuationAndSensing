#include <Adafruit_NeoPixel.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define PIN 6
#define NUMPIXELS 8
#define DELAYVAL 500
#define READ_INTERVAL_ms 10
#define RESET_INTERVAL_ms 2

void set_LED(int ledNum, int intensity);

enum states_t {
  _RESET,
  _READING,
  _DISPLAY
};

bool checkDistance = false;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN);

void setup() {
  // Begin the Serial Monitor
  Serial.begin(9600);

  // Setup the UltraSonic Sensor Pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Begin the Pixel Array
  pixels.begin();
}

void loop() {

  /*
    Minimum time to get a new UltraSonic reading is 10ms.
    Take a new reading every 10ms, and display via LEDs.
    Each LED represents 7cm distance
  */

  static unsigned long lastTime = millis();
  static states_t currState = _RESET;
  static bool triggerProcess = true;

  switch(currState){
    case _RESET:
      
      if(triggerProcess){
        // begin the reset process
        digitalWrite(TRIG_PIN, LOW);  // clears trigger pin
        lastTime = millis();
        triggerProcess = false;
      }

      if(!triggerProcess && (millis() - lastTime > RESET_INTERVAL_ms)){
        // Reset process has been completed AND 2ms has elapsed
        triggerProcess = true;
        currState = _READING;  // change the state to begin reading
      }

      break;
    case _READING:

      if(triggerProcess){
        // begin the read process
        digitalWrite(TRIG_PIN, HIGH); // tells trigger to start reading
        lastTime = millis();
        triggerProcess = false;
      }

      if(!triggerProcess && (millis() - lastTime >= READ_INTERVAL_ms)){
        // Read process has been completed AND 10ms has elapsed
        digitalWrite(TRIG_PIN, LOW);
        triggerProcess = true;
        currState = _DISPLAY;  // change the state to display
      }

      break;
    case _DISPLAY:

      long duration = pulseIn(ECHO_PIN, HIGH);
      float distance = 34400*duration/2000000;

      // Output the cm Distance
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println("cm");

      // map a distance in cm within 60cm to 8 LEDs
      if(distance > 60){
        set_LED(7, 0); // turn off all lights
      }
      else{
        int ledNum = map(round(distance), 0, 60, 0, 7);
        set_LED(ledNum, 255); // show white light
      }
      
      currState = _RESET;

      break;
    default:
      break;
  }
}

void set_LED(int ledNum, int intensity){
  pixels.clear();

  // Show more LEDs the closer the object is
  for(int i = 0; i < ledNum; i++){
    pixels.setPixelColor(i, intensity, intensity, intensity);
  }
  pixels.show();
}