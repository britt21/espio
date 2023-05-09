// NAME.......  datamngr.h
// PURPOSE....  Management of configuration data. Internally, this component manages the following data members (aggregates):
//
// 			tTerminalContext				gTerminalContext;
// 			tProcessingContext				gContactProcessingContext;
// 			tProcessingContext				gContactlessProcessingContext;
//			tListOfCLSupportedAID 			gSupportedAID;
//			tListOfCLSupportedCombination 	gCombination;
//			tEntryPointContext 				gEntryPointContext;
// 			tSupportedKernel				gSupportedKernel;
//
//			These data members are initialized and accessed by primitives described below.
//
// PROJECT....  AGNOSMW
// REFERENCES.	--
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS�?, All Rights Reserved
//

#ifndef DATAMNGR_H
#define	DATAMNGR_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------
//			Include Files
//---------------------------------------------------------
//---- Local Headers ----
#include "paymenterrors.h"
//---- Agnos Framework Headers ----
#include "agnos.h"
#include "selection.h"
//---- GPI Headers ----
#include "gpi.h"

//---------------------------------------------------------
//			Definitions
//---------------------------------------------------------
typedef long tKey;

#define dtmINVALID_KEY				-1

#define DEFAULT_CONTEXT       		0

#define SUPPORTED_AID				100
#define SUPPORTED_COMBINATION		200
#define TERMINAL_CTX				300
#define CONTACT_PROCESSING_CTX		400
#define ENTRY_POINT					500
#define CONTACTLESS_PROCESSING_CTX	600
#define KERNEL_ID_FROM_CONFIG_CTX   700

// Typically, these information are retrieved from the processor to the merchant's terminal
// and then persisted onto the terminal
#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tString			mDeviceName;					// Not persisted in binary files (transient)
	tString			mPinPadName;					// Not persisted in binary files (transient)
	tByte			mTerminalCountryCode[2];		// TAG 0x9F1A
	tByte			mTerminalIdentification[8];		// TAG 0x9F1C
													// Not persisted in binary files. Retrieved through gpi primitive gpiGetTerminalIdentification
	tByte			mIFDSerialNumber[8];			// TAG 0x9F1E
													// Not persisted in binary files. Retrieved through gpi primitive gpiGetSerialNumber
	tBoolean		mProvideCardholderConfirmation;
	tTerminalType	mTerminalType;					// TAG 0x9F35
    tBoolean		mEMVContact;
	tByte			mTerminalCapabilities[3];			// TAG 0x9F33
	tByte			mAdditionalTerminalCapabilities[5];	// TAG 0x9F40
    tBoolean		mEMVContactless;
    tBoolean		mMagstripe;
	tCounter		mPinTimeOut;	// seconds
    tBoolean		mBatchManaged;
    tBoolean		mAdviceManaged;
    tBoolean		mPSE;
    tBoolean 		mAutorun;
    tByte			mPredefinedAmount[3];

    //Extension (not yet managed by Atmos)
    tByte			mPINByPass;
    tByte			mReferralManaged;
    tByte			mDefaultTAC;
    tByte			mDefaultTACDenial[5];
    tByte			mDefaultTACOnline[5];
    tByte			mDefaultTACDefault[5];
    tByte			mNotRTS;
    tByte			mNotVelocity;
    tByte			mCDAType;
    tBoolean		mClipping;
    tBoolean		mSRED;

} tTerminalContext;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {

	// Table of supported applications 0x9F06
	tByte		mNumberOfAID;
	tAIDContext	mAIDList[MAX_SUPPORTED_AID];

	tBoolean	mX;
	tBoolean	mY;
	tAmount		mXAmount;
	tAmount		mYAmount;
	tBoolean	mXPerAID; // if bTRUE, mX will be ignored
	tBoolean	mYPerAID; // if bTRUE, mY will ignored
} tProcessingContext;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tByte	mAID[MAX_AID_LENGTH];
	tByte	mLen;
} tCLSupportedAID;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tByte mKernelIndex;
	tByte mAIDId;
} tCombination;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tWord			mNumberOfCLSupportedCombination;
	tBoolean		mList[MAX_KERNEL][MAX_SUPPORTED_AID/*MAX_AID*/];
	// Kernel from 1 to n-1
	// AID from 1 to n-1
} tListOfCLSupportedCombination;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tByte				mNumberOfCLSupportedAID;
	tCLSupportedAID		mList[MAX_SUPPORTED_AID/*MAX_AID*/]; // from 1 to n-1
} tListOfCLSupportedAID;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tCombination mCombination;
    tWord mDataObjectLen;
    tByte* mDataObject;
} tEntryPointConfigurationData;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tWord							mNumberOfEntryPointConfigurationData;
	tEntryPointConfigurationData	mList[MAX_COMBINATION_PER_TRANSACTION_TYPE]; // from 1 to n-1
} tEntryPointContext;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tCombination	mCombination;
	tBoolean 		mStatusCheckRequested;
	tBoolean 		mContactlessApplicationNotAllowed;
    tBoolean 		mExtendedSelectionSupportFlag;
	tByte 			mTTQCopy[4];
	// 	Byte1	MagstripeMode		RFU				EMVMode			EMVContactChip 		OfflineOnly		OnlinePIN	Signature	RFU
	//	Byte2	OnlineCryptogram	CVMRequired		OfflinePIN		RFU					RFU				RFU			RFU			RFU
	//	Byte3	IssuerScript		MobileCVM		RFU				RFU					RFU				RFU			RFU			RFU
	//	Byte4	RFU					RFU				RFU				RFU					RFU				RFU			RFU			RFU
	
} tEntryPointIndicators;
#ifdef PACKING
#pragma pack()
#endif


