#ifndef AMPJSON_H_
#define AMPJSON_H_

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
* File       	 : 		AMPJson.h
* Library	 	 : 		AMP Component
* Date Coded  : 		08/17/2019
**************************************************************************/

// AMP Library Header
#include "AMPDataTypes.h"
#include "AMPDefine.h"

#include "cJSON.h"


class cAMPJson
{
public:
	//! Constructor
	cAMPJson();
  	
	//! Destructor
	~cAMPJson();

	// Key sample formats:
	// Root.ParamElem
	// Root.ParamArrayObject.1.Param1
	// Root.ParamArrayObject.1.Param2
	// Root.ParamArray.1

	//! Sets the JSON tag value based on Key
	int SetTagVal(const char *Key, const char *szValue);
	int SetTagNum(const char *Key, double num);
	int SetTagBool(const char *Key, BOOL bVal);
	int SetTagNull(const char *Key);
	
	
	//! Gets the JSON tag value based on Key (needs a buffer value container)
	int GetTagVal(const char *Key, char *OutBuff);
	double GetTagNum(const char *Key);
	BOOL GetTagBool(const char *Key);

	//! Reads and parses the JSON stream/string
	int SetStream(const char *JSONStream);

	//! Gets the JSON stream/string (Compact or Non-Compact)
	int GetStream(char *JSONStream, BOOL bCompact=FALSE);

	void TraverseJsonNode(void);

	//! Gets Root Key, returns key length otherwise A<
	int GetRootKey(char *OutBuff);

	void ClearContents(void);	

protected:
	cJSON* JsonFindValue(const char *Key, cJSON *JsonNode, BOOL bInsert=FALSE);
	cJSON* JsonFindObject(const char *Key, cJSON *JsonNode, BOOL bInsert=FALSE);
	cJSON* JsonFindArray(const char *Key, cJSON *JsonNode, BOOL bInsert=FALSE);

private:
	void TraverseJsonNode(cJSON *JsonNode);

	cJSON *m_JsonDoc;
	
	//! Pointer to class name
	static char m_className[];

};


#endif /*AMPJSON_H_*/
