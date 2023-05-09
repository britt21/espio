#ifndef AMPAGNOSCONFIG_H_
#define AMPAGNOSCONFIG_H_

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
* File       	 : 		AMPAgnosConfig.h
* Library	 	 : 		AMP Component
* Date Coded  : 		09/05/2016
**************************************************************************/

#include <AMPDataTypes.h>
#include "BER-TLV.h"
#include "AMPAgnosConfigTagDefs.h"
#include <stdio.h>



#define MAX_FILENAME_SIZE 		256
#define MAX_CFG_DATA_SIZE		50000
#define MAX_PARAM_DATA_SIZE		512
#define MAX_CFG_AID_DATA_SIZE	256
#define DEFAULT_CFG_VERSION 	0xAA
#define MIN_CRL_REC_SIZE		9


#define MAX_MODULUS_SIZE 	248
#define MAX_EXPONENT_SIZE	0x03
#define CHECKSUM_SIZE		20
#define RID_SIZE			5

//CFG Filenames
#define TERMINAL_CFG_FILE 		"TERMINAL"
#define PROCESSING_CFG_FILE 	"PROCESSING"
#define ENTRY_POINT_CFG_FILE 	"ENTRY_POINT"
#define CAKEYS_CFG_FILE 		"CAKeys"
#define CAKEYS_XML_FILE 		"CAKeys.xml"
#define CRL_CFG_FILE 			"CRL"
#define CRL_XML_FILE 			"CRL.xml"


//CFG File Version No
#define MIN_CFG_VERSION 0xAA
#define MAX_CFG_VERSION 0xAF

//XML SECTION NAME
#define MAX_SECTION_NAME_LEN 	256

//Error return
#define PATH_NOT_FOUND		-1
#define FILE_NOT_FOUND		-2


//Kernel IDs
#define KERNEL_PURE			1
#define KERNEL_PAYPASS		2
#define KERNEL_PAYWAVE		3
#define KERNEL_EXPRESSPAY	4
#define KERNEL_JSPEEDY		5
#define KERNEL_DPAS			6
#define KERNEL_QUICKPASS	7
#define KERNEL_FLASH		0x41


#define MAX_KERNEL_ID		0xFF

typedef enum
{
	TERMINAL_CFG,
	PROCESSING_CFG,
	ENTRY_POINT_CFG,
	CAKEYS_CFG,
	CRL_CFG
}tConfigType;


typedef enum
{
	NO_PROC_TYPE,
	CT_PROC_TYPE,
	CTLS_PROC_TYPE

}tProcessingType;

typedef enum
{
	CFG_TRANS_PURCHASE,
	CFG_TRANS_CASH,
	CFG_TRANS_WITHCASHBACK,
	CFG_TRANS_REFUND,
	CFG_TRANS_MANUAL_CASH,
	CFG_TRANS_QUASI_CASH,
	CFG_TRANS_DEPOSIT,
	CFG_TRANS_INQUIRY,
	CFG_TRANS_PAYMENT,
	CFG_TRANS_TRANSFER,
	CFG_TRANS_ADMINISTRATIVE,
	CFG_TRANS_HOUSE_KEEPING,
	CFG_TRANS_RETRIEVAL,
	CFG_TRANS_UPDATE,
	CFG_TRANS_AUTHENTICATION,
	CFG_TRANS_MAX
	
}tConfigTransType;


typedef struct _tCAPK_
{
	BYTE RID[RID_SIZE];				
	BYTE Index;		
	BYTE ExpoLen; 						//0x01 or 0x03 as per EMV specs
	BYTE ModLen;  						//Max 248 as per EMV specs
	BYTE Exponent[MAX_EXPONENT_SIZE];	
	BYTE Modulus[MAX_MODULUS_SIZE];		
	BYTE Expiry[3];						//ddmmyy
	BYTE Checksum[CHECKSUM_SIZE];

	struct _tCAPK_ *pnext;
}tCAPK;

