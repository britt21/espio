// NAME.......  dataxchng.h
// PURPOSE....	Data exchange as per Mastercard specification is based on list management. This module implements the related
//				primitives (see M/Chip Advanced 3.0 section 5.3 List Handling)
// PROJECT....  AGNOSMW
// REFERENCES.	--
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//

#ifndef DATAXCHNG_H_
#define DATAXCHNG_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------
//			Include Files
//---------------------------------------------------------
//---- Local Headers ----
#include "datamngr.h"
//---- Agnos Framework Headers ----
#include "agnostypes.h"
//---- GPI Headers ----
#include "gpi.h"

//---------------------------------------------------------
//			Definitions
//---------------------------------------------------------
#define MAX_TAG						15  // Per data exchange list
#define MAX_TAG_LENGTH				200	// within a data exchange list (need to support at least MasterCard's 9F7x tags length)
#define	MAX_STREAM_SIZE				500
#define	IGNORE_TIME					0xFFFF
#define	IDX_NOT_FOUND				0xFFFF

typedef void (*emvCallback)(void *data);

typedef enum {
	deNONE,
	deMADS,
	deVIUDS,
	deFLASH,
	deZIP,
	deAMEX,
	deDPAS,
	dePURE,
	deJCB,
	deCUP,
	deEFTPOS,
	deSTAR,
	deAGNOS
} tDataExchangeType;

typedef enum {
	deCONTINUE,
	deABORT,
	deTIMEOUT
} tDecision;

typedef enum {
	erL1OK,
	erL1TIME_OUT_ERROR,
	erL1TRANSMISSION_ERROR,
	erL1PROTOCOL_ERROR
} tErrorL1; // errors are defined as per mastercard's specifications

typedef enum {
	erL2OK,
	erL2CARD_DATA_MISSING,
	erL2CAM_FAILED,
	erL2STATUS_BYTES,
	erL2PARSING_ERROR,
	erL2MAX_LIMIT_EXCEEDED,
	erL2CARD_DATA_ERROR,
	erL2MAGSTRIPE_NOT_SUPPORTED,
	erL2NO_PPSE,
	erL2PPSE_FAULT,
	erL2EMTPY_CANDIDATE_LIST,
	erL2IDS_READ_ERROR,
	erIDS_WRITE_ERROR,
	erIDS_DATA_ERROR,
	erIDS_NO_MATCHING_AC,
	erTERMINAL_DATA_ERROR
} tErrorL2; // errors are defined as per mastercard's specifications

typedef enum {
	erL3OK,
	erL3TIME_OUT_ERROR,
	erL3STOP,
	erL3AMOUNT_NOT_PRESENT
} tErrorL3; // errors are defined as per mastercard's specifications

#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tErrorL1 mL1; // DF56
	tErrorL2 mL2; // DF57
	tErrorL3 mL3; // DF58
    tWord mSW1SW2; // DF59
    tByte mMessageOnError; // DF5A
} tErrorIndication; // errors are defined as per mastercard's specifications
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tWord	mLength;
	tByte	mStream[MAX_STREAM_SIZE];
} tTLVStream;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tWord	mLength;
	tByte	mStream[2*MAX_STREAM_SIZE];
} tHugeTLVStream;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef enum {
	tlTAG_LIST,
	tlDATA_OBJECT_LIST,
} tTypeOfList;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tWord  		mLength;
	tByte 		*mValue;
} tHugeDataObjectReference;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tWord 		mTag;
	tByte  		mLength;
	tByte 		mValue[MAX_TAG_LENGTH];
} tDataObject;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef	struct {
	tString		mName;
	tTypeOfList	mType;
	tDataObject	mList[MAX_TAG];

	// Specific to mastercard's Data Storage (for DET/DataToSend processing)
	tHugeDataObjectReference mTagsToWriteBeforeGenAC; // alias FF8102
	tHugeDataObjectReference mTagsToWriteAfterGenAC; // alias FF8103

} tDataObjectList;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef	struct {
	tByte			*mCursor;
	tWord	mLength;
	tByte	mStream[5*MAX_STREAM_SIZE];
} tScratchPAD;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	tDataObjectList	mDataToSend; // alias FF8104
	tDataObjectList	mDataNeeded; // alias DF8106

	tDataObjectList	mTagsToReadYet;
	tDataObjectList	mTagsToWriteYetBeforeGenAC;
	tDataObjectList	mTagsToWriteYetAfterGenAC;

	tScratchPAD	mScratchPad1; // Provide a free memory space for specific Data Storage processing, i.e. alias FF02
	tScratchPAD	mScratchPad2; // Provide a free memory space for specific Data Storage processing, i.e. alias FF03
} tDataExchangeList;
#ifdef PACKING
#pragma pack()
#endif


