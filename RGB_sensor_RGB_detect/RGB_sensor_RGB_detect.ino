#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_4X);

// Set the threshold value for the red channel (adjust as needed)
const uint16_t RED_THRESHOLD = 6;
const uint16_t GREEN_THRESHOLD = 6;
const uint16_t BLUE_THRESHOLD = 6;

void setup(void) {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r, g, b, c;
  tcs.setInterrupt(true);
  tcs.getRawData(&r, &g, &b, &c);
  
  // Scale down the raw red channel value for better readability
  uint8_t redValue = map(r, 0, 65535, 0, 255);
  Serial.print("R: "); Serial.print(r, DEC); Serial.print("\t");
  Serial.print("R: "); Serial.print(redValue); Serial.print("\n");

  uint8_t greenValue = map(g, 0, 65535, 0, 255);
  Serial.print("G: "); Serial.print(g, DEC); Serial.print("\t");
  Serial.print("G: "); Serial.print(greenValue); Serial.print("\n");

  uint8_t blueValue = map(b, 0, 65535, 0, 255);
  Serial.print("B: "); Serial.print(b, DEC); Serial.print("\t");
  Serial.print("B: "); Serial.print(blueValue); Serial.print("\n");
  
  // Check if the scaled red channel value is above the threshold
  if (redValue > RED_THRESHOLD) {
    Serial.println("Red Detected");
  } else {
    Serial.println("No Red Found");
  }

  if (greenValue > GREEN_THRESHOLD) {
    Serial.println("Green Detected");
  } else {
    Serial.println("No Green Found");
  }


  if (blueValue > BLUE_THRESHOLD) {
    Serial.println("Blue Detected");
  } else {
    Serial.println("No Blue Found");
  }

  delay(2000);
}
