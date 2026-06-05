/* ==========================================================================
 * Member: Member 3 & Member 5
 * Tasks:  TS5, TS8, TS9
 * ==========================================================================
*/

#include "editor.h"
#include <ncurses.h>

extern void edit(char *filename);
extern void save(char *filename);
extern void insert(int target_line, const char *new_text);
extern void delete(int target_line);
extern void replace(int target_line, const char *new_text);
extern void garbageCollection();

int main() {
    edit("tests/mytext.txt");

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(1);

    print();

    int ch;
    int selected_line = 0;
    int edit_counter = 0;

    char input[40];
    char filename[100] = "tests/mytext.txt";

    while (1) {
        ch = getch();

        if (ch == KEY_UP) {
            if (selected_line > 0) {
                selected_line--;
            }
            move(selected_line, 0);
        }

        else if (ch == KEY_DOWN) {
            selected_line++;
            move(selected_line, 0);
        }

        else if (ch == 'P' || ch == 'p') {
            print();
            selected_line = 0;
            move(selected_line, 0);
        }

        else if (ch == 'I' || ch == 'i') {
            echo();
            mvprintw(31, 0, "Insert text: ");
            getnstr(input, 39);
            noecho();

            insert(selected_line + 1, input);
            edit_counter++;

            if (edit_counter >= 10) {
                garbageCollection();
                edit_counter = 0;
            }

            print();
        }

        else if (ch == 'D' || ch == 'd') {
            delete(selected_line);
            edit_counter++;

            if (edit_counter >= 10) {
                garbageCollection();
                edit_counter = 0;
            }

            print();
            selected_line = 0;
        }

        else if (ch == 'R' || ch == 'r') {
            echo();
            mvprintw(31, 0, "Replace line with: ");
            getnstr(input, 39);
            noecho();

            replace(selected_line, input);
            print();
        }

        else if (ch == 'S' || ch == 's') {
            save(filename);
            mvprintw(31, 0, "File saved.");
            refresh();
        }

        else if (ch == 'G' || ch == 'g') {
            garbageCollection();
            print();
        }

        else if (ch == 'E' || ch == 'e') {
            echo();
            mvprintw(31, 0, "File name: ");
            getnstr(filename, 99);
            noecho();

            edit(filename);
            print();
            selected_line = 0;
        }

        else if (ch == 'Q' || ch == 'q') {
            break;
        }
    }

    endwin();
    return 0;
}
