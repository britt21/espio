#ifndef _SHA256_H
#define _SHA256_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SHA256_SUM_LEN	32

typedef struct {
	uint32_t total[2];
	uint32_t state[8];
	uint8_t buffer[64];
} sha256_context_t;

#define hash_state sha256_context_t

//void sha256_starts(sha256_context_t * ctx);
//void sha256_update(sha256_context_t * ctx, uint8_t * input, uint32_t length);
//void sha256_finish(sha256_context_t * ctx, uint8_t digest[SHA256_SUM_LEN]);
//int hash256(uint8_t* datain1,uint8_t* datain2,uint32_t datain_len1,uint32_t datain_len2,uint8_t* dataout);

int sha256_init(hash_state * md);
int sha256_process(hash_state * md, const unsigned char *in, unsigned long inlen);
int sha256_done(hash_state * md, unsigned char *out);
//#define VERIFY_DEBUG

#if defined(VERIFY_DEBUG)
  #define verify_debug(format, arg...)			    printk(format, ##arg)
#else
  #define verify_debug(format, arg...)				do {} while(0)
#endif


#define verify_debug_error(format, args...) \
		verify_debug("<%d:%s> \033[1;31m" format "\033[0m", __LINE__, __FUNCTION__, ##args)

#define verify_debug_api_enter(format, args...)		verify_debug("+++ %s(" format ")\n", __FUNCTION__, ##args)
#define verify_debug_api_exit2(format, args...)		verify_debug("--- %s(" format ")\n", __FUNCTION__, ##args)
#define verify_debug_api_exit(msg) 					verify_debug("--- %s()=%s\n", __FUNCTION__, msg)
#define verify_debug_warning(format, args...)		verify_debug("\033[1;31m%s:" format "\033[0m" "\n", __FUNCTION__, ##args)
#define verify_debug_notice(format, args...)		verify_debug("\033[1;32m%s:" format "\033[0m" "\n", __FUNCTION__, ##args)

#ifdef __cplusplus
}
#endif

#endif /* _SHA256_H */
