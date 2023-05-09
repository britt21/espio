
#ifndef _FILE_NAME_H_
#define _FILE_NAME_H_

#include <android/log.h>

#define OBJECT_ID_MAX_LEN           64
#define KEY_DIR                     "/data/key"
#define PED_RET_COLLISION_KEY   	2007  //  collision key
#define PED_RET_NOKEY           	2009  //  No designated key in PED

static const char FILE_INTEGRITY_FLAG[16] = "FILE INTEGRATED";

#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, "Keymanage", __VA_ARGS__)

//#define KEY_DEBUG
#if defined(KEY_DEBUG)
//#define key_debug(format, args...) printf(format, ##args)
#define key_debug LOGD
#else
#define key_debug(format, args...)	do {} while (0)

#endif


/*
 * 密钥体系
 */
typedef enum {
    MS_DES          = 0x00, /* 0 : Master Session DES */
    MS_SM4,                 /* 1 : Master Session SM4 */
    FIXED_DES,              /* 2 : FIXED DES */
    FIXED_SM4,              /* 3 : FIXED SM4 */
    DUKPT_DES,              /* 4 : DUKPT DES */
    ICC_PLAIN,              /* 5 : ic card Offline plain pin */
    ICC_CIPHER,             /* 6 : ic card offline cipher pin */
    TMS_DES,				/* 7 : TMS DES   */
    KS_SM2,                 /* 8 : SM2 key system */
    KS_RSA,                 /* 9 : RSA */
    KS_ANS,                 /* 10: ANS SM4 */
    MS_AES, 				/* 11 : Master Session AES */
    FIXED_AES,				/* 12 : FIXED AES */
    KS_MAX,                 /* END */
} KeySystem_t;

/*
 * 密钥类型
 */
#define KEY_TYPE_SIEK           0x01    // The key to encrypt the internal sensitive infomation(internal use)
#define KEY_TYPE_MASTK          0x02    // MASTER KEY
#define KEY_TYPE_PINK           0x03    // PIN KEY
#define KEY_TYPE_MACK           0x04    // MAC KEY
#define KEY_TYPE_FIXPINK        0x05    // Fixed PIN KEY
#define KEY_TYPE_FIXMACK        0x06    // Fixed MAC KEY
#define KEY_TYPE_DUKPTK         0x07    // DUKPT KEY
#define KEY_TYPE_EMRKEY         0x08    // The key for securty magstripe reader
#define KEY_TYPE_KMMK           0x09    // The key for KMM
#define KEY_TYPE_EAK            0x0A    // Account Data KEY
#define KEY_TYPE_FIXEAK         0x0B    // Fixed Account Data KEY
#define KEY_TYPE_TMSK			0x0C	// TMS KEY
#if defined(CFG_GM_HW)
#define KEY_TYPE_SM2PRI			0x0D	// SM2 Private KEY
#endif
#define KEY_TYPE_RSAPRIK        0x0E    // RSA PRIVATE KEY
#define KEY_TYPE_ANSK           0x0F    // ANS SM4 KEY

#define KEY_TYPE_RSA_CA_CERT          0x10
#define KEY_TYPE_RSA_CLIENT_CERT      0x11

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

#define TOTAL_KEYINDEX				99

#define SM2_PRI_KEY_SIZE        32

typedef struct {
    uint16_t        KeyLen;             /* 密钥长度     */
    uint8_t         Key[24];            /* 密钥数据     */
    uint8_t         Pad[6];
} TDesSecret_t; /* 32 bytes */

typedef struct {
    uint16_t        Index;              /* 密钥逻辑编号 */
    uint8_t         KeyType;            /* 密钥类型     */
    uint8_t         Status;             /* 密钥状态     */
    uint32_t        CUID;               /* 客户和用户号 */
    uint32_t        Ctime;              /* 密钥生成时间 */

    TDesSecret_t    Secret;

    uint8_t         ChkSum[4];          /* 对前面数据的校验 */
} TDesKey_t;    /* 48 bytes */

