/* 
 * File:   application.h
 * Author: omarm
 *
 * Created on March 6, 2023, 2:43 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */
#include "MCAL_Layer/CCP1/hal_ccp1.h"
#include "MCAL_Layer/Timer2/hal_timr2.h"
#include "ECU_Layer/DC_Motor/ecu_dc_motor.h"
#include "ECU_Layer/LM35_TEMP_SENSOR/ecu_temp_sensor.h"
#include "ECU_Layer/LCD/ecu_chr_lcd.h"

/* Section : Macro Declarations */
#define LCD_TEMP_ROW        ROW1           
#define LCD_TEMP_TEXT_COL   1
#define LCD_TEMP_VALUE_COL  13

#define LCD_SPEED_ROW       ROW2
#define LCD_SPEED_TEXT_COL  1
#define LCD_SPEED_VALUE_COL 13

#define ARRAY_LEN           4

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
Std_ReturnType ret;
ccp1_t CCP = {
    .CCP1_InterruptHandler = NULL,
    .ccp1_mode = CCP1_PWM_MODE_SELECTED,
    .ccp1_mode_variant = CCP1_PWM_MODE,
    .PWM_Frequency = 20000,
    .ccp1_pin.port = GPIO_PORTC_INDEX,
    .ccp1_pin.pin = GPIO_PIN2,
    .ccp1_pin.direction = GPIO_DIRECTION_OUTPUT,
    .timer2_postscaler_value = 1,
    .timer2_prescaler_value = 1
};
timer2_t TIMR2 = {
    .timer2_prescaler_value = TIMER1_PRESCALER_DIV_BY_1,
    .timer2_postscaler_value = TIMER2_POSTSCALER_DIV_BY_1,
    .timer2_preload_value = 0
};
dc_motor_t MOTOR = {
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT, .dc_motor_pin[0].port = GPIO_PORTC_INDEX,
    .dc_motor_pin[0].pin = GPIO_PIN0, .dc_motor_pin[0].logic = GPIO_LOW,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT, .dc_motor_pin[1].port = GPIO_PORTC_INDEX,
    .dc_motor_pin[1].pin = GPIO_PIN1, .dc_motor_pin[1].logic = GPIO_LOW,
};
temp_sensor_t mySENSOR = {
    .SENSOR_ADC.acquisition_time = ADC_12_TAD,
    .SENSOR_ADC.adc_channel = ADC_CHANNEL_AN0,
    .SENSOR_ADC.conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    .SENSOR_ADC.result_format = ADC_RESULT_RIGHT,
    .SENSOR_ADC.voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLED
};
chr_lcd_4bit_t myLCD = {
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT, .lcd_rs.logic = GPIO_LOW,
    .lcd_rs.port = GPIO_PORTD_INDEX, .lcd_rs.pin = GPIO_PIN0,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT, .lcd_en.logic = GPIO_LOW,
    .lcd_en.port = GPIO_PORTD_INDEX, .lcd_en.pin = GPIO_PIN1,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[0].port = GPIO_PORTD_INDEX, .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[1].port = GPIO_PORTD_INDEX, .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[2].port = GPIO_PORTD_INDEX, .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT, .lcd_data[3].logic = GPIO_LOW,
    .lcd_data[3].port = GPIO_PORTD_INDEX, .lcd_data[3].pin = GPIO_PIN5,
};

/* Section : Function Declarations */
void application_initialize(void);
void print_default_screen(void);
void print_temp_value(uint8 _value);
void print_speed_value(uint8 _value);
void change_duty_cycle(uint8 _dutyCycle);

#endif	/* APPLICATION_H */

