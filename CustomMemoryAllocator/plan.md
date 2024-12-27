1. Implement the Basic Allocator - Done
2. Implement Memory Pool Allocator - Done
3. Measure performance - Done
4. Optrimize performance:
    - Reduce fragmentation by coalescing adjacent free blocks during deallocation. - Done
    - Implement a best-fit or first-fit strategy for block allocation.
    - Use a free-list to track free blocks efficiently.
5. Add more features:
    - Support alignment (e.g., 4-byte, 8-byte aligned allocations). - Done
    - Add thread safety
    - Implement dynamic resizing of memory pool
    - Handle double-free adn out-of-memory errors
6. Track and compare memory efficency
    - Track and log memory usage statistics:
        - Total memory allocated.
        - Memory fragmentation (free/used blocks).
    - Compare memory efficiency with malloc/free.