/*
 * thermoclock_WS2812.c
 *
 *  Created on: 12 janv. 2022
 *      Author: Utilisateur
 */

#include "stm32f1xx_hal.h"
#include "stm32f1_adc.h"
#include "systick.h"
#include "WS2812S.h"

#define COLOR_BLUE	0x0000FF
#define COLOR_RED	0x00FF00
#define COLOR_GREEN	0xFF0000
#define COLOR_WHITE	0xFFFFFF
#define COLOR_ORANGE 0x45FF00

static uint16_t temperature;


void Thermoclock_WS2812_Init(void)
{
	//Initialisation du ruban de Leds
	LED_MATRIX_init();

	ADC_init();
	Systick_add_callback_function(DEMO_adc_process_1ms);
}


void Temperature_on_WS2812(void)
{
	uint16_t value;
	int16_t millivolt;

	value = ADC_getValue(1);
	millivolt = (int16_t)((((int32_t)value)*3300)/4096);		//On la convertit en volts
	temperature = ((millivolt - 400))/19.5; 					//Calcul datasheet : conversion en degrés Celsius


	//récupérer valeur obtenue par capteur de température à chaque changement de pallier
	uint32_t pixels[8]; //8 leds à allumer
	//float temperature = 18.6;
	for(uint8_t i=0; i<8; i++){ //boucle pour le nombre de leds à allumer
		if(temperature >30  && temperature <50)
			pixels[i] = COLOR_RED;
		//affichage valeur température

		else if(temperature >=25 && temperature <30)
			pixels[i] = COLOR_ORANGE;
		//affichage valeur température

		else if(temperature >=0xF && temperature <0x19)
			pixels[i] = COLOR_GREEN;
		//affichage valeur température

		else if(temperature >=5 && temperature <15)
			pixels[i] = COLOR_BLUE;
		//affichage valeur température

		else
			pixels[i] = COLOR_WHITE;
			//affichage valeur température
		}
	LED_MATRIX_display(pixels, 8);
	HAL_Delay(100);
}
