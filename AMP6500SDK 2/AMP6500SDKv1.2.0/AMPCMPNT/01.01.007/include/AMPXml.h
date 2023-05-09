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
* File       	 : 		AMPXml.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/28/2016
**************************************************************************/

#ifndef AMPXML_H_
#define AMPXML_H_

// AMP Library Header
#include "AMPDataTypes.h"
#include "AMPDefine.h"

// Project Header
#include "tinyxml2.h"

#define MAX_XMLTAG_LEN		50*2
#define MAX_XMLKEY_LEN		256

// Return Values
#define AMP_XMLTAG_EXISTING		-1000
#define AMP_XMLTAG_NOT_EXIST	-1001
#define AMP_XMLTAG_NO_CHILD		-1002
#define AMP_XMLTAG_NO_TEXT		-1003

#if 0
// Structure for XML Attribute Details
typedef struct _tXMLAttrDetails_
{
	char szAttrRecNo[MAX_STR_SZ+1];
	char szName[MAX_STR_SZ+1];
	char szValue[MAX_STR_SZ+1];
	
}tXMLAttrDetails;

// Structure for XML Attribute Records
typedef struct _tXMLAttribute_
{
	char szParentID[MAX_STR_SZ+1];
	char szRecordNo[MAX_STR_SZ+1];
	tXMLAttrDetails stAttrDetails;
	
}tXMLAttribute;

typedef enum {
	MODE_PARENT,
	MODE_CHILDREN
} MODE_TYPE;
#endif
using namespace tinyxml2;

class cAMPXml
{
  public:
	  //! Constructor
	  cAMPXml();
	  cAMPXml(BOOL bProcessEntities);
  	
	//! Destructor
	virtual ~cAMPXml();

	//! Clears the XML Document Object
	virtual void Clear(void);

	//! Adds a Declaration
	virtual int AddDeclaration(const char *Key, const char *szValue);
	//! Adds Unknown
	virtual int AddUnknown(const char *Key, const char *szValue);

	//! Gets the XML tag value based on Key (needs a buffer value container)
	virtual int GetTagVal(const char *Key, char *szBuff, int nBuffLen);
	//! Sets the XML tag value based on Key
	virtual int SetTagVal(const char *Key, const char *szValue, int nValLen);

	//! Gets the XML tag attribute value based on Key (needs a buffer value container)
	virtual int GetTagAttrib(const char *Key, const char *Attrib, char *szBuff, int nBuffLen);
	//! Sets the XML tag attribute value based on Key
	virtual int SetTagAttrib(const char *Key, const char *Attrib, const char *szValue, int nValLen);

	//! Gets the XML stream/string
	virtual void GetStream(char *XMLStream);
	//! Gets the XML stream/string (Compact or Non-Compact)
	virtual void GetStream(char *XMLStream, BOOL bCompact);
	//! Gets the size of the XML stream/string (Compact or Non-Compact)
	virtual int GetStreamSize(BOOL bCompact);
	//! Reads and parses the XML stream/string
	virtual int SetStream(const char *XMLStream);

	long GetTagLong(const char *Key);
	int SetTagLong(const char *Key, long lnValue);
	int GetTagInt(const char *Key);
	int SetTagInt(const char *Key, int nValue);

	//! Finds the Tag name of based on Key. This is the first function to navigate the XML structure
	int FindTagName(const char *Key);
	//! Gets the next Tag name of the current node
	int GetNextTagName(char *TagName);
	//! Gets the previous Tag name of the current node
	int GetPrevTagName(char *TagName);
	//! Gets the first child Tag name of the current node
	int GetChildTagName(char *TagName);
	//! Gets the parent name of the current node
	int GetParentTagName(char *TagName);
#if 0
	//! LoadXmlFile
	int LoadXmlFile(const char* filename);
	//! Read XML File Attributes based on Element key
	tXMLAttribute* ReadXmlFile(MODE_TYPE nMode, int *nSize = NULL);
	//! Close XML File
	int CloseXmlFile(void);
#endif
  protected:
	  //! Gets the node from the XML config file of the entered Key
	  XMLNode* GetXMLNode(const char *Key, BOOL bFillElement = FALSE);
	  //! Gets subkeys from the main key
	  int GetKeyfromParam(const char *Key, int *nKeyIndex, char *szBuffer, int* nElementIdx = NULL);
#if 0
	  //! Parse for elements and attributes	
	  tXMLAttribute* GetNextSibling(XMLNode* pNode, int nRecordCnt, int nGrpRecCnt, int nParentID, tXMLAttribute *stDataOut, int *nSize = NULL);
	  //! Parse for Attributes
	  tXMLAttribute* GetAttributes(XMLDocument *XMLDoc, MODE_TYPE nMode, int *nSize = NULL);
	  //! Set Attribute Field
	  void SetAttributeFields(tXMLAttribute *Dest, tXMLAttribute *Src);
#endif
  private:

	XMLDocument *m_XMLDoc;

	//! Pointer to class name
	static char m_className[];

	XMLNode *m_pNode;

};

#endif /* AMPXML_H_ */
