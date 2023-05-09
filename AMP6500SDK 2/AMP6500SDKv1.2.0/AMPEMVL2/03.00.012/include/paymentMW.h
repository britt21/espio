// NAME.......  paymentMW.h
// PURPOSE....  At the core of a transaction are tPaymentContext and tOutComeParameter structures. These structures are used by
//				applications to set preconditions and to get post conditions. Any information or data related to a transaction are
//				embedded here. This component comes with few primitives useful for application development.
// PROJECT....  AGNOSMW
// REFERENCES.	--
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//

#ifndef PAYMENTMW_H_
#define PAYMENTMW_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------
//			Include Files
//---------------------------------------------------------
//---- Local Headers ----
#include "datamngr.h"
#include "dataxchng.h"
//---- Agnos Framework Headers ----
#include "agnos.h"
//---- Global Headers ----
#include "gpi_agnos_framework_globals.h"

//---------------------------------------------------------
//			Definitions
//---------------------------------------------------------
#define CHIP_MODE                   0x05
#define MAG_MODE					0x90
#define FALLBACK_MODE				0x80
#define MANUAL_MODE                 0x01
#define EMV_CL_MODE                 0x07
#define MAG_CL_MODE                 0x91

#define PSE_DDF_NAME				"1PAY.SYS.DDF01"
#define PSE_DDF_LENGTH				14

#define PPSE_DDF_NAME				"2PAY.SYS.DDF01"
#define PPSE_DDF_LENGTH				14

#define ACCOUNT_TYPE_RANGE          10

typedef enum {
	ttPURCHASE,
	ttCASH,
	ttWITH_CASHBACK,
	ttREFUND,
	ttMANUAL_CASH,
	ttQUASI_CASH,
	ttDEPOSIT,
	ttINQUIRY,
	ttPAYMENT,
	ttTRANSFER,
	ttADMINISTRATIVE,
	ttHOUSE_KEEPING,
	ttRETRIEVAL,
	ttUPDATE,
	ttAUTHENTICATION,
	ttCASH_DISBURSEMENT,
	ttPRE_AUTHORIZATION,
	ttUNDEFINED
} tTransactionType;

typedef enum {
	atDEFAULT,
	atSAVINGS,
	atCHECKING,
	atCREDIT
} tAccountType;

// See Book A for following data definitions
typedef enum {
	spNO_START,

	spSTART_A,	// as per EMVCo contactless specifications
	spSTART_B,	// as per EMVCo contactless specifications
	spSTART_C,	// as per EMVCo contactless specifications - No used by external calling applications (internal start)
	spSTART_D,	// as per EMVCo contactless specifications

	// Amadis to generalize EMVCo's entrypoint architecture pattern
	spSTART_K,	// Agnos call for EMV contact transactions -> DEPRECATED
	spSTART_M,	// Agnos call for MAG stripe transactions -> DEPRECATED

	spSTART_L	// Agnos call for ManualKey entry transactions  -> DEPRECATED
} tStartingPoint;

typedef enum {
	ocNONE,
	ocTRY_ANOTHER_INTERFACE,
   	ocOFFLINE_APPROVED,
   	ocOFFLINE_DECLINED,
	ocOFFLINE_FAILED,
	ocOFFLINE_NOT_ACCEPTED,
	ocAPPROVED,
	ocDECLINED,
	ocFAILED,
	ocNOT_ACCEPTED,
	ocTRANSACTION_CANCELLED,
	ocSELECT_NEXT_NOT_ACCEPTED,
	ocSELECT_NEXT_RETRY,
	ocTRY_AGAIN,
	ocONLINE_REQUEST,
	ocEND_APPLICATION,
	ocNOT_EMV_CARD_POOLED
} tOutCome;

typedef enum {
	stCONTACT,
	stCONTACTLESS,
	stMAGSTRIPE,
	stMANUAL,
	stNUMBER_OF_INTERFACE,
} tInterface;

typedef enum {
	ipNONE,			// i.e. not applicable
	ipCONTACTCHIP,
	ipMAGSTRIPE
} tAlternateInterfacePreference;