//
// All the tags defined in tDataExchange are not set by configuration
// So, these tags are not managed through AgnosDB
//
#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {

	emvCallback			mCallback;

	
	struct {
		tWord 		mTag;
		tByte  		mLength;
		tByte 		mValue[6];
	} mBalanceBeforeGenAC; // alias DF04 or DF8104
	

	
	struct {
		tWord 		mTag;
		tByte  		mLength;
		tByte 		mValue[6];
	} mBalanceAfterGenAC; // alias DF05 or DF8105
	

	// Online Processing
	tTLVStream		mDataRecord;  // alias FF8105

	
	struct {
		tWord	mLength;
		tByte	mStream[76];
	} mTrack1; // alias 56
	

	
	struct {
		tWord	mLength;
		tByte	mStream[19];
	} mTrack2; // alias 9F6B
	

	// Messages
	tUIRequestData	mUIRequestData; // alias alias DF16 or DF8116

	// Error management
    tErrorIndication	mError; // alias alias DF15 or DF8115

#ifdef _AGNOSCPL_
	tHugeTLVStream	mIssuerResponse;     // Shall be consistent with MAX_SCRIPT_SIZE
	tTLVStream		mReversalData;
#endif

#ifdef _AGNOSFMSG_
	tTLVStream		mBatchData;
	tTLVStream		mAdviceData;
#endif

#ifdef _AGNOSCL_
	tHugeTLVStream	mDiscretionaryData;  // alias FF8106

	
	struct {
		tWord	mLength;
		tByte	mStream[56];
	} mDDTrack1; // alias DF2A  or DF812A
	

	
	struct {
		tWord	mLength;
		tByte	mStream[8];
	} mDDTrack2; // alias DF2B or DF812B
	
#endif

	tDataExchangeList* mDEList;

} tDataExchange;
#ifdef PACKING
#pragma pack()
#endif


//---------------------------------------------------------
//            Public Primitives
//---------------------------------------------------------
//---------------------------------------------------------
//            pmwInitializeDataExchange()
//---------------------------------------------------------
//	Initialize DataToSend Send list as follow:
//
//		- DataToSend = tlDATA_OBJECT_LIST
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtxInitializeDataExchange(tDataExchange *data);

//---------------------------------------------------------
//            pmwSetBalanceBeforeGenAC()
//            pmwSetBalanceAfterGenAC()
//---------------------------------------------------------
DLLEXPORT void dtxSetBalanceBeforeGenAC(tDataExchange *data, tByte *bal);
DLLEXPORT void dtxSetBalanceAfterGenAC(tDataExchange *data, tByte *bal);

//---------------------------------------------------------
//            dtxInitializeUIRequestData()
//---------------------------------------------------------
//	Initialize UI Request
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtxInitializeUIRequestData(tUIRequestData *data);

//---------------------------------------------------------
//            dtxInitializeErrorIndication()
//---------------------------------------------------------
//	Initialize Error Indication
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtxInitializeErrorIndication(tErrorIndication *data);

//---------------------------------------------------------
//            dtxSetUILanguage()
//---------------------------------------------------------
//	Set language of the UI request Data context
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtxSetUILanguage(tUIRequestData *data, const tByte* language, tByte languageLen);

//---------------------------------------------------------
//            dtxInitializeDataToSend()
//---------------------------------------------------------
//	Initialize a DataToSend list
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtxInitializeDataToSend(tDataExchangeList *data);

//---------------------------------------------------------
//            dtxInitializeDataNeeded()
//---------------------------------------------------------
//	Initialize a DataNeed list
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtxInitializeDataNeeded(tDataExchangeList *data);

//---------------------------------------------------------
//            dtxInitializeScratchPAD()
//---------------------------------------------------------
//	Initialize a scratch PAD
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtxInitializeScratchPAD(tDataExchangeList *data);

//---------------------------------------------------------
//            dtxInitializeList()
//---------------------------------------------------------
//	Initialize a list
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtxInitializeList(const tString name, tTypeOfList type, tDataObjectList *list);

//---------------------------------------------------------
//            pmwPushDataObjectToDataToSend()
//---------------------------------------------------------
//	Push a data object to DataToSend list (see data exchange structure)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//void dtxPushDataObjectToDataToSend(tDataExchange *data, tDataObject *object);

