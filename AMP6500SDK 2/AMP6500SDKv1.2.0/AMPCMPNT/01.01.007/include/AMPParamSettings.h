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
* File       	 : 		AMPParamSettings.h
* Library	 	 : 		AMP Component
* Date Coded  : 		09/05/2018
**************************************************************************/

#ifndef AMPPARAMSETTINGS_H_
#define AMPPARAMSETTINGS_H_

// AMP Library Header
#include "AMPDataTypes.h"
#include "AMPDefine.h"

// Project Header
#include "tinyxml2.h"

using namespace tinyxml2;

class cAMPParamSettings
{
  public:
	  //! Constructor
	  cAMPParamSettings();
  	
	//! Destructor
	virtual ~cAMPParamSettings();

	//! Loads the Input Parameters Settings File (NOTE: Include Full path of filename)
	virtual int LoadParamFile(const char *szFileName);

	//! Sets the Category Name Keyword
	virtual int SetCategoryKeyName(const char *szCategoryKey);
	//! Sets the Attribute Name Keyword
	virtual int SetAttributeKeyName(const char *szAttributeKey);

	//! Gets the 1st Category Name
	int GetFirstCategory(char *szCategoryName);

	//! Gets the Next Category Name
	int GetNextCategory(char *szCategoryName);

	//! Gets the Previous Category Name
	int GetPrevCategory(char *szCategoryName);

	//! Gets the 1st Record from a Category
	int GetFirstRecFromCategory(const char *szCategory, char *szTag, char *szType, char *szReadOnly, 
										char *szRequired, char *szDisplayName, char *szDisplay, char *szMaxLength);

	//! Gets the Next Record from a Category
	int GetNextRecFromCategory(const char *szCategory, char *szTag, char *szType, char *szReadOnly, 
										char *szRequired, char *szDisplayName, char *szDisplay, char *szMaxLength);

	//! Gets the Previous Record from a Category
	int GetPrevRecFromCategory(const char *szCategory, char *szTag, char *szType, char *szReadOnly, 
										char *szRequired, char *szDisplayName, char *szDisplay, char *szMaxLength);

  protected:
  	
	//! Closes the Parameter Settings File
	virtual int CloseParamFile();

	//! Gets the Value of Attribute from the current Node
	int GetAttribValueFromNode(XMLNode *pNode, const char* szAttrib, char *szValue);

	//! Search for the Category Name
	int SearchCategoryName(const char *szCategoryName);
  

  private:

	//! Pointer to the XML Document (the whole XML contents)
	XMLDocument *m_XMLDoc;

	//! Pointer to the current Node (used to browse the XML contents)
	XMLNode *m_pNode;

	//! Param Settings Filename;
	char m_FileName[MAX_STR_SZ];

	//! Category Key Name
	char m_szCategoryKey[MAX_STR_SZ];

	//! Attribute Key Name
	char m_szAttributeKey[MAX_STR_SZ];

	//! Pointer to class name
	static char m_className[];
};
	
#endif /* AMPXML_H_ */