typedef struct {
    uint8_t         Key[16];            // 密钥数据
    uint32_t        CRC;
} DukptKey_t ;      /* 24 Bytes */

typedef struct {
    uint8_t         KSN[10];            // KSN: Initial Key Serial Number: 59 bits
    uint8_t         CurUserKSN[10];     // Current use
    DukptKey_t      CurUserKey;         // 当前可供用户使用的密钥
    DukptKey_t      FutureKey[21];      // 未来密钥内容
    uint32_t        CurKeyPointer;      // 当前使用的未来密钥
} DukptSecret_t;    /* 464 Bytes 8字节的倍数 */

typedef struct {
    uint16_t        Index;              /* 密钥逻辑编号 */
    uint16_t        KeyType;            /* 密钥类型     */
    uint32_t        CUID;               /* 客户和用户码 */
    uint8_t         Status;             /* 密钥状态 */
    uint8_t         Renew;              /* 需要更新标志 */
    uint8_t         Res[2];

    DukptSecret_t   Secret;

    uint32_t        ChkSum;
} DukptObj_t;       /* 480 bytes */

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


typedef struct {
    uint16_t            Index;              /* 密钥逻辑编号 */
    uint8_t             KeyType;            /* 密钥类型     */
    uint8_t             Status;             /* 密钥状态     */
    uint32_t            CUID;               /* 客户和用户号 */
    uint32_t            Ctime;              /* 密钥生成时间 */
    
    R_RSA_PRIVATE_KEY   Secret;             /* 私钥, 2312 bytes */

    uint8_t             ChkSum[4];          /* 对前面数据的校验 */
} RsaPriKey_t;    /* 16 + 2312 = 2328 bytes */

typedef struct {
	int		len;
	uint8_t	key[SM2_PRI_KEY_SIZE];
} SM2_PriKey_t ;

typedef struct {
    uint16_t            Index;              /* 密钥逻辑编号 */
    uint8_t             KeyType;            /* 密钥类型     */
    uint8_t             Status;             /* 密钥状态     */
    uint32_t            CUID;               /* 客户和用户号 */
    uint32_t            Ctime;              /* 密钥生成时间 */
    
    SM2_PriKey_t        Secret;             /* 私钥, 36 bytes */

    uint8_t             ChkSum[4];          /* 对前面数据的校验 */
} Sm2PriKeyData_t;    /* 16 + 36 = 52 bytes */

typedef struct {
    uint16_t            Index;              /* 密钥逻辑编号 */
    uint8_t             KeyType;            /* 密钥类型     */
    uint8_t             Status;             /* 密钥状态     */
    uint32_t            CUID;               /* 客户和用户号 */
} __attribute__((packed)) KeyHead_t;

typedef struct {
    uint16_t        KeyLen;             /* 密钥长度     */
    uint8_t         Key[32];            /* 密钥数据     */
    uint8_t         Pad[6];
} TAesSecret_t; /* 40 bytes */

typedef struct {
    uint16_t        Index;              /* 密钥逻辑编号 */
    uint8_t         KeyType;            /* 密钥类型     */
    uint8_t         Status;             /* 密钥状态     */
    uint32_t        CUID;               /* 客户和用户号 */
    uint32_t        Ctime;              /* 密钥生成时间 */

    TAesSecret_t    Secret;

    uint8_t         ChkSum[4];          /* 对前面数据的校验 */
} TAesKey_t;    /* 56 bytes */

typedef TDesSecret_t    Sm4Secret_t;
typedef TDesKey_t       Sm4Key_t;


void hexdump(const void *data, uint32_t len);
int path_to_pathname(const char *path, char *filepath);
int mkdir_p(const char *pathname);
int create_key_file_name(uint32_t CUID, uint32_t KeySystem, uint32_t KeyType, 
												 uint32_t KeyIndex, uint32_t limit, char *pathname);
int ped_check_file_intergrated(int fd, int *datasize);

int ped_copy_file(const char *src, const char *dst);
int ped_delete_file_with_prefix(char *PrefixName);
int delete_dir(char * dirname);
int memcmp_safe(const void *cs, const void *ct, size_t count);


#endif
