// -----------------------------------------------------------------------------------------------------------------
// NAME.......  gpiutils.h
// PURPOSE....  Generic Platform Interface - Utilities
// PROJECT....  GPI
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//
// -----------------------------------------------------------------------------------------------------------------

//==================================================================================================================
//      Complete Function List
//==================================================================================================================
// * toNumeric
// * toByte
// * toBinary
// * toWord
// * hexToNumeric
// * bcdToDecimal
// *
// -----------------------------------------------------------------------------------------------------------------

#ifndef GPIUTILS_H
#define	GPIUTILS_H

#ifdef __cplusplus
extern "C" {
#endif

//==================================================================================================================
//      INCLUDES
//==================================================================================================================
//---- GPI Headers ----
#include "gpi_agnos_framework_globals.h"

//==================================================================================================================
//      MACROS + DEFINES
//==================================================================================================================

//==================================================================================================================
//      PRIMITIVES
//==================================================================================================================
DLLEXPORT unsigned char toNumeric(unsigned char value);
DLLEXPORT unsigned char toByte(char value);
DLLEXPORT unsigned char toBinary(unsigned char value);
DLLEXPORT unsigned short toWord(char high, char low);
DLLEXPORT unsigned int hexToNumeric(const char *src, const int length);
DLLEXPORT unsigned char bcdToDecimal(unsigned char bcd);

#ifdef __cplusplus
}
#endif

#endif	/* GPIUTILS_H */

