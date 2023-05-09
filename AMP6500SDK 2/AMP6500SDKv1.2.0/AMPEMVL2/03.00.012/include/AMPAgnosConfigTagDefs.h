#ifndef AMPAGNOSCONFIGTAGDEFS_H_
#define AMPAGNOSCONFIGTAGDEFS_H_

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
* File       	 : 		AMPAgnosConfigTagDefs.h
* Library	 	 : 		AMPEMVL2
* Date Coded  : 		11/15/2016
**************************************************************************/


//1 TERMINAL

#define TERMINAL_COUNTRY_CODE					0x9f1a 	//Country code
#define TERMINAL_CARDHOLDER_CONFIRMATION		0xdf79 	//Cardholder confirmation
#define TERMINAL_TERMINAL_TYPE					0x9f35	//Terminal type
#define TERMINAL_EMV_CONTACT_SUPPORTED			0xdf0a	//EMV contact supported
#define TERMINAL_TERM_CAP						0x9f33	//Terminal capabilities
#define TERMINAL_ADDTL_TERMCAP					0x9f40	//Additional terminal capabilities
#define TERMINAL_EMV_CTLS_SUPPORTED				0xdf55	//EMV contactless supported
#define TERMINAL_MSD_SUPPORTED					0xdf0b	//MSD Supported
#define TERMINAL_PIN_TIMEOUT					0xdf27	//PIN Timeout
#define TERMINAL_BATCH_MANAGED					0xdf06	//Batch managed
#define TERMINAL_ADVICE_MANAGED					0xdf08	//Advice managed
#define TERMINAL_PSE_SUPPORTED					0xdf7a	//PSE Supported
#define TERMINAL_AUTORUN_MODE					0xdf0d	//Autorun mode
#define TERMINAL_PRE_AMOUNT						0xdf10	//Pre-Amount for Autorun mode
#define TERMINAL_PIN_BYPASS_SUPPORTED			0xdf7b	//PIN Bypass supported
#define TERMINAL_REFERRAL_MANAGED				0xdf07	//Referral managed
#define TERMINAL_DEFAULT_TAC_SUPPORTED			0xdf09	//Default TAC Supported
#define TERMINAL_DEFAULT_TAC_DEFAULT			0xdf73	//Default TAC-Default
#define TERMINAL_DEFAULT_TAC_DENIAL				0xdf74	//Default TAC-Denial
#define TERMINAL_DEFAULT_TAC_ONLINE				0xdf75	//Default TAC-Online
#define TERMINAL_RANDOM_TRANS_SEL_NOT_SUPPORTED	0xdf53	//Random Transaction Selection not supported
#define TERMINAL_VELOCITY_CHECK_NOT_SUPPORTED	0xdf54	//Velocity Check not supported
#define TERMINAL_CDA_TYPE						0xdf7c	//CDA Type


//1 PROCESSING

#define PROCESSING_DELIMITER					0xff33	//AID record delimiter
#define PROCESSING_ACQUIRER_ID					0x9f01	//Acquirer ID
#define PROCESSING_AID							0x4f	//Application Identifier
#define PROCESSING_ASI							0xdf7e 	//Application selection indicator
#define PROCESSING_AVN							0x9f09	//Application version number
#define PROCESSING_SKIP_TAC_IAC					0xdf11	//Skip TAC/IAD Default checking
#define PROCESSING_RANDOM_TRANS_SEL_SUPPORTED	0xdf12	//Random transaction supported
#define PROCESSING_VELOCICTY_CHECK				0xdf13 	//Velocity checking
#define PROCESSING_FLOOR_LIMIT_CHECK			0xdf14	//Floor limit checking
#define PROCESSING_TAC_SUPPORTED				0xdf15	//TAC Supported
#define PROCESSING_TAC_DEFAULT					0xdf20	//TAC-Default
#define PROCESSING_TAC_DENIAL					0xdf21	//TAC-Denial
#define PROCESSING_TAC_ONLINE					0xdf22	//TAC-Online
#define PROCESSING_FLOOR_LIMIT					0x9f1b	//Floor limit
#define PROCESSING_TARGET_PERCENTAGE			0xdf70	//Target Percentage (ex: 63 -> 99%)
#define PROCESSING_THRESHOLD_VALUE				0xdf6e	//Threshold value (ex: 1F4 ->500)
#define PROCESSING_MAX_TARGET_PERCENTAGE		0xdf6f	//Maximum target percentage (ex: 63 ->99%)
#define PROCESSING_DEFAULT_DDOL_SUPPORTED		0xdf01	//Default DDOL supported
#define PROCESSING_DEFAULT_DDOL					0xdf71	//Default DDOL
#define PROCESSING_DEFAULT_TDOL_SUPPORTED		0xdf02	//Default TDOL supported
#define PROCESSING_DEFAULT_TDOL					0xdf72	//Default TDOL
#define PROCESSING_TRANS_CURRENCY_CODE			0x5f2a	//Transaction currency code
#define PROCESSING_TRANS_CURRENCY_EXPO			0x5f36	//Transaction currency exponent

