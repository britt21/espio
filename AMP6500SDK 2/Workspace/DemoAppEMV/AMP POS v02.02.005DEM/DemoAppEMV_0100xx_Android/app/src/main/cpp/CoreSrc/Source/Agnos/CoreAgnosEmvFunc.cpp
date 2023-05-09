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
* File       	 : 		CoreAgnosEmvFunc.cpp
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		08/30/2016
**************************************************************************/

/***************************************************************************
 * Includes
 **************************************************************************/

// Standard Library
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// AMP Library
#include <AMPUtils.h>
#include <AMPReturnCodes.h>

#include <EmvTags.h>
#include <BER-TLV.h>
#include <AMPDebug.h>

// Core Project Includes
#include "CoreAgnosEmvFunc.h"
#include "CoreScreens.h"
#include "CoreTransObj.h"
#include "CoreConfig.h"
#include "CoreFlow.h"
#include "CoreUtils.h"
#include "CoreDefines.h"
#include "CoreCardUtils.h"

// Project Includes
#include "Project.h"
#include "Screens.h"
#include "TransUtils.h"

/***************************************************************************
* Perprocessor Defines
**************************************************************************/
//#ifdef DEBUG_FLAG
#define DEBUG_EMV_DATAREAD
//#endif

/***************************************************************************
* Globals
**************************************************************************/
	
static BYTE gTagList[] = {
	0x9F, 0x39, 0x9F, 0x27, 0x9F, 0x1A, 0x9A, 0x9F, 0x26, 0x82, 0x9F, 0x36, 0x9F, 0x37, 0x95, 0x9B, 0x9C, 0x5F, 0x2A, 0x5F, 0x57, 0x9F, 0x41, 0x9F, 0x4E,
	0x9F, 0x02, 0x9F, 0x03, 0x9F, 0x07, 0x9F, 0x0D, 0x9F, 0x0E, 0x9F, 0x0F, 0x9F, 0x10, 0x5F, 0x34, 0x9F, 0x35, 0x9F, 0x34, 0x9F, 0x09, 0x84, 0x5A, 
	0x9F, 0x6B, 0x99, 0x9F, 0x1C, 0x9F, 0x1E, 0x9F, 0x15, 0x9F, 0x16, 0x4F, 0x9F, 0x12, 0x50, 0x5F, 0x30, 0x5F, 0x20, 0x5F, 0x24, 0x9F, 0x33, 0x5F, 0x25, 
	0x5F, 0x28, 0x57, 0x9F, 0x6E, 0x9F, 0x01, 0x9F, 0x53, 0x9F, 0x6D, 0x8A, 0x9F, 0x66, 0x5F, 0x2D, 0x8f, 0x9f, 0x6c, 0x9F, 0x1D, 0x5F, 0x36, 0x9F, 0x40,
	0x9F, 0x06, 0x9F, 0x21
};

/***************************************************************************
* Local Functions
**************************************************************************/
int SetAdditionalEMVTags();
int EmvSetTransPinByPass(void);
int DoSetAdditionalTransactionalContext(void);

/***************************************************************************
* Implementations
**************************************************************************/

