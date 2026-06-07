/* ==========================================================================
 * Member: Member 2
 * Tasks:  TS3 (Core Edits), TS4 (Memory Rebalancing)
 * ========================================================================== */

#include "editor.h"
#include <string.h>

// -------------------------------------------------------------------------
// TS4: Memory Rebalancing (Garbage Collection)
// Defined first so the compiler recognizes it when insert() calls it
// -------------------------------------------------------------------------

void garbageCollection() {
    struct node temp[100]; 
    int curr = head;
    int active_count = 0;

    // 1. Traverse the fragmented linked list and pack lines sequentially into temp
    while (curr != -1 && active_count < 100) {
        // Copy the text
        strncpy(temp[active_count].statement, textbuffer[curr].statement, 40);
        
        // Rebuild purely sequential pointers
        temp[active_count].prev = (active_count == 0) ? -1 : active_count - 1;
        temp[active_count].next = -1; // Will be overwritten by next iteration if not tail
        
        if (active_count > 0) {
            temp[active_count - 1].next = active_count;
        }

        curr = textbuffer[curr].next;
        active_count++;
    }

    // 2. Overwrite the main buffer with the clean, packed temp array
    for (int i = 0; i < active_count; i++) {
        textbuffer[i] = temp[i];
    }

    // 3. Update global pointers to reflect the new sequential layout
    head = (active_count > 0) ? 0 : -1;
    tail = (active_count > 0) ? active_count - 1 : -1;
    
    // 4. Reset free_index to the first available empty slot
    free_index = active_count;
}

// -------------------------------------------------------------------------
// TS3: Core Edit Functions
// -------------------------------------------------------------------------

void insert(int node_index, const char *new_text) {
    if (free_index >= 100) {
        garbageCollection();
        if (free_index >= 100) return; 
    }

    int new_node = free_index;
    free_index++;

    strncpy(textbuffer[new_node].statement, new_text, 39);
    textbuffer[new_node].statement[39] = '\0';

    if (head == -1) {
        head = new_node;
        tail = new_node;
        textbuffer[new_node].prev = -1;
        textbuffer[new_node].next = -1;
        return;
    }

    // If node_index is invalid, append to the end
    if (node_index == -1) {
        node_index = tail;
    }

    // Insert AFTER the given node_index (per assignment)
    textbuffer[new_node].next = textbuffer[node_index].next;
    textbuffer[new_node].prev = node_index;

    if (textbuffer[node_index].next != -1) {
        textbuffer[textbuffer[node_index].next].prev = new_node;
    } else {
        tail = new_node;
    }
    textbuffer[node_index].next = new_node;
}

void delete(int node_index) {
    if (node_index == -1) return; 

    if (textbuffer[node_index].prev != -1) {
        textbuffer[textbuffer[node_index].prev].next = textbuffer[node_index].next;
    } else {
        head = textbuffer[node_index].next;
    }

    if (textbuffer[node_index].next != -1) {
        textbuffer[textbuffer[node_index].next].prev = textbuffer[node_index].prev;
    } else {
        tail = textbuffer[node_index].prev;
    }
}

void replace(int node_index, int char_index, char new_char) {
    // Ensure we don't try to write outside the bounds of the 40-char array
    if (node_index != -1 && char_index >= 0 && char_index < 39) {
        int len = strlen(textbuffer[node_index].statement);
        
        // Replace existing character
        if (char_index < len) {
            textbuffer[node_index].statement[char_index] = new_char;
        } 
        // If cursor is at the exact end of the string, extend it by 1 character
        else if (char_index == len) {
            textbuffer[node_index].statement[char_index] = new_char;
            textbuffer[node_index].statement[char_index + 1] = '\0';
        }
    }
}