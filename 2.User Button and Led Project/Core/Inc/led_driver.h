/*
 * led_driver.h
 *
 *  Created on: Jul 8, 2022
 *      Author: anilk
 */

#ifndef INC_LED_DRIVER_H_
#define INC_LED_DRIVER_H_

void user_led_init(void);
void user_led_toggle(void);
void user_led_set(void);
void user_led_reset(void);
void user_button_init(void);
int user_button_state(void);

#endif /* INC_LED_DRIVER_H_ */
