

/****************************************************************************
 Module
   EventCheckers.c

 Revision
   1.0.1 

 Description
   This is the sample for writing event checkers along with the event 
   checkers used in the basic framework test harness.

 Notes
   Note the use of static variables in sample event checker to detect
   ONLY transitions.
   
 History
 When           Who     What/Why
 -------------- ---     --------
 08/06/13 13:36 jec     initial version
****************************************************************************/

// this will pull in the symbolic definitions for events, which we will want
// to post in response to detecting events
#include "ES_Configure.h"
// this will get us the structure definition for events, which we will need
// in order to post events in response to detecting events
#include "ES_Events.h"
// if you want to use distribution lists then you need those function 
// definitions too.
#include "ES_PostList.h"
// This include will pull in all of the headers from the service modules
// providing the prototypes for all of the post functions
#include "ES_ServiceHeaders.h"
// this test harness for the framework references the serial routines that
// are defined in ES_Port.c
#include "ES_Port.h"
// include our own prototypes to insure consistency between header & 
// actual functionsdefinition
#include "EventCheckers.h"
#include <Arduino.h>
//#include <Adafruit_BLE.h>
//#include <Adafruit_BluefruitLE_SPI.h>
//#include <Adafruit_BluefruitLE_UART.h>

// This is the event checking function sample. It is not intended to be 
// included in the module. It is only here as a sample to guide you in writing
// your own event checkers
static uint8_t TickCount; // remove this??? 

#if 0
/****************************************************************************
 Function
   Check4Lock
 Parameters
   None
 Returns
   bool: true if a new event was detected
 Description
   Sample event checker grabbed from the simple lock state machine example
 Notes
   will not compile, sample only
 Author
   J. Edward Carryer, 08/06/13, 13:48
****************************************************************************/
bool Check4Lock(void)
{
  static uint8_t LastPinState = 0;
  uint8_t CurrentPinState;
  bool ReturnVal = false;

  CurrentPinState =  LOCK_PIN;
  // check for pin high AND different from last time
  // do the check for difference first so that you don't bother with a test
  // of a port/variable that is not going to matter, since it hasn't changed
  if ( (CurrentPinState != LastPinState) &&
       (CurrentPinState == LOCK_PIN_HI) )
  {                     // event detected, so post detected event
    ES_Event ThisEvent;
    ThisEvent.EventType = ES_LOCK;
    ThisEvent.EventParam = 1;
    // this could be any of the service post function, ES_PostListx or 
    // ES_PostAll functions
    ES_PostList01(ThisEvent); 
    ReturnVal = true;
  }
  LastPinState = CurrentPinState; // update the state for next time

  return ReturnVal;
}
#endif

/****************************************************************************
 Function
   Check4Keystroke
 Parameters
   None
 Returns
   bool: true if a new key was detected & posted
 Description
   checks to see if a new key from the keyboard is detected and, if so, 
   retrieves the key and posts an ES_NewKey event to TestHarnessService1
 Notes
   The functions that actually check the serial hardware for characters
   and retrieve them are assumed to be in ES_Port.c
   Since we always retrieve the keystroke when we detect it, thus clearing the
   hardware flag that indicates that a new key is ready this event checker 
   will only generate events on the arrival of new characters, even though we
   do not internally keep track of the last keystroke that we retrieved.
 Author
   J. Edward Carryer, 08/06/13, 13:48
****************************************************************************/

// TODO -- we really only want this to work in some debug mode 


bool CheckSerial(void)
{


  if ( Serial.available() > 0 ) // new key waiting?
  {
    ES_Event ThisEvent;
    ThisEvent.EventType = EV_SERIAL_RECEIVE;
    char incomingByte = Serial.read();

    // Frmae or output handoffs 
    if ((incomingByte == 'f') || (incomingByte == 'F'))
    {
      // wait for the newline 
      while(Serial.read() != '\n'); 
      ES_Event NewEvent;
      NewEvent.EventType = EV_ENGAGE_FRAME; 
      NewEvent.EventParam = 0;  // TODO  
      PostClutchSM(NewEvent);
    } 
    else if ((incomingByte == 'o') || (incomingByte == 'O'))
    {
      while(Serial.read() != '\n'); 
      ES_Event NewEvent;
      NewEvent.EventType = EV_ENGAGE_OUTPUT; 
      NewEvent.EventParam = 0;  // TODO  
      PostClutchSM(NewEvent);
    }
  }
  return false;
}

 /*
    else if ((incomingByte == 'C') || (incomingByte == 'c'))     // "C" for control  
    {
      // wait for the newline 
      while(Serial.read() != '\n'); 
      Serial.println("Type the hex value for the updated control:"); 
      uint16_t controlBytes;

      //Serial.read();
      // while(!Serial.available()){}; // blocking code to wait for control 
      while(1)
      {
        
        int inbyte = Serial.read(); 
        if (inbyte == '\n')
        {
          break;
        } 
        else if (inbyte != -1)
        {
          controlBytes <<= 4; 
          uint16_t hex;
          if (( inbyte > 47) && (inbyte < 58))
          {
            hex = inbyte - '0';
          }
          else if (( inbyte > 64) && (inbyte < 71)) // uppercase
          {
            hex = inbyte - 65 + 0xA;   // for A - F  
          }
          else if (( inbyte > 96) && (inbyte < 103)) // lowercase
          {
            hex = inbyte - 97 + 0xA;   // for A - F  
          }
          controlBytes |= hex;  
        }
      }

      // now post it 
      ES_Event NewEvent;
      NewEvent.EventType = EV_NEW_CONTROL; 
      NewEvent.EventParam = controlBytes; 
      Serial.print("Sent Control: 0x");
      Serial.println(controlBytes, HEX); 
      PostClutchSM(NewEvent);
      */
   



