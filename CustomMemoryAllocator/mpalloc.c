#include <stdio.h>
#include <stdlib.h>
#include "mpalloc.h"

// Memory pool variables
void* memory_pool = NULL;            // Pointer to the start of the pool
struct MemPoolBlockMetadata* mp_head = NULL;   // mp_head of the linked list

// Align size to a multiple of 8 (for memory alignment)
#define ALIGN(size) (((size) + 7) & ~7)

// Initialize the memory pool
void init_memory_pool(int pool_size) {
    memory_pool = malloc(pool_size);
    if (!memory_pool) {
        fprintf(stderr, "Failed to initialize memory pool\n");
        exit(EXIT_FAILURE);
    }

    // Create the first block metadata
    mp_head = (struct MemPoolBlockMetadata*)memory_pool;
    mp_head->size = pool_size - sizeof(struct MemPoolBlockMetadata); // Remaining size after metadata
    mp_head->is_free = 1;                                     // Initially free
    mp_head->next = NULL;                                     // No next block
}

// Custom malloc using the memory pool
void* mp_alloc(size_t size) {
    size = ALIGN(size); // Align size to ensure proper alignment
    struct MemPoolBlockMetadata* current = mp_head;

    // Search for a suitable free block
    while (current != NULL) {
        if (current->is_free && current->size >= size) {
            // Split the block if it's larger than needed
            if (current->size > size + sizeof(struct MemPoolBlockMetadata)) {
                struct MemPoolBlockMetadata* new_block = (struct MemPoolBlockMetadata*)((char*)(current + 1) + size);
                new_block->size = current->size - size - sizeof(struct MemPoolBlockMetadata);
                new_block->is_free = 1;
                new_block->next = current->next;
                current->next = new_block;
                current->size = size;
            }
            current->is_free = 0; // Mark block as allocated
            return (void*)(current + 1); // Return memory after metadata
        }
        current = current->next;
    }

    // No suitable block found
    fprintf(stderr, "Out of memory\n");
    return NULL;
}

// Custom free using the memory pool
void mp_free(void* ptr) {
    if (!ptr) return; // NULL pointer, do nothing

    // Get the metadata by moving back from the pointer
    struct MemPoolBlockMetadata* block = (struct MemPoolBlockMetadata*)ptr - 1;
    block->is_free = 1; // Mark block as free

    // Coalesce adjacent free blocks
    struct MemPoolBlockMetadata* current = mp_head;
    while (current != NULL) {
        if (current->is_free && current->next && current->next->is_free) {
            current->size += sizeof(struct MemPoolBlockMetadata) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}


void mp_free_pool() {
    free(memory_pool);
}

void mp_print_blocks() {
    struct MemPoolBlockMetadata* current = mp_head;

    printf("Memory Blocks:\n");
    printf("--------------------------------------------------\n");
    printf("| Block Address | Size (bytes) | Status  | Next   |\n");
    printf("--------------------------------------------------\n");
    while(current != NULL) {
        printf("| %p     | %-13zu | %-7s | %p |\n", 
                (void*)current,
                current->size,
                current->is_free ? "Free" : "Used",
                (void*)current->next);
        current = current->next;
    }
}
