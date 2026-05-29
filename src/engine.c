/* ==========================================================================
 * Member: Member 2 (Umut Danışmaz)
 * Tasks:  TS3 (Core Edits), TS4 (Memory Rebalancing)
 * Functions: 
 * - garbageCollection()
 * - insert(int index, const char *new_text)
 * - delete(int index)
 * - replace(int index, const char *new_text)
 * ========================================================================== */

#include "editor.h"
#include <string.h>

// Helper function: Translates a visual line number into the actual array index
static int get_actual_index(int logical_line) {
    int curr = head;
    int count = 0;
    while (curr != -1 && count < logical_line) {
        curr = textbuffer[curr].next;
        count++;
    }
    return curr;
}

// -------------------------------------------------------------------------
// TS4: Memory Rebalancing (Garbage Collection)
// Placed before insert() so the compiler recognizes it immediately
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
    
    // 4. Reset free_index to the first available empty slot!
    free_index = active_count;
}

// -------------------------------------------------------------------------
// TS3: Core Edit Functions
// -------------------------------------------------------------------------

void insert(int target_line, const char *new_text) {
    // 1. Check if we are out of sequential space
    if (free_index >= 100) {
        garbageCollection();
        if (free_index >= 100) return; // Buffer is 100% full, ignore insert
    }

    // 2. Claim the next available slot at the bottom of the array
    int new_node = free_index;
    free_index++;

    // 3. Populate text (Member 1 used max 39 chars + null terminator)
    strncpy(textbuffer[new_node].statement, new_text, 39);
    textbuffer[new_node].statement[39] = '\0';

    // 4. Handle empty buffer
    if (head == -1) {
        head = new_node;
        tail = new_node;
        textbuffer[new_node].prev = -1;
        textbuffer[new_node].next = -1;
        return;
    }

    // 5. Insert at the very top (Line 0)
    if (target_line <= 0) {
        textbuffer[new_node].next = head;
        textbuffer[new_node].prev = -1;
        textbuffer[head].prev = new_node;
        head = new_node;
        return;
    }

    // 6. Insert in the middle or end
    int curr = get_actual_index(target_line - 1); // Get node BEFORE insertion point
    if (curr == -1) curr = tail; // If target_line is too large, append to end

    textbuffer[new_node].next = textbuffer[curr].next;
    textbuffer[new_node].prev = curr;

    if (textbuffer[curr].next != -1) {
        textbuffer[textbuffer[curr].next].prev = new_node;
    } else {
        tail = new_node; // Appended to end
    }
    textbuffer[curr].next = new_node;
}

void delete(int target_line) {
    int target_node = get_actual_index(target_line);
    if (target_node == -1) return; // Line doesn't exist

    // 1. Repair previous link (or update head)
    if (textbuffer[target_node].prev != -1) {
        textbuffer[textbuffer[target_node].prev].next = textbuffer[target_node].next;
    } else {
        head = textbuffer[target_node].next;
    }

    // 2. Repair next link (or update tail)
    if (textbuffer[target_node].next != -1) {
        textbuffer[textbuffer[target_node].next].prev = textbuffer[target_node].prev;
    } else {
        tail = textbuffer[target_node].prev;
    }

    // Note: The memory slot is now "orphaned". We do not touch free_index.
    // The Garbage Collector will reclaim this space later.
}

void replace(int target_line, const char *new_text) {
    int target_node = get_actual_index(target_line);
    if (target_node != -1) {
        strncpy(textbuffer[target_node].statement, new_text, 39);
        textbuffer[target_node].statement[39] = '\0';
    }
}