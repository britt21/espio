#ifndef COM_NEWPOS_IPEDSERVICE_H
#define COM_NEWPOS_IPEDSERVICE_H

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <android/log.h>

#include "ped.h"
#if 0
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, "PedService", __VA_ARGS__)

#define PED_DEBUG
#if defined(PED_DEBUG)
//#define ped_debug(format, args...) printf(format, ##args)
#define ped_debug LOGD
void pedhexdump(const void *data, uint32_t len);
#else
#define ped_debug(format, args...)  do {} while (0)
#define pedhexdump(data, len)  do { } while (0)
#endif
#else
#if defined(PED_DEBUG)
void pedhexdump(const void *data, uint32_t len);
#else
#define pedhexdump(data, len)  do { } while (0)
#endif

#endif



namespace android
{
    enum {
        // step 1. define marco here
        SVC_PED_RANDOM = IBinder::FIRST_CALL_TRANSACTION,
        SVC_PED_FORMAT,
        SVC_PED_GETCONFIG,
        SVC_PED_GET_FULL_STATUS,
        SVC_PED_GET_SENSITIVE_TIMER,
        SVC_PED_TRY_AND_GET_SENSITIVE_TIMER,
        SVC_PED_SET_PIN_INPUT_TIME,
        SVC_PED_ROOT_INJECT_KEY,
        SVC_PED_INJECT_KEY,
        SVC_PED_WRITE_KEY_UNIFIED,
        SVC_PED_CLEAR_USER_KEYS,
        SVC_PED_CLEAR_ALL_KEYS,
        SVC_PED_DELETE_KEY_UNIFIED,
        SVC_PED_CHECK_KEY_UNIFIED,
        SVC_PED_SET_LOGIN_LIMIT,
        SVC_PED_GET_LOGIN_LIMIT,
        SVC_PED_INPUT_PWD,
        SVC_PED_VERIFY_PWD,
        SVC_PED_GET_CIPHERPWD,
        SVC_PED_INJECT_KEY_BY_HAND,
        SVC_PED_CREATE_DUKPT_KEY,
        SVC_PED_DUKPT_RENEW,
        SVC_PED_GET_DUKPT_KSN,
        SVC_PED_DUKPT_ENCRYPT_REQUEST,
        SVC_PED_DUKPT_DECRYPT_RESPONSE,
        SVC_PED_DUKPT_CALC_MAC_RESPONSE,
        SVC_PED_DUKPT_VERIFY_MAC_RESPONSE,
        SVC_PED_GET_MAC_UNIFIED,
        SVC_PED_GET_ACCOUNT,
        SVC_PED_GET_KVC,
        SVC_PED_DES_KEY_CRYPTO_UNIFIED,
        SVC_PED_RSA_EXPORT_PUB_KEY,
        SVC_PED_RSA_PRIVATE_OPERATION,
        SVC_PED_INJECT_RSA_PUB_CERT,
        SVC_PED_GET_RSA_PUB_CERT,
        SVC_PED_SAVE_CIPHERPWD,
        SVC_PED_SET_PIN_KEYMAP_RANDOM,
        SVC_PED_CANCEL_PIN_INPUT,
        SVC_PED_ENTRY_PIN_INPUT,
        SVC_PED_READ_OTP_INFO,
        SVC_PED_WRITE_OTP_INFO,
        SVC_PED_WRITE_KEY_BY_CUID,
        SVC_PED_CHECK_KEY_BY_CUID,

    };

    class IPedService : public IInterface
    {
    public:
        DECLARE_META_INTERFACE(PedService); // declare macro
        // step 2. add virtual method here
        virtual int ped_ped_get_random_nr(unsigned int bytes, void *data) = 0;
        virtual int ped_ped_format(void) = 0;
        virtual int ped_ped_get_config(PedConfig_t *config) = 0;
        virtual int ped_ped_get_full_status(uint64_t *status) = 0;
        virtual int ped_ped_get_sensitive_timer(unsigned int SensitiveType) = 0;
        virtual int ped_ped_try_and_get_sensitive_timer(unsigned int SensitiveType) = 0;
        virtual int ped_ped_set_pin_input_timeout(uint32_t timeout) = 0;
        virtual int ped_ped_root_inject_key(KeySystem_t KeySystem,
                                            uint32_t    KeyType,
                                            uint32_t    KeyIndex,
                                            uint32_t    CUID,
                                            uint32_t    KeyLen,
                                            const void *PlaintextKey) = 0;
        virtual int ped_ped_inject_key(KeySystem_t KeySystem,
                                       uint32_t    KeyType,
                                       uint32_t    KeyIndex,
                                       uint32_t    KeyLen,
                                       const void *Key) = 0;
        virtual int ped_ped_write_key_unified(KeySystem_t KeySystem,
                                              uint32_t    KeyType,
                                              uint32_t    MasterKeyIndex,
                                              uint32_t    DestKeyIndex,
                                              uint32_t    Mode,
                                              uint32_t    KeyLen,
                                              const void *KeyData) = 0;
        virtual int ped_ped_clear_user_keys(void) = 0;
        virtual int ped_ped_clear_all_keys(void) = 0;
        virtual int ped_ped_delete_key_unified(KeySystem_t KeySystem,
                                               uint32_t KeyType,
                                               uint32_t KeyIndex) = 0;
        virtual int ped_ped_check_key_unified(KeySystem_t KeySystem,
                                              uint32_t    KeyType,
                                              uint32_t    KeyIndex,
                                              uint32_t    Mode) = 0;

