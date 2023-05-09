#ifndef COM_NEWPOS_PEDSERVICE_H
#define COM_NEWPOS_PEDSERVICE_H

#include <utils/RefBase.h>
#include "IPedService.h"


namespace android
{
// ---------------------------------------------------------------------------
    class PedService : public BnPedService
    {
    public:
        static int instantiate();

    private:
        // protected by mLock
        mutable Mutex mLock;

        // IBankService interface
        PedService();
        virtual ~PedService();

        // step 1, add method here
        virtual int ped_ped_get_random_nr(unsigned int bytes, void *data);

        virtual int ped_ped_format(void);

        virtual int ped_ped_get_config(PedConfig_t *config);

        virtual int ped_ped_get_full_status(uint64_t *status);

        virtual int ped_ped_get_sensitive_timer(unsigned int SensitiveType);

        virtual int ped_ped_try_and_get_sensitive_timer(unsigned int SensitiveType);

        virtual int ped_ped_set_pin_input_timeout(uint32_t timeout);

        virtual int ped_ped_root_inject_key(KeySystem_t KeySystem,
                                            uint32_t    KeyType,
                                            uint32_t    KeyIndex,
                                            uint32_t    CUID,
                                            uint32_t    KeyLen,
                                            const void *PlaintextKey);

        virtual int ped_ped_inject_key(KeySystem_t KeySystem,
                                       uint32_t    KeyType,
                                       uint32_t    KeyIndex,
                                       uint32_t    KeyLen,
                                       const void *Key);

        virtual int ped_ped_write_key_unified(KeySystem_t KeySystem,
                                              uint32_t    KeyType,
                                              uint32_t    MasterKeyIndex,
                                              uint32_t    DestKeyIndex,
                                              uint32_t    Mode,
                                              uint32_t    KeyLen,
                                              const void *KeyData);

        virtual int ped_ped_clear_user_keys(void);

        virtual int ped_ped_clear_all_keys(void);

        virtual int ped_ped_delete_key_unified(KeySystem_t KeySystem,
                                               uint32_t KeyType,
                                               uint32_t KeyIndex);

        virtual int ped_ped_check_key_unified(KeySystem_t KeySystem,
                                              uint32_t    KeyType,
                                              uint32_t    KeyIndex,
                                              uint32_t    Mode);

        virtual int ped_ped_set_login_limit(uint32_t max_err_cnt,
                                            uint32_t err_delay_time,
                                            uint32_t lock_time);

        virtual int ped_ped_get_login_limit(uint32_t *left_err_cnt, uint32_t *wait_time);

        virtual int ped_ped_input_pwd(int Key, uint32_t *State, uint32_t *PwdLen);

        virtual int ped_ped_verify_pwd(const char *CiphPwd, uint32_t login);

        virtual int ped_ped_get_cipherpwd(char *CiphPwd, uint32_t CiphPwdSize);
#if 0
        virtual int ped_ped_inject_key_by_hand(uint32_t    Type,
                                               uint32_t    KeySystem,
                                               uint32_t    KeyType,
                                               uint32_t    KeyIndex,
                                               uint32_t    CUID,
                                               const void *Ksn,
                                               int         Key,
                                               uint32_t   *State,
                                               uint32_t   *KeyLen);
#endif
        virtual int ped_ped_create_dukpt_key(uint32_t    KeyIndex,
                                             const void *InitKey,
                                             uint32_t    KeyLen,
                                             const void *Ksn);

        virtual int ped_ped_dukpt_renew(uint32_t KeyIndex, void *Ksn);

        virtual int ped_ped_get_dukpt_ksn(uint32_t KeyIndex, void *Ksn);

        virtual int ped_ped_dukpt_encrypt_request(uint32_t    KeyIndex,
                uint32_t    DataLen,
                const void *DataIn,
                void       *DataOut);

        virtual int ped_ped_dukpt_decrypt_response(uint32_t    KeyIndex,
                uint32_t    DataLen,
                const void *DataIn,
                void       *DataOut);

        virtual int ped_ped_dukpt_calc_mac_response(uint32_t    KeyIndex,
                uint32_t    Mode,
                uint32_t    DataLen,
                const void *DataIn,
                void       *MacBlock);

        virtual int ped_ped_dukpt_verify_mac_response(uint32_t    KeyIndex,
                uint32_t    Mode,
                uint32_t    DataLen,
                const void *DataIn,
                const void *MacBlock);

        virtual int ped_ped_get_mac_unified(KeySystem_t KeySystem,
                                            uint32_t    KeyIndex,
                                            uint32_t    Mode,
                                            uint32_t    DataLen,
                                            const void *DataIn,
                                            void       *MacBlock);

        virtual int ped_ped_get_account(KeySystem_t KeySystem,
                                        uint32_t    KeyIndex,
                                        uint32_t    Mode,
                                        uint32_t    DataLen,
                                        const void *DataIn,
                                        void       *DataOut);

        virtual int ped_ped_get_key_kvc(KeySystem_t KeySystem,
                                        uint32_t KeyType,
                                        uint32_t KeyIndex,
                                        uint8_t KVC[4]);

        virtual int ped_ped_des_key_crypto_unified(KeySystem_t KeySystem,
                uint32_t    KeyType,
                uint32_t    KeyIndex,
                uint32_t    Mode,
                uint8_t     IV[8],
                uint32_t    DataLen,
                const void *DataIn,
                void       *DataOut);

        virtual int ped_ped_rsa_export_pub_key(uint32_t KeyIndex, void *PubKey, uint32_t *KeyLen);

        virtual int ped_ped_rsa_private_operation(uint32_t    KeyIndex,
                void       *output,
                uint32_t   *outputLen,
                const void *input,
                uint32_t    inputLen) ;

        virtual int ped_ped_inject_rsa_pub_cert(uint32_t KeyIndex, uint32_t CUID, uint32_t KeyType, const void *input, uint32_t inputLen);

        virtual int ped_ped_get_rsa_pub_cert(uint32_t KeyIndex, uint32_t KeyType, void *output, uint32_t *outputlen);

        virtual int ped_ped_save_cipherpwd(char *user);

        virtual int ped_ped_set_pin_keymap_random(uint32_t value);

        virtual int ped_ped_cancel_pin_input(void);

        virtual int ped_ped_entry_pin_input(void);

        virtual int ped_ped_read_otp_info(OtpSys_t id, void *data, uint32_t *len);

        virtual int ped_ped_write_otp_info(OtpSys_t id, const void *data, uint32_t len);

        virtual int ped_ped_write_key_unified_by_cuid(KeySystem_t KeySystem,
                uint32_t    KeyType,
                uint32_t    CUID,
                uint32_t    MasterKeyIndex,
                uint32_t    DestKeyIndex,
                uint32_t    Mode,
                uint32_t    KeyLen,
                const void *KeyData);

        virtual int ped_ped_check_key_unified_by_cuid(KeySystem_t KeySystem,
                uint32_t    KeyType,
                uint32_t    CUID,
                uint32_t    KeyIndex,
                uint32_t    Mode);

    };
// ---------------------------------------------------------------------------
};
#endif
