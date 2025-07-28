// Development of a simple 3D engine inside a terminal
// This engine uses ANSI escape codes to render 3D objects in a terminal window.
// The engine supports basic 3D rendering, including face creation and texture mapping.

// Main engine loop
// This loop will run indefinitely until the user presses the Escape key.
#ifdef _WIN32
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <time.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "console_init.h"


// Cross-platform function to get the current time in milliseconds
unsigned long clear_screen() {
#ifdef _WIN32                                              
    system("cls"); // Clear the terminal screen on Windows
    return 0;                     
#else
    system("clear"); // Clear the terminal screen
    return 0;
#endif
}  
// Cross-platform function to get the current time in milliseconds
unsigned long get_current_time_ms() {
#ifdef _WIN32                                              
    return GetTickCount();                            
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (unsigned long)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#endif
}                                                                                                             // Function to check if a key is pressed
int is_key_pressed() {
#ifdef _WIN32
    printf("\x1b[3H\x1b[33mWINDOWS RUN");
    return GetAsyncKeyState(VK_ESCAPE) & 0x8000;

#else
    struct termios oldt, newt;
    int ch;
    int oldf;

    // Get the terminal settings for stdin
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return ch == 27; // ASCII code for Escape key
    }
    printf("\x1b[3H\x1b[31mLINUX RUN");
    return 0;
#endif
}




// Main engine loop
int main(int argc, char const *argv[])
{   
    clear_screen(); // Clear the terminal screen at the start
    launch(); // Initialize console settings
    unsigned long lastTime = get_current_time_ms();
    int frameCount = 0;
    float fps = 0.0f;
    int render_mode = 0; // 0 = ANSI pattern, 1 = 3D cube

    printf("Press Escape to exit.\n");

    while (1)
    {
        unsigned long currentTime = get_current_time_ms();
        frameCount++;

        // Calculate FPS every second
        if (currentTime - lastTime >= 250) {
            fps = frameCount * 250.0f / (currentTime - lastTime);
            frameCount = 0;
            lastTime = currentTime;
        }

        // Check for exit (Escape key)
        if (is_key_pressed()) {
            break;
        }

        // Display the engine ticks
        printf("\x1B[37m\x1B[2H%.2fEngine Ticks", fps);

            // Corner markers for the console buffer
        printf("\x1B[31m\x1b[0H#\x1b[0;%dH#\x1b[%d;%dH#\x1b[%d;0H#", cmd_buffer_width, cmd_buffer_height, cmd_buffer_width, cmd_buffer_height);
        system("clear");
    }
    return 0;
}