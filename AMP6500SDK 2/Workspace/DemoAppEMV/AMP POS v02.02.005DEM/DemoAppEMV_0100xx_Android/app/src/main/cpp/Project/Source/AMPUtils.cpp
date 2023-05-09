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
* File       	 : 		AMPUtils.cpp
* Library	 	 : 		AMP Component
* Date Coded  : 		03/09/2015
**************************************************************************/

/***************************************************************************
 * Includes
 **************************************************************************/

// Standard Library
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

// AMP Library
#include <posapi.h>

// Project Header
#include "AMPUtils.h"
#include "AMPDefine.h"


/***************************************************************************
* Perprocessor Defines
**************************************************************************/

/***************************************************************************
* Globals
**************************************************************************/

static char AsciiHexLookup[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

/***************************************************************************
* Local Functions
**************************************************************************/
BOOL isLeapYear(int year);

typedef struct
{
    uint8_t       fid;
    uint8_t       attr;
    uint8_t       type;
    char		  name[17];
    uint32_t      length;
} FILE_INFO;

int fileOpen(const char *filename, int oflag, ...);
int fileSeek(int fd, off_t offset, int whence);
int fileRead(int fd, void *buf, size_t count);
int fileWrite(int fd, const void *buf, size_t count);
int fileClose(int fd);
int fileTruncate(int fd, off_t length);
int fileRemoveExt(const char *FileName, uint32_t BelongApp, uint32_t FileType);
int fileRemove(const char *filename);
int fileOpenExt(const char *FileName, uint32_t Mode, uint32_t BelongApp, uint32_t FileType);
int fileExistExt(const char *FileName, uint32_t BelongApp, uint32_t FileType);
int fileSizeExt(const char *FileName, uint32_t BelongApp, uint32_t FileType);
int fileGetInfo(FILE_INFO *pFileInfo);
int fileExist(const char *filename);
int fileSize(const char *filename);
int fileMakeDir(const char *pathname);

int fileOpen(const char *filename, int oflag, ...)
{
	int fd;

	if (oflag & O_CREAT) {
		int mode = 0644;
		
		fd = open(filename, oflag, mode);
	} else {
		fd = open(filename, oflag);
	}

	return fd;
}

int fileSeek(int fd, off_t offset, int whence)
{
	return lseek(fd, offset, whence);
}

int fileRead(int fd, void *buf, size_t count)
{
	return safety_read(fd, buf, count);
}

int fileWrite(int fd, const void *buf, size_t count)
{
	return safety_full_write(fd, buf, count);
}

int fileClose(int fd)
{
	return close(fd);
}

int fileTruncate(int fd, off_t length)
{
	return ftruncate(fd, length);
}

int fileRemoveExt(const char *FileName, uint32_t BelongApp, uint32_t FileType)
{
	return remove(FileName);
}

int fileRemove(const char *filename)
{
	return remove(filename);
}

int fileExistExt(const char *FileName, uint32_t BelongApp, uint32_t FileType)
{
	return fileExist(FileName);
}

/* Use it for file  that doesn't belong to current APP */
int fileOpenExt(const char *FileName, uint32_t Mode, uint32_t BelongApp, uint32_t FileType)
{
	int fd;
	if (Mode & O_CREAT)
		fd = open(FileName, Mode, 0644);
	else
		fd = open(FileName, Mode);
	return fd;
}

int fileSizeExt(const char *FileName, uint32_t BelongApp, uint32_t FileType)
{
	return fileSize(FileName);
}

int fileSize(const char *filename)
{
	struct stat	stat;
	int			retval;

	retval = lstat(filename, &stat);
	if (! retval)
		return stat.st_size;

	return -1;
}

int fileExist(const char *filename)
{
	return access(filename, F_OK);
}

int fileGetInfo(FILE_INFO *pFileInfo)
{
	return 0;
}

//create multiple folder
int fileMakeDir(const char *pathname)
{
	char dirname[512] = {0};
	int len, i;

	strncpy(dirname, pathname, sizeof(dirname)-1);

	len = strlen(dirname);
	if(dirname[len-1] != '/')
	{
			//printf("%C\n", dirname[len]);
			dirname[len] = '/';
			dirname[len+1] = 0;
			len = strlen(dirname);
	}

	for(i = 1; i < len; i++)
	{

		if(dirname[i] == '/')
		{
			dirname[i] = 0;
			if(access(dirname, 0) != 0)
			{
				if(mkdir(dirname, 0777) == -1)
				{
					perror("mkdir error: ");
					return -1;
				}
			}
			dirname[i] = '/';
		}
	}
	return 0;
}



/***************************************************************************
* Implementations
**************************************************************************/

void BinHexToAsciiHex(unsigned char * in, unsigned char* out, int hexpair)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return;
#endif
		
	int i, out_idx;

	for(i = 0, out_idx = 0; i < hexpair; ++i)
	{
		out[out_idx++] = AsciiHexLookup[(in[i] & 0xF0) >> 4];
		out[out_idx++] = AsciiHexLookup[in[i] & 0x0F];
	}
	out[out_idx] = 0;
}

