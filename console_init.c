#include "console_init.h"

// Saves current console size to avoid infinite scrolling
unsigned int save_console_width = 0;
unsigned int save_console_height = 0;

// Buffer dimensions
unsigned int cmd_buffer_width; 
unsigned int cmd_buffer_height;

#ifdef _WIN32
    #include <windows.h>
    void win_console_init() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);

        cmd_buffer_width  = csbi.dwSize.X;
        cmd_buffer_height = csbi.dwSize.Y;

        // Check if the console buffer size matches the desired dimensions if console is resized
        if (cmd_buffer_width != save_console_width || cmd_buffer_height != save_console_height) {
            // Resize console buffer if necessary
            system("cls"); // Clear the console
        }

        // Save current console size, to avoid infinite scrolling
        save_console_width = cmd_buffer_width;
        save_console_height = cmd_buffer_height;
    }
#else
    #include <sys/ioctl.h> // For ioctl and winsize
    #include <unistd.h>    // For STDOUT_FILENO
    #include <stdio.h>     // For printf
    #include <stdlib.h>    // For system
    void linux_console_init() {
        struct winsize w;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
            perror("ioctl"); // Print error if ioctl fails
            return;
        }

        // Update global variables directly
        cmd_buffer_width = w.ws_col;
        cmd_buffer_height = w.ws_row;

        // Check if the console buffer size matches the desired dimensions if console is resized
        if (cmd_buffer_width != save_console_width || cmd_buffer_height != save_console_height) {
            // Clear the console using ANSI escape codes
            system("clear");
        }

        // Save current console size, to avoid infinite scrolling
        save_console_width = cmd_buffer_width;
        save_console_height = cmd_buffer_height;
    }

#endif





void launch() {
#ifdef _WIN32
    win_console_init();
#else
    linux_console_init();
#endif
}