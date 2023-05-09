
#ifndef AMPAGNOSEMV_H_
#define AMPAGNOSEMV_H_

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
* File       	 : 		AMPAgnosEmv.h
* Library	 	 : 		AMP Component
* Date Coded  : 		08/16/2016
**************************************************************************/

#include <AMPDataTypes.h>

#include <paymentMW.h>
#include <agnostypes.h>
#include <agnosinternal.h>
#include <selection.h>
#include "AMPAgnos.h"

typedef unsigned short tEmvError;

#define EmvL2NO_ERROR			0x0000		//normal 

#define EmvL2MUTE_ERROR			0x0001		//mute card, no atr

#define EmvL2READER_ERROR		0x0002		//reader error, gpi error

#define EmvL2SW6A81_ERROR		0x0003 		//Card blocked

#define EmvL2PROCESSING_ERROR		0x0004		//interrupted during exchange of APDU

#define EmvL2EMV_ERROR				0x0005		//generic error for handling purposes,
												//APDU response error from card
												//wrong usage of final selection function 
												

#define EmvL2SYSTEM_ERROR			0x0006		//invalid APDU send command

#define EmvL2NOMUTUAL_ERROR			0x0007		//NO mutual list

#define EmvL2NOMUTUAL_SW6A81_ERROR	0x0008		//NO mutual list and card blocked SW 6A81

#define EmvL2NOMUTUAL_SW6283_ERROR	0x0009		//No mutual list and card blocked SW 6283

#define EmvL2CANCEL_ERROR			0x000A		//User Cancel 

#define EmvL2ICC_FORMAT_ERROR		0x000B		//tags invalid format 
#define EmvL2ICC_MISSING_ERROR		0x000C		//Missing mandatory tags 5f24 (Exp Date), 5a(PAN), 8c(CDOL1), 8d (CDOL2)
												//missing other tags for GPO

#define EmvL2CVM_PROCESSING_ERROR	0x000D		//interrupted during exchange of APDU

#define EmvL2SERVICE_NOT_ALLOWED	0x000E		//Service not allowed 
#define EmvL2TXN_REJECTED			0x000F		//Transaction rejected




typedef void (*EmvReadRecordCB)(void);
typedef void (*EmvFlowCB)(tAgnosState currentState, tBoolean *stop, tBoolean *bypass);

typedef BOOL (*EmvExcludeAidCB)(tADF *pADF);

typedef void (*EmvMutualListCB)(tADFList *mutualList, tBoolean bCL);

typedef BOOL (*EmvPostFinalAppSelectCB)(tADF *pADF);


class cAMPAgnosEmv : public cAMPAgnos
{

public:


	static cAMPAgnosEmv *get_Instance(void);
	

	/*
	*	Initialization Methods
	*/
	//4 Only needs to be called once, to register the function callbacks
	//void EMVInitUserCallBack(AMP_EMVCB* UserCallback);
	//4 Must be call upon starting an EMV Transaction, preferrably right after Card Insert
	
	int InitTrans(void);
	int DeInitTrans(void);
	

	//2 Methods for EMV Transaction Flow 

	int SetTagListCollection(const BYTE *TagList, int TagListLen);
	int PowerOn(void);
	int EmvSelectApplication(void);
	int EmvSelectLanguage(void);
	int EmvSetTransactionalContext(void);
	tTransactionalContext* EmvGetTransactionalContext(void);
	tTerminalContext* EmvGetTerminalContext(void);
	
	int EmvOpenKernelSession(void);
	int EmvSetMandatoryTags(void);
	int EmvInitiateApplication(void);
	int EmvSetOnlineResponse(const unsigned char uARC[2], unsigned char uCID, const unsigned char *IssuerResponse, int IssuerRespLen);
	int EmvCompletion(void);
	int EmvCloseKernelSession(void);


	//! Sets Transaction PinBypass
	int EmvSetTransPinByPass(BOOL bPinByPass);

	//! Set Exit State for Initiate EMV Flow in EmvInitiateApplication())
	int EmvSetExitStateFlow(tAgnosState ExitState);

	int EmvSetNextStateFlow(tAgnosState NextState);

	int EmvSetCID(tByte CID);

	//! Sets Transaction PinBypass
	BOOL EmvGetTerminalPinByPass(void);


	//! To Check if mutual list is empty after application selection
	BOOL IsMutualListEmpty(void);

	//! To Check if mutual list is empty due to Card blocked after application selection
	BOOL IsCardBlocked(void);

	//! To check if last card used is an Interac Card that can be invoked after application selection
	BOOL EmvIsInteracCard(void);

	//! To check if to display Preferred Name based on the Issuer Code Tale and Addt't Term Capabilities
	BOOL EmvIsToDisplayPreferredName(void);

	//! To check if last card used is a VISA Debit Canada card
	BOOL EmvIsVisaDebitCanada(void);

	//! This sets the amount tag 9f01 and 81 directly in the kernel
	int EmvSetAuthorizedAmount(tAmount Amount);

	//! To set the Read Record callback
	void EmvSetReadRecordCB(EmvReadRecordCB cb);

	//! To set EMV flow callback, allows L3 layer to control the EMV flow
	void EmvSetFlowCB(EmvFlowCB cb);