void AsciiHexToBinHex(unsigned char * in, unsigned char* out, int hexpair)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return;
#endif

	int i, out_idx; 
	unsigned char hn, ln, ch;

	for (i = 0, out_idx = 0; i < (hexpair*2); i+=2, ++out_idx) 
	{
		ch = toupper(in[i]);
		hn = (ch > '9') ? (ch - 'A' + 10) : (ch - '0');
		ch = toupper(in[i+1]);
		ln = (ch > '9') ? (ch - 'A' + 10) : (ch - '0');

		out[out_idx] = ((hn << 4) & 0xF0) | (ln & 0x0F);
	}
}

int copy_file(const char *from, const char  *to)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return AMP_ERROR;
#endif

	FILE  *ptr_old, *ptr_new;
	int  a;

	ptr_old = fopen(from, "rb");
	ptr_new = fopen(to, "wb");

	if(ptr_old == NULL)
		return	AMP_ERROR;

	if(ptr_new == NULL)
	{
		fclose(ptr_old);
		return AMP_ERROR;
	}

	while(1)
	{
		a  =  fgetc(ptr_old);

		if(!feof(ptr_old))
			fputc(a, ptr_new);
		else
			break;
	}

	fclose(ptr_new);
	fclose(ptr_old);
	
	return AMP_SUCCESS;
}

int move_file(const char *from, const char  *to)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return AMP_ERROR;
#endif

	int iRetVal = AMP_SUCCESS;
	if((iRetVal = copy_file(from, to)) == AMP_SUCCESS)
		delete_file(from);
	return iRetVal;
}

void delete_file(const char* file)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return;
#endif

	remove(file);
}

int sync_file(const char* szFileName)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return AMP_ERROR;
#endif

	FILE* file;
	int file_no;

	if((szFileName != NULL) &&	((file = fopen(szFileName, "rb")) != NULL))
	{	
		file_no = fileno(file);
		fsync(file_no);
		fclose(file);

		return AMP_SUCCESS;
	}

	return AMP_ERROR;
}

uint64_t get_file_size(const char *file)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return 0;
#endif

	uint64_t ulSize = 0;
	struct stat st;

	if(stat(file, &st) != -1)
	{
		ulSize = st.st_size;
	}

	return ulSize;
}

int ExecuteLinuxCmd(const char* cmd, char* outbuff, int outsize)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return AMP_ERROR;
#endif

	int iRetVal = AMP_ERROR, iLen = 0;
    FILE *pf;

 	if(cmd && outbuff && outsize)
 	{
	    // Setup our pipe for reading and execute our command.
	    pf = popen(cmd, "r"); 

		if(pf != NULL)
		{
		    // Get the data from the process execution
		    while(fgets(outbuff + iLen, outsize - iLen - 1, pf) != NULL)
				iLen += strlen(outbuff + iLen);

			// Close pipe
		    pclose(pf);

			iRetVal = AMP_SUCCESS;
		}
 	}		

    return iRetVal;
}

int CreateTempFile()
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return AMP_ERROR;
#endif

	char szTmpFile[64] = { 0 };
	int Handle = -1;

	// Check if directory exist
	if(IsFileExist(UNIX_TMP_PATH) == FALSE)
		mkdir(UNIX_TMP_PATH, 0700);

	sprintf(szTmpFile,"%s%d-XXXXXX", UNIX_TMP_PATH, rand());

	// Create the temporary file
    Handle = mkstemp(szTmpFile);

    // Unlink so that whenever the file is closed or the program exits
    // 	the temporary file is automatically deleted
    unlink(szTmpFile);

	return Handle;
}

BOOL IsFileExist(const char* fname)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return FALSE;
#endif

	if( access( fname, F_OK ) != -1 ) 
		return TRUE;
	else
		return FALSE;
}

