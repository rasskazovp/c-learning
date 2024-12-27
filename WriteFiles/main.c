#include <stdio.h>
#include <stdlib.h>

void * my_malloc(size_t size);
void my_free(void * ptr);

struct BlockMetadata {
    size_t size;             // Size of the memory block
    int is_free;             // Whether the block is free or allocated
    struct BlockMetadata* next; // Pointer to the next block
};

int main(){

    int n = 5; // Number of integers
    int* arr = (int*)malloc(n * sizeof(int)); // Allocate memory for 5 integers

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1; // Exit program if malloc fails
    }

    // Initialize and use the allocated memory
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(arr);

}