typedef enum {
	rdNONE,			// i.e. not applicable
	rdEMV,
	rdANY
} tOnlineResponseData;

typedef enum {
	cvNONE,	// i.e. not applicable
	cvNO_CVM,
	cvOBTAIN_SIGNATURE,
	cvONLINE_PIN,
	cvCONFIRMATION_CODE_VERIFIED
} tCVM;

#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tOutCome 						mOutCome;

	tStartingPoint 					mStartingPoint;
	tOnlineResponseData				mOnlineResponseData;
	tCVM							mCVM;
	tBoolean						mUIReqOnOutcomePresent; // If bTRUE, found in DataExchange
	tBoolean						mUIReqOnRestartPresent; // If bTRUE, found in DataExchange
	tBoolean						mReceipt;
	tBoolean						mDRPresent;	// Data record. If present, found in DataExchange
	tBoolean						mDDPresent;	// Discretionary Data. If present, found in DataExchange
	tAlternateInterfacePreference	mAlternateInterfacePreference;
	tWord							mFieldOffReq;
	tWord							mRemovalTimeout;
} tOutComeParameter;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	////////////////////////////////////////////////////////////////////
	// Information provided by Level3
	tAmount				*mAmount;    					// EMV Tag 9F02 = "Amount, Authorized"  + "Amount, Other"
    tAmount				*mCashBack;						// EMV Tag 9F03 = "Amount, Other"
	tTransactionType	mTransactionType;				// EMV Tag 9C
	tNumericDate		mTransactionDate[3];			// EMV Tag 9A
	tNumericDate		mTransactionTime[3];			// EMV Tag 9F21
    tByte				mMerchantCustomData[20];		// EMV Tag 9F7C
	tByte 				mTransactionCurrencyCode[2];	// EMV Tag 5F2A
	tByte				mTransactionCurrencyExponent;	// EMV Tag 5F36
    tByte				mTransactionCategoryCode;		// EMV Tag 9F53
    tByte				mMerchantCategoryCode[2];		// EMV Tag 9F15
    tByte				mMerchantID[15];				// EMV Tag 9F16
    tBoolean            mForcedOnline;					// As per merchant decision
    char				mWorkingPath[2*MAX_NAME_LENGTH];

    ////////////////////////////////////////////////////////////////////
	// Information set by Payment System
    tBoolean            mEMVContact;		// by configuration (terminal)
    tBoolean            mEMVContactless;	// by configuration	(terminal)
    tBoolean            mMagstripe;			// by configuration	(terminal)

    tAmount				mAmountReferenceCurrency;				// EMV Tag 9F3A - not used yet
	tByte				mTransactionReferenceCurrencyCode[2];	// EMV Tag 9F3C - not used yet
	tByte				mTransactionReferenceCurrencyExponent;	// EMV Tag 9F3D - not used yet
	tByte				mTerminalRiskManagementData[8];			// EMV Tag 9F1D - not used yet
	tAccountType		mAccountType;							// EMV Tag 5F57 - payment application specific
	tByte				mPOSEntryMode;							// EMV Tag 9F39 - payment application specific

	tCounter			mTransactionSequenceCounter;
	tARC                mARC;	//Authorization Response Code, eg mapping from Issuer's Response Code (ISO8583:DE39)
    tBoolean            mUnableToGoOnline;

    ////////////////////////////////////////////////////////////////////
    // Information set by Payment Application (from Agnos primitives)
    tByte               mRID[RID_LENGTH];
	tADF				mADF;
	tByte				mADFOrderNumber;    // For a given configuration, AID's order number

    tBoolean			mAdvice;
    tBoolean			mBatchData;
    tBoolean			mReversal;

	////////////////////////////////////////////////////////////////////
    // Information set by EMV Library
	tSessionId			mSession;
	tByte 				mCID;				// Information used by Level3 to detect transaction's outcome requested by ICC
	
