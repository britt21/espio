
#ifndef AMPAGNOS_H_
#define AMPAGNOS_H_

/***************************************************************************
 * 
 * Copyright (C) 2015 by APEX, Inc.
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of APEX Co. LLC.
 **************************************************************************/

/**************************************************************************
* File       	 : 		AMPAgnos.h
* Library	 	 : 		AMP Component
* Date Coded  : 		08/03/2016
**************************************************************************/
//! This ensures application layer aligned with Agnos data structure
#ifndef PACKING
#define PACKING
#endif

#include <tlv.h>
#include <AMPDataTypes.h>

#include "paymentMW.h"
#include "AMPAgnosConfig.h"

#if defined(ANDROID)
	#define ENCRYPT_SENSITIVE_DATA
	#define CTLS_DETECT_DELAY
#endif

#ifdef ENCRYPT_SENSITIVE_DATA
typedef struct
{
	char Track1Masked[256];
	char Track2Masked[256];
	char Track1Encrypt[256];
	char Track2Encrypt[256];

	char PANMasked[64];
	char PANEncrypt[64];

} CARD_TRACK_DATA;
#endif

/* Keyboard Codes */
#define AMPKEY_POWER	0xF00A
#define AMPKEY_UP		0xF002
#define AMPKEY_DOWN		0xF003
#define AMPKEY_LEFT		AMPKEY_UP
#define AMPKEY_RIGHT	AMPKEY_DOWN
#define AMPKEY_MENU		0xF204
#define AMPKEY_FUNC		0xF202
#define AMPKEY_ALPHA	0xF201
#define AMPKEY_ENTER	0x000D
#define AMPKEY_CLEAR	0x0008
#define AMPKEY_CANCEL	0x001B
#define AMPKEY_0		0x0030
#define AMPKEY_1		0x0031
#define AMPKEY_2		0x0032
#define AMPKEY_3		0x0033
#define AMPKEY_4		0x0034
#define AMPKEY_5		0x0035
#define AMPKEY_6		0x0036
#define AMPKEY_7		0x0037
#define AMPKEY_8		0x0038
#define AMPKEY_9		0x0039


typedef enum 
{
	OUTCOME_NONE,
	OUTCOME_TRY_OTHER_INTERFACE,
	OUTCOME_OFFLINE_APPROVED,
	OUTCOME_OFFLINE_DECLINED,
	OUTCOME_OFFLINE_FAILED,
	OUTCOME_OFFLINE_NOT_ACCEPTED,
	OUTCOME_APPROVED,
	OUTCOME_DECLINED,
	OUTCOME_FAILED,
	OUTCOME_NOT_ACCEPTED,
	OUTCOME_CANCELLED,
	OUTCOME_SELECT_NXT_NOT_ACCEPTED,
	OUTCOME_SELECT_NXT_RETRY,
	OUTCOME_TRY_AGAIN,
	OUTCOME_ONLINE_REQUEST,
	OUTCOME_END_APPLICATION,
	OUTCOME_NOT_EMV_CARD_POOLED
}TRANS_OUTCOME;

typedef enum
{
	EP_NO_START,
	EP_START_A,
	EP_START_B,
	EP_START_C,
	EP_START_D,
	EP_START_K,
	EP_START_M,
	EP_START_L
}ENTRYPOINT;


