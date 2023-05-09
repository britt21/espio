// NAME.......  selection.h
// PURPOSE....  Selection of EMV applications (calculate list of application mutually supported by ICC and terminal)
// PROJECT....  AGNOS
// REFERENCES.	--
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS�?, All Rights Reserved
//
#ifndef SELECTION_H_
#define SELECTION_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------
//            Include Files
//---------------------------------------------------------
//---- Local Headers ----
#include "agnoserrors.h"
//---- Global Headers ----
#include "gpi_agnos_framework_globals.h"

/**
 * \addtogroup Selection
 * @{
 * @file selection.h
 * @brief Set of selection primitives related to Agnos API
 */
//---------------------------------------------------------
//            Definitions
//---------------------------------------------------------
#define	LOWEST_PRIORITY		0x0F		// Order of an application at cardholder confirmation time

// AID information kept in  the terminal as per semantic's EMVCo proposal
#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tByte			mAcquirerIdentifier[6];			//  TAG 0x9F01

	tByte			mAID[MAX_AID_LENGTH];	
	tByte			mAIDLen;
	tBoolean		mApplicationSelectionIndicator;
	tByte 			mApplicationVersionNumber[2];	//  TAG 0x9F09

	tAmount			mXAmount;
	tAmount			mYAmount;
	
	//Risk Management
	tBoolean		mSkipTACIACDefault;
	tBoolean		mTAC;
	tBoolean		mFloorLimitChecking;			// TAG 9F4B
	tBoolean		mRandomTransactionSelection;
	tBoolean		mVelocityChecking;
	tTVR 			mTACDenial; 
	tTVR 			mTACOnline; 
	tTVR 			mTACDefault;
	tAmount		 	mTerminalFloorLimit;
	tPercentage  	mTargetPercentage;
	tAmount		  	mThresholdValue;
	tPercentage  	mMaxTargetPercentage;

	tBoolean		mDefaultTDOL;
#ifdef _AGNOSK_
	tByte			mTDOLValue[TDOL_MAX_LENGTH];	// TAG 0x97
#else
	tByte			mTDOLValue[1];	// TAG 0x97 (dummy size. Not used in _AGNOSCL_)
#endif
	tByte			mTDOLLen;
	tBoolean		mDefaultDDOL;
#ifdef _AGNOSK_
	tByte			mDDOLValue[DDOL_MAX_LENGTH];	// TAG 0x9F49
#else
	tByte			mDDOLValue[1];	// TAG 0x9F49 (dummy size. Not used in _AGNOSCL_)
#endif
	tByte			mDDOLLen;

	tByte 			mTransactionCurrencyCode[2];	// TAG 0x5F2A
	tByte			mTransactionCurrencyExponent;	// TAG 0x5F36

} tAIDContext;
#ifdef PACKING
#pragma pack()
#endif


// AID information - alias ADF - kept in the ICC as per semantic's EMVCo proposal
#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tByte		mADFName[MAX_AID_LENGTH]; 		//0x4F
	tByte		mADFLen;
	tByte		mLabel[MAX_AID_LENGTH]; 		//0x50
	tByte		mLabelLen;
	tByte		mPreferredName[MAX_AID_LENGTH]; //0x9F12
	tByte		mPreferredNameLen;
	tByte		mPriorityIndicator; 			//0x87
	tByte		mLangagePreference[8]; 			//0x5F2D
	tByte		mLangagePreferenceLen;
	tByte		mIssuerCodeTableIndex; 			//0x9F11
	tByte		mRemainingFCI[200]; 			//0xBF0C. May contain Issuer Country Code 5F56 AND/OR Application Selection Flag DF62
	tByte		mRemainingFCILen;
	tByte		mBlocked;
	tByte		mCorrespondingAIDOrderNumber;	// Order of the ADF in the AID list (application supported by terminal)

	// Extension to support PPSE
	tByte		mKernelIdentifier[8];			//0x9F2A
	tByte		mKernelIdentifierLen;
	tByte		mRequestedKernelId;
	tByte		mExtendedSelection[MAX_AID_LENGTH];			//0x9F29
	tByte		mExtendedSelectionLen;
} tADF;
#ifdef PACKING
#pragma pack()
#endif

#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tByte 		mNumberOfADF;
	tADF 		mList[MAX_SUPPORTED_ADF];
	tBoolean 	mEliminatedADF[MAX_SUPPORTED_ADF];
	tBoolean 	mCardBlocked;
	tBoolean 	mAnyBlockedApplication;
	tByte		mSelectionIndex;
} tADFList;
#ifdef PACKING
#pragma pack()
#endif


// PSE FCI related data
#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tByte		mPSEName[MAX_AID_LENGTH]; 		//0x84
	tByte		mPSELen;
	tByte		mSFI; 			//0x88
	tByte		mLangagePreference[8]; 			//0x5F2D
	tByte		mLangagePreferenceLen;
	tByte		mIssuerCodeTableIndex; 			//0x9F11
	tByte		mRemainingFCI[MAX_REMAINING_FCI_LENGTH]; 			//0xBF0C. May contain Issuer Country Code 5F56 AND/OR Application Selection Flag DF62
	tByte		mRemainingFCILen;
} tPSE;
#ifdef PACKING
#pragma pack()
#endif


