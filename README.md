# Auto Clicker

![Auto Clicker](https://img.shields.io/badge/AutoClicker-v1.6-blue.svg) ![Licence](https://img.shields.io/github/license/Raniom/auto-clicker)![Dernière MAJ](https://img.shields.io/github/last-commit/Raniom/auto-clicker)![Langage Principal](https://img.shields.io/github/languages/top/Raniom/auto-clicker)![Nombre de Langages](https://img.shields.io/github/languages/count/Raniom/auto-clicker)![Repo Size](https://img.shields.io/github/repo-size/Raniom/auto-clicker)

A simple auto-clicker for Windows that simulates mouse clicks at a user-defined frequency.

---

## 🚀 Features

- 🔘 Custom Key for start and stop (`S`)
- ⏳ Custom interval between clicks (`0.5`)
- ⚡ "No delay" mode for ultra-fast clicking (`0`)
- 🖱️ Simulates left, right and middle mouse clicks

---

## 🛠️ Installation

1. **Compile the program** (Windows only, requires MinGW)

```windres resources.rc -O coff -o resources.o

```

```gcc -o AutoClicker.exe main.c resources.o -mwindows

```

2. **Or copy the .exe**

---

## 🖥️ Usage

1. Run the executable
2. Enter an interval in seconds or type `0` for no delay mode
3. Press `S` to start and stop or set key

---

## 📌 Future Improvements

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
