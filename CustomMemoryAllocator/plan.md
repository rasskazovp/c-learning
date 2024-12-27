1. Implement the Basic Allocator
2. Implement Memory Pool Allocator
3. Measure performance
4. Optrimize performance:
    - Reduce fragmentation by coalescing adjacent free blocks during deallocation.
    - Implement a best-fit or first-fit strategy for block allocation.
    - Use a free-list to track free blocks efficiently.
5. Add more features;
    - Support alignment (e.g., 4-byte, 8-byte aligned allocations).
    - Add thread safety
    - Implement dynamic resizing of memory pool
6. Track and compare memory efficency
    - Track and log memory usage statistics:
        - Total memory allocated.
        - Memory fragmentation (free/used blocks).
    - Compare memory efficiency with malloc/free.