/**
 * @file    rpc_parameter.h
 *          
 * @author  Li.Hua <lihua_338@163.com>.
 *          
 * @date    2017-02-24
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

#ifndef __RPC_PARAMETER_H__
#define __RPC_PARAMETER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t    nr;
    struct {
        uint32_t        L;
        const uint8_t   *V;
    } p[16];
} rpc_param_t;


int parameters_decode(uint32_t len, const void *data, rpc_param_t *param);
int parameters_get_value(uint32_t which, const rpc_param_t *param, void *output, uint32_t maxlen);
int parameters_get_addr(uint32_t which, const rpc_param_t *param, void *output);
void parameters_add(uint8_t *prarm_buf, int *param_len, const void *ptr, uint32_t size);


#ifdef __cplusplus
}
#endif

#endif /* __RPC_PARAMETER_H__ */

