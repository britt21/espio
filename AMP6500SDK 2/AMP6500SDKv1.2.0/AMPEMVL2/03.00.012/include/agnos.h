// NAME.......  agnos.h
// PURPOSE....  Portable and multiconfiguration EMV kernel
// PROJECT....  AGNOS
// REFERENCES.	--
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//

#ifndef AGNOS_H_
#define AGNOS_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------
//			Include Files
//---------------------------------------------------------
//---- Local Headers ----
#include "agnoserrors.h"
//---- Agnos Framework Headers ----
#include "agnosdatabase.h"
//---- Global Headers ----
#include "gpi_agnos_framework_globals.h"

//---------------------------------------------------------
//            Standard interface - Data Structures
//---------------------------------------------------------
//

/** @mainpage Agnos EMV Library
 * This page presents the Agnos API.
 *
 * Agnos is an EMV Level2 library that is:
 * 		- Testable;
 * 		- Dual;
 * 		- Portable;
 * 		- Multi-configuration;
 *
 * To learn the Agnos API, this documentation is split up into 4 sections:
 *
 * 		- @ref Library "EMV Structure and Primitives"
 * 		- @ref Selection "EMV Selection Structure and Primitives"
 * 		- @ref Errors "EMV Errors"
 * 		- @ref Types "EMV Types"
 *
 * 	The API is developed in ANSI C and available on Linux, Windows, MacOS.
 *
 *
 *
 *
 * Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
 *
 */


/**
 * \addtogroup Library
 * @{
 * @file agnos.h
 * @brief Provides a set of data structure, primitives, types and errors to support EMV transaction flows.
 *
 */

/** \defgroup Structure	Data Structure
 * @{
 * @file agnos.h
 * @brief Provides a C data structure to manage EMV transaction sessions
 * This structure is used by Level3 to provide the kernel with a transaction context
 * It is initialized from a TERMINAL context and a PROCESSING context independent from Agnos
 */

// Structure used by Level3 to provide the kernel with a transaction context
// This structure is initialized from a terminal context AND a processing context
// See agnostypes.h also and ABC's product documentation
//
#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	/** If bTRUE, TAC/IAC default processing is skipped if unable to go online*/
	tBoolean				mSkipTACIACDefault;
	/** If bTRUE, TAC processing is performed*/
	tBoolean				mTAC;
	/** If bTRUE, Floor Limit Checking is performed*/
	tBoolean				mFloorLimitChecking;
	/** If bTRUE, RTS is performed*/
	tBoolean				mRandomTransactionSelection;
	/** If bTRUE, Velocity Checking is performed*/
	tBoolean				mVelocityChecking;
	/** If bTRUE, Default TDOL is supported*/
	tBoolean				mDefaultTDOL;
	/** TDOL length*/
	tByte					mDefaultTDOLLen;
	/**Tag 0x97*/
	tByte					mDefaultTDOLValue[TDOL_MAX_LENGTH];
	/** If bTRUE, Default DDOL is supported*/
	tBoolean				mDefaultDDOL;
	/** DDOL length*/
	tByte					mDefaultDDOLLen;
	/**Tag 0x9F49 or 0x9F69 (UDOL for contactless)*/
	tByte					mDefaultDDOLValue[DDOL_MAX_LENGTH];
	/**Terminal Action Code - Denial*/
	tTVR 					mTACDenial; 
	/**Terminal Action Code - Online*/
	tTVR 					mTACOnline; 
	/**Terminal Action Code - Default*/
	tTVR 					mTACDefault;
	/**Tag 0x9F1B*/
	tAmount		 			mTerminalFloorLimit;
	/**See EMV Book III, TRM section - Random Transaction Selection*/
	tPercentage  			mTargetPercentage;
	/**See EMV Book III, TRM section - Random Transaction Selection. Same transaction currency exponent as 0x9F02*/
	tAmount		  			mThresholdValue;
	/**See EMV Book III, TRM section - Random Transaction Selection*/
	tPercentage  			mMaxTargetPercentage;
	/**if bTRUE, pin may be bypassed when requested*/
	tBoolean				mPINByPass;
	/**bTRUE when merchant manually requested transaction to go online*/
	tBoolean				mForcedOnline;

	/**Tag 0x9A*/
	tNumericDate			mTransactionDate[3];
	/**Tag 0x9F21*/
	tNumericDate			mTransactionTime[3];
	/**Tag 0x9F35*/
	tTerminalType			mTerminalType;
	/** Transaction language*/
	tByte					mLanguage;
	/** PIN entry delay in second*/
	tCounter				mPinTimeOut;
	/** CDAMode1, CDAMode2 and CDAMode3 only*/
	tCDAType				mCDAType;
	/**if bTRUE, Terminal Risk Management is performed even if ICC doesn't request it*/
	tBoolean				mForceTRM;

	/**Tag 0x5F57*/
	tByte					mAccountType;
	/**Tag 0x9F39*/
	tByte					mPOSEntryMode;
	/**Tag 0x9F41*/
	tCounter				mTransactionSequenceCounter;
	/**Tag 0x9F1D*/
	tByte					mTerminalRiskManagementData[8];
	/**Tag 0x9F3A*/
	tAmount					mAmountReferenceCurrency;
	/**Tag 0x9F3C*/
	tByte					mTransactionReferenceCurrencyCode[2];
	/**Tag 0x9F3D*/
	tByte					mTransactionReferenceCurrencyExponent;
	/**Tag 0x9F1A*/
	tByte 					mTerminalCountryCode[2];
	/**Tag 0x5F2A*/
	tByte 					mTransactionCurrencyCode[2];
	/**Tag 0x5F36*/
	tByte 					mTransactionCurrencyExponent;
	/**Tag 0x9F33*/
	tByte 					mTerminalCapabilities[3];
	/**Tag 0x9F40*/
	tByte 					mAdditionalTerminalCapabilities[5];
	/**Tag 0x9F09*/
	tByte 					mApplicationVersionNumber[2];
	/**Tag 0x9C*/
	tByte					mTxnType;
	/**Tag 0x9F1C*/
	tByte					mTerminalIdentification[8];
	/**Tag 0x9F1E*/
	tByte					mIFDSerialNumber[8];
	/**Tag 0x9F01*/
	tByte					mAcquirerIdentifier[6];
} tTransactionalContext;
#ifdef PACKING
#pragma pack()
#endif

