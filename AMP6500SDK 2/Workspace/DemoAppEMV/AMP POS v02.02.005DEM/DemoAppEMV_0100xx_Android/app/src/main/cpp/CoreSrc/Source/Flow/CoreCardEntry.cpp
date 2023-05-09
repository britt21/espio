

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
* File       	 : 		CoreCardEntry.cpp
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
#include <AMPAgnosEmvCtls.h>
#include "AMPPosEntry.h"

// Core Project Includes
#include "CoreFlow.h"
#include "CoreCardUtils.h"
#include "CoreScreens.h"
#include "CoreConfig.h"

// Project Includes
#include "Project.h"
#include "SizeDefines.h"
#include "TransUtils.h"
#include "CoreAgnosEmvCtlsFunc.h"
#include "CoreAgnosEmvFunc.h"

#include <AmpBaseAndroidIF.h>
#include <AMPUIDisplay.h>

/***************************************************************************
* Perprocessor Defines
**************************************************************************/
// Default No. of Card Entry Retry
#define CARD_RETRIES	4

/***************************************************************************
* Globals
**************************************************************************/

/***************************************************************************
* Local Functions
**************************************************************************/

/***************************************************************************
* Implementations
**************************************************************************/

int DoCardEntry(TRANSACTION_OBJECT1* pobTran)
{
	int  iSupprtdEntry 	= DEVCARD_ALL;
	int  iCardEntryMethod = CARD_NONE;
	int  iCardRetry 	= CARD_RETRIES;
	int  iRetVal 		= AMP_ERROR;
	BOOL bOnFallback	= FALSE;
	BOOL bDoRetry		= TRUE;
	long msTimeout 		= 30;
	char szPAN[MAX_PAN_SIZE+1]	= { 0 };
	char szExpiry[SZ_EXPIRY_DATE+1] = { 0 };
    char szExpiryLabel[SZ_EXPIRY_DATE+10]={0};
    char szPANLabel[MAX_PAN_SIZE+10]={0};
	USHORT ucReadKey = 0;

	//1 Initialize Agnos Transaction
	cAMPAgnos *pAgnos = cAMPAgnos::get_Instance();

    pAgnos->InitTrans(AGN_PURCHASE);
	pAgnos->SetSupprtdCardEntry(iSupprtdEntry);
	
	// Get Header string
    DisplayPassTerminalToCustomer(NULL, "Turn unit towards the Customer", NULL);

    while(1) {

        while ((iCardRetry) && (bDoRetry == TRUE)) {

            iCardRetry--;

            //2 Display Prompt if Card is not yet Entered
            if(iCardEntryMethod == CARD_NONE) {
                if ((iSupprtdEntry & (DEVCARD_MSR | DEVCARD_CTLS | DEVCARD_ICC)) == (DEVCARD_MSR | DEVCARD_CTLS | DEVCARD_ICC))
                    DisplayCardEntryPrompt(NULL, "Insert / Swipe / Tap Card", "Inserer / Glisser / Tap Carte", TRUE);
            }

            //2 Wait for Card Entry if not yet done
            if(iCardEntryMethod == CARD_MANUAL)
                iRetVal = CARD_MANUAL;
            else
                iRetVal = pAgnos->CardEntryPolling((msTimeout), &ucReadKey);

           if(iRetVal == AMP_CANCEL || iRetVal == AMP_TIMEOUT || iRetVal == AMP_ERROR)
               break;
            else
                iCardEntryMethod = iRetVal;

            //2 On Swipe
            if(iCardEntryMethod == CARD_SWIPE) {

                if((iRetVal = AgnosReadMSRTrackData(pobTran)) == AMP_SUCCESS) {

                    // Check Card Expiry
                    memcpy(szExpiry, pobTran->szExpiry, sizeof(szExpiry));
                    memmove(szExpiry+2, szExpiry, 4);
                    memcpy(szExpiry, szExpiry+4, 2);
                    szExpiry[4] = 0;

                    if(bIsExpired(szExpiry) == TRUE) {
                        // Return to Main Menu
                        //iRetVal = AMP_CANCEL;
                        break;
                    }

                    if(!bOnFallback && IsCardSwipedICC(pobTran)) {

                        PromptDisplay(NULL, "Please use chip reader", NULL, NULL, NULL, BEEP_WARN, WARN_TIMEOUT);
                        PromptDisplay(NULL, "Please insert card", NULL, NULL, NULL, BEEP_WARN, WARN_TIMEOUT);

                        if(iCardRetry == 1) {

                            iRetVal = AMP_ERROR;
                            break;
                        }

                    }
                    else if(bOnFallback) {

                        iCardEntryMethod = CARD_SWIPE;
                        break;
                    }
                    else {
                        sprintf(szPANLabel, "PAN: %s", pobTran->szPAN);
                        sprintf(szExpiryLabel, "Expiry Date: %s", szExpiry);
                        //DisplayPassTerminalToCustomer("Card Details", szPANLabel, szExpiryLabel, TRUE);
                        //PerformDisplayOperation("Card Details", "", szPANLabel, szExpiryLabel, "", BEEP_INFO, INFO_TIMEOUT);
                        iCardEntryMethod = CARD_SWIPE;
                        break;
                    }

                }
                else {

                    PromptDisplay(NULL, "Card Read Error", NULL, NULL, NULL, BEEP_ERROR, ERROR_TIMEOUT);
                    if(iCardRetry == 1)
                        break;
                }
            }

            //2 On Insert
            else if(iCardEntryMethod == CARD_INSERT) {

                iRetVal = DoAgnosEmvInitiateFlow(pobTran); //returns outcome

                //Fallback to magstripe
                if(iRetVal == ocTRY_ANOTHER_INTERFACE) {

                    PromptDisplay(NULL, "Chip Cannot Be Read", NULL, NULL, NULL, BEEP_WARN, WARN_TIMEOUT);

                    // Prompt for Chip prompt entry for 3 times before fallback to magstripe
                    if(iCardRetry == 1) {

                        PromptDisplay(NULL, "Use Mag Stripe", NULL, NULL, NULL, BEEP_WARN, WARN_TIMEOUT);
                        bOnFallback = TRUE;

                        //3 Set Card Entry to Mag Stripe Only
                        iSupprtdEntry = DEVCARD_MSR;
                        pAgnos->SetSupprtdCardEntry(iSupprtdEntry);
                        iCardEntryMethod = CARD_NONE;
                        break;
                    }
                }
                else if(iRetVal == AMP_CANCEL) {

                    iCardEntryMethod = CARD_NONE;
                    break;
                }
                else {

                    iCardEntryMethod = CARD_INSERT;
                    break;
                }
            }

            //2 On Tap
            else if(iCardEntryMethod == CARD_TAP) {

                iRetVal = DoAgnosEmvCtlsInitiateFlow(pobTran); //returns outcome

                if(iRetVal == ocNOT_EMV_CARD_POOLED){

                    iCardEntryMethod = CARD_TAP;
                    break;
                }
                else if(iRetVal == ocTRY_ANOTHER_INTERFACE) {

                    bOnFallback = TRUE;

                    //3 Set Card Entry to Insert or Swipe?
                    iSupprtdEntry = DEVCARD_MSR | DEVCARD_ICC;
                    pAgnos->SetSupprtdCardEntry(iSupprtdEntry);
                    iCardEntryMethod = CARD_NONE;
                }
                // No need to retry if Cancelled
                else if(iRetVal == AMP_CANCEL) {

                    iCardEntryMethod = CARD_NONE;
                    break;
                }
                else{

                    iCardEntryMethod = CARD_TAP;
                    break;
                }
            }

            //2 On Key Pressed
            else if(iCardEntryMethod == CARD_MANUAL) {

                pAgnos->CloseGpiDeviceReader(DEVICE_CARD_CONTACTLESS);

                if((iSupprtdEntry & DEVCARD_MANUAL) == 0) {

                    PromptDisplay(NULL, "Manual entry not allowed", NULL, NULL, NULL, BEEP_ERROR, ERROR_TIMEOUT);
                }
                else if(ucReadKey == AMPKEY_CANCEL) {

                    iRetVal = AMP_CANCEL;
                    break;
                }
                else {
                    if( (ucReadKey >= AMPKEY_0) && (ucReadKey <= AMPKEY_9) ) {

                        sprintf(szPAN, "%c", ucReadKey);
                        memcpy(pobTran->szPAN, szPAN, strlen(szPAN));
                    }
                    if((iRetVal = DoManualEntry(pobTran)) == AMP_SUCCESS) {

                        iCardEntryMethod = CARD_MANUAL;
                        break;
                    }
                    else if(iRetVal == AMP_CANCEL) {

                        iCardEntryMethod = CARD_NONE;
                        break;
                    }

                    // We are showing manual entry only, means user really wants to cancel and not do other entry methods
                    else if(iSupprtdEntry == DEVCARD_MANUAL)
                        break;
                }
            }

            // Reset Card Entry Method
            iCardEntryMethod = CARD_NONE;

            if( bDoRetry == TRUE ) {
                pAgnos->CloseGpiDeviceReader(DEVICE_CARD_ALL);

                if (!bOnFallback && IsCardSwipedICC(pobTran))
                    ClearMSRTrackData(pobTran);
                else
                    PromptDisplay(NULL, "TRY AGAIN", NULL, NULL, NULL, BEEP_WARN, 1000);

            }
        }// end while card entry

        //2 If User Cancelled or if Timed out, exit loop
        if( (iRetVal == AMP_CANCEL) || (iRetVal == AMP_TIMEOUT) || (iRetVal == AMP_ERROR) ) {

            pAgnos->CloseGpiDeviceReader(DEVICE_CARD_ALL);
            ClearMSRTrackData(pobTran);
            PromptDisplay(NULL, "Cancelled", NULL, NULL, NULL, BEEP_WARN, ERROR_TIMEOUT);
            break;
        }

        //1 EMV and CTLS Process
        if(iCardEntryMethod==CARD_TAP || iCardEntryMethod==CARD_INSERT) {

            pobTran->iCardEntryMethod = iCardEntryMethod;
            if( iRetVal != AMP_ERROR)
                iRetVal = AMP_SUCCESS;
        }

        //2 If All Verification is successful, or if Retry ran out, exit loop
        if( (iRetVal == AMP_SUCCESS) || (!iCardRetry ) ) {

            pAgnos->CloseGpiDeviceReader(DEVICE_CARD_CONTACTLESS);
            break;
        }
        else {

            //2 Reset card entry method
            iCardEntryMethod = CARD_NONE;
            pobTran->iCardEntryMethod = iCardEntryMethod;

            //2 Reset MSR Track Data
            ClearMSRTrackData(pobTran);
            iCardEntryMethod = CARD_NONE;
	    }
    }

	//2 Close Card Reader (for ICC Card slot if not yet close)
	if(iRetVal != AMP_SUCCESS) {

		pAgnos->CloseGpiDeviceReader(DEVICE_CARD_ALL);
	}
	return iRetVal;
}

