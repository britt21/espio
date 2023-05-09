// NAME.......  agnosinternal.h
// PURPOSE....  Internal structure and related primitives
// PROJECT....  AGNOS
// REFERENCES.	--
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//
#ifndef AGNOSINTERNAL_H_
#define AGNOSINTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------
//			Include Files
//---------------------------------------------------------
//---- Local Headers ----
#include "agnos.h"
//---- GPI Headers ----
#include "gpi.h"
//---- Global Headers ----
#include "gpi_agnos_framework_globals.h"
//---- AgnosDB Headers ----
#include "agnosdatabase.h"

//---------------------------------------------------------
//			Definitions
//---------------------------------------------------------

//#define _OBFUSCATION_

#define	CHECK_SW1_SW2(primitive,apduResponse,length)		if (gpiMemCmp(apduResponse+length,"\x90\x00",2)!=0) { \
																return agnEMV_ERROR; \
															}

//Application Interchange Profile bitmap
#define PERFORM_SDA						0x40
#define PERFORM_DDA						0x20
#define PERFORM_CVM						0x10	
#define PERFORM_TRM						0x08
#define PERFORM_EXTERNAL_AUTH			0x04
#define PERFORM_CDA						0x01

//Date Management
#define	PIVOT_DATE						50
#define	CENTURY_20						1900
#define	CENTURY_21						2000

//Terminal Capabilities
#define SDA								0x80
#define DDA								0x40
#define CDA								0x08

//GenerateAC
#define	DEFAULT_IAC_DENIAL				0x00
#define	DEFAULT_IAC_ONLINE				0xFF
#define	DEFAULT_IAC_DEFAULT				0xFF

#define SMARTCARDREADER_NAME(x)		x->mSmartcardReaderName
#define PINPAD_NAME(x)				x->mPinPadName

// APDU management
#define P1_IS_RECORD_NUMBER			0x04
#define P1_IS_RECORD_NUMBER_MASK	0xFB
#define CLA							apduReq[0]
#define INS							apduReq[1]
#define P1							apduReq[2]			
#define P2							apduReq[3]
#define Lc							apduReq[4]			

// EMV control
#define AFL_MODULO_SIZE				4
#define CVM_MINIMUM_SIZE			10
#define CVM_X_Y_SIZE				8
#define CVM_RULE_SIZE				2
#define ARC_Y						0x59
#define ARC_Z						0x5A
#define ARC_1						0x31
#define ARC_3						0x33

// Offline Data Authentication
#define CONSTRUCTED_TAG_70			0x70

// EMV Script processing
#define	SCRIPT_NOT_PERFORMED		0x00
#define	SCRIPT_FAILED				0x10
#define	SCRIPT_SUCCESSFUL			0x20
#define	MAX_SCRIPT_SEQUENCE_NUMBER	0x0F

//---------------------------------------------------------
//            Data structure
//---------------------------------------------------------
//
#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	// Transactional context
	tDate 					mTransactionDate; 					//0x9A
	tDate 					mTransactionTime; 					//0x9F21
	tBoolean				mSkipTACIACDefault;
	tBoolean				mTAC;
    tBoolean				mForceTRM;
	tBoolean				mFloorLimitChecking;
	tBoolean				mRandomTransactionSelection;
	tBoolean				mVelocityChecking;
	tBoolean				mDefaultTDOL;
	tByte					mDefaultTDOLLen;
	tByte					mDefaultTDOLValue[TDOL_MAX_LENGTH];	//0x97
	tBoolean				mDefaultDDOL;
	tByte					mDefaultDDOLLen;
	tByte					mDefaultDDOLValue[DDOL_MAX_LENGTH]; //0x9F49
	tCDAType				mCDAType;
	tBoolean				mPINByPass;
	tBoolean				mForcedOnline;
	
	//Risk Management Values
	tAmount		 			mTerminalFloorLimit; 				//0x9F1B (decimal value)
	tPercentage  			mTargetPercentage;
	tAmount		  			mThresholdValue;
	tPercentage  			mMaxTargetPercentage;
	tBoolean  				mTransactionLog;	
	tByte					mTransactionLogDepth;
	
	//Internal
	tAgnosState				mState;
	tBoolean				mDirectExecution;
	tAgnosState				mExitState;
	tStateCallback			mStateCallBack;
	tBoolean				mContactless;
	tBoolean				mPINEntered;

	tTagDataBase			mTagDataBase;

	char					mSmartcardReaderName[MAX_NAME_LENGTH];
	char					mPinPadName[MAX_NAME_LENGTH];
	char					mApplicationId[MAX_NAME_LENGTH];  // Agnos' client
	tAmount					mAuthorizedAmount;
	tAmount					mOtherAmount;
	tByte					mAID[MAX_AID_LENGTH]; // Selected AID
	tByte					mAIDLen;
	tByte					mCID; // Calculated at TAA time
	tByte					mCAKeyModulusLength;
	tEMVPubKey				mIssuerKey;	// Issuer RSA Public Key, present if modulusLn != 0
	tEMVPubKey				mIccKey;	// ICC RSA Public Key, present if modulusLn != 0
	tEMVPubKey				mIccPinKey;	// ICC PIN RSA Public Key, present if modulusLn != 0
	tBoolean				mCDAPublicKeyChainNotVerified;
	tWord					mRemainderMissing;
