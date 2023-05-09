
#ifndef CORECONFIG_H_
#define CORECONFIG_H_

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
* File       	 : 		TranObj.h
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		08/10/2015
**************************************************************************/

#include <string.h>
#include "CoreDefines.h"
#include <AMPAgnosConfig.h>

#define CONFIG_NO_VALUE "NONE"

extern char g_szTMSConfigFile[256];

//! Internal Don't use
const char* ConfigPath(const char *format, ...);

//! Macro for Formating Configuration Path
#define CFG_PATH(...) ConfigPath(__VA_ARGS__)

//! Get/Set for STRING. Get buffer size should include space for NULL terminator.
int GetCfgData(const char *key, void *buffer, const size_t buffer_len);
int PutCfgData(const char *key, const void *data_buffer, const size_t data_len);

//! Gets the next key specified by current key
int GetNextCfg(const char *currkey, char *nextkey, const size_t nextkey_len);

//! Get/Set for INT
int GetCfgInt(const char *key);
int SetCfgInt(const char *key, int nValue);

//! Get/Set for LONG
long GetCfgLong(const char *key);
int SetCfgLong(const char *key, long lnValue);

//! Get/Set for CHAR
char GetCfgChar(const char *key);
int SetCfgChar(const char *key, char chValue);

//! Get/Set for BOOL
BOOL GetCfgBool(const char *key);
int SetCfgBool(const char *key, BOOL bValue);

//! Get/Set for FLAG
FLAG GetCfgFlag(const char *key);
int SetCfgFlag(const char *key, FLAG fValue);

//! Check if a Config is present and has value
BOOL IsCfgHasValue(const char *key);

//! Delete Config
int DeleteCfg(const char *key);

//! Set to TMS Config
int PutTMSData(const char *key, const void *data_value, const size_t data_len);
int SetTMSFlag(const char *key, FLAG fValue);

//! Delete TMS Config Data
int DeleteTMSData(const char *key);


//2 AGNOS Config

//! Get Number of records in Agnos Config
int GetRecordCountAgnosCfg(tConfigType CfgType);

//! Get Record Data
int GetRecordAgnosCfg(tConfigType CfgType, const int iRecNumber, BYTE *Data, unsigned long *DataLen );

//! Get Record of CAKeys
tCAPK* GetRecordCAKeysXml(int iRecNumber);

//! Get EMV Tag Value
int GetTagValueAgnosCfg(tConfigType CfgType, unsigned char KernelID, BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType,  tConfigTransType TransType, unsigned long ulTag, BYTE *Value, unsigned long *ulLen);

//! Get TlvStream Tag Value
int	GetTlvTagValueAgnosCfg(const BYTE *TlvStream, const unsigned long ulTlvStreamLen, const unsigned long ulTag, BYTE *Value, unsigned long ulValueSize);

//! Get EMV Tag Value in String
int GetStrTagValue(tConfigType CfgType, unsigned char KernelID, BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType,  tConfigTransType TransType, unsigned long ulTag, char* BufferOut);

//! Get EMV Tag Value in Terminal Config
int GetTagValueTerminalCfg(unsigned long TagName, char* BufferOut);

//! Get EMV Tag Value in Processing Config
int GetTagValueProcessingCfg(BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType, unsigned long TagName, char* BufferOut);

//! Get EMV Tag Value in Entry Point Config
int GetTagValueEntryPointCfg(unsigned char KernelID, BYTE *AIDKey, unsigned char uAIDKeyLen, tProcessingType ProcType, tConfigTransType TransType, unsigned long TagName, char* BufferOut);


#endif /* CORECONFIG_H_ */