//!@returns outcome: 	ocOFFLINE_APROVED, ocONLINE_REQUEST, ocOFFLINE_DECLINED, ocNOT_ACCEPTED 
//!						ocSELECT_NEXT_NOT_ACCEPTED, ocSELECT_NEXT_RETRY, ocEND_APPLICATION, ocOFFLINE_FAILED
int DoAgnosEmvInitiateFlow(TRANSACTION_OBJECT1 *pobTran)
{
	int iRetVal = AMP_SUCCESS;
	long lnCBAmount = 0;
	int EmvCardDecision =0;
	
	cAMPAgnosEmv *pAgnosEmv = cAMPAgnosEmv::get_Instance();
	cAMPAgnos *pAgnos = cAMPAgnos::get_Instance();
	char szHeader[MAX_HEADER_SIZE+1]	= { 0 };

	pAgnosEmv->SetAmount(atol(pobTran->szBaseAmount));
	pAgnosEmv->SetCashbackAmount(lnCBAmount);

	//2 1. Setup Tag List
	pAgnosEmv->SetTagListCollection( gTagList, sizeof(gTagList));
	
	//2 2. Initiliaze EMV Agnos Data	
	pAgnosEmv->InitTrans();
	
	//2 3. Power On Card Reader
	iRetVal = pAgnosEmv->PowerOn();

	if( iRetVal != AMP_SUCCESS) {
		pAgnosEmv->RemoveChipCard();
		return iRetVal;
	}
		
	do {
		//2 4. Select Application	
		iRetVal = pAgnosEmv->EmvSelectApplication(); //returns AMP_SUCCESS
		if(iRetVal == ocNOT_ACCEPTED || iRetVal == ocTRY_ANOTHER_INTERFACE || iRetVal == ocTRANSACTION_CANCELLED || iRetVal == ocEND_APPLICATION) {
			pAgnosEmv->RemoveChipCard();

			if(iRetVal == ocTRANSACTION_CANCELLED)
				iRetVal = AMP_CANCEL;
			else if(iRetVal == ocNOT_ACCEPTED)
				iRetVal = ocTRY_ANOTHER_INTERFACE;
			else if(iRetVal == ocEND_APPLICATION)
				iRetVal = AMP_ERROR;

			return iRetVal;
		}
		
		//2 5. Select Language
		iRetVal = pAgnosEmv->EmvSelectLanguage(); //retuns AMP_SUCCESS
		if(iRetVal == ocNOT_ACCEPTED || iRetVal == ocTRY_ANOTHER_INTERFACE || iRetVal == ocTRANSACTION_CANCELLED || iRetVal == ocEND_APPLICATION) {

			pAgnosEmv->RemoveChipCard();

			if(iRetVal == ocTRANSACTION_CANCELLED)
				iRetVal = AMP_CANCEL;
			else if(iRetVal == ocNOT_ACCEPTED)
				iRetVal = ocTRY_ANOTHER_INTERFACE;
			else if(iRetVal == ocEND_APPLICATION)
				iRetVal = AMP_ERROR;
			
			return iRetVal;
		} 

		//2 6. Setup Agnos Transactional Context
		iRetVal = pAgnosEmv->EmvSetTransactionalContext(); //returns AMP_SUCCESS

		//2 6.a Set Additional Transactional Context
		iRetVal = DoSetAdditionalTransactionalContext();

		//2 6.b Set Transaction PIN Bypass
		iRetVal = EmvSetTransPinByPass();

		//2 7. Open Agnos Kernel Session
		iRetVal = pAgnosEmv->EmvOpenKernelSession(); //returns AMP_SUCCESS, AMP_ERROR

		//2 8. Set EMV Mandatory Tags
		iRetVal = pAgnosEmv->EmvSetMandatoryTags(); //returns AMP_SUCCESS

		//2 8.a Set Additional EMV Tags
		iRetVal = SetAdditionalEMVTags(); //returns AMP_SUCCESS

		//2 9. Initiate Application
		//returns outcome
		iRetVal = pAgnosEmv->EmvInitiateApplication(); //1st GenAc 
	
	}while(iRetVal == ocSELECT_NEXT_NOT_ACCEPTED || iRetVal == ocSELECT_NEXT_RETRY);

	// When not going online, power off card because transaction is completed
	// Else, it will be performed at completion time
	if(iRetVal != ocONLINE_REQUEST) {
		pAgnosEmv->DeInitTrans();
	}

	switch(iRetVal) {
	case ocONLINE_REQUEST:
		EmvCardDecision = EMV_GO_ONLINE;
		break;
	case ocOFFLINE_APPROVED:
		EmvCardDecision = EMV_APPROVED;
		break;
	case ocOFFLINE_DECLINED:
	case ocNOT_ACCEPTED:
	case ocOFFLINE_FAILED:
	default:
        EmvCardDecision = EMV_DECLINE;
        iRetVal = AMP_ERROR;
        pAgnosEmv->RemoveChipCard();
        break;
	}

#ifdef ENCRYPT_SENSITIVE_DATA
	CARD_TRACK_DATA *pCardData = pAgnos->GetCardTrackData(CARD_ENTRY_INSERT);
	if(pCardData != NULL)
	{
		memcpy(pobTran->szTrack1, pCardData->PANMasked, strlen(pCardData->PANMasked));
		memcpy(pobTran->szTrack2, pCardData->Track2Masked, strlen(pCardData->Track2Masked));
		memcpy(pobTran->szTrack1Enc, pCardData->PANEncrypt, strlen(pCardData->PANEncrypt));
		memcpy(pobTran->szTrack2Enc, pCardData->Track2Encrypt, strlen(pCardData->Track2Encrypt));

		//Check if track 2 data is present
		if (strlen((char*)pobTran->szTrack2) != 0) {
			PutMSRTrackDataToTransObj(pobTran);
			iRetVal = AMP_SUCCESS;
		}
		else
			iRetVal = AMP_ERROR;
	}
#endif

	DoAgnosEmvFirstReadTLVCollxn(pobTran);
	return iRetVal;
}