int DoManualEntry(TRANSACTION_OBJECT1* pobTran)
{
	char szHeader[MAX_HEADER_SIZE+1]	= { 0 };
	char szPAN[MAX_PAN_SIZE+1]	= { 0 };	
	int iTimeout = DEFAULT_INPUT_TIMEOUT;
	int iRetVal = AMP_SUCCESS;


	//2 Prompt for PAN
	iRetVal = PromptEntry(NULL, "Enter Card Number", NULL, MAX_PAN_SIZE, MIN_PAN_SIZE,
						NULL /* FieldFormat */, NULL /* Mask */, NULL /* CurrSymbol */,
						INP_METH_CARD_NUMBER /* InpMethod */, ALIGN_RIGHT /* InpAlign */, 
						szPAN, 0, iTimeout);

	//2 Update Card Info to pobTran
	if(iRetVal == AMP_SUCCESS)
        memcpy(pobTran->szPAN, szPAN, strlen(szPAN));

	if(iRetVal == AMP_SUCCESS)
		iRetVal = DoExpDateEntry(pobTran);

	return iRetVal;	
}

int DoExpDateEntry(TRANSACTION_OBJECT1* pobTran)
{
	char szHeader[MAX_HEADER_SIZE+1] = { 0 };
	char szExpiry[SZ_EXPIRY_DATE+1] = { 0 };	
    int iTimeout = DEFAULT_INPUT_TIMEOUT;
	int iRetVal = AMP_SUCCESS;

	//2 Prompt for Card Expiry
	if(iRetVal == AMP_SUCCESS) {

		iRetVal = PromptEntry(NULL, "Enter Expiry Date", NULL, SZ_EXPIRY_DATE, SZ_EXPIRY_DATE,
                    NULL /* FieldFormat */, NULL /* Mask */, NULL /* CurrSymbol */,
                    INP_METH_NUM_ONLY /* InpMethod */, ALIGN_RIGHT /* InpAlign */,
                    szExpiry, 0, iTimeout);
	}

	//2 Check If Expired
	if(iRetVal == AMP_SUCCESS) {
		if(bIsExpired(szExpiry) == TRUE)
			iRetVal = AMP_ERROR;
		else
			iRetVal = AMP_SUCCESS;
	}

	//2 Update Card Info to pobTran
	if(iRetVal == AMP_SUCCESS)
        memcpy(pobTran->szExpiry, szExpiry, strlen(szExpiry));

	return iRetVal;

}

