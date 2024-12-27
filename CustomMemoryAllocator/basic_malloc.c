#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic_malloc.h"

struct BasicBlockMetadata* basic_head = NULL; // Pointer to the first block in the pool
#define ALIGN(size) (((size) + 7) & ~7) // Align size to a multiple of 8 (for memory alignment)

void* basic_malloc(size_t size) {
    size = ALIGN(size); // Align size to ensure proper alignment
    struct BasicBlockMetadata* current = basic_head;

    // Search for a free block
    while(current != NULL) {
        if(current->is_free && current->size >= size) {
            // printf("Reusing existing block\n");
            current->is_free = 0;
            return (void*)(current + 1);
        }
        current = current->next;
    }

    // No suitable block found, allocate a new block
    // printf("Allocating new block\n");
    size_t total_size = size + sizeof(struct BasicBlockMetadata);
    struct BasicBlockMetadata* new_block = (struct BasicBlockMetadata*)malloc(total_size);
    if(!new_block) {
        return NULL; // Return NULL if malloc fails
    }

    // Initialize the new block
    new_block->size = size;
    new_block->is_free = 0;
    new_block->next = basic_head;
    basic_head = new_block;

    return (void*)(new_block + 1);
}

void basic_free(void * ptr) {
    if(!ptr) {
        // printf("Cannot free NULL pointer\n");
        return; // Do nothing if ptr is NULL
    }

    struct BasicBlockMetadata* block_ptr = (struct BasicBlockMetadata*)ptr - 1;
    // printf("Freeing block %p\n", block_ptr);
    block_ptr->is_free = 1;
}

void basic_free_all() {
    struct BasicBlockMetadata* current = basic_head;
    while(current != NULL) {
        struct BasicBlockMetadata* next = current->next;
        free(current);
        current = next;
    }
    basic_head = NULL;
}

void basic_print_blocks() {
    struct BasicBlockMetadata* current = basic_head;

    printf("Memory Blocks:\n");
    printf("|       Block      | Usable Size (byte) | Free |\n");
    while(current != NULL) {
        printf("| %p |         %lu         |  %d  |\n", current, current->size, current->is_free);
        current = current->next;
    }
}