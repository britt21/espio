#ifndef POS_INTERFACE_H
#define POS_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
//#include <unistd.h>
#include <string.h>
#if defined(ANDROID)
#include "android/android_adapter.h"
#include "posapi.h"
#include "android/seos.h"
#elif defined(LINUX)
#include "linux/seos.h"
#include "posapi.h"
#elif defined(N58)
#define __VERIFY_H__
#define __PED_USER_API_H__
#define _NETDB_H_
#include "key.h"
#include "posapi.h"
#include "n58/n58.h"
#elif defined(N28)
#include "N28/n28.h" 
#else
#endif


#define CONTACTLESS_OK          0
#define CONTACTLESS_NO_CARD 	1
#define CONTACTLESS_MULTI_CARD  2

#ifndef EMV_CL_APDU_STATUS_DEF
#define EMV_CL_APDU_STATUS_DEF
typedef enum{
	EMV_CL_APDU_PROCESSING,
		EMV_CL_APDU_ABORTED,
		EMV_CL_APDU_DONE
}EMV_CL_APDU_STATUS;
#endif


#if !defined(ON) 
#define ON  1
#endif

#if !defined(OFF)
#define OFF 0
#endif

typedef enum {
	LAN_CHINESE,
		LAN_ENGLISH
}POS_LANGUAGE;

int  pos_init(int argc, char * argv[]);
void pos_uninit(void);

void * pos_os_library_load(const char * dll_file);
void   pos_os_library_close(void * inst);
void*  pos_os_library_function_get(void* library, const char * func_name);



POS_LANGUAGE pos_language_get(void);
void         pos_language_set(POS_LANGUAGE lang);

unsigned int pos_get_tick_count(void);
void * pos_malloc(unsigned int uiSize);
void * pos_realloc(void * p, unsigned int uiSize);
void   pos_free(void * p);
void pos_get_time(unsigned char * pTimeYYMMDDHHMMSS);
int pos_set_time(const unsigned char * pTimeYYMMDDHHMMSS);
void pos_random_read(void * pvbuf, int size);



int  pos_kb_hit(void);
int  pos_kb_get_key(void);
int  pos_kb_get_keyMs(int msec);
void pos_kb_flush(void);

void pos_kb_SetCancelKey(void);

void pos_beep(int frequency, int durationMs);
void pos_beep_ok(void);
void pos_beep_error(void);

typedef struct{
	unsigned int Freq;
	unsigned int Duration;
	unsigned int WaitMSeconds;
}beep_param;
void pos_beep_ex(const beep_param * param, int count);
void pos_beep_start(void);
void pos_beep_stop(void);


void pos_msleep(int mseconds);

typedef enum{
	POS_LED_BLUE,
	POS_LED_YELLOW,
	POS_LED_GREEN,
	POS_LED_RED,
	POS_LED_ALL
}POS_LED_IDENTIFY;

typedef enum{
	POS_LED_OFF,
	POS_LED_ON,
	POS_LED_FLASH
}POS_LED_STATUS;
void pos_led_init(void);
void pos_led_uninit(void);
void pos_led_set(POS_LED_IDENTIFY id, POS_LED_STATUS status);



void pos_lcd_save(void);
void pos_lcd_restore(void);

int  pos_lcd_get_text_lines(unsigned int Mode, const char * pszMsg);
int  pos_lcd_max_lines_get(void);

#define LCD_BACK_LIGHT_ON_ALWAYS   -1
#define LCD_BACK_LIBHT_OFF         0
void pos_lcd_auto_update(int Enable);
void pos_lcd_update(void);

void pos_lcd_get_size(int * width, int * height);
void pos_lcd_keep_dealy(unsigned int delayms);
void pos_lcd_clear(void);
int  pos_lcd_display(int Col, int Line, unsigned int Mode, const char *format, ...);
void pos_lcd_clear_line(int BeginLine, int EndLine);
void pos_lcd_disp_picture(int Col, int line, int width, int height, const char * file_name);


int  pos_lcd_get_time(void);
void pos_lcd_set_time(int TimVal);

/*
int  pos_get_enter_amount(const char * pszTitle, uint32_t * puiAmount);
int  pos_get_enter_number(const char * pszTitle, uint32_t * puiNumber);
int  pos_get_enter_number_string(const char * pszTitle, char * pszBuff, int min, int max);
int  pos_get_enter_hex_string(const char * pszTitle, char * pszBuff, int min,int max);
*/



void pos_contactless_display_logo(void);
int  pos_contactless_open(void);
void pos_contactless_close(int ifd);
int  pos_contactless_active(int ifd);
int  pos_contactless_status_get(int ifd);
int  pos_contactless_exchange_apdu(int ifd, 
                                  unsigned int ApduLen,const void * pApdu,
                                  unsigned int * pApduRespLen, void * pApduResp);

