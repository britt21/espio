/**
 * @file    ped.h
 *          
 * @author  Li.Hua <lihua_338@163.com>.
 *          
 * @date    2016-02-29
 *          
 * @brief   PED API for A-SMART platform
 *          
 * @note    
 *          
 * Modification history
 * ----------------------------------------------------------------------------
 * Date         Version  Author       History
 * ----------------------------------------------------------------------------
 *
 */

#ifndef __PED_H__
#define __PED_H__

#include <stdint.h>
#include <ped_common.h>
#include "buildconfig.h"

#ifdef __cplusplus 
extern "C" { 
#endif 

/*
 * OTP
 */
typedef enum {
    CPUID          = 0x00, /* 0 : CPUID */
    FORMAT_FLAG,           /* 1 : PED format flag */
    FID_FLAG,              /* 2 : firmware id flag */
    OTP_MAX,                 /* END */
} OtpSys_t;


/* 
 * PED 状态定义: 锁定，正常，过期
 */
enum {
	PED_STATUS_LOCK			= 0,
	PED_STATUS_NORMAL,
	PED_STATUS_EXPIRED,
};


#if 0
typedef struct {   // 公钥结构
    uint32_t bits;                   /* length in bits of modulus */
    uint8_t  exponent[4];            /* public exponent */
    uint8_t  modulus[512];           /* modulus */
} __attribute__((packed)) R_RSA_PUBLIC_KEY;

typedef struct {  // 私钥结构
    uint32_t bits;                   /* length in bits of modulus */
    uint8_t  modulus[512];           /* modulus */
    uint8_t  publicExponent[4];      /* public exponent */
    uint8_t  exponent[512];          /* private exponent */
    uint8_t  prime[2][256];          /* prime factors */
    uint8_t  primeExponent[2][256];  /* exponents for CRT */
    uint8_t  coefficient[256];       /* CRT coefficient */
} __attribute__((packed)) R_RSA_PRIVATE_KEY;
#else
typedef struct {   // 公钥结构
    uint32_t bits;                   /* length in bits of modulus */
    uint8_t  exponent[4];            /* public exponent */
    uint8_t  modulus[256];           /* modulus */
} __attribute__((packed)) R_RSA_PUBLIC_KEY;

typedef struct {  // 私钥结构
    uint32_t bits;                   /* length in bits of modulus */
    uint8_t  modulus[256];           /* modulus */
    uint8_t  publicExponent[4];      /* public exponent */
    uint8_t  exponent[256];          /* private exponent */
    uint8_t  prime[2][128];          /* prime factors */
    uint8_t  primeExponent[2][128];  /* exponents for CRT */
    uint8_t  coefficient[128];       /* CRT coefficient */
} __attribute__((packed)) R_RSA_PRIVATE_KEY;

#endif
#define TYPE_PIN_INTERVAL       0x01    // PIN Input interval
#define TYPE_UPDATE_INTERVAL	0x02	// Firmware update interval
#define TYPE_ACCOUNT_INTERVAL   0x03    // Account data encrypt interval

/* 
 * 加解密算法定义，用0~7位表示
 */
#define TDEA_DECRYPT            0x00000000	// TDES解密
#define TDEA_ENCRYPT            0x00000001	// TDES加密
#define TDEA_NONE               0x00000002	// 不做加解密操作(给ped的api使用)
#define SM4_DECRYPT				0x00000010	// SM4解密
#define SM4_ENCRYPT				0x00000011	// SM4加密
#define SM4_NONE				0x00000012	// 不做加解密操作(给ped的api使用)
#define AES_DECRYPT             0x00000020  // AES解密
#define AES_ENCRYPT             0x00000021  // AES加密
#define AES_NONE                0x00000022  // 不做加解密操作(给ped的api使用)

/* 
 * 加解密模式定义，用8~15位表示
 */
#define TDEA_MODE_ECB			0x00000000	// TDEA MODE ECB
#define TDEA_MODE_CBC			0x00000100	// TDEA MODE CBC
#define TDEA_MODE_CFB			0x00000200	// TDEA MODE CFB
#define TDEA_MODE_OFB			0x00000300	// TDEA MODE OFB
#define SM4_MODE_ECB			0x00001000	// SM4 MODE ECB
#define SM4_MODE_CBC			0x00001100	// SM4 MODE CBC
#define SM4_MODE_CFB			0x00001200	// SM4 MODE CFB
#define SM4_MODE_OFB			0x00001300	// SM4 MODE OFB
#define AES_MODE_ECB            0x00002000  // AES MODE ECB
#define AES_MODE_CBC            0x00002100  // AES MODE CBC
#define AES_MODE_CFB            0x00002200  // AES MODE CFB
#define AES_MODE_OFB            0x00002300  // AES MODE OFB

/*
 * 校验算法，用24~31位表示
 */
#define KEY_VERIFY_NONE			0x00000000	// 无
#define KEY_VERIFY_KVC			0x01000000	// KVC use DES
#define KEY_VERIFY_CMAC			0x02000000	// CMAC
#define KEY_VERIFY_SM4_KVC		0x11000000	// KVC use SM4
#define KEY_VERIFY_MASK			0xff000000	// 掩码

/*
 * PIN BLOCK 算法定义
 */
#define PIN_BLOCK_FORMAT_0      0x00    //  PIN BLOCK FORMAT 0
#define PIN_BLOCK_FORMAT_1      0x01    //  PIN BLOCK FORMAT 1
#define PIN_BLOCK_FORMAT_2      0x02    //  PIN BLOCK FORMAT 2
#define PIN_BLOCK_FORMAT_3      0x03    //  PIN BLOCK FORMAT 3
#define PIN_BLOCK_FORMAT_4      0x04    //  PIN BLOCK FORMAT 4
#define PIN_BLOCK_FORMAT_EPS    0x0A    //  PIN BLOCK FORMAT EPS

/*
 * MAC BLOCK 算法定义
 */
#define MAC_MODE_1              0x00    //  MAC method 1, TDES-TDES...TDES
#define MAC_MODE_2              0x01    //  MAC method 2, XOR...XOR...TDES
#define MAC_MODE_EMV            0x02    //  MAC for EMV EMV, DES-DES...TDES
#define MAC_MODE_CUP            0x03    //  MAC for CUP, XOR-XOR...TDES(left)-XOR-TDES...
#define MAC_MODE_DUKPT          0x04    //  MAC for DUKPT,Expand, XOR-XOR...TDES(left)-XOR-TDES...
#define MAC_MODE_CUP_8          0x05    //  MAC for CUP, XOR-XOR...TDES(left)-XOR-TDES...
#define MAC_MODE_1_8            0x06    //  MAC for CUP, TDES-TDES...TDES


/*
 * DES密钥类型
 */
#define KEY_TYPE_DES_MASTK      0x82    // MASTER KEY
#define KEY_TYPE_DES_PINK       0x83    // PIN KEY of SM4
#define KEY_TYPE_DES_MACK       0x84    // MAC KEY of SM4
#define KEY_TYPE_DES_FIXPINK    0x85    // Fixed PIN KEY
#define KEY_TYPE_DES_FIXMACK    0x86    // Fixed MAC KEY
#define KEY_TYPE_DES_EAK        0x8A    // Account Data KEY
#define KEY_TYPE_DES_FIXEAK     0x8B    // Fixed Account Data KEY
#define KEY_TYPE_DES_TMSK       0x8C    // TMS KEY

/*
 * SM4密钥类型
 */
#define KEY_TYPE_SM4_MASTK      0x92    // MASTER KEY
#define KEY_TYPE_SM4_PINK       0x93    // PIN KEY of SM4
#define KEY_TYPE_SM4_MACK       0x94    // MAC KEY of SM4
#define KEY_TYPE_SM4_FIXPINK    0x95    // Fixed PIN KEY
#define KEY_TYPE_SM4_FIXMACK    0x96    // Fixed MAC KEY
#define KEY_TYPE_SM4_EAK        0x9A    // Account Data KEY
#define KEY_TYPE_SM4_FIXEAK     0x9B    // Fixed Account Data KEY
#define KEY_TYPE_SM4_TMSK       0x9C    // TMS KEY

/*
 * AES密钥类型
 */
#define KEY_TYPE_AES_MASTK      0xA2    // MASTER KEY
#define KEY_TYPE_AES_PINK       0xA3    // PIN KEY of SM4
#define KEY_TYPE_AES_MACK       0xA4    // MAC KEY of SM4
#define KEY_TYPE_AES_FIXPINK    0xA5    // Fixed PIN KEY
#define KEY_TYPE_AES_FIXMACK    0xA6    // Fixed MAC KEY
#define KEY_TYPE_AES_EAK        0xAA    // Account Data KEY
#define KEY_TYPE_AES_FIXEAK     0xAB    // Fixed Account Data KEY
#define KEY_TYPE_AES_TMSK       0xAC    // TMS KEY

#define KEY_TYPE_EXPIRED_KEY    0xFE    // The expired key
#define KEY_TYPE_INVALID        0xFF    // Invalid key


/*
 * 返回值定义
 */
#define PED_RET_OK              0x00	//  PED OK
#define PED_RET_BASE_NO			2000
#define PED_RET_LOCKED          (PED_RET_BASE_NO +  1)	//  PED Locked
#define PED_RET_ERROR           (PED_RET_BASE_NO +  2)	//  The others error
#define PED_RET_COMMERR         (PED_RET_BASE_NO +  3)	//  Communicate with PED failed
#define PED_RET_NEEDAUTH        (PED_RET_BASE_NO +  4)	//  Need auth before use sensitive service or expired
#define PED_RET_AUTHERR         (PED_RET_BASE_NO +  5)	//  PED auth failed
#define PED_RET_WEAK_KEY		(PED_RET_BASE_NO +  6)	//  weak length key
#define PED_RET_COLLISION_KEY	(PED_RET_BASE_NO +  7)	//  collision key
#define PED_RET_KEYINDEXERR     (PED_RET_BASE_NO +  8)	//  The index of key incorrect
#define PED_RET_NOKEY           (PED_RET_BASE_NO +  9)	//  No designated key in PED
#define PED_RET_KEYFULL         (PED_RET_BASE_NO + 10)	//  Key space is full
#define PED_RET_OTHERAPPKEY     (PED_RET_BASE_NO + 11)	//  The designated key is not belong to this APP
#define PED_RET_KEYLENERR       (PED_RET_BASE_NO + 12)	//  The key length error
#define PED_RET_NOPIN           (PED_RET_BASE_NO + 13)	//  Card holder press ENTER directly when enter PIN(no PIN)
#define PED_RET_CANCEL          (PED_RET_BASE_NO + 14)	//  Card holder press CANCEL to quit enter PIN
#define PED_RET_TIMEOUT         (PED_RET_BASE_NO + 15)	//  Timeout
#define PED_RET_NEEDWAIT        (PED_RET_BASE_NO + 16)	//  Two frequent between 2 sensitive API
#define PED_RET_KEYOVERFLOW     (PED_RET_BASE_NO + 17)	//  DUKPT KEY overflow
#define PED_RET_NOCARD          (PED_RET_BASE_NO + 18)	//  No ICC
#define PED_RET_ICCNOTPWRUP     (PED_RET_BASE_NO + 19)	//  ICC no power up
#define PED_RET_PARITYERR       (PED_RET_BASE_NO + 20)	//  The parity incorrect
#define PED_RET_UNSUPPORTED		(PED_RET_BASE_NO + 255)	//  can not support

/*
 * 手动注入密钥分量定义
 */
#define TYPE_INPUT_KEY_A		(1 << 0)
#define TYPE_INPUT_KEY_B		(1 << 1)
#define TYPE_INPUT_KEY_ALL		(TYPE_INPUT_KEY_A | TYPE_INPUT_KEY_B)

/*
 * RSA 模位数
 */
#define MIN_RSA_BITS            2048
#define MAX_RSA_BITS            2048//4096

typedef struct
{
    char		Model[16];		// Machine Type
    char		HwVer[16];		// Hardware Version
    char		SwVer[16];		// Software Version
    uint32_t	Status;			// PED status
    uint32_t	MaxBps;			// PED MAX Baud Rate 
    uint32_t	MaxAppNum;		// Max Application Number
    uint32_t	MasterKeyNum;	// Max Master Key Number
    uint32_t	PINKeyNum;		// Max PIN Key Number
    uint32_t	MACKeyNum;		// Max MAC Key Number
    uint32_t	FixPINKeyNum;	// Max Fixed PIN Key Number
    uint32_t	FixMACKeyNum;	// Max Fixed MAC Key Number
    uint32_t	DukptKeyNum;	// Max DUKPT Key Number
	uint32_t	Ctime;			// Create Time
	uint32_t	MagKeyTime;		// MagKey Create Time
	uint32_t	MagKeyStatus;	// MagKey valid or not
	int16_t		MaxTemp;		// High Temperature Limit
	int16_t		MinTemp;		// Low  Temperature Limit
	int16_t		CurTemp;		// Current CPU Temperature
	uint32_t	EAKKeyNum;		// Max EAK Key Number
	 uint32_t	FixEAKKeyNum;	// Max Fixed EAK Key Number
    uint8_t		Res[146];		// Reserved
}PedConfig_t;   				// Total 256 bytes

typedef struct {
     uint32_t   modlen;           // The module length of PIN encryption public key,
     uint8_t    mod[256];         // The module data of PIN encryption public key,
     uint32_t   explen;           // The exponet length of PIN encryption public key,
     uint8_t    exp[4];           // The exponet data of PIN encryption public key,
     uint8_t    iccrandom[8];     // The random data from ICC
} RsaPinKey_t;

typedef struct {
    uint8_t     cla;
    uint8_t     ins;
    uint8_t     p1;
    uint8_t     p2;
    uint8_t     leflg;
    uint8_t     le;
    RsaPinKey_t rsakey;
} IccOfflinePinApdu_t;

typedef struct {
    uint16_t rel_x, rel_y;
    uint16_t width, height;
    uint16_t value;
} __attribute__((packed)) tp_key_desc;

typedef struct {
	uint16_t keysystem;
	uint16_t keyindex;
	uint32_t cuid;
	uint32_t mode;
	uint16_t pin_mode;
	uint16_t pininputtime;
	char expectpinlenstr[32];
	char cardno[30];
	tp_key_desc tp_key[13];
} __attribute__((packed)) tp_key_map;

/**
 * @fn          ped_open
 * @brief       open PED for further use
 * @param in    none
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        This API must be called before other PED API be called.
 *              Call it only once is enough.
 */
int ped_open(void);

/**
 * @fn          ped_close
 * @brief       close PED and release the resource
 * @param in    none
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        This API should be called after ped_open.
 *              ped_open and ped_close should be a pair.
 */
int ped_close(void);

/**
 * @fn          ped_get_random
 * @brief       get a 32-bits random data from RNG by PED
 * @param in    none
 * @param out   none
 * @return      random data
 * @note        
 */
uint32_t ped_get_random(void);

/**
 * @fn          ped_get_random_nr
 * @brief       get a serials of random data from RNG by PED
 * @param in    bytes - how many data you want to get
 * @param out   data  - point the buffer that data save to
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */
int ped_get_random_nr(uint32_t bytes, void *data);

/**
 * @fn          ped_get_config
 * @brief       get configuation of PED
 * @param in    none
 * @param out   config - point the buffer that inforamtion save to
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */
int ped_get_config(PedConfig_t *config);

/**
 * @fn          ped_get_full_status
 * @brief       get the ped status, it can tell you the tamper source
 * @param in    none
 * @param out   status - tamper source (0-normal, else-tamper source)
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */
int ped_get_full_status(uint64_t *status);

/**
 * @fn          ped_set_pin_input_region
 * @brief       set position and size of PIN input window
 * @param in    x,y - start pointer of window
 * @param in    width,height - window size, it will be ignore in A-SMART platform
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */
int ped_set_pin_input_region(int x, int y, int width, int height);

/**
 * @fn          ped_format
 * @brief       clear all the Keys and tamper, make PED enter normal status
 * @param in    none
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        if PED is tampered, normal application call this function will be refused;
 *              privilege application can call it at any time.
 */
int ped_format(void);

#if 0
/**
 * @fn          ped_clear_user_keys
 * @brief       clear all the Keys belongs to this application, 
 *              other Keys not belong to this application will not be clear.
 * @param in    none
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */
int ped_clear_user_keys(void);

/**
 * @fn          ped_clear_all_keys
 * @brief       clear all keys injected or written in device
 * @param in    none
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */
int ped_clear_all_keys(void);

/**
 * @fn          ped_delete_key_unified
 * @brief       delete a Key that belong to this APP
 * @param in    KeySystem: MS_DES, MS_SM4, FIXED_DES, FIXED_SM4, DUKPT_DES
 * @param in    KeyType  : KEY_TYPE_PINK, KEY_TYPE_MACK, KEY_TYPE_EAK
 * @param in    KeyIndex : index of Key
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        KeySystem and KeyType can decide which type of key will be deleted.
 *              for example, KeySystem is FIXED_DES, KeyType is KEY_TYPE_PINK, the key should be "Fixed PIN Key"
 */
int ped_delete_key_unified(KeySystem_t KeySystem, uint32_t KeyType, uint32_t KeyIndex);
#endif

/**
 * @fn          ped_get_sensitive_timer
 * @brief       get timer left of call sensitive service, for example PIN enter.
 * @param in    SensitiveType - TYPE_PIN_INTERVAL, TYPE_ACCOUNT_INTERVAL, TYPE_UPDATE_INTERVAL
 * @param out   none
 * @return      >=0  - time left in seconds
 *              else - failure, use errno to get detail
 * @note        
 */
int ped_get_sensitive_timer(uint32_t SensitiveType);

/**
 * @fn          ped_get_sensitive_timer
 * @brief       try and get timer left of call sensitive service, for example PIN enter, Sensitive count add 1.
 * @param in    SensitiveType - TYPE_PIN_INTERVAL, TYPE_ACCOUNT_INTERVAL, TYPE_UPDATE_INTERVAL
 * @param out   none
 * @return      >=0  - time left in seconds
 *              else - failure, use errno to get detail
 * @note
 */
int ped_try_and_get_sensitive_timer(uint32_t SensitiveType);


/**
 * @fn          ped_set_pin_input_timeout
 * @brief       set timeout of PIN input
 * @param in    timeout - seconds of input timeout, 0 ~ 60
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */
int ped_set_pin_input_timeout(uint32_t timeout);
int ped_get_pin_input_timeout(void);

/**
 * @fn          ped_create_dukpt_key
 * @brief       create a DUKPT key and save to PED
 * @param in    KeyIndex - index of key, 0 ~ 99
 * @param in    InitKey  - initialized key, 16 bytes.
 * @param in    KeyLen   - ignored, default is 16
 * @param in    Ksn      - KSN, 10 bytes.
 * @param out   OutLen   - After encryption, the length of the key//加密后，密钥的长度
 				KeyOut	 - Ciphertext Key, save in the ap side //密文 KEY, 保存在AP端
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */
 int ped_create_dukpt_key(uint32_t    KeyIndex,
						 uint32_t    CUID,
                         const void *InitKey,
                         uint32_t    KeyLen,
                         const void *Ksn,
                         uint32_t   *OutLen,
                         void		*KeyOut);

/**
 * @fn          ped_dukpt_renew
 * @brief       update KSN of this DUKPT Key, KSN will increased
 * @param in    KeyIndex - index of key, 0 ~ 99
 * @param out   KSN - point buffer to be saved
			    OutLen   - After encryption, the length of the key//加密后，密钥的长度
 				KeyOut	 - Ciphertext Key, save in the ap side //密文 KEY, 保存在AP端
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        call it once can allow you enter PIN and get mac one time individually.
 */
int ped_dukpt_renew(uint32_t KeyIndex, 
							 uint32_t CUID,
							 void *Ksn,
							 uint32_t KeyLen,
							 const void *KeyIn,
							 uint32_t *OutLen,
							 void *KeyOut);

/**
 * @fn          ped_get_dukpt_ksn
 * @brief       get KSN of this DUKPT Key
 * @param in    KeyIndex - index of key, 0 ~ 99
 * @param out   KSN - point buffer to be saved
 				OutLen   - After encryption, the length of the key//加密后，密钥的长度
 				KeyOut	 - Ciphertext Key, save in the ap side //密文 KEY, 保存在AP端
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        call it once can allow you enter PIN and get mac one time individually.
 */
int ped_get_dukpt_ksn(uint32_t KeyIndex, 
								uint32_t CUID,
								void *Ksn,
								uint32_t KeyLen,
								const void *KeyIn,
								uint32_t *OutLen,
								void *KeyOut);

/**
 * @fn          ped_dukpt_encrypt_request
 * @brief       encrypt request data that to be sent to server
 * @param in    KeyIndex - index of key, 0 ~ 99
 				KeyLen   - length of Key in bytes
 				DukptKey - ciphertext Key
 * @param in    DataLen  - length of DataIn in bytes
 * @param in    DataIn   - plaintext data
 * @param out   DataOut  - ciphertext data
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        call this function will not increase KSN
 */

int ped_dukpt_encrypt_request(uint32_t    KeyIndex,
							  uint32_t    CUID,
							  uint32_t    KeyLen,
							  const void *DukptKey,
                              uint32_t    DataLen,
                              const void *DataIn,
                              void       *DataOut);

/**
 * @fn          ped_dukpt_decrypt_response
 * @brief       decrypt response data the received from server
 * @param in    KeyIndex - index of key, 0 ~ 99
 				KeyLen   - length of Key in bytes
 				DukptKey - ciphertext Key
 * @param in    DataLen  - length of DataIn in bytes
 * @param in    DataIn   - ciphertext data
 * @param out   DataOut  - plaintext data
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        call this function will not increase KSN
 */
int ped_dukpt_decrypt_response(uint32_t    KeyIndex,
								   uint32_t    CUID,
								   uint32_t    KeyLen,
								   const void *DukptKey,
	                               uint32_t    DataLen,
	                               const void *DataIn,
	                               void       *DataOut);

/**
 * @fn          ped_dukpt_calc_mac_response
 * @brief       cacluate MAC of response data that receive from server
 * @param in    KeyIndex - index of key, 0 ~ 99
 				KeyLen   - length of Key in bytes
 				DukptKey - ciphertext Key
 * @param in    Mode     - [MAC_MODE_1, MAC_MODE_2, MAC_MODE_EMV, MAC_MODE_CUP, MAC_MODE_DUKPT]
 * @param in    DataLen  - length of DataIn in bytes
 * @param in    DataIn   - point data buffer to be calcuated
 * @param out   MacBlock - 8 bytes
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        call this function will not increase KSN
 */
int ped_dukpt_calc_mac_response(uint32_t    KeyIndex,
								uint32_t    CUID,
								uint32_t    KeyLen,
							    const void *DukptKey,
                                uint32_t    Mode,
                                uint32_t    DataLen,
                                const void *DataIn,
                                void       *MacBlock);

/**
 * @fn          ped_dukpt_verify_mac_response
 * @brief       verify MAC of response data that receive from server
 * @param in    KeyIndex - index of key, 0 ~ 99
 * @param in    Mode     - [MAC_MODE_1, MAC_MODE_2, MAC_MODE_EMV, MAC_MODE_CUP, MAC_MODE_DUKPT]
 				KeyLen   - length of Key in bytes
 				DukptKey - ciphertext Key
 * @param in    DataLen  - length of DataIn in bytes
 * @param in    DataIn   - point data buffer to be calcuated
 * @param in    MacBlock - MAC that receive from server
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        call this function will not increase KSN
 *              this function use the same key as ped_get_mac_unified(DUKPT_DES)
 */
int ped_dukpt_verify_mac_response(uint32_t    KeyIndex,
								  uint32_t    CUID,
								  uint32_t    KeyLen,
							      const void *DukptKey,
                                  uint32_t    Mode,
                                  uint32_t    DataLen,
                                  const void *DataIn,
                                  const void *MacBlock);

/**
 * @fn          ped_write_key_unified
 * @brief       save key in to PED that encrypted by master key.
 * @param in    KeySystem      - MS_DES, MS_SM4
 * @param in    KeyType        - KEY_TYPE_PINK, KEY_TYPE_MACK, KEY_TYPE_EAK
 * @param in    Mode           - verify mode
 *                                  KEY_VERIFY_NONE
 *                                  KEY_VERIFY_KVC
 *                                  KEY_VERIFY_CMAC
 *                                  KEY_VERIFY_SM4_KVC
 * @param in    MasterKeyIndex - index of master key
 * @param in    DestKeyIndex   - index of target key
 * @param in 	MasterKeyLen   - the length of the master key
 * @param in    Key            - key content include master key and write Key
 * @param out   OutLen   - After encryption, the length of the key//加密后，密钥的长度
 				KeyOut	 - Ciphertext Key, save in the ap side //密文 KEY, 保存在AP端
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        KeySystem and KeyType can decide which type of key will be written.
 *              for example, KeySystem is FIXED_DES, KeyType is KEY_TYPE_PINK, the key should be "Fixed PIN Key"
 */
int ped_write_key_unified(KeySystem_t KeySystem,
						  uint32_t	  KeyType,
						  uint32_t	  CUID,
						  uint32_t	  DestKeyIndex,
						  uint32_t	  Mode,
						  uint32_t	  MasterKeyLen,
						  void       *MasterKey,
						  uint32_t	  KeyLen,
						  const void *KeyData,
						  uint32_t	 *OutLen,
						  void		 *KeyOut);


/**
 * @fn          ped_get_pin_unified
 * @brief       input user's PIN and encrypted it, return pin block to app
 * @param in    KeySystem    - MS_DES, MS_SM4, FIXED_DES, FIXED_SM4, DUKPT_DES
 * @param in    KeyIndex     - index of key
 * @param in    Mode         - DES(MS_DES, FIXED_DES, DUKPT_DES) can support : PIN_BLOCK_FORMAT_0, PIN_BLOCK_FORMAT_EPS
 *                             SM4(MS_SM4, FIXED_SM4) can support  : PIN_BLOCK_FORMAT_0
 * @param in    ExpectPinLen - list of expected length, format is [digit<,digit>], no more than 12,
 *                             for example, "0,6,7,8,12"
 * @param in    CardNo       - processed card No, 16 bytes, first 4 bytes are invalid, just use last 12 bytes
 * @param out   PinBlock     - DES : 8 bytes PIN Block
 *                             SM4 : 16 bytes PIN Block 
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        if one of MS_DES/FIXED_DES/DUKPT_DES seleted, this function will use DES to calculate PIN, PIN block are 8 bytes
 *              if one of MS_SM4/FIXED_SM4 selected, this function will use SM4 to calculate PIN, PIN block are 16 bytes
 */
int ped_get_pin_unified(KeySystem_t KeySystem,
                        uint32_t    KeyIndex,
                        uint32_t    CUID,
                        uint32_t    Mode,
                        const char *ExpectPinLen,
                        const char *CardNo,
                        void       *PinBlock);

/**
 * @fn          ped_icc_get_slotno
 * @brief       get slot number of ic card
 * @param in    fd - device description that return by call open()
 * @param out   slotno - current slot number
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        this function use to get slot number of ic card, slot number is
 *              need by function ped_get_offline_pin
 */
//int ped_icc_get_slotno(int fd, uint32_t *slotno);

/**
 * @fn          ped_get_offline_pin
 * @brief       input PIN and send offline pin block to IC card then get response
 * @param in    KeySystem    - ICC_PLAIN, ICC_CIPHER
 * @param in    slotno       - No. of IC card slot, user can use ped_get_offline_pin() to got it
 * @param in    ExpectPinLen - list of expected length, format is [digit<,digit>], no more than 12,
 *                             for example, "0,6,7,8,12"
 * @param in    icc          - APDU information, CLA＋INS＋P1＋P2＋LC
 * @param out   rsplen       - length of rspdata in bytes
 *              rspdata      - response data that received from IC card, format is SWA＋SWB
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        ICC_PLAIN    - offline plaintext PIN, don't encrypt user's PIN
 *              ICC_CIPHER   - offline ciphertext PIN, use RSA to encrypt user's PIN
 */ 
int ped_get_offline_pin(KeySystem_t                KeySystem,
						uint32_t    			   CUID,
                        uint32_t                   slotno,
                        const char                *ExpectPinLen,
                        const IccOfflinePinApdu_t *icc,
                        uint32_t                  *rsplen,
                        void                      *rspdata);

/**
 * @fn          ped_get_mac_unified
 * @brief       calculate MAC of data
 * @param in    KeySystem - MS_DES, MS_SM4, FIXED_DES, FIXED_SM4, DUKPT_DES
 * @param in    KeyIndex  - index of key
 * @param in    Mode      - MS_DES, MS_SM4, FIXED_DES, FIXED_SM4 can support: MAC_MODE_1, MAC_MODE_2, MAC_MODE_EMV, MAC_MODE_CUP
 *                          DUKPT_DES can support : MAC_MODE_1, MAC_MODE_2, MAC_MODE_EMV, MAC_MODE_CUP, MAC_MODE_DUKPT                                 
 * @param in	KeyLen    - length of Key in bytes
 * @param in	KeyIn     - ciphertext Key
 * @param in    DataLen   - length of DataIn in bytes
 *                          DES : must be a multiple of 8
 *                          SM4 : must be a multiple of 16
 * @param in    DataIn    - point buffer to be calcuated
 * @param out   MacOut    - MAC block
 *                          DES : 8 bytes
 *                          SM4 : 16 bytes
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        if one of MS_DES/FIXED_DES/DUKPT_DES selected, this function will use DES to calculate MAC, result are 8 bytes
 *              if one of MS_SM4/FIXED_SM4/KS_ANS selected, this function will use SM4 to calculate MAC, result are 16 bytes
 */
int ped_get_mac_unified(KeySystem_t KeySystem,
                        uint32_t    KeyIndex,
                        uint32_t    CUID,
                        uint32_t    Mode,
                        uint32_t    KeyLen,
						void       *KeyIn,
                        uint32_t    DataLen,
                        const void *DataIn,
                        void       *MacBlock);
/**
 * @fn          ped_get_account
 * @brief       Account Data encrypt
 * @param in    KeySystem - MS_DES, FIXED_DES
 * @param in    Mode      - only support TDEA_ENCRYPT
 * @param in    KeyIndex  - index of key
 * @param in	KeyLen    - length of Key in bytes
 * @param in	KeyIn     - ciphertext Key
 * @param in    DataLen   - length of DataIn, must be a multiple of 8
 * @param in    DataIn    - point buffer to be encrypted
 * @param out   DataOut   - point buffer to save ciphertext data
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        this function use KEY_TYPE_EAK encrypt data by DES
 */
int ped_get_account(KeySystem_t KeySystem,
                    uint32_t    KeyIndex,
                    uint32_t    CUID,
                    uint32_t    Mode,
                    uint32_t    KeyLen,
					const void *KeyIn,
                    uint32_t    DataLen,
                    const void *DataIn,
                    void       *DataOut);

/**
 * @fn          ped_inject_key
 * @brief       inject plaintext key
 * @param in    KeySystem - FIXED_DES, FIXED_SM4
 * @param in    KeyType   - KEY_TYPE_PINK, KEY_TYPE_MACK, KEY_TYPE_EAK
 * @param in    KeyIndex  - index of key
 * @param in    KeyLen    - length of Key in bytes
 * @param in 	MasterKeyLen   - the length of the master key
 * @param in    Key            - key content include master key and write Key
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        KeySystem and KeyType can decide which type of key will be injected.
 *              for example, KeySystem is FIXED_DES, KeyType is KEY_TYPE_PINK, the key should be "Fixed PIN Key"
 */
int ped_inject_key(KeySystem_t KeySystem,
                   uint32_t    KeyType,
                   uint32_t    KeyIndex,
                   uint32_t    CUID,
                   uint32_t    KeyLen,
                   const void *Key,
                   uint32_t   *OutLen,
                   void       *KeyOut);

/**
 * @fn          ped_root_inject_key
 * @brief       inject key by privilege application, normal APP will be refused
 * @param in    KeySystem - MS_DES, MS_SM4, FIXED_DES, FIXED_SM4, DUKPT_DES
 * @param in    KeyType   - KEY_TYPE_MASTK, KEY_TYPE_PINK, KEY_TYPE_MACK, KEY_TYPE_EAK
 * @param in    KeyIndex  - index of key
 * @param in    CUID      - CID and UID
 * @param in    KeyLen    - length of PlaintextKey in bytes
 * @param in 	MasterKeyLen   - the length of the master key
 * @param in    PlaintextKey - plaintext key and master key
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        KEY_TYPE_EAK only MS_DES can supported
 */
#if 0
int ped_root_inject_key(KeySystem_t KeySystem,
                        uint32_t    KeyType,
                        uint32_t    KeyIndex,
                        uint32_t    CUID,
                        uint32_t    KeyLen,
                        uint32_t    MasterKeyLen,
                        const void *PlaintextKey,
                        uint32_t   *OutLen,
                        void	   *KeyOut);
#endif
/**
 * @fn          ped_check_key_unified
 * @brief       check specified key exist or not
 * @param in    KeySystem - MS_DES, MS_SM4, FIXED_DES, FIXED_SM4, DUKPT_DES
 * @param in    KeyType   - KEY_TYPE_MASTK, KEY_TYPE_PINK, KEY_TYPE_MACK
 * @param in    KeyIndex  - index of key
 * @param in    Mode      - not used for the moment, set to 0
 * @param in    KeyLen    - the length of the key
 * @param in    KeyData   - ciphertext key
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        KEY_TYPE_EAK is not supported for the moment
 */
int ped_check_key_unified(KeySystem_t KeySystem,
                          uint32_t    KeyType,
                          uint32_t    KeyIndex,
                          uint32_t    CUID,
                          uint32_t    Mode,
                          uint32_t    KeyLen,
                          const void *KeyData);


/**
 * @fn          ped_set_login_limit
 * @brief       config login max error count and time limit 
 * @param in    max_err_cnt    -- default value is 3, can only set less than default value
 * @param in    err_delay_time -- default value is 3, can only set more than default value
 * @param in    lock_time      -- default value is 30, can only set more than default value
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @author      Brian.Yang
 * @date        2016-03-29
 * @note        
 *				Once input a wrong login password, you have to wait 'err_delay_time' seconds to input password again.
 *				If continue input wrong password 'max_err_cnt' times, then will be locked in 'lock_time' seconds.
 *				Once input a correct password, the limit will reset
 */
int ped_set_login_limit(uint32_t max_err_cnt, uint32_t err_delay_time, uint32_t lock_time);

/**
 * @fn          ped_get_login_limit
 * @brief       get login left error count and wait time
 * @param in    none
 * @param out   left_err_cnt -- the chance you can try to input another password
 * @param out   wait_time    -- the time you have to wait before try to input another password 
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @author      Brian.Yang
 * @date        2016-03-29
 * @note        
 *				Once input a correct password, the limit will reset
 */
int ped_get_login_limit(uint32_t *left_err_cnt, uint32_t *wait_time);

/**
 * @fn          ped_inject_key_by_hand
 * @brief       inject key by inputing 2 conponent TYPE_INPUT_KEY_A and TYPE_INPUT_KEY_B of key data
 * @param in    Type      - TYPE_INPUT_KEY_A or TYPE_INPUT_KEY_B
 * @param in    KeySystem - MS_DES, MS_SM4, FIXED_DES, FIXED_SM4, DUKPT_DES
 * @param in    KeyType   - KEY_TYPE_MASTK, KEY_TYPE_PINK, KEY_TYPE_MACK, KEY_TYPE_EAK
 * @param in    KeyIndex  - index of key
 * @param in    CUID      - CID and UID
 * @param in    KSN       - valid when KeySystem is DUKPT;
 *							set NULL when KeySystem is not DUKPT
 * @param in    Key       - key value
 * @param out   State	  - STATE_INPUT_OK		current input key value OK
 *							STATE_INPUT_ENTER	current input key value is Enter
 *							STATE_INPUT_CLEAR	current input key value is Clear
 *							STATE_INPUT_CANCEL	current input key value is Cancel
 *							STATE_INPUT_ERROR	current input key value not correct
 * @param out   KeyLen	  - the length had inputted	
 * @return      0    - success
 *              else - failure, use errno to get detail      
 * @author      Brian.Yang
 * @date        2016-04-05
 * @note        
 */
#if 0
int ped_inject_key_by_hand(uint32_t    Type,
                           uint32_t    KeySystem,
                           uint32_t    KeyType,
                           uint32_t    KeyIndex,
                           uint32_t    CUID,
                           const void *Ksn,
                           int         Key,
                           uint32_t   *State,
                           uint32_t   *KeyLen,
                           uint32_t   *OutLen,
                           void       *KeyOut);

#endif

/**
 * @fn          ped_input_pwd
 * @brief       input login password
 * @param in    Key       - key value
 * @param out   State	  - STATE_INPUT_OK		current input key value OK
 *							STATE_INPUT_ENTER	current input key value is Enter
 *							STATE_INPUT_CLEAR	current input key value is Clear
 *							STATE_INPUT_CANCEL	current input key value is Cancel
 *							STATE_INPUT_ERROR	current input key value not correct
 * @param out   PwdLen	  - the length had inputted	
 * @return      0    - success
 *              else - failure, use errno to get detail  
 * @author      Brian.Yang
 * @date        2016-04-05
 * @note        
 */
int ped_input_pwd(int Key, uint32_t *State, uint32_t *PwdLen);

/**
 * @fn          ped_verify_pwd
 * @brief       verify input password by comparing with ciphertext string
 * @param in    CiphPwd - ciphertext string
 * @param in    login   - 1: used for login verify
 *						  0: used for modify password verify
 * @param out   none
 * @return      0    - success
 *              else - failure, use errno to get detail        
 * @author      Brian.Yang
 * @date        2016-04-05
 * @note        
 */
int ped_verify_pwd(const char *CiphPwd, uint32_t login);

/**
 * @fn          ped_get_cipherpwd
 * @brief       get the ciphertext string of input password
 * @param in	CiphPwdSize - buffer size of CiphPwd
 * @param out   CiphPwd 	- ciphertext string 
 * @return      0    - success
 *              else - failure, use errno to get detail        
 * @author      Brian.Yang
 * @date        2016-04-05
 * @note        
 */
int ped_get_cipherpwd(char *CiphPwd, uint32_t CiphPwdSize);

int ped_save_cipherpwd(char *user);

/**
 * @fn          ped_get_reboot_time_left
 * @brief       get the time left before reboot
 * @param in    none
 * @param out   time_left -- time left before reboot
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @author      Brian.Yang
 * @date        2016-04-16
 * @note        
 */
int ped_get_reboot_time_left(uint32_t *time_left);

/**
 * @fn          ped_des_crypto
 * @brief       encrypt/decrypt data by DES
 * @param in    Mode      - (TDEA_ENCRYPT or TDEA_DECRYPT) | (TDEA_MODE_ECB or TDEA_MODE_CBC)
 * @param in    IV        - initial IV, must be 8 bytes
 * @param in    KeyLen    - length DesKey, must be 8/16/24
 * @param in    DesKey    - plain des/3des key
 * @param in    DataIn    - point buffer to be encrypt/decrypt,no more then 512K bytes
 * @param out   IV        - update iv after call this function
 * @param out   DataOut   - point buffer to save decrypt/encrypt data
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        this function support DES/TDES
 */
int ped_des_crypto(uint32_t Mode,    uint8_t IV[8],
				   uint32_t KeyLen,  const void *DesKey,
				   uint32_t DataLen, const void *DataIn, void *DataOut);


/**
 * @fn          ped_des_key_crypto_unified
 * @brief       choose key to encrypt/decrypt data by DES
 * @param in    KeySystem - TMS_DES, MS_DES, FIXED_SM4
 * @param in    KeyType   - For encrypt KEY_TYPE_MACK, KEY_TYPE_EAK
 * @param in    KeyIndex  - index of key
 * @param in	KeyLen    - length of Key in bytes
 * @param in	KeyIn     - ciphertext Key
 * @param in    Mode      - (TDEA_ENCRYPT or TDEA_DECRYPT) | (TDEA_MODE_ECB or TDEA_MODE_CBC)
 * @param in    IV        - initial IV, must be 8 bytes
 * @param in    DataIn    - point buffer to be encrypt/decrypt
 * @param out   IV        - update iv after call this function
 * @param out   DataOut   - point buffer to save decrypt/encrypt data
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        this function support DES/TDES
 */
int ped_des_key_crypto_unified(KeySystem_t KeySystem,
                               uint32_t    KeyType,
                               uint32_t    KeyIndex,
                               uint32_t    CUID,
                               uint32_t    Mode,
                               uint8_t     IV[8],
                               uint32_t    KeyLen,
                               const void *KeyIn,
                               uint32_t    DataLen,
                               const void *DataIn,
                               void       *DataOut);


/**
 * @fn          ped_get_key_kvc
 * @brief       get work key kvc
 * @param in    KeySystem: MS_DES, MS_SM4, FIXED_DES, FIXED_SM4, DUKPT_DES
 * @param in    KeyType  : KEY_TYPE_PINK, KEY_TYPE_MACK, KEY_TYPE_EAK
 * @param in    KeyIndex : index of Key
 * @param in	KeyLen    - length of Key in bytes
 * @param in	KeyIn     - ciphertext Key
 * @param out   KVC		 : KVC
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        For UMS certification, only support key type KEY_TYPE_PINK, KEY_TYPE_MACK, KEY_TYPE_EAK in MS_DES key system.
 */
int ped_get_key_kvc(KeySystem_t KeySystem,
							 uint32_t    KeyType,
							 uint32_t    KeyIndex,
							 uint32_t    CUID,
							 uint32_t    KeyLen,
							 const void *KeyIn,
							 uint8_t KVC[4]);


int ped_get_machine_type(uint32_t *type);

/**
 * @fn          ped_get_button_type
 * @brief       get pinpad key type
 * @param in    none
 * @param out   type :返回按键类型
 *										01:表示触摸屏
 *										02:表示矩阵按键
 * @return      0  : OK
 *              -1 : Failed
 * @author      Jiang.Li
 * @date        2016-11-24
 * @note        
 */
int ped_get_button_type(uint32_t *type);

/**
 * @fn          ped_get_keymap_position
 * @brief       get pinpad keymap[0-9,Cancle,Clear,Enter] position
 * @param in    输入0-9按键的坐标值，但是不知道是什么按键，还有PID号
 * @param out   输出按键坐标值所对应的按键
 * @return      0  : OK
 *              -2003 : Failed
 * @author      Jiang.Li
 * @date        2016-11-24
 * @note        
 */
//int ped_get_keymap_position(tp_key_map *map);
int ped_get_keymap_position(tp_key_map *map, uint32_t KeyLen, const void *KeyIn);


/**
 * @fn          ped_query_pin_input_by_user
 * @brief       query current pin input status
 * @param in    none
 * @param out   nr_pin  : 已经输入PIN的个数
 *              status  : 当前输入状态
 *                        1 : 表示当前正在输入
 *                        0 : 表示当前未开始输入, 或者已经输入完成, 或用户取消输入
 *              user_hit : 用户按键次数，每点击一次计数一次
 *              timeleft : PIN输入剩余时间，单位ms
 * @return      0  : OK
 *              -1 : Failed
 * @author      Brian.Yang
 * @date        2016-09-13
 * @note        
 */
int ped_query_pin_input_by_user(uint32_t *nr_pin, uint32_t *status, uint32_t *user_hit, uint32_t *timeleft);

/**
 * @fn          ped_cancel_pin_input_by_user
 * @brief       cancel pin input by user
 * @param in    none
 * @param out   none
 * @return      0  : OK
 *              -1 : Failed
 * @author      Brian.Yang
 * @date        2016-09-13
 * @note        
 */
int ped_cancel_pin_input_by_user(void);



/**
 * @fn          ped_rsa_private_operation
 * @brief       rsa private operation
 * @param in    KeyIndex  - index of key
 * @param in	KeyLen    - length of Key in bytes
 * @param in	KeyIn     - ciphertext Key
 * @param in    input     - point buffer to be operated
 * @param in    inputLen  - length of input
 * @param out   output    - point buffer to save operated data
 * @param [in/out]
 *              outputLen 
 *                        - [in]  size of output buffer
 *                        - [out] length of real output data
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */
int ped_rsa_private_operation(uint32_t    KeyIndex,
							  uint32_t    CUID,
							  uint32_t    KeyLen,
							  const void *KeyIn,
                              void       *output, 
                              uint32_t   *outputLen, 
                              const void *input, 
                              uint32_t    inputLen);

/**
 * @fn          ped_rsa_export_pub_key
 * @brief       export rsa public key
 * @param in    KeyIndex  - index of key
 * @param in	KeyLen    - length of Key in bytes
 * @param in	KeyIn     - ciphertext Key
 * @param out   PubKey    - point buffer to save public key data
 * @param [in/out]
 *              KeyLen 
 *                        - [in]  buffer size to save pubkey
 *                        - [out] length of real output data
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */
int ped_rsa_export_pub_key(uint32_t    KeyIndex,
										uint32_t    CUID,
										uint32_t    RsaKeyLen,
							  			const void *KeyIn,
							  			void       *PubKey,
							  			uint32_t   *KeyLen);

int ped_rsa_decrypt_pub_key_cert(uint32_t    KeyIndex,
                           uint32_t    CUID,
                           uint32_t    KeyType,
                           uint32_t    InputLen,
                           const void *Input,
                           void       *Output,
                           uint32_t   *OutputLen);

int ped_rsa_verify_pub_key_cert(uint32_t    KeyIndex,
                           uint32_t    CUID,
                           uint32_t    KeyType,
                           uint32_t    InputLen,
                           const void *Input);


int ped_query_pin_input(uint32_t *pin_len,
								   uint32_t *status_out,
								   uint32_t *timeleft,
								   uint32_t *Pinblock_len,
								   void *PinBlock);

int ped_bbl_tamper(uint64_t *status);

int ped_read_otp_info(OtpSys_t id, void *data, uint32_t *len);

int ped_write_otp_info(OtpSys_t id, const void *data, uint32_t len);

#if defined (RANDOM_KEYBOARD_AND_CANCEL_ENTER_BUTTON)	
/**
 * @fn          set_pin_keymap_random
 * @brief       PIN keymap random
 * @input       0:random    1:not random
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */
int set_pin_keymap_random(uint32_t value);

/**
 * @fn          ped_cancel_pin_input
 * @brief       PIN keymap random
 * @return      0    - success
 *              else - failure, scpd failed
 * @note        
 */
int ped_cancel_pin_input(void);

/**
 * @fn          set_pin_keymap_random
 * @brief       PIN keymap random
 * @return      0    - success
 *              else - failure, scpd failed
 * @note        
 */
int ped_entry_pin_input(void);

#endif


#ifdef __cplusplus 
}
#endif 

#endif

