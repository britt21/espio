
#ifndef AMPPED_H_
#define AMPPED_H_

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
* File       	 : 		AMPPed.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/30/2015
**************************************************************************/

#include <Ped_common.h>
#include <AMPDataTypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MAC_LEN			8
#define DUKPT_KEY_LEN	16
#define DUKPT_KSN_LEN	10

//! Mode for Mac-ing
typedef enum {
	MODE_1				,	//  MAC method 1, TDES-TDES...TDES
	MODE_2				,	//  MAC method 2, XOR...XOR...TDES
	MODE_EMV			,	//  MAC for EMV EMV, DES-DES...TDES
	MODE_CUP			,	//  MAC for CUP, XOR-XOR...TDES(left)-XOR-TDES...
	MODE_DUKPT			,	//  MAC for DUKPT,Expand, XOR-XOR...TDES(left)-XOR-TDES...
} MAC_MODE;

//! Pinblock Format
typedef enum {
	PIN_FORMAT_0		,	//  PIN BLOCK FORMAT 0 - ANSI X9.8
	PIN_FORMAT_1		,	//  PIN BLOCK FORMAT 1
	PIN_FORMAT_2		,	//  PIN BLOCK FORMAT 2
	PIN_FORMAT_3		,	//  PIN BLOCK FORMAT 3
	PIN_FORMAT_4		,	//  PIN BLOCK FORMAT 4
	PIN_FORMAT_EPS	,	//  PIN BLOCK FORMAT EPS
} PIN_FORMAT;

//! Master Key Injection Mode
typedef enum {
	CLEARTTXT			,	// Master Key will be injected in clear text
	ENCRYPTED			,	// Master key injected is encrypted by another master key
} MKEY_INJECT_MODE;

//! TDEA Mode
typedef enum {
	ENCRYPT,
	DECRYPT
} TDEA_MODE;

//! Key Type
typedef enum {
	TYPE_MASTER_KEY,
	TYPE_SESS_PIN_KEY,
	TYPE_SESS_MAC_KEY,
	TYPE_SESS_DATA_KEY,
	TYPE_DUKPT,
} KEY_TYPE;

#ifndef TDEA_DECRYPT
#define TDEA_DECRYPT            0x00            // TDEA decryption
#endif

#ifndef TDEA_ENCRYPT
#define TDEA_ENCRYPT            0x01            // TDEA encryption
#endif

#ifndef TDEA_NONE
#define TDEA_NONE				0x02			// TDEA none
#endif


//! Generate Random Number
int PedGenerateRandom(unsigned char* buff, int byte_len);

//! Inject Fix Key
int PedWriteFixKey(int destKeyIDX, int KeyLen, unsigned char *FixKey);

//! Inject Master Key, in case mode is encrypted the srcKeyIDX is the master key
int PedWriteMasterKey(MKEY_INJECT_MODE Mode, int srcKeyIDX, int destKeyIDX, int KeyLen, unsigned char *MasterKey);

//! Inject Generic Working/Session Key (based on KeyType)
int PedWriteWorkingKey(int MasterKeyIDX, int WorkingKeyIDX, int KeyType, int KeyLen, unsigned char *WorkingKey);

//! Inject Working/Session PIN Key
int PedWritePinKey(int  MasterKeyIDX, int PinKeyIDX, int PinKeyLen, unsigned char *PinKey);

//! Inject Working/Session MAC Key
int PedWriteMacKey(int  MasterKeyIDX, int MacKeyIDX, int MacKeyLen, unsigned char *MacKey);

//! Inject Working/Session Data Key
int PedWriteDataKey(int  MasterKeyIDX, int DataKeyIDX, int DataKeyLen, unsigned char *DataKey);

//! Calculate MAC
int PedGetMac(int MacKeyIDX, unsigned char *DataIn, int InLen, MAC_MODE Mode, unsigned char *MacOut);

//! Triple DES Encryption using key previously injected keys
int PedTDEA(int Mode, int KeyType, unsigned int KeyIDX, unsigned char IV[8], int DataLen, const void *InBuf, void *OutBuf);

//! Checks if key is already injected
int PedCheckKey(int keySystem, int keyType, int keyIndex, int mode);

//! Injects DUKPT Keys
int PedCreateDukptKey(unsigned int DukptKeyIDX, unsigned int KeyLen, unsigned char *InitKey, unsigned char *InitKSN);

//! Get Future KSN
int PedGetDukptKSN(unsigned int DukptKeyIDX, unsigned char *CurrKSN);

//! Get Dukpt MAC
int PedGetDukptMac(unsigned int MacKeyIDX, unsigned char *DataIn, unsigned int InLen, MAC_MODE Mode, unsigned char *MacOut);

//! Dukpt Verify MAC Response
int PedVerifyDukptMacResponse(unsigned int MacKeyIDX, unsigned char *DataIn, unsigned int InLen, MAC_MODE Mode, unsigned char *MacOut, unsigned char *MacValMask);

//!Dukpt Data Encryption
int PedDukptEncrypt(unsigned int KeyIDX, unsigned char *DataIn, unsigned int InLen, unsigned char IV[8], unsigned char *DataOut);

//! Dukpt Data Decryption
int PedDukptDecrypt(unsigned int KeyIDX, unsigned char *DataIn, unsigned int InLen, unsigned char IV[8], unsigned char *DataOut);


#ifdef __cplusplus
}
#endif

#endif /* AMPPED_H_ */

