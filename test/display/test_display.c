#include <stdio.h>
#include <stdbool.h>

void display_init() 
{
    printf("Display initialization\n");
}

void display_clear() 
{
    printf("Display cleared\n");
}

void display_print(const char *message) 
{
    printf("Display printed: %s\n", message);
}

void display_hello_world() 
{
    display_init();
    display_clear();
    display_print("Hello, world!");
}

void test_display() 
{
    display_hello_world();
}

int main(void) 
{
    test_display();

    return 0;
}