/**@}*/


/** \defgroup Behavior Primitives
 * @{
 * @file agnos.h
 * @brief Provides a set of C primitives to manage EMV transaction sessions
 */

//---------------------------------------------------------
//            Standard interface - Primitives
//---------------------------------------------------------
//
//---------------------------------------------------------
//            Standard interface - Mandatory Primitives
//---------------------------------------------------------
//

/**
 * @brief Opens a session and initializes Agnos' data structure from a transaction context provided by application level and resets internal parameters.
 * A session - and related EMV tags - lives until it's been explicitly closed.
 * @param[in] smartcardReaderName
 * @param[in] pinPadName
 * @param[in] applicationId
 * @param[in] txnContext context provided by the payment application
 * @param[in] DirectExecution bTRUE: EMV transaction is performed until GenAC; bFALSE: EMV transaction is performed between Select and GPO
 * @param[in] setEMVTag if bTRUE, set EMV tags in kernel database
 * @param[out] session session identifier returned by the kernel to be used for subsequent primitives calls
 * @param[in] activate software clipping into Agnos
 * @param[in] activate low level clipping
 * @return value in:
 * 		- agnMAX_SESSION_REACHED: no more session slot available in the kernel
 * 		- agnSESSION_CLOSED: invalid txnContext, session, transaction type, or terminal type provided by calling application. Session is automatically closed
 * 		- agnINVALID_SERVICE_CALL: invalid date or time
 * 		- agnNO_ERROR: normal case
 *
 */
DLLEXPORT tAgnosError agnOpenSession(
	const tString smartcardReaderName,
	const tString pinPadName,
	const tString applicationId,
	const tTransactionalContext *txnContext,
	tBoolean DirectExecution,
	tBoolean setEMVTag,
	tSessionId *session,
	tBoolean clipping,
	tBoolean sred
);

/**
 *@brief Closes all sessions. Multiple session feature is used (for now) only for performance matters. No concurrency is managed but multiple sessions can live.
 * Subsequently, this primitive close all opened sessions. In _AGNOSDEBUG_ mode, Agnos context is dumped.
 * @note in the current version, all opened sessions are closed on this call
 * @param[in] session session to be closed
 * @return value in:
 * 		- agnINVALID_SERVICE_CALL: invalid session provided by calling application
 * 		- agnNO_ERROR: normal case
 *
 */
DLLEXPORT tAgnosError agnCloseSession	(
	tSessionId session
);

 /**
  *@brief Get all tags from AgnosDB.
  * @note a session shall be opened
  * @param[in] session current session
  * @param[in] buffer	buffer receiving tags
  * @param[in] maxLength	maximum buffer's length receiving tags
  * @param[out] actualLength 	actual data length written into buffer
  *
  * @return value in:
  * 		- agnINVALID_SERVICE_CALL: invalid session provided by calling application
  * 		- agnNO_ERROR: normal case
  *
  */
DLLEXPORT tAgnosError agnGetAllTags	(
 	tSessionId session,
 	tByte *buffer,
 	tWord maxLength,
 	tWord *actualLength
 );

 /**
  * @brief Sets strategy for EMV tags storage and updates
  * @note
  * @param[in] session current session
  * @param[in] strategy value in:
  *
  *			- STANDARD				0x00
  *			- MASTERCARD_PAYPASS	0x01
  *			- AMEX_EXPRESSPAY		0x02
  *			- DISCOVER_ZIP			0x03
  *			- VISA_PAYWAVE			0x04
  *
  * @return value in:
  * 	- agnINVALID_SERVICE_CALL: invalid session provided by calling application
  * 	- agnNO_ERROR: normal case
  *
  */
DLLEXPORT tAgnosError agnSetAgnosDataBaseStrategy	(
	tSessionId session,
	tByte strategy
);

/**
 * @brief Selects an application and return the FCI. This function may be used during mutual list application building
 * @note EMVCo Book III 6.5
 * @param[in] smartcardReaderName
 * @param[in] AID AID to be selected
 * @param[in] AIDLen
 * @param[in] next
 * @param[out] FCI
 * @param[out] FCILen
 * @return value in:
 * 		- agnINVALID_SERVICE_CALL: invalid pointers provided by calling application
 * 		- agnSYSTEM_ERROR: EMV flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
 * 		- agnINTERRUPTED: user stopped transaction
 * 		- agnEMV_ERROR: SW1SW2 different from 0x9000. Status Word trails FCI (2 last bytes)
 * 		- agnNO_ERROR: normal case
 *
 */
DLLEXPORT tAgnosError agnSelect (
	const tString smartcardReaderName,
	const tByte *AID,
	tByte AIDLen,
	tBoolean next,
	tByte *FCI,
	tWord *FCILen
);


