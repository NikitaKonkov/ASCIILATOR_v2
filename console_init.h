#ifndef CONSOLE_INIT_H
#define CONSOLE_INIT_H

// Saves current console size to avoid infinite scrolling
extern unsigned int save_console_width;
extern unsigned int save_console_height;

// Buffer dimensions
extern unsigned int cmd_buffer_width; 
extern unsigned int cmd_buffer_height;

void console_init();

#endif // CONSOLE_INIT_H