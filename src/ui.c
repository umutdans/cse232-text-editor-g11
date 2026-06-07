/* ==========================================================================
 * Member: Member 3 & Member 4
 * Tasks:  TS6, TS7
 * ========================================================================== 
*/

#include "editor.h"
#include <ncurses.h>

/* --------------------------------------------------------------------------
 * TS6: print()
 * Refreshes the entire screen by traversing the textbuffer[] linked list.
 * -------------------------------------------------------------------------- */
void print() {
    clear();   /* Erase everything on the NCURSES screen */
 
    int curr = head;   
    int row  = 0;      
 
    /* Traverse the linked list and print each statement */
    while (curr != -1 && row < 30) {
        mvprintw(row, 0, "%s", textbuffer[curr].statement);
        curr = textbuffer[curr].next;
        row++;
    }
 
    /* Print the command prompt on the line right after the last statement */
    mvprintw(row, 0, "> ");

    /* ==========================================================================
     * DYNAMIC HELP MENU (Floats right below the prompt)
     * ========================================================================== */
    mvprintw(row + 1, 0, "Commands can be used by pressing the key inside []");
    mvprintw(row + 2, 0, "Press ENTER to lock curser location first then you can use commands: [I]nsert  [D]elete  [R]eplace");
    mvprintw(row + 3, 0, "These commands can be used any time: [E]dit  [S]ave  [G]arbage Collect  [Q]uit");
 
    /* Move the cursor back up to the > prompt so it's ready for action */
    move(row, 2);
 
    refresh(); 
}
 
/* --------------------------------------------------------------------------
 * TS7: cursorLine() and cursorChar()
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