
#ifndef COREFLOW_H_
#define COREFLOW_H_

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
* File       	 : 		CoreFlow.h
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		09/08/2015
**************************************************************************/

#include "CoreTransObj.h"

/*
*	Implementation of Most Basic Core Flow
*/

//! Card Entry
int DoCardEntry(TRANSACTION_OBJECT1* pobTran);

//! Manual Card Entry of PAN
int DoManualEntry(TRANSACTION_OBJECT1* pobTran);
//! Manual Card Entry of Exp. Date
int DoExpDateEntry(TRANSACTION_OBJECT1* pobTran);

//! Amount Entries
int DoAmountEntry(TRANSACTION_OBJECT1* pobTran);

int DoPasswordCheckStrength(char* chPassword);

//! Card Imprint Prompt
int DoCardImprintPrompt(TRANSACTION_OBJECT1* pobTran);

//! AVS Address and ZIP Entry
int DoAVSDataEntry(TRANSACTION_OBJECT1* pobTran);

//! ZIP Code Entry
int DoZIPCodeEntry(TRANSACTION_OBJECT1* pobTran);

//! CVD Entry
int DoCVV2Entry(TRANSACTION_OBJECT1* pobTran);

//! Check if Card is expired
BOOL bIsExpired(const char* szExpiryDate);

#endif /* COREFLOW_H_ */

