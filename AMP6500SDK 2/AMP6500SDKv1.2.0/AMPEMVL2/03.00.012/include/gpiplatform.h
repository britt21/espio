// -----------------------------------------------------------------------------------------------------------------
// NAME.......  gpiplatform.h
// PURPOSE....  Generic Platform Interface - Platform
// PROJECT....  GPI
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//
// -----------------------------------------------------------------------------------------------------------------

//==================================================================================================================
//      Complete Function List
//==================================================================================================================
// * gpiGetDate
// * gpiGetTime
// * gpiSetDateTime
// * gpiGetTerminalIdentification
// * gpiSleep
// * gpiFileOpen
// * gpiFileClose
// * gpiFileRead
// * gpiFileWrite
// * gpiFileDelete
// * gpiFileRename
// * gpiFileGetSize
// * gpiOpenLibrary
// * gpiGetLibraryFunction
// * gpiCloseLibray
// * gpiGetTotalRAM
// * gpiGetRAMForTags
// * gpiGetRAMForUnknownTags
// * gpiGetFreeRAM
// * gpiGetPrivateScratchPAD
// * gpiMemCpy
// * gpiMemCmp
// * gpiMemSet
// * gpiStrCpy
// * gpiStrNCpy
// * gpiStrCmp
// * gpiStrLen
// *
// -----------------------------------------------------------------------------------------------------------------

#ifndef GPIPLATFORM_H_
#define GPIPLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

//==================================================================================================================
//      INCLUDES
//==================================================================================================================
//---- GPI Headers ----
#include "gpi.h"

//==================================================================================================================
//      MACROS + DEFINES
//==================================================================================================================
// -----------------------------------------------------------------------------------------------------------------
// File management services
// -----------------------------------------------------------------------------------------------------------------
#define READ            0x10
#define WRITE           0x20
#define READ_WRITE      0x30
#define CREATE          0x40
#define APPEND          0x80
#define TXT            	0x01
#define BINARY          0x02

typedef unsigned long tFileHandler;
typedef unsigned long tDataFileSize;

// -----------------------------------------------------------------------------------------------------------------
// Timer services
// -----------------------------------------------------------------------------------------------------------------
typedef unsigned char tTimerHandler;
typedef unsigned long tTimerTimeout;
typedef unsigned long tTimerTime;
typedef enum
{
	tsNONE,
	tsRUNNING,
	tsSTOPPED,
	tsTIMEOUT
} tTimerState;

//==================================================================================================================
//      PRIMITIVES
//==================================================================================================================
// -----------------------------------------------------------------------------------------------------------------
// RTC services
// -----------------------------------------------------------------------------------------------------------------
/**
 * Get current date
 * @note Format is YYYMMDD
 * @param currentDate (out) Buffer for current date
 */
DLLEXPORT tGPIError gpiGetDate( // Return current date. Format is YYYYMMDD
	unsigned char* currentDate
);

/**
 * Get current time
 * @note Format is HHMMSS
 * @param currentTime (out) Buffer for current time
 */
DLLEXPORT tGPIError gpiGetTime( // Return current time. Format is HHMMSS
	unsigned char* currentTime
);

 /**
  * Set device's date and time
  * @note Format is YYMMDDHHMMSS
  * @param currentDateTime (int) Current date and time
  */
DLLEXPORT tGPIError gpiSetDateTime(
	const unsigned char* currentDateTime
);

// -----------------------------------------------------------------------------------------------------------------
// Platform services
// -----------------------------------------------------------------------------------------------------------------
 /**
 * Return platform's identification
 * @param terminalId (out) 8 byte length buffer to receive identification
 */
DLLEXPORT tGPIError gpiGetTerminalIdentification(
	unsigned char* terminalId
);

/**
* Suspend execution for specified time
* @param ms Time to suspend for (milliseconds)
*/
DLLEXPORT tGPIError gpiSleep(
	unsigned long ms
);

// -----------------------------------------------------------------------------------------------------------------
// File management services
// -----------------------------------------------------------------------------------------------------------------
/**
* Open a file on the terminal
* @param fileName Name of the file to open
* @param ifp (out) File identifier
* @param openMode Requested file access mode
*/
DLLEXPORT tGPIError gpiFileOpen(
	const char* fileName,
	tFileHandler* ifp,
	unsigned char openMode
);

/**
* Close a file on the terminal
* @param ifp File identifier
*/
DLLEXPORT tGPIError gpiFileClose(
	tFileHandler ifp
);

/**
* Read from a file on the terminal
* @param ifp File identifier
* @param buffer (out) Buffer for read data
* @param length Length of the buffer
*/
DLLEXPORT tGPIError gpiFileRead(
	tFileHandler ifp,
	unsigned char *buffer,
	tDataFileSize *length
);

/**
* Write to a file on the terminal
* @param ifp File identifier
* @param buffer Output data buffer
* @param length Length of the buffer
*/
DLLEXPORT tGPIError gpiFileWrite(
	tFileHandler ifp,
	unsigned char *buffer,
	tDataFileSize length
);

/**
* Delete a file on the terminal
* @param fileName Name of the file
*/
DLLEXPORT tGPIError gpiFileDelete(
	const char* fileName
);

/**
* Rename a file on the terminal
* @param fileName Name of the file
* @param newFileName File after rename
*/
DLLEXPORT tGPIError gpiFileRename(
	const char* fileName,
	const char* newFileName
);

/**
* Retrieve a file's size on the terminal
* @param fileName Name of the file
* @param length (out) Size of the file
*/
DLLEXPORT tGPIError gpiFileGetSize(
	const char *fileName,
	tDataFileSize *length
);