/**
 * @brief Starts an EMV session and stop depending on DirectExecution setting. Proceed to:
 * 				- TVR and TSI initialization
 * 				- Application Selection from the final selection's result
 * 				- GPO
 * 				- Read Application Data
 *
 *	If mDirectExecution == bTRUE, then perform subsequent processing to reach first GenAC and to provide a CID to calling application level
 *	Else call stops before GPO.
 *	If mDirectExecution == bTRUE, the processing will be stopped depending on mExitState that has been set after agnOpenSession call
 *
 *	9F02 and 9F03 are set accordingly.
 *
 *  If an error occurs, application level shall close the session.
 *
 * @note EMVCo Book III 4.2. See below for more details
 * @param[in] session current session
 * @param[in] amount transaction amount
 * @param[in] cashBack transaction cash back if any
 * @param[in] AID AID to be selected at final select
 * @param[in] AIDLen
 * @param[out] CID Cryptogram Information Data (ARQC, TC, or AAC) provided by ICC
 * @return value in (session shall be closed when any error occurs):
 * 		- agnINVALID_SERVICE_CALL: session, CID not defined
 * 		- agnSELECTION_ERROR: SW1SW2 different from 0x9000
 * 		- agnSYSTEM_ERROR: EMV flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
 * 		- agnINTERRUPTED: user stopped transaction
 * 		- agnEMV_ERROR: card response different from normal flow
 * 		- agnICC_MISSING: mandatory tag(s) missing in ICC
 * 		- agnICC_FORMAT_ERROR: invalid FCI or erroneous tag found in ICC
 * 		- agnUNCOMPLETE_TLV_PARSING : erroneous tag found in ICC
 * 		- agnREDUNDANT_TAG: tag occurred twice in ICC
 * 		- agnPROCEED_TO_NEW_SELECTION: conditions of used not satisfied returned at GPO time, normal case
 * 		- agnCVM_PROCESS_FAILED : CVM execution failed
 * 		- agnCVM_UNKNOWN : CVM not managed
 * 		- agnTXN_ACCEPTED: normal case
 * 		- agnTXN_REJECTED: normal case
 * 		- agnTXN_ONLINE: normal case
 * 		- agnSERVICE_NOT_ALLOWED: normal case
 * 		- agnNO_ERROR: normal case when mDirectExecution == FALSE (application level retrieves the control of the EMV flow)
 *
 * 		Important: terminal shall inspect CID to detect whether transaction requires an advice (when supported by terminal). Refer to payment system rules. For fall back rules see also payment system rules
 *
 *	CID Bit map (see also EMV4.2 book III section 6.5.5.4):
 *		- Bitmap										b8		b7		b6		b5		b4		b3		b2		b1
 *		- CID											x		x		-		-		-		-		-		-
 *		- AAC											0		0		-		-		-		-		-		-
 *		- TC											0		1		-		-		-		-		-		-
 *		- ARQC											1		0		-		-		-		-		-		-
 *		- RFU											1		1		-		-		-		-		-		-
 *		- Payment System-specific cryptogram			-		-		-		-		x		-		-		-
 *		- No advice required							-		-		-		-		0		-		-		-
 *		- Advice required								-		-		-		-		1 		-		-		-
 *		- Reason/advice code							-		-		-		-		-		x		x		x
 *		- No information given							-		-		-		-		-		0		0		0
 *		- Service not allowed							-		-		-		-		-		0		0		1
 *		- PIN try limit exceeded						-		-		-		-		-		0		1		0
 *		- Issuer authentication failed					-		-		-		-		-		0		1		1
 *		- Other values RFU								-		-		-		-		-		1		x		x
 *
 *
 */
DLLEXPORT tAgnosError agnInitiateEMVTransaction (
	tSessionId session,
	const tAmount *amount,
	const tAmount *cashBack,
	const tByte *AID,
	tByte AIDLen,
	tByte *CID
);

/**
 * @brief Completes EMV transaction:
 *				- Extracts 91, 71, and 72 tags from issuer's response (other tags are ignored and no error raised)
 *				- If unable to go online, calculates a CID to be provided to ICC and initializes EMV Tag 8A
 *				- Parses, executes scripts, and reports scripts executions
 *				- Authenticates the issuer
 *
 * After completion, the application may retrieve tags for data capture purposes and then closes the session
 *
 * @note EMVCo Book III 4.2. See below for more details
 * @param[in] session current session
 * @param[in] ARC Authorization Response Code depending on the issuer's response code received. Example: [0x30,0x35] when DE39=05. [0x00,0x00] if unable to go online
 * @param[in] CID TC or AAC depending on issuer's response code. Null if unable to go online
 * @param[out] CID TC or AAC provided by ICC at 2nd GenAC time
 * @param[in] issuerResponse  Issuer's data embedded into the DE55, i.e. 91, 71, and 72 tags. Null if unable to go online
 * @param[in] issuerResponseLen  maximum length is 256. 0 if unable to go online
 * @param[in] unableToGoOnline indicates whether or not application was able to go online (on an ARQC situation)
 * @return value in (session shall be closed when any error occurs):
 * 		- agnINVALID_SERVICE_CALL: session, ARC, CID or issuer's response (on online case) not defined
 * 		- agnSYSTEM_ERROR: EMV flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
 * 		- agnINTERRUPTED: user stopped transaction
 * 		- agnEMV_ERROR: authentication failed
 * 		- agnICC_FORMAT_ERROR: issuer authentication data leads to an erroneous length of data
 * 		- agnTXN_ACCEPTED: normal case
 * 		- agnTXN_REJECTED: normal case
 * 		- agnSERVICE_NOT_ALLOWED: normal case
 *
 * 		Important: terminal shall inspect CID to detect whether transaction requires an advice (when supported). Refer to payment system rules. See above for CID bitmap
 */
#ifdef _AGNOSCPL_
DLLEXPORT tAgnosError agnCompleteEMVTransaction (
	tSessionId session,
	tARC ARC,
	tByte *CID,
	const tByte *issuerResponse,
	tWord issuerResponseLen,
	tBoolean unableToGoOnline
);
#endif

//---------------------------------------------------------
//            Standard interface - Optional Primitives (may be used by application level when mDirectExecution==bFALSE)
//---------------------------------------------------------
//
//---------------------------------------------------------
//            agnGetProcessingOptions()
//---------------------------------------------------------
//  Initiate application processing with card. VMode is used to support VIUDS
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2
///
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		agnSYSTEM_ERROR: application selection leads to an unexpected error  (card removed, memory failure, dummy card response, ...)
//		agnINTERRUPTED: user stopped transaction
//		agnEMV_ERROR: card response different from normal flow
//		agnPROCEED_TO_NEW_SELECTION: ICC returned 0x6985 on GPO
//		agnICC_MISSING: AIP or AFL are missing
//		agnREDUNDANT_TAG: an existing tag has been found in FCI
//		agnICC_FORMAT_ERROR: a TLV is invalid in term of length in the FCI
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnGetProcessingOptions (
	tSessionId session,	// In: Kernel's session
	tBoolean VMode,		// In: bTRUE if VIUDS used
	tByte *tmplt		// Out: template used for GPO response
);

//---------------------------------------------------------
//            agnReadApplicationData()
//---------------------------------------------------------
//  Implement read record sequences from AFL retrieve at GPO time
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		agnSYSTEM_ERROR: application selection leads to an unexpected error  (card removed, memory failure, dummy card response, ...)
//		agnINTERRUPTED: user stopped transaction
//		agnEMV_ERROR: card response different from normal flow
//		agnICC_FORMAT_ERROR: AFL information are invalid
//		agnREDUNDANT_TAG: an existing tag has been found in ICC record
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnReadApplicationData (
	tSessionId session	// In: Kernel's session
);

