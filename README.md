# Auto Clicker

![Auto Clicker](https://img.shields.io/badge/AutoClicker-v1.5-blue.svg)

A simple auto-clicker for Windows that simulates mouse clicks at a user-defined frequency.

---

## 🚀 Features

- 🔘 Start with `F4` and stop with `F5`
- ⏳ Custom interval between clicks
- ⚡ "No delay" mode for ultra-fast clicking
- 🖱️ Simulates left or right mouse clicks

---

## 🛠️ Installation

1. **Compile the program** (Windows only, requires MinGW)
   ```sh
   gcc auto-clicker-windows.c -o auto-clicker-windows.exe
   ```
2. **Or copy the .exe**

3. **Run the auto-clicker**
   ```sh
   auto-clicker-windows.exe
   ```

---

## 🖥️ Usage

1. Run the executable
2. Enter an interval in seconds or type `none` for no delay mode
3. Press `F4` to start
4. Press `F5` to stop

---

## 📜 Main Source Code

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define DEFAULT_START_KEY VK_F4
#define DEFAULT_STOP_KEY VK_F5

int START_KEY = DEFAULT_START_KEY;
int STOP_KEY = DEFAULT_STOP_KEY;
float interval = 0.1;
int click_type = MOUSEEVENTF_LEFTDOWN;

void click_mouse() {
    mouse_event(click_type, 0, 0, 0, 0);
    mouse_event(click_type == MOUSEEVENTF_LEFTDOWN ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

int set_key() {
    int key = 0;
    printf("Press the key you want to use: ");
    while (key == 0) {
        for (int i = 0x01; i < 0xFE; i++) {
            if (GetAsyncKeyState(i) & 0x8000) {
                key = i;
                break;
            }
        }
        Sleep(50);
    }
    printf("Key registered!\n\n");
    return key;
}

void menu() {
    int choice;
    char input[20];

    while (1) {
        system("cls");
        printf(
            "\t- [1] Set click interval (current: %.2f sec)\n"
            "\t- [2] Choose click type (current: %s)\n"
            "\t- [-] Choose start key (current: %d)\n"
            "\t- [-] Choose stop key (current: %d)\n"
            "\t- [5] Start auto-clicker\n"
            "\t- [6] Exit\n\n",
            interval, click_type == MOUSEEVENTF_LEFTDOWN ? "Left" : "Right", START_KEY, STOP_KEY
        );

        printf("Select an option: ");
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        switch (choice) {
            case 1:
                printf("Enter interval in seconds (or 'none' for rapid click): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                if (strcmp(input, "none") == 0) {
                    interval = 0;
                    printf("Rapid click mode enabled!\n");
                } else {
                    interval = atof(input);
                    if (interval <= 0) {
                        printf("Invalid interval, defaulting to 0.1 sec.\n");
                        interval = 0.1;
                    }
                }
                break;

            case 2:
                printf("1 = Left Click, 2 = Right Click: ");
                fgets(input, sizeof(input), stdin);
                click_type = (atoi(input) == 2) ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_LEFTDOWN;
                break;

            case 5:
                printf("\033[36m - Press \033[35mF4\033[36m to START, \033[35mF5\033[36m to STOP.\n");
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
                            switch (choice) {,
                                case 6:
                                    printf("Exiting...\n");
                                    return;}
                            Sleep(100);
                        }
                        break;
            case 6:
                printf("Exiting...\n");
                return;

            default:
                printf("Invalid option. Choose between 1,2,5,6.\n");
                break;
        }
        Sleep(1000);
    }
}

int main() {
    system("color 0B");
    menu();
    return 0;
}
```

---

## 📌 Future Improvements

- ✅ Graphical User Interface (GUI) for setting the interval
- ✅ Multi-OS support (Linux, MacOS)

---

## 📄 License

This project is licensed under the **MIT License**. You are free to use and modify it.

---

## 🤝 Contributions

Contributions are welcome! Create an **issue** or **pull request** to propose improvements.

---

## 📧 Contact

📌 Developed by **[Romain](https://github.com/Raniom)**  
📩 Email: **romain.rend@outlook.fr**  
🌍 GitHub: [Raniom](https://github.com/Raniom)
