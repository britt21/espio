#ifndef LINUX_LED_H
#define LINUX_LED_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define LED_CARD				"card"
#define LED_PEN					"pen"
#define LED_KEY_BL				"key_bl"


#define LED_BRIGHTNESS_MIN		0
#define LED_BRIGHTNESS_MAX		255

int led_set_brightness(const char *led_name, uint32_t brightness);

int led_get_brightness(const char *led_name, uint32_t *brightness);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* end for LINUX_LED_H */