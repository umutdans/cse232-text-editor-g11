/* ==========================================================================
 * Member: Member 3 & Member 5
 * Tasks:  TS5, TS8, TS9 
 * ========================================================================== 
*/

#include "editor.h"
#include <ncurses.h>

extern void edit(char *filename);

int main() {

    edit("tests/mytext.txt"); /* Opening up the mytext.txt for testing purposes */
   
    initscr();            /* Start NCURSES mode                          */
    noecho();             /* Don't echo typed characters to screen       */
    cbreak();             /* Disable line buffering, get chars instantly */
    keypad(stdscr, TRUE); /* Enable arrow keys (KEY_UP, KEY_DOWN, etc.)  */
    curs_set(1);          /* Show cursor                                 */
 
    
    print();   /* TS6: draw the (empty) buffer on screen */
 
    /* ------------------------------------------------------------------
     * TS8: Main event loop — listen for key presses (Member 5)
     * ------------------------------------------------------------------ */
    /* TODO (Member 5): implement key handling for E,I,D,R,P,S,G,Q */
    


    getch();  /* Freeze the screen for testing purposes */

    endwin(); /* End NCURSES window*/
    return 0;
}