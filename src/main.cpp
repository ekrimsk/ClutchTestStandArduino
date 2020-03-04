#include <stdio.h>

#include "Arduino.h"
#include "ES_Configure.h"
#include "ES_Framework.h"



#include <Wire.h>   // For I2C
#include <SPI.h>    // For SPI 


//#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
//#include <SoftwareSerial.h>
//#endif


// #include "TemplateFSM.h"

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"


// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}


void setup() {
  //All code from adafruit's example
  while (!Serial);  // required for Flora & Micro
  delay(500);
  Serial.begin(115200);

  delay(500);
  Serial.println("Setup done I guess????");
}

void loop() {
  ES_Return_t ErrorType = ES_Initialize(ES_Timer_RATE_1MS);
  if ( ErrorType == Success ) {
    Serial.println("Going to ES RUN");
    ErrorType = ES_Run();
  }

  //if we got to here, there was an error
  switch (ErrorType) {
    case FailedPost:
      Serial.println("Failed on attempt to Post");
      break;
    case FailedPointer:
      Serial.println("Failed on NULL pointer");
      break;
    case FailedInit:
      Serial.println("Failed Initialization");
      break;
    default:
      Serial.println("Other Failure");
      break;
  }

  for (;;)
    ;

}