//	CID Bit map (see also EMV4.2 book III section 6.5.5.4)
//												b8		b7		b6		b5		b4		b3		b2		b1
//	AAC											0		0
//	TC											0		1
//	ARQC										1		0	
//	RFU											1		1
//	Payment System-specific cryptogram							x		x
//	No advice required															0
//	Advice required																1
//	Reason/advice code																	x		x		x
//	No information given																0		0		0
//	Service not allowed																	0		0		1
//	PIN try limit exceeded																0		1		0
//	Issuer authentication failed														0		1		1
//	Other values RFU																	1		x		x
//
//		Important: terminal shall inspect CID to detect whether transaction requires an advice (when supported by terminal)
//		Pls, refer to payment system rules
//

	////////////////////////////////////////////////////////////////////
	// Information calculated by Level3 once transaction is completed (from paymentMW primitives)
    tByte               mFinal9F02[6];
    tByte               mCVMResult[3];
    tByte               mTVR[5];
    tByte               mTSI[2];
    tByte               mAC[8];
    tByte               mUN[4];
    tByte               mAID[MAX_AID_LENGTH];
    tByte               mAIDLen;
    tByte               mPANSHA[20];
    tByte               mCardholderNameLen;
    tByte               mCardholderName[26];
    tByte               mAgnosTVR[AGNOS_TVR_SIZE];
#ifdef _AGNOSISR_
    tBoolean            mIsScriptExecuted;
    tByte            	mIssuerScriptResultLen;
    tByte            	mIssuerScriptResult[2*MAX_SCRIPT*sizeof(tScriptResult)];
#endif

	////////////////////////////////////////////////////////////////////
    // Level3 <-> Level2 communication
    tDataExchange		mDataExchange;

} tPaymentContext;
#ifdef PACKING
#pragma pack()
#endif

typedef void (*CtlsFlashCB)(void);

#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tDataExchangeType 	mDEType;		// In
	tByte 				mAPDUStatus;	// In
	tPaymentContext		*mPayment;		// In
	tDecision			mDecision;		// Out
	void*				mProprietary;	// In/Out
} tLevel3DataExchange;
#ifdef PACKING
#pragma pack()
#endif


//---------------------------------------------------------
//            Public Primitives
//---------------------------------------------------------
//---------------------------------------------------------
//            pmwGetPaymentMiddlewareVersion()
//---------------------------------------------------------
//	Get PaymentMW version
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT char* pmwGetPaymentMiddlewareVersionNumber(void);

//---------------------------------------------------------
//            pmwIntializePaymentContext()
//---------------------------------------------------------
//	Initialize a payment context. This primitive must be called before any transaction involving Agnos framework.
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void pmwInitializePaymentContext(tPaymentContext *ctx);

//---------------------------------------------------------
//            pmwIntializeOutComeParameter()
//---------------------------------------------------------
//	Initialize an outcome. This primitive must be called before any transaction involving Agnos framework.
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void pmwInitializeOutComeParameter(tOutComeParameter *outcome);

//---------------------------------------------------------
//            pmwGetLanguage()
//---------------------------------------------------------
//	Return language of the payment context
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//DLLEXPORT tLanguage pmwGetLanguage(tPaymentContext *ctx);
DLLEXPORT tByte pmwGetLanguage(tPaymentContext *ctx);

//---------------------------------------------------------
//            pmwSetLanguage()
//---------------------------------------------------------
//	Set language of the payment context
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//DLLEXPORT void pmwSetLanguage(tPaymentContext *ctx, tLanguage language);
DLLEXPORT void pmwSetLanguage(tPaymentContext *ctx, tByte language);

//---------------------------------------------------------
//            pmwGetEMVData()
//---------------------------------------------------------
//	Fill up a tag list from ICC and EMV transaction information
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void pmwGetEMVData(
	tSessionId session, 	//Session retrieved at emvProceedToPayment time
	tByte *TagList, 		//Tag list to fill up (ex: 9F105F2A9C...)
	tWord TagListLength, 
	tByte *EMVData,			//Tag list filled up (ex:9F100811223344556677889C0101...)
	tWord *EMVDataLength);

