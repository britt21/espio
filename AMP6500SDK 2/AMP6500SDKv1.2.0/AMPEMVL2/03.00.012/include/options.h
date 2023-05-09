// -----------------------------------------------------------------------------------------------------------------
// NAME.......  options.h
// PURPOSE....  Generic Platform Interface - This code implements administrative services related to a platform
// PROJECT....  GPI
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS�?, All Rights Reserved
//
// -----------------------------------------------------------------------------------------------------------------

#ifndef OPTIONS_H_
#define OPTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------------------------------------------
//			Includes
// -----------------------------------------------------------------------------------------------------------------
//---- GPI Headers ----
#include "gpi.h"

// -----------------------------------------------------------------------------------------------------------------
//			Macros + Defines
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------
//			Primitives
// -----------------------------------------------------------------------------------------------------------------
// Setters
DLLEXPORT void setTrace(unsigned char trace /* file depth */);
DLLEXPORT void setAutomation(unsigned char automation);
DLLEXPORT void setACE(unsigned char ace);
DLLEXPORT void setPollingTimeout(unsigned long timeout /* seconds */);
DLLEXPORT void setSignal(unsigned char signal);
DLLEXPORT void setAPDULog(unsigned char apdu);
DLLEXPORT void setUIDisplay(unsigned char ui);
DLLEXPORT void setReplay(unsigned char replay);
DLLEXPORT void setIDMessageDisplay(unsigned char display);
DLLEXPORT void setDigitalSignal(unsigned char digitalSignal);

// Getters
DLLEXPORT unsigned char getTraceOn(void);
DLLEXPORT unsigned char isAutomationOn(void);
DLLEXPORT unsigned char isACEOn(void);
DLLEXPORT unsigned long getPollingTimeout(void);
DLLEXPORT unsigned char isSignalOn(void);
DLLEXPORT unsigned char isAPDULogOn(void);
DLLEXPORT unsigned char isUIDisplayOn(void);
DLLEXPORT unsigned char isReplayOn(void);
DLLEXPORT unsigned char isIDMessageDisplayOn(void);
DLLEXPORT unsigned char isDigitalSignalOn(void);

#ifdef __cplusplus
}
#endif

#endif /* OPTIONS_H_ */
