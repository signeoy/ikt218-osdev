// print in terminal: https://wiki.osdev.org/Printing_To_Screen
// forked from: https://github.com/uiaict/ikt218-osdev/


#include <cstddef>

#include "screen.h"
#include <system.h>

// BASIC DEFINE 
#define VIDEO_BUFFER 0xB8000
#define VIDEO_HEIGHT 80
#define VIDEO_WIDTH 80


// COLORS FOR LETTERS IN TERMINAL
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

// finds length of string
size_t size(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

//volitile char
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

//print in terminal
void screenPrint(const char* data) {

	//VARIABLES
    const uint8_t color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    size_t stringLength = size(data);
    uint16_t *video = (uint16_t*)VIDEO_BUFFER;
    static size_t cursorPos = 0; // Keep track of cursor position

    for (size_t i = 0; i < stringLength; i++) {
        // Handle line breaks
        if (data[i] == '\n') {
            // Move to beginning of next line
            cursorPos = (cursorPos / VIDEO_WIDTH + 1) * VIDEO_WIDTH;
        } else {
            video[cursorPos] = vga_entry(data[i], color);
            cursorPos++;
        }
    }

    // Insert newline after printing whole char
    if (size(data) == stringLength) {
        cursorPos = (cursorPos / VIDEO_WIDTH + 1) * VIDEO_WIDTH;
    }
}


//clear terminal
void screenClear() {

	//VARIABLES
    const uint8_t color = vga_entry_color(VGA_COLOR_GREEN,VGA_COLOR_BLACK);
    uint16_t *video = (uint16_t*)VIDEO_BUFFER;

    for(size_t i = 0; i < VIDEO_HEIGHT*VIDEO_WIDTH; i++)
    {
        video[i] = vga_entry(' ', color);
    }
}

