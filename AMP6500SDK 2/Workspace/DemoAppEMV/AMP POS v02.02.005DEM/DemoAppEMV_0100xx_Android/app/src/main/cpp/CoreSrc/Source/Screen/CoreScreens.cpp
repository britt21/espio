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
* File       	 : 		CoreScreens.cpp
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		09/09/2015
**************************************************************************/

/***************************************************************************
 * Includes
 **************************************************************************/

// AMP Library
#include "AMPReturnCodes.h"
#include <AMPAgnos.h>
#include <AmpBaseAndroidIF.h>
#include <CoreConfig.h>
#include <AMPUIDisplay.h>
#include "CoreUtils.h"
#include "Project.h"
#include "CoreScreens.h"
#include <AMPBaseConsole.h>

/***************************************************************************
* Perprocessor Defines
**************************************************************************/

/***************************************************************************
* Globals
**************************************************************************/

void PromptDisplay(const char* szHeader, const char* szPrompt1, const char* szPrompt2,
                   const char* szPrompt3, const char* szPrompt4, int iBeep, int iDelayMS)
{
    PerformDisplayOperation(szHeader, szPrompt1, szPrompt2, szPrompt3, szPrompt4, iBeep, iDelayMS);
}

int PromptEntry(const char* szHeader, const char* szPrompt1, const char* szPrompt2, int iMax, int iMin,
                char* FieldFormat, char Mask, char *CurrSymbol,
                INPUT_METHOD InpMethod, ALIGNMENT InpAlign, char* szOutBuffer, int FontSize, int iTimeout)
{
    int iValLen = 0;
    char* szOut = {0};

    int iRetVal = PerformEntryOperation(szHeader, szPrompt1, szPrompt2, iMax, iMin, FieldFormat, Mask, CurrSymbol, InpMethod, szOutBuffer, FontSize, iTimeout);

    if(iRetVal == AMP_SUCCESS)
        szOut = PerformGetEntryValueOperation();

    if(szOut == NULL)
        return iRetVal;

    iValLen = strlen(szOut);
    memcpy(szOutBuffer, szOut, iValLen);

    return(iRetVal);
}

int PromptEnterCancel(const char* szHeader, const char* szPrompt1, const char* szPrompt2,
                      const char* szPrompt3, const char* szPrompt4, int iTimeout, int iBeep)
{
    int iRetVal = PerformEnterCancelOperation(szHeader, szPrompt1, szPrompt2, szPrompt3, szPrompt4, iBeep, iTimeout);
    return(iRetVal);
}

int PromptCancel(const char* szHeader, const char* szPrompt1, const char* szPrompt2,
                 const char* szPrompt3, const char* szPrompt4, int iTimeout, int iBeep)
{
    int iRetVal = PerformCancelOperation(szHeader, szPrompt1, szPrompt2, szPrompt3, szPrompt4, iBeep, iTimeout);
    return(iRetVal);
}


int PromptYesNo(const char *szHeader, const char* szPrompt1, const char *szPrompt2, int iTimeOut, int iBeep)
{
    int iRetVal = PromptSelection(szHeader, szPrompt1, szPrompt2, 2, "NO", "YES", NULL, iTimeOut, iBeep);

    switch(iRetVal)
    {
        case AMPKEY_MENU1:
            iRetVal = BUTTON_NO;
            break;
        case AMPKEY_MENU2:
        case AMPKEY_ENTER:
            iRetVal = BUTTON_YES;
            break;
        case AMPKEY_CANCEL:
            iRetVal = AMP_CANCEL;
            break;
    }

    return iRetVal;
}

int PromptSelection(const char *szHeader, const char* szPrompt1, const char* szPrompt2, int nSelectionButtons,
                    const char *szButtonMsg1, const char* szButtonMsg2, const char* szButtonMsg3, int iTimeout, int iBeep)
{
    int iRetVal = PerformSelectionOperation(szHeader, szPrompt1, szPrompt2, nSelectionButtons,
                                            szButtonMsg1, szButtonMsg2, szButtonMsg3, iTimeout, iBeep);
    return(iRetVal);
}

void DisplayCardEntryPrompt(const char *szHeader, const char *szPromptLang1, const char *szPromptLang2, BOOL bDisplayIcon)
{
    PerformDisplayCardEntry(szHeader, szPromptLang1, szPromptLang2, (unsigned char)bDisplayIcon);
}

int DisplayPassTerminalToCustomer(const char *szHeader, const char *szPrompt1, const char *szPrompt2, BOOL bWaitForKey)
{
    return PerformDisplayPassTerminal(szHeader, szPrompt1, szPrompt2, bWaitForKey);
}