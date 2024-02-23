#include <stdio.h>
#ifdef DISPLAY
#include <wiringPi.h>
#include <lcd.h>
#endif
#include "../include/display.h"
#include "../include/mqtt.h"

#define LCD_RS  3   // Pino do Raspberry Pi conectado ao pino RS do display LCD
#define LCD_E   0   // Pino do Raspberry Pi conectado ao pino E do display LCD
#define LCD_D4  6   // Pino do Raspberry Pi conectado ao pino D4 do display LCD
#define LCD_D5  1   // Pino do Raspberry Pi conectado ao pino D5 do display LCD
#define LCD_D6  5   // Pino do Raspberry Pi conectado ao pino D6 do display LCD
#define LCD_D7  4   // Pino do Raspberry Pi conectado ao pino D7 do display LCD

#ifdef DISPLAY
int lcd;
void write_on_display(int value, char *text)
{
        lcdPosition(lcd, 0, value); 
        lcdPuts(lcd, text);
}
#endif
int main() {

#ifdef DISPLAY
    wiringPiSetup()
    lcd = lcdInit(4, 20, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0)
    if (lcd < 0) 
    {
        printf(stderr, "Erro ao inicializar o display LCD\n");
        return 1;
    }
 #endif   
    init_mqtt();

    return 0;
}