int DoSetAdditionalTransactionalContext(void)
{
	cAMPAgnosEmv *pAgnosEmv = cAMPAgnosEmv::get_Instance();
	pAgnosEmv->EmvGetTransactionalContext();
	return AMP_SUCCESS;
}

int DoAgnosEmvCompletion(TRANSACTION_OBJECT1 *pobTran)
{
	int iRetVal = AMP_SUCCESS;
	unsigned char uCID=0;
	unsigned char uARC[2] ={0};
	BYTE TagData[EMV_MAX_DATA_SIZE];
	int EmvCardDecision=EMV_UNKNOWN;
	BER_TLV* pTLV = NULL;
	BYTE bTLVIssuerResp[ISSUER_RESPONSE_SIZE]= { 0 };
	unsigned long lnTLVSize = 0;
	int TagDataLen = 0;
	BOOL bUnableToGoOnline = FALSE;
	char szHeader[MAX_HEADER_SIZE+1]	= { 0 };
	
	cAMPAgnosEmv *pAgnosEmv = cAMPAgnosEmv::get_Instance();

	if(pobTran->iCardEntryMethod != CARD_INSERT)
		return AMP_SUCCESS;

    uCID = TC;
    memcpy(uARC, AUTH_ACCEPTED, 2);

	//Set Online Response
	pAgnosEmv->EmvSetOnlineResponse( uARC, uCID, bTLVIssuerResp, lnTLVSize);

	//Process Completion
	iRetVal = pAgnosEmv->EmvCompletion();
	pAgnosEmv->EmvCloseKernelSession();

	pAgnosEmv->RemoveChipCard();

	//Evaluate OutCome
	switch(iRetVal) {
	case ocONLINE_REQUEST:
		EmvCardDecision = EMV_GO_ONLINE; //should not happen
		iRetVal = AMP_SUCCESS;
		break;
	case ocOFFLINE_APPROVED:
	case ocAPPROVED:
		EmvCardDecision = EMV_APPROVED;
		iRetVal = AMP_SUCCESS;
		break;
	case ocOFFLINE_DECLINED:
	case ocDECLINED:	
	case ocNOT_ACCEPTED:
	case ocOFFLINE_FAILED:
	case ocEND_APPLICATION:
	case ocFAILED:	
	case ocNOT_EMV_CARD_POOLED:
	case ocTRANSACTION_CANCELLED:	
	default:
		EmvCardDecision = EMV_DECLINE;
		iRetVal = AMP_SUCCESS;
		break;
	}

    pobTran->iCardEntryMethod = CARD_NONE;
	return iRetVal;
}

int SetAdditionalEMVTags()
{
	int iRetVal = AMP_SUCCESS;
	BYTE TagData[EMV_MAX_DATA_SIZE];
	
	cAMPAgnosEmv *pAgnosEmv = cAMPAgnosEmv::get_Instance();
	
	return iRetVal;
}

