// -----------------------------------------------------------------------------------------------------------------
// NAME.......  gpi_agnos_framework_globals.h
// PURPOSE....  Generic Platform Interface - Globals symbols, options, and constants
// PROJECT....  GPI
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS�?, All Rights Reserved
//
// -----------------------------------------------------------------------------------------------------------------

#ifndef GPIGLOBALS_H_
#define	GPIGLOBALS_H_

#ifdef __cplusplus
extern "C" {
#endif

//==================================================================================================================
//			WARNING
//==================================================================================================================
// 			!!! Modifying this file requires to recompile all the framework !!!
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------

//==================================================================================================================
//      INCLUDES
//==================================================================================================================
#include <stdint.h>

//==================================================================================================================
// 		MACROS + DEFINES
//==================================================================================================================
#if (defined(_WIN32) || defined(WIN32))
	#define DLLEXPORT	__declspec(dllexport)
#else
	#define DLLEXPORT
#endif

#define _ACE_
//#define _ADAPTER_
#define	_AGNOSCL_
#define _AGNOSCPL_
#define	_AGNOSFMSG_
#define	_AGNOSISR_
#define	_AGNOSK_
//#define	_AGNOSTRACE_
//#define _AUTOMATION_
#define _DATA_EXCHANGE_
#define _DUAL_POLLING_
//#define _CONFIGURATOR_
//#define _EMBEDDED_
#define _LOG_
//#define PACKING
#define _RAW_FORMAT_ // Mandatory for EVAL4DEV
//#define _REPLAY_
//#define _TIME_STAMP_

// -----------------------------------------------------------------------------------------------------------------
// 	Constants for Size Optimization
// -----------------------------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------
// 	Configurable Shared RAM
// -----------------------------------------------------------------------------------------------------------------
#define SIZE_FOR_EMV_TAGS			11500 	// MANDATORY: 11.5kB to store all tags for a single transaction
#define SIZE_FOR_EMV_UNKNOWNTAGS	2500  	// MANDATORY: 2.5kB to store all unknowns tags for a single transaction
#define FREE_RAM_SIZE				3000	// MANDATORY: L3 implementation + house keeping in C2 (minimum = 3000). Maybe increased depending on L3 needs
#define SIZE_FOR_CL_DATA_OBJECT		10000	// set 1 if CL not supported
#define SIZE_FOR_PAYPASS_TORN		13500	// set 1 if not used

// -----------------------------------------------------------------------------------------------------------------
// Configurable Display
// -----------------------------------------------------------------------------------------------------------------
// String table
#define MAX_NB_LANGUAGE 			10 // 3
#define MAX_STRING_LENGTH			50
#define NB_EMV_STRINGS				35 //34
#define NB_INDIVIDUAL_STRINGS		0
#define NB_ACQUIRER_STRINGS			30 //26
#define NB_ISSUER_STRINGS			0
// Selection list
#define MAX_NUMBER_ITEMS			50
#define MAX_ITEM_NAME_LENGTH		100
// Global names (reader, pinpad, files, paths, ...)
#define MAX_NAME_LENGTH				125

// -----------------------------------------------------------------------------------------------------------------
// Configurable Logger
// -----------------------------------------------------------------------------------------------------------------
#ifdef _TIME_STAMP_
#define TIME_STAMP_BUFFER_SIZE		40000
#endif

#ifdef _LOG_
#define MAX_LOGDATA_BUFFER			4096
#else
#define MAX_LOGDATA_BUFFER			1
#endif

// -----------------------------------------------------------------------------------------------------------------
// Configurable EMV Library Agnos
// -----------------------------------------------------------------------------------------------------------------
#ifdef _AGNOSISR_
	#define MAX_SCRIPT_SIZE			128	// arbitrary
#else
	#define MAX_SCRIPT_SIZE         0
#endif

#ifdef  _AGNOSCPL_
#define ISSUER_RESPONSE_SIZE		(128 +  MAX_SCRIPT_SIZE) // DE55 only, eg tags 71/72/91, arbitrary
#endif

#define MAX_SUPPORTED_ADF			10
#define MAX_SCRIPT					20
#define DEFAULT_DEPTH				10 // Transaction log

#define TDOL_MAX_LENGTH				60 // Defined by PROCESSING configuration as default TDOL(previous value before RAM optimization: 252)
#define PDOL_MAX_LENGTH				252
#define DDOL_MAX_LENGTH				60 // Defined by PROCESSING configuration as default DDOL (previous value before RAM optimization: 252)
#define CDOL_MAX_LENGTH				252
#define DRDOL_MAX_LENGTH			252
#define DSDOL_MAX_LENGTH			252

#define MAX_REMAINING_FCI_LENGTH	200

// -----------------------------------------------------------------------------------------------------------------
// Configurable Data Model AgnosMW
// -----------------------------------------------------------------------------------------------------------------

#define	MAX_SUPPORTED_AID			30	// i.e. declared in PROCESSING file
#define MAX_KERNEL					25 	// i.e. declared in ENTRY POINT file and from kernel id 1 to kernel id 25
#define MAX_AID						15 	// i.e. declared in ENTRY POINT file and from aid id 1 to aid id 15 (MAX_AID means MAX_AID per kernel. Some certifications require up to 15 AIDs)

#define MAX_COMBINATION_PER_TRANSACTION_TYPE		65 // required value for entry point certification
#define MAX_SIMULTANEOUS_SESSION					MAX_COMBINATION_PER_TRANSACTION_TYPE

#define RAW_FORMAT_DATA_OBJECT_SIZE	400 // EVAL4DEV configuration

#define ONLINE_BUFFER_SIZE			3000 // may be adjusted

#define	MAX_KERNEL_PER_AID			MAX_KERNEL
#define MAX_DRL_SET					4

// -----------------------------------------------------------------------------------------------------------------
// Configurable Entry Point AgnosEP
// -----------------------------------------------------------------------------------------------------------------
#define MAX_SERVICES_PER_INTERFACE	(MAX_KERNEL - 1)
#define LIBRARY_FILE				"apps"
#define MAX_LIB_NAME                100
#define MAX_VERSION_LENGTH			100
#define MAX_AID_PER_SERVICE			10
#define MAX_KERNEL_ID_LEN			8

// -----------------------------------------------------------------------------------------------------------------
// Configurable Level3
// -----------------------------------------------------------------------------------------------------------------
#define TERMINAL_DATA_SIZE			44

#define	AGNOS_INI_SIZE				30
#define MAX_TRACE_DEPTH				5
#define	MAX_TRD_SIZE				500
#define	MAX_GENERIC_FILE			5
#define	MAX_FILE_NAME_LENGTH		50

#define MAX_DET_SIZE				2500

#define	PINPAD						"stdin"
#define INI_FILE					"agnos.ini"
#define	PATH						"./AGNOS/"
#define LANG						"lang.ini"

#define FILE_TERMINAL               "TERM.DAT"
#define FILE_PROCESSING             "PROC.DAT"
#define FILE_AID                    "AID.DAT"
#define FILE_ENTRY_POINT            "EP.DAT"
#define FILE_COMBINATION            "COB.DAT"


#define	CERT						"CAKeys"	// Binary file name for CAPK for EMV txn
#define	CRL							"CRL"		// Binary file name for revoked CAPK for EMV txn
#define	EFL							"EFL"		// Binary file name for exception PAN list for EMV txn
#define	TRACE						"txn"		// GPI logging

#define RID_LENGTH					5

#define MASTERCARD_RID				"\xA0\x00\x00\x00\x04"
#define VISA_RID					"\xA0\x00\x00\x00\x03"
#define AMEX_RID					"\xA0\x00\x00\x00\x25"
#define JCB_RID						"\xA0\x00\x00\x00\x65"
#define DISCOVER_RID_1				"\xA0\x00\x00\x01\x52"
#define DISCOVER_RID_2				"\xA0\x00\x00\x03\x24"
#define CUP_RID						"\xA0\x00\x00\x03\x33"

#define CANADA						"\x01\x24"

// Currency
#define	EURO						2424
#define USDOL						2112
#define CANDOL						292
#define	EURO_STR					"EUR"
#define USDOL_STR					"US$"
#define CANDOL_STR					"CAD$"

//==================================================================================================================
//      PRIMITIVES
//==================================================================================================================

#ifdef __cplusplus
}
#endif

#endif // _GPIGLOBALS_H_