int  pos_contactless_apdu_send(int fd, unsigned int sendlen, const void * senddata);
int  pos_contactless_apdu_resp_get(int fd, int allowStop, unsigned int *recvlen, void *recvdata, EMV_CL_APDU_STATUS * status);
int  pos_contactless_exchange_apdu_ex(int fd, unsigned int sendlen, const void *senddata, unsigned int *recvlen, void *recvdata, int * aborted);
void pos_contactless_remove_card(int fd);
int  pos_iccard_open(void);
void pos_iccard_close(int ifd);
int  pos_iccard_check_present(int ifd);
int  pos_iccard_power_on(int ifd);
void pos_iccard_power_off(int ifd);
int  pos_iccard_exchange_apdu(int ifd, 
											  unsigned int ApduLen,const void * pApdu, 
											  unsigned int * pApduRespLen, void * pApduResp);


int pos_magstripe_open(void);
void pos_magstripe_close(int ifd);
void pos_magstripe_reset(int ifd);
int  pos_magstripe_check_swiped(int ifd);
int  pos_magstripe_read(int ifd,
					    char * pszTrack1,
					    char * pszTrack2,
					    char * pszTrack3);

#if defined(NEW2110)|| defined(N58)
#define pos_printer_init()
#define pos_printer_printf(fmt,...)
#define pos_printer_start()
#elif defined(N58)
void pos_printer_init();
void pos_printer_printf(const char * fmt,...);
void pos_printer_start();
#else
#define pos_printer_init     prnInit
#define pos_printer_printf   prnPrintf
#define pos_printer_start    prnStart
#endif




void pos_file_get_full_file_name(const char * file_name, char * full_file_name, int size);
int  pos_file_size_get(const char * pszFileName, unsigned int * size);
int  pos_file_exists(const char * pszFileName);
int  pos_file_remove(const char * pszFileName);
int  pos_file_open(const char * pszFileName, int CreateIfNotExit);
void pos_file_close(int ifd);
void pos_file_flush(int ifd);
off_t pos_file_seek(int ifd, off_t move, int whence);
int pos_file_read(int ifd, void * pvBuff, int size);
int pos_file_write(int ifd, const void * pvData, int size);
int pos_file_delete_block(int ifd, unsigned int length);
int pos_file_insert_block(int ifd, unsigned int length);
int pos_file_truncate(int ifd, unsigned int size);

#if defined(NEW8110) || defined(NEW2110)
int pos_commu_open(int SerialPort);

#else
int pos_commu_open(const char * pszPort);
#endif

void pos_commu_close(void);
int pos_commu_has_data(int timeout_msec);
int pos_commu_read(void * pvBuff, int size, int TimeOutMs);
int pos_commu_write(const void * pvData, int size);


int pos_timer_create(unsigned int uiTimeOutSec);
unsigned int pos_timer_check(int timer_handle); 


#if defined(_DEBUG)
void pos_dbg_cach_enable(void);
void pos_dbg_cach_disable(void);
void pos_dbg_cach_print(void);

void pos_debug_printf(const char * pszFmt,...);
void pos_debug_memory_dump(const char * pszTitle, const void * pvData, unsigned int uiSize);
#define pos_debug_enter(fmt, arg...) {pos_debug_printf("%s(" fmt ")>>", __FUNCTION__, ##arg);}
#define pos_debug_leave(fmt, arg...) {pos_debug_printf("%s()<< " fmt , __FUNCTION__, ##arg);}
#define pos_debug_trace(fmt, arg...) pos_debug_printf("FILE:%s LINE:%d %s " fmt, __FILE__, __LINE__, __FUNCTION__, ##arg)
#else

#define pos_dbg_cach_enable()
#define pos_dbg_cach_disable()
#define pos_dbg_cach_print()

#define pos_debug_printf(fmt,...)
#define pos_debug_memory_dump(title, pvdata, uisize)
#define pos_debug_enter(fmt, arg...)
#define pos_debug_leave(fmt, arg...)
#define pos_debug_trace(fmt, arg...)

#endif


void pos_debug_step(const char * pszMsg,...);




typedef enum{
	AMP3000_POS,
	AMP5000_POS,
	AMP7000_POS,
	AMP9000_POS,
	AMP8000_POS,
	AMP8200_POS,
	AMP6700_POS,
	AMP6500_POS,
	
	NEW8110_POS,
	NEW8210_POS,
	NEW7210_POS,
	
	NEW6210_POS,
	NEW9210_POS,
	NEW9220_POS,
	NEW5210_POS,
	NEW5310_POS,
	
	
	N28_POS,
	UNKNOW_POS,
}POS_TYPE;

POS_TYPE pos_type_get(void);
const char * pos_sn_get(void);
const char * pos_type_name_get(void);
const char * pos_type_os_version_get(void);
const char * pos_firmware_version_get(void);
const char * pos_contactless_level1_info_get(void);

int pos_get_trycount(void);

void pos_reset_trycount(void);

void pos_add_trycount(void);


#ifdef __cplusplus
}
#endif

#endif
