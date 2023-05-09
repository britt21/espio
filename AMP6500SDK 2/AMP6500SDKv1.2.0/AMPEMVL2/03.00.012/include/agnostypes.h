// NAME.......  agnostypes.h
// PURPOSE....  Portable types defined by Agnos
// PROJECT....  AGNOS
// REFERENCES.	--
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//

#ifndef AGNOSTYPES_H_
#define AGNOSTYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------
//			Include Files
//---------------------------------------------------------
//---- GPI Headers ----
#include "gpi.h"

//---------------------------------------------------------
//			Definitions
//---------------------------------------------------------
// All definitions follow EMVCo specifications
// Please refer to books I, II, III, IV
//
#define UNDEFINED_TERMINAL_TYPE							0x00

//Attended terminal types
#define	ATT_ONLINE_ONLY_FINANCIAL						0x11
#define	ATT_ONLINE_ONLY_MERCHANT						0x21
#define	ATT_OFFLINE_WITH_ONLINE_CAP_FINANCIAL			0x12
#define	ATT_OFFLINE_WITH_ONLINE_CAP_MERCHANT			0x22
#define	ATT_OFFLINE_ONLY_FINANCIAL						0x13
#define	ATT_OFFLINE_ONLY_MERCHANT						0x23

//Unattended terminal types
#define	UNATT_ONLINE_ONLY_FINANCIAL						0x14
#define	UNATT_ONLINE_ONLY_MERCHANT						0x24
#define	UNATT_ONLINE_ONLY_CARDHOLDER					0x34
#define	UNATT_OFFLINE_WITH_ONLINE_CAP_FINANCIAL			0x15
#define	UNATT_OFFLINE_WITH_ONLINE_CAP_MERCHANT			0x25
#define	UNATT_OFFLINE_WITH_ONLINE_CAP_CARDHOLDER		0x35
#define	UNATT_OFFLINE_ONLY_FINANCIAL					0x16
#define	UNATT_OFFLINE_ONLY_MERCHANT						0x26
#define	UNATT_OFFLINE_ONLY_CARDHOLDER					0x36

//Cryptogram information data
#define ARQC											0x80
#define TC												0x40
#define AAC												0x00
#define UNDEFINED_CID									0xF7

//Transaction type information data
#define	TT_PURCHASE				0x00
#define	TT_CASH					0x01
#define	TT_PRE_AUTHORIZATION	0x03
#define	TT_WITH_CASHBACK		0x09
#define	TT_QUASI_CASH			0x11
#define	TT_MANUAL_CASH			0x12
#define	TT_CASH_DISBURSEMENT	0x17
#define	TT_REFUND				0x20
#define	TT_DEPOSIT				0x21
#define	TT_INQUIRY				0x31
#define	TT_PAYMENT				0x50
#define	TT_TRANSFER				0x60
#define	TT_ADMINISTRATIVE		0x70
#define	TT_RETRIEVAL			0x78
#define	TT_UPDATE				0x79
#define	TT_AUTHENTICATION		0x90
#define	TT_UNDEFINED			0xFF

#define MIN_AID_LENGTH			5
#define MAX_AID_LENGTH			16

#define	NO_SELECT_FINAL			0xFF
#define AGNOS_TVR_SIZE			30

//---------------------------------------------------------
//			Declarations
//---------------------------------------------------------
typedef unsigned char 	tByte;
typedef unsigned short 	tWord;
typedef unsigned char 	tTerminalType;
typedef unsigned short 	tSessionId;
typedef char* 			tString;
typedef unsigned int 	tDate;
typedef tByte			tNumericDate;
typedef tByte 			tTVR[5];
typedef tByte 			tTSI[2];
typedef tByte 			tScriptResult[5];

typedef uint64_t		tAmount; // This definition is required since test plans integrates cases using 9F0206999999999999

typedef unsigned long	tCounter;
typedef unsigned int 	tPercentage;
typedef tByte			tTransactionKey[5];
typedef tByte			tARC[2];

typedef enum {
	bFALSE,
	bTRUE
} tBoolean;

typedef void (*tGetDataCallback)(tBoolean lastRead, tBoolean *next);

#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tTransactionKey mKey;
	tAmount mAmount;
} tTransaction;
#ifdef PACKING
#pragma pack()
#endif


typedef enum {
	tmALL,
	tmFL,
	tmRTS,
	tmVC
} tTRMMethod;

typedef enum {
	asREADY = 0,
	asSELECT = 10,
	asGPO = 20,
	asRRD = 30,
	asREAD = 40,
	asRESTRICTION = 70,
	asODA = 80,
	asCVM = 90,
	asTRM = 100,
	asTAA = 110,
	asGENAC1 = 120,
	asCCC = 130,
	asEXTAUTH = 140,
	asGENAC2 = 150,
	asGETDATA = 160,
	asPUTDATA = 170
} tAgnosState;

typedef void (*tStateCallback)(tAgnosState currentState, tBoolean *stop, tBoolean *bypass);

typedef enum {
	ctUNDEFINED,
	ctMODE_1,
	ctMODE_2,
	ctMODE_3,
	ctMODE_4
} tCDAType;

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /*AGNOSTYPES_H_*/
