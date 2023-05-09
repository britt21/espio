
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
* File       	 : 		CoreInvoiceNumEntry.cpp
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		10/17/2015
**************************************************************************/

/***************************************************************************
 * Includes
 **************************************************************************/


// AMP Library
#include "AMPReturnCodes.h"

// Core Project Includes
#include "CoreFlow.h"
#include "CoreScreens.h"
#include "CoreConfig.h"

// Project Header
#include "Project.h"
#include "Screens.h"

// AMP Library
#include <AMPBaseConsole.h>
#include <AMPAgnos.h>
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
int DoAddressEntry(TRANSACTION_OBJECT1* pobTran);
int DoZIPCodeEntry(TRANSACTION_OBJECT1* pobTran);
int DoCVVConfirmation(TRANSACTION_OBJECT1* pobTran);

/***************************************************************************
* Implementations
**************************************************************************/
int DoCardPresentEntry(TRANSACTION_OBJECT1* pobTran)
{
	int iRetVal = AMP_SUCCESS;
	int iCardEntryMethod = pobTran->iCardEntryMethod;

	if (iCardEntryMethod == CARD_MANUAL) {

		iRetVal = PromptCardPresent(NULL, "Card Present?", NULL);
		switch(iRetVal)
		{
			case CARD_PRESENT_NO:
				iRetVal = AMP_SUCCESS;
				break;
			case CARD_PRESENT_YES:
				iRetVal = DoCardImprintPrompt(pobTran);
				break;
		}
	}

	return iRetVal;
}

int DoCardImprintPrompt(TRANSACTION_OBJECT1* pobTran)
{
	int iRetVal = AMP_SUCCESS;
	int iCardEntryMethod = pobTran->iCardEntryMethod;

	if (iCardEntryMethod == CARD_MANUAL) {

		// Get Header string
		iRetVal = PromptCardImprint(NULL, "Imprint Card", "Please press Enter to confirm.");
	}

	return iRetVal;
}

int DoAVSDataEntry(TRANSACTION_OBJECT1* pobTran)
{
	int iRetVal = AMP_SUCCESS;
	int iCardEntryMethod = pobTran->iCardEntryMethod;

	if (iCardEntryMethod == CARD_MANUAL) {

		// Check if AVS Mail Address Entry is Enabled
		iRetVal = DoAddressEntry(pobTran);

		// Check if ZIP Code Entry is Enabled
		iRetVal = DoZIPCodeEntry(pobTran);
	}
	return iRetVal;	
}

int DoAddressEntry(TRANSACTION_OBJECT1* pobTran)
{
	int iRetVal = AMP_SUCCESS;
	char szAddress[MAX_STR_SZ+1] = { 0 };
	int iTimeOut = DEFAULT_INPUT_TIMEOUT;

	// Prompt Address
	iRetVal = PromptAddressEntry(NULL, "Enter Address", NULL, iTimeOut, szAddress);

	// Set pobTran Data
	if(iRetVal == AMP_SUCCESS)
		memcpy(pobTran->szAddress, szAddress, strlen(szAddress));

	return iRetVal;
}

int DoZIPCodeEntry(TRANSACTION_OBJECT1* pobTran)
{
	int iRetVal = AMP_SUCCESS;
	char szZIPCode[MAX_STR_SZ+1] = { 0 };
	int iTimeOut = DEFAULT_INPUT_TIMEOUT;

	// Prompt ZIP Code
	iRetVal = PromptZIPCodeEntry(NULL, "Enter ZIP Code", NULL, iTimeOut, szZIPCode);

	// Set pobTran Data
	if(iRetVal == AMP_SUCCESS)
		memcpy(pobTran->szZipCode, szZIPCode, strlen(szZIPCode));

	return iRetVal;
}

int DoCVV2Entry(TRANSACTION_OBJECT1* pobTran)
{
	int iRetVal  = AMP_SUCCESS;
	int iTimeOut = DEFAULT_INPUT_TIMEOUT;
	int iCardEntryMethod = pobTran->iCardEntryMethod;
	char szCVV2  [MAX_STR_SZ+1] = { 0 };
	int iMax = SZ_CVV2-1;

	if(iCardEntryMethod == CARD_MANUAL) {

		// Prompt CVV2
		iRetVal = PromptCVV2Entry(NULL, "Enter V-Code", NULL, iMax, iTimeOut, szCVV2);

		if(strlen(szCVV2) == 0)
			iRetVal = DoCVVConfirmation(pobTran);
		else if(iRetVal == AMP_SUCCESS)
			memcpy(pobTran->szCVV2, szCVV2, strlen(szCVV2));
		
	}
	return iRetVal;	
}

int DoCVVConfirmation(TRANSACTION_OBJECT1* pobTran)
{
	int iRetVal = AMP_ERROR;
	int iTimeOut = DEFAULT_INPUT_TIMEOUT;

	iRetVal = PromptSelection(NULL, "V-Code Present?", NULL, 2, "No", "Xread", NULL, iTimeOut);
	switch(iRetVal)
	{
		case AMPKEY_MENU1:
		case AMPKEY_ENTER:
		case AMPKEY_MENU2:
		case AMP_TIMEOUT:
		case AMPKEY_CANCEL:
			iRetVal = AMP_SUCCESS;
			break;
	}
    return iRetVal;
}