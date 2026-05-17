## Project Overview
This project is a simple text editor written in C, built using the `gcc` compiler on a Linux environment. The application manages a custom text buffer in memory using an array-based doubly linked list and utilizes the NCURSES library for dynamic terminal user interface rendering and cursor navigation. It features both manual and automated garbage collection to optimize memory layout. Check docs/232proj26s.pdf for further information

---

## Task Distribution (TS0 - TS9)
To ensure a smooth forkflow , this project follows a sequential development process.

| Group Member’s Name | Tasks |
| :--- | :--- |
| **Member 1** | TS0- Defining the node struct<br>TS1- Initialising global variables<br>TS2- Implementing edit() and save() functions |
| **Member 2** | TS3- Implementing insert(), delete() and replace() functions<br>TS4- Implementing the garbageCollection() function |
| **Member 3** | TS5 -Initialising NCURSES screen in main()<br>TS6- Implementing the print() function |
| **Member 4** | TS7- Coding cursorLine() and cursorChar() functions |
| **Member 5** | TS8- Handling listening for E,I,D,R,P,S,G,Q presses and routing presses to functions<br>TS9 - Implementing automatic triggering of garbage collection |

---

## Installation & Prerequisites
Before compiling the project, you must install the NCURSES development package on your local Linux machine.

On Debian/Ubuntu-based systems, run:
```bash
sudo apt update && sudo apt install libncurses-dev