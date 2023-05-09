#ifndef  MAGSTRIPEAPI_H
#define  MAGSTRIPEAPI_H
#ifdef __cplusplus
extern "C" {
#endif
typedef struct MAGSTRIPE_S * MAGSTRIPE;

typedef enum{
	MAGSTRIPE_OK,
	MAGSTRIPE_FAILED,
	MAGSTRIPE_NO_SWIPED,
	MAGSTRIPE_CALL_FAILED,
	MAGSTRIPE_NOT_OPEN,
	MAGSTRIPE_BUSY,	
}MAGSTRIPE_ERROR;

typedef enum{
	MAGSTRIPE_DECODE_OK = 0,
	MAGSTRIPE_DECODE_EER_RAW = 1,
	MAGSTRIPE_DECODE_EER_LRC = 2,
	MAGSTRIPE_DECODE_EER_ODD = 4,	
}MAG_TRACK_STATUS;

typedef enum{
	MAGSTRIPE_SWIPED,
	MAGSTRIPE_MEMORY_NO_ENOUGH
}MAGSTRIPE_STATUS;

MAGSTRIPE magcard_initialize(const char * dev_name_suffix);
void magcard_free(MAGSTRIPE magstripe);
void magcard_stop(MAGSTRIPE magstripe);
MAGSTRIPE_ERROR magcard_setkey(MAGSTRIPE magstripe);
//MAGSTRIPE_ERROR magcard_start(MAGSTRIPE magstripe,const sp<IMagstripeListener>& listener);	
MAGSTRIPE_ERROR magcard_start_ex(MAGSTRIPE magstripe);	
MAGSTRIPE_STATUS magcard_get_status();	
void get_track(MAG_TRACK_STATUS * status1, unsigned char* track1,MAG_TRACK_STATUS * status2, unsigned char * track2,MAG_TRACK_STATUS * status3,unsigned char * track3);
#ifdef __cplusplus
}
#endif
#endif