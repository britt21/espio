
#ifndef AMPDEBUG_H_
#define AMPDEBUG_H_

/***************************************************************************
 * 
 * Copyright (C) 2015 by APEX, Inc.
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of APEX Co. LLC.
 **************************************************************************/

/**************************************************************************
* File       	 : 		AMPDebug.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/08/2015
**************************************************************************/

typedef enum {
	USB_TTY_S2		= 1,
	USB_TTY_GS0		= 6,
	USB_TTY_USB0	= 7,
	USB_TTY_ACM0	= 8,
} ANDROID_USB_PORT;

#ifdef DEBUG_FLAG
#ifdef MEMWATCH
#include <MemWatch.h>
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

void LogProcessStatus(const char *FileName, int LineNum);
void LogTimeStamp(const char *FileName, int LineNum);
void LogInit(const char* AppName, int iDevPort);
void LogMessage(const char *FileName, int LineNum, const char *Format, ...);
void EnterMethod(const char *FileName, int LineNum, const char *Format, ...);
void LeaveMethod(const char *FileName, int LineNum, const char *Format, ...);
void LogHEXBuffer(const char *FileName, int LineNum, const unsigned char *in_buf, int num_bytes, const char *title);
void LogHEXData (const char *FileName, int LineNum, const unsigned char *in_buf, int offset, int num_bytes, int ascii_rep);

#ifdef DEBUG_FLAG
	#define DEBUG_INFO(...) LogMessage(__FILE__, __LINE__, __VA_ARGS__)
	#define _LogMessage(...) LogMessage(__FILE__, __LINE__, __VA_ARGS__)
	#define _EnterMethod(...) EnterMethod(__FILE__, __LINE__, __VA_ARGS__)
	#define _LeaveMethod(...) LeaveMethod(__FILE__, __LINE__, __VA_ARGS__)
	#define _LogHEXBuffer(...) LogHEXBuffer(__FILE__, __LINE__, __VA_ARGS__)
	#define _LogHEXData(...) LogHEXData(__FILE__, __LINE__, __VA_ARGS__)
	#define DUMP_TIMESTAT(...) LogTimeStamp(__FILE__, __LINE__)
	#define DUMP_PROCESSSTAT(...) LogProcessStatus(__FILE__, __LINE__)
#else
	#define DEBUG_INFO(...)
	#define _LogMessage(...)
	#define _EnterMethod(...)
	#define _LeaveMethod(...)
	#define _LogHEXBuffer(...)
	#define _LogHEXData(...)
	#define DUMP_TIMESTAT(...)
	#define DUMP_PROCESSSTAT(...)
#endif

#define ENTER_CLASS_FUNC(a) _EnterMethod("ENTER[%s::%s]", a, __FUNCTION__)
#define EXIT_CLASS_FUNC(a) _LeaveMethod("EXIT[%s::%s]", a, __FUNCTION__)

#define ENTER_FUNC() _EnterMethod("ENTER[%s]", __FUNCTION__)
#define EXIT_FUNC() _LeaveMethod("EXIT[%s]", __FUNCTION__)

#ifdef __cplusplus
}
#endif

#endif /* AMPDEBUG_H_ */

