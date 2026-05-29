#include <stdio.h>
#include <string.h>
#include "editor.h"

// Bring in your TS3 and TS4 functions
extern void insert(int target_line, const char *new_text);
extern void delete(int target_line);
extern void replace(int target_line, const char *new_text);
extern void garbageCollection();

// Helper function to print the exact state of the linked list
void printEngineState(const char* stage_name) {
    printf("\n--- %s ---\n", stage_name);
    int curr = head;
    int count = 0;
    
    if (curr == -1) {
        printf("[Buffer is entirely empty]\n");
    } else {
        while (curr != -1 && count < 5) { // Print only first 5 to avoid terminal spam
            printf("Line %d [Array Index %d]: %s\n", count, curr, textbuffer[curr].statement);
            curr = textbuffer[curr].next;
            count++;
        }
        if (curr != -1) printf("... (Remaining lines hidden) ...\n");
    }
    printf(">> METRICS -> head: %d | tail: %d | free_index: %d\n", head, tail, free_index);
}

int main() {
    printf("==================================================\n");
    printf("      ENGINE STRESS TEST: TS3 & TS4\n");
    printf("==================================================\n");

    // We manually reset globals to ensure a clean slate
    head = -1;
    tail = -1;
    free_index = 0;

    // ---------------------------------------------------------
    // TEST 1: TS3 Basic Edits (Insert, Replace, Delete)
    // ---------------------------------------------------------
    insert(0, "Initial Line A.");
    insert(1, "Initial Line B.");
    insert(0, "INJECTED AT TOP."); // Tests shifting the head down
    
    printEngineState("After 3 Insertions");

    replace(1, "REPLACED LINE A."); // Tests string replacement
    delete(2);                      // Tests link repairing on deletion
    
    printEngineState("After 1 Replace and 1 Delete");

    // ---------------------------------------------------------
    // TEST 2: TS4 Garbage Collection Trigger
    // ---------------------------------------------------------
    printf("\n[!] STRESS TEST INITIATED: Maxing out array capacity...\n");
    
    char dummy_text[40];
    // We already used index 0, 1, 2. Let's fill the remaining 97 slots.
    for (int i = 0; i < 97; i++) {
        sprintf(dummy_text, "Filler line #%d", i);
        insert(100, dummy_text); // Appending to the very end
    }
    
    printf(">> METRICS -> free_index is now: %d\n", free_index);
    printf("\n[!] Deleting the top 5 lines to create fragmented 'ghost' memory...\n");
    
    for (int i = 0; i < 5; i++) {
        delete(0);
    }
    
    // Notice that free_index is still 100, even though we just freed up 5 slots.
    printf(">> METRICS -> free_index after deletions: %d\n", free_index);
    
    printf("\n[!] Attempting to insert a new line while free_index == 100.\n");
    printf("[!] This MUST silently trigger garbageCollection()...\n");
    
    insert(0, "SUCCESS: SURVIVED GARBAGE COLLECTION!");

    printEngineState("Final Engine State");

    printf("\n==================================================\n");
    printf("If you see the SUCCESS line at Line 0, your TS4 is flawless.\n");
    printf("==================================================\n");

    return 0;
}