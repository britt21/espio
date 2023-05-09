
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
* File       	 : 		CoreCardUtils.cpp
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		09/07/2015
**************************************************************************/

/***************************************************************************
 * Includes
 **************************************************************************/

// Standard Library
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// AMP Library
#include <AMPUtils.h>
#include <AMPAgnos.h>
#include <AMPReturnCodes.h>
#include <AMPDebug.h>

// Core Project Includes
#include "CoreCardUtils.h"
#include "CoreFlow.h"

// Project Includes
#include "Project.h"
#include "SizeDefines.h"
#include "CoreConfig.h"
#include "Screens.h"

/***************************************************************************
* Perprocessor Defines
**************************************************************************/

//! Compare PANs
int PANCompare(const char* pan1, const char* pan2);

//! Returns the Bin Range Index
int FindBinRange(const char* szPAN);

//! Select Acquirer and Issuer. For Mulit Acq/Iss.
void AcquirersBaseOnBIN(char* szExpctRange, int SuppAcqList[], int& iSuppAcqCnt);
void AcquirersBaseOnAID(char* szAID, int SuppAcqList[], int& iSuppAcqCnt);
void IssuersBaseOnBIN(int iSelectedAcq, char* szExpctRange, int SuppIssList[], int& iSuppIssCnt);
void IssuersBaseOnAID(int iSelectedAcq,	char* szAID, int SuppIssList[], int& iSuppIssCnt);

/***************************************************************************
* Implementations
**************************************************************************/

int AgnosReadMSRTrackData(TRANSACTION_OBJECT1* pobTran)
{
    cAMPAgnos* pAgnos = cAMPAgnos::get_Instance();
    int iRetVal = AMP_ERROR;

#ifdef ENCRYPT_SENSITIVE_DATA
	CARD_TRACK_DATA *pCardData = pAgnos->GetCardTrackData(CARD_ENTRY_SWIPE);
	if(pCardData != NULL)
	{
		memcpy(pobTran->szTrack1, pCardData->Track1Masked, strlen(pCardData->Track1Masked));
		memcpy(pobTran->szTrack2, pCardData->Track2Masked, strlen(pCardData->Track2Masked));
		memcpy(pobTran->szTrack1Enc, pCardData->Track1Encrypt, strlen(pCardData->Track1Encrypt));
		memcpy(pobTran->szTrack2Enc, pCardData->Track2Encrypt, strlen(pCardData->Track2Encrypt));

		//Check if track 2 data is present
		if (strlen((char*)pobTran->szTrack2) != 0) {
			PutMSRTrackDataToTransObj(pobTran);
			iRetVal = AMP_SUCCESS;
		}
		else
			iRetVal = AMP_ERROR;
	}
#else
    unsigned char Track1[MAX_TRACK_DATA_SIZE] = {0};
    unsigned char Track2[MAX_TRACK_DATA_SIZE] = {0};
    unsigned char Track3[MAX_TRACK_DATA_SIZE] = {0};
    int nSizeTrack1 = 0, nSizeTrack2 = 0, nSizeTrack3 = 0;

    iRetVal = pAgnos->ReadMagstripe(Track1, &nSizeTrack1,
                                    Track2, &nSizeTrack2,
                                    Track3, &nSizeTrack3);

    // Read MSR Buffer
    if(iRetVal == AMP_SUCCESS)
    {
        if(nSizeTrack1 > 0)
            memcpy(pobTran->szTrack1, Track1, nSizeTrack1);

        if(nSizeTrack2 > 0)
            memcpy(pobTran->szTrack2, Track2, nSizeTrack2);

        if(nSizeTrack3 > 0)
            memcpy(pobTran->szTrack3, Track3, nSizeTrack3);

        //Check if track 2 data is present
        if (nSizeTrack2 != 0) {
            PutMSRTrackDataToTransObj(pobTran);
            iRetVal = AMP_SUCCESS;
        }
        else
            iRetVal = AMP_ERROR;
    }
#endif

	return iRetVal;
}

