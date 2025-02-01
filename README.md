# Auto Clicker

![Auto Clicker](https://img.shields.io/badge/AutoClicker-v1.0-blue.svg)

A simple auto-clicker for Windows that simulates mouse clicks at a user-defined frequency.

---

## 🚀 Features

- 🔘 Start with `F4` and stop with `F5`
- ⏳ Custom interval between clicks
- ⚡ "No delay" mode for ultra-fast clicking
- 🖱️ Simulates left mouse clicks

---

## 🛠️ Installation

1. **Compile the program** (Windows only, requires MinGW or Visual Studio)
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

#define START_KEY VK_F4
#define STOP_KEY VK_F5

void click_mouse() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

int main() {
    float interval = -1;
    char input[20];

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
```

---

## 📌 Future Improvements

- ✅ Add right-click option
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