void DoAgnosEmvFirstReadTLVCollxn(TRANSACTION_OBJECT1 *pobTran)
{
#ifdef DEBUG_EMV_DATAREAD
	ENTER_FUNC();
#endif

	char TagDataAscii[(EMV_MAX_DATA_SIZE*2)+1];
	BYTE TagData[EMV_MAX_DATA_SIZE];
	BYTE TagDataLen = 0;
	BYTE TagDataCrypto[EMV_MAX_DATA_SIZE];

	cAMPAgnosEmv *pAgnosEmv = cAMPAgnosEmv::get_Instance();

	//POS Entry Mode 9F39
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9F39, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F39_POS_ENTRY_MODE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F39_POS_ENTRY_MODE, TagDataLen, "TAG_9F39_POS_ENTRY_MODE");
		#endif
	}

	//Additional Terminal Capabilities 9F40
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9F40, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F40_TERM_ADTNAL_CAP, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F40_TERM_ADTNAL_CAP, TagDataLen, "TAG_9F40_TERM_ADTNAL_CAP");
		#endif
	}

	//Language Preference 5F2D
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x5F2D, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_5F2D_LANG_PREFERENCE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_5F2D_LANG_PREFERENCE, TagDataLen, "TAG_5F2D_LANG_PREFERENCE");
		#endif
	}
	
	//Transaction Category Code 9F53
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9F53, TagData, sizeof(TagData))) > 0)
	{		
		memcpy(pobTran->TAG_9F53_TERM_CAT_CODE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F53_TERM_CAT_CODE, TagDataLen, "TAG_9F53_TERM_CAT_CODE");
		#endif
	}
	else if ((TagDataLen = pAgnosEmv->EmvGetTransCategoryCode(TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F53_TERM_CAT_CODE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F53_TERM_CAT_CODE, TagDataLen, "TAG_9F53_TERM_CAT_CODE");
		#endif
	}

#ifndef ENCRYPT_SENSITIVE_DATA
	// PAN 5A
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9F6B, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F6B_TRACK2_DATA, TagData, TagDataLen);

		memset(TagDataAscii, 0, sizeof(TagDataAscii));
		BinHexToAsciiHex(TagData, (BYTE*)TagDataAscii, TagDataLen);
		RemovePadChar(TagDataAscii, PAD_D, PAD_BOTH); // Remove Pad Char D
		strcpy(pobTran->szPAN, TagDataAscii);

		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F6B_TRACK2_DATA, TagDataLen, "TAG_9F6B_TRACK2_DATA");
		#endif
	}
	else if((TagDataLen = pAgnosEmv->EmvGetTag(0x57, TagData, sizeof(TagData))) > 0)
	{
		char* delimiter = NULL;
		
		memcpy(pobTran->TAG_57_TRACK2_EQ_DATA, TagData, TagDataLen);

		memset(TagDataAscii, 0, sizeof(TagDataAscii));
		BinHexToAsciiHex(TagData, (BYTE*)TagDataAscii, TagDataLen);
		
		if((delimiter = strstr(TagDataAscii, "D")) != NULL)
			*delimiter = '=';

		RemovePadChar(TagDataAscii, '='); // Remove Pad Char F
		strcpy(pobTran->szPAN, TagDataAscii);

		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F6B_TRACK2_DATA, TagDataLen, "TAG_9F6B_TRACK2_DATA");
		#endif
	}
	else if((TagDataLen = pAgnosEmv->EmvGetTag(0x5a, TagData, sizeof(TagData))) > 0)
	{		
		memcpy(pobTran->TAG_5A_APPL_PAN, TagData, TagDataLen);

		memset(TagDataAscii, 0, sizeof(TagDataAscii));
		BinHexToAsciiHex(TagData, (BYTE*)TagDataAscii, TagDataLen);
		RemovePadChar(TagDataAscii, PAD_F); // Remove Pad Char F
		strcpy(pobTran->szPAN, TagDataAscii);

		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_5A_APPL_PAN, TagDataLen, "TAG_5A_APPL_PAN");
		#endif
	}
