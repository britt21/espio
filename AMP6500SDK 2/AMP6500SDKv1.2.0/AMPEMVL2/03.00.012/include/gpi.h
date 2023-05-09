// -----------------------------------------------------------------------------------------------------------------
// NAME.......  gpi.h
// PURPOSE....  Generic Platform Interface - Administration services
// PROJECT....  GPI
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//
// -----------------------------------------------------------------------------------------------------------------

//==================================================================================================================
//      Complete Function List
//==================================================================================================================
// * gpiInitialize
// * gpiMain
// * gpiCleanUp
// * gpiRelease
// * gpiGetInterfaceVersionNumber
// *
// -----------------------------------------------------------------------------------------------------------------

#ifndef GPI_H_
#define GPI_H_

#ifdef __cplusplus
extern "C" {
#endif

//==================================================================================================================
//      INCLUDES
//==================================================================================================================
//---- GPI Globals ----
#include "gpi_agnos_framework_globals.h"
//---- GPI Errors ----
#include "gpierrors.h"
//---- GPI Interfaces ----
#include "gpicad.h"
#include "gpihsm.h"
#include "gpidisplay.h"
#include "gpilog.h"
#include "gpiplatform.h"
#include "gpisped.h"
#include "gpiutils.h"

//==================================================================================================================
//      MACROS + DEFINES
//==================================================================================================================
#define gpi_false	0x00
#define gpi_true    0x01

#ifdef _AGNOSTRACE_
#define LOG(errorid, errormsg, ...) gpiLogf(__FUNCTION__,  __LINE__, errorid, (const char*)errormsg, (char*)__VA_ARGS__)
#define LOGDATA(errorid, message, bindata, binlen) gpiLogData(__FUNCTION__, __LINE__, errorid, (char*)message, bindata, binlen)
#else
#define LOG(...) ((void)0)
#define LOGDATA(...) ((void)0)
#endif

//==================================================================================================================
//      PRIMITIVES
//==================================================================================================================
/**
 * Initialize GPI to access log files
 * @note File names may be NULL depending on the context
 * @param transactionLogName Log's name to be used for current transaction traces
 */
DLLEXPORT tGPIError gpiInitialize(const char* transactionLogName);

/**
 * Main device initialisation
 * @param argc Argument count
 * @param argv Argument list, string based
 */
DLLEXPORT tGPIError gpiMain(int argc, char ** argv);

/**
 * Clean up device specific stuff...
 */
DLLEXPORT tGPIError gpiCleanUp(void);

/**
 * Clean up GPI log service and other stuff...
 */
DLLEXPORT tGPIError gpiRelease(void);

/**
 * Return GPI interface version
 * @param version (out) Contains the GPI version number
 */
DLLEXPORT tGPIError gpiGetInterfaceVersionNumber(char ** version);

#ifdef __cplusplus
}
#endif

#endif /*GPI_H_*/