//1 ENTRY POINT

#define EP_DELIMITER							0xff35	//KAT record delimiter
#define EP_KAT									0xdf0e	//KAT Combibation B1-KernelID, B2-AIDindex, B3-TransType
#define EP_KAT_PARAMS							0xdf0f	//holds the set of parameter tags

//Kernel-2 Paypass Mastercard
#define EP_PAYPASS_DEFAULT_UDOL					0xdf1a	//default UDOL
#define EP_PAYPASS_KERNEL_ID					0xdf0c	//kernel id
#define EP_PAYPASS_MAGSTRIPE_AVN				0x9f6d	//magstripe AVN
#define EP_PAYPASS_MAGSTRIPE_CVM_REQ_CAP		0xdf1e 	//magstripe CVM Capabilities
#define EP_PAYPASS_MAGSTRIPE_NOCVM_REQ_CAP		0xdf2c 	//magstripe No-CVM Capabilities
#define EP_PAYPASS_RCFL							0xdf23 	//Reader Contactless floor limit
#define EP_PAYPASS_RCTL_NO_ONDEVICE				0xdf24 	//Reader contactless transaction limit NO-On-device
#define EP_PAYPASS_RCTL_ONDEVICE				0xdf25 	//Reader contactless transaction limit On-Device
#define EP_PAYPASS_RCRL							0xdf26 	//Reader CVM Required Limit
#define EP_PAYPASS_TERM_COUNTRY_CODE			0x9f1a	//Terminal Country code
#define EP_PAYPASS_MOBILE_SUPPORT_INDICATOR		0x9f7e	//Mobile support indicator
#define EP_PAYPASS_ADDTL_TERMCAP				0x9f40	//Additional Terminal Capabilities
#define EP_PAYPASS_AVN							0x9f09	//Application version number
#define EP_PAYPASS_CARD_DATA_INPUTCAP			0xdf17	//Card data input capabilities
#define EP_PAYPASS_CVM_CAP_CVM_REQ				0xdf18	//CVM Capabilities - CVM Required
#define EP_PAYPASS_CVM_CAP_NOCVM_REQ			0xdf19	//CVM Capabilities - No-CVM Required
#define EP_PAYPASS_KERNEL_CONFIG				0xdf1b	//kernel configuration
#define EP_PAYPASS_MAX_LIFE_TRANS				0xdf1c	//Max Life transaction (in sec) (ex: 012c ->300sec)
#define EP_PAYPASS_MAX_TORN_TRANS				0xdf1d	//Max number of torn transaction
#define EP_PAYPASS_SECURITY_CAP					0xdf03	//Security capabilities
#define EP_PAYPASS_TAC_DEFAULT					0xdf20	//TAC-Default
#define EP_PAYPASS_TAC_DENIAL					0xdf21	//TAC-Denial
#define EP_PAYPASS_TAC_ONLINE					0xdf22	//TAC-Online
#define EP_PAYPASS_TERMINAL_TYPE				0x9f35	//Terminal Type
#define EP_PAYPASS_MSG_HOLDTIME					0xdf2d	//Message holdtime  in 100ms (00000D -> 1300ms)
#define EP_PAYPASS_MERCHANT_CATEGORY_CODE		0x9f15	//Merchant category code

