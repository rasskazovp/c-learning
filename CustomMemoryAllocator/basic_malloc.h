#ifndef BASIC_MALLOC_H
#define BASIC_MALLOC_H

void * basic_malloc(size_t size);
void basic_free(void * ptr);
void basic_free_all();
void basic_print_blocks();

struct BasicBlockMetadata {
    size_t size;             // Size of the memory block
    int is_free;             // Whether the block is free (1) or allocated (0)
    struct BasicBlockMetadata* next; // Pointer to the next block
};

#endif