//2 AMP Agnos Callback Structure - Function Prototype of callback functions for Display and Online PIN Entry Customizations
/*
These functions should be defined in the application layer to customize the display and Online PIN entry functions:

  CBAppSelection		- Application Selection for EMV Contact can be customized using this Callback function.
  CBLangSelection		- Language Selection customization. Priority for language selection and/or default language can be set by the application using this Callback function.
  CBDisplayMessage	- Screen/Message Display customization.  String messages come from the file "lang.ini", which depends on the current selected Language ID.
  CBSelectItemFromList	- Choice/Options Screen Display used for Application Selection and Language Selection.
  CBGpiSwitchLED		- 
*/
typedef struct 
{
	int				(*CBAppSelection) (tADFList *mutualList, BYTE *MLIndex, const tTerminalContext *terminal, BOOL CLMode);
	int				(*CBLangSelection) (unsigned char LangId, unsigned char StringId, int TimeOut, unsigned char *SelectedId);
	unsigned short	(*CBDisplayMessage) (unsigned char bClearScreen, unsigned char LangId, const char *szMessage, unsigned char MessageId);
	unsigned short	(*CBSelectItemFromList) (const char *arrItems[], unsigned char arrCount, const char *Title, int TimeOut, unsigned char *SelectedId);
	unsigned short	(*CBGpiSwitchLED) (unsigned char Led, unsigned char Flag, unsigned char Colour);
	void			(*CBDisplayPinEntryPrompt) (unsigned char bClearScreen, unsigned char LangId, const char *szMessage);
	unsigned short	(*CBOnlinePinEntry) (const char *PAN, int PANlen, unsigned char *PinBlock, int *PinBlockLen);
	void 			(*CBPinRetries) (int PinRetries);
#if !defined(ANDROID)
	void		    (*CBCardEntryDisplay) (const unsigned char SupportedEntryMethod);
#endif

	unsigned long (*CBGetCvmLimit) (const BYTE *byAid, BYTE AidLen);
	unsigned long (*CBGetNoCvmLimit) (const BYTE *byAid, BYTE AidLen);
	int	(*CBSelectDebitCredit)(const BYTE *byAid, BYTE AidLen);

	

	#if defined(ANDROID)
	unsigned short (*CBOfflinePinEntry) (char bEnciphered, unsigned int lan, int timeout, tEMVPubKey* pubkey, unsigned char *IccRandom, unsigned char *RespData);
	#endif
	
}AMPAGNOS_CB;

//! Log file
#define AGNOS_LOG_FILE	"AgnosLog.txt"


//! ARC Response
#define UNABLE_TO_GO_ONLINE 	"\x50\x50"
#define TECHNICAL_ISSUE 		"\x60\x60"
#define ISSUER_REFERRAL 		"\x30\x31"
#define AUTH_ACCEPTED			"\x30\x30"
#define AUTH_DECLINED			"\x30\x35" //old: "\x35\x31"

//! (CID) Cryptogram Information Data
#define ARQC					0x80
#define TC						0x40
#define AAC						0x00
#define UNDEFINED_CID			0xF7


//! Card Input Devices
#define BASE_DEVCARD_MSR		(1<<0) //-1
#define BASE_DEVCARD_CTLS		(1<<1) //-2
#define BASE_DEVCARD_ICC		(1<<2) //-4
#define BASE_DEVCARD_MANUAL		(1<<3) //-8
#define BASE_DEVCARD_ALL		(BASE_DEVCARD_MSR|BASE_DEVCARD_CTLS|BASE_DEVCARD_ICC|BASE_DEVCARD_MANUAL)

typedef enum
{
	CARD_ENTRY_NONE,
	CARD_ENTRY_MANUAL,		//PosEntryMode = 0x01
	CARD_ENTRY_SWIPE,		//PosEntryMode = 0x90
	CARD_ENTRY_INSERT,		//PosEntryMode = 0x50
	CARD_ENTRY_TAP,			//POSEnryMode	 = 0x07
	CARD_ENTRY_MIFARE_TAP,
	CARD_ENTRY_MULTI_CARD_TAP,
	CARD_ENTRY_TAP_MAG,		//POSEnryMode	 = 0x91
	CARD_ENTRY_FALLBACK		//POSEnryMode	 = 0x90
}CARD_ENTRY;

typedef enum
{
	AGN_PURCHASE,
	AGN_CASH,
	AGN_WITH_CASHBACK,
	AGN_REFUND,
	AGN_MANUAL_CASH,
	AGN_QUASI_CASH,
	AGN_DEPOSIT,
	AGN_INQUIRY,
	AGN_PAYMENT,
	AGN_TRANSFER,
	AGN_ADMINISTRATIVE,
	AGN_HOUSE_KEEPING,
	AGN_RETRIEVAL,
	AGN_UPDATE,
	AGN_AUTHENTICATION,
	AGN_CASH_DISBURSEMENT,
	AGN_PRE_AUTHORIZATION,
	AGN_UNDEFINED
}AGN_TRANS_TYPE;

typedef tPaymentContext 	PAYMENT_CONTXT;
typedef tOutComeParameter 	OUTCOME_CONTXT;


