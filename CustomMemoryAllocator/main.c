#include <stdio.h>
#include <stdlib.h>
#include "mpalloc.h"

int main() {
    init_memory_pool(1024 * 1024);
    void* ptr1 = mp_alloc(100);
    void* ptr2 = mp_alloc(200);
    void* ptr3 = mp_alloc(300);
    void* ptr4 = mp_alloc(400);
    void* ptr5 = mp_alloc(500);
    void* ptr6 = mp_alloc(600);
    void* ptr7 = mp_alloc(700);
    void* ptr8 = mp_alloc(800);
    void* ptr9 = mp_alloc(900);
    void* ptr10 = mp_alloc(1000);

    mp_print_blocks();

    mp_free(ptr1);
    mp_free(ptr3);
    mp_free(ptr5);
    mp_free(ptr7);
    mp_free(ptr9);

    mp_print_blocks();

    mp_free(ptr2);
    mp_free(ptr4);

    mp_print_blocks();

    void* ptr11 = mp_alloc(1000);
    mp_print_blocks();

    mp_free(ptr6);
    mp_free(ptr8);
    mp_free(ptr10);

    mp_print_blocks();

    mp_free_pool();
    mp_print_blocks();

    return 0;
}