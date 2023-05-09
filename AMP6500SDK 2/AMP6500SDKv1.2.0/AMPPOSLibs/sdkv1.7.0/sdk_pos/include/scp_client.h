
#ifndef _SCP_CLIENT_H_
#define _SCP_CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define UNIX_IPC_SERVER_FILE         	"/dev/scpd_unix_server"
#define UNIX_MAX_IPC_CONN            	256
#define MAX_CLIENT_DATA_SIZE       		1024
#define MAX_CLIENT_API_NAME				58 /* See struct scp_client_head */

#define DEBUG_LIB(fmt, args...) if (1) \
    fprintf(stderr, "libscp: %s:%d - "fmt"\n", __FUNCTION__, __LINE__, ##args)


enum SCP_CLIENT_MSG {
	SCP_REQUEST = 1,
	SCP_REPLY,
};


#define SCP_CLIENT_FLAG_PRIOR		0x1
#define SCP_CLIENT_FLAG_CUID		0x2
#define SCP_CLIENT_FLAG_ERROR		0x4


/* 64-Bytes in total,  */
struct scp_client_head {
	uint16_t	msg_type;
	uint16_t	sndid; /* non-zero if it is a request */
	uint16_t	flags;	/* SCP_CLIENT_FLAG_xxx */
	uint8_t     apiname[MAX_CLIENT_API_NAME];
} __attribute__((packed));


enum SCP_ERR_RESULT {
	SCP_ERR = -1,
	SCP_DISCONNECTED = -2,
	SCP_INVALID_ARG = -3,
	SCP_CONNECT_FAIL = -4,
	SCP_BUFFER_TOO_SHORT = -5,
};

int scp_open(const char *username);
int scp_send(int sk, const void *buf, int len);
int scp_send2(int sk, void *first_buf, int first_len, 
				void *second_buf, int second_len);
int scp_recv(int sk, void *ubuf, int len);
int scp_recv2(int sk, void *hdr, int hlen, void *data, int dlen);
void scp_close(int sk);
int scp_is_alive(int sk);

int sp_rpc_ped(int sk,const char *func,void *arg,int *arglen);
int sp_rpc_sys(int sk,const char *func,void *arg,int *arglen);

/* thread local channel */
int scp_thread_get_chan(void);
int scp_thread_close_chan(void);


/* sp file operation */
int sp_file_open(const char *name, int flags, int mode);
int sp_file_read(int fp, char *buf, int len);
int sp_file_write(int fp, const char *buf, int len);
int sp_file_ioctl(int fp, int cmd, void *arg, int arglen);
int sp_file_ioctl2(int fp, int cmd, void *arg, int *arglen);
int sp_file_ioctl_block(int fp, int cmd, void *arg, int arglen);
int sp_file_close(int fp);
int sp_file_ioctl_block_upper(int fp, int cmd, void *arg, int arglen);
int sp_file_ioctl_block_lower(int fp, void *arg, int arglen, int timeout);
int sp_file_lseek(int fp, int offset, int whence);

#ifdef __cplusplus
}
#endif

#endif /* _SCP_CLIENT_H_ */

