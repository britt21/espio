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
* File       	 : 		AMPMsgTbl.h
* Library	 	 : 		AMP Component
* Date Coded  : 		07/02/2015
**************************************************************************/

#ifndef AMPMSGTBL_H_
#define AMPMSGTBL_H_

// Project Header
#include "tinyxml2.h"
#include "AMPDataTypes.h"

// Message Checking
#define AMP_MSGKEY_EXIST	 -1000
#define AMP_MSGKEY_NOT_EXIST -1001
#define AMP_LANGCODE_EXIST	-2000
#define AMP_LANGCODE_NOT_EXIST	-2001
#define MAX_MSGKEY_LEN		256


using namespace tinyxml2;

class cAMPMsgTbl
{
	public:

		//! Constructor
		cAMPMsgTbl();

		//! Destructor
		virtual ~cAMPMsgTbl();

		//! Opens MsgTable file and loads data into memory (calls LoadMsgTbl function )
		virtual int OpenMsgTbl(const char* Filename);

		//! Close the MsgTable file
		virtual void CloseMsgTbl(void);

		//! Set the current language
		void SetLanguageCode(const char* LangCode);

		//! Get Message Key from Message Table File
		char* GetMessage(const char *Key);

		//! Get Message Key from Message Table File based on Language Code
		//! Calls the GetLanguage to verify Language Code
		char* GetMessage(const char* szLangCode, const char *Key);
		
	protected:

		//! Opens XML MsgFile and loads all data/parameters onto the memory
		virtual int LoadMsgFile();

		//! Gets the node from the XML Message file based from the Key
		XMLNode* GetXMLMsgNode(const char *Key);

		//!Get the subkeys based from the main key in the GetMessage() function call
		int GetMsgKey (const char *Key, int *nKeyIndex, char * szBuffer);



	private:
		
		BOOL m_bMsgOpen;

		XMLDocument *m_XMLMsgDoc;
	  
		//! Pointer to class name
		static char m_className[];

		//! Message Table Filename;
		char m_MsgFileName[256];

		//! Language Code
		char szLangCode[25];
	
};


#endif /* AMPMSGTBL_H_ */
