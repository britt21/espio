
#ifndef COREDEFINES_H_
#define COREDEFINES_H_

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
* File       	 : 		CoreDefines.h
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		09/07/2015
**************************************************************************/

// Project Includes
#include "SizeDefines.h"


//! Password Entry/Input Mode
typedef enum
{
	PW_ENTRY_NORMAL = 0,
	PW_ENTRY_STRICT = 1,
	
} PASSWORD_ENTRY_MODE;

//! Card Entry Methods

typedef enum {
	FLAGTRUE = 'Y',
	FLAGFALSE = 'N',
} FLAG;

//! Card Entry Methods

typedef enum {
	CARD_NONE,			//4 Card Not Yet Entered
	CARD_MANUAL,		//4 Manual Entry PAN + Expiry
	CARD_SWIPE,			//4 MSR
	CARD_INSERT,		//4 ICC
	CARD_TAP,			//4 CTLS
} CARD_ENTRY_METHOD;

//! Card Input Devices

#define DEVCARD_MSR		(1<<0)
#define DEVCARD_CTLS	(1<<1)
#define DEVCARD_ICC		(1<<2)
#define DEVCARD_MANUAL	(1<<3)
#define DEVCARD_ALL		(DEVCARD_MSR|DEVCARD_CTLS|DEVCARD_ICC|DEVCARD_MANUAL)

//! Account Types

typedef enum {
	SAVINGS	= 1,
	CHEQUE 	= 2,
} ACCNT_TYPE;

//! Card Types

typedef enum {

	ADMIN_CARD = 0xFF,
	CREDIT_CARD = 0,
	DEBIT_CARD = 1,
	NON_CARD = 3,
	LOYALTY_CARD = 6,		// Loyalty Only Card
	LOYCREDIT_CARD = 7,		// Loyalty & Credit Card Combo
	EBT_CARD = 8,
	PURCHASE_CARD = 9, 
	COMMERCIAL_CARD = 10,
	FLEET_CARD = 11,
	GIFT_CARD = 12,
	BUSINESS_CARD = 13,
	CORPORATE_CARD = 14
} CARD_TYPE;

//! Card Type Labels

#define LABEL_ADMIN_CARD 		"Admin"
#define LABEL_CREDIT_CARD 		"Credit"
#define LABEL_DEBIT_CARD 		"Debit"
#define LABEL_NON_CARD 			"Non-card"
#define LABEL_LOYALTY_CARD 		"Loyalty"
#define LABEL_LOYCREDIT_CARD 	"Loyalty Credit"
#define LABEL_EBT_CARD 			"EBT"
#define LABEL_PURCHASE_CARD 	"Purchase"
#define LABEL_COMMERCIAL_CARD 	"Commercial"
#define LABEL_FLEET_CARD 		"Fleet"
#define LABEL_GIFT_CARD 		"Gift"
#define LABEL_BUSINESS_CARD 	"Business"
#define LABEL_CORPORATE_CARD 	"Corporate"

//! Issuers

typedef enum {

	VISA,
	MASTERCARD,
	AMEX,
	PAYPAYL,
	DISCOVER,
	JCB,
	INTERAC,

} ISSUER_TYPE;

//! Issuer Label / Issuer Name

#define LABEL_VISA 			"Visa"
#define LABEL_MASTERCARD 	"MasterCard"
#define LABEL_AMEX 			"Amex"
#define LABEL_PAYPAL		"PayPal"
#define LABEL_DISCOVER		"Discover"
#define LABEL_JCB			"JCB"
#define LABEL_INTERAC		"Interac"

//! Emv Card Decission

typedef enum {
	EMV_UNKNOWN,
	EMV_GO_ONLINE,
	EMV_APPROVED,
	EMV_DECLINE,
	EMV_VOICE_REFERRAL,
} EMV_RESULT;

//! Terminal Type

typedef enum {

	// Attended
	ATT_ONLINE_ONLY			  = 0x21,
	ATT_OFFLINE_WITH_ONLINE	  = 0x22,
	ATT_OFFLINE_ONLY		  = 0x23,

	// Unattended
	UNATT_ONLINE_ONLY 		  = 0x24,
	UNATT_OFFLINE_WITH_ONLINE = 0x25,
	UNATT_OFFLINE_ONLY		  = 0x26,
	
} TERMINAL_TYPE;

//! Host Communication Result, value updated upon execution of DoHostCommunication

