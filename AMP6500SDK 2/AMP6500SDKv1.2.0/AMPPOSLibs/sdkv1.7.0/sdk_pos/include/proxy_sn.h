/**
 * @file    proxy_sn.h
 *
 * @author  Brian.Yang <brian.yang@newpostech.com>.
 *
 * @date    2016-08-13
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
#ifndef __PROXY_SN_H__
#define __PROXY_SN_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AP_FW_ID = 0,
    SP_FW_ID,
    SP_FW_ID_CIPHER,
    SP_VENDOR_FW_ID,
} FirmwareId_t;

int terminal_set_hw_config(const char *key, const char *value);
int terminal_get_hw_config(const char *key, uint8_t *buff, uint32_t buff_len, uint32_t *out_len);
int sys_get_sp_version(char *version, int len);
int get_hardware_version(char *version, int len);
int set_sp_time(int second);
int get_firmware_id(FirmwareId_t type, char *buf, uint32_t buf_len);
int get_random_for_firmwareid(uint8_t random[8]);
int read_otp_fw_flag(void *data, uint32_t *len);
int write_otp_fw_flag(const void *data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* __PROXY_SN_H__ */