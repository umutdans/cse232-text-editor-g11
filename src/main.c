/* ==========================================================================
 * Member: Member 3 & Member 5
 * Tasks:  TS5, TS8, TS9 
 * ========================================================================== 
*/

#include "editor.h"
#include <ncurses.h>

int main() {
    /* ------------------------------------------------------------------
     * TS5: Initialize NCURSES
     * ------------------------------------------------------------------ */
    initscr();            /* Start NCURSES mode                          */
    noecho();             /* Don't echo typed characters to screen       */
    cbreak();             /* Disable line buffering, get chars instantly */
    keypad(stdscr, TRUE); /* Enable arrow keys (KEY_UP, KEY_DOWN, etc.)  */
    curs_set(1);          /* Show cursor                                 */
 
    /* ------------------------------------------------------------------
     * TS1: Initialize global variables (defined in editor.c)
     * head, tail, free_index are set to -1 / 0 there.
     * Display initial empty screen with prompt.
     * ------------------------------------------------------------------ */
    print();   /* TS6: draw the (empty) buffer on screen */
 
    /* ------------------------------------------------------------------
     * TS8: Main event loop — listen for key presses (Member 5)
     * ------------------------------------------------------------------ */
    /* TODO (Member 5): implement key handling for E,I,D,R,P,S,G,Q */
 
    /* ------------------------------------------------------------------
     * Cleanup: end NCURSES before exit
     * ------------------------------------------------------------------ */
    endwin();
    return 0;
}