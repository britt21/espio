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
* File       	: 		Transactions.h
* Application 	: 		AMP-Base Application
* Date Coded	: 		03/28/2015
**************************************************************************/

#ifndef TRANSACTIONS_H_
#define TRANSACTIONS_H_

#define RETURN_LAST_MENU		2000

//4 Transaction ID
typedef enum
{
	TRANS_NONE = 0,
	TRANS_PURCHASE,

}TRANS_TYPE;

//3 Transactions

// Purchase/Sale Transaction
int Purchase(void);


#endif /* TRANSACTIONS_H_ */
