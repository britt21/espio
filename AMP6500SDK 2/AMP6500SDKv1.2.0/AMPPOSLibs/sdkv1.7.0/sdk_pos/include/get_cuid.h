#ifndef __GET_UID_CID__
#define __GET_UID_CID__

#ifdef __cplusplus
extern "C" {
#endif

#define POS_VERIFY_RSA_LEN 			256
#define POS_SIGN_LEN 					256
#define SIGN_MARK_1  					"SIG:0001"
#define SIGN_MARK_2  					"SIG:0002"
#define SIGN_V1						1
#define SIGN_V2						2

struct pos_sign_tail {
	/* program/data type[4bytes] */
	uint8_t  sign_src_type;
	uint8_t  uid;
	uint16_t cid;
	uint32_t sign_effe_time;
	uint32_t sign_exp_time;
	uint8_t  app_name[64];
	uint8_t  app_provider[64];
	uint8_t  app_version[4];
	uint8_t  reserve[44];
	uint16_t sign_len;
	uint16_t sign_tail_len;
	uint8_t  sign_mark[8];
};

int get_process_cuid_by_pid(uint32_t *cuid, uint32_t pid);
int check_mf_sign_by_pid(uint32_t *cuid, uint32_t pid);


#ifdef __cplusplus
}
#endif

#endif