//    Serial.print("incoming data: ");
//    Serial.println(incomingByte);

    // test distribution list functionality by sending the 'L' key out via
    // a distribution list.
    //if ( ThisEvent.EventParam == 'L'){
      //ES_PostList00( ThisEvent );
    //}else{   // otherwise post to Service 0 for processing
      //PostTestHarnessService0( ThisEvent );
    //}
  //  return true;
 // }


/*
 * CheckMode
 * Keystroke-ish event checker for debugging the state machine
 */
/*
bool CheckMode(void)
{  
  if ( Serial.available() > 0 ) // new key waiting?
  {
    ES_Event ThisEvent;
    ES_Event NewEvent;
    ThisEvent.EventType = EV_SERIAL_RECEIVE;
    char incomingByte = Serial.read();
//    Serial.print("incoming data: ");
//    Serial.println(incomingByte);
    ThisEvent.EventParam = incomingByte;

    // test distribution list functionality by sending the 'L' key out via
    // a distribution list.
    if ( ThisEvent.EventParam == 'C'){
      //ES_PostList00( ThisEvent ); 
      NewEvent.EventType = Connected;
      Serial.println("Connected EVENT");
//      Serial.print("Incoming letter: ");
//      Serial.println((char)ThisEvent.EventParam);
      PostTemplateFSM(NewEvent);
    }else if (ThisEvent.EventParam == 'N'){   // otherwise post to Service 0 for processing
      NewEvent.EventType = Disconnected;
      Serial.println("Disconnected EVENT");
//      Serial.print("Incoming letter: ");
//      Serial.println((char)ThisEvent.EventParam);
      PostTemplateFSM(NewEvent);
    }
    else if (ThisEvent.EventParam == 'B'){   // otherwise post to Service 0 for processing
      NewEvent.EventType = Blink;
      Serial.println("Blink EVENT");
//      Serial.print("Incoming letter: ");
//      Serial.println((char)ThisEvent.EventParam);
      PostTemplateFSM(NewEvent);
    }
    else if (ThisEvent.EventParam == 'S'){   // otherwise post to Service 0 for processing
      NewEvent.EventType = Solid;
      Serial.println("Solid EVENT");
//      Serial.print("Incoming letter: ");
//      Serial.println((char)ThisEvent.EventParam);
      PostTemplateFSM(NewEvent);
    }
    else if (ThisEvent.EventParam == 'O'){   // otherwise post to Service 0 for processing
      NewEvent.EventType = On;
      Serial.println("On EVENT");
//      Serial.print("Incoming letter: ");
//      Serial.println((char)ThisEvent.EventParam);
      PostTemplateFSM(NewEvent);
    }
    else if (ThisEvent.EventParam == 'A'){   // otherwise post to Service 0 for processing
      NewEvent.EventType = Auto;
      Serial.println("Auto EVENT");
//      Serial.print("Incoming letter: ");
//      Serial.println((char)ThisEvent.EventParam);
      PostTemplateFSM(NewEvent);
    }
    else if (ThisEvent.EventParam == 'D'){   // otherwise post to Service 0 for processing
      NewEvent.EventType = Dark;
      Serial.println("Dark EVENT");
//      Serial.print("Incoming letter: ");
//      Serial.println((char)ThisEvent.EventParam);
      PostTemplateFSM(NewEvent);
    }
    else if (ThisEvent.EventParam == 'L'){   // otherwise post to Service 0 for processing
      NewEvent.EventType = Bright;
      Serial.println("Bright EVENT");
//      Serial.print("Incoming letter: ");
//      Serial.println((char)ThisEvent.EventParam);
      PostTemplateFSM(NewEvent);
    }
    else if (ThisEvent.EventParam == 'M'){   // otherwise post to Service 0 for processing
      NewEvent.EventType = Moving;
      Serial.println("Moving EVENT");
//      Serial.print("Incoming letter: ");
//      Serial.println((char)ThisEvent.EventParam);
      PostTemplateFSM(NewEvent);
    }
    else if (ThisEvent.EventParam == 'P'){   // otherwise post to Service 0 for processing
      NewEvent.EventType = NotMoving;
      Serial.println("NotMoving EVENT");
//      Serial.print("Incoming letter: ");
//      Serial.println((char)ThisEvent.EventParam);
      PostTemplateFSM(NewEvent);
    }
    else {   // otherwise post to Service 0 for processing
      NewEvent.EventType = Error;
      Serial.print("Wrong shit, bitch, no use for '");
      Serial.print((char)ThisEvent.EventParam);
      Serial.println("'");
      PostTemplateFSM(NewEvent);
    }
    return true;
  }
  return false;
}


*/ 