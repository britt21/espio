#ifndef  ICCARDAPI_H
#define  ICCARDAPI_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
        ICCARD_OK               = 0,
        ICCARD_FAILED 			= -1,
        ICCARD_NOT_OPEN 		= -2,
        ICCARD_CALL_FAILED 		= -3,
        ICCARD_MEMORY_NO_ENOUGH = -4,
        ICCARD_OPEN_FAILED	 	= -5,
        ICCARD_NOT_NFC 			= -6,
        ICCARD_NOT_CONTACT 		= -7,
        ICCARD_IN_PROCESSING 	= -8,
        ICCARD_NO_CARD 			= -9,
        ICCARD_BUSY 			= -10,
        ICCARD_NFC_ACTIVE_FAILED= -11,
} ICCARD_ERROR;

typedef enum {
        ICCARD_INSERTED,
        ICCARD_WRONG
} ICCARD_STATUS;
    typedef enum {
        NFC_ERROR,
        NFC_CARD_PRESENT,
        NFC_NO_CARD,
        NFC_COLLISION,
    } NFC_STATUS; 

typedef enum {
        ICCARD_EMV_MODE     = 0,
        ICCARD_ISO_MODE     = 1,
        ICCARD_ISO_19200    = 2,
        ICCARD_ISO_38400    = 3
} ICCARD_MODE;

typedef enum {
        ICCARD_CVCC_1_8_VOLT = 1,
        ICCARD_CVCC_3_VOLT   = 2,
        ICCARD_CVCC_5_VOLT   = 3
} ICCARD_VOLT;
typedef struct ICCARD_S * ICCARD;

ICCARD iccard_initialize(const char * dev_name_suffix);
void   iccard_free(ICCARD iccard);
void   iccard_stop(ICCARD iccard);

ICCARD_ERROR emv_iccard_exchange_apdu(ICCARD iccard,
                        				unsigned int apdu_len,
                        				const unsigned char * apdu,
                        			    unsigned int *apdu_resp_len,
                        			    unsigned char  * apdu_resp);
ICCARD_ERROR iccard_card_start_ex(ICCARD iccard);
ICCARD_STATUS iccard_card_present(ICCARD iccard);
NFC_STATUS   Iccard_nfc_status_get(ICCARD iccard);
void Iccard_nfc_setNFC(ICCARD iccard);
ICCARD_ERROR iccard_card_power_on(ICCARD_VOLT volt, ICCARD_MODE mode,ICCARD iccard, unsigned int * atr_len, unsigned char * atr);
ICCARD_ERROR iccard_card_power_off(ICCARD iccard);

ICCARD_ERROR iccard_nfc_start_ex(ICCARD iccard);
ICCARD_ERROR iccard_nfc_remove_card(ICCARD iccard);
ICCARD_ERROR iccard_nfc_apdu_send(ICCARD iccard,unsigned int apdu_len,
						  				const unsigned char* apdu);
ICCARD_ERROR iccard_nfc_resp_get(ICCARD iccard, unsigned int *apdu_resp_len,
						  			  unsigned char  * apdu_resp);
ICCARD_ERROR iccard_nfc_abort(ICCARD iccard);

ICCARD_ERROR iccard_nfc_active(ICCARD iccard);

ICCARD_ERROR iccard_nfc_close(ICCARD iccard);


#ifdef __cplusplus
}
#endif
#endif