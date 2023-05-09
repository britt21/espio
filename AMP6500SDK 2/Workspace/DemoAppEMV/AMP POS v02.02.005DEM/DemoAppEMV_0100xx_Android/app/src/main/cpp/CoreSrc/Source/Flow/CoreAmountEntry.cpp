
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
* File       	 : 		CoreAmountEntry.cpp
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		09/08/2015
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

// Core Project Includes
#include "CoreFlow.h"
#include "CoreScreens.h"
#include "CoreConfig.h"

// Project Header
#include "Screens.h"
#include "Project.h"

#include <AmpBaseAndroidIF.h>
#include <AMPAgnos.h>
#include <TransUtils.h>

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
int DoAmountEntry(TRANSACTION_OBJECT1* pobTran)
{
	int iRetVal = AMP_SUCCESS;
	char szHeader[MAX_HEADER_SIZE+1] = { 0 };
	char szAmount[MAX_STR_SZ+1] = { 0 };
	int iTimeOut = DEFAULT_INPUT_TIMEOUT;

	// Prompt Base Amount
	iRetVal = PromptAmountEntry(NULL, "Enter Amount:", NULL, DEFAULT_AMOUNT_SIZE, 2, iTimeOut, szAmount);

	// Set pobTran Data
	if(iRetVal == AMP_SUCCESS)
		memcpy(pobTran->szBaseAmount, szAmount, strlen(szAmount));

	return iRetVal;	
}