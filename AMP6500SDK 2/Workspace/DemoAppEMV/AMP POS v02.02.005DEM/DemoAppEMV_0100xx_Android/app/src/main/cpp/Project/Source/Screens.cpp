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
* File       	 	: 		Screen.cpp
* Application 	 	: 		AMP-Base Application
* Date Coded 		: 		08/20/2015
**************************************************************************/

/***************************************************************************
 * Includes
 **************************************************************************/
 
// Standard Library
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <CoreConfig.h>

// AMP Library
#include <AMPAgnos.h>
#include <AMPReturnCodes.h>
#include <AMPBaseConsole.h>

// Core Project Header
#include "CoreScreens.h"
#include "CoreTransObj.h"
#include "CoreFlow.h"

// Project Header
#include "Project.h"
#include "Screens.h"
#include "TransUtils.h"
#include "AmpBaseAndroidIF.h"

/***************************************************************************
* Perprocessor Defines
**************************************************************************/

/***************************************************************************
* Globals
**************************************************************************/

/***************************************************************************
* Local Functions
**************************************************************************/

/***************************************************************************
* Implementations
**************************************************************************/

int PromptAmountEntry(const char *szHeader, const char *szLine1, const char *szLine2, int iMaxDigits, int iMinDigits, int iTimeout, char *szOutput)
{
	int iRetVal;
	char szCurrSymbol[MAX_STR_SZ+1] = { 0 };

	strcpy(szCurrSymbol, DEFAULT_CURRENCY_SYMBOL);

	iRetVal = PromptEntry(szHeader, szLine1, szLine2, iMaxDigits, iMinDigits, (char*)AMOUNT_FORMAT_NO_CURRENCY, NULL, szCurrSymbol, INP_METH_AMOUNT, ALIGN_RIGHT, szOutput, 0, iTimeout);

	return(iRetVal);
}

int PromptChoiceSelection(char* szTitle, char Choices[][MAX_STR_SZ+1], int NumChoices, int DefaultSelection, ALIGNMENT Align)
{
    return PerformChoiceSelectionOperation(szTitle, Choices, NumChoices, DefaultSelection);
}

int PromptCardPresent(const char *szHeader, const char *szPrompt1, const char *szPrompt2)
{
	int iRetVal = AMP_ERROR;
	int iTimeOut = DEFAULT_INPUT_TIMEOUT;

	iRetVal = PromptSelection(szHeader, szPrompt1, szPrompt2, 2, "NO", "YES", NULL, iTimeOut);
	switch(iRetVal)
	{
		case AMPKEY_MENU1:
		case AMPKEY_1:
			iRetVal = CARD_PRESENT_NO;
			break;
		case AMPKEY_ENTER:
		case AMPKEY_MENU2:
			iRetVal = CARD_PRESENT_YES;
			break;
		case AMP_TIMEOUT:
		case AMPKEY_CANCEL:
			iRetVal = AMP_CANCEL;
			break;
	}

	return iRetVal;
}

int PromptCardImprint(const char *szHeader, const char *szPrompt1, const char *szPrompt2)
{
	int iRetVal = AMP_ERROR;
	int iTimeOut = 0;	//4 Timeout is Disabled!

    int Key = 0;
    Key = PromptSelection(szHeader, szPrompt1, szPrompt2, 2, "Enter", "Cancel", NULL, iTimeOut);
    switch(Key)
    {
        case AMP_TIMEOUT:
            iRetVal = AMP_TIMEOUT;
            break;
        case AMPKEY_CANCEL:
        case AMPKEY_MENU2:
            iRetVal = AMP_CANCEL;
            break;
        case AMPKEY_MENU1:
            iRetVal = AMP_SUCCESS;
            break;
        default:
            break;
    }
    return iRetVal;
}

int PromptAddressEntry(const char *szHeader, const char *szLine1, const char *szLine2, int iTimeout, char *szOutput)
{
	return PromptEntry(szHeader, szLine1, szLine2, 20, 0, NULL, NULL, NULL, INP_METH_ALL_KEYS, ALIGN_CENTER, szOutput, 0, iTimeout);
}

int PromptZIPCodeEntry(const char *szHeader, const char *szLine1, const char *szLine2, int iTimeout, char *szOutput)
{
	return PromptEntry(szHeader, szLine1, szLine2, 6, 0, NULL, NULL, NULL, INP_METH_NUM_ONLY, ALIGN_CENTER, szOutput, 0, iTimeout);
}

int PromptCVV2Entry(const char *szHeader, const char *szLine1, const char *szLine2, int iMax, int iTimeout, char *szOutput)
{
	return PromptEntry(szHeader, szLine1, szLine2, iMax, 0, NULL, '*', NULL, INP_METH_NUM_ONLY | INP_METH_PASSWORD, ALIGN_CENTER, szOutput, 0, iTimeout);
}

int PromptAVSOverride(const char *szHeader, const char *szPrompt1, const char *szPrompt2)
{
	int iRetVal = AMP_ERROR;
	int iTimeOut = DEFAULT_INPUT_TIMEOUT;

	iRetVal = PromptSelection(szHeader, szPrompt1, szPrompt2, 2, "NO", "YES", NULL, iTimeOut);
	switch(iRetVal)
	{
		case AMPKEY_MENU1:
		case AMP_TIMEOUT:
			iRetVal = AVS_OVERRIDE_NO;
			break;
		case AMPKEY_ENTER:
		case AMPKEY_MENU2:
			iRetVal = AVS_OVERRIDE_YES;
			break;
	}

	return iRetVal;
}

int PromptGenericNumEntry(const char *szHeader, const char *szLine1, const char *szLine2, int iMax, int iMin, int iTimeout, char *szOutput)
{
	return PromptEntry(szHeader, szLine1, szLine2, iMax, iMin, NULL, NULL, NULL, INP_METH_NUM_ONLY, ALIGN_CENTER, szOutput, 0, iTimeout);
}