//---------------------------------------------------------
//            agnPerformProcessingRestrictions()
//---------------------------------------------------------
//  Implement check consistency and restrictions calculation as defined per EMV
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		agnICC_FORMAT_ERROR: date are invalid (month > 12, day < 1, etc...)
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnPerformProcessingRestrictions (
	tSessionId session,	// In: Kernel's session
	tBoolean performConsistencyCheck	// In: allow to activate/deactivate
);

//---------------------------------------------------------
//            agnPerformSDA()
//---------------------------------------------------------
//	Perform Static Data Authentication
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		ODA errors in:
//			{	agnSDA_FAILED, 		agnICC_MISSING, 	agnNOT_FOUND, 		agnSIGN_LENGTH, 	agnEMV_ERROR,	agnDECRYPT_BEGIN,
//				agnDECRYPT_END, 	agnWRONG_CERTIF, 	agnCERT_EXPIRED, 	agnCERT_REVOKED, 	agnSIGN_DIGEST}
//
//		agnNO_ERROR: normal case (TVR is set accordingly)
//
DLLEXPORT tAgnosError agnPerformSDA (
	tSessionId session	// In: Kernel's session
);

//---------------------------------------------------------
//            agnPerformDDA()
//---------------------------------------------------------
//	Perform Dynamic Data Authentication
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2. See below for more details
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		ODA errors in:
//			{	agnSDA_FAILED, 		agnICC_MISSING, 	agnNOT_FOUND, 		agnSIGN_LENGTH, 	agnEMV_ERROR,	agnDECRYPT_BEGIN,
//				agnDECRYPT_END, 	agnWRONG_CERTIF, 	agnCERT_EXPIRED, 	agnCERT_REVOKED, 	agnSIGN_DIGEST}
//
//		agnNO_ERROR: normal case (TVR is set accordingly)
//
DLLEXPORT tAgnosError agnPerformDDA (
	tSessionId session,	// In: Kernel's session
	tBoolean fDDAMode	// In: Visa specific
);

//---------------------------------------------------------
//            agnPerformCDA()
//---------------------------------------------------------
//	Perform combined Dynamic Data Authentication / Application Cryptogram request.
//	In contacltess mode, should be jointly used with agnVerifyCDAIntegrity (once card out of field)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2. See below for more details
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		ODA errors in:
//			{	agnSDA_FAILED, 		agnICC_MISSING, 	agnNOT_FOUND, 		agnSIGN_LENGTH, 	agnEMV_ERROR,	agnDECRYPT_BEGIN,
//				agnDECRYPT_END, 	agnWRONG_CERTIF, 	agnCERT_EXPIRED, 	agnCERT_REVOKED, 	agnSIGN_DIGEST}
//
//		agnNO_ERROR: normal case (TVR is set accordingly)
//
DLLEXPORT tAgnosError agnPerformCDA (
	tSessionId session	// In: Kernel's session
);

//---------------------------------------------------------
//            agnPerformCVM()
//---------------------------------------------------------
//	Perform CVM as specified by EMVCo. Create, and set CVM results accordingly (9F34)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		agnSYSTEM_ERROR: CVM processing failed due to unexpected system behavior
//		agnINTERRUPTED: user stopped transaction
//		agnICC_MISSING: CVM list is missing (Tag 8E)
//		agnICC_FORMAT_ERROR: any EMV data format error (odd CVM list length, length = 0)
//		agnNO_ERROR: ICC's AIP doesn't support CVM processing
//		agnCVM_SUCCESSFUL: CVM executed with success
//		agnCVM_UNKNOWN: executed CVM is either signature or online PIN
//		agnCVM_NOT_SUCCESSFUL: any other case of CVM execution (failed is not a final status in EMV)
//
DLLEXPORT tAgnosError agnPerformCVM (
	tSessionId session	// In: Kernel's session
);

//---------------------------------------------------------
//            agnPerformTRM()
//---------------------------------------------------------
//	Perform Transaction Risk Management
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		agnNO_ERROR: normal case (TVR is set accordingly)
//
DLLEXPORT tAgnosError agnPerformTRM (
	tSessionId session,	// In: Kernel's session
	tTRMMethod method	// In: see agnostype.h
);

//---------------------------------------------------------
//            agnPerformTAA()
//---------------------------------------------------------
//	Perform Terminal Action Analysis and set an internal CID for subsequent the first GenAC
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnPerformTAA (
	tSessionId session, // In: Kernel's type
	tByte *CID 			// Out: Result of TAA
);

//---------------------------------------------------------
//            agnPerformFirstGenAC()
//---------------------------------------------------------
//	Perform Terminal Action Analysis and Card Action Analysis (through the GenAC)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		agnSYSTEM_ERROR: application selection leads to an unexpected error  (card removed, memory failure, dummy card response, ...)
//		agnINTERRUPTED: user stopped transaction
//		agnICC_MISSING: mandatory tags on GenAC are not sent by ICC (9F26, 9F27, 9F36)
//		agnICC_FORMAT_ERROR: data format on GenAC response is not valid
//		agnEMV_ERROR:: ICC decision at higher risk or ICC CID present in AAR
//		agnSERVICE_NOT_ALLOWED: normal case
//		agnTXN_REJECTED : normal case
//		agnTXN_ONLINE : normal case
//		agnTXN_ACCEPTED : normal cas
//
DLLEXPORT tAgnosError agnPerformFirstGenAC (
	tSessionId session,		// In: Kernel's session
	tBoolean performTAA,	// In: bTRUE will chain TAA calculation
	tByte *CID 				// In/Out: if performTAA = bFalse;
							// Out: if performTAA = bTRUE
);

//---------------------------------------------------------
//            Standard interface - Utils
//---------------------------------------------------------
//

//---------------------------------------------------------
//            agnGetDatabase()
//---------------------------------------------------------
//	Return current database storing tags
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tTagDataBase* agnGetDatabase(const tSessionId session);

