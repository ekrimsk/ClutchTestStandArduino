#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"

int main1( void ) {
ES_Return_t ErrorType;

// When doing testing, it is usefull to annouce just which program
// is running.
/*puts("Starting Test Harness for \r");
puts("the 2nd Generation Events & Services Framework V2.1\r");
puts(__TIME__ " " __DATE__);
puts("\n\r");
puts("Press 1 to post key-stroke events to Service 1\r");
puts("Press 0 to post key-stroke events to Service 0\n\r");*/

// Your hardware initialization function calls go here

// now initialize the Events and Services Framework and start it running
ErrorType = ES_Initialize(ES_Timer_RATE_1MS);
if ( ErrorType == Success ) {

  ErrorType = ES_Run();

}
//if we got to here, there was an error
switch (ErrorType){
  case FailedPost:
    //puts("Failed on attempt to Post");
    break;
  case FailedPointer:
    //puts("Failed on NULL pointer");
    break;
  case FailedInit:
    //puts("Failed Initialization");
    break;
 default:
    //puts("Other Failure");
    break;
}
for(;;)
  ;

};

/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/
