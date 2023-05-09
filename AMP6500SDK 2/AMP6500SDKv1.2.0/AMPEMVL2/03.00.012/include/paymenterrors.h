// NAME.......  paymenterrors.h
// PURPOSE....  Encoding of Payment errors following Agnos grammar
// PROJECT....  AGNOSMW
// REFERENCES.	--
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//

#ifndef PAYMENTERRORS_H_
#define PAYMENTERRORS_H_

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////
// Errors' Module encoding
// Module	0 0			= GPI 
// Module	0 1 		= Agnos
// Module	1 0 		= Atmos
// Module	1 1 		= Payment

// Errors' Severity encoding
// Severity	0 0			= Event 
// Severity	0 1 		= EMV error
// Severity	1 0 		= System error
// Severity	1 1 		= RFU

////////////////////////////////////////////////
// Payment Errors for Interface to middleware
//			HIGH BYTE			LOW BYTE
// Module	1 1 
// Interface	0 0 0 0 0 0 	
// Severity						x x 
// Code								x x	x x x x
typedef unsigned short tPaymentError;

#define	payNO_ERROR						0xC000
#define	payNO_ERROR_TXT					"No Error"

#define	payNEW_SELECTION				0xC001
#define	payNEW_SELECTION_TXT			"New Selection"

#define	payCONFIGURATION_FAILURE		0xC002
#define	payCONFIGURATION_FAILURE_TXT	"Configuration Failure"

#define	payGO_ONLINE					0xC003
#define	payGO_ONLINE_TXT				"Go Online"

#define	payACCEPTED						0xC004
#define	payACCEPTED_TXT					"Accepted"

#define	payDECLINED						0xC005
#define	payDECLINED_TXT					"Declined"

#define	payNOT_ACCEPTED					0xC006
#define	payNOT_ACCEPTED_TXT				"Not Accepted"

#define	paySYSTEM_ERROR					0xC007
#define	paySYSTEM_ERROR_TXT				"Application Error"

#define	payCARD_ERROR					0xC008
#define	payCARD_ERROR_TXT				"Card Error"

#define	payINVALID_SVC_CALL				0xC009
#define	payINVALID_SVC_CALL_TXT			"Invalid Service Call"

#define	payFALLBACK_TO_MAGSTRIPE		0xC00A
#define	payFALLBACK_TO_MAGSTRIPE_TXT	"Fallback To Magstripe"

#define	payTRANSACTION_TERMINATED		0xC00B
#define	payTRANSACTION_TERMINATED_TXT	"Transaction Terminated"

#define	paySELECTION_ERROR				0xC00C
#define	paySELECTION_ERROR_TXT			"Application Not Selected"

#define	payTRANSACTION_CANCELLED		0xC00D
#define	payTRANSACTION_CANCELLED_TXT	"Transaction Cancelled"

#define	payNO_MUTUAL_APPLICATION    	0xC00E
#define	payNO_MUTUAL_APPLICATION_TXT	"No Mutual Application"


typedef unsigned short tDataMngrError;

#define	dtmNO_ERROR						0xC020
#define	dtmNO_ERROR_TXT					"No Error"

#define	dtmFILE_NO_OPENED				0xC021
#define	dtmFILE_NO_OPENED_TXT			"File No opened"

#define	dtmSYSTEM_ERROR					0xC080
#define	dtmSYSTEM_ERROR_TXT				"Fail System Error"

#ifdef __cplusplus
}
#endif

#endif /*PAYMENTERRORS_H_*/