//---------------------------------------------------------
//            agnIsEMVTagKnown()
//---------------------------------------------------------
//	Return bTRUE if tag is known. Else bFALSE
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		bFALSE: tag unknown
//		bTRUE: tag known
//
DLLEXPORT tBoolean agnIsEMVTagKnown(
	tWord tag	// In: Tag to search in db storing referenced tags
);

//---------------------------------------------------------
//            agnIsEMVTagPresent()
//---------------------------------------------------------
//	Return bTRUE if tag is present. Else bFALSE
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		bFALSE: tag not present
//		bTRUE: tag present
//
DLLEXPORT tBoolean agnIsEMVTagPresent(
	tSessionId session,	// In: Kernel's session
	tWord tag			// In: Tag to search in current session
);

//---------------------------------------------------------
//            agnIsEMVTagEmpty()
//---------------------------------------------------------
//	Return bTRUE if tag is present and empty. Else bFALSE
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		bFALSE: tag not empty
//		bTRUE: tag empty and present
//
DLLEXPORT tBoolean agnIsEMVTagEmpty(
	tSessionId session,	// In: Kernel's session
	tWord tag			// In: Tag to assess length
);

//---------------------------------------------------------
//            agnIsEMVTagNotEmpty()
//---------------------------------------------------------
//	Return bTRUE if tag is present and not empty. Else bFALSE
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		bFALSE: tag empty
//		bTRUE: tag not empty and present
//
DLLEXPORT tBoolean agnIsEMVTagNotEmpty(
	tSessionId session,	// In: Kernel's session
	tWord tag			// In: Tag to assess length
);

//---------------------------------------------------------
//            agnGetEMVTagLength()
//---------------------------------------------------------
//	Return tag's length if found
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		agnOPTIONAL_ICC_MISSING: requested tag is missing
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnGetEMVTagLength(
	tSessionId session,  // In: Kernel's session
	tWord      tag,      // In: See agnostypes.h. Tags values are word values (unsigned short)
	tByte     *length    // Out: Tag's length
);

//---------------------------------------------------------
//            agnGetEMVTag()
//---------------------------------------------------------
//	Return tag's length and value if found
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		agnOPTIONAL_ICC_MISSING: requested tag is missing
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnGetEMVTag(
	tSessionId session, 		// In: Kernel's session
	tWord tag,				// In: See agnostypes.h. Tags values are word values (unsigned short)
	tByte *length,				// Out: Tag's length
	tByte *value				// Out: Value shall be allocated by calling application
);

//---------------------------------------------------------
//            agnSetEMVTag()
//---------------------------------------------------------
//	Set tag's length and value. If not found, create it in Agnos database
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnSetEMVTag(
	tSessionId session,			// In: Kernel's session
	tWord tag,					// In: See agnostypes.h. Tags values are word values (unsigned short)
	tByte length,				// In: Length of tag's value
	const tByte *value			// In: Tag's length
);

//---------------------------------------------------------
//            agnOverWriteEMVTag()
//---------------------------------------------------------
//	Overwrite tag's length and value. If not found, create it in Agnos database
//	If length is greater than the current one then remove/create a new tag
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnOverwriteEMVTag(
	tSessionId session,			// In: Kernel's session
	tWord tag,					// In: See agnostypes.h. Tags values are word values (unsigned short)
	tByte length,				// In: Length of tag's value
	const tByte *value			// In: Tag's length
);

//---------------------------------------------------------
//            agnRemoveEMVTag()
//---------------------------------------------------------
//	Remove tag. If not found, nothing's done
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag supplied by application level
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnRemoveEMVTag(
	tSessionId session,			// In: Kernel's session
	tWord tag					// In: See agnostypes.h. Tags values are word values (unsigned short)
);

//---------------------------------------------------------
//            agnRemoveICCEMVTag()
//---------------------------------------------------------
//	Remove tag having ICC as origin
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnRemoveICCEMVTag(tSessionId session);

//---------------------------------------------------------
//            agnGetScriptResult()
//---------------------------------------------------------
//	Retrieve scripts results (since no EMV tag exists).
//
//	Note: Maximum buffer size required is 200 bytes (5 bytes per script are required as per EMV specifications)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: See EMVCo Book IV section 6.39
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session invalid or invalid tag/length supplied by application level
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnGetScriptResult(
	tSessionId session,			// In: Kernel's session
	tByte *scriptResults,		// Out: ScriptResults shall be allocated by calling application (2*MAX_SCRIPT size required)
	tByte *length				// Out: ScriptResults's length
);

//---------------------------------------------------------
//            agnGetStatusWord()
//---------------------------------------------------------
//	Return SW1SW2 word retrieved when kernel exchanges ADPU to ICC.
//	This call allows application level to manage specific cases (ie, fallback situations, ...)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values: Status Word (0x000 if error occurs)
//
DLLEXPORT tWord agnGetStatusWord(
	tSessionId session // In: Kernel's session
);

//---------------------------------------------------------
//            agnGetKernelStatus()
//---------------------------------------------------------
//	Return the kernel's current status indicating the last operation performed (SELECT, GPO, CVM, ...)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values: State (asREADY if error occurs)
//
DLLEXPORT tAgnosState agnGetKernelStatus(
	tSessionId session // In: Kernel's session
);

//---------------------------------------------------------
//            agnVersionNumber()
//---------------------------------------------------------
//	Return Agnos' version number
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values: String
//
DLLEXPORT tString agnGetVersionNumber(void);

//---------------------------------------------------------
//            agnResetTransactionLog()
//---------------------------------------------------------
//	Reset all transactions stored in the Agons' internal log (key/amount pairs)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values: void
//
DLLEXPORT void agnResetTransactionLog(void);

//---------------------------------------------------------
//            agnIsScriptExecuted()
//---------------------------------------------------------
//  Return bTRUE if any script was executed at completion time
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values: Boolean (bFALSE if error occurs)
//
DLLEXPORT tBoolean agnIsScriptExecuted(
	tSessionId session // In: Kernel's session
);

//---------------------------------------------------------
//            agnSetAuthorizedAmount()
//---------------------------------------------------------
//	Notify the kernel with the actual transaction amount
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//	
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session, or amount invalid
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnSetAuthorizedAmount(
	tSessionId session,			// In: Kernel's session
	const tAmount *amount		// In: New amount value (ajusted during the EMV flow)
); 