#ifdef _AGNOSCPL_
	tByte					mIssuerResponse[ISSUER_RESPONSE_SIZE]; // contains all scripts to execute
	tWord					mIssuerResponseLength;
#endif
#ifdef _AGNOSISR_
	tByte*					mScript71[MAX_SCRIPT]; // mScript71[i] points at the TLV's Value of a script
	tByte					mScript71Number;
	tByte*					mScript72[MAX_SCRIPT]; // mScript72[i] points at the TLV's Value of a script
	tByte					mScript72Number;
	tByte					mExecutedScriptNumber;
	tScriptResult			mScriptResult[2*MAX_SCRIPT]; // For each script, a 5-byte length result
#endif
	tWord					mSW1SW2;
//	tLanguage				mLanguage;
	tByte					mLanguage;
	tCounter				mPinTimeOut;
	tBoolean				mPerformCDA;
	tByte					mPDOL[PDOL_MAX_LENGTH];
	tByte					mPDOLLen;
	tByte					mCDOL1[CDOL_MAX_LENGTH];
	tByte					mCDOL1Len;
	tByte					mCDOL2[CDOL_MAX_LENGTH];
	tByte					mCDOL2Len;

	tByte					mGenAC1Response[MAX_APDU_LENGTH];
	tByte					mGenAC1ResponseLen;
	tBoolean				mCDARequest;

#ifdef _AGNOSCL_
	// Recovery for contactless
	tByte					mDRDOL[DRDOL_MAX_LENGTH];
	tByte					mDRDOLLen;
	// Specific to MasterCard Data Storage
	tByte					mDSDOL[DSDOL_MAX_LENGTH];
	tByte					mDSDOLLen;
#endif
	tByte					mReferenceControlParameter;

	tGetDataCallback		mGetData;
	tBoolean				mCallBackBeforeAPDU;

	// SRED related
	tBoolean				mClipping;
	tBoolean				mSRED;
	tBoolean				mObfuscation;
	tByte					mSRED56Length;
	tByte					mSRED56Offset;
	tByte					mSRED57Length;
	tByte					mSRED57Offset;
	tByte					mSRED5ALength;
	tByte					mSRED5AOffset;

} tInternalContext;
#ifdef PACKING
#pragma pack()
#endif

//---------------------------------------------------------
//            Primitives accessing the data structure
//---------------------------------------------------------
//

DLLEXPORT tByte 			agiGetSessionNumber(void);
DLLEXPORT tByte 			agiGetSessionSlot(void);
DLLEXPORT void 				agiFreeSessionSlot(const tSessionId session);
DLLEXPORT tBoolean			agiSessionValid(const tSessionId session);

DLLEXPORT tInternalContext* agiGetInternalContext(const tSessionId session);
DLLEXPORT tAgnosError 		agiResetContext(tInternalContext* ctx);
//DLLEXPORT void 			agiDumpContext(const tSessionId session, char* buffer, const tWord bufferLen);
DLLEXPORT void 				agiDumpContext(const tSessionId session);

DLLEXPORT tBoolean 			agiIsOfflineOnly(const tTerminalType type);
DLLEXPORT tBoolean 			agiIsOnlineOnly(const tTerminalType type);

DLLEXPORT tBoolean 			agiIsICCCIDAtHigherRisk(const tByte ICCCID, const tByte TerminalCID);
DLLEXPORT tBoolean 			agiICCCIDPresentAAR(const tByte ICCCID);

DLLEXPORT tAgnosError		agiIsFCIValid(tByte* FCI, const tWord FCILen);
DLLEXPORT tBoolean 			agiIsRecordValid(tByte* record, const tWord recordLen);
DLLEXPORT tBoolean			agiIsTemplate77FromGPOValid(tByte* data, const tWord dataLen);
DLLEXPORT tAgnosError		agiIsTemplate77FromCCCValid(tByte* data, const tWord dataLen);
DLLEXPORT tAgnosError		agiIsTemplate77FromGenACValid(tByte* data, const tWord dataLen, tBoolean CDARequest);

