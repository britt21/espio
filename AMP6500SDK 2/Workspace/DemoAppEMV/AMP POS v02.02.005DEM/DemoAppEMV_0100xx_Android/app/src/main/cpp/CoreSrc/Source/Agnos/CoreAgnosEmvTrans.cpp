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
* File       	 : 		CoreAgnosEmvTrans.cpp
* Library	 	 : 		AMPEMVL2
* Date Coded  : 		09/17/2017
**************************************************************************/

/***************************************************************************
 * Includes
 **************************************************************************/

// Standard Library
#include <string.h>
#include <AMPAgnosEmvCtls.h>

// Project Includes
#include "AMPAgnos.h"

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

void InitializeEMVConfig(void)
{
    cAMPAgnosConfig *pAgnosConfig = cAMPAgnosConfig::get_Instance();

    pAgnosConfig->LoadAgnosConfig(TERMINAL_CFG);
    pAgnosConfig->LoadAgnosConfig(PROCESSING_CFG);
    pAgnosConfig->LoadAgnosConfig(ENTRY_POINT_CFG);
    pAgnosConfig->LoadAgnosConfig(CAKEYS_CFG);
    pAgnosConfig->UpdateAgnosConfig(CAKEYS_CFG);
}

void InitAmpEmvL2(const char *szAgnosIniPath, const char *szAgnosConfigPath, const char *szAgnosLibsPath, AMPAGNOS_CB *Callback)
{
    // Create Instance of EMV Obj
    // NOTE:  Do not edit by order of creation of instances to maintain singleton of instance!
    cAMPAgnosEmvCtls *pAgnosEmvCtls = cAMPAgnosEmvCtls::get_Instance();
    cAMPAgnosEmv *pAgnosEmv = cAMPAgnosEmv::get_Instance();
    cAMPAgnos *pAgnos = cAMPAgnos::get_Instance();
    cAMPAgnosConfig *pAgnosConfig = cAMPAgnosConfig::get_Instance();

    //Set Agnos Init Path
    if(strlen(szAgnosIniPath) > 0)
    {
        pAgnos->SetIniPath(szAgnosIniPath);
    }

    //Set Agnos Config Path
    if(strlen(szAgnosConfigPath) > 0)
    {
        pAgnos->SetConfigPath(szAgnosConfigPath);
        pAgnosConfig->SetConfigPath(szAgnosConfigPath);
    }

    //Set Agnos Enp Libs Path
    if(strlen(szAgnosLibsPath) > 0)
    {
        pAgnos->SetEnpLibsPath(szAgnosLibsPath);
    }

    // Initialize Agnos Framework
    pAgnos->Initialize();

    // Register Callback
    pAgnos->RegisterCallback(Callback);

    // Initialize EMV Config
    InitializeEMVConfig();
}