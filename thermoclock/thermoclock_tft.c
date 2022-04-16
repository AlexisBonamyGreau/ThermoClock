/*
 * thermoclock_tft.c
 *
 *  Created on: 11 janv. 2022
 *      Author: Eurydice BOURIGAULT & Alexis BONAMY
 */


#include "tft_ili9341/stm32f1_ili9341.h"
#include "stm32f1_rtc.h"
#include "stm32f1xx_hal.h"


const char * weekday_str[7] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendre Eddy", "Samedi"};

void Thermoclock_TFT_Init(void){
	//Initialisation de l'écran TFT
	ILI9341_Init();
	ILI9341_DrawFilledRectangle(0, 0, 300, 20, ILI9341_COLOR_BLUE);
	ILI9341_DrawFilledRectangle(0, 100, 300, 120, ILI9341_COLOR_RED);

	//Initialisation de l'horloge RTC
	RTC_init(FALSE);
	//RTC_set_time_acceleration();
	RTC_TimeTypeDef time = {14, 40, 00};
	RTC_DateTypeDef date = {RTC_WEEKDAY_TUESDAY, RTC_MONTH_JANUARY, 11, 22};
	RTC_set_time_and_date(&time, &date);


}


void Time_on_TFT(void){
	static uint8_t save = -1;

	RTC_TimeTypeDef time;
	RTC_get_time(&time);

	uint8_t hour[2];
	uint8_t minutes[2];

	uint8_t time_tft[5] = "";
	if(time.Hours<10)
		strcat(time_tft, "0");
	strcat(time_tft, itoa(time.Hours,hour,10));
	strcat(time_tft, ":");
	if(time.Minutes<10)
		strcat(time_tft, "0");
	strcat(time_tft, itoa(time.Minutes,minutes,10));

	if (save != time.Minutes){
		//ILI9341_Fill(ILI9341_COLOR_WHITE);
		ILI9341_Puts(10,75, time_tft, &Font_11x18, ILI9341_COLOR_GRAY, ILI9341_COLOR_WHITE);
	}

	save = time.Minutes;
}


//Affichage de l'heure sur l'écran TFT
void Date_on_TFT(void){
	static uint8_t save = -1;

	RTC_DateTypeDef date;
	RTC_get_date(&date);

	uint8_t day[2];
	uint8_t month[2];
	uint8_t	year[4];

	uint8_t date_tft[10] = "";
	if(date.Date<10)
		strcat(date_tft, "0");
	strcat(date_tft, itoa(date.Date, day, 10));
	strcat(date_tft, "/");
	if(date.Month<10)
		strcat(date_tft, "0");
	strcat(date_tft, itoa(date.Month, month, 10));
	strcat(date_tft, "/20");
	if(date.Year<10)
		strcat(date_tft, "0");
	strcat(date_tft, itoa(date.Year, year, 10));

	if (save != date.Date)
	{
		ILI9341_Puts(10,50, date_tft, &Font_11x18, ILI9341_COLOR_GRAY, ILI9341_COLOR_WHITE);
		ILI9341_Puts(10,25, weekday_str[date.WeekDay], &Font_11x18, ILI9341_COLOR_GRAY, ILI9341_COLOR_WHITE);
	}

	save = date.Date;
}

