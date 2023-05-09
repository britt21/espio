// NAME.......  agnoserros.h
// PURPOSE....  Agnos errors managment
// PROJECT....  AGNOS
// REFERENCES.
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//

#ifndef AGNOSERRORS_H_
#define AGNOSERRORS_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------
//			Include Files
//---------------------------------------------------------
//---- Local Headers ----
#include "agnostypes.h"
//---- Global Headers ----
#include "gpi_agnos_framework_globals.h"

/**
 * \addtogroup Errors
 * @{
 * @file agnoserrors.h
 * @brief Set of errors related to Agnos API
 */

//---------------------------------------------------------
//			Definitions
//---------------------------------------------------------

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

typedef unsigned short	tAgnosError;

////////////////////////////////////////////////
// Agnos Errors
//			HIGH BYTE			LOW BYTE
// Module	0 1 
// Interface	0 0 0 0 0 0 	
// Severity						x x 
// Code								x x	x x x x

//////////// Events (do not interrupt the EMV flow)
#define	agnNO_ERROR								0x4000
#define	agnNO_ERROR_TXT							"Normal Processing"

#define	agnTVR_BIT_RAISED						0x4001
#define	agnTVR_BIT_RAISED_TXT					"TVR Status Changed"

#define	agnTSI_BIT_RAISED						0x4002
#define	agnTSI_BIT_RAISED_TXT					"TSI Status Changed"

#define agnUNDEFINED_VALUE						0x4003
#define agnUNDEFINED_VALUE_TXT					"Tag Not Defined - Default Value Used"

#define agnOPTIONAL_ICC_MISSING					0x4004
#define agnOPTIONAL_ICC_MISSING_TXT				"Tag Not Defined - Tag Ignored"

#define	agnUNKNOWN_TAG							0x4005
#define agnUNKNOWN_TAG_TXT						"Tag Unknown By Terminal"

#define	agnDEFINED_PDOL							0x4006
#define	agnDEFINED_PDOL_TXT						"PDOL Defined In ICC"

#define	agnEXPIRATION_DATE_REACHED				0x4007
#define agnEXPIRATION_DATE_REACHED_TXT			"Expiration Date Reached"

#define	agnEFFECTIVE_DATE_NOT_REACHED			0x4008
#define	agnEFFECTIVE_DATE_NOT_REACHED_TXT		"Effective Date Not Reached"

//CVM
#define	agnCVM_RULE_BYPASSED					0x4009
#define	agnCVM_RULE_BYPASSED_TXT				"CVM Rule Bypassed"

#define	agnCVM_SUCCESSFUL						0x400A
#define	agnCVM_SUCCESSFUL_TXT					"CVM Successful"

#define	agnCVM_UNKNOWN							0x400B
#define	agnCVM_UNKNOWN_TXT						"CVM Unknown"

#define	agnCVM_NOT_SUCCESSFUL					0x400C
#define	agnCVM_NOT_SUCCESSFUL_TXT				"CVM Not Successful"

#define	agnCVM_FAILED							0x400D
#define	agnCVM_FAILED_TXT						"CVM Failed"

//TRM
#define	agnINVALID_RTS_PARAMETERS				0x400E
#define	agnINVALID_RTS_PARAMETERS_TXT			"Floor Limit Smaller Or Equals Threshold Value"

//Scripting
#define	agnSCRIPT_EXECUTION_ERROR				0x400F
#define	agnSCRIPT_EXECUTION_ERROR_TXT			"Script Execution Failed"

// Offline Authentication
#define	agnODA_FAILED							0x4010
#define	agnODA_FAILED_TXT						"Offline Data Authentication Failure"

#define	agnSDA_FAILED							0x4011
#define	agnSDA_FAILED_TXT						"Static Data Authentication Failure"

#define	agnDDA_FAILED							0x4012
#define	agnDDA_FAILED_TXT						"Dynamic Data Authentication Failure"

#define	agnCDA_FAILED							0x4013
#define	agnCDA_FAILED_TXT						"Combined Data Authentication Failure"

#define agnSIGN_LENGTH							0x4014
#define agnSIGN_LENGTH_TXT						"Wrong Signature Length"

#define	agnDECRYPT_BEGIN						0x4015
#define	agnDECRYPT_BEGIN_TXT					"Wrong Decryption (BEGIN Tag)"

#define	agnDECRYPT_END							0x4016
#define	agnDECRYPT_END_TXT						"Wrong Decryption (END Tag)"

#define	agnWRONG_CERTIF							0x4017
#define	agnWRONG_CERTIF_TXT						"Invalid Certificate"							

#define	agnWRONG_SIGN							0x4018
#define	agnWRONG_SIGN_TXT						"Wrong Signature"