int CreateDirectory(const char *pathname)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return AMP_ERROR;
#endif

	return fileMakeDir(pathname);
}

char *TrimWhiteSpaces(char *str)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return NULL;
#endif

	char *end;

	// Trim leading space
	while(isspace(*str)) str++;

	if(*str == 0)  // All spaces?
	return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace(*end)) end--;

	// Write new null terminator
	*(end+1) = 0;

	return str;
}

/*
 * All leading spaces from a string is removed, string is a null terminated
 * string.
 */
void TrimLeadZeroes(char* pchString) 
{
    int inIndex;

    inIndex = 0;
    while (pchString[inIndex] == '0')
        inIndex++;
    if (inIndex != 0)
        strcpy(pchString, &(pchString[inIndex]));
}

void pad_string(char* str,int padlen,char padval,int padtype) {
    int padno;

    if ((padno = padlen - strlen(str)) > 0) {
        if (padtype == LEFT)
            memmove(str + padno, str, strlen(str) + 1);
        else
            str += strlen(str);
        memset(str, padval, padno);
        if (padtype == RIGHT)
            *(str + padno) = '\0';
    } else if (padno < 0) {
        // Truncate string if too long!!
        memmove(str, str + abs(padno), padlen + 1);
    }
}

void replace_char(char* str, char find, char replace)
{
    char *current_pos = strchr(str,find);

	while (current_pos)
	{
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
}

void GetPosTime(uint8_t *pszDate, uint8_t *pszTime)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return;
#endif

	char szDateTime[15] = { 0 };

	if(pszDate || pszTime)
		GetTerminalDateAndTime(szDateTime);

	if(pszDate)
		memcpy(pszDate, szDateTime, 8);

	if(pszTime)
		memcpy(pszTime, szDateTime+8, 6);
}

void GetTerminalDateAndTime(char buffer[15])
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return;
#endif

	time_t		t;
	struct tm	ltm;
	int			year, month, day, hour, minute, second, week;

	time(&t);
	localtime_r(&t, &ltm);
	year   = ltm.tm_year + 1900;
	month  = ltm.tm_mon + 1;
	day    = ltm.tm_mday;
	hour   = ltm.tm_hour;
	minute = ltm.tm_min;
	second = ltm.tm_sec;
	week   = ltm.tm_wday == 0 ? 7 : ltm.tm_wday;

	// YYYYMMDDhhmmss
	sprintf(buffer, "%04d%02d%02d%02d%02d%02d", year, month, day, hour, minute, second);
}

void AddDaysOnDate(char date[10], int days)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return;
#endif
	
	int daysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	time_t		t;
	struct tm	ltm;
	int			year, month, day;

	time(&t);
	localtime_r(&t, &ltm);
	year   = ltm.tm_year + 1900;
	month  = ltm.tm_mon + 1;
	day    = ltm.tm_mday;
	
	for (int i=0;i<days;i++)
	{
		day++;
		if (day > daysPerMonth[month-1] || ( month==2 && day==29 && !isLeapYear(year) ) )
		{
			day = 1;
			month++;
			if (month==13)
			{
				month = 1;
				year++;
			}
		}
	}
	
	sprintf(date, "%02d/%02d/%04d", month, day, year);

}

BOOL isLeapYear(int year)
{
    if (year%400==0) 
		return true;
	
    if (year%100==0) 
		return false;

	return (year%4==0);
}

void AddMinutesOnTime(char ExpDate[10], char ExpTime[6], int Minutes)
{
	time_t		t;
	struct tm	ltm;
	int			year, month, day, hour, minute, second;
	char CurrentDate[10+1] = {0};

	time(&t);
	localtime_r(&t, &ltm);
	year   = ltm.tm_year + 1900;
	month  = ltm.tm_mon + 1;
	day    = ltm.tm_mday;
	hour   = ltm.tm_hour;
	minute = ltm.tm_min;
	second = ltm.tm_sec;
	
	// Add minutes
	minute += Minutes;

	// Adjust hour if max
	if (minute >= 60)
	{
		hour++;
		minute = minute - 60;
	}

	// Adjust day if max
	if (hour >= 24)
	{
		hour = hour - 24;
		AddDaysOnDate(CurrentDate, 1);	// Format: MM/DD/YYYY
	}
	else
	{
		sprintf(CurrentDate, "%02d/%02d/%04d", month, day, year);
	}

	strcpy(ExpDate, CurrentDate);
	sprintf(ExpTime, "%02d%02d%02d", hour, minute, second);

}