#endif
	// Add tag 4F (AID)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x4f, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_4F_AID, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_4F_AID, TagDataLen, "TAG_4F_AID");
		#endif
	}
	else if ((TagDataLen = pAgnosEmv->EmvGetAIDInfo(TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_4F_AID, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_4F_AID, TagDataLen, "TAG_4F_AID");
		#endif
	}

	// Add tag 95 (TVR)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x95, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_95_TVR, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_95_TVR, TagDataLen, "TAG_95_TVR");
		#endif
	}

	// Get CID, 1 byte (0x9F27, 0X01, [AAC, TC, ARQC])
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f27, TagData, sizeof(TagData))) > 0)
	{
		memset(TagDataAscii, 0, sizeof(TagDataAscii));
		BinHexToAsciiHex(TagData, (BYTE*)TagDataAscii, TagDataLen);

		#ifdef DEBUG_EMV_DATAREAD
		DEBUG_INFO("pAgnosEmv->EMVIsQuickChipTrans(): %d", pAgnosEmv->EMVIsQuickChipTrans());
		_LogHEXBuffer((unsigned char*)TagData, TagDataLen, "CRYPTO: 0x9f27");
		#endif

		if((pAgnosEmv->EMVIsQuickChipTrans() == TRUE) && (strcmp(TagDataAscii, "00") == 0))
		{
			AsciiHexToBinHex((BYTE*)"80", TagDataCrypto, TagDataLen);
			memcpy(pobTran->TAG_9F27_CRYPT_INFO_DATA, TagDataCrypto, TagDataLen);
		}
		else
			memcpy(pobTran->TAG_9F27_CRYPT_INFO_DATA, TagData, TagDataLen);
			
					
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F27_CRYPT_INFO_DATA, TagDataLen, "TAG_9F27_CRYPT_INFO_DATA");
		#endif
	}
	
	// Add tag 9F12 (application preferred name)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f12, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F12_APPL_PRE_NAME, TagData, TagDataLen);

		#ifdef DEBUG_EMV_DATAREAD
		TagData[TagDataLen] = 0; //4 Native Data is already Ascii
		DEBUG_INFO("TAG_9F12_APPL_PRE_NAME (%s)", TagData);
		#endif
	}
	// Add tag 50 (application label)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x50, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_50_APPL_LABEL, TagData, TagDataLen);

		#ifdef DEBUG_EMV_DATAREAD
		TagData[TagDataLen] = 0; //4 Native Data is already Ascii
		DEBUG_INFO("TAG_50_APPL_LABEL (%s)", TagData);
		#endif
	}
	// Add tag 5F30 (service code)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x5f30, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_5F30_SERVICE_CODE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_5F30_SERVICE_CODE, TagDataLen, "TAG_5F30_SERVICE_CODE");
		#endif
	}
	// Add tag 5F20 (card holder name)	( This Data is alrady ASCII )
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x5f20, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_5F20_CARDHOLDER_NAME, TagData, TagDataLen);

		TagData[TagDataLen] = 0; //4 Native Data is already Ascii
		strcpy(pobTran->szCardHolderName, (char*)TagData);

		#ifdef DEBUG_EMV_DATAREAD
		DEBUG_INFO("TAG_5F20_CARDHOLDER_NAME (%s)", TagData);
		#endif
	}
	// Add tag 57 (track 2)
