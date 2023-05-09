#ifndef CORESRC_INCLUDE_COREUTILS_H_
#define CORESRC_INCLUDE_COREUTILS_H_

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
* File       	 : 		CoreUtils.h
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		09/08/2015
**************************************************************************/

/***************************************************************************
 * Includes
 **************************************************************************/
#include "AMPDataTypes.h"

// TMS Configuration Folder
#define TMS_CONFIG_FOLDER "../appcfg"

typedef enum {
	PAD_LEFT  = 0x01,
	PAD_RIGHT = 0x02,
	PAD_BOTH  = 0x03,	// Left & Right	
} PAD_POS; //4 Padding Position

int ChangeToUpper(int nValue);

BOOL EqualityCheck(const char szValue1[], const char szValue2[]);

int UnpackTARfile(const char *szTARfile, const char *szDestDir, BOOL bDelTARfile);

void RemovePadChar(char* szBuff, char cPad, PAD_POS PadPos = PAD_RIGHT);

char CalcLRC(unsigned char *pData, int iDataLen, unsigned char cInit);

char* GetTMSConfigFileName(char* szAppName);

char* RemoveFileExt(char *szFilename);

char* GetJulianDate(const char *szYYYYMMDD);

int HexToInt(char c);

int HexToAscii(char c, char d);

long HexToDec(const char *szHex);

char* RemoveEndSpaces(char* szValue);

#endif /* CORESRC_INCLUDE_COREUTILS_H_ */


