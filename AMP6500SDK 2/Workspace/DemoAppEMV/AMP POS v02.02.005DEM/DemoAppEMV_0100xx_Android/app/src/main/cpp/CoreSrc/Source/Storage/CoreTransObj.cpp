
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
* File       	 : 		TranObj.cpp
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		08/10/2015
**************************************************************************/

/***************************************************************************
 * Includes
 **************************************************************************/

// Standard Library
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>

// AMP Library
#include <AMPUtils.h>
#include <AMPDebug.h>
#include <AMPEmvSizes.h>

// Core Project Includes
#include "CoreTransObj.h"

/***************************************************************************
* Perprocessor Defines
**************************************************************************/

// Logging
#ifdef DEBUG_FLAG
//	#define DEBUG_TRANOBJ
//	#define DEBUG_I_AM_POBTRAN
#endif

/***************************************************************************
* Globals
**************************************************************************/

//cTransObj1* g_TransObj = new cTransObj1();

/***************************************************************************
* Local Functions
**************************************************************************/

/***************************************************************************
* Implementations
**************************************************************************/

cTransObj1::cTransObj1()
{
    ClearContents();
}

cTransObj1::~cTransObj1()
{
}

void cTransObj1::ClearContents()
{
	iCardEntryMethod = -1;

	memset(szBaseAmount, 0, sizeof(szBaseAmount));
	memset(szTrack1, 0, sizeof(szTrack1));
	memset(szTrack2, 0, sizeof(szTrack2));
	memset(szTrack1Enc, 0, sizeof(szTrack1Enc));
	memset(szTrack2Enc, 0, sizeof(szTrack2Enc));
	memset(szTrack3, 0, sizeof(szTrack3));
	memset(szPAN, 0, sizeof(szPAN));
	memset(szExpiry, 0, sizeof(szExpiry));
	memset(szCardHolderName, 0, sizeof(szCardHolderName));
	memset(szSvcCode, 0, sizeof(szSvcCode));
	memset(szAddress, 0, sizeof(szAddress));
	memset(szZipCode, 0, sizeof(szZipCode));
	memset(szCVV2, 0, sizeof(szCVV2));
	memset(szTransTime, 0, sizeof(szTransTime));

// EMV Tags
	unsigned char TAG_9F39_POS_ENTRY_MODE[MAX_STR_SZ];
	unsigned char TAG_9F40_TERM_ADTNAL_CAP[MAX_STR_SZ];
	unsigned char TAG_5F2D_LANG_PREFERENCE[MAX_STR_SZ];
	unsigned char TAG_9F53_TERM_CAT_CODE[MAX_STR_SZ];
	unsigned char TAG_9F6B_TRACK2_DATA[MAX_STR_SZ*2];
	unsigned char TAG_57_TRACK2_EQ_DATA[MAX_STR_SZ*2];
	unsigned char TAG_5A_APPL_PAN[MAX_STR_SZ*2];
	unsigned char TAG_4F_AID[MAX_STR_SZ];
	unsigned char TAG_9F27_CRYPT_INFO_DATA[MAX_STR_SZ];
	unsigned char TAG_9F12_APPL_PRE_NAME[MAX_STR_SZ];
	unsigned char TAG_50_APPL_LABEL[MAX_STR_SZ];
	unsigned char TAG_5F30_SERVICE_CODE[MAX_STR_SZ];
	unsigned char TAG_5F20_CARDHOLDER_NAME[MAX_STR_SZ];
	unsigned char TAG_5F24_EXPIRY_DATE[MAX_STR_SZ];
	unsigned char TAG_9F33_TERM_CAP[MAX_STR_SZ];
	unsigned char TAG_5F34_APPL_PAN_SEQNUM[MAX_STR_SZ];
	unsigned char TAG_5F25_EFFECT_DATE[MAX_STR_SZ];
	unsigned char TAG_5F28_ISSUER_COUNTY_CODE[MAX_STR_SZ];
	unsigned char TAG_9F1A_TERM_COUNTY_CODE[MAX_STR_SZ];
	unsigned char TAG_82_APPL_INTCHG_PROFILE[MAX_STR_SZ];
	unsigned char TAG_9F35_TERM_TYPE[MAX_STR_SZ];
	unsigned char TAG_9F09_TERM_VER_NUM[MAX_STR_SZ];
	unsigned char TAG_84_DF_NAME[MAX_STR_SZ];
	unsigned char TAG_9F1B_TERM_FLOOR_LIMIT[MAX_STR_SZ];
	unsigned char TAG_9B_TSI[MAX_STR_SZ];
	unsigned char TAG_95_TVR[MAX_STR_SZ];
	unsigned char TAG_8E_CVM_LIST[MAX_STR_SZ];
	unsigned char TAG_9F34_CVM_RESULTS[MAX_STR_SZ];
	unsigned char TAG_9F26_APPL_CRYPTOGRAM[MAX_STR_SZ];
	unsigned char TAG_9F36_ATC[MAX_STR_SZ];
	unsigned char TAG_5F2A_TRANS_CURCY_CODE[MAX_STR_SZ];
	unsigned char TAG_9C_TRAN_TYPE[MAX_STR_SZ];
	unsigned char TAG_9F10_ISSUER_APP_DATA[MAX_STR_SZ];
	unsigned char TAG_9F02_AMT_AUTH_NUM[MAX_STR_SZ];
	unsigned char TAG_9F03_AMT_OTHER_NUM[MAX_STR_SZ];
	unsigned char TAG_9F07_APPL_USE_CNTRL[MAX_STR_SZ];
	unsigned char TAG_9F0D_IAC_DEFAULT[MAX_STR_SZ];
	unsigned char TAG_9F0E_IAC_DENIAL[MAX_STR_SZ];
	unsigned char TAG_9F0F_IAC_ONLINE[MAX_STR_SZ];
	unsigned char TAG_9F37_UNPRED_NUM[MAX_STR_SZ];
	unsigned char TAG_9A_TRAN_DATE[MAX_STR_SZ];
	unsigned char TAG_9F21_TRANS_TIME[MAX_STR_SZ];
	unsigned char TAG_9F6E_EC_FORM_FACTOR_IND[MAX_STR_SZ];
	unsigned char TAG_9F70_FLASH_FORM_FACTOR_IND[MAX_STR_SZ];
	unsigned char TAG_9F59_FLASH_TTI[MAX_STR_SZ];
	unsigned char TAG_9F06_APPL_ID[MAX_STR_SZ];
	unsigned char TAG_9F41_TRANS_SEQ_COUNTER[MAX_STR_SZ];
	unsigned char TAG_9F1E_IFD_SER_NUM[MAX_STR_SZ];
	unsigned char TAG_9F24_PAYMENT_ACCNT_REF[MAX_STR_SZ];
}


