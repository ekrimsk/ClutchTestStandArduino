/****************************************************************************
 Module
     ES_DeferRecall.c

 Description
     This is a module implementing  the management of event deferal and recall
      queues
 Notes
     

 History
 When           Who     What/Why
 -------------- ---     --------
 
 11/02/13 16:38 jec      Began Coding
****************************************************************************/

/*----------------------------- Include Files -----------------------------*/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_General.h"
#include "ES_Events.h"
#include "ES_DeferRecall.h"

/*--------------------------- External Variables --------------------------*/

/*----------------------------- Module Defines ----------------------------*/

/*------------------------------ Module Types -----------------------------*/

/*---------------------------- Module Functions ---------------------------*/

/*---------------------------- Module Variables ---------------------------*/

/*------------------------------ Module Code ------------------------------*/
/****************************************************************************
 Function
     ES_RecallEvent
 Parameters
      uint8_t WhichService, number of the service to post Recalled event to
      ES_Event * pBlock, pointer to the block of memory that implements the
        Defer/Recall queue
 Returns
     bool true if an event was recalled, false if no event was left in queue
 Description
     pulls an event off the deferral queue if one is available. It there was
     something in the queue, then it posts it LIFO fashion to the queue 
     indicated by WhichService
 Notes
     None.
 Author
     J. Edward Carryer, 11/20/13 16:49
****************************************************************************/
bool ES_RecallEvent( uint8_t WhichService, ES_Event * pBlock ){
  ES_Event RecalledEvent;
  // recall any event from the top of the queue
  ES_DeQueue( pBlock, &RecalledEvent );
  if (RecalledEvent.EventType != ES_NO_EVENT){
    ES_PostToServiceLIFO( WhichService, RecalledEvent);
    return true;
  }else{
    return false;
  }
}
  
/*------------------------------- Footnotes -------------------------------*/


/*------------------------------ End of file ------------------------------*/

