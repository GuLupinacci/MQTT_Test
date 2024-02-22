#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>
#include "../include/display.h"
#include "../include/mqtt.h"

#define LCD_RS  3   // Pino do Raspberry Pi conectado ao pino RS do display LCD
#define LCD_E   0   // Pino do Raspberry Pi conectado ao pino E do display LCD
#define LCD_D4  6   // Pino do Raspberry Pi conectado ao pino D4 do display LCD
#define LCD_D5  1   // Pino do Raspberry Pi conectado ao pino D5 do display LCD
#define LCD_D6  5   // Pino do Raspberry Pi conectado ao pino D6 do display LCD
#define LCD_D7  4   // Pino do Raspberry Pi conectado ao pino D7 do display LCD

int lcd;

void write_on_display(int value, char *text)
{
        lcdPosition(lcd, 0, value); // Define a posição do cursor
        lcdPuts(lcd, text);
}

int main() {

    wiringPiSetup();

    // Inicializa o display LCD 20x4 em I2C
    lcd = lcdInit(4, 20, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);

    // Verifica se houve erro na inicialização
    if (lcd < 0) {
        fprintf(stderr, "Erro ao inicializar o display LCD\n");
        return 1;
    }
    init_mqtt();
    // Escreve uma mensagem no display


    //delay(2000); // Aguarda 2 segundos

    // Limpa o display
    //lcdClear(lcd);

    // Escreve outra mensagem no display
    //lcdPosition(lcd, 0, 0); // Define a posição do cursor
    //lcdPuts(lcd, "LCD 20x4 com I2C");

    delay(2000); // Aguarda 2 segundos

    return 0;
}