typedef struct {
	char 			mPATH[500];	// location for key files, logs
	char 			mCADCL[500];
	char 			mCADK[500];
	char 			mPINPAD[500];
	char 			mCERT[500];
	char 			mCRL[500];
	char 			mEFL[500];
	char 			mTRACE[500];
	char 			mLANG[500];
	char 			mCurrencyCode[10];
	unsigned char 	mCurrExponent;
	int				mTraceDepth;
	unsigned char	mAutomation;
	unsigned char	mSDK;
	unsigned char	mContactless;
	unsigned char	mKeyIn;
	unsigned char	mFallbackAID;
	unsigned char	mEntryPoint;
	unsigned char	mFileIntegrity;
	unsigned char	mDefaultTransactionType;
	unsigned char	mAlwaysReceipt;
	unsigned char	mDefaultLanguage;
	unsigned char	mDECallback;
	unsigned char	mEMVSelectionCallback;
	unsigned char	mKernelSelectionCallback;
	unsigned char	mLanguageSelectionCallback;
	unsigned char	mAmountSelectionCallback;
	unsigned char	mAccountSelection;
	unsigned char	mTransactionLooping;
	unsigned char	mSignal;
	unsigned char	mPollingTimeout;
//	unsigned char	mPPSEZip; // Mantis #000014: PPSE ZIP
	unsigned char	mLegacyZip; // Mantis #000014: PPSE ZIP
	unsigned char	mLegacyPayPass;
	unsigned char	mLegacyAmex;
	unsigned char	mLegacyJcb;
	unsigned char	mLegacyCup;
	unsigned char	mLegacyDpas;
	unsigned char	mLegacyVisa;
	
	unsigned char 	mErrLEDDisplay; //to display RED LED indicator
	unsigned char 	mUSDebitAppSel;
	unsigned char 	mUSDebitModeCT; // 1-Autoselect, 2=Manual select
	unsigned char 	mUSDebitModeCTLS; // 1-Autoselect, 2=Manual select
	unsigned char 	mUSDebitAIDListMode; // 1-US AID List, 2-Global AID List
	unsigned char 	mUSDebitAIDListModeCTLS; // 1-US AID List, 2-Global AID List
	unsigned char 	mQuickChip;
	unsigned char 	mEnableMifareDetect; //enable Mifare card detection in gpiTechnoPolling
	unsigned char 	mVisaDebitOptOut;	//enable Visa Debit Opt Out for Canada
	unsigned char 	mAidListExclusion;	//enable exclusion of AID List	
	unsigned char 	mInteracAppSelect; //enable Interac App Selection for Canada
	unsigned char 	mLogFile;		//enable  agnos logs in file

#ifdef ENCRYPT_SENSITIVE_DATA
	int				mEncryptKeyIdx;
	char			mEncryptFWVersion[20];
	bool			mAllowEncrypt;
	char			mEncryptType[20];
#endif

	unsigned char 	mCTLSBypassRemoveCard;	//1-bypasses ctls remove card procedure
	unsigned char 	mUseQuickChipAidList;
	
} tExecutionContext;


typedef struct {
	////////////////////////////////////////////////////////////////////
	// Information provided by Level3
	tAmount				mAmount;    					// EMV Tag 9F02 = "Amount, Authorized"  + "Amount, Other"
    tAmount				mCashBack;						// EMV Tag 9F03 = "Amount, Other"
	AGN_TRANS_TYPE		mTransactionType;				// EMV Tag 9C
	BYTE				mTransactionDate[3];			// EMV Tag 9A (yymmdd)
	BYTE				mTransactionTime[3];			// EMV Tag 9F21 (hhmmss)
    BYTE				mMerchantCustomData[20];		// EMV Tag 9F7C
	BYTE 				mTransactionCurrencyCode[2];	// EMV Tag 5F2A
	BYTE				mTransactionCurrencyExponent;	// EMV Tag 5F36
    BYTE				mTransactionCategoryCode;		// EMV Tag 9F53
    BYTE				mMerchantCategoryCode[2];		// EMV Tag 9F15
    BYTE				mMerchantID[15];				// EMV Tag 9F16
    BOOL  		        mForcedOnline;					// As per merchant decision
    unsigned long 		mTransactionSequenceCounter;		//ENMV Tag9F41
} tInitTransData;


class cAMPAgnos
{
public:

	//! Returns the single instance of the cAMPAgnos object.  Creates the cAMPAgnost object on the first function call.
	static cAMPAgnos* get_Instance(void);

	//! Returns the Agnos Kernel Version and the MiddleWare Version numbers
	void AboutAgnosFW(void);

	//! Returns AMPEMVL2 Library version and build details
	const char* GetLibVersion(void);

	//! Initialization routine of Agnos Framework
	int Initialize(void);

	//! Deinitialization routine of Agnos Framework
	int DeInitialize(void);

	//! Registers the Callback functions needed - refer to AMPAGNOS_CB structure definition
	void RegisterCallback(const AMPAGNOS_CB *callback);

