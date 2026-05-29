#include <stdio.h>
#include "../include/editor.h"

// Note: You must declare the external functions from other files to test them
extern void edit(char *filename);
extern void save(char *filename);
extern void insert(int target_line, const char *new_text);
extern void delete(int target_line);
extern void replace(int target_line, const char *new_text);
extern void garbageCollection();

int main() {
    printf("=== Starting Engine Test ===\n");

    // 1. Test Member 1's file loading
    edit("tests/mytext.txt"); 
    printf("Loaded original file into memory.\n");

    // 2. Test your engine functions
    insert(1, "THIS IS A BRAND NEW LINE INJECTED.");
    delete(3);
    replace(0, "I REPLACED THE VERY FIRST LINE.");
    
    // Force a garbage collection to ensure it doesn't break links
    garbageCollection();
    printf("Garbage collection successful.\n");

    // 3. Test Member 1's file saving
    save("tests/mytest.txt"); // Assuming save() writes to tests/mytext.txt or a new file
    printf("Saved new memory state back to disk. Check tests/mytext.txt!\n");

    return 0;
}