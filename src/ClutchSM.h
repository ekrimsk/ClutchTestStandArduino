/****************************************************************************
 
  Header file for template Flat Sate Machine 
  based on the Gen2 Events and Services Framework

 ****************************************************************************/

#ifndef ClutchSM_H
#define ClutchSM_H

// Event Definitions
#include "ES_Configure.h" /* gets us event definitions */
#include "ES_Types.h"     /* gets bool type for returns */

// typedefs for the states
// State definitions for use with the query function
typedef enum {
  Frame, 
  FrameWait, 
  Output,
  OutputWait
} ClutchState_t ; 


//typedef enum {
 //	WaitForControl, 
 //	WaitForHandoff 
//} ClutchState_t ;


// Public Function Prototypes
#ifdef __cplusplus
extern "C" {
#endif

bool InitClutchSM ( uint8_t Priority );
bool PostClutchSM( ES_Event ThisEvent );
ES_Event RunClutchSM( ES_Event ThisEvent );
ClutchState_t QueryClutchSM ( void );


bool SetHandoffDelay(uint16_t delayTime); // in ms 


#ifdef __cplusplus
}
#endif

#endif /* ClutchSM_H */

