/* ==========================================================================
 * Member: Member 1
 * Tasks:  TS2
 * ========================================================================== 
*/

#include "editor.h"
#include <stdio.h>
#include <string.h>

void edit(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        head = -1;
        tail = -1;
        free_index = 0;
        return;
    }

    int current_index = 0;
    char line_buffer[100];

    head = -1;
    tail = -1;

    while (current_index < 100 && fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        line_buffer[strcspn(line_buffer, "\n")] = '\0';

        strncpy(textbuffer[current_index].statement, line_buffer, 39);
        textbuffer[current_index].statement[39] = '\0';

        if (current_index == 0) {
            head = 0;
            textbuffer[current_index].prev = -1;
        } else {
            textbuffer[current_index - 1].next = current_index;
            textbuffer[current_index].prev = current_index - 1;
        }

        tail = current_index;
        textbuffer[current_index].next = -1;

        current_index++;
    }

    free_index = current_index;
    fclose(file);
}

void save(char *filename) {
    if (filename == NULL) return;

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }

    if (head == -1) {
        fclose(file);
        return;
    }

    int current = head;
    while (current != -1) {
        fprintf(file, "%s\n", textbuffer[current].statement);
        current = textbuffer[current].next;
    }

    fclose(file);
}

 