//---------------------------------------------------------
//            agnSetOtherAmount()
//---------------------------------------------------------
//	Notify the kernel with the other amount (ie, cashback amount - when needed).
//	As per EMVCo specs, other amount is added to authorized amount
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//	
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session, or amount invalid
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnSetOtherAmount(
	tSessionId session,			// In: Kernel's session
	const tAmount *amount		// In: New amount value (ajusted during the EMV flow)
); 

//---------------------------------------------------------
//            agnSetDateTime()
//---------------------------------------------------------
//	Set Date and Time
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session, date or time
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnSetDateTime(
	tSessionId session,			// In: Kernel's session
	const tByte *date,			// In: Date on 3 bytes [0..2] YYMMDD
	const tByte *time			// In: Time on 3 bytes [0..2] HHMMSS
);

//---------------------------------------------------------
//            agnSetAID()
//---------------------------------------------------------
//	Set kernel with an AID
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session, or AID invalid
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnSetAID(
	tSessionId session,			// In: Kernel's session
	const tByte *AID,			// In: AID
	const tWord AIDLen			// In: AID's length
);

//---------------------------------------------------------
//            agnSetAgnosDatabase()
//---------------------------------------------------------
//	Set Tags in Agnos database for the corresponding session.
// Use this primitive instead of transacitonal context's EMV tags
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session, date or time
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnSetAgnosDatabase(
	tSessionId session,			// In: Kernel's session
	const tByte *TLV,			// In: TLV stream
	const tWord TLVLen			// In: stream's length
);

//---------------------------------------------------------
//            agnSetExitState()
//---------------------------------------------------------
//	Set the state to exit when reached during agnInitiateEMVTransaction (SELECT, GPO, CVM, ...)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session, date or time
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError  agnSetExitState(
	tSessionId session, // In: Kernel's session
	tAgnosState exitState
);

//---------------------------------------------------------
//            agnSetParsingCallback()
//---------------------------------------------------------
//	Set a callback to parse ICC tags during read record sequence (after each APDU)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session, date or time
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnSetParsingCallback(
	tSessionId session,					// In: Kernel's session
	const tGetDataCallback callback,	// In: Callback
	tBoolean before						//
);

//---------------------------------------------------------
//            agnSetStateCallback()
//---------------------------------------------------------
//	Set a callback to process each Agnos' state in addition to the standard flow
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session, date or time
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnSetStateCallback(
	tSessionId session,				// In: Kernel's session
	const tStateCallback callback	// In: Callback
);

//---------------------------------------------------------
//            agnIsTagInPDOL()
//---------------------------------------------------------
//  Return bTRUE if tag exists in PDOL and its len if tByte* is valid
//
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values: Boolean (bFALSE if error occurs)
//
DLLEXPORT tBoolean agnIsTagInPDOL(
	tSessionId session,	// In: Kernel's session
	tByte high,			// In: Tag's high nibble
	tByte low,			// In: Tag's low nibble
	tByte *len			// Out: Tag's len
);

//---------------------------------------------------------
//            agnIsTagInDOL()
//---------------------------------------------------------
//  Return bTRUE if tag exists in DOL and its len if tByte* is valid
//
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values: Boolean (bFALSE if error occurs)
//
DLLEXPORT tBoolean agnIsTagInDOL(
	tSessionId session,	// In: Kernel's session
	tWord dol,			// In: dol
	tByte high,			// In: Tag's high nibble
	tByte low,			// In: Tag's low nibble
	tByte *len			// Out: Tag's len
);


//---------------------------------------------------------
//            agnORTVR()
//---------------------------------------------------------
//   Perform value | TVR[TVRPosition]. TVRPosition is 0 based
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values: --
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnNO_ERROR: normal case (TVR is set accordingly)
//
DLLEXPORT tAgnosError agnORTVR(
	tSessionId session,	// In: Kernel's session
	tByte TVRPosition, 	// In: 0 based position
	tByte value			// In: Value to OR
);

//---------------------------------------------------------
//            agnORAgnosTVR()
//---------------------------------------------------------
//   Perform value | AgnosTVR[AgnosTVRPosition]. AgnosTVRPosition is 0 based
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values: --
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnNO_ERROR: normal case (Agnos TVR is set accordingly)
//
DLLEXPORT tAgnosError agnORAgnosTVR(
	tSessionId session,		// In: Kernel's session
	tByte AgnosTVRPosition, // In: 0 based position
	tByte value				// In: Value to OR
);

//---------------------------------------------------------
//            agnSetAgnosTVR()
//---------------------------------------------------------
//   Set AgnosTVR[AgnosTVRPosition]. AgnosTVRPosition is 0 based
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values: --
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnNO_ERROR: normal case (Agnos TVR is set accordingly)
//
DLLEXPORT tAgnosError agnSetAgnosTVR(
	tSessionId session,		// In: Kernel's session
	tByte AgnosTVRPosition, // In: 0 based position
	tByte value				// In: Value to Set
);

//---------------------------------------------------------
//            agnGetData()
//---------------------------------------------------------
//	Get data from card and store it in kernel database if tag available
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnSYSTEM_ERROR: emv flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
//		agnINTERRUPTED: user stopped transaction
//		agnSESSION_CLOSED: invalid transactional context provided by calling application. Session is closed
//		agnEMV_ERROR: requested tag not is not valid
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnGetData(
	tSessionId session, 	// In: Kernel's session
	tByte hghP1,			// In: Highest byte of the tag to get or 00
	tByte lowP2,			// In: Lowest byte of the tag to get
	tByte *length,			// Out: Length read
	tByte *value			// Out: Value shall be allocated by calling application (MAX = 255)
);

//---------------------------------------------------------
//            agnPutData()
//---------------------------------------------------------
//	Put data to card
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnSYSTEM_ERROR: emv flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
//		agnINTERRUPTED: user stopped transaction
//		agnSESSION_CLOSED: invalid transactional context provided by calling application. Session is closed
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnPutData(
	tSessionId session,		// In: Kernel's session
	tByte hghP1,			// In: Highest byte of the tag to get or 00
	tByte lowP2,			// In: Lighest byte of the tag to get
	tByte length,			// In: Length to write
	const tByte *value		// In: Value to write
);