/*	if(((TagDataLen = pAgnosEmv->EmvGetTag(0x57, TagData, sizeof(TagData))) > 0) ||
		((TagDataLen = pAgnosEmv->EmvGetTag(0x9F6B, TagData, sizeof(TagData))) > 0))
	{
		char* delimiter = NULL;

		memset(TagDataAscii, 0, sizeof(TagDataAscii));
		BinHexToAsciiHex(TagData, (BYTE*)TagDataAscii, TagDataLen);
		
		if((delimiter = strstr(TagDataAscii, "D")) != NULL)
			*delimiter = '=';

		RemovePadChar(TagDataAscii, PAD_F); // Remove Pad Char F
		strcpy((char*)pobTran->szTrack2, TagDataAscii);
	
		#ifdef DEBUG_EMV_DATAREAD
		DEBUG_INFO("TAG_57_TRACK2_EQ_DATA -> Track2 (%s)", TagDataAscii);
		#endif
	}			
*/	// Add tag 5F24 (expiry date)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x5f24, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_5F24_EXPIRY_DATE, TagData, TagDataLen);

		memset(TagDataAscii, 0, sizeof(TagDataAscii));
		BinHexToAsciiHex(TagData, (BYTE*)TagDataAscii, TagDataLen);

		// Convert as MMYY (Same as Manual Entry Format)
		memmove(TagDataAscii+2, TagDataAscii, 4);
		memcpy(TagDataAscii, TagDataAscii+4, 2);
		TagDataAscii[4] = 0;
		
		strcpy(pobTran->szExpiry, TagDataAscii);
		#ifdef DEBUG_EMV_DATAREAD
		DEBUG_INFO("TAG_5F24_EXPIRY_DATE (%s)", TagDataAscii);
		#endif
	}
	// Add tag 9F33 (Terminal Capabilities)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f33, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F33_TERM_CAP, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F33_TERM_CAP, TagDataLen, "TAG_9F33_TERM_CAP");
		#endif
	}
	// Add tag 5F34 (PAN sequence number)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x5f34, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_5F34_APPL_PAN_SEQNUM, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_5F34_APPL_PAN_SEQNUM, TagDataLen, "TAG_5F34_APPL_PAN_SEQNUM");
		#endif
	}
	// Add tag 5F25 (Application Effective Date)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x5f25, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_5F25_EFFECT_DATE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_5F25_EFFECT_DATE, TagDataLen, "TAG_5F25_EFFECT_DATE");
		#endif
	}
	// Add tag 5F28 (Issuer Country Code)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x5f28, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_5F28_ISSUER_COUNTY_CODE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_5F28_ISSUER_COUNTY_CODE, TagDataLen, "TAG_5F28_ISSUER_COUNTY_CODE");
		#endif
	}
	// Add tag 9F1A (Terminal Country Code)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f1A, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F1A_TERM_COUNTY_CODE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F1A_TERM_COUNTY_CODE, TagDataLen, "TAG_9F1A_TERM_COUNTY_CODE");
		#endif
	}
	// Add tag 82 (Application Interchange Profile)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x82, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_82_APPL_INTCHG_PROFILE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_82_APPL_INTCHG_PROFILE, TagDataLen, "TAG_82_APPL_INTCHG_PROFILE");
		#endif
	}
	// Add tag 9F35 (EMV Terminal Type)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f35, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F35_TERM_TYPE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F35_TERM_TYPE, TagDataLen, "TAG_9F35_TERM_TYPE");
		#endif
	}
	// Add tag 9F09 (Application Version Number)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f09, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F09_TERM_VER_NUM, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F09_TERM_VER_NUM, TagDataLen, "TAG_9F09_TERM_VER_NUM");
		#endif
	}
	// Add tag 84 (Dedicated Filename)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x84, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_84_DF_NAME, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_84_DF_NAME, TagDataLen, "TAG_84_DF_NAME");
		#endif
	}

//#ifdef DEBUG_EMV_DATA_LOG
	// Add tag 9F1B (Terminal Floor Limit)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f1b, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F1B_TERM_FLOOR_LIMIT, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F1B_TERM_FLOOR_LIMIT, TagDataLen, "TAG_9F1B_TERM_FLOOR_LIMIT");
		#endif
	}