// -----------------------------------------------------------------------------------------------------------------
// Shared library services
// -----------------------------------------------------------------------------------------------------------------
/**
* Open specified dynamic library
* @param name Name of the library
* @return Pointer to the opened library
*/
DLLEXPORT void* gpiOpenLibrary(
	char *name
);

/**
* Get specified function from a shared library
* @param library Reference to the library from where to grab the function
* @param name Name of a function
* @return Reference to the function
*/
DLLEXPORT void*	gpiGetLibraryFunction(
	void *library,
	char *name
);

/**
* Close an open shared library
* @param library Reference to the library
*/
DLLEXPORT void gpiCloseLibrary(
	void *library
);

// -----------------------------------------------------------------------------------------------------------------
// Shared RAM services
// -----------------------------------------------------------------------------------------------------------------
/**
* Provide a pointer to all shared RAM
* @param available ram
* @param ram size
*/
DLLEXPORT tGPIError gpiGetTotalRAM(
	unsigned char** ram,
	unsigned long* ramSize
);

/**
* Provide a pointer to RAM used to store EMV tags during a transaction
* @param available ram
* @param ram size
*/
DLLEXPORT tGPIError gpiGetRAMForTags(
	unsigned char** ram,
	unsigned long* ramSize
);

/**
* Provide a pointer to RAM used to store unknown tags during a transaction
* @param available ram
* @param ram size
*/
DLLEXPORT tGPIError gpiGetRAMForUnknownTags(
	unsigned char** ram,
	unsigned long* ramSize
);

/**
* Provide a pointer to RAM used to store free data
* @param available ram
* @param ram size
*/
DLLEXPORT tGPIError gpiGetFreeRAM(
	unsigned char** ram,
	unsigned long* ramSize
);

/**
* Provide a pointer to RAM used to store private data
* @param RFU
* @param available private ram
* @param private ram size
*/
DLLEXPORT tGPIError gpiGetPrivateScratchPAD(
	unsigned char slot,
	unsigned char** ram,
	unsigned long* ramSize
);

/**
* Provide a pointer to RAM used to store contactless data objects
* @param available ram
* @param ram size
*/
DLLEXPORT tGPIError gpiGetDataObjectRAM(
	unsigned char** ram,
	unsigned long* ramSize
);

// -----------------------------------------------------------------------------------------------------------------
// Timer services
// -----------------------------------------------------------------------------------------------------------------
/**
* Reset all GPI's timers
* @param
*/
DLLEXPORT tGPIError gpiResetTimers(void);

/**
* Get the maximum number of timers supported by GPI
* @param
*/
DLLEXPORT tGPIError gpiGetMaxTimer(
	tTimerHandler* timer
);

/**
* Get a timer and reset it
* @param
*/
DLLEXPORT tGPIError gpiGetTimer(
	tTimerHandler* timer
);

/**
* Free a timer and reset it
* @param
*/
DLLEXPORT tGPIError gpiFreeTimer(
	tTimerHandler timer
);

/**
* Start a timer, set a timeout (if different from 0), and set its state to tmRunning
* @param
*/
DLLEXPORT tGPIError gpiStartTimer(
	tTimerHandler timer,
	tTimerTimeout timeout_second /* s */,
	tTimerTimeout timeout_microsecond /* us */
);

/**
* Restart a timer
* @param
*/
DLLEXPORT tGPIError gpiRestartTimer(
	tTimerHandler timer
);

/**
* Stop a timer a set its state to tmStopped
* @param
*/
DLLEXPORT tGPIError gpiStopTimer(
	tTimerHandler timer
);

/**
*	Get timer's state
* @param
*/
DLLEXPORT tGPIError gpiGetTimerState(
	tTimerHandler timer,
	tTimerState* state
);

/**
*	Get timer's time
* @param
*/
DLLEXPORT tGPIError gpiGetTimerTime(
	tTimerHandler timer,
	tTimerTime* elapsed_second /* s */,
	tTimerTime* elapsed_microsecond /* us */
);

/**
*	Get last allocated timer
* @param
*/
DLLEXPORT tGPIError gpiGetLastAllocated(tTimerHandler* timer);

// -----------------------------------------------------------------------------------------------------------------
// Memory and String services
// -----------------------------------------------------------------------------------------------------------------
/**
*	Copy src to dest data for a given length
* @param
*/
DLLEXPORT tGPIError gpiMemCpy(
	void* dest,
	const void* src,
	unsigned int length);

/**
*	Compare 2 sources of data of a given length
* @param
*/
DLLEXPORT int gpiMemCmp(
	const void* s1,
	const void* s2,
	unsigned int length
);

/**
*	Initialize a source of a given length with a specific value
* @param
*/
DLLEXPORT tGPIError gpiMemSet(
	void* s,
	unsigned char value,
	unsigned int  length
);

/**
*	Copy src to dest string
* @param
*/
DLLEXPORT tGPIError gpiStrCpy(
	char* dest,
	const char* src
);

/**
*	Copy N character from src to dest string
* @param
*/
DLLEXPORT tGPIError gpiStrNCpy(
	char* dest,
	const char* src,
	unsigned int  length
);

/**
*	Compare 2 strings
* @param
*/
DLLEXPORT int gpiStrCmp(
	const void* s1,
	const void* s2
);

/**
*	Get string length
* @param
*/
DLLEXPORT int gpiStrLen(
	const void* s1
);

#ifdef __cplusplus
}
#endif

#endif /* GPIPLATFORM_H_ */