//---------------------------------------------------------
//            Primitives
//---------------------------------------------------------

//---------------------------------------------------------
//            selInitializeADFList()
//---------------------------------------------------------
//	Initialize a list before any processing
//
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void selInitializeADFList(
	tADFList *list				// In: list of mutual AID to be used for selection process
);

//---------------------------------------------------------
//            selGetDFName()
//---------------------------------------------------------
//	Get DF Name from ADF list
//
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tAgnosError selGetDFName(
	tByte ADFNumber, 
	tADFList* list, 
	tByte* DFName, 
	tByte* DFLen
);

//---------------------------------------------------------
//            selGetMutualList()
//---------------------------------------------------------
//	Calculate mutual supported application between ICC and supportedAIDList
//
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book I 12.3 See below for more details
//
//	Returned values:
//
//		agnSYSTEM_ERROR: emv flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
//		agnINTERRUPTED: user stopped transaction
//		agnSW_6A81: Card blocked. mutualList->mCardBlocked is set to bTRUE
//		agnNO_ERROR: normal case
//
//
DLLEXPORT tAgnosError selGetMutualList(
	const tString deviceName,
	tByte numberOfSupportedAID,				// Number of AID supported by the terminal
	const tAIDContext* supportedAIDList,	// List of AID, which are submitted through AIDContext
	tADFList* mutualList					// Out: Mutual list, eg common applications between ICC and terminal
);

//---------------------------------------------------------
//            selGetMutualListFromPSE()
//---------------------------------------------------------
//	Select Application using PSE. Fallback to selGetMutualList is required during the process
//
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book I 12.2 See below for more details
//
//	Returned values:
//
//		agnSYSTEM_ERROR: emv flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
//		agnINTERRUPTED: user stopped transaction
//		agnSW_6A81: card blocked. mutualList->mCardBlocked is set to bTRUE
//		agnSELECTION_ERROR : invalid PSE selection.
//		agnNO_ERROR: normal case
//
//
DLLEXPORT tAgnosError selGetMutualListFromPSE(
	const tString deviceName,
	tByte* PSE,
	tByte PSELen,
	tByte numberOfSupportedAID,	// Number of AID supported by the terminal
	const tAIDContext* supportedAIDList,// List of AID, which are submitted through AIDContext
	tADFList* mutualList,				// Out: Mutual list, eg common applications between ICC and terminal
	tWord* SW1SW2							// Out: Status Word
);

//---------------------------------------------------------
//            selGetMutualListFromPPSE()
//---------------------------------------------------------
//	Select Application using PPSE.
//
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book I 12.2 See below for more details + Book B
//
//	Returned values:
//
//		agnSYSTEM_ERROR: emv flow leads to an unexpected error (card removed, memory failure, dummy card response, ...)
//		agnINTERRUPTED: user stopped transaction
//		agnSW_6A81: Card blocked. mutualList->mCardBlocked is set to bTRUE
//		agnNO_ERROR: normal case
//
//
DLLEXPORT tAgnosError selGetMutualListFromPPSE(
	const tString deviceName,
	tByte* PSE,
	tByte PSELen,
	tByte numberOfSupportedAID,		// Number of AID supported by the terminal
	const tAIDContext* supportedAIDList,	// List of AID, which are submitted through AIDContext
	tADFList* mutualList,					// Out: Mutual list, eg common applications between ICC and terminal
	tWord* SW1SW2,							// Out: Status Word
	tPSE* PPSE								// Out: PPSE's FIC
);

//---------------------------------------------------------
//            selSetEMVCoPPSEState()
//---------------------------------------------------------
//	Set PPSE selection to ON or OFF in regards with EMVCo Book B rules
//
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book B
//
//	Returned values:
//
//		agnNO_ERROR: normal case
//
//
DLLEXPORT void selSetEMVCoPPSEState(tBoolean state);

//---------------------------------------------------------
//            selGetEMVCoPPSEState()
//---------------------------------------------------------
//	Get PPSE selection to ON or OFF in regards with EMVCo Book B rules
//
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: EMVCo Book B
//
//	Returned values:
//
//		agnNO_ERROR: normal case
//
//
DLLEXPORT tBoolean selGetEMVCoPPSEState(void);

//---------------------------------------------------------
//            selSetADFListReference()
//---------------------------------------------------------
//	Set mutual list reference used by entry point during selection process
//
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		agnNO_ERROR: normal case
//
DLLEXPORT void selSetADFListReference(tADFList* list);

//---------------------------------------------------------
//            selGetADFListReference()
//---------------------------------------------------------
//	Get mutual list reference used by entry point during selection process
//
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		tADFList*: list
//
//
DLLEXPORT tADFList* selGetADFListReference(void);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* SELECTION_H_ */
