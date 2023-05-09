// -----------------------------------------------------------------------------------------------------------------
// NAME.......  sep.h
// PURPOSE....  Generic Platform Interface - Implementation of the secure part related to pin management
// PROJECT....  GPI
// REFERENCES.
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
// -----------------------------------------------------------------------------------------------------------------

#ifndef SEP_H_
#define SEP_H_

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------------------------------------------
//			Includes
// -----------------------------------------------------------------------------------------------------------------
//---- GPI Globals ----
#include "gpi_agnos_framework_globals.h"

// -----------------------------------------------------------------------------------------------------------------
//			Macros + Defines
// -----------------------------------------------------------------------------------------------------------------
#define sepNO_ERROR										0x00
#define sepTIME_OUT										0x01
#define sepCANCEL										0x02
#define	sepWRONG_LENGTH									0x03
#define	sepPINPAD_MALFUNCTIONING						0x04
#define	sepPINBLOCK_RECOVERY_FAILED						0x05
#define	sepWRONG_PIN									0x06 // Where highest nibble indicates remaining tries
#define	sepNO_REMAINING_PIN_TRIES						0x07
#define	sepPIN_BLOCKED									0x08
#define	sepPIN_NOT_ENTERED								0x09
#define	sepRANDOM_NUMBER_ERROR							0x0A
#define	sepRSA_CALCULATION_ERROR						0x0B
#define	sepPROCESS_FAILED								0x0C

// -----------------------------------------------------------------------------------------------------------------
//			Primitives
// -----------------------------------------------------------------------------------------------------------------
DLLEXPORT unsigned short sepPINPadStatus(
	const char* pinPadName
);

DLLEXPORT unsigned short sepGetOnlineEncipheredPin (
	const char* pinPadName,
	unsigned char lanId,
	unsigned char stringId,
	unsigned char* encryptedPIN,
	unsigned char* encryptedLen,
	int timeout
);

DLLEXPORT unsigned short sepEnterOfflinePin(
	const char* pinPadName,
	unsigned char lanId,
	unsigned char stringId,
	int timeout
);

DLLEXPORT unsigned short sepVerifyOfflinePlainText(
	const char* smartcardReaderName
);

DLLEXPORT unsigned short sepVerifyOfflineCiphered(
	const char* smartcardReaderName,
	unsigned char* modulus, const unsigned char modulusLen,
	unsigned char* exponent, const unsigned char exponentLen
);

void sepSetExpectedPinLength(const char *szExpectedPINLen);
char* sepGetExpectedPinLength(void);

#ifdef __cplusplus
}
#endif

#endif /*SEP_H_*/
