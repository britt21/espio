/**
 * @file    ped_mem.h
 *          
 * @author  Li.Jiang <lijiang2407@163.com>.
 *          
 * @date    2017-05-12
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

#ifndef PED_MEM_H
#define PED_MEM_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef size_t
typedef unsigned int size_t;
#endif


__attribute__((noinline))  int memcmp_safe(const void *cs, const void *ct, size_t count);
__attribute__((noinline))  void *memset_safe(void *m, int c, size_t n);


#ifdef __cplusplus
}
#endif

#endif

