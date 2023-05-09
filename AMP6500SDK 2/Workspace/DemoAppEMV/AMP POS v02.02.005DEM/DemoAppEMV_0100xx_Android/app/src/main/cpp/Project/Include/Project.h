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
* File       	: 		Project.h
* Application 	: 		AMP-Base Application
* Date Coded	: 		11/08/2015
**************************************************************************/

#ifndef PROJECT_INCLUDE_PROJECT_H_
#define PROJECT_INCLUDE_PROJECT_H_

// AMP Library
#include <EmvTags.h>

// Core Project Includes
#include "AMPDefine.h"
#define USING_AMPEMVL2

//4 Custom Timers
//#define CUSTOM_TIMER1_TIMEOUT		0

//4 Screen Transition Timeout
#define SCREEN_TRANSITION_TIMEOUT	5000

//4 Enable Comm TR/RX Debug Logs in Release version
//#define RELEASE_SHOW_TR_RX


//4 Enable Manual Entry
#define MANUAL_ENTRY_SUPPORTED

//4 Enable Contactless MSD
//#define ENABLE_CTLS_MSD

//4 Enable CTLS EMV
#define ENABLE_CTLS_EMV


//4 Enable Contact EMV
#define ENABLE_CONCTACT_EMV


//4 Additional Data Type for Journal Data
#define EMVTAG 0xF


//4 Maximum Fields for a Record Entry
#define MAX_JOURNAL_FIELD	512


//4 Definition of Journal Table IDs & Table Name
#define JOURNAL_TRANSRECORDS 			1					// Table ID
#define JOURNAL_TRANSRECORDS_TBL_NAME 	"TransRecords"		// Table Name


//4 Name of Critical Error Log File
#define CRITICAL_ERR_LOG_FILE	"CritErr.txt"

//4 Default Screen Timeouts
#define ERROR_TIMEOUT	3000
#define WARN_TIMEOUT	3000
#define INFO_TIMEOUT	3000
#define ENTRY_TIMEOUT	30000

#define DEFAULT_INPUT_TIMEOUT	30


//4 Maximum Acquirers and Issuers
#define MAX_ACQUIRERS	32
#define MAX_ISSUERS		32


//4 Default Currency Symbol
#define DEFAULT_CURRENCY_SYMBOL	"$"

//4 Default Amount Size
// TODO: Make this configurable
#define DEFAULT_AMOUNT_SIZE	8

//4 Card Present during Manual Entry
#define CARD_PRESENT_NO			0
#define CARD_PRESENT_YES		1

//4 AVS Override
#define AVS_OVERRIDE_NO			0
#define AVS_OVERRIDE_YES		1

//4 Tax Exempt
#define TAX_EXEMPT_NO			0
#define TAX_EXEMPT_YES			1

//4 Check if Transaction was Approve/Success (Base on TSYS Specs)
	// 00 	Approval  	Approved and completed
	// 08 	Approval  	Honor MasterCard with ID
	// 10 	Partial 		Approval  Partial approval for the authorized amount returned in Group III version 022
	// 11 	Approval 		VIP approval	
	// T0 	Approval  	First check is OK and has been converted
	// A1 	Activated 	POS device authentication successful
	// A3 	Deactivated  	POS device deactivation successful
#define IsTransApproved(RespCode) ((\
		(strcmp(RespCode, "00") == 0) ||\
		(strcmp(RespCode, "08") == 0) ||\
		(strcmp(RespCode, "10") == 0) ||\
		(strcmp(RespCode, "11") == 0) ||\
		(strcmp(RespCode, "85") == 0) ||\
		(strcmp(RespCode, "T0") == 0) ||\
		(strcmp(RespCode, "A1") == 0) ||\
		(strcmp(RespCode, "A3") == 0) ||\
		(strcmp(RespCode, "GB") == 0)\
		) ? TRUE : FALSE)

//4 Check if Transaction was Referral (Base on TSYS Specs)
	// 01 Call Refer to issuer
	// 02 Call Refer to issuer-Special condition
#define IsTransReferral(RespCode) ((\
		(strcmp(RespCode, "01") == 0) ||\
		(strcmp(RespCode, "02") == 0)\
		) ? TRUE : FALSE)

#endif /* PROJECT_INCLUDE_PROJECT_H_ */