int CompareDateToday(const char Date[10])
{
	time_t		t;
	struct tm	ltm;
	int			year_cur, month_cur, day_cur;	// current
	char		year[4+1]= {0}, month[2+1] = {0}, day[2+1] = {0};
	int			year_cmp, month_cmp, day_cmp;	// to compare

	// Get the current date
	time(&t);
	localtime_r(&t, &ltm);
	year_cur   = ltm.tm_year + 1900;
	month_cur  = ltm.tm_mon + 1;
	day_cur    = ltm.tm_mday;

	// Parse the date to compare
	strncpy(month, Date, 2);
	month_cmp = atoi(month);
	strncpy(day, &Date[3], 2);
	day_cmp = atoi(day);
	strncpy(year, &Date[6], 10);
	year_cmp = atoi(year);

	if (year_cmp > year_cur)
	{
		return AMP_SUCCESS;
	}
	else
	{
		if ((month_cmp > month_cur) && (year_cmp == year_cur))
		{
			return AMP_SUCCESS;
		}
		else
		{
			if ((day_cmp >= day_cur) && (month_cmp == month_cur) && (year_cmp == year_cur))
			{
				return AMP_SUCCESS;
			}
			else
			{
				return AMP_ERROR;
			}
		}
	}
}

const char* GetLibraryVersion(void)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return NULL;
#endif

	static char szLibVersion[MAX_STR_SZ*2] = { 0 };
	if(!szLibVersion[0])
	{
		sprintf(szLibVersion, "Version[%s] Build[%s %s]", AMPCMPNT_VER, __DATE__, __TIME__);
	}
	return szLibVersion;
}

int Open_File(const char* fname)
{	
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return AMP_ERROR;
#endif

	int fd;
	
	fd = fileOpen(fname, O_RDWR|O_CREAT);
	if( fd<0 )
	{
		return AMP_ERROR;
	}
	
	return fd;
}

int Seek_File(int fd)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return AMP_ERROR;
#endif

	UINT ret;
	ret = fileSeek(fd, 0, SEEK_END);
	if( ret<0 ) 
	{
		Close_File(fd);
		return AMP_ERROR;
	}
	
	return ret;
}

int WriteToFile(int fd, const void *buf, size_t size)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return AMP_ERROR;
#endif

	UINT ret;
	
	ret = fileWrite(fd, (uint8_t *)buf, size);
	Close_File(fd);
	if( ret != size) 
	{
		return AMP_ERROR;
	}
	
	return AMP_SUCCESS;
}

int ReadFromFile(int fd, const void *buf, size_t size)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return AMP_ERROR;
#endif

	UINT ret;

	ret = fileRead(fd, (uint8_t *)buf, size);
	if( ret != size ) 
	{
		return AMP_ERROR;
	}

	return AMP_SUCCESS;
}

void Close_File(int fd)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return;
#endif

	fileClose(fd);
}

void InitRandomNumberGenerator(void)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return;
#endif

	unsigned int seed;
	FILE *urandom = fopen("/dev/urandom", "r");
	fread(&seed, sizeof(int), 1, urandom);
	fclose(urandom);
	srand(seed);
}