BOOL bIsExpired(const char* szExpiryDate)
{
	BOOL bRetVal = TRUE;
	char szDateTime[15] = { 0 };
	char szCurrDate[5] = { 0 };
	char szTemp1[3] = {0}, szTemp2[3] = {0}, szTemp3[3] = {0};
	char szHeader[MAX_HEADER_SIZE+1]	= { 0 };

	if(szExpiryDate)
	{		
		GetTerminalDateAndTime(szDateTime);
		szDateTime[8] = 0;

		memcpy(szCurrDate, &szDateTime[4], 2);
		memcpy(&szCurrDate[2], &szDateTime[2], 2);

		// Verify Month is valid
		strncpy(szTemp3, &szExpiryDate[0], 2);
		if (atoi(szTemp3) > 12)
		{
			PromptDisplay(NULL, "Invalid Date", NULL, NULL, NULL, BEEP_ERROR, ERROR_TIMEOUT);
			return TRUE;
		}

		// Verify Year
		strncpy(szTemp1, &szCurrDate[2], 2);
		strncpy(szTemp2, &szExpiryDate[2], 2);
		if(atoi(szTemp1) < atoi(szTemp2))
		{
			bRetVal = FALSE;
		}
		else if(atoi(szTemp1) == atoi(szTemp2))
		{
			// Verify Month if Expiry Year is same as current Year
			strncpy(szTemp1, &szCurrDate[0], 2);
			strncpy(szTemp2, &szExpiryDate[0], 2);
			if(atoi(szTemp1) <= atoi(szTemp2))
				bRetVal = FALSE;
		}
	}

	if (bRetVal == TRUE)
		PromptDisplay(NULL, "Expired Card", NULL, NULL, NULL, BEEP_ERROR, ERROR_TIMEOUT);

	return bRetVal;
}