//Kernel-3 PayWave Visa
#define EP_PAYWAVE_TERM_COUNTRY_CODE			0x9f1a	//Terminal Country code
#define EP_PAYWAVE_KERNEL_CONFIG				0xdf1b	//Kernel Configuration
#define EP_PAYWAVE_MSG_HOLDTIME					0xdf2d	//Message holdtime in 100ms (00000A -> 1000ms)
#define EP_PAYWAVE_AVN							0x9f09	//Application version number
#define EP_PAYWAVE_TERM_CAP						0x9f33	//Terminal capabilities
#define EP_PAYWAVE_ADDTL_TERMCAP				0x9f40	//Additional Terminal Capabilities
#define EP_PAYWAVE_BITMAP_ENTRY					0xdf30	//Bitmap Entrypoint
#define EP_PAYWAVE_STATUS_ZERO_AMNT_FLAG		0xdf32	//Status zero amount allowed flag
#define EP_PAYWAVE_TERMINAL_TYPE				0x9f35	//Terminal Type
#define EP_PAYWAVE_TTQ							0x9f66	//Terminal Transaction Qualifier (TTQ)
#define EP_PAYWAVE_FLOOR_LIMIT					0x9f1b	//Floor limit
#define EP_PAYWAVE_RCFL							0xdf23 	//Reader Contactless floor limit
#define EP_PAYWAVE_RCTL							0xdf24 	//Reader contactless transaction limit
#define EP_PAYPASS_RCRL							0xdf26 	//Reader CVM Required Limit

//Kernel-4 ExpressPay Amex
#define EP_EXPRESSPAY_CTLS_READER_CAP			0x9f6d	//Contactless reader capabilities
#define EP_EXPRESSPAY_TERM_COUNTRY_CODE			0x9f1a	//Terminal Country code
#define EP_EXPRESSPAY_TID_IFD_SERIALNO			0x9f1e	//TID IFD Serial Number
#define EP_EXPRESSPAY_KERNEL_CONFIG				0xdf1b	//Kernel configuration
#define EP_EXPRESSPAY_TERMINAL_TYPE				0x9f35	//Terminal Type
#define EP_EXPRESSPAY_ADDTL_TERMCAP				0x9f40	//Additional Terminal Capabilities
#define EP_EXPRESSPAY_AVN						0x9f09	//Application version number
#define EP_EXPRESSPAY_TERM_CAP					0x9f33	//Terminal capabilities
#define EP_EXPRESSPAY_TAC_DEFAULT				0xdf20	//TAC-Default
#define EP_EXPRESSPAY_TAC_DENIAL				0xdf21	//TAC-Denial
#define EP_EXPRESSPAY_TAC_ONLINE				0xdf22	//TAC-Online
#define EP_EXPRESSPAY_MSG_HOLDTIME				0xdf2d	//Message holdtime in 100ms (00000A -> 1000ms)
#define EP_EXPRESSPAY_BITMAP_ENTRY				0xdf30	//Bitmap Entrypoint
#define EP_EXPRESSPAY_STATUS_ZERO_AMNT_FLAG		0xdf32	//Status zero amount allowed flag
#define EP_EXPRESSPAY_RCFL						0xdf23 	//Reader Contactless floor limit
#define EP_EXPRESSPAY_RCTL						0xdf24 	//Reader contactless transaction limit
#define EP_EXPRESSPAY_RCRL						0xdf26 	//Reader CVM Required Limit
#define EP_EXPRESSPAY_TIMEOUT					0xdf27	//Timeout (ex: 0F -> 15secs)

//Kernel-5 J/Speedy JCB


//Kernel-6 DPAS Discover
#define EP_DPAS_AVN								0x9f09	//Application version number
#define EP_DPAS_TERM_COUNTRY_CODE				0x9f1a	//Terminal Country code
#define EP_DPAS_KERNEL_CONFIG					0xdf1b	//Kernel configuration
#define EP_DPAS_TERMINAL_TYPE					0x9f35	//Terminal Type
#define EP_DPAS_TAC_DEFAULT						0xdf20	//TAC-Default
#define EP_DPAS_TAC_DENIAL						0xdf21	//TAC-Denial
#define EP_DPAS_TAC_ONLINE						0xdf22	//TAC-Online
#define EP_DPAS_BITMAP_ENTRY					0xdf30	//Bitmap Entrypoint
#define EP_DPAS_STATUS_ZERO_AMNT_FLAG			0xdf32	//Status zero amount allowed flag
#define EP_DPAS_TTQ								0x9f66	//Terminal Transaction Qualifier (TTQ)
#define EP_DPAS_FLOOR_LIMIT						0x9f1b	//Floor limit
#define EP_DPAS_RCFL							0xdf23 	//Reader Contactless floor limit
#define EP_DPAS_RCTL							0xdf24 	//Reader contactless transaction limit
#define EP_DPAS_RCRL							0xdf26 	//Reader CVM Required Limit



#endif /*AMPAGNOSCONFIGTAGDEFS */