typedef enum {

	NOT_EXECUTED,		// The function DoHostCommunication was not yet executed

	HOSTCOMM_SUCCESS,	// Successfull Connect, Tx, & Rx has beed done w/ the Host
	
	CONNECTION_FAILED,	// Connection attempts to host failed
	SEND_FAILED,		// Sending of data to host failed
	RECEIVE_FAILED,		// No data received from host (or timeout was reached)

	BUILDPKT_FAILED,	// Error Occured on building the request packet e.g. mandatory field missing, etc.
	RESPONSEPKT_FAILED,	// Error on Parsing of response packet from host e.g. unknownd field, etc.

	VERIFYMAC_FAILED,	// Resonpse packet has incorrect MAC
	
} HOSTCOMM_RESULT;

//! Media Names

#define MEDIA_IP	"IP"
#define MEDIA_DIAL	"DIAL"
#define MEDIA_GPRS	"GPRS"

//! Host Type

#define HOSTTYPE_TRANS	"TRX"			// Transaction Host
#define HOSTTYPE_SETTLE	"SETTLEMENT"	// Settlement Host

//! Key Management Type

#define KEYMGT_MASTERSESSION	"MASTERSESSION"
#define KEYMGT_DUKPT			"DUKPT"

#ifndef ANDROID_POS
//! Thread Function (Data Type Def.)

typedef struct {
	pthread_t Pid;	
	pthread_mutex_t	Lock;
	bool bIsOngoing;
} THD_FUNC;

//! End to End Encryption

typedef struct
{
	UBYTE ENCTYPE;	// encryption key type
	UBYTE KEYID;	// encryption key ID

	// Union of encryption-specific data
	union
	{
		// Voltage-specific
		struct
		{
			uint16_t KTBLEN;
			UBYTE KTB[SZ_TRE2EE_KTB]; // Key Transmission Block for voltage
		} VOLTAGE;

		// EFTSEC-specific
		struct
		{
			UBYTE KSN[SZ_KSN];

			struct EncryptionInfo
			{
				UBYTE Mode;
				UBYTE CheckDigit;
			};

			EncryptionInfo PAN;
			EncryptionInfo Track[3];
			EncryptionInfo TrackPAN[3];
		} EFTSEC;
	};
}TRE2EE;

//! Historically separated. May be also useful in the future.

typedef struct
{
	UBYTE TRTRK1[MAX_TRACK_SZ];
	UBYTE TRTRK2[MAX_TRACK_SZ];
	UBYTE TRTRK3[MAX_TRACK_SZ];
	UBYTE TRPAN[MAX_PAN_SIZE+1];
} TRE2EESEC; // Secure E2EE data
#else
#define MAX_TRACK_SZ    244
#endif

//! Control Codes
// #define	NUL	0x0
#define	SOH	0x01
#define	STX	0x02
#define	ETX	0x03
#define	EOT	0x04
#define	ENQ	0x05
#define	ACK	0x06
#define	BEL	0x07
#define	BS	0x08
#define	HT	0x09
#define	LF	0x0A
#define	VT	0x0B
#define	FF	0x0C
#define	CR	0x0D
#define	SO	0x0E
#define	SI	0x0F
#define	DLE	0x10
#define	DC1	0x11
#define	DC2	0x12
#define	DC3	0x13
#define	DC4	0x14
#define	NAK	0x15
#define	SYN	0x16
#define	ETB	0x17
#define	CAN	0x18
#define	EM	0x19
#define	SUB	0x1A
#define	ESC	0x1B
#define	FS	0x1C
#define	GS	0x1D
#define	RS	0x1E
#define	US	0x1F

//! CVM Result Byte 1

#define EMV_CVM_OFFLINEPIN_PLAIN				0x01	// offline pin done by kernel
#define EMV_CVM_ONLINEPIN 						0x02
#define EMV_CVM_OFFLINEPIN_WITH_SIGNATURE 		0x03	// appl performs signature part only. offline pin done by kernel
#define EMV_CVM_OFFLINEPIN_ENC					0x04	// offline pin done by kernel
#define EMV_CVM_ENCOFFLINEPIN_WITH_SIGNATURE 	0x05	// appl performs signature part only. offline pin done by kernel
#define EMV_CVM_SIGNATURE 						0x1E
#define EMV_CVM_NO_CVM_REQUIRED					0x1F

// Pad Characters
#define PAD_F	'F'
#define PAD_D	'D'

// PIN Retries
#define PIN_RETRIES		3

#endif /* COREDEFINES_H_ */

