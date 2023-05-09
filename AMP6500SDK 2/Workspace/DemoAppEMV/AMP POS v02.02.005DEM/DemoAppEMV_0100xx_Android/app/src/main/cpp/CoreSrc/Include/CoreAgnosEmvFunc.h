
#ifndef COREAGNOSEMVFUNC_H_
#define COREAGNOSEMVFUNC_H_

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
* File       	 : 		CoreAgnosEmvFunc.h
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		08/29/2016
**************************************************************************/

// AMP Library Includes
#include <AMPDataTypes.h>
#include <AMPEmvSizes.h>


// Core Project Includes
#include "CoreTransObj.h"
#include <AMPAgnosEmv.h>


int DoAgnosEmvInitiateFlow(TRANSACTION_OBJECT1 *pobTran);
int DoAgnosEmvCompletion(TRANSACTION_OBJECT1 *pobTran);
void DoAgnosEmvFirstReadTLVCollxn(TRANSACTION_OBJECT1 *pobTran);
BOOL IsEmvDebitTransaction(void);


#endif

