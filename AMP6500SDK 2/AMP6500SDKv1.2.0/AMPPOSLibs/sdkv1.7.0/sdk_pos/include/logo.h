/**
 * @file    logo.h
 *          
 * @author  poe.cao <poe.cao@newpostech.com>.
 *          
 * @date    2017-09-21
 *          
 * @brief   LOGO API for write png to splash device
 *          
 * @note    
 *          
 * Modification history
 * ----------------------------------------------------------------------------
 * Date         Version  Author       History
 * ----------------------------------------------------------------------------
 *
 */

#ifndef __LOGO_H__
#define __LOGO_H__


#ifdef __cplusplus 
extern "C" { 
#endif 

/**
 * @fn          write_splash_device
 * @brief       write png to splash
 * @param in    none
 * @param out   none
 * @return      0    - success
 *              -1 - failure
 * @note        none
 *              
 */
int write_splash_device(const char *pngpath);

/**
 * @fn          file_copy_channel
 * @brief       write file to dest
 * @param in    none
 * @param out   none
 * @return      0    - success
 *              -1 - failure
 * @note        none
 *              
 */
int file_copy_channel(const char *src, const char *dest);

#ifdef __cplusplus 
}
#endif 

#endif

