/* ==========================================================================
 * Member: Member 3, 4 & 5
 * Tasks:  TS5, TS7, TS8, TS9
 * ==========================================================================
*/

#include "editor.h"
#include <ncurses.h>
#include <string.h> // Required for string stripping

// External function declarations
extern void edit(char *filename);
extern void save(char *filename);
extern void insert(int node_index, const char *new_text);
extern void delete(int node_index);
extern void replace(int node_index, int char_index, char new_char);
extern void garbageCollection();
extern void print();

// Pull Member 4's functions from ui.c
extern int cursorLine();
extern int cursorChar();

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(1);

    int ch;
    int cursor_y = 0;       
    int cursor_x = 0;       
    int selected_line = -1; 
    int edit_counter = 0;

    char input[40];
    char filename[100] = ""; 

    print();
    
    move(cursor_y, cursor_x);
    refresh();

    while (1) {
        ch = getch();

        /* --- NAVIGATION --- */
        if (ch == KEY_UP) {
            if (cursor_y > 0) cursor_y--;
            move(cursor_y, cursor_x);
            refresh();
        }
        else if (ch == KEY_DOWN) {
            if (cursor_y < 29) cursor_y++;
            move(cursor_y, cursor_x);
            refresh();
        }
        else if (ch == KEY_LEFT) {
            if (cursor_x > 0) cursor_x--;
            move(cursor_y, cursor_x);
            refresh();
        }
        else if (ch == KEY_RIGHT) {
            if (cursor_x < 39) cursor_x++;
            move(cursor_y, cursor_x);
            refresh();
        }

        /* --- SELECTION & DESELECTION (ENTER KEY) --- */
        else if (ch == '\n' || ch == '\r' || ch == KEY_ENTER) {
            
            // If a line is ALREADY locked, hitting ENTER again cancels the lock
            if (selected_line != -1) {
                selected_line = -1; // Reset to safe state
                
                move(LINES - 6, 0);
                clrtoeol(); // Erase the prompt
                
                move(cursor_y, cursor_x); 
                refresh();
            } 
            // If no line is locked, act normally and lock it
            else {
                move(cursor_y, cursor_x);
                selected_line = cursorLine(); 
                
                move(LINES - 6, 0);
                clrtoeol(); 
                // Using your custom text, plus the cancel instruction
                printw("Line locked. Now you can use commands: [I]nsert  [D]elete  [R]eplace (Press ENTER to cancel)");
                
                move(cursor_y, cursor_x); 
                refresh();
            }
        }

        /* --- COMMANDS --- */
        else if (ch == 'P' || ch == 'p') {
            print();
            cursor_y = 0;
            cursor_x = 0;
            selected_line = -1;
            move(cursor_y, cursor_x);
            refresh();
        }

        else if (ch == 'I' || ch == 'i' ) {
            if (selected_line == -1) continue; 

            move(LINES - 6, 0);
            clrtoeol();
            printw("Insert statement: ");
            
            echo();
            getnstr(input, 39);
            noecho();

            // CRITICAL FIX: Strip the hidden newline so it doesn't cause a visual gap
            input[strcspn(input, "\r\n")] = '\0';

            insert(selected_line, input); 
            edit_counter++;

            if (edit_counter >= 10) {
                garbageCollection();
                edit_counter = 0;
            }

            print(); // print() naturally clears the whole screen, removing the prompt
            selected_line = -1;
            move(cursor_y, cursor_x);
            refresh();
        }

        else if (ch == 'D' || ch == 'd') {
            if (selected_line == -1) continue;

            delete(selected_line);
            edit_counter++;

            if (edit_counter >= 10) {
                garbageCollection();
                edit_counter = 0;
            }

            print();
            selected_line = -1;
            move(cursor_y, cursor_x);
            refresh();
        }

        else if (ch == 'R' || ch == 'r') {
            if (selected_line == -1) continue;

            move(cursor_y, cursor_x);
            int char_pos = cursorChar(); 
            
            move(LINES - 6, 0);
            clrtoeol();
            printw("Enter new character: ");
            refresh();
            
            int new_char = getch(); 
            
            replace(selected_line, char_pos, (char)new_char);
            
            print();
            selected_line = -1;
            move(cursor_y, cursor_x);
            refresh();
        }

        else if (ch == 'S' || ch == 's') {
            move(LINES - 6, 0);
            clrtoeol();
            printw("File saved successfully. Press any key...");
            save(filename);
            refresh();
            
            getch();
            print();
            move(cursor_y, cursor_x);
            refresh();
        }

        else if (ch == 'G' || ch == 'g') {
            garbageCollection();
            move(LINES - 6, 0);
            clrtoeol();
            printw("Garbage Collection Forced. Press any key...");
            refresh();
            
            getch();
            print();
            move(cursor_y, cursor_x);
            refresh();
        }

        else if (ch == 'E' || ch == 'e') {
            move(LINES - 6, 0);
            clrtoeol();
            printw("Edit file name: ");
            
            echo();
            getnstr(filename, 99);
            noecho();

            filename[strcspn(filename, "\r\n")] = '\0'; // Strip newline from filename too

            edit(filename);
            print();
            cursor_y = 0; cursor_x = 0; selected_line = -1;
            move(cursor_y, cursor_x);
            refresh();
        }

        else if (ch == 'Q' || ch == 'q') {
            break;
        }
    }

    endwin();
    return 0;
}