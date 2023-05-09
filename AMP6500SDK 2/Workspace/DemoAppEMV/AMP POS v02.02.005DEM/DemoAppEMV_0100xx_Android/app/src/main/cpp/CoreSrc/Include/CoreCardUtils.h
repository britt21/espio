
#ifndef CARDUTILS_H_
#define CARDUTILS_H_


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
* File       	 : 		CoreCardUtils.h
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		09/07/2015
**************************************************************************/

#include "CoreDefines.h"
#include "CoreTransObj.h"


/*
*	Methods to Open/Close Card readers
*		use options to specify device reader e.g. CARD_ALL
*/
void OpenCardReaders(int Option);
void CloseCardReaders(int Option);

//! Parses MSR Track Data and put them to TransOBJ
void PutMSRTrackDataToTransObj(TRANSACTION_OBJECT1* pobTran);

//! Reads the Track1/2/3 of Magstripe through Agnos library
int AgnosReadMSRTrackData(TRANSACTION_OBJECT1* pobTran);

//! Clears the MSR Track Data from pobTran
int ClearMSRTrackData(TRANSACTION_OBJECT1* pobTran);

//! Checks if the PAN's Luhn is correct
int LUHNCheck(const char* PAN);

//! Checks if the MOD10 is correct
int VerifyMOD10CheckDigit(const char* szPAN);

//! Returns TRUE if the swiped card is ICC
BOOL IsCardSwipedICC(TRANSACTION_OBJECT1 *pobTran);

//! Check is the Card Type and Label Provided matches
BOOL bIsCardTypeLabelMatch(const char* szCardType, int iCardType);

//! Return PIN Bypass Y/N
BOOL GetPinByPassOnAID(const char* szAID);

//! Returns Card Type Based on AID
int GetCardTypeOnAID(const char* szAID);

//! Check if AID is supported in Internal.cfg
BOOL IsAIDSupported(const char* szAID);

//! Returns No CVM Limit Based on AID
unsigned long GetNoCVMLimitOnAID(const char* szAID);

//! Returns CVM Limit Based on AID
unsigned long GetCVMLimitOnAID(const char* szAID);


#endif /* CARDUTILS_H_ */

