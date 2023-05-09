
#ifndef _KEY_MANAGE_H_
#define _KEY_MANAGE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int ped_save_encrypt_key(uint32_t    CUID,
                         uint32_t    KeySystem,
                         uint32_t    KeyType,
                         uint32_t    KeyIndex,
                         const void *EncryptKey,
                         uint32_t    KeyLen);


int ped_load_encrypt_key(uint32_t CUID,
                         uint32_t KeySystem,
                         uint32_t KeyType,
                         uint32_t KeyIndex,
                         void     *EncryptKey,
                         uint32_t *KeyLen);

int ped_clear_user_keys(uint32_t CUID);

int ped_clear_all_keys(void);

int ped_delete_key_unified(uint32_t CUID, uint32_t KeySystem, uint32_t KeyType, uint32_t KeyIndex);

int ped_check_unique_ciphertext_key(uint32_t CUID, uint32_t KeySystem, void *EncryptKey, uint32_t KeyLen);


#ifdef __cplusplus
}
#endif
#endif