#define	agnCERT_EXPIRED							0x4019
#define	agnCERT_EXPIRED_TXT						"Certificate Expired"

#define	agnCERT_REVOKED							0x401A
#define	agnCERT_REVOKED_TXT						"Certificate Revoked"

#define	agnSIGN_DIGEST							0x401B
#define	agnSIGN_DIGEST_TXT						"Wrong Signature Digest"

#define	agnWRONG_DDOL							0x401C
#define	agnWRONG_DDOL_TXT						"Wrong DDOL"

#define	agnNOT_FOUND							0x401D
#define	agnNOT_FOUND_TXT						"Information Not Found"

// Others
#define	agnUNCOMPLETE_TLV_PARSING				0x401E
#define	agnUNCOMPLETE_TLV_PARSING_TXT			"Invalid BERTLV Parsing State"

#define	agnCVM_PROCESS_FAILED					0x401F
#define	agnCVM_PROCESS_FAILED_TXT				"CVM Process Failed"

#define	agnNO_ERROR_CONTINUE					0x4020
#define	agnNO_ERROR_CONTINUE_TXT				"No Error Continue"


//////////// EMV errors (has an EMV origin and abort the EMV flow)
#define	agnEMV_ERROR							0x4041
#define	agnEMV_ERROR_TXT						"EMV Flow Aborted"

#define	agnICC_MISSING							0x4042		
#define agnICC_MISSING_TXT						"Tag Not Defined In ICC"

#define	agnICC_FORMAT_ERROR						0x4043
#define	agnICC_FORMAT_ERROR_TXT					"Wrong ICC Data Format"

#define	agnDATA_NOT_DEFINED						0x4044
#define	agnDATA_NOT_DEFINED_TXT					"Data Not Defined By Application Level"

#define	agnREDUNDANT_TAG						0x4045
#define	agnREDUNDANT_TAG_TXT					"Redundant Primitive Tag Object Found"

#define	agnPROCEED_TO_NEW_SELECTION				0x4046
#define	agnPROCEED_TO_NEW_SELECTION_TXT			"Proceed To New Selection"

#define	agnTXN_ACCEPTED							0x4047
#define	agnTXN_ACCEPTED_TXT						"Approved"

#define	agnTXN_REJECTED							0x4048
#define	agnTXN_REJECTED_TXT						"Declined"

#define	agnTXN_ONLINE							0x4049
#define	agnTXN_ONLINE_TXT						"Process Online"

#define	agnSERVICE_NOT_ALLOWED					0x404A
#define	agnSERVICE_NOT_ALLOWED_TXT				"Not Accepted"

//////////// System errors (has a application origin and abort the EMV flow)
#define	agnSYSTEM_ERROR							0x4080
#define	agnSYSTEM_ERROR_TXT						"Unexpected Application Behavior"

#define	agnINVALID_SERVICE_CALL					0x4081
#define	agnINVALID_SERVICE_CALL_TXT				"Invalid Data Provided By Application Level"

#define	agnMAX_SESSION_REACHED					0x4082
#define	agnMAX_SESSION_REACHED_TXT				"Maximum Agnos Sessions Reached"

#define	agnSESSION_CLOSED						0x4083
#define	agnSESSION_CLOSED_TXT					"Session Not Opened"

#define agnINTERRUPTED							0x4084
#define	agnINTERRUPTED_TXT						"Session Interrupted By User"

#define agnMEMORY_EXCEEDED						0x4085
#define	gnMEMORY_EXCEEDED_TXT					"Agnos DataBase Out of Memory"

////////////////////////////////////////////////
// Payment Errors for Interface to selection
//			HIGH BYTE			LOW BYTE
// Module	0 1 
// Interface	0 0 0 0 0 1 	
// Severity						x x 
// Code								x x	x x x x
#define	agnSW_9000								0x4100
#define	agnSW_9000_TXT							"Normal Processing"

#define	agnSW_6283								0x4101
#define	agnSW_6283_TXT							"Selected File Invalidated"

#define	agnSW_6A81								0x4102
#define	agnSW_6A81_TXT							"Card Blocked or Command Not Supported"

#define	agnSW_6A82								0x4103
#define	agnSW_6A82_TXT							"File Not Found"

#define	agnSELECTION_ERROR						0x4104
#define	agnSELECTION_ERROR_TXT					"Application Not Selected"

/**@}*/

//---------------------------------------------------------
//			Primitives
//---------------------------------------------------------
DLLEXPORT tString agnGetStringError( // Return corresponding error's string. "" if error is not defined
	tWord error
);

#ifdef __cplusplus
}
#endif

#endif /*AGNOSERRORS_H_*/