//---------------------------------------------------------
//            pmwICCRequestAnAdvice()
//---------------------------------------------------------
//	Return bTRUE when ICC requests an advice
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tBoolean pmwICCRequestAnAdvice(const tByte CID);

//---------------------------------------------------------
//            	pmwSetTransactionCounter()
//            	pmwGetTransactionCounter()
//            	pmwResetTransactionCounter()
//            	pmwIncrementTransactionCounter()
//---------------------------------------------------------
//	Set an initial value to Transaction Sequence Counter
//	Get current Transaction Sequence Counter
//	Reset Transaction Sequence Counter to 1
//	Add 1 to Transaction Sequence Counter
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void 		pmwSetTransactionCounter(tCounter value);
DLLEXPORT tCounter 	pmwGetTransactionCounter(void);
DLLEXPORT void 		pmwResetTransactionCounter(void);
DLLEXPORT tCounter 	pmwIncrementTransactionCounter(void);

//---------------------------------------------------------
//            pmwIsIssuerScriptSent()
//---------------------------------------------------------
//  Return bTRUE if issuer sent scripts in authorization response
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tBoolean pmwIsIssuerScriptSent(tPaymentContext *ctx);

//---------------------------------------------------------
//            pmwSetEMVResult()
//---------------------------------------------------------
//    Set a EMV Result on tags 9F34, 95, 9B, 9F26, 84, 5A
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void pmwSetEMVResult(tPaymentContext *ctx);

//---------------------------------------------------------
//            pmwIsCVMSignature()
//---------------------------------------------------------
//  Return bTRUE if CVM Result is a signature
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tBoolean pmwIsCVMSignature(tPaymentContext *ctx);

//---------------------------------------------------------
//            pmwResetTRMTransactionLog()
//---------------------------------------------------------
//    Reset Kernel internal log managing TRM
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void pmwResetTRMTransactionLog(void);

//---------------------------------------------------------
//            pmwGetKernelVersion()
//---------------------------------------------------------
//    Return Kernel's version
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tString pmwGetKernelVersion(void);

//---------------------------------------------------------
//            pmwProceedInteracToFinalSelection()
//---------------------------------------------------------
//	Perform a final selection according to Interac rules and EMV standard
//	That method is generic for any selection processing worldwide
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//	
//	Returned values:
//
//		payTRANSACTION_TERMINATED: no more application
//		payTRANSACTION_CANCELLED: transaction stopped on confirmation (cardholder selects cancel)
//		payNO_ERROR: application number is indicated by AIDIndex
//
DLLEXPORT tPaymentError pmwProceedToUniversalFinalSelection(
	tADFList 			*mutualList,
	tByte				*AIDIndex,	// Index in the AID list supported by the terminal (see processing context)
    tByte				*MLIndex,	// Index in the mutual list
	const tTerminalContext 	*terminal,
	tBoolean			CLMode);


//---------------------------------------------------------
//            pmwSetEnableAidListExclusion()
//---------------------------------------------------------
//	This method is to enables the processing of exclusion of AID exclusion list 
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//	
//	Returned values:
//
//		dtmNO_ERROR: no error
//Input: bExclusion  
tPaymentError pmwSetEnableAidListExclusion(tBoolean bExclusion);


//---------------------------------------------------------
//            pmwSetAidListExclusion()
//---------------------------------------------------------
//	This method is for exclusion of AID list 
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//	
//	Returned values:
//
//		dtmNO_ERROR: no error
//Input: 
//  AidStrList - a string stream that contains Aid of VISA with "space ( )" or "comma (,)" delimiters 
//				(e.g. "A0000000031010, A0000000032010)
tPaymentError pmwSetAidListExclusion(const char *AidStrList);

//---------------------------------------------------------
//            pmwSetInteracAppSelect()
//---------------------------------------------------------
//	This method enables the Interac Application Selection Process
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//	
//	Returned values:
//
//		dtmNO_ERROR: no error
//Input: 
//  bInterac - flag that enables/disables the Interac Process
tPaymentError pmwSetInteracAppSelect(tBoolean bInterac);

