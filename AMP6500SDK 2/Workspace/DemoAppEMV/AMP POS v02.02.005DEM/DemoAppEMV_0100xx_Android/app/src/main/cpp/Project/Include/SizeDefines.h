
#ifndef SIZESDEFENITION_H_
#define SIZESDEFENITION_H_

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
* File       	 : 		SizeDefines.h
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		10/18/2015
**************************************************************************/

// Max and Min Pans size
#define MAX_PAN_SIZE	19	//25
#define MIN_PAN_SIZE 	13

// Max Card Holder Name
#define SZ_CARDHOLDER_NAME	32

// Expiry Date Size for Manual Entry
#define SZ_EXPIRY_DATE	4

// Service Code Size
#define SZ_SVC_CODE		3

// Card Verification Value Size
#define SZ_CVV2			4

// Operator ID, Name, and Password Size
#define SZ_OPERATOR_ID		4
#define SZ_OPERATOR_NAME	20
//#define SZ_OPERATOR_PW		10

// Size of MAC and PIN Blocks
#define SZ_MACBLOCK		8
#define SZ_PINBLOCK		8
#define SZ_KSN			10

// Size of Passwords
#define SZ_PASSWORD_MAX	10
#define SZ_PASSWORD_MIN	8

// E2EE Size
#define SZ_TRE2EE_KTB 500 // taken from E2EE source

// Max Config Data Size
#define MAX_CFG_DATA_SZ	64

// Max Batch Number
#define MAX_BATCH_NUMBER 999

// Max size of Header
#define MAX_HEADER_SIZE 64

#define MAX_PACKET_SIZE			2048

#endif /* SIZESDEFENITION_H_ */

