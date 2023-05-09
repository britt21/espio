/******************************************************************************
 * seos.h
 * 
 * Copyright (c) 2011 by Li.Hua <lihua_338@163.com>.
 * 
 * DESCRIPTION: - 
 * 
 * Modification history
 * ----------------------------------------------------------------------------
 * Date         Version  Author       History
 * ----------------------------------------------------------------------------
 * 2011-01-19   1.0.0    Li.Hua       written
 ******************************************************************************/
#if defined(ANDROID)
 
#ifndef __SEOS_H__
#define __SEOS_H__

#include <stdint.h>
#include <assert.h>

#if defined(N58)

#else
#include <netinet/in.h>
#endif




#if defined(NEW8110) || defined(NEW2110) || defined(N58)
#else
#include "led.h"

#include "posapi.h"

#ifdef __cplusplus
	extern "C" {
#endif /* __cplusplus */


int application_init(int *argc, char **argv[], int LedWidth);
int application_exit(void);



/* System API */
void sysReadSN(void *SerialNo);
int sysReadConfig(uint8_t *ConfigInfo);
void sysGetLastError(int *ModInfo, int *ErrorNum);
void sysBeef(uint32_t Freq, uint32_t BeepTime);
void sysBeep(void);
int sysSetTime(const void *TimeStr);
void sysGetTime(void *TimeStr);
uint32_t sysGetTimerCount(void);
void sysTimerSet(uint32_t TimerNo, uint32_t CountMs);
uint32_t sysTimerCheck(uint32_t TimerNo);
void sysDelayMs(uint32_t CountMs);
void sysPowerOff(void);
void sysReset(void);
int sysGetPowerStatus(void);
int sysGetVolt(void);
void sysAutoPowerSave(int mode);
uint32_t sysPowerSave(uint32_t Event, uint32_t TimeOutMs);
int sysEncode2bmp(const void *image, uint32_t width, uint32_t height, void *bmpfilebuffer);
int accGetMotion(int *Xaxis, int *Yaxis, int *Zaxis);
int sysSetPowerKey(int32_t DelayMs);
int sysGetPowerKeyStatus(void);


#undef	KEY0
#define	KEY0                    0	//  

#undef	KEY1
#define	KEY1                    1  //  

#undef	KEY2
#define	KEY2                    2  //  

#undef	KEY3
#define	KEY3                    3	//  

#undef	KEY4
#define	KEY4                    4	//  

#undef	KEY5
#define	KEY5                    5	//  

#undef	KEY6
#define	KEY6                    6	//  

#undef	KEY7
#define	KEY7                    7	//  

#undef	KEY8
#define	KEY8                    8	//  

#undef	KEY9
#define	KEY9                    9	//  

#undef	KEY_BACKSPACE
#define	KEY_BACKSPACE           10	//  

#undef	KEY_CLEAR
#define	KEY_CLEAR               11		//  

#undef	KEY_ALPHA
#define	KEY_ALPHA               12		//  

#undef	KEY_UP
#define	KEY_UP                  13	//  

#undef	KEY_DOWN
#define	KEY_DOWN                14	//  

#undef	KEY_FN
#define	KEY_FN                  15	//  

#undef	KEY_MENU
#define	KEY_MENU                16        //  

#undef	KEY_ENTER
#define	KEY_ENTER               17		//  

#undef	KEY_CANCEL
#define	KEY_CANCEL              18		//  

#undef	KEY_PRNUP
#define	KEY_PRNUP               19		//  

#undef	KEY_INVALID
#define	KEY_INVALID             20		//  

#undef	KEY_TIMEOUT
#define	KEY_TIMEOUT             -1				//  

#define KB_MAXLEN               256         
#define KB_EN_REVDISP           0x01        
#define KB_EN_FLOAT             0x02        
#define KB_EN_SHIFTLEFT         0x04       
#define KB_EN_CRYPTDISP         0x08        
#define KB_EN_CHAR              0x10      
#define KB_EN_NUM               0x20        
#define KB_EN_BIGFONT           0x40        
#define KB_EN_PRESETSTR         0x80        
#define KB_EN_NEWLINE           0x100       

// 预设几组常用的输入控制模式
#define KB_BIG_ALPHA            0x1F5       //  大字体字符串输入
#define KB_BIG_NUM              0x1E5       //  大字体数字串输入
#define KB_BIG_PWD              0x6D        //  大字体密码输入
#define KB_SMALL_ALPHA          0x1B5       //  小字体字符串输入
#define KB_SMALL_NUM            0x1A5       //  小字体数字串输入
#define KB_SMALL_PWD            0x2D        //  小字体密码输入

#define KB_CANCEL               -1          //  串输入被用户按取消键退出
#define KB_TIMEOUT              -2          //  串输入超时退出
#define KB_ERROR                -3          //  串输入参数非法



int kbCheckKey(void);
int kbWaitKey(int status);

int kbhit(void);
int kbGetKey(void);
int kbGetKeyMs(int TimeOutMs);
void kbFlush(void);
void kbSound(int Mode, int DelayTimeMs);
int kbGetString(uint32_t mode, int minlen, int maxlen, uint32_t timeoutms, char *info);
int kbGetHZ(int MinLen, int MaxLen, int TimeOutMs, char *StrBuf);



// 背光模式
#define LIGHT_ON_TEMP           0           //  背光临时开启(对于定时模式用)
#define LIGHT_TIMER_MODE        1           //  背光定时模式
#define LIGHT_ON_MODE           2           //  背光常开模式
#define LIGHT_OFF_MODE          3           //  背光常关模式

void lcdLight(int Mode);


/* LCD */
#define DISP_ASCII          0x00    //  display small font(6*8)
#define DISP_CFONT          0x01    //  display the pointed font (default 8*16)
#define DISP_CLRLINE        0x20    //  clear the line before display
#define DISP_MEDIACY        0x40    //  display in the middle of line
#define DISP_REVERSE        0x80    //  display inverse character
#define DISP_INVLINE		0x10	//  display inverse whole line
#define DISP_LEFT                               0x100   //  display in the LEFT of line
#define DISP_RIGHT                              0x200   //  display in the RIGHT of line

void lcdGetSize(int *width, int *height);
void lcdCls(void);
void lcdClrLine(int BeginLine, int EndLine);
void lcdGoto(int Col, int Line);
void lcdSetInverse(int Mode);
void lcdPrintf(const char *format, ...);
void lcdFlip(void);
void lcdDisplay(int Col, int Line, uint32_t Mode, const char *format);
void lcdStipple(int X, int Y, int Color);
void lcdDrawPicture(int x, int y, int w, int h, const char *filename);
int lcdSetFont(const char *pFontName, const char *pFontCharacter, 
			   int Style, int Size, int FontPriority);
void lcdGetCurFont(char *pFontName, char *pFontCharacter, 
				   int *pStyle, int *pSize, int FontPriority);
void lcdDrawFrame(int StartX, int StartY, int EndX, int EndY, int Mode);

#define lcdStore(pCol, pLine, pucBitMapBuf) \
	do { \
		lcdGoto(0, 0); \
		lcdSetInverse(0); \
		lcdPrintf("Notice: the function lcdStore() has not implemented."); \
		while (1) usleep(10*1000); \
	} while (0);

#define lcdRestore(Col, Line, pucBitMapBuf) \
	do { \
		lcdGoto(0, 0); \
		lcdSetInverse(0); \
		lcdPrintf("Notice: the function lcdRestore() has not implemented."); \
		while (1) usleep(10*1000); \
	} while (0);
	
void lcd_store();
void lcd_restore();

//  返回值
#define     PRN_OK              0x00
#define     PRN_BUSY            0x01
#define     PRN_PAPEROUT        0x02
#define     PRN_WRONG_PACKAGE   0x03
#define     PRN_FAULT           0x04
#define     PRN_TOOHEAT         0x08
#define     PRN_UNFINISHED      0xF0
#define     PRN_NOFONTLIB       0xFC
#define     PRN_OUTOFMEMORY     0xFE

int prnInit(void);
int prnPrintf(const char *format, ...);
int prnStart(void);


#ifdef __cplusplus
	}
#endif /* __cplusplus */

#endif /* __SEOS_H__ */
#endif

#endif
