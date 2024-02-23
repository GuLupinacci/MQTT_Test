#include <stdio.h>
#ifdef DISPLAY
#include <wiringPi.h>
#include <lcd.h>
#endif
#include "../include/display.h"
#include "../include/mqtt.h"

#ifdef DISPLAY
int lcd;
void write_on_display(int display_line, char *display_message)
{
        lcdPosition(lcd, 0, display_line); 
        lcdPuts(lcd, display_message);
}
#endif
int main() {

#ifdef DISPLAY
    wiringPiSetup();
    lcd = lcdInit(4, 20, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
    if (lcd < 0) 
    {
        printf( "Erro ao inicializar o display LCD\n");
        return 1;
    }
 #endif   
    init_mqtt();

    return 0;
}