	//! Initialization Transaction Routine, should be called before to perform payment
	int InitTrans(AGN_TRANS_TYPE TransType);

	//! Sets the InitTransData, an information provided by application layer
	int SetInitTransData( const tInitTransData *InitTransData);

	//! Returns the current InitTransData value
	int GetInitTransData( tInitTransData *InitTransData);

	//Returns the Payment Context
	tPaymentContext* GetPaymentContext(void);
#if 0	
	int SetAmount(unsigned long Amount);
#endif
	int SetAmount(tAmount Amount);
#if 0
	int SetCashbackAmount(unsigned long Amount);
#endif
	int SetCashbackAmount(tAmount Amount);
	int SetTransType(int TransType );

	//! Set/Get 5F2A Transaction Currency Code
	int SetTransCurrCode( const BYTE CurrCode[2]);
	
	int GetTransCurrCode( BYTE *CurrCode);

	//! Set/Get 9F41 Transaction Sequence Counter
	int SetTransSeqCounter( unsigned long SeqNo);
	unsigned long GetTransSeqCounter(void);


	int SetSupprtdCardEntry(unsigned int SupportedCardEntry);

	int SetMifareDetection(BOOL bEnable);

	//! Sets internal card polling timeout (in secs, default if not set 30sec)
	int SetPollingTimeOut(unsigned int CardEntryTimeOut);

#ifdef CTLS_DETECT_DELAY
	void SetCTLSDetectDelayTimeOut(int nTimeOutMS);
#endif

	//! Detects card entry 
	int CardEntryPolling(unsigned int CardEntryTimeOut, USHORT *AddlStatus);

#if 0
	//! Set list of MAX PIN Length used in PIN Entry, default is "4,5,6,7,8,9,10,11,12"
	int SetMaxPinLength(const char *szMaxPINLength);
#endif
	//! Set list of Expected PIN Length used in PIN Entry, default is "4,5,6,7,8,9,10,11,12"
	int SetExpectedPinLen(const char *szExpectedPinLen);
	char* GetExpectedPinLen(void);

	int ExecuteTrans(ENTRYPOINT EntryPoint);
	BOOL IsRequireOnlinePin(void);

	void  BeepError(void);
	void  BeepLongError(void);
	void  BeepSuccess(void);


	unsigned char GetDefLanguageCodeID(const char *langCode);
	int SetDefLanguageCodeID(const char *langCode);

	//! Get Language Code
	unsigned char GetCurrentLangCodeId(void);

	//! Sets the List of AID to be excluded during Final Selection
	//! comma delimited list (ex: "A0001111000, A000033333300"
	int SetAidListExclusion(const char *szAidList);

	int CloseGpiDeviceReader(BYTE CardReader);

#ifdef ENCRYPT_SENSITIVE_DATA
	CARD_TRACK_DATA* GetCardTrackData(int CardEntryMethod);
	BOOL IsKeyEncryptPresent(void);	
#endif

	int ReadMagstripe(unsigned char *Track1, int *Track1Len, unsigned char *Track2, int *Track2Len, unsigned char *Track3, int *Track3Len);

	int GetEMVTlvData(unsigned char *Buffer, int BufferSize);

	int LogContext();
	
	void DisplayMessageById( int MessageId );

	int GetTlvTagValue(const BYTE *TlvStream, unsigned long ulTlvStreamLen, unsigned long ulTag, BYTE *Value, unsigned long ulValueSize); //returns length

	
	//2 Level-2 API 
	int EmvSetTag( unsigned short Tag, BYTE length, const BYTE *value);

	int EmvGetKernelId(BYTE *Buffer, int BufferSize);
	
	//int EmvGetTag( unsigned short Tag, BYTE *length, BYTE *value);

	int EmvGetTag(unsigned long TagName, BYTE *value, int valuesize); //returns length, or AMP_ERROR

	//! Find specified tag by traversing constructed tag element
	int EmvGetTag(const BYTE *TlvData, int TlvLen, unsigned long TagName, BYTE *value, int valuesize);

	int EmvGetAIDInfo(BYTE *Buffer, int BufferSize);
	int EmvGetApplicationLabel(BYTE *Buffer, int BufferSize);
	int EmvGetPreferredName(BYTE *Buffer, int BufferSize);
	int EmvGetTransCategoryCode(BYTE *Buffer, int BufferSize);
	int EmvGetAuthRespCode(BYTE *Buffer, int BufferSize);
	int EmvGetPAN(BYTE *Buffer, int BufferSize);
	int EmvGetIssuerScriptResult(BYTE *Buffer, int BufferSize);


