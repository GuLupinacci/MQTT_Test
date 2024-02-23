
// Initialize the LCD display
int lcd_init();

// Clear the LCD display
int lcd_clear();

// Set the cursor position on the LCD display
int lcd_set_cursor(int row, int column);

// Display text on the LCD display
int lcd_display_text(const char *text);

void write_on_display(int display_line, char *display_message);