//---------------------------------------------------------
//            agnBuildDOL()
//---------------------------------------------------------
//	Build DOL
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnNO_ERROR : normal case
//
DLLEXPORT tAgnosError agnBuildDOL(
	tSessionId session,	// In: Kernel's session
	tWord tag			// In: tag corresponding to DOL
);

//---------------------------------------------------------
//            agnGetCAKeyModulusLength()
//---------------------------------------------------------
//	Retrieve public key CA certificate's modulus length
////
//  Visibility: Public
//  Hypothesis: --
//  Reference: --9
//
//	Returned values:
//
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnGetCAKeyModulusLength(
	tSessionId session,			// In: Kernel's session
	tByte *length				// Out: CA PK modulus length
);

//---------------------------------------------------------
//            agnGetIssuerKeyModulusLength()
//---------------------------------------------------------
//	Retrieve public key Issuer certificate's modulus length
////
//  Visibility: Public
//  Hypothesis: --
//  Reference: --9
//
//	Returned values:
//
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnGetIssuerKeyModulusLength(
	tSessionId session,			// In: Kernel's session
	tByte *length				// Out: Issuer PK modulus length
);

//---------------------------------------------------------
//            agnGetICCKeyModulusLength()
//---------------------------------------------------------
//	Retrieve public key ICC certificate's modulus length
////
//  Visibility: Public
//  Hypothesis: --
//  Reference: --9
//
//	Returned values:
//
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnGetICCKeyModulusLength(
	tSessionId session,			// In: Kernel's session
	tByte *length				// Out: ICC PK modulus length
);

//---------------------------------------------------------
//            agnIsCLIPPINGModeSet()
//---------------------------------------------------------
//	Return CLIPPING mode
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//		bFALSE: CLIPPING if off
//		bTRUE: CLIPPING is on
//
//
DLLEXPORT tBoolean agnIsCLIPPINGModeSet(
	tSessionId session // In: Kernel's session
);

//---------------------------------------------------------
//            agnIsSREDModeSet()
//---------------------------------------------------------
//	Return SRED mode
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//		bFALSE: SRED if off
//		bTRUE: SRED is on
//
//
DLLEXPORT tBoolean agnIsSREDModeSet(
	tSessionId session // In: Kernel's session
);

#ifdef _AGNOSCL_
//---------------------------------------------------------
//            agnOpenSessionCL()
//---------------------------------------------------------
//	Open a session in a contactless mode and initialize Agnos' data structure from a
//	transactional context provided by application level and reset internal parameters
//	A session - and related EMV tags - lives until it's been explicitly closed.
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnMAX_SESSION_REACHED: no more session slot available in the kernel
//		agnSESSION_CLOSED: invalid transactional context provided by calling application. Session Closed
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnOpenSessionCL(
	const tString smartcardReaderName,			// In: Smartcard device name
	const tString pinPadName,					// In: Secured PIN entry device name
	const tString applicationId, 				// In: Application Id
	const tTransactionalContext *txnContext, 	// In: Context provided by the payment application
	tBoolean setEMVTag,							// In: set EMV data in kernel database (from transacitonal context)
	tSessionId *session,						// Out: Session returned by the kernel to be used when primitives are called
	tBoolean clipping,							// In: activate software clipping into Agnos
	tBoolean sred								// In: activate low level clipping
);

//-----------------------------------------------------
//            agnResetSessionContext()
//---------------------------------------------------------
//	Reset a context in a contactless mode to allow a restart of the same session
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnSESSION_CLOSED: invalid transactional context provided by calling application. Session Closed
//		agnNO_ERROR: normal case
//
DLLEXPORT tAgnosError agnResetSessionContext(tSessionId session /* In: Session to be reset */);

//---------------------------------------------------------
//            agnComputeCryptographicChecksum()
//---------------------------------------------------------
//  Implement a specific requirement for Mastercard
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: See M/Chip PayPass 3.1 section 5.2
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnSYSTEM_ERROR: emv flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
//		agnINTERRUPTED: user stopped transaction
//		agnICC_MISSING: mandatory tag(s) missing in ICC
//		agnREDUNDANT_TAG: an existing tag has been found in ICC record
//		agnICC_FORMAT_ERROR: a TLV is invalid in term of length
//		agnUNCOMPLETE_TLV_PARSING: a TLV is invalid in term of components
//		agnNO_ERROR : normal case
//
DLLEXPORT tAgnosError agnComputeCryptographicChecksum(
	tSessionId session // In: Kernel's session
);

//---------------------------------------------------------
//            agnExchangeRelayResistanceData()
//---------------------------------------------------------
//  Implement a specific requirement for Mastercard
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: See M/Chip PayPass 3.1 section 5.3
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnSYSTEM_ERROR: emv flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
//		agnINTERRUPTED: user stopped transaction
//		agnICC_FORMAT_ERROR: a TLV is invalid in term of length
//		agnNO_ERROR : normal case
//
DLLEXPORT tAgnosError agnExchangeRelayResistanceData(
	tSessionId session // In: Kernel's session
);

//---------------------------------------------------------
//            agnIsCDARequested()
//---------------------------------------------------------
//	Return bTRUE if CDA was requested at GenAC1
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2. See below for more details
//
//	Returned values:
//
//		bFALSE: CDA not requested
//		bTRUE: CDA requested
//
DLLEXPORT tBoolean agnIsCDARequested (
	tSessionId session	// In: Kernel's session
);

//---------------------------------------------------------
//            agnIsCDAPerformed()
//---------------------------------------------------------
//  Return bTRUE if CDA was performed
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values: Boolean (bFALSE if error occurs)
//
DLLEXPORT tBoolean agnIsCDAPerformed(
	tSessionId session	// In: Kernel's session
);

//---------------------------------------------------------
//            agnSetCDAType()
//---------------------------------------------------------
//
//	Set internal CDA type (mode1, mode 2 or mode 3). If type is different from supported value CDA type is force to mode 3
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnNO_ERROR: normal case (TVR is set accordingly)
//
DLLEXPORT tAgnosError agnSetCDAType (
	tSessionId session, // In: Kernel's session
	tCDAType type		// In: CDA type
);