int ClearMSRTrackData(TRANSACTION_OBJECT1* pobTran)
{
	memset(pobTran->szTrack1, NULL, sizeof(pobTran->szTrack1));
	memset(pobTran->szTrack2, NULL, sizeof(pobTran->szTrack2));
	memset(pobTran->szTrack3, NULL, sizeof(pobTran->szTrack3));

	memset(pobTran->szTrack1Enc, NULL, sizeof(pobTran->szTrack1Enc));
	memset(pobTran->szTrack2Enc, NULL, sizeof(pobTran->szTrack2Enc));

	memset(pobTran->szPAN, NULL, sizeof(pobTran->szPAN));
	memset(pobTran->szExpiry, NULL, sizeof(pobTran->szExpiry));
	memset(pobTran->szSvcCode, NULL, sizeof(pobTran->szSvcCode));
	memset(pobTran->szCardHolderName, NULL, sizeof(pobTran->szCardHolderName));

	return AMP_SUCCESS;
}

void PutMSRTrackDataToTransObj(TRANSACTION_OBJECT1* pobTran)
{
	DEBUG_INFO("ENTER PutMSRTrackDataToTransObj");
	char*pDelimiter = NULL, *pDelimiter2 = NULL;	
	char szPAN[MAX_PAN_SIZE+16]	= { 0 };	
	char szExpiry[SZ_EXPIRY_DATE+1] = { 0 };	
	char szCardHolderName[SZ_CARDHOLDER_NAME+1] = { 0 };	
	char TrackData[MAX_TRACK_SZ];
	char szSvcCode[SZ_SVC_CODE+1] = { 0 };

	//2 Extract PAN and EXPIRY from TRACK 2
	memset(TrackData, 0, sizeof(TrackData));
    memcpy(TrackData, pobTran->szTrack2, sizeof(TrackData));
	if((TrackData != NULL)&& ((pDelimiter = strchr(TrackData, '=')) != NULL)) {
        
		memcpy(szPAN, TrackData, pDelimiter-TrackData);
		memcpy(szExpiry, pDelimiter+1, SZ_EXPIRY_DATE);
		memcpy(szSvcCode, pDelimiter+5, SZ_SVC_CODE);

		memcpy(pobTran->szPAN, szPAN, strlen(szPAN));
		memcpy(pobTran->szExpiry, szExpiry, strlen(szExpiry));
		memcpy(pobTran->szSvcCode, szSvcCode, strlen(szSvcCode));
	}

	//2 Extract CardHolder Name From TRACK1
	memset(TrackData, 0, sizeof(TrackData));
	if((pobTran->szTrack2 != NULL) && ((pDelimiter = strchr(TrackData, '^')) != NULL) &&
		((pDelimiter2 = strchr(pDelimiter+1, '^')) != NULL)) {
		memcpy(szCardHolderName, pDelimiter+1, pDelimiter2 - (pDelimiter+1));
		memcpy(pobTran->szCardHolderName, szCardHolderName, strlen(szCardHolderName));

		memcpy(szSvcCode, pDelimiter2+5, SZ_SVC_CODE);
		memcpy(pobTran->szSvcCode, szSvcCode, strlen(szSvcCode));
	}

	DEBUG_INFO("EXIT PutMSRTrackDataToTransObj");
}

int LUHNCheck(const char* PAN)
{
	const int m[] = {0,2,4,6,8,1,3,5,7,9}; // mapping for rule
	int i, odd = 1, sum = 0;

	if(PAN)
	{
		for (i = strlen(PAN); i--; odd = !odd)
		{
			int digit = PAN[i] - '0';
			sum += odd ? digit : m[digit];
		}
	 
		return ((sum % 10 == 0) ? AMP_SUCCESS : AMP_ERROR);
	}

	return AMP_ERROR;
}