DLLEXPORT tBoolean 			agiIsCertificateExpired(tInternalContext* ctx, tByte* certificateDate);
DLLEXPORT tByte 			agiGetCertificatePANLength(tByte* certificatePAN);

DLLEXPORT tAgnosError		agiCreateTag(tInternalContext* ctx, const enum DataElementIndex idx, const tWord length, const tByte initValue);
DLLEXPORT tAgnosError		agiCreateTagWith(tInternalContext* ctx, const enum DataElementIndex idx, const tWord length, const tByte* byteArray);
DLLEXPORT tAgnosError		agiInitTag(tInternalContext* ctx, const enum DataElementIndex idx, const tByte initValue);
DLLEXPORT tAgnosError		agiInitTagWith(tInternalContext* ctx, const enum DataElementIndex idx, const tByte* byteArray);
DLLEXPORT tAgnosError		agiRemoveTag(tInternalContext* ctx, const enum DataElementIndex idx);

//---------------------------------------------------------
//            agiAllMandatoryDataPresent()
//---------------------------------------------------------
//	Return bTRUE if all mandatory object are present in a given context 
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2. See below for more details (section 7.2)
// 	
DLLEXPORT tBoolean agiAllMandatoryDataPresent(tInternalContext* ctx);

//---------------------------------------------------------
//            agiCheckConsistency()
//---------------------------------------------------------
//	Return bTRUE if consistency of data objects is confirmed in a given context 
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book III 4.2. See below for more details (section 7.5)
//
DLLEXPORT void agiCheckConsistency(tInternalContext* ctx);

//---------------------------------------------------------
//			agiBuildDOL()
//---------------------------------------------------------
//	Build Data List from a DOL
//
//  Visibility: Public
//  Hypothesis: --
//	Reference: Book3-5.4
//
DLLEXPORT void agiBuildDOL(	//	Build Data List from a DOL
		tInternalContext*,	// Internal Transaction Context
		tWord,				// DOL Index in context
		tByte*,				// Buffer to build Data List
		tWord*				// Data List Length
);

//---------------------------------------------------------
//			agiGetTransactionKey()
//---------------------------------------------------------
//	Return a TransactionKey from a context. Key is calculated from PAN EMV Tag 5A
//
//  Visibility: Public
//  Hypothesis: --
//	Reference: --
//
DLLEXPORT void agiGetTransactionKey(
	tInternalContext* ctx, // Internal Transaction Context
	tTransactionKey key   // TransactionKey corresponding to the context
);

//---------------------------------------------------------
//			agiLogTransaction()
//---------------------------------------------------------
//	Log a new transaction. If the transaction key already exist, cumul the amount.	 
//
//  Visibility: Public
//  Hypothesis: --
//	Reference: --
//
DLLEXPORT void agiLogTransaction(
	tInternalContext* ctx, // Internal Transaction Context
	tTransaction* transaction
);

//---------------------------------------------------------
//			agiGetAmount()
//---------------------------------------------------------
//	Return an amount from a TransactionKey (0 if not found)	 
//
//  Visibility: Public
//  Hypothesis: --
//	Reference: --
//
DLLEXPORT tAmount agiGetAmount(
	tInternalContext* ctx, // Internal Transaction Context
	tTransactionKey key);

//---------------------------------------------------------
//			agiGetTransactionLog()
//---------------------------------------------------------
//	Return the log	 
//
//  Visibility: Public
//  Hypothesis: --
//	Reference: --
//
DLLEXPORT tTransaction* agiGetTransactionLog(void);

//---------------------------------------------------------
//			agiResetTransactionLog()
//---------------------------------------------------------
//	Reset all keys and amounts	 
//
//  Visibility: Public
//  Hypothesis: --
//	Reference: --
//
DLLEXPORT void agiResetTransactionLog(void);

//---------------------------------------------------------
//            agiGetTagLength()
//---------------------------------------------------------
//	Calculate a Tag's length
//
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tByte agiGetTagLength(
	tByte* TagLength,		// EMV Tag to parse
	tWord* length			// Length of the tag
);

//---------------------------------------------------------
//            agiTerminalSupportPINRelatedCVM()
//---------------------------------------------------------
//	Return bTRUE if terminal supports a CVM related to PIN (offline plaintext / offline enciphered / online enciphered)
//
//  Visibility: Private
//  Hypothesis: --
//  Reference: EMVCo Book IV, section 6.3.4.1
//
DLLEXPORT tBoolean agiTerminalSupportPINRelatedCVM(tInternalContext* ctx);

#ifdef __cplusplus
}
#endif

#endif /*AGNOSINTERNAL_H_*/