	//! Set Debugging Port
	void SetDebugLogPort(const char *szAppName, int nLogPort);

#if 0
	//! internal used for extended process of Payment Context using callback member
	void PaymentCBGetEMVData( tLevel3DataExchange *data );
#endif
	//! Set Agnos Ini Path (agnos.ini, lang.ini, CAKeys.xml, QuickChip.cfg, USDebit.cfg)
	int SetIniPath(const char *szPath );

	//! Set Configuration Path (apps, TERMINAL, PROCESSING, ENTRY_POINT, CAKeys, CRL, *.so)
	int SetConfigPath(const char *szPath );

	//! Set Entry Point Libraries Path
	int SetEnpLibsPath(const char *szPath);

	//! Set Configuration File Name
	int SetConfigFile(const char *szFileName, tConfigType ConfigType);

#ifndef ANDROID
	//! Sets a Cancel key on the keyboard buffer (to emulate a cancel keypress)
	int SetCancelKey(void);
#endif

	//! Sets language support
	int SetLangSupport(const char *szLangList );

	//! Enables FarePod mode
	void EnableFarePod(BOOL bEnable);

	BOOL IsAIDUSDebit(const BYTE *byAID, int AIDLen);

	int GetLanguageCodeOfId(int LangId, char *LangCode);

	void SetUseQuickChipAidList(BOOL bEnable);

protected:

	cAMPAgnos();
	virtual ~cAMPAgnos();

	//! Quick Chip AID List
	int LoadQuickChipAIDList(void);
	BOOL IsAIDQuickChip(const BYTE *byAID, int AIDLen);

	//! US Debit AID List
	int LoadUSDebitAIDList(void);
	//BOOL IsAIDUSDebit(const BYTE *byAID, int AIDLen);

#ifdef ENCRYPT_SENSITIVE_DATA
	int EncryptCardData(const char *EncryptType, unsigned int KeyIndex, unsigned char *InpData, unsigned int InpDataLen, char *szOutData);
#endif

	//! An extension function of TLV of Agnos - for internal use only
	int EmvTlvFindTag(const BYTE *TlvData, int TlvLen, cursor_t *cursor, unsigned long TagName, BYTE *value, int valuesize);

	char m_szQuickChipAIDList[MAX_SUPPORTED_AID][32+1]; //holds the AID Quick Chip
	int m_QuickChipCount;


	char m_szUSDebitAIDList[MAX_SUPPORTED_AID][32+1]; //holds the AID Quick Chip
	int m_USDebitCount;
	
	//!Holds Parameters needed by Agnos Framework
	tExecutionContext 	*m_pExeContext;
	
	//!Holds Payment Context
	tPaymentContext	*m_pPaymentContext;
	
	//!Holds Outcome Context 
	tOutComeParameter	*m_pOutComeContext;

	//!Holds Amount 
	tAmount m_Amount;
	//!Holds Cashback Amount 
	tAmount m_CashbackAmnt;

	//! Setup Execution Parameters of Agnos Framework
	int SetContext(void);

	int SetGPIOption(void);

	AMPAGNOS_CB m_AgnosCallback;
	AMPAGNOS_CB *m_pAgnosCallback;

	//! ./
	char m_szIniPath[200]; //with '/'

	//!AGNOS Path "./AGNOS/"
	char m_szAgnosPath[200];
	char m_szIniFile[200];
	char m_szEnpLibsPath[500];

	//! Filenames
	char m_szTerminalCfg[MAX_FILENAME_SIZE];	//TERMINAL
	char m_szProcessingCfg[MAX_FILENAME_SIZE];	//PROCESSING
	char m_szEntryPointCfg[MAX_FILENAME_SIZE];	//ENTRY_POINT
	char m_szCAKeysCfg[MAX_FILENAME_SIZE];		//CAKeys
	char m_szCRLCfg[MAX_FILENAME_SIZE];		//CRL
	

	unsigned char m_SupprtdCardEntry;
	unsigned int  m_CardEntryTimeOut;


	tByte m_TagList[MAX_STREAM_SIZE];
	int m_TagListLen;

#ifdef ENCRYPT_SENSITIVE_DATA
	BOOL m_bKeyEncryptPresent;
#endif

	//! Pointer to class name
	static char m_className[];

	static cAMPAgnos *single;

private:
	tTLVStream m_tlvStreamCB;

};




#endif /*AMPAGNOS_H_*/

