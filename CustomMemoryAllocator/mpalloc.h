#ifndef MPALLOC_H
#define MPALLOC_H

void init_memory_pool();
void * mp_alloc(size_t size);
void mp_free(void * ptr);
void mp_free_pool();
void mp_print_blocks();

struct MemPoolBlockMetadata {
    size_t size;             // Size of the memory block
    int is_free;             // Whether the block is free (1) or allocated (0)
    struct MemPoolBlockMetadata* next; // Pointer to the next block
};

#endif