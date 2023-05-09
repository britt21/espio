/**
 * @file    ped_inner.h
 *
 * @author  Li.Hua <lihua_338@163.com>.
 *
 * @date    2016-02-27
 *
 * @brief
 *
 * @note
 *
 * Modification history
 * ----------------------------------------------------------------------------
 * Date         Version  Author       History
 * ----------------------------------------------------------------------------
 *
 */

#ifndef PED_COMMON_H
#define PED_COMMON_H

#include <stdint.h>

#ifdef __cplusplus 
extern "C" { 
#endif 

#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, "Libped", __VA_ARGS__)

#define PED_DEBUG
#if defined(PED_DEBUG)
#define ped_debug LOGD
void hexdump(const void *data, uint32_t len);
#else
#define ped_debug(format, args...)	do {} while (0)
#define hexdump(data, len)  do { } while (0)
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
    MS_AES,                 /* 11: AES */
    FIXED_AES,				/* 12: FIXED_AES */
    KS_MAX,					/* END */
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
#define KEY_TYPE_SM2PRI			0x0D	// SM2 Private KEY
#define KEY_TYPE_RSAPRIK        0x0E    // RSA PRIVATE KEY
#define KEY_TYPE_ANSK           0x0F    // ANS SM4 KEY

#define KEY_TYPE_RSA_CA_CERT      0x10
#define KEY_TYPE_RSA_CLIENT_CERT  0x11
#define KEY_TYPE_RSA_PIN        0x12
#define KEY_TYPE_RSA_PIN_CERT   0x13
#ifdef __cplusplus 
}
#endif 
#endif