UINT GenerateRandomNumber(UINT Min, UINT Max)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return 0;
#endif

	int iRandom = 0, LowNum = 0, HiNum = 0;

	if(Min < Max)
	{
		LowNum = Min;
		HiNum  = Max + 1;
	}
	else
	{
		LowNum = Max;
		HiNum  = Min + 1;
	}

	iRandom = (rand() % (HiNum - LowNum)) + LowNum;

	return (UINT)(iRandom);
}
#if 0
void SystemReboot(void)
{
#ifdef PLATFORM_AMPPOS_ONLY
	if(!IsAMPPosTerminal()) return;
#endif

	sysReset();
}
#endif
#if 0
bool IsAMPPosTerminal(void)
{
	return true;
#if 0
	static int iRetVal = -1;

	if(iRetVal < 0)
	{
		int nr;
		char machine[128] = { 0 };

		//2 Terminal Model
		memset(machine, 0, sizeof(machine)); nr = 0;
		sys_get_hardware_config(HARDWARE_MACHINE, machine, NULL);

		if(memcmp(machine, "AMP", 3) == 0)
			iRetVal = 1;
		else
			iRetVal = 0;

	#ifdef DEBUG_KEYS
		_LogHEXBuffer((unsigned char*)machine, 64, "[HARDWARE_MACHINE]");
		DEBUG_INFO("IsAMPPosTerminal (%d)", iRetVal);
	#endif

		fprintf(stdout,"\n*******************************************\n");
		fprintf(stdout,"IsAMPPosTerminal (%d)\n", iRetVal);
		fprintf(stdout,"IsAMPPosTerminal (%s)\n", machine);
		fprintf(stdout,"*******************************************\n");
	}

	return iRetVal;
#endif
}
#endif
#if 0
int SetTerminalDateTime(const char szDateTime[14+1])
{
	struct tm DateTime;
	char szYear[4+1], szMonth[2+1], szDay[2+1], szHour[2+1], szMinute[2+1], szSecond[2+1];

	if(strlen(szDateTime) < 14)
			return AMP_ERROR;
		
	strncpy(szYear, szDateTime, 4);
	strncpy(szMonth, szDateTime+4, 2);
	strncpy(szDay, szDateTime+6, 2);
	strncpy(szHour, szDateTime+8, 2);
	strncpy(szMinute, szDateTime+10, 2);
	strncpy(szSecond, szDateTime+12, 2);


	DateTime.tm_year = atoi(szYear) - 1900;
	DateTime.tm_mon = atoi(szMonth) - 1;
	DateTime.tm_mday = atoi(szDay);
	DateTime.tm_hour = atoi(szHour);
	DateTime.tm_min = atoi(szMinute);
	DateTime.tm_sec = atoi(szSecond);

	sys_set_time(&DateTime);

	return AMP_SUCCESS;
}


int AdjustDateTimeByMinutes(const char szOrigDateTime[14+1], long lMinutes, char szNewDateTime[14+1])
{
	char szYear[4+1], szMonth[2+1], szDay[2+1], szHour[2+1], szMinute[2+1], szSecond[2+1];
	int year, month, day, hour, minute, second;
	int addHour = 0, addMinute = 0, addDay=0, addMonth=0, addYear=0;
	int daysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if(strlen(szOrigDateTime) < 14)
		return AMP_ERROR;
	
	strncpy(szYear, szOrigDateTime, 4);
	strncpy(szMonth, szOrigDateTime+4, 2);
	strncpy(szDay, szOrigDateTime+6, 2);
	strncpy(szHour, szOrigDateTime+8, 2);
	strncpy(szMinute, szOrigDateTime+10, 2);
	strncpy(szSecond, szOrigDateTime+12, 2);

	year = atoi(szYear);
	if (isLeapYear(year))
	{
		daysPerMonth[1] = 29;
	}

	month = atoi(szMonth);
	if( month > 12)
		return AMP_ERROR;

	day = atoi(szDay);
	if(day > daysPerMonth[month-1])
		return AMP_ERROR;

	hour = atoi(szHour);
	if( hour >= 24)
		return AMP_ERROR;
		
	minute = atoi(szMinute);
	if( minute >= 60)
		return AMP_ERROR;
		
	second = atoi(szSecond);
	if( second >= 60)
		return AMP_ERROR;

	addMinute = lMinutes % 60;
	addHour = (lMinutes - addMinute)/60;
	
	//add minute
	minute += addMinute;
	if(minute >= 60)
	{
		minute -= 60;
		addHour++;
	}
	else if(minute < 0)
	{
		minute += 60;
		addHour--;
	}

	//add hour
	hour += addHour;
	if(hour >= 24)
	{
		hour -= 24;
		addDay++;
	}
	else if( hour < 0)
	{
		hour += 24;
		addDay--;
	}
	
	//add day
	day += addDay;
	if (day > daysPerMonth[month - 1])
	{
		
		day -= daysPerMonth[month - 1];
		addMonth++;
	}
	else if (day <= 0)
	{
		month--;
		if( month == 0)
		{
			month = 12;
			addYear--;
		}
		day = daysPerMonth[month - 1]- day;
	}

	//add month
	month += addMonth;
	if (month > 12)
	{
		month -= 12;
		addYear++;
	}

	//add year
	year += addYear;

	sprintf(szNewDateTime, "%04d%02d%02d%02d%02d%02d", year, month, day, hour, minute, second);
	
	return AMP_SUCCESS;

}
#endif