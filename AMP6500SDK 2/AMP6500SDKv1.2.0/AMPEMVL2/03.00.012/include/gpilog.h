// -----------------------------------------------------------------------------------------------------------------
// NAME.......  gpilog.h
// PURPOSE....  Generic Platform Interface - Logging utilities
// PROJECT....  GPI
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//
// -----------------------------------------------------------------------------------------------------------------

//==================================================================================================================
//      Complete Function List
//==================================================================================================================
// * gpiInitializeLogger
// * gpiLog
// * gpiLogAddFileLogger
// * gpiLogData
// * gpiLogf
// * gpiLogSpecific
// * gpiReleaseLogger
// *
// -----------------------------------------------------------------------------------------------------------------

#ifndef GPILOG_H_
#define GPILOG_H_

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
#define LOG_FLAG_ALL			0xFFFF

#define LOG_FLAG_DEBUG			0x0010

#define LOG_FLAG_FILE			0x1000
#define LOG_FLAG_TCP			0x2000

#define LOG_FLAG_TCP_STAYALIVE	0x0100 	// TCP only - keep the connection alive
										//   if this flag is not set the connection is re-established
										//	 on every log call

#define LOG_FLAG_FILE_WRITEHEAD	0x0100 	// FILE only - write the predefined log header

//==================================================================================================================
//      PRIMITIVES
//==================================================================================================================
/**
 * Initialize GPI log services
 * @note File name may be NULL depending on the context
 * @param fileName Default logger's file name
 */
DLLEXPORT  tGPIError gpiInitializeLogger(
	const char* fileName
);

/**
 * Initialize GPI log services on remote ACE tool
 * @note Use address where ACE has been installed
 * @param address service's address
 * @param port service's port
 */
DLLEXPORT tGPIError gpiInitializeRemoteLogger(
	const char* address,
	unsigned short port
);

/**
 * Clean up GPI log services
 */
DLLEXPORT tGPIError gpiReleaseLogger(void);

/**
 * Log all the parameters received from the calling application.
 * @param errorId Error code at logpoint
 * @param source Source of the log call
 * @param data Data to be logged (null terminated string)
 * @param comments Additional information at logpoint
 */
DLLEXPORT  tGPIError gpiLog(
	unsigned short errorId,
	char* source,
	char* data,
	char* comments
);

/**
 * Log all the parameters received from the calling application - with additional data.
 * @param source Source of the log call
 * @param logFlags Log flags for destination-specific logging
 * @param errorId Error code at logpoint
 * @param comments Additional information at logpoint
 * @param data Format string of the additional data
 * @param ... Additionnal data
 */
DLLEXPORT tGPIError gpiLogf(
	const char* source,
	const short line,
	const unsigned short errorId,
	const char* comments,
	char *data,
	...
);

/**
 * Log all the parameters received from the calling application - binary data.
 * @param source Source of the log call
 * @param logFlags Log flags for destination-specific logging
 * @param errorId Error code at logpoint
 * @param comments Additional information at logpoint
 * @param message Information at the log point
 * @param bindata Binary data for logging
 * @param binlength Length of bindata
 */
DLLEXPORT tGPIError gpiLogData(
	const char* source,
	const short line,
	const unsigned short errorId,
	char *message,
	const unsigned char *bindata,
	const int binlength
);

/**
 * Log all the parameters received from the calling application - with additional data.
 * @param source Source of the log call
 * @param logFlags Log flags for destination-specific logging
 * @param errorId Error code at logpoint
 * @param comments Additional information at logpoint
 * @param message Information at the log point
 */
DLLEXPORT  tGPIError gpiLogSpecific(
	const char* source,
	const unsigned short logFlags,
	const unsigned short errorId,
	const char* comments,
	char *message
);

/**
 * Open a new File based logger with specific log flags
 * @param logFile File to open for logging
 * @param logFlags Log flags for destination-specific logging
 */
DLLEXPORT tGPIError gpiLogAddFileLogger(
	char * logFile,
	unsigned short logFlags
);

/**
 * Open a new TCP/IP based logger with specific log flags
 * @param host Hostname where the logging server is located
 * @param port Port on which to contact the host
 * @param logFlags Log flags for destination-specific logging
 */
DLLEXPORT  tGPIError gpiLogAddTCPLogger(
	char * host,
	unsigned int port,
	unsigned short logFlags);
/**
 * Switch on time stamping
 */
DLLEXPORT tGPIError gpiSwitchOnTimeStamp(void);

/**
 * Switch off time stamping
 */
DLLEXPORT tGPIError gpiSwitchOffTimeStamp(void);

/**
 * Get a time stamp
 */
DLLEXPORT tGPIError gpiGetTimeStamp(
	const char* code,
	int line,
	const char* comment
);

/**
 * Dump a time stamp
 */
DLLEXPORT tGPIError gpiDumpTimeStamp(
	void* stream
);

#ifdef __cplusplus
}
#endif

#endif /*GPILOG_H_*/
