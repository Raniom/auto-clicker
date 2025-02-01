#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define START_KEY VK_F4
#define STOP_KEY VK_F5

void click_mouse() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

int main() {
    float interval = -1;
    char input[20];
    printf(
"\n"
"  /$$$$$$   /$$$$$$  /$$                /$$$$$$ \n"
" /$$__  $$ /$$__  $$| $$               /$$__  $$\n"
"| $$  \\ $$|$$    \\_/| $$              | $$  \\_/\n"
"| $$$$$$$$| $$      | $$       /$$$$$$| $$      \n"
"| $$__  $$| $$      | $$      |______/| $$      \n"
"| $$  | $$| $$    $$| $$              | $$    $$\n"
"| $$  | $$|  $$$$$$/| $$$$$$$$        |  $$$$$$/\n"
"|__/  |__/ \\______/ |________/         \\______/ \n");

    printf("Enter an interval in seconds between each click (or 'none' for no delay) : ");
    fgets(input, sizeof(input), stdin);

    if (strcmp(input, "none\n") != 0) {
        interval = atof(input);
        if (interval <= 0) {
            printf("Please enter a positive number.\n");
            return 0;
        }
    }

    printf("Press F4 to start and F5 to stop.\n");

    while (1) {
        if (GetAsyncKeyState(START_KEY) & 0x8000) {
            printf("Auto-click started !\n");
            while (1) {
                if (GetAsyncKeyState(STOP_KEY) & 0x8000) {
                    printf("Auto-click stopped !\n");
                    break;
                }
                click_mouse();
                if (interval > 0) {
                    Sleep((unsigned int)(interval * 1000));
                } else {
                    Sleep(10);
                }
            }
        }
        Sleep(100);
    }
    return 0;
}