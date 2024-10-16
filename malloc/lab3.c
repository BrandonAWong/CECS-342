#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Block {
    int block_size;
    struct Block* next_block;
};

const int OVERHEAD_SIZE = sizeof(struct Block); // refers to size & pointer of a block
const int POINTER_SIZE = sizeof(void*);
struct Block* free_head; // always points to the first free block

void my_initialize_heap(int size) {
    free_head = malloc(size); 
    free_head->block_size = size;
    free_head->next_block = NULL;
}

void* my_alloc(int size) {
    if (size <= 0) {
        printf("Size must be greater than 0\n");
        return 0;
    }

    // size must be a multiple of POINTER_SIZE. So, if pointer_size is 4, size
    // must be at least 4, 8, 12... 
    if (size % POINTER_SIZE) {
        printf("Size must be a multiple of pointer size { %d }\n", POINTER_SIZE);
        //return 0;
    }

    // Iterators
    struct Block* curr = free_head;
    struct Block* prev = 0;
    bool found = false;

    // Iterare through each node, if a node has equal or more space than
    // necessary to hold size, use that node.
    while (curr != NULL) {
        if(curr->block_size >= size) {
            found = true;
            // Determine if the current block can be split.
            if (curr->block_size > size + OVERHEAD_SIZE + POINTER_SIZE) { // Splittable
                // Create a pointer to the newly split block's position
                // then assign its structure members.
                struct Block* splitBlock = (struct Block*)(char*)curr+ size + OVERHEAD_SIZE;
                splitBlock->block_size = curr->block_size - size;
                splitBlock->next_block = curr->next_block;
                
                // Update Curr's block size as a result of splitting.
                curr->block_size = curr->block_size - splitBlock->block_size;
                curr->next_block = splitBlock;
                
                // Adjust the double linked list, depending on whether curr is the head or not.
                if (curr == free_head) {
                     prev = curr;
                     free_head = splitBlock;
                     curr = splitBlock;
                }
            }
            else { // Not splittable
                // If curr is the head, curr's next block is the new head.
                if (curr == free_head) {
                    free_head = curr->next_block;
                }
                // If curr is not the head, the previous block points to curr's next block.
                else {
                    prev = curr->next_block; 
                }
            }
            // Since we found a block, no need to keep searching.
            break;
        }

        // Haven't found an available space yet.
        else {
            prev = curr;
            curr = curr->next_block;
        }
    } 
    // Return a pointer to the allocated data, if possible.
    return curr;
}

void my_free(void* data) {
    struct Block* freed_block = (struct Block*)((char*)data - OVERHEAD_SIZE);
    freed_block->next_block = free_head;
    free_head = freed_block;
}

void menuOptionOne() {
    int *numOne = my_alloc(sizeof(int));
    printf("Address of int A: %p\n", numOne);
    my_free(numOne);
    int *numTwo = my_alloc(sizeof(int));
    printf("Address of int B: %p\n", numTwo);
}

//Allocate two ints and print their addresses; they should be exactly the size of
// your overhead plus the larger of (the size of an integer; the minimum block size) apart.
void menuOptionTwo() {
    int *numOne = my_alloc(sizeof(int));
    printf("Address of int A: %p\n", numOne);
    int *numTwo = my_alloc(sizeof(int));
    printf("Address of int B: %p\n", numTwo);
    printf("Verifying Results...\n");
    int overheadPlusLarger = OVERHEAD_SIZE + sizeof(void*);
    printf("Size of overhead + larger of (the size of an integer; the minimum block size): %d bytes\n", overheadPlusLarger);
    printf("Address B - Address A: %d bytes \n", *numTwo - *numOne);
}

//Allocate three ints and print their addresses, then free the second of the three. Allocate an array of 2
//double values and print its address (to allocate an array in C, allocate (2 *sizeof(double)); verify
//that the address is correct. Allocate another int and print its address; verify that the address is the
//same as the int that you freed.
void menuOptionThree() {
    int *numOne = my_alloc(sizeof(int));
    printf("Address of int A: %p\n", numOne);
    int *numTwo = my_alloc(sizeof(int));
    printf("Address of int B: %p\n", numTwo);
    int *numThree = my_alloc(sizeof(int));
    printf("Address of int C: %p\n", numThree);
    my_free(numTwo);
    printf("After freeing int B...\n");
    double *arr = my_alloc(2 * sizeof(double));
    printf("Address of array of 2 double values: %p\n", arr);
    int *numFour = my_alloc(sizeof(int));
    printf("Address of int D (should be the int B): %p\n", numFour);
}

//Allocate one char, then allocate one int, and print their addresses. They should be exactly the same
//distance apart as in test #2.
void menuOptionFour() {
    int check = 0;
    char *charOne = my_alloc(sizeof(char));
    printf("Address of char A: %p\n", charOne);
    int *numTwo = my_alloc(sizeof(int));
    printf("Address of int B: %p\n", numTwo);
    int overheadPlusLarger = OVERHEAD_SIZE + sizeof(void*);
    printf("Size of overhead + larger of (the size of an integer; the minimum block size): %d\n", overheadPlusLarger);
}

//Allocate space for a 80-element int array, then for one more int value. Verify that the address of
//the int value is 80 * sizeof(int) + the size of your header after the array's address. Free the array.
//Verify that the int's address and value has not changed.
void menuOptionFive() {
    int *arr = my_alloc(80 * sizeof(int));
    int *numOne = my_alloc(sizeof(int));
    printf("Address of array: %p\n", arr);
    printf("Address of int A: %p\n", numOne);
    printf("Address of int value: %p\n", arr + 80 + sizeof(int));
    printf("Value of int A: %d\n", *numOne);
    printf("Difference betwween array and int A: %d\n", *numOne - *arr);
    my_free(arr);
    printf("After freeing array...\n");
    printf("Address of int value: %p\n", numOne);
    printf("Value of int A: %d\n", *numOne);
}

int main() {
    int menuChoice = 0;
    int runAgain = 1;
    while (runAgain == 1) {
        printf("\n1. Allocate an int \n2. Allocate two ints \n3. Allocate three "
        "ints \n4. Allocate one char \n5. Allocate space for an 80-element int array \n6. "
        "Quit \nChoose a menu option: ");
        scanf("%d", &menuChoice);
        printf("\n---Test Case %d---\n", menuChoice);
        my_initialize_heap(1000);
        if (menuChoice == 1) {
            menuOptionOne();
        }
        else if (menuChoice == 2) {
            menuOptionTwo();
        }
        else if (menuChoice == 3) {
            menuOptionThree();
        }
        else if (menuChoice == 4) {
            menuOptionFour();
        }
        else if (menuChoice == 5) {
            menuOptionFive();
        }
        else if (menuChoice == 6) {
            printf("Done!\n");
            runAgain = 0;
        }
    }
    return 0;
}
