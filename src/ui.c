/* ==========================================================================
 * Member: Member 3 & Member 4
 * Tasks:  TS6, TS7
 * ========================================================================== 
*/

#include "editor.h"
#include <ncurses.h>

/* --------------------------------------------------------------------------
 * TS6: print()
 *
 * Refreshes the entire screen by traversing the textbuffer[] linked list
 * starting from head and following the "next" links.
 *
 * Layout:
 *   Row 0  -> first statement
 *   Row 1  -> second statement
 *   ...
 *   Row N  -> last statement
 *   Row N+1-> "> " prompt line
 *
 * After drawing, the cursor is left on the prompt line so the user
 * can type commands.
 * -------------------------------------------------------------------------- */
void print() {
    clear();   /* Erase everything on the NCURSES screen */
 
    int curr = head;   /* Start from the first valid node */
    int row  = 0;      /* Current screen row              */
 
    /* Traverse the linked list and print each statement on its own row.
     * The spec says maximum text size is 30 lines, so we stop at 30. */
    while (curr != -1 && row < 30) {
        mvprintw(row, 0, "%s", textbuffer[curr].statement);
        curr = textbuffer[curr].next;
        row++;
    }
 
    /* Print the command prompt on the line right after the last statement */
    mvprintw(row, 0, "> ");
 
    /* Move the cursor to just after the prompt, ready for user input */
    move(row, 2);
 
    refresh(); /* Push all changes to the actual terminal screen */
}
 
/* --------------------------------------------------------------------------
 * TS7: cursorLine() and cursorChar() — to be implemented by Member 4
 * -------------------------------------------------------------------------- */
 
int cursorLine() {
    int y, x;
    getyx(stdscr, y, x); 
    
    int curr = head;
    int count = 0;
    
    while (curr != -1 && count < y) {
        curr = textbuffer[curr].next;
        count++;
    }
    
    return curr; 
}

int cursorChar() {
    int y, x;
    getyx(stdscr, y, x);
    
    return x; 
}
