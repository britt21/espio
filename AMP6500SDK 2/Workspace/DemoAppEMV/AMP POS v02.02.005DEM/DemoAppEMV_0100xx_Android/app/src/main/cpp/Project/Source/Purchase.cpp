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
* File       	 	: 		Purchase.cpp
* Application 	 	: 		AMP-Base Application
* Date Coded 		: 		09/12/2015
**************************************************************************/

/***************************************************************************
 * Includes
 **************************************************************************/
// AMP Library
#include <AMPUtils.h>

// Core Project Includes
#include "CoreTransObj.h"
#include "CoreScreens.h"
#include "CoreFlow.h"
#include "CoreAgnosEmvFunc.h"
#include "CoreAgnosEmvCtlsFunc.h"

// Project Includes
#include "Project.h"
#include "TransUtils.h"

// AMP Library
#include <AMPReturnCodes.h>
#include <AmpBaseAndroidIF.h>

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

int Purchase(void)
{
	int iRetVal;

	TRANS_OBJ1->ClearContents();

	iRetVal = DoAmountEntry(TRANS_OBJ1);

	if(iRetVal == AMP_SUCCESS)
		iRetVal = DoCardEntry(TRANS_OBJ1);

	if(iRetVal == AMP_SUCCESS)
		iRetVal = DoCVV2Entry(TRANS_OBJ1);

	if(iRetVal == AMP_SUCCESS)
		iRetVal = DoAVSDataEntry(TRANS_OBJ1);

	if(iRetVal == AMP_SUCCESS)
		iRetVal = DoAgnosEmvCompletion(TRANS_OBJ1);

	if(iRetVal == AMP_SUCCESS)
		iRetVal = DoAgnosEmvCtlsCompletion(TRANS_OBJ1);

	PerformDisplayOperation("Card Details", (char*)TRANS_OBJ1->szTrack1, (char*)TRANS_OBJ1->szTrack2, (char*)TRANS_OBJ1->szPAN, NULL, BEEP_INFO, INFO_TIMEOUT*3);

	return RETURN_LAST_MENU;
}