typedef struct _tCRL_
{
	BYTE RID[RID_SIZE];
	BYTE Index;	
	BYTE SerialNumber[3];

	struct _tCRL_ *pnext;
}tCRL;




class cAMPAgnosConfig
{

public:

	static cAMPAgnosConfig *get_Instance(void);

	//2 Main Configuration Interface

	//! Reads the configuration file and loads it in the memory for data processing
	int LoadAgnosConfig(tConfigType CfgType);

	//! Sets the value of the specified tag
	int SetFieldTagValueAgnosConfig(tConfigType CfgType, unsigned char KernelID, const BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType, tConfigTransType TransType, unsigned long ulTag, const BYTE *Value, unsigned long ulLen);

	//! Sets the value of the specified tlv tags
	int SetFieldTagValueAgnosConfig(tConfigType CfgType, unsigned char KernelID, const BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType,  tConfigTransType TransType, const BYTE *TlvParams, unsigned long ulTlvParamsLen);

	//! Gets the value of the specified tag
	int GetFieldTagValueAgnosConfig(tConfigType CfgType, unsigned char KernelID, const BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType,  tConfigTransType TransType, unsigned long ulTag, BYTE *Value, unsigned long *ulLen);

	//! Adds record to the given configuration (TERMINAL, PROCESSING, ENTRY_POINT)
	int AddRecordToAgnosConfig(tConfigType CfgType, unsigned char KernelID, const BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType, tConfigTransType TransType, const BYTE *TlvParams=NULL, unsigned long ulTlvParamsLen=0 );

	//! Deletes record in the given configuration (TERMINAL, PROCESSING, ENTRY_POINT)
	int DeleteRecordToAgnosConfig(tConfigType CfgType, unsigned char KernelID, const BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType, tConfigTransType TransType);

	//! Gets the set of parameters (TLV stream) by record number
	int GetRecordAgnosConfig(tConfigType CfgType, int RecNumber, BYTE *Data, unsigned long *DataLen );	

	//! Gets the record count 
	int GetRecordCountAgnosConfig(tConfigType CfgType );	

	//! Writes the data loaded in the memory to the specified configuration file
	int UpdateAgnosConfig(tConfigType CfgType);

	//! Clears data loaded in the memory (destroys list, tree structures)
	int ClearMemoryAgnosConfig(tConfigType CfgType);

	//! Gets the entire TLV stream parameters of the config (TERMINAL, PROCESSING, ENTRY_POINT)
	int GetTLVStreamAgnosConfig(tConfigType CfgType, BYTE *Buffer, unsigned long BufferSize, unsigned long *OutLen);

	//! Reads the config file
	int ReadTlvDataFromConfig(tConfigType CfgType, BYTE *TlvDataBuff, unsigned long *ulDataSize);

	//! Writes to config file
	int WriteTlvDataToConfig(tConfigType CfgType, BYTE *TlvDataBuff, unsigned long ulDataSize);

	//! Writes to Xml file
	int WriteTlvDataToXml(tConfigType CfgType);

	//! Set CAKeyXMLFile
	int SetCAKeyXMLFile(const char *szCAKeyFile );

	//! Set Configuration Path
	int SetConfigPath(const char *szPath );

	//! Set Configuration File Name
	int SetConfigFile(const char *szFileName, tConfigType ConfigType);


// TODO: Workaround for sequence order of PROCESSING
#if 0
	//! Sorts Processing AID-CTLS first then AID-CT, it will also re-index the ENTRY_POINT record
	int SortProcessingConfig();
#endif	

	//2 XML Utils

	//! Gets the Value of the given XML path (ex: "CAPKEYLIST._1.RID" )
	int GetXMLPathData(const char *szFileName, const char *path, unsigned char *buffer, unsigned int bufflen);

	//2 TLV Utils

