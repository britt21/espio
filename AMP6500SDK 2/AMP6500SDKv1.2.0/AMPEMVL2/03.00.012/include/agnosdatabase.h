// NAME.......  agnosdatabase.h
// PURPOSE....  Tags container
// PROJECT....  AGNOSDB
// REFERENCES.	--
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//

#ifndef AGNOSDATABASE_H_
#define AGNOSDATABASE_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------
//			Include Files
//---------------------------------------------------------
//---- Local Headers ----
#include "emvtag.h"
//---- Global Headers ----
#include "gpi_agnos_framework_globals.h"

//---------------------------------------------------------
//			Definitions
//---------------------------------------------------------
// !!! Value aligned on Agnos errors !!!
#define adbNO_ERROR					0x4000
#define adbNO_ERROR_CONTINUE		0x4020
#define adbICC_FORMAT_ERROR			0x4043
#define adbREDUNDANT_TAG			0x4045

// Static allocation
#define MAX_SSAD_RECORD_NUMBER		30

// Database structure
#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	unsigned char*	mIndex[NUMBER_OF_DATA_ELEMENT]; 	// mIndex[i] points at the TLV's Value
	unsigned char	mLength[NUMBER_OF_DATA_ELEMENT]; 	// Maximum EMV TAG's length is 255
	unsigned char 	*mValue; 							// refers to a series T-L-V triplet data
	unsigned char*	mCursor; 							// mCursor points at the first mValue[i] available
	unsigned char*	mEnd;

	unsigned char*	mSSAD[MAX_SSAD_RECORD_NUMBER];  	// mSSAD[i] points at the TLV's TAG
	unsigned char	mNumberOfSSADRecord;
	unsigned short	mSSADLength[MAX_SSAD_RECORD_NUMBER];

	// Unknown tags management
	unsigned char	*mUnknownTags;
	unsigned short	mUnknowTagsLen;
	unsigned char	mUnknowTagsCount;

	unsigned char	mStrategy;

	// Patches for xxAddTag callback
	unsigned short	mCurrentTemplate;
	unsigned char	mPreviousTagInstanceLength;

} tTagDataBase;
#pragma pack()

typedef unsigned short (*AddTag_Contactless)(	tTagDataBase *db,
												enum DataElementIndex idx,const unsigned char checkRedundancy, const unsigned char rule);

//---------------------------------------------------------
//			Macros
//---------------------------------------------------------
#define TAG_INDEX(x,y)				x.mIndex[y] 		// Gets the TAG's address (stored in mIndex[])
#define SSAD(x,y)					x.mSSAD[y] 			// Gets the TAG's address (stored in mSSAD[])
#define TAG_LENGTH(x,y)				x.mLength[y]		// Gets the TAG's LENGTH
#define TAG_VALUE					*
#define TAG_EXIST(x,y)				x.mIndex[y]!=0		// Does the TAG exist? bTRUE if address is not null
#define CURSOR(x)					x.mCursor
#define TAG_ABSENT(x,y)				x.mIndex[y]==0		// Does the EMV Data absent? bTRUE if address is null
#define END_CURSOR(x)				x.mEnd

//---------------------------------------------------------
//			Public Primitives
//---------------------------------------------------------
DLLEXPORT char* adbGetVersionNumber(void);

DLLEXPORT void adbResetDataBase(tTagDataBase *db);
DLLEXPORT void adbDumpDataBase(tTagDataBase *db);
DLLEXPORT void adbSetStrategy(tTagDataBase *db, const unsigned char strategy);

DLLEXPORT unsigned short adbAddTag(tTagDataBase *db, enum DataElementIndex idx, const unsigned char checkRedundancy, const unsigned char rule);

DLLEXPORT unsigned short adbAddUnknownTag(tTagDataBase* db, const unsigned char* tlv, const unsigned char len);
DLLEXPORT unsigned char* adbGetUnknownTags(tTagDataBase* db);
DLLEXPORT unsigned short adbGetUnknownTagsLength(tTagDataBase* db);
DLLEXPORT unsigned char adbGetUnknownTagsCount(tTagDataBase* db);

DLLEXPORT void adbSetAddTagContactlessCallback(AddTag_Contactless callback);
DLLEXPORT void adbGetAllTLV(tTagDataBase*db, const unsigned char* buffer, unsigned short maxLength, unsigned short* actualLength);

#ifdef __cplusplus
}
#endif

#endif /* AGNOSDATABASE_H_ */
