
#ifndef AMPEMVSIZES_H_
#define AMPEMVSIZES_H_

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
* File       	 : 		AMPEmvSizes.h
* Application	 : 		AMP Component
* Date Coded  : 		08/31/2015
**************************************************************************/


// EMV-related definitions

#define EMV_MAX_DATA_SIZE					254		// Max Data Size of an EMV Tag

/*
*	ASCII Sizes (excluding Null terminator)
*/

#define EMV_COUNTRY_CODE_SIZE                4       // ASCII rep. of 2 bytes binary
#define EMV_CURRENCY_CODE_SIZE               4       // ASCII rep. of 2 bytes binary
#define EMV_TERM_CAPABILITIES_SIZE           6       // ASCII rep. of 3 bytes binary
#define EMV_ADD_TERM_CAPABILITIES_SIZE       10      // ASCII rep. of 5 bytes binary
#define EMV_TERM_TYPE_SIZE                   2       // ASCII rep. of 1 byte
#define EMV_TAC_DEFAULT_SIZE                 10      // ASCII rep. of 5 bytes binary
#define EMV_TAC_DENIAL_SIZE                  10      // ASCII rep. of 5 bytes binary
#define EMV_TAC_ONLINE_SIZE                  10      // ASCII rep. of 5 bytes binary
#define EMV_TAC_SIZE                         10      // ASCII rep. of 5 bytes binary
#define EMV_MAX_TDOL_SIZE                    512     // ASCII rep. of 32 bytes binary
#define EMV_MAX_DDOL_SIZE                    512     // ASCII rep. of 32 bytes binary
#define EMV_CURR_CODE_SIZE                   4       // ASCII rep. of 2 bytes binary
#define EMV_APPL_VER_SIZE					 4
#define EMV_RID_SIZE                         10      // ASCII rep. of 5 bytes binary
#define EMV_MAX_PK_MODULUS_SIZE              496     // ASCII rep. of 248 bytes binary
#define EMV_MAX_PK_EXPONENT_SIZE             6       // ASCII rep. of 3 bytes binary
#define EMV_MAX_AID_SIZE                     32      // ASCII rep. of 16 bytes binary
#define EMV_AVN_SIZE                         4       // ASCII rep. of 2 bytes binary
#define EMV_SCHEME_NAME_SIZE                 32      // Name of Card Scheme
#define EMV_PK_FILE_NAME                     30      // Name of file containing Public Key + Exponent
#define EMV_PK_EXPDATE_SIZE                  6       // DDMMYY
#define EMV_PK_CHECKSUM_SIZE                 40      // Hash is 20 bytes
#define EMV_CSN_FILE_NAME_SIZE               30      // Name of file containing CSN validation list
#define EMV_TERM_ID_SIZE                     8
#define EMV_MERCH_ID_SIZE                    15
#define EMV_MERCH_CAT_CODE_SIZE              4 

#define EMV_MAX_PAN_SIZE					 20		 // ASCII rep. of 10 bytes binary

/*
*	HEX Sizes
*/

#define TVR_SIZE                             5  // Represented in bytes
#define TSI_SIZE                             2  // Represented in bytes
#define AVN_SIZE                     		 2  // Represented in bytes
#define TAC_SIZE                     		 5  // Represented in bytes
#define IAC_SIZE                     		 5  // Represented in bytes
#define RID_SIZE							 5

#define CVM_RESULT_SIZE						 3

#define TERMINAL_CAPABILITY_SIZE			 3
#define ADDL_TERM_CAPABILITY_SIZE			 5

#define CAPK_EXP_DATE_SIZE					 3
#define CAPK_CHECKSUM_SIZE					 20

#define AID_MIN_SIZE                   		 5
#define AID_MAX_SIZE                   		 16

#define APPL_PREFERNAME_SIZE             	 16
#define APPL_LABEL_SIZE             		 16
#define APPL_VERSION_SIZE					 2

#define CMD_TO_PERFORM_MAX_SIZE      		 239
#define TRACK2_EQ_DATA_MAX_SIZE         	 19
#define APPL_PAN_MAX_SIZE              		 10

#define CARDHOLDER_NAME_MIN_SIZE       		 2
#define CARDHOLDER_NAME_MAX_SIZE       		 26

#define EMV_DATE_SIZE                  		 3
#define COUNTRY_CODE_SIZE              		 2
#define CURRENCY_CODE_SIZE               	 2

#define LANG_PREF_MIN_SIZE       		 	 2
#define LANG_PREF_MAX_SIZE       		 	 8

#define EMV_SERVICE_CODE_SIZE          		 2
#define PAN_SEQNUM_SIZE                		 1
#define CURR_EXP_SIZE                  		 1
#define AMOUNT_AUTH_SIZE               		 4
#define APPL_INTCHG_PROFILE_SIZE       		 2

#define DF_FILE_MIN_SIZE               		 5
#define DF_FILE_MAX_SIZE               		 16

#define ISSUER_SCRIPT_CMD_MAX_SIZE     		 261
#define APPL_PRIORITY_IND_SIZE         		 1
#define SFI_SIZE                       		 1
#define EMV_AUTH_CODE_SIZE             		 6 
#define AUTH_RESP_CODE_SIZE            		 2 
#define ISS_AUTH_DATA_SIZE            		 16

#define CDOL_MAX_SIZE                  		 252
#define CVM_LIST_MAX_SIZE              		 252

#define MAX_AID_LIST                    	 32		// Max Application on a Single card

#define MERCH_CAT_CODE_SIZE					 2

#define EMV_STRING_SIZE                      32            

#endif /* AMPEMVSIZES_H_ */

