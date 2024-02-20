#include "lcd_hal.h"
#include <stdio.h>
#include <wiringPi.h>

#define LCD_RS  0  // GPIO pin connected to RS pin of LCD
#define LCD_E   1  // GPIO pin connected to E pin of LCD
#define LCD_D4  2  // GPIO pin connected to D4 pin of LCD
#define LCD_D5  3  // GPIO pin connected to D5 pin of LCD
#define LCD_D6  4  // GPIO pin connected to D6 pin of LCD
#define LCD_D7  5  // GPIO pin connected to D7 pin of LCD

#define LCD_WIDTH 16
#define LCD_HEIGHT 2

void lcd_pulse_enable() {
    digitalWrite(LCD_E, HIGH);
    delayMicroseconds(1); // Ensure pulse width
    digitalWrite(LCD_E, LOW);
    delayMicroseconds(1); // Ensure pulse width
}

void lcd_send_nibble(int value) {
    digitalWrite(LCD_D4, (value >> 0) & 1);
    digitalWrite(LCD_D5, (value >> 1) & 1);
    digitalWrite(LCD_D6, (value >> 2) & 1);
    digitalWrite(LCD_D7, (value >> 3) & 1);
}

void lcd_send_command(int command) {
    digitalWrite(LCD_RS, LOW);
    lcd_send_nibble(command >> 4);
    lcd_pulse_enable();
    lcd_send_nibble(command);
    lcd_pulse_enable();
}

void lcd_send_character(char character) {
    digitalWrite(LCD_RS, HIGH);
    lcd_send_nibble(character >> 4);
    lcd_pulse_enable();
    lcd_send_nibble(character);
    lcd_pulse_enable();
}

int lcd_init() {
    // Initialize wiringPi library
    wiringPiSetup();

    // Set GPIO pins as outputs
    pinMode(LCD_RS, OUTPUT);
    pinMode(LCD_E, OUTPUT);
    pinMode(LCD_D4, OUTPUT);
    pinMode(LCD_D5, OUTPUT);
    pinMode(LCD_D6, OUTPUT);
    pinMode(LCD_D7, OUTPUT);

    // Initialization sequence
    delay(15); // Wait >15ms
    lcd_send_nibble(0x03);
    delay(5); // Wait >4.1ms
    lcd_send_nibble(0x03);
    delayMicroseconds(100); // Wait >100us
    lcd_send_nibble(0x03);
    delay(5); // Wait >4.1ms
    lcd_send_nibble(0x02); // Set 4-bit mode
    delay(1); // Wait >37us
    lcd_send_command(0x28); // Function set: 4-bit, 2 lines, 5x8 font
    delay(1); // Wait >37us
    lcd_send_command(0x08); // Display off
    delay(1); // Wait >37us
    lcd_send_command(0x01); // Clear display
    delay(2); // Wait >1.52ms
    lcd_send_command(0x06); // Entry mode set: Increment cursor, no shift
    delay(1); // Wait >37us
    lcd_send_command(0x0C); // Display on, cursor off, blinking off
    delay(1); // Wait >37us

    return 0;
}

int lcd_clear() {
    lcd_send_command(0x01); // Clear display
    delay(2); // Wait >1.52ms
    return 0;
}

int lcd_set_cursor(int row, int column) {
    int offset = 0x00;
    if (row == 1) {
        offset = 0x40;
    }
    lcd_send_command(0x80 | (column + offset)); // Set DDRAM address
    return 0;
}

int lcd_display_text(const char *text) {
    while (*text) {
        lcd_send_character(*text++);
    }
    return 0;
}