	//! Gets tag value in the TLV stream
	//! returns length of value; 0 if error
	int GetTlvTagValue(const BYTE *TlvStream, unsigned long ulTlvStreamLen, unsigned long ulTag, BYTE *Value, unsigned long ulValueSize);

	//2 OTHER Utils

	//! Converts hex byte to string
	int  Hex2Asc(const unsigned char * in, int inLen, unsigned char* szOut);

	//! Converts string to hex byte
	int Asc2Hex(const unsigned char* szIn, unsigned char* out);


	//2 CAKeys Interface

	//! Loads CAKeys in memory
	int LoadCAKeysConfig(void);

	//! Adds Capk record to CAKeys list
	int AddCapkToCAKeys(const tCAPK *Capk);

	//! Deletes Capk record to CAKeys list
	int DeleteCapkToCAKeys(const BYTE *RID, BYTE Index);

	//! Gets CAPK record from the CAKeys list
	tCAPK* GetRecordCAKeysXml(int iRecNumber );

	//Writes CAPK list in XML format
	int WriteCAKeysXML(void);

	//2 CRL Interface

	//! Adds CRL record to CRL list
	int AddCrlToCRLConfig(const tCRL *pCrl);
	
	//! Deletes Capk record to CAKeys list
	int DeleteCrlToCRLConfig(const BYTE *RID, BYTE Index, const BYTE *SerialNo);

	//! Gets record from the CRL Configy
	tCRL* GetRecordCRLConfig(int iRecNumber );
	


protected:


	cAMPAgnosConfig();
	virtual ~cAMPAgnosConfig();

	//2 TERMINAL Configuration
	int LoadTerminalConfig(void);
	int SetFieldTagValueTerminalConfig(unsigned long ulTag, const BYTE *Value, unsigned long ulLen);
	int SetFieldTagValueTerminalConfig(const BYTE *TlvParams, unsigned long ulTlvParamsLen);

	int GetFieldTagValueTerminalConfig(unsigned long ulTag, BYTE *Value, unsigned long *ulLen);
	int AddTermRecordToTerminalConfig(void);
	int DeleteTermRecordToTerminalConfig(void);
	int GetRecordTerminalConfig(BYTE *Data, unsigned long *DataLen);
	int UpdateTerminalConfig(void);

	//2 PROCESSING Configuration
	int LoadProcessingConfig(void);
	int SetFieldTagValueProcessingConfig(const BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType, unsigned long ulTag, const BYTE *Value, unsigned long ulLen);
	int SetFieldTagValueProcessingConfig(const BYTE *AIDKey, unsigned char uAIDKeyLen,  tProcessingType ProcType, const BYTE *TlvParams, unsigned long ulTlvParamsLen);

	int GetFieldTagValueProcessingConfig(const BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType, unsigned long ulTag, BYTE *Value, unsigned long *ulLen);
	int AddAIDRecordToProcessingConfig(unsigned char KernelID, const BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType);
	int DeleteAIDRecordToProcessingConfig(const BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType);
	int UpdateProcessingConfig(void);

	//2 ENTRY_POINT Configuration
	int LoadEntryPointConfig(void);
	int SetFieldTagValueEntryPointConfig(unsigned char KernelID, const BYTE *AIDKey, unsigned char uAIDKeyLen, tConfigTransType TransType, unsigned long ulTag, const BYTE *Value, unsigned long ulLen);
	int SetFieldTagValueEntryPointConfig(unsigned char KernelID, const BYTE *AIDKey, unsigned char uAIDKeyLen, tConfigTransType TransType, const BYTE *TlvParams, unsigned long ulTlvParamsLen);
	
	int GetFieldTagValueEntryPointConfig(unsigned char KernelID, const BYTE *AIDKey, unsigned char uAIDKeyLen, tConfigTransType TransType, unsigned long ulTag, BYTE *Value, unsigned long *ulLen);
	int AddKATRecordToEntryPointConfig(unsigned char KernelID, const BYTE *AIDKey,  unsigned char uAIDKeyLen, tConfigTransType TransType);
	int DeleteKATRecordToEntryPointConfig(unsigned char KernelID, const BYTE *AIDKey, unsigned char uAIDKeyLen, tConfigTransType TransType);
	int UpdateEntryPointConfig(void);

