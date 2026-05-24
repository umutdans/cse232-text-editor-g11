/* ==========================================================================
 * Member: Member 1
 * Tasks:  TS0 (Define node struct), TS1 (Initialize globals)
 * ========================================================================== */
struct node {
    char statement[40];
    int next;
    int prev;
};

extern struct node textbuffer[100];
extern int head;
extern int tail;
extern int free_index;
