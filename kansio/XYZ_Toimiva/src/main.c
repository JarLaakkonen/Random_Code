/*
 * Copyright (c) 2020 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/logging/log.h>
#include <dk_buttons_and_leds.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include "adc.h"
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

#include "confusion.h"
//thread varten
#define STACKSIZE 1024
#define PRIORITY 7

// ledit käyttöön
#define USER_LED1         	 	DK_LED1
#define USER_LED2          		DK_LED2
#define USER_LED3               DK_LED3
#define USER_LED4               DK_LED4
// buttonit käyttöön

#define USER_BUTTON_1           DK_BTN1_MSK
#define USER_BUTTON_2           DK_BTN2_MSK
#define USER_BUTTON_3           DK_BTN3_MSK
#define USER_BUTTON_4           DK_BTN4_MSK

#define DEBUG 0  // 0 = changes direction when button 3 is pressed
                 // 1 = fake 100 measurements done to each 6 directions when 3 pressed.
static int direction = 0;	// 0 = x direction high
							// 1 = x directon low	
							// 2 = y direction high
							// 3 = y direction low
							// 4 = z direction high
							// 5 = z direction low
						
volatile uint_fast8_t Position= 0;			 
volatile uint_fast8_t LastPosition;
LOG_MODULE_REGISTER(MAIN, LOG_LEVEL_INF);

void Sensor_Val_print(){
	while(1){
	struct Measurement m = readADCValue();
		Position=MinValCalc(m.x , m.y , m.z);
		if (Position!=LastPosition){
		printk("Asento on =%d ja X=%d Y=%d Z=%d \n", Position , m.x, m.y , m.z);
		LastPosition=Position;
		k_sleep(K_MSEC(50));
		}

	 k_sleep(K_MSEC(100));
	 
	 }
	}
// buttoni handleri!
static void button_changed(uint32_t button_state, uint32_t has_changed){
	// Debugausta varten
	//printk("button_state = %d\n",button_state);
	//printk("has_changed = %d\n",has_changed);


	if ((has_changed & USER_BUTTON_1) && (button_state & USER_BUTTON_1)) {
		
		printk("Button 1 down, printing current Confusion Matrix\n");
		printConfusionMatrix();
		struct Measurement m = readADCValue();
		printk("X = %d\n",m.x);
		printk("Y= %d\n",m.y);
		printk("Z= %d\n",m.z);
		k_sleep(K_MSEC(1000));
		
		
	}

	if ((has_changed & USER_BUTTON_2) && (button_state & USER_BUTTON_2)) 
	{
		printk("Button 2 down, resetting confusion matrix\n");
		resetConfusionMatrix();
		printConfusionMatrix();
	}		
	
	if ((has_changed & USER_BUTTON_3) && (button_state & USER_BUTTON_3)) 
	{
		printk("Button 3 down, making fake 100 meas or one real meas depending on DEBUG state\n");
		// vaihda Debug arvoa jos haluat käyttää Elsen jälkeisiä komentoja
		#if DEBUG
		direction = -1;
		randomdata();
		printConfusionMatrix();
		#else
        direction = (direction +1)%6;
		switch (direction)
		{
		case 0:
			printk("Direction is now set x = high\n");
			break;
		case 1:
			printk("Direction is now set x = low\n");
			break;
		case 2:
			printk("Direction is now set y = high\n");
			break;
		case 3:
			printk("Direction is now set y = low\n");
			break;
		case 4:
			printk("Direction is now set z = high\n");
			break;
		case 5:
			printk("Direction is now set z = low\n");
			break;
		
		default:
		    printk("Wrong direction set!!!\n");
			break;
		}

		struct Measurement m = readADCValue();
		printk("x = %d,  y = %d,  z = %d\n",m.x,m.y,m.z);
		#endif
	}		
		// perus button 4
	if ((has_changed & USER_BUTTON_4) && (button_state & USER_BUTTON_4)) 
	{
		printk("button 4 down, one meas and classification with current direction =%d\n",direction);
		if ( direction ==-1){
		CaclOneAndUpdConfMatrix(direction);	
		}
		else {
		printk("tehdään 20 arvoa ");
		for (int i=0;i<20;i++){	
		struct Measurement m = readADCValue();
		DatHandler(m.x , m.y , m.z);
		CaclOneAndUpdConfMatrix(direction);
		}
		}
		printConfusionMatrix();
	}		
}

// ite maini
void main(void)
{
	int err;
	err = dk_leds_init();
	if (err) {
		LOG_ERR("LEDs init failed (err %d)\n", err);
		return;
	}

	err = dk_buttons_init(button_changed);
	if (err) {
		printk("Cannot init buttons (err: %d)\n", err);
		return;
	}
	
	
	if(initializeADC() != 0)
	{
	printk("ADC initialization failed!");
	return;
	}
// välkyttää valoja vain!
	while (1) 
	{
		//struct Measurement m = readADCValue();
		//printk("x = %d,  y = %d,  z = %d\n",m.x,m.y,m.z);
		
		k_sleep(K_MSEC(1000));
		
		dk_set_led_on(USER_LED1);
		dk_set_led_on(USER_LED2);
		dk_set_led_on(USER_LED3);
		dk_set_led_on(USER_LED4);
		 
		k_sleep(K_MSEC(1000));
		
		dk_set_led_off(USER_LED1);
		dk_set_led_off(USER_LED2);
		dk_set_led_off(USER_LED3);
		dk_set_led_off(USER_LED4);


	}
}
K_THREAD_DEFINE(Sensor_val_Check, STACKSIZE, Sensor_Val_print, NULL, NULL, NULL, PRIORITY, 0, 0);

