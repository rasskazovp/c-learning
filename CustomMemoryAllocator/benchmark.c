#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "basic_malloc.h"
#include "mpalloc.h"

void small_allocattions_benchmark(void* (*allocator)(size_t), void (*deallocator)(void*)) {
    LARGE_INTEGER frequency, start, end;
    size_t block_size = 16;
    const int chunk_size = 1000;
    const int num_allocations = chunk_size * 1000;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    void* ptrs[chunk_size];
    for (int i = 0; i < num_allocations/chunk_size; i++) {
        for (int j = 0; j < chunk_size; j++) {
            ptrs[j] = allocator(block_size);
        }
        for (int j = 0; j < chunk_size; j++) {
            deallocator(ptrs[j]);
        }
    }

    QueryPerformanceCounter(&end);
    double time_taken = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("Small allocations - Time taken: %f seconds\n", time_taken);
}

void large_allocattions_benchmark(void* (*allocator)(size_t), void (*deallocator)(void*)) {
    LARGE_INTEGER frequency, start, end;
    double cpu_time_used;
    size_t block_size = 1024 * 1024;
    const int chunk_size = 100;
    const int num_allocations = chunk_size * 100;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    void* ptrs[chunk_size];
    for (int i = 0; i < num_allocations/chunk_size; i++) {
        for (int j = 0; j < chunk_size; j++) {
            ptrs[j] = allocator(block_size);
        }
        for (int j = 0; j < chunk_size; j++) {
            deallocator(ptrs[j]);
        }
    }

    QueryPerformanceCounter(&end);
    double time_taken = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("Large allocations - Time taken: %f seconds\n", time_taken);
}

void high_fragmentation_benchmark(void* (*allocator)(size_t), void (*deallocator)(void*)) {
    LARGE_INTEGER frequency, start, end;
    double cpu_time_used;
    int bytes_list[] = {4, 8, 16, 32, 64, 128, 20, 36, 24, 12};
    const int chunk_size = 100;
    const int num_allocations = chunk_size * 1000;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    void* ptrs[chunk_size];
    for (int i = 0; i < num_allocations/chunk_size; i++) {
        for (int j = 0; j < chunk_size; j++) {
            ptrs[j] = allocator(bytes_list[j % 10]);
        }
        for (int j = 0; j < chunk_size; j++) {
            deallocator(ptrs[j]);
        }
    }

    QueryPerformanceCounter(&end);
    double time_taken = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("High fragmentation benchmark - Time taken: %f seconds\n", time_taken);
}

void* malloc_allocator(size_t size) {
    return malloc(size);
}

void malloc_deallocator(void* ptr) {
    free(ptr);
}

int main(){

    // Run benchmark with malloc/free
    printf("Benchmarking without standard (malloc/free):\n");
    small_allocattions_benchmark(malloc_allocator, malloc_deallocator);
    large_allocattions_benchmark(malloc_allocator, malloc_deallocator);
    high_fragmentation_benchmark(malloc_allocator, malloc_deallocator);

    // Run benchmark with basic allocator/deallocator
    printf("\nBenchmarking with basic implementation (basic_malloc/basic_free):\n");
    small_allocattions_benchmark(basic_malloc, basic_free);
    basic_free_all();
    large_allocattions_benchmark(basic_malloc, basic_free);
    basic_free_all();
    high_fragmentation_benchmark(basic_malloc, basic_free);
    basic_free_all();

    // Run benchmark with Memory Pool allocator/deallocator
    printf("\nBenchmarking with basic implementation (mp_alloc/mp_free):\n");
    init_memory_pool(1024 * 1024);
    small_allocattions_benchmark(mp_alloc, mp_free);
    mp_free_pool();
    init_memory_pool(101 * 1024 * 1024);
    large_allocattions_benchmark(mp_alloc, mp_free);
    mp_free_pool();
    init_memory_pool(1024 * 1024);
    high_fragmentation_benchmark(mp_alloc, mp_free);
    mp_free_pool();

}