int VerifyMOD10CheckDigit(const char* szPAN)
{
	int iRetVal = AMP_ERROR;
	int iAcctLen, iCtr;
	BYTE Chksum, tmp;

	if(!szPAN)
		return iRetVal;

	iAcctLen = strlen(szPAN);

	for(Chksum = 0, iCtr = ( iAcctLen - 2 ); iCtr >= 0; iCtr -= 2)
	{
		tmp = ( szPAN[iCtr] - '0' ) * 2;
		if ( tmp >= 10 )
			Chksum += ( tmp % 10 ) + 1;
		else
			Chksum += tmp;

		if ( ( iCtr - 1 ) < 0 )
			break;
		else
			Chksum += ( szPAN[iCtr - 1] - '0' );
	}

	if ( Chksum % 10 )
		Chksum = ( ( Chksum / 10 ) + 1 ) * 10 - Chksum;
	else
		Chksum = 0;

	if ( ( szPAN[iAcctLen - 1] - '0' ) == Chksum )
		iRetVal = AMP_SUCCESS;

	return iRetVal;
}

int PANCompare(const char* pan1, const char* pan2)
{
	uint32_t i;

	for( i=0; i<MAX_PAN_SIZE; ++i )
	{
		if( pan1[i] < '0' || pan1[i] > '9' || pan2[i] < '0' || pan2[i] > '9' )
			return 0;
		if( pan1[i] < pan2[i] )
			return -1;
		if( pan1[i] > pan2[i] )
			return 1;
	}

	return 0;
}

BOOL IsCardSwipedICC(TRANSACTION_OBJECT1 *pobTran)
{
	BOOL bICC = FALSE;
	char szSvcCode[SZ_SVC_CODE+1] = { 0 };

	memcpy(szSvcCode, pobTran->szSvcCode, sizeof(szSvcCode));
	if( (szSvcCode[0] == '2') || (szSvcCode[0] == '6') )
		bICC = TRUE;
		
	return bICC;
}

BOOL bIsCardTypeLabelMatch(const char* szCardType, int iCardType)
{
	if(
		((strcasecmp(szCardType, LABEL_ADMIN_CARD) 		== 0) && (iCardType == ADMIN_CARD)) 	||
		((strcasecmp(szCardType, LABEL_CREDIT_CARD)		== 0) && (iCardType == CREDIT_CARD)) 	||
		((strcasecmp(szCardType, LABEL_DEBIT_CARD) 		== 0) && (iCardType == DEBIT_CARD)) 	||
		((strcasecmp(szCardType, LABEL_NON_CARD) 		== 0) && (iCardType == NON_CARD))		||
		((strcasecmp(szCardType, LABEL_LOYALTY_CARD) 	== 0) && (iCardType == LOYALTY_CARD))	||
		((strcasecmp(szCardType, LABEL_LOYCREDIT_CARD) 	== 0) && (iCardType == LOYCREDIT_CARD))	||
		((strcasecmp(szCardType, LABEL_EBT_CARD) 		== 0) && (iCardType == EBT_CARD))		||
		((strcasecmp(szCardType, LABEL_PURCHASE_CARD) 	== 0) && (iCardType == PURCHASE_CARD))	||
		((strcasecmp(szCardType, LABEL_COMMERCIAL_CARD) == 0) && (iCardType == COMMERCIAL_CARD))||
		((strcasecmp(szCardType, LABEL_FLEET_CARD) 		== 0) && (iCardType == FLEET_CARD))		||
		((strcasecmp(szCardType, LABEL_GIFT_CARD) 		== 0) && (iCardType == GIFT_CARD))		||
		((strcasecmp(szCardType, LABEL_BUSINESS_CARD) 	== 0) && (iCardType == BUSINESS_CARD))	||
		((strcasecmp(szCardType, LABEL_CORPORATE_CARD) 	== 0) && (iCardType == CORPORATE_CARD))	
	)
		return TRUE;
	return FALSE;
}

