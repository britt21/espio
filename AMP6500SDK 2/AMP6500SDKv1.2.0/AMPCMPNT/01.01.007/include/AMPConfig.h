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
* File       	 : 		AMPMenu.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/24/2015
**************************************************************************/

#ifndef AMPCONFIG_H_
#define AMPCONFIG_H_

// Project Header
#include "tinyxml2.h"
#include "AMPDataTypes.h"

// Config Filename (Hard-coded value and should not be configurable!)
//#define AMP_CONFIG_PATH			"../config/"
#define AMP_CONFIG_FILENAME		"param.cfg"	//AMP_CONFIG_PATH "param.cfg"

// TMS Configuration Section
#define TMS_APPLICATION_SECTION		"Application"

#define MAX_PARAM_VAL_LEN		256
#define MAX_KEY_LEN 			256

// Return Values
#define AMP_CFG_PARAM_EXISTING		-1000
#define AMP_CFG_PARAM_NOT_EXIST		-1001
#define AMP_CFG_PARAM_NO_CHILD		-1002
#define AMP_CFG_PARAM_NO_TEXT		-1003


using namespace tinyxml2;

typedef int (*TMS_CONFIG_CB)(const char *Section, const char *Key, const char *Value, const void *AMPConfig);
int DumpAllTMSCfg(const char *section, const char *key, const char *value, const void *amp_config);

class cAMPConfig
{
  public:
	  //! Constructor
	  cAMPConfig();
	//! Get Config Object
//	static cAMPConfig * getConfigObj();
  	
	//! Destructor
	//! Opens the config file and loads all data onto the memory (calls the LoadConfigFile function)
	virtual int OpenConfig();
	virtual ~cAMPConfig();

	//! Opens the config file and loads all data onto the memory (calls the LoadConfigFile function)
	virtual int OpenConfig(const char* filename);
	//! Should close the config file but does nothing! (Not necessary)
	virtual void CloseConfig();
	//! Saves all of the data/parameter changes in the config memory onto the XML config file
	virtual int SaveConfigFile();
	//! Delete Config File
	virtual void DeleteConfigFile();

	//! Gets the parameter value based on Key from the config memory (needs a buffer value container)
	virtual int GetParamVal(const char *Key, char *szBuff, int nBuffLen);
	//! Sets the parameter value based on Key into the config memory
	virtual int SetParamVal(const char *Key, const char *szValue, int nValLen);

	//! Sets the parameter name based on the specified Key.
	int SetParamName(const char *Key, const char *szNewKeyName);

	//! Returns the integer value of the parameter based on Key from the config memory 
	int GetParamInt(const char *Key);
	//! Sets the integer value of the parameter based on Key into the config memory 
	int SetParamInt(const char *Key, int nValue);

	//! Returns the long integer value of the parameter based on Key from the config memory 
	long GetParamLong(const char *Key);
	//! Sets the long integer value of the parameter based on Key into the config memory 
	int SetParamLong(const char *Key, long lnValue);

	//! Deletes the specified Key in the parameters (also deletes parents if they have no child left)
	int DeleteParam(const char *Key);

	//! Returns TRUE if the specified Key exists.  Returns FALSE if not.
	BOOL IsParamExisting(const char *Key);
	//! Gets the name of the first child of the specified Key.
	int GetFirstChildName(const char *Key, char *szBuffer, int nBuffSize);
	//! Gets the name of the next child (or the sibling) specified by Key.  Key should include the child name returned by GetFirstChildName.
	int GetNextChildName(const char *Key, char *szBuffer, int nBuffSize);

	//! Gets the Error Code/ID. strError1 and strError2 returns possibly helpful diagnostic location or string
	virtual void GetError(int *nErrorID, char *strError1, char *strError2);

	//! Returns TRUE if config is already open
	virtual BOOL IsOpen();

	//! Apply TMS Config values the current config, default CB applies/merges all key/value.
	//!		Override the callback function if you need full control e.g. checking or skipping
	int ApplyUpdateFromTMS(const char* szTMSConfig, TMS_CONFIG_CB callback = DumpAllTMSCfg);

	//! Apply current config values to TMS Config
	int ApplyUpdateTMSConfig(const char* szTMSConfig, const char *key, const char *szValue, int nValLen);
	
	//! Copies the Config File to a Back Up file
	int BackUpConfig(const char* origFile, const char* backUpFile);

  protected:
	//! Opens the XML config file and loads all data/parameters onto the memory
	virtual int LoadConfigFile();

	//! Gets the node from the XML config file of the entered Key
	XMLNode* GetXMLNode(const char *Key);
	//! Gets subkeys from the main key given at GetParamVal function
	int GetKeyfromParam(const char *Key, int *nKeyIndex, char *szBuffer);

	//! Pointer to Static cAMPConfig Object
	//static cAMPConfig* ConfigObj;

  private:

	BOOL m_bOpen;

	XMLDocument *m_XMLDoc;
  
	//! Pointer to class name
	static char m_className[];

	//! Configuration Filename;
	char m_FileName[256];

};

#endif /* AMPCONFIG_H_ */

