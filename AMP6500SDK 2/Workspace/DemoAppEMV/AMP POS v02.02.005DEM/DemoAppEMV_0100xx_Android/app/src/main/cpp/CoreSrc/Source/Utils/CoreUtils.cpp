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
* File       	 : 		CoreUtils.cpp
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		09/08/2015
**************************************************************************/

/***************************************************************************
 * Includes
 **************************************************************************/

// System Library
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// AMP Library
#include "AMPDataTypes.h"
#include "AMPDefine.h"

// Project Header
#include "CoreUtils.h"

int ChangeToUpper(int nValue)
{
	if(nValue >= 'a' && nValue <= 'z')
	{
		return nValue + 'A' - 'a';
	}
	else
	{
		return nValue;
	}
}

char* ChangeToLower(char *szData)
{
	char* pData = szData;

	while(*pData)
	{
		*pData = tolower(*pData);
		pData++;
	}

	return szData;
}

BOOL EqualityCheck(const char szValue1[], const char szValue2[])
{
	int i = 0;
	BOOL bEqual;

	while(szValue1[i] == szValue2[i] && szValue1[i] != '\0' && szValue2[i] != '\0') {
		i++;
	}
	
	if(szValue1[i] == '\0' && szValue2[i] == '\0') 
		bEqual = TRUE;
	else
		bEqual = FALSE;

	return bEqual;
}

void RemovePadChar(char* szBuff, char cPad, PAD_POS PadPos)
{
	int iStrLen, iDX;

	if(!szBuff || !szBuff[0] || !cPad)
		return;

	if(PadPos & PAD_RIGHT)
	{
		iStrLen = strlen(szBuff);
		for(iDX = iStrLen - 1; iDX >= 0; iDX--)
		{
			if(szBuff[iDX] == cPad)
			{
				szBuff[iDX] = NULL;
				break;
			}
		}
	}

	if(PadPos & PAD_LEFT)
	{
		iDX = 0;
		while(szBuff[iDX] == cPad)
			iDX++;
		if(iDX)
		{
			iStrLen = strlen(szBuff+iDX);
			memmove(szBuff, szBuff+iDX, (size_t) iStrLen);
			szBuff[iStrLen] = NULL;
		}
	}
}

char CalcLRC(unsigned char *pData, int iDataLen, unsigned char cInit)
{
	while( iDataLen > 0 )
	{
		cInit ^= *pData++;
		iDataLen--;
	}
	
	return cInit;
}

char* GetTMSConfigFileName(char* szAppName)
{
    FILE *pf;
	char FindCmd[64] = { 0 };
	static char OutBuff[128] = { 0 };
	int iLen = 0;
	char szConfigFiles[256][MAX_STR_SZ+1];
	char *Start = OutBuff, *End = OutBuff;
	int nLines = 0;
	int i = 0;
	static char szFinalCfg[MAX_STR_SZ+1] = { 0 };
	char szShortName[MAX_STR_SZ+1] = { 0 };
	char *pShortName = NULL;
	BOOL bFound = FALSE;
	char szOrigName[256][MAX_STR_SZ+1];

	// Memset output buffer
	memset(OutBuff, 0, sizeof(OutBuff));

	// Browse for INI or TXT file in the appcfg folder
    sprintf(FindCmd, "find %s -iname \"*.txt\" 2> /dev/null", TMS_CONFIG_FOLDER);
	//sprintf(FindCmd, "find %s -iname \"*.ini\" 2> /dev/null", TMS_CONFIG_FOLDER);
	
	if((pf = popen(FindCmd, "r")) != NULL)
	{
	    while(fgets(OutBuff + iLen, sizeof(OutBuff) - iLen - 1, pf) != NULL)
			iLen += strlen(OutBuff + iLen);
	    pclose(pf);
	}

	// Get short name from the Application Name
	memset(szShortName, 0, sizeof(szShortName));
	if(strstr(szAppName, "-") != NULL)
	{
		pShortName = strchr(szAppName, '-');
		memcpy(szShortName, pShortName+1, strlen(pShortName)-1);
	}
	else
		strcpy(szShortName, szAppName);

	// Parse List of Configuration Files (MultiApp download Support)
	memset(szOrigName, 0, sizeof(szOrigName));
	memset(szConfigFiles, 0, sizeof(szConfigFiles));
	while(End != NULL)
	{
		End = strchr(Start+1, '\n');
		if(End != NULL)
		{
			strncpy(szConfigFiles[i],
					(*Start != '\n') ? Start : Start+1,
					(*Start != '\n') ? End-Start : End-Start-1);

			// Check if the short name match to the list of config file names
			strcpy(szOrigName[i], szConfigFiles[i]);
			if(strstr(ChangeToLower(szConfigFiles[i]), ChangeToLower(szShortName)) != NULL)
			{
				memset(szFinalCfg, 0, sizeof(szFinalCfg));
				strcpy(szFinalCfg, szOrigName[i]);
				bFound = TRUE;
				break;
			}
			else
				bFound = FALSE;
			nLines++;
		}
		Start = End;
		i++;
	}

    return szFinalCfg;
}

