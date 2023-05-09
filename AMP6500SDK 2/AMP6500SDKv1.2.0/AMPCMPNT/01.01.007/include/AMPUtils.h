
#ifndef AMPUTILS_H_
#define AMPUTILS_H_

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
* File       	 : 		AMPUtils.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/09/2015
**************************************************************************/

#include <AMPDataTypes.h>
#include <AMPReturnCodes.h>
#include <AMPDefine.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define PLATFORM_AMPPOS_ONLY

#define DECIMAL '.'
#define COMMA ','

//Amount Formatter
#define ERR_MISSING_FORMAT 10234
#define ERR_FORMAT_TOO_LARGE 10235
#define ERR_FORMAT_TOO_SMALL 10236
#define ERR_NO_MAPPING_TO_FORMAT 10237
#define ERR_NO_EXPECTED_SIGN_CHAR 10238
#define ERR_CURRENCY_NO_MATCH 10239
#define ERR_NON_NUMERIC_AMOUNT 10240
#define ERR_EXPECT_CHAR_MISSING 10241

#define AMOUNT_MAXIMUM  60

#define CURRENCY_SYMBOL                 'C'
#define CURRENCY_SYMBOL_NO_PAD          'c'
#define SIGN_SYMBOL                     'S'
#define SIGN_SYMBOL_NO_PAD              's'
#define SIGN_SYMBOL_PLUS                'P'
#define SIGN_SYMBOL_PLUS_NO_PAD         'p'
#define NUMERIC_VALUE                   'N'
#define NUMERIC_VALUE_NO_PAD            'n'

#define LEFT		1
#define RIGHT		2

//! Returns the Library Version
const char* GetLibraryVersion(void);

//! Formats the amount string into the formatted amount string
char* formatAmt(char *dest, char *src, int DestBufSize, char *format, char *CurSymbol, char *Separator, int forcePad, int forcePadding);

//! Removes format characters (decimal, comma) from amount string
char* RemoveAmtFormat(char *dest, char *src, int DestBufSize, const char *FormatChars);

//! Converts an array of bin hex to an ascii hex string
void BinHexToAsciiHex(unsigned char * in, unsigned char* out, int hexpair);

//! Converts an ascii hex string to an array of bin hex
void AsciiHexToBinHex(unsigned char * in, unsigned char* out, int hexpair);

//! Modifies the string to remove trailing and leading spaces
char *TrimWhiteSpaces(char *str);

//!  All leading spaces from a string is removed, string is a null terminated string.
void TrimLeadZeroes(char* pchString);

//! Padding of a character
void pad_string(char* str,int padlen,char padval,int padtype);

//! Replacd a character on a string
void replace_char(char* str, char find, char replace);

//! Return Terminal Data and Time - YYYYMMDDhhmmss
void GetTerminalDateAndTime(char buffer[15]);
void GetPosTime(uint8_t *pszDate, uint8_t *pszTime);
void AddDaysOnDate(char date[10], int days);
void AddMinutesOnTime(char ExpDate[10], char ExpTime[6], int Minutes);
BOOL isUnlockDateTimeExpired(const char *ExpDate, const char *ExpTime);

void StartTickCount(void);
unsigned int GetTickCount(void);

//! File Operations
int copy_file(const char *from, const char  *to);
int move_file(const char *from, const char  *to);
void delete_file(const char* file);
uint64_t get_file_size(const char *file);
int Open_File(const char* fname);
int Seek_File(int fd);
int WriteToFile(int fd, const void *buf, size_t size);
int ReadFromFile(int fd, const void *buf, size_t size);
void Close_File(int fd);

//! Synchronize file data to its storage device
int sync_file(const char* szFileName);

//! Checks if File or Directory exist
BOOL IsFileExist(const char* fname);

//! Execute a linux command. Input and output are in ascii string
int ExecuteLinuxCmd(const char* cmd, char* outbuff, int outsize);

//! Creates a temporay file, the file is automatically deleted when the file is close or program exits
int CreateTempFile(void);

//! Creates Directory
int CreateDirectory(const char *pathname);

//! Initializes the Random Number Generator
void InitRandomNumberGenerator(void);

//! Generates a Random Integer Number between MIN and MAX
UINT GenerateRandomNumber(UINT Min, UINT Max);

//! System will Restart
void SystemReboot(void);

//! Checks if running on AMP POS Terminal
BOOL IsAMPPosTerminal(void);

//! Sets Terminal Date and Time (yyyymmddhhmmss)
//int SetTerminalDateTime(const char szDateTime[14+1]);
void SetTerminalDateTime(char *szDateTime);

//! Adjust DateTime by minutes (minus/plus minutes) (yyyymmddhhmmss)
int AdjustDateTimeByMinutes(const char szOrigDateTime[14+1], long lMinutes, char szNewDateTime[14+1]);

//! Gets the Terminal Serial Number
char* GetTerminalSerialNumber(void);

//! Returns the Terminal Firmware Version
char* GetFirmwareVersion(void);

//! Returns TRUE if current date is expired based on the start date and the number of days of expiration
BOOL IsExpiredToday(char *szStartDate, int nDaysExpiry);

#ifdef __cplusplus
}
#endif

#endif /* AMPUTILS_H_ */

