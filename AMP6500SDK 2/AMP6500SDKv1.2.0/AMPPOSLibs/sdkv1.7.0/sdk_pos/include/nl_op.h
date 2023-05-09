/**
 * @file    nl_op.h
 *
 * @brief	export rsa key encrypt api(c language api) to openssl.
 * 
 * @author  wulinhe
 *
 * @date    2017-08-07
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
#ifndef __NL_OP_H
#define __NL_OP_H


#define NETLINK_SCPD	28	/* scpd communition*/
#define PORTID_KERNEL   0

void nl_close(int fd);
int nl_send(int fd, unsigned short nl_id,  void *data, int len);
int nl_send_initiative(int fd, void *data, int len);

int nl_recv_raw(int fd, void *data, int len);
int nl_recv2(int fd, void *hdr, int hlen, void *data, int dlen);
int nl_sk_create(unsigned int portid);
int nl_thread_get_chan(void);
int nl_thread_close_chan(void);
int nl_rpc_call(int sk, const char *func, void *arg, int *arglen);

#endif