//---------------------------------------------------------
//            agnSetPerformCDA()
//---------------------------------------------------------
//	Set internal flag to perform CDA without managing AIP and setting TSI
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnNO_ERROR: normal case (TVR is set accordingly)
//
DLLEXPORT tAgnosError agnSetPerformCDA (
	tSessionId session,	// In: Kernel's session
	tBoolean flag		// In: bTRUE or bFALSE
);

//---------------------------------------------------------
//            agnPopForRecoverAC()
//---------------------------------------------------------
//	Get necessary data to prepare a subsequent recovery
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnNO_ERROR : normal case
//
DLLEXPORT tAgnosError agnPopForRecoverAC(
	tSessionId session,					// In: Kernel's session
	tByte *PDOL,						// Out: 9F38 related data
	tByte *PDOLLen,						// Out: Related length
	tByte *CDOL1,						// Out: 8C related data
	tByte *CDOL1Len,					// Out: Related length
	tByte *DRDOL,						// Out: 9F51 related data if doesn't exist DRDOLLen = 0
	tByte *DRDOLLen,					// Out: Related length
	tByte *referenceControlParameter	// Out: P1 at GenAC time
);

//---------------------------------------------------------
//            agnPushForRecoverAC()
//---------------------------------------------------------
//	Set necessary data to prepare a subsequent recovery
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnNO_ERROR : normal case
//
DLLEXPORT tAgnosError agnPushForRecoverAC(
	tSessionId session,					// In: Kernel's session
	tByte *PDOL,						// In: 9F38 related data
	tByte PDOLLen,						// In: Related length
	tByte *CDOL1,						// In: 8C related data
	tByte CDOL1Len,						// In: Related length
	tByte *UN							// In: 9F37 always on 4 bytes
);

//---------------------------------------------------------
//            agnPushGenAC1Response()
//---------------------------------------------------------
//	Set necessary data to prepare a subsequent CDA verification
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnSYSTEM_ERROR : invalid generate AC1 length
//		agnNO_ERROR : normal case
//
DLLEXPORT tAgnosError agnPushGenAC1Response(
	tSessionId session,					// In: Kernel's session
	tByte *genAC1Response,				// In: Generate AC1 response
	tByte genAC1ResponseLen				// In: Generate AC1 response length
);

//---------------------------------------------------------
//            agnRecoverAC()
//---------------------------------------------------------
//	Implement transaction recovering, a specific requirement for Mastercard
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnSYSTEM_ERROR: emv flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
//		agnINTERRUPTED: user stopped transaction
//		agnICC_MISSING: mandatory tag(s) missing in ICC
//		agnICC_FORMAT_ERROR: a TLV is invalid in term of length
//		agnNO_ERROR : normal case
//
DLLEXPORT tAgnosError agnRecoverAC(
	tSessionId session,					// In: Kernel's session
	tByte ReferenceControlParameter,	// In: P1 at GenAC time
	tByte length,						// In: Data's length
	const tByte *value,					// In: Data to recover
	tByte *CID							// Out: Cryptogram Information Data resulting from GenAC
);

//---------------------------------------------------------
//            agnVerifyCDAIntegrity()
//---------------------------------------------------------
//	Verify the current CDA processing, This method shall always be performed after agnPerformFirstGenAC
//	The context is stored at this time to allow a back-to-back call
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnSYSTEM_ERROR: emv flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
//		ODA errors in:
//			{	agnSDA_FAILED, 		agnICC_MISSING, 	agnNOT_FOUND, 		agnSIGN_LENGTH, 	agnEMV_ERROR,	agnDECRYPT_BEGIN,
//				agnDECRYPT_END, 	agnWRONG_CERTIF, 	agnCERT_EXPIRED, 	agnCERT_REVOKED, 	agnSIGN_DIGEST}
//		agnNO_ERROR : normal case
//
DLLEXPORT tAgnosError agnVerifyCDAIntegrity(
	tSessionId session	// In: Kernel's session
);

//---------------------------------------------------------
//            agnVerifySDAIntegrity()
//---------------------------------------------------------
//	Verify the current SDA processing, This method shall always be performed after agnPerformFirstGenAC
//	The context is stored at this time to allow a back-to-back call
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnSYSTEM_ERROR: emv flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
//		ODA errors in:
//			{	agnSDA_FAILED, 		agnICC_MISSING, 	agnNOT_FOUND, 		agnSIGN_LENGTH, 	agnEMV_ERROR,	agnDECRYPT_BEGIN,
//				agnDECRYPT_END, 	agnWRONG_CERTIF, 	agnCERT_EXPIRED, 	agnCERT_REVOKED, 	agnSIGN_DIGEST}
//		agnNO_ERROR : normal case
//
DLLEXPORT tAgnosError agnVerifySDAIntegrity(
	tSessionId session,	// In: Kernel's session
	tBoolean vSDAMode	// In: Visa specific
);

//---------------------------------------------------------
//            agnVerifyCDAPublicKeyChain()
//---------------------------------------------------------
//	Verify the current Issuer public key and ICC public key.
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnINVALID_SERVICE_CALL: session not defined
//		agnSYSTEM_ERROR: emv flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
//		ODA errors in:
//			{	agnSDA_FAILED, 		agnICC_MISSING, 	agnNOT_FOUND, 		agnSIGN_LENGTH, 	agnEMV_ERROR,	agnDECRYPT_BEGIN,
//				agnDECRYPT_END, 	agnWRONG_CERTIF, 	agnCERT_EXPIRED, 	agnCERT_REVOKED, 	agnSIGN_DIGEST}
//		agnNO_ERROR : normal case
//
DLLEXPORT tAgnosError agnVerifyCDAPublicKeyChain(
	tSessionId session 	// In: Kernel's session
);

//---------------------------------------------------------
//            agnIsRemainderMissing()
//---------------------------------------------------------
//	Return whether or not a PK remainder is missing
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//		bFALSE: no remainder missing
//		bTRUE: remainder missing
//
//
DLLEXPORT tBoolean agnIsRemainderMissing(
	tSessionId session, 	// In: Kernel's session
	tWord* remainderType		// Out: remainder's tag missing
);

/**@}*/

/**@}*/

#endif /*_AGNOSCL_*/

#ifdef __cplusplus
}
#endif

#endif /*AGNOS_H_*/