//#endif

	// Get TSI, 4 bytes (0x9B, 0x02, 0xnn, 0xnn)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9b, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9B_TSI, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9B_TSI, TagDataLen, "TAG_9B_TSI");
		#endif
	}
	// Add tag 95 (TVR)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x95, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_95_TVR, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_95_TVR, TagDataLen, "TAG_95_TVR");
		#endif
	}

	// Add tag 8E (CVM List)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x8E, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_8E_CVM_LIST, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_8E_CVM_LIST, TagDataLen, "TAG_8E_CVM_LIST");
		#endif
	}

	// Add tag 9F34 (CVM Result)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f34, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F34_CVM_RESULTS, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F34_CVM_RESULTS, TagDataLen, "TAG_9F34_CVM_RESULTS");
		#endif
	}
	#if 0
	// Get CID, 1 byte (0x9F27, 0X01, [AAC, TC, ARQC])
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f27, TagData, sizeof(TagData))) > 0)
	{
		pobTran->EmvColxnPutBin(TL(TAG_9F27_CRYPT_INFO_DATA), TagData, TagDataLen); 
		memset(TagDataAscii, 0, sizeof(TagDataAscii));
		BinHexToAsciiHex(TagData, (BYTE*)TagDataAscii, TagDataLen);

		#ifdef DEBUG_EMV_DATAREAD
		pobTran->EmvColxnGetStr(TL(TAG_9F27_CRYPT_INFO_DATA), TagDataAscii, sizeof(TagDataAscii)-1);
		DEBUG_INFO("TAG_9F27_CRYPT_INFO_DATA (%s)", TagDataAscii);
		#endif
	}
	#endif
	// Add tag 9F26 (cryptogram)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f26, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F26_APPL_CRYPTOGRAM, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F26_APPL_CRYPTOGRAM, TagDataLen, "TAG_9F26_APPL_CRYPTOGRAM");
		#endif
	}
	// Add tag 9F36 (ATC)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f36, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F36_ATC, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F36_ATC, TagDataLen, "TAG_9F36_ATC");
		#endif
	}	
	// Add tag 5F2A (Transaction Currency Code)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x5f2a, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_5F2A_TRANS_CURCY_CODE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_5F2A_TRANS_CURCY_CODE, TagDataLen, "TAG_5F2A_TRANS_CURCY_CODE");
		#endif

	}
	// Add tag 9C (Transaction Type)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9c, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9C_TRAN_TYPE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9C_TRAN_TYPE, TagDataLen, "TAG_9C_TRAN_TYPE");
		#endif
	}
	// Add tag 9F10 (Issuer Application Data)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f10, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F10_ISSUER_APP_DATA, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F10_ISSUER_APP_DATA, TagDataLen, "TAG_9F10_ISSUER_APP_DATA");
		#endif
	}
	// Add tag 9F02 (Cryptogram Amount)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f02, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F02_AMT_AUTH_NUM, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F02_AMT_AUTH_NUM, TagDataLen, "TAG_9F02_AMT_AUTH_NUM");
		#endif
	}
	// Add tag 9F03 (Cryptogram Amount)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f03, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F03_AMT_OTHER_NUM, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F03_AMT_OTHER_NUM, TagDataLen, "TAG_9F03_AMT_OTHER_NUM");
		#endif
	}
	// Add tag 9F07 (Application Usage Control)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f07, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F07_APPL_USE_CNTRL, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F07_APPL_USE_CNTRL, TagDataLen, "TAG_9F07_APPL_USE_CNTRL");
		#endif
	}
	// Add tag 9F0D (Issuer Action Code - Default)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f0D, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F0D_IAC_DEFAULT, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F0D_IAC_DEFAULT, TagDataLen, "TAG_9F0D_IAC_DEFAULT");
		#endif
	}
	// Add tag 9F0E (Issuer Action Code - Denial)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f0E, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F0E_IAC_DENIAL, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F0E_IAC_DENIAL, TagDataLen, "TAG_9F0E_IAC_DENIAL");
		#endif
	}
	// Add tag 9F0F (Issuer Action Code - Online)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f0F, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F0F_IAC_ONLINE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F0F_IAC_ONLINE, TagDataLen, "TAG_9F0F_IAC_ONLINE");
		#endif
	}
	// Add tag 9F37 (Unpredictable Number)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f37, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F37_UNPRED_NUM, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F37_UNPRED_NUM, TagDataLen, "TAG_9F37_UNPRED_NUM");
		#endif
	}
	// Add tag 9A (Transaction Date)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9a, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9A_TRAN_DATE, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		DEBUG_INFO("TAG_9A_TRAN_DATE (%s)", TagDataAscii);
		#endif
	}
	// Add tag 9F21 (Transaction Time)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f21, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F21_TRANS_TIME, TagData, TagDataLen);

		memset(TagDataAscii, 0, sizeof(TagDataAscii));
		BinHexToAsciiHex(TagData, (BYTE*)TagDataAscii, TagDataLen);
		strcpy(pobTran->szTransTime, TagDataAscii);
		#ifdef DEBUG_EMV_DATAREAD
		DEBUG_INFO("TAG_9F21_TRANS_TIME (%s)", TagDataAscii);
		#endif
	}
	
	// Add tag 9F6E VISA (Form Factor Indicator), MasterCard Device Type
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f6e, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F6E_EC_FORM_FACTOR_IND, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F6E_EC_FORM_FACTOR_IND, TagDataLen, "TAG_9F6E_EC_FORM_FACTOR_IND");
		#endif
	}
	
	// Add tag 9F70 Interac (Form Factor Indicator)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f70, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F70_FLASH_FORM_FACTOR_IND, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F70_FLASH_FORM_FACTOR_IND, TagDataLen, "TAG_9F70_FLASH_FORM_FACTOR_IND");
		#endif
	}

	// Add tag 9F59 Interac Terminal Transaction Information (TTI)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f59, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F59_FLASH_TTI, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F59_FLASH_TTI, TagDataLen, "TAG_9F59_FLASH_TTI");
		#endif
	}

	// Add tag 9F06 (Application Identifier - Terminal)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f06, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F06_APPL_ID, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F06_APPL_ID, TagDataLen, "TAG_9F06_APPL_ID");
		#endif
	}

	// Add tag 9F41 (Transaction Sequence Counter)
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f41, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F41_TRANS_SEQ_COUNTER, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F41_TRANS_SEQ_COUNTER, TagDataLen, "TAG_9F41_TRANS_SEQ_COUNTER");
		#endif
	}
	
	// Add tag 9F1E (Interface Device (IFD) Serial Number )
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f1e, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F1E_IFD_SER_NUM, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F1E_IFD_SER_NUM, TagDataLen, "TAG_9F1E_IFD_SER_NUM");
		#endif
	}

	// Add tag 9F24 (Payment Account Reference (PAR))
	if((TagDataLen = pAgnosEmv->EmvGetTag(0x9f24, TagData, sizeof(TagData))) > 0)
	{
		memcpy(pobTran->TAG_9F24_PAYMENT_ACCNT_REF, TagData, TagDataLen);
		#ifdef DEBUG_EMV_DATAREAD
		_LogHEXBuffer(pobTran->TAG_9F24_PAYMENT_ACCNT_REF, TagDataLen, "TAG_9F24_PAYMENT_ACCNT_REF");
		#endif
	}
}

int EmvSetTransPinByPass(void)
{
	int iRetVal=AMP_SUCCESS;
	BOOL bPinByPass = FALSE;
	char szAID[(EMV_MAX_DATA_SIZE*2)+1]={0};
	BYTE byAID[EMV_MAX_DATA_SIZE]={0};
	int iAIDLen=0;
	cAMPAgnosEmv *pAgnosEmv = cAMPAgnosEmv::get_Instance();

	iAIDLen = pAgnosEmv->EmvGetAIDInfo(byAID, sizeof(byAID));
	BinHexToAsciiHex(byAID, (BYTE*)szAID, iAIDLen);

	// Set to false as a static brute-force value
	// to be replaced by own checking of PIN bypass assessment
	bPinByPass = false;

	pAgnosEmv->EmvSetTransPinByPass(bPinByPass);

	return iRetVal;
}
