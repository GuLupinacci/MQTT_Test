#define LCD_RS  3   // Pino do Raspberry Pi conectado ao pino RS do display LCD
#define LCD_E   0   // Pino do Raspberry Pi conectado ao pino E do display LCD
#define LCD_D4  6   // Pino do Raspberry Pi conectado ao pino D4 do display LCD
#define LCD_D5  1   // Pino do Raspberry Pi conectado ao pino D5 do display LCD
#define LCD_D6  5   // Pino do Raspberry Pi conectado ao pino D6 do display LCD
#define LCD_D7  4   // Pino do Raspberry Pi conectado ao pino D7 do display LCD

// Initialize the LCD display
int lcd_init();

// Clear the LCD display
int lcd_clear();

// Set the cursor position on the LCD display
int lcd_set_cursor(int row, int column);

// Display text on the LCD display
int lcd_display_text(const char *text);

void write_on_display(int display_line, char *display_message);