        virtual int ped_ped_set_login_limit(uint32_t max_err_cnt,
                                            uint32_t err_delay_time,
                                            uint32_t lock_time) = 0;
        virtual int ped_ped_get_login_limit(uint32_t *left_err_cnt, uint32_t *wait_time) = 0;
        virtual int ped_ped_input_pwd(int Key, uint32_t *State, uint32_t *PwdLen) = 0;
        virtual int ped_ped_verify_pwd(const char *CiphPwd, uint32_t login) = 0;
        virtual int ped_ped_get_cipherpwd(char *CiphPwd, uint32_t CiphPwdSize) = 0;
#if 0
        virtual int ped_ped_inject_key_by_hand(uint32_t    Type,
                                               uint32_t    KeySystem,
                                               uint32_t    KeyType,
                                               uint32_t    KeyIndex,
                                               uint32_t    CUID,
                                               const void *Ksn,
                                               int         Key,
                                               uint32_t   *State,
                                               uint32_t   *KeyLen) = 0;
#endif
        virtual int ped_ped_create_dukpt_key(uint32_t    KeyIndex,
                                             const void *InitKey,
                                             uint32_t    KeyLen,
                                             const void *Ksn) = 0;

        virtual int ped_ped_dukpt_renew(uint32_t KeyIndex, void *Ksn) = 0;
        virtual int ped_ped_get_dukpt_ksn(uint32_t KeyIndex, void *Ksn) = 0;
        virtual int ped_ped_dukpt_encrypt_request(uint32_t    KeyIndex,
                uint32_t    DataLen,
                const void *DataIn,
                void       *DataOut) = 0;
        virtual int ped_ped_dukpt_decrypt_response(uint32_t    KeyIndex,
                uint32_t    DataLen,
                const void *DataIn,
                void       *DataOut) = 0;

        virtual int ped_ped_dukpt_calc_mac_response(uint32_t    KeyIndex,
                uint32_t    Mode,
                uint32_t    DataLen,
                const void *DataIn,
                void       *MacBlock) = 0;

        virtual int ped_ped_dukpt_verify_mac_response(uint32_t    KeyIndex,
                uint32_t    Mode,
                uint32_t    DataLen,
                const void *DataIn,
                const void *MacBlock) = 0;

        virtual int ped_ped_get_mac_unified(KeySystem_t KeySystem,
                                            uint32_t    KeyIndex,
                                            uint32_t    Mode,
                                            uint32_t    DataLen,
                                            const void *DataIn,
                                            void       *MacBlock) = 0;

        virtual int ped_ped_get_account(KeySystem_t KeySystem,
                                        uint32_t    KeyIndex,
                                        uint32_t    Mode,
                                        uint32_t    DataLen,
                                        const void *DataIn,
                                        void       *DataOut) = 0;

        virtual int ped_ped_get_key_kvc(KeySystem_t KeySystem, uint32_t KeyType, uint32_t KeyIndex, uint8_t KVC[4]) = 0;

        virtual int ped_ped_des_key_crypto_unified(KeySystem_t KeySystem,
                uint32_t    KeyType,
                uint32_t    KeyIndex,
                uint32_t    Mode,
                uint8_t     IV[8],
                uint32_t    DataLen,
                const void *DataIn,
                void       *DataOut) = 0;

        virtual int ped_ped_rsa_export_pub_key(uint32_t KeyIndex, void *PubKey, uint32_t *KeyLen) = 0;

        virtual int ped_ped_rsa_private_operation(uint32_t    KeyIndex,
                void       *output,
                uint32_t   *outputLen,
                const void *input,
                uint32_t    inputLen) = 0;

        virtual int ped_ped_inject_rsa_pub_cert(uint32_t KeyIndex, uint32_t CUID, uint32_t KeyType, const void *input, uint32_t inputLen) = 0;

        virtual int ped_ped_get_rsa_pub_cert(uint32_t KeyIndex, uint32_t KeyType, void *output, uint32_t *outputlen) = 0;
        virtual int ped_ped_save_cipherpwd(char *user) = 0;
        virtual int ped_ped_set_pin_keymap_random(uint32_t value) = 0;
        virtual int ped_ped_cancel_pin_input(void) = 0;
        virtual int ped_ped_entry_pin_input(void) = 0;

        virtual int ped_ped_read_otp_info(OtpSys_t id, void *data, uint32_t *len) = 0;

        virtual int ped_ped_write_otp_info(OtpSys_t id, const void *data, uint32_t len) = 0;

        virtual int ped_ped_write_key_unified_by_cuid(KeySystem_t KeySystem,
                uint32_t    KeyType,
                uint32_t    CUID,
                uint32_t    MasterKeyIndex,
                uint32_t    DestKeyIndex,
                uint32_t    Mode,
                uint32_t    KeyLen,
                const void *KeyData) = 0;

        virtual int ped_ped_check_key_unified_by_cuid(KeySystem_t KeySystem,
                uint32_t    KeyType,
                uint32_t    CUID,
                uint32_t    KeyIndex,
                uint32_t    Mode) = 0;

    };

    class BnPedService : public BnInterface<IPedService>
    {
    public:
        virtual status_t    onTransact(uint32_t code,
                                       const Parcel &data,
                                       Parcel *reply,
                                       uint32_t flags = 0);
    };
} ;// namespace android
#endif