//---------------------------------------------------------
//            Public Primitives
//---------------------------------------------------------
//---------------------------------------------------------
//            dtmInitializeFromFile()
//---------------------------------------------------------
//	Retrieve data from a set of binary files :
//		- supported AIDs,
//		- combination,
//		- kernel context,
//		- entry point context,
//		- terminal context,
//		- processing context
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//			dtmNO_ERROR: no error
//			dtmSYSTEM_ERROR: SHA-1 on file integrity check
//
DLLEXPORT tDataMngrError dtmInitializeFromFile(
	const tString path,
	const tString terminal,
	const tString processing,
	const tString aid,
	const tString combination,
	const tString entryPoint,
	const tByte transactionType,
	tBoolean sha
);

//---------------------------------------------------------
//            dtmSelectCTKernel()
//---------------------------------------------------------
//	Retrieve data from a terminal context (selectable contact kernel as per emvco definition)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//			dtmNO_ERROR: no error
//			dtmSYSTEM_ERROR: SHA-1 on file integrity check
//
DLLEXPORT tDataMngrError dtmSelectCTKernel(
	const tString path,
	const tString terminal,
	tBoolean sha
);

//---------------------------------------------------------
//            dtmSetData()
//---------------------------------------------------------
// Set a specific data type (TERMINAL, or PROCESSING, or ENTRY POINT) from a tlv stream
// SUPPORTED_COMBINATION and SUPPORTED_AID are not supported
//
//
//  Visibility: Public
//  Hypothesis: Processing context must be initialized before Entry Point context
//  Reference: --
//
//	Returned values:
//
//			dtmNO_ERROR: no error
//			dtmSYSTEM_ERROR: invalid parameters
//
DLLEXPORT tDataMngrError dtmSetData(tKey key, tByte *tlv, tWord len, tByte transactionType);

//---------------------------------------------------------
//            dtmGetData()
//---------------------------------------------------------
//	Retrieve data from local repository.
// 	Calling application shall cast void* to expected data that was requested (as per tKey)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//			void* :
//
DLLEXPORT void* dtmGetData(tKey key);

//---------------------------------------------------------
//            emvSetTransactionalContext()
//---------------------------------------------------------
//	From a processing and a terminal context, set a transaction context used to initiate a contact kernel session.
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtmSetTransactionalContext(tByte AIDNumber,tTransactionalContext *transaction);

//---------------------------------------------------------
//            dtmGetAIDId()
//---------------------------------------------------------
//	Retrieve AID's id from AID table. AIDId start from 1.
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//			tKey : key value or dtmINVALID_KEY
//
DLLEXPORT tKey dtmGetAIDId(const tByte *AID, tByte len);

//---------------------------------------------------------
//            dtmGetDefaultKernelId()
//---------------------------------------------------------
//	Return the default kernelId from AID.
//  As perEMVCo book B, table 3-6:
//
//			- Mastercard 	->	0x02
//			- Visa			->	0x03
//			- Amex 			->	0x04
//			- JCB 			->	0x05
//			- Discover 		->	0x06
//			- CUP 			->	0x07
//			- Other			->	0x00
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//			tByte : kernel identifier
//
DLLEXPORT tByte dtmGetDefaultKernelId(const tByte *AIDId);

//---------------------------------------------------------
//            dtmGetKernelIdFromConfig()
//---------------------------------------------------------
//	Return the kernelId for an AIDId in the configuration.
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tKey dtmGetKernelIdFromConfig(tKey AIDId);

//---------------------------------------------------------
//            dtmIsCombinationSupported()
//---------------------------------------------------------
//	Retrieve kernel configuration data for a specific combination (or KAT key)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//			bFALSE: not supported
//			bTRUE: supported
//
DLLEXPORT tBoolean dtmIsCombinationSupported(tKey kernelIndex, tKey AIDId);

//---------------------------------------------------------
//            dmtInitKernelIdIndexTable()
//---------------------------------------------------------
//  Initialize a table of kernel index for a kernel id
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dmtInitKernelIdIndexTable(void);

//---------------------------------------------------------
//            dtmAssignKernelIndex()
//---------------------------------------------------------
//  Assigns a kernel index for a kernel id in a table
//  Returns the kernel index
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tByte dtmAssignKernelIndex(tByte kernelId);

//---------------------------------------------------------
//            dtmGetKernelIndex()
//---------------------------------------------------------
//	Return the kernel index for a kernel Id from a table
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tByte dtmGetKernelIndex(tByte kernelId);

//---------------------------------------------------------
//            dtmSetCurrentKernelIdentifier()
//---------------------------------------------------------
//  Make 9F2A (from card PPSE data) available for applications
//  (required by Entry Point qualification)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtmSetCurrentKernelIdentifier(tByte *kernelIdentifier, tByte  len);

//---------------------------------------------------------
//            dtmGetCurrentKernelIdentifier()
//---------------------------------------------------------
//  Make 9F2A (from card PPSE data)available for applications
//  (required by Entry Point qualification)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtmGetCurrentKernelIdentifier(tByte *kernelIdentifier, tByte *len);

#ifdef __cplusplus
}
#endif

#endif	/* DATAMNGR_H */

