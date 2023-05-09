#ifndef POS_VERIFY_H
#define POS_VERIFY_H

#ifdef __cplusplus
extern "C" {
#endif

int verify_open(void);
int verify_close(int fd);
int rsa_verify_file(int fd, const char *filename, int sign_separate);
int is_development_version(void);
int pos_no_need_to_verify_thirdparty(int fd, const char *filename);
int pos_is_system_file(int fd, const char *filename);
int pos_is_mf_signed(int fd, const char *filename);
int set_machine_cid(int cuid);
#ifdef __cplusplus
}
#endif

#endif
