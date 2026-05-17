# cse232-text-editor-g11
A text editor written in C for the Yeditepe University course CSE232

## Project Overview
This project is a simple text editor written in C, built using the `gcc` compiler on a Linux environment. The application manages a custom text buffer in memory using an array-based doubly linked list and utilizes the NCURSES library for dynamic terminal user interface rendering and cursor navigation. It features both manual and automated garbage collection to optimize memory layout.

### Core Requirements & Constraints
* **Line Limit:** The text buffer supports a maximum of 100 lines.
* **Line Width:** Each statement has a maximum length of 40 characters.
* **Display Limit:** The terminal window displays a maximum of 30 lines of text at any time.
* **Automatic Garbage Collection:** Automatically triggers when the text buffer runs out of insertion space or exactly after every 10 insertions/deletions.

---

## Assembly Line Task Distribution (TS0 - TS9)
To ensure a smooth pipeline, this project follows a strict sequential development process.

| Member | Task Sequence (TS) | Assigned Functions / Responsibilities |
| :--- | :--- | :--- |
| **Member 1** | **TS0, TS1, TS2** | Define node struct, initialize globals, implement `edit()` and `save()`. |
| **Member 2** | **TS3, TS4** | Implement `insert()`, `delete()`, `replace()`, and `garbageCollection()`. |
| **Member 3** | **TS5, TS6** | Initialize the NCURSES context in `main()` and implement the visual `print()` function. |
| **Member 4** | **TS7** | Implement coordinate translation math via `cursorLine()` and `cursorChar()`. |
| **Member 5** | **TS8, TS9** | Connect UI commands (E, I, D, R, P, S, G, Q) to functions and build automatic garbage collection triggers. |

---

## Installation & Prerequisites
Before compiling the project, you must install the NCURSES development package on your local Linux machine.

On Debian/Ubuntu-based systems, run:
```bash
sudo apt update && sudo apt install libncurses-dev