char* GetJulianDate(const char *szYYYYMMDD)
{
	static char JulianDate[5+1] = { 0 };	// yyddd format (Output Format)

	char szCurrYear[4+1] = { 0 };
	char szCurrMonth[2+1] = { 0 };
	char szCurrDay[2+1] = { 0 };

	int iCurrYear = 0;
	int iCurrMonth = 0;
	int iCurrDay = 0;

	static const int month_len[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int leap = 0;
	int iDayOfYear = 0;
	char szDayOfYear[3+1] = { 0 };

	memcpy(szCurrYear,	&szYYYYMMDD[0], 4);
	memcpy(szCurrMonth,	&szYYYYMMDD[4], 2);
	memcpy(szCurrDay,	&szYYYYMMDD[6], 2);

	iCurrYear	= atoi(szCurrYear);
	iCurrMonth	= atoi(szCurrMonth);
	iCurrDay	= atoi(szCurrDay);

	leap = (iCurrYear % 4 == 0) && (iCurrYear % 100 != 0 || iCurrYear % 400 == 0);

	for (int month = 0; month < iCurrMonth; month ++)
	{
		int mlen = month_len[month];

		if (leap && month == 1)
			mlen ++;

		if(month == (iCurrMonth-1))
			iDayOfYear += iCurrDay;
		else
			iDayOfYear += mlen;
	}

	sprintf(szDayOfYear, "%03d", iDayOfYear);
	
	memcpy(&JulianDate[0], &szCurrYear[2], 2);	// yy
	memcpy(&JulianDate[2], szDayOfYear, 3);		// ddd

	return JulianDate;
}

int HexToInt(char c)
{
    int first = c / 16 - 3;
    int second = c % 16;
    int result = first*10 + second;
    if(result > 9) result--;
    return result;
}

int HexToAscii(char c, char d)
{
    int high = HexToInt(c) * 16;
    int low = HexToInt(d);
    return high+low;
}

long HexToDec(const char *szHex)
{
	unsigned long result=0;
    int i;
    int length;
	
    length = strlen(szHex);
    for(i=0; i<length; i++)
	{
		/* 16-base = 2^4 = <<4 */
        result <<= 4; 

        if(szHex[i] > 96) /* a to f */
		{ 	
			/* hex[i]-'a'+10=hex[i]-97+10 */
        	result += (szHex[i]-87); 
        }
        else if(szHex[i] > 64) /* A to F */
		{ 
			/* hex[i]-'A'+10 */
        	result += (szHex[i]-55); 
        }
        else	/* 1 to 9 Digits */
		{ 				
        	result += szHex[i] & 0x0F;
        }
    }

	return result;
}

char* RemoveEndSpaces(char* szValue)
{
	int size;
	char *last;

	size = strlen(szValue);

	if(!size)
		return szValue;

	last = szValue +  size - 1;
	while(last >= szValue && isspace(*last))
		last--;
	*(last + 1) = '\0';

	while(*szValue && isspace(*szValue))
		szValue++;

	return szValue;
}



