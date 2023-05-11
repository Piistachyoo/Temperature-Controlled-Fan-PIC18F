/* 
 * File:   application.c
 * Author: Omar Yamany
 *
 * Created on March 6, 2023, 2:10 AM
 */

#include "application.h"

int main() {
    uint8 sensor_reading; // Tempreature Value
    application_initialize(); // Initialize function
    CCP1_PWM1_Start(); // Start PWM
    dc_motor_move_right(&MOTOR); // Set motor direction
    print_default_screen();
	while(1){
        TEMP_SENSOR_GET_READING(&mySENSOR, &sensor_reading); // Blocking function
        print_temp_value(sensor_reading);
        if(sensor_reading < 70){
            change_duty_cycle(0);
        }
        else if((70 <= sensor_reading) && (sensor_reading <= 80)){
            change_duty_cycle(25);
        }
        else if((80 < sensor_reading) && (sensor_reading <= 93)){
            change_duty_cycle(50);
        }
        else if(93 < sensor_reading){
            change_duty_cycle(100);
        }
        __delay_ms(100);
    }

    return (EXIT_SUCCESS);
}

void change_duty_cycle(uint8 _dutyCycle){
    CCP1_PWM1_Set_Duty(_dutyCycle);
    print_speed_value(_dutyCycle);
}

void print_temp_value(uint8 _value){
    uint8 local_string[ARRAY_LEN];
    convert_uint8_to_string(_value, local_string, ARRAY_LEN);
    lcd_4bit_send_string_pos(&myLCD, LCD_TEMP_ROW, LCD_TEMP_VALUE_COL, (uint8*)"    ");
    lcd_4bit_send_string_pos(&myLCD, LCD_TEMP_ROW, LCD_TEMP_VALUE_COL, local_string);
    lcd_4bit_send_char_data(&myLCD, 'C');
}

void print_speed_value(uint8 _value){
    uint8 local_string[ARRAY_LEN];
    convert_uint8_to_string(_value, local_string, ARRAY_LEN);
    lcd_4bit_send_string_pos(&myLCD, LCD_SPEED_ROW, LCD_SPEED_VALUE_COL, (uint8*)"    ");
    lcd_4bit_send_string_pos(&myLCD, LCD_SPEED_ROW, LCD_SPEED_VALUE_COL, local_string);
    lcd_4bit_send_char_data(&myLCD, '%');
}

void print_default_screen(void){
    lcd_4bit_send_string_pos(&myLCD, LCD_TEMP_ROW, LCD_TEMP_TEXT_COL, (uint8*)"Tempreature:");
    lcd_4bit_send_string_pos(&myLCD, LCD_SPEED_ROW, LCD_SPEED_TEXT_COL, (uint8*)"Motor Speed:");
}

void application_initialize(){
    dc_motor_initialize(&MOTOR);
    CCP1_Init(&CCP);
    Timer2_Init(&TIMR2);
    lcd_4bit_initialize(&myLCD);
    TEMP_SENSOR_INIT(&mySENSOR);
}


