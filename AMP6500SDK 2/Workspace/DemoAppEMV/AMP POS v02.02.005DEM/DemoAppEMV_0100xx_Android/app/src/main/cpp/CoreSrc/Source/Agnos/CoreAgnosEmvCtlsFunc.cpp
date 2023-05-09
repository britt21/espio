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
* File       	 : 		CoreAgnosEmvCtlsFunc.cpp
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		08/31/2016
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
#include <CoreConfig.h>
#include <TransUtils.h>

// Core Project Includes
#include "CoreAgnosEmvFunc.h"
#include "CoreScreens.h"
#include "CoreTransObj.h"
#include "CoreFlow.h"
#include "CoreUtils.h"
#include "CoreDefines.h"
#include "CoreCardUtils.h"
#include "CoreAgnosEmvCtlsFunc.h"

// Project Includes
#include "Project.h"
#include "Screens.h"


/***************************************************************************
* Perprocessor Defines
**************************************************************************/

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
BOOL EmvAIDIsSupported(void);

/***************************************************************************
* Implementations
**************************************************************************/

int DoAgnosEmvCtlsInitiateFlow(TRANSACTION_OBJECT1 *pobTran)
{
	int iRetVal = AMP_SUCCESS;
	long lnCBAmount=0;
	int EmvCardDecision = 0;
	BYTE byCurrCode[2]={0};
	char *szCurrencyCode[20]={0};

	cAMPAgnosEmvCtls *pAgnosEmvCtls = cAMPAgnosEmvCtls::get_Instance();

	//1 Initial Setup for Agnos Transaction
	pAgnosEmvCtls->SetAmount(atol(pobTran->szBaseAmount));
	pAgnosEmvCtls->SetCashbackAmount(lnCBAmount);

	//Set Currency Code
	memcpy(szCurrencyCode, "0840", sizeof(szCurrencyCode));
	AsciiHexToBinHex((unsigned char *)szCurrencyCode, byCurrCode, sizeof(byCurrCode));	
	pAgnosEmvCtls->SetTransCurrCode(byCurrCode);

	unsigned long SeqNo = 1;

	pAgnosEmvCtls->SetTransSeqCounter(SeqNo);

	//2 1. Setup Tag List
	pAgnosEmvCtls->SetTagListCollection( gTagList, sizeof(gTagList));

	//2 2. Init Trans
	iRetVal = pAgnosEmvCtls->InitTrans();

	//sets timeout for "Try again"
	iRetVal = pAgnosEmvCtls->SetPollingTimeOut(30);
	
	iRetVal = pAgnosEmvCtls->ProcessCtlsEntryPoint();

	// Unknown AID: If AID is not Card blocked but Empty Candidate List, Switch to another interface
	// This is specific to Discover Test Case: E2E CL 20 (Unknown AID)
	if(!pAgnosEmvCtls->IsCardBlocked() && (pAgnosEmvCtls->IsMutualListEmpty()))
	{
		iRetVal = ocTRY_ANOTHER_INTERFACE;
	}


	//2 Evaluate Outcome
	switch(iRetVal)
	{
	case ocNOT_EMV_CARD_POOLED: //MAG EMV DATA
		break;
	case ocTRY_ANOTHER_INTERFACE: //To fallback?
		break;
	case ocTRANSACTION_CANCELLED:
		iRetVal = AMP_CANCEL;
		pAgnosEmvCtls->BeepError();
		break;
	case ocONLINE_REQUEST:
		EmvCardDecision = EMV_GO_ONLINE;
		break;
	case ocAPPROVED:
		EmvCardDecision = EMV_APPROVED;
		break;
	case ocOFFLINE_APPROVED:
		EmvCardDecision = EMV_APPROVED;
		break;
	case ocOFFLINE_DECLINED:
	case ocDECLINED:
		EmvCardDecision = EMV_DECLINE;
		break;
	case ocNOT_ACCEPTED:
	case ocOFFLINE_FAILED:
	case ocEND_APPLICATION:
	case ocFAILED:	
	default:
		EmvCardDecision = EMV_DECLINE;
		iRetVal = AMP_ERROR;
		break;
	}

#ifdef ENCRYPT_SENSITIVE_DATA
	cAMPAgnos *pAgnos = cAMPAgnos::get_Instance();
	CARD_TRACK_DATA *pCardData = pAgnos->GetCardTrackData(CARD_ENTRY_TAP);
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


int DoAgnosEmvCtlsCompletion(TRANSACTION_OBJECT1 *pobTran)
{
	int iRetVal = AMP_SUCCESS;
	unsigned char uCID=0;
	unsigned char uARC[2] ={0};
	int EmvCardDecision=0;
	BYTE TagData[EMV_MAX_DATA_SIZE];
	BER_TLV* pTLV = pstTLV_make_element();
	BYTE bTLVIssuerResp[ISSUER_RESPONSE_SIZE]= { 0 };
	unsigned long lnTLVSize = 0;
	int TagDataLen = 0;

	cAMPAgnosEmvCtls *pAgnosEmvCtls = cAMPAgnosEmvCtls::get_Instance();

	if(pobTran->iCardEntryMethod != CARD_TAP)
		return AMP_SUCCESS;

    uCID = TC;
    memcpy(uARC, AUTH_ACCEPTED, 2);

	//Set Online Response
	pAgnosEmvCtls->EmvSetOnlineResponse( uARC, uCID, bTLVIssuerResp, lnTLVSize);
	iRetVal = pAgnosEmvCtls->ProcessCtlsCompletion();

	//2 Evaluate Outcome
	switch(iRetVal)
	{
	case ocONLINE_REQUEST:
		EmvCardDecision = EMV_GO_ONLINE;
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
		pAgnosEmvCtls->BeepError();

		iRetVal = AMP_SUCCESS;
		break;
	}

	pobTran->iCardEntryMethod = CARD_NONE;
	return iRetVal;
}

BOOL EmvAIDIsSupported(void)
{
	int iRetVal=AMP_SUCCESS;
	BOOL bPinByPass = FALSE;
	char szAID[(EMV_MAX_DATA_SIZE*2)+1]={0};
	BYTE byAID[EMV_MAX_DATA_SIZE]={0};
	int iAIDLen=0;
	cAMPAgnosEmv *pAgnosEmv = cAMPAgnosEmv::get_Instance();
	BOOL bAIDSupported = FALSE;

	iAIDLen = pAgnosEmv->EmvGetAIDInfo(byAID, sizeof(byAID));
	BinHexToAsciiHex(byAID, (BYTE*)szAID, iAIDLen);

    // Set to true as a static brute-force value
    // to be replaced by own checking of AID validation
	bAIDSupported = true;

	return bAIDSupported;
}

