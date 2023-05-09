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
* File       	: 		Screens.h
* Application 	: 		AMP-Base Application
* Date Coded	: 		08/20/2015
**************************************************************************/

#ifndef PROJECT_INCLUDE_SCREEN_H_
#define PROJECT_INCLUDE_SCREEN_H_

// AMP Library
#include "AMPEMVSizes.h"
#include "AMPUIDisplay.h"

#include "AMPDefine.h"
#include "CoreDefines.h"
#include "CoreTransObj.h"
#include "Transactions.h"

//! Prompts language selection screen.  Displays all of the supported languages in the terminal
int PromptLanguageSelection(char* OutBuff_LangName);

//! Prompts the EMV Application selection screen.  Application/s to be displayed/selected should be supplied in AppLabels parameter.
int PromptApplicationSelection(char AppLabels[][APPL_LABEL_SIZE+1], int NumLabels);	

//! Prompts the EMV Application selection confimation.  Application selected should be supplied in AppName parameter.
int PromptApplicationConfirmation(char *AppName);

//! Prompts the Base Amount entry
int PromptAmountEntry(const char *szHeader, const char *szLine1, const char *szLine2, int iMaxDigits, int iMinDigits, int iTimeout, char *szOutput);

//! Generic Choice Screen
int PromptChoiceSelection(char* szTitle, char Choices[][MAX_STR_SZ+1], int NumChoices, int DefaultSelection = 0, ALIGNMENT Align = ALIGN_NONE);

//! Prompts if Card Present or not entry
int PromptCardPresent(const char *szHeader, const char *szPrompt1, const char *szPrompt2);

//! Prompts Card Imprint Screen
int PromptCardImprint(const char *szHeader, const char *szPrompt1, const char *szPrompt2);

//! Prompts the AVS ZIP Code entry
int PromptZIPCodeEntry(const char *szHeader, const char *szLine1, const char *szLine2, int iTimeout, char *szOutput);

//! Prompts the AVS Address entry
int PromptAddressEntry(const char *szHeader, const char *szLine1, const char *szLine2, int iTimeout, char *szOutput);

//! Prompts the CVD/CVV2 entry
int PromptCVV2Entry(const char *szHeader, const char *szLine1, const char *szLine2, int iMax, int iTimeout, char *szOutput);

//! Prompts the Transaction ID for Offline entry
int PromptTransactionIDEntry(const char *szHeader, const char *szLine1, const char *szLine2, int iTimeout, char *szOutput);

//! Prompts AVS Override
int PromptAVSOverride(const char *szHeader, const char *szPrompt1, const char *szPrompt2);

//! Select Transaction to Re-Enter
int PromptSelectTransToReEnter(const char *szHeader, CARD_TYPE CardType, TRANS_TYPE *OutTransType);

//! Selection of Card Type
int PromptCardTypeSelection(char CardTypeLabels[][MAX_STR_SZ+1], int NumItems, char* OutTxtSelection);

//! Generic Numeric Entry
int PromptGenericNumEntry(const char *szHeader, const char *szLine1, const char *szLine2, int iMax, int iMin, int iTimeout, char *szOutput);


#endif /* PROJECT_INCLUDE_SCREEN_H_ */