	//2 Config To Xml
	int WriteTerminalToXml(void);
	int WriteProcessingToXml(void);
	int WriteEntryPointToXml(void);


	//2 CAKeys Configuration

	//! Loads CAKeys.xml file in memory
	int LoadCAKeysXMLConfig(void);

	//! Loads CAKeys.xml file in memory
	int LoadCAKeysTinyXMLConfig(void);

	//! Update CAKeys file
	int UpdateCAKeysConfig(void);

	//! Get record of CAKeys by record number
	int GetRecordCAKeysConfig(int iRecNumber, BYTE *Data, unsigned long *DataLen );

#if 0		
	//! Converts CAPK struct to binary format
	int CreateCAPKData(tCAPK *Capk, BYTE *byCapk, unsigned long *CapkLen);
#endif

	//! Clears the CAKeys List in memory
	int DestroyCAKeysList(void);
	
	
	//2 CRL Configuration
	
	//! Loads CRL file in memory
	int LoadCRLConfig(void);

	//! Update CRL file
	int UpdateCRLConfig(void);

	//! Gets record of CRL by record number
	int GetRecordCRLConfig(int iRecNumber, BYTE *Data, unsigned long *DataLen );

	//! Clears the CRL List in memory
	int DestroyCRLList(void);

	//2 Generic Functions
	int CheckSHAConfig(BYTE *Buffer, unsigned long Size);

	void ConvertULTag( unsigned long uTag, BYTE *arrTag, BYTE *arrTagLen);
	BER_TLV* SearchTLVConstructedByAid(const BYTE*AidKey, unsigned char AidKeyLen, tProcessingType ProcType, unsigned char *AIDIndex);
	BER_TLV* SearchTLVConstructedByKAT(unsigned char KernelID,  const BYTE* AidKey, unsigned char AidKeyLen, tConfigTransType TransType);
	int GetKernelTLVDefaultParams(unsigned char KernelID, BYTE *TlvStream, unsigned long *TlvStreamLen);
	int GetAIDIndexFromProcCfg(const BYTE* AidKey, unsigned char AidKeyLen, tProcessingType ProcType);

	tCAPK* SearchCapkToList(const BYTE *RID, BYTE Index);
	tCRL* SearchCrlToList(const BYTE *RID, BYTE Index, const BYTE *SerialNo);
	int GetCAKeysXMLPathData(FILE *fp, const char *path, unsigned char *buffer, unsigned int bufflen);

	
private:

	char m_szCAKeyXML[200];
	char m_szAgnosPath[200];
	
	BYTE m_pCfgVersionNo;

	BYTE m_BufferCfg[MAX_CFG_DATA_SIZE];
	BYTE *m_pBufferCfg;
	unsigned long m_BufferCfgLen;
	
	BER_TLV *m_pstTerminalCfg;
	BER_TLV *m_pstProcessingCfg;
	BER_TLV *m_pstEntryPointCfg;

	tCAPK *m_pCAKeysCfg;

	tCRL *m_pCRLCfg;

	//! Filenames
	char m_szTerminalCfg[MAX_FILENAME_SIZE];	//TERMINAL
	char m_szProcessingCfg[MAX_FILENAME_SIZE];	//PROCESSING
	char m_szEntryPointCfg[MAX_FILENAME_SIZE];	//ENTRY_POINT
	char m_szCAKeysCfg[MAX_FILENAME_SIZE];		//CAKeys
	char m_szCRLCfg[MAX_FILENAME_SIZE];		//CRL

	
	//!The singleton instance
	static cAMPAgnosConfig * single;

	static char m_className[];	

};





#endif  //AMPAGNOSCONFIG_H_