//---------------------------------------------------------
//            pmwPopDataObjectFromDataToSend()
//---------------------------------------------------------
//	Pop a data object from DataToSend list (see data exchange structure)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//
//	Returned values:
//
//		tWord: data object's tag or 0x0000 if not found
//
DLLEXPORT tWord dtxPopDataObjectFromDataToSend(tDataExchangeList *data, tDataObject *object);

//---------------------------------------------------------
//            dtxIsListEmpty()
//---------------------------------------------------------
//	Return bTRUE if list is empty
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tBoolean dtxIsListEmpty(tDataObjectList *list);

//---------------------------------------------------------
//            dtxPushItemToList()
//---------------------------------------------------------
//	Push an item in the list. Update it if exist (perform a simple copy, i.e. no dynamic allocation)
//	If list is full, nothing's done
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtxPushItemToList(const tDataObject *item, tDataObjectList *list);

//---------------------------------------------------------
//            dtxPopItemFromList()
//---------------------------------------------------------
// Get data object from a list and remove it. Set dataObject = NULL 0x0000 if not found
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		tWord: data object's tag or 0x0000 if not found
//
DLLEXPORT tWord dtxPopItemFromList(tDataObject *dataObject, tDataObjectList *list);

//---------------------------------------------------------
//            dtxPopTagFromList()
//---------------------------------------------------------
// Get tag from a list and remove it. Return 0x0000 if not found
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		tWord: data object's tag or 0x0000 if not found
//
//
DLLEXPORT tWord dtxPopTagFromList(tDataObjectList *list);

//---------------------------------------------------------
//            dtxGetFirstTag()
//---------------------------------------------------------
// Get the first tag found from a list of tags. Return 0x0000 if not found
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		tWord: data object's tag or 0x0000 if not found
//
//
DLLEXPORT tWord dtxGetFirstTag(tDataObjectList *list);

//---------------------------------------------------------
//            dtxAddListToList()
//---------------------------------------------------------
// Add list1 to the list2 if they have the same type
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtxAddListToList(tDataObjectList *list1, tDataObjectList *list2);

//---------------------------------------------------------
//            dtxAddTagListToList()
//---------------------------------------------------------
// Add the first list of tags to the second list (if tlTAG_LIST type)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtxAddTagListToList(tByte *tagsList, tWord tagListLen, tDataObjectList *list);

//---------------------------------------------------------
//            dtxRemoveTag()
//---------------------------------------------------------
// Remove tag from a list of tags  (if tlTAG_LIST type)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		tWord: data object's tag or 0x0000 if not found
//
//
DLLEXPORT void dtxRemoveTag(tWord tag, tDataObjectList *list);

//---------------------------------------------------------
//            dtxFindTag()
//---------------------------------------------------------
// Find tag from a list of tags  (if tlTAG_LIST type)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
//	Returned values:
//
//		tByte: tag's position if found
//
//
DLLEXPORT tByte dtxFindTag(tWord tag, tDataObjectList *list);

//---------------------------------------------------------
//            dtxSerializeListForDEKDET()
//---------------------------------------------------------
// Serialize an object list. If data = null then return length to be serialized
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void dtxSerializeListForDEKDET(tDataObjectList *list, tByte *data, tWord *dataLen);

//---------------------------------------------------------
//            dtxGetItemAtFromList()
//---------------------------------------------------------
// Get an item from a list at a specified index (if tlTAG_LIST type)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//	Returned values:
//
//		tWord: data object's tag or 0x0000 if not found
//
DLLEXPORT tWord dtxGetItemAtFromList(tByte at, tDataObjectList *list);

//---------------------------------------------------------
//            dtxFindItemFromList()
//---------------------------------------------------------
// Find and return a data object from a list
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//	Returned values:
//
//		tBoolean: bTrue if found
//
//
DLLEXPORT tBoolean dtxFindItemFromList(tDataObject *item, tDataObjectList *list);

//---------------------------------------------------------
//            dtxProcessDOLAndPushMissingTagsToDataNeeded()
//---------------------------------------------------------
//	Process a DOL a push missing tag to DataNeeded
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tBoolean dtxProcessDOLAndPushMissingTagsToDataNeeded(tSessionId session, tDataExchange* data, tWord dolTag);

#ifdef __cplusplus
}
#endif

#endif /* DATAXCHNG_H_ */