//---------------------------------------------------------
//            pmwSetInteracVisaOptOut()
//---------------------------------------------------------
//	Sets Visa Support 
//	That method is for selection processing for Interac only
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//	
//	Returned values:
//
//		dtmNO_ERROR: no error
//Input: 
//	bOptOut - Optout Visa Support, if TRUE VISA AID will be eliminated in the candidate list
//  AidStrList - a string stream that contains Aid of VISA with "space ( )" or "comma (,)" delimiters 
//				(e.g. "A0000000031010, A0000000032010)
tPaymentError pmwSetInteracVisaOptOut(tBoolean bOptOut, const char *AidStrList);

//---------------------------------------------------------
//            pmwIsInteracCard()
//---------------------------------------------------------
//	Can be called after invoking Select Application to determine if the card is an Interac card

tBoolean pmwIsInteracCard(void);

//---------------------------------------------------------
//            pmwCloseEMVSession()
//---------------------------------------------------------
//	Close a kernel session. Session identifier is found in tPaymentContext
//	See also Atmos configuration data model.
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		payNO_ERROR: normal case
//
DLLEXPORT tPaymentError pmwCloseEMVSession(tSessionId session);

//---------------------------------------------------------
//            pmwDEK()
//---------------------------------------------------------
//	Send a DEK signal to Terminal
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void pmwDEK(tLevel3DataExchange *L3Data);

//---------------------------------------------------------
//            pmwDET()
//---------------------------------------------------------
// Process a DET signal received from Terminal
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void pmwDET(tLevel3DataExchange *L3Data);

//---------------------------------------------------------
//				SIGNALS
//---------------------------------------------------------
// These services has been implemented only to support certification sessions.
// So, use it only when connected onto Atmos. This is a flaw by design to expose
// it in that interface (paymentMW.h). However, since AgnosEP requires it (certification
// test points are within the "tested" solution under certification when outcome is SELECT_NEXT_RETRY)
// these services must be in paymentMW whereas a POIClient would have been the place.

typedef void (*sgnSendOutcome)(tOutComeParameter *outcome);
typedef void (*sgnSendDR)(tPaymentContext *payment);
typedef void (*sgnSendDD)(tPaymentContext *payment);
typedef void (*sgnSendRawDD)(tByte *data, tWord dataLen);
typedef void (*sgnSendDEK)(tPaymentContext *payment, tByte ADPUState, tBoolean sendDataNeeded, tByte* outDET, tWord* lenOutDET);
typedef void (*sgnSendDET)(tPaymentContext *payment);

#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	sgnSendOutcome 	mSendOutcomeSignal;
	sgnSendDR		mSendDRSignal;
	sgnSendDD		mSendDDSignal;
	sgnSendRawDD	mSendRawDDSignal;
	sgnSendDEK		mSendDEKSignal;
	sgnSendDET		mSendDETSignal;
} tSignal;
#ifdef PACKING
#pragma pack()
#endif


DLLEXPORT void pmwSetSignal(tSignal *signal);
DLLEXPORT void pmwSendOutcome	(tOutComeParameter 	*outcome);
DLLEXPORT void pmwSendDR (tPaymentContext *payment);
DLLEXPORT void pmwSendDD (tPaymentContext *payment);
DLLEXPORT void pmwSendRawDD (tByte *data, tWord dataLen);
DLLEXPORT void pmwSendDEK (tPaymentContext *payment, tByte ADPUState, tBoolean sendDataNeeded, tByte* outDET, tWord* lenOutDET);
DLLEXPORT void pmwSendDET (tPaymentContext *payment);


//---------------------------------------------------------
//            pmwSetTagList
//---------------------------------------------------------
// Use to hold list of tags to be extracted by pmwSetEMVResult()
// for contactless transaction
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void pmwSetTagList(const tByte *TagList, int TagListLen);

//---------------------------------------------------------
//            pmwGetTagList
//---------------------------------------------------------
// To get the global gTagList
// 
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT int pmwGetTagList(tByte *TagList);


#ifdef __cplusplus
}
#endif




#endif /*PAYMENTMW_H_*/
