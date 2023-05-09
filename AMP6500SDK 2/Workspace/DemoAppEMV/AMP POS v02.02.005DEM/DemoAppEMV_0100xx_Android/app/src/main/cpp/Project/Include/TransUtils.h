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
* File       	: 		TransUtils.h
* Application 	: 		AMP-Base Application
* Date Coded	: 		09/13/2015
**************************************************************************/

#ifndef TRANSUTILS_H_
#define TRANSUTILS_H_

// Core Project Include
#include "CoreTransObj.h"

// Project Include
#include "Transactions.h"

//!Checks if batch is empty (based on current batch number: CFGPATH_INTERNAL_BATCHNUMBER)
BOOL IsBatchEmpty(void);

//! Deletes all records in the batch (based on current batch number: CFGPATH_INTERNAL_BATCHNUMBER)
int DeleteBatchRecords(void);

void SysSleep(int ms_delay);

#endif //BASEAPP_TRANSUTILS_H
