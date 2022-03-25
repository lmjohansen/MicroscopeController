#include <Arduino.h>
//#include <Wire.h>
#define BUTTON_PIN     13 // GIOP21 pin connected to button
#define DEBOUNCE_TIME  50 // the debounce time in millisecond, increase this time if it still chatters

// Variables will change:
int lastSteadyState = LOW;       // the previous steady state from the input pin
int lastFlickerableState = LOW;  // the previous flickerable state from the input pin
int currentState;                // the current reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

void setup() {
  //Wire.begin(5,4);
 
  Serial.begin(9600);
  Serial2.begin(115200);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nMicroscope Controller");

  while (!Serial2);             // Leonardo: wait for serial monitor
  Serial.println("\n");

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  }


void loop() {

  // read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch/button changed, due to noise or pressing:
  if (currentState != lastFlickerableState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastFlickerableState = currentState;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // if the button state has changed:
      if(lastSteadyState == HIGH && currentState == LOW)
      {
        Serial.println("The button is pressed");
        Serial2.println("\n");
        Serial2.println("./talk m");
      }
      else if(lastSteadyState == LOW && currentState == HIGH)
      {
        Serial.println("The button is released");
        Serial2.println("");
        Serial2.println("./talk a");

      }

      // save the the last steady state
      lastSteadyState = currentState;
    }
}