	//! To set the Mutual List callback, allows L3 layer to preprocess the mutual list before final app selection
	void EmvSetMutualListCB(EmvMutualListCB cb);

	//! To set the Exclude AID callback, allows L3 layer to eliminate the Aid
	void EmvSetExcludeAidCB(EmvExcludeAidCB cb);

	//! Post Processing Final App Selection
	void EmvSetPostFinalAppSelectCB(EmvPostFinalAppSelectCB cb);

	tEmvError EmvGetError(void);


	//1 Quick Chip API Interface
	
	//! Return TRUE if transaction is Quick Chip trans so that application layer can adjust the flow of Authorisation Request
	BOOL EMVIsQuickChipTrans(void);

	//! Enable/Disable Quick Chip
	int EmvSetEnableQuickChip(BOOL bEnableFlag );

	//! Quick Chip Completion
	int EmvQuickChipCompletion(void);
	
	
	//1 U.S. Debit Final Selection

	//! Enable/Disable US Debit Final Application Selection
	int EmvSetEnableUSDebitFinalAppSelect(BOOL bEnableFlag );
	int EmvSetUSDebitMode(BOOL bCTLS, unsigned char Mode );
	int EmvSetUSDebitAIDListMode( unsigned char Mode, BOOL bCTLS=FALSE);

	//1 Interac Final Selection
	//! Enable/Disable Interac Final Application Selection
	int EmvSetInteracAppSelect(BOOL bInterac );
	int EmvSetInteracVisaOptOut(BOOL bOptOut, const char *AidStrList=NULL );


	//2 Agnos Level-2 API

	

	//2 Miscellaneous

	BOOL IsCardPresent(void);
	BOOL IsCardStillPresent(void);

	void RemoveChipCard(int TimeoutS=0);

	//! Internal use
	tPaymentError EmvFinalAppSelection(tADFList *mutualList, tBoolean bCL);

	//! Sends Get Data command
	int GetPinTryCounter(void);
	

	//! Internal use, for L2 to set Agnos State callback
	void EmvStateCB(tAgnosState currentState, tBoolean *stop, tBoolean *bypass);

	void DumpMutualList(tADFList *mutualList);



protected:

	cAMPAgnosEmv();
	virtual ~cAMPAgnosEmv();

	
	void SetPOSEntryMode(void);
	int GetLastError(void);

	BOOL IsLanguageSelectionSupported(void);

	tPaymentError EmvUSDebitFinalAppSelection (tADFList *mutualList, tByte *MLIndex, tBoolean bCL );
	tPaymentError EmvUSDebitFinalAppSelection_1(tADFList *mutualList, tByte *MLIndex, tBoolean bCL );
	tPaymentError EmvUSDebitFinalAppSelection_2(tADFList *mutualList, tByte *MLIndex, tBoolean bCL );

	int EmvPSESetLangPref(void);
	int EMVSetPPSERemainingFCI(tADFList *mutualList);

	BOOL EmvGetTag5F55(tByte *data, tByte dataLen, tByte *tag, int tagsize);
	BOOL EmvGetTag5F56(tByte *data, tByte dataLen, tByte *tag, int tagsize);
	BOOL EmvGetTag42(tByte *data, tByte dataLen, tByte *tag, int tagsize);

	int EmvGetFCI61ByAID(const BYTE *data, int datalen, const BYTE* byAID, int AIDLen, BYTE* value, int valuesize);


	BOOL EmvIsIssuerCodeTable(const tByte* AddtlTermCap, tByte IssuerCodeTable);

	BOOL EmvCheckVisaDebitCanada(tADF *AidInfo);	

	//For internal only
	void EmvReadRecorCB(void);
	void ExcludeAidCB(tADFList *mutualList, tBoolean bCL);
	

	//! Terminal Context
	tTerminalContext 		*m_pTerminalContext;

	//!The singleton instance
	static cAMPAgnosEmv * single;

	BOOL m_bCardBlocked;
	BOOL m_bMutualListEmpty;
	int m_USDebitModeExe;
	BOOL m_bVisaDebitCanada;	//EmvIsVisaDebitCanada

	BOOL m_bPreferredName;
	
private:

	tSessionId m_SessionId;
	BOOL m_bQuickChipTrans;

	//!ReadRecordCB
	EmvReadRecordCB m_ReadRecordCB;

	//EmvStateCB
	EmvFlowCB		m_EmvFlowCB;

	//Exclude AID
	EmvExcludeAidCB	m_EmvExcludeAidCB;

	//Mutual list Callback
	EmvMutualListCB m_EmvMutualListCB;

	//Post Processing of Final App Select
	EmvPostFinalAppSelectCB m_EmvPostFinalAppSelectCB;

	//! Processing Context
	tProcessingContext*		m_pProcessingContext;

	//! Transaction Context
	tTransactionalContext 	*m_pTransactionalContext;

	//! ADF List
	tADFList 				m_MutualList;


	//! Flag PSE Selection Performed
	tBoolean 				m_PSESelectionPerformed;

	//! TLV Stream (MAX 500bytes)
	tTLVStream				m_EMVData;

	tEmvError m_EmvError;

	static char m_className[];
	

};





#endif
