/**
 * @file    pedkey.c
 *
 * @brief	export rsa key encrypt api(c language api) to openssl.
 * 
 * @author  wulinhe
 *
 * @date    2017-07-07
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
 #ifdef __cplusplus 
extern "C" { 
#endif 

/**
 * @fn          pedkey_rsa_priv_op
 * @brief       rsa private operation
 * @param in    KeyIndex  - index of key
 * @param in	KeyLen    - length of Key in bytes
 * @param in	KeyIn     - ciphertext Key
 * @param in    input     - point buffer to be operated
 * @param in    inputLen  - length of input
 * @param out   output    - point buffer to save operated data
 * @param [in/out]
 *              outputLen 
 *                        - [in]  size of output buffer
 *                        - [out] length of real output data
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */
int pedkey_rsa_priv_op(uint32_t KeyIndex,
					void *output,
					uint32_t *outputLen,
					const void *input,
					uint32_t inputLen);

/**
 * @fn          pedkey_rsa_export_pub_key
 * @brief       export rsa public key
 * @param in    KeyIndex  - index of key
 * @param in	KeyLen    - length of Key in bytes
 * @param in	KeyIn     - ciphertext Key
 * @param out   PubKey    - point buffer to save public key data
 * @param [in/out]
 *              KeyLen 
 *                        - [in]  buffer size to save pubkey
 *                        - [out] length of real output data
 * @return      0    - success
 *              else - failure, use errno to get detail
 * @note        
 */					
int pedkey_rsa_export_pub_key(uint32_t KeyIndex, void *PubKey, uint32_t *KeyLen);

#ifdef __cplusplus 
}
#endif 