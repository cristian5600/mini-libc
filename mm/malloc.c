// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
// *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
void *malloc(size_t size)
{
	
	struct mem_list *block = mem_list_find(NULL);
    if (block != NULL && block->len >= size) {
        // Found a memory block in the list
        void *ptr = block->start;
        block->start += size;
        block->len -= size;
        if (block->len == 0) {
            // Remove empty memory block from list
            mem_list_del(ptr);
        }
        return ptr;
    } else {
        // No suitable memory block found in the list, use mmap
        struct mem_list *new_block = mmap(NULL, size + sizeof(struct mem_list), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
        if (new_block == MAP_FAILED) {
            // mmap failed, set errno and return NULL
            errno = ENOMEM;
            return NULL;
        } else {
            new_block->start = new_block + 1;
            new_block->len = size;
            mem_list_add(new_block->start, new_block->len);
            return new_block->start;
        }
    }
}

void *calloc(size_t nmemb, size_t size)
{
	// Calculate the total amount of memory needed
    size_t total_size = nmemb * size;
    
    // Allocate memory
    void *ptr = malloc(total_size);
    if (ptr == NULL) {
        // malloc failed, return NULL
        return NULL;
    }
    
    // Initialize memory to zero
    unsigned char *p = ptr;
    for (size_t i = 0; i < total_size; i++) {
        *p++ = 0;
    }
    
    return ptr;
}


void free(void *ptr){
	 if (ptr == NULL) {
        return;
    }
    
    // Find the memory block that ptr points to
    struct mem_list *block = mem_list_find(ptr);
    if (block == NULL) {
        errno = EINVAL;
        return;
    }
    
    // Remove the block from the memory list
    if (mem_list_del(ptr) == -1) {
        errno = EINVAL;
        return;
    }
    
    // Deallocate the block's memory
    if (munmap(ptr, block->len) == -1) {
        errno = ENOMEM;
    }
}

void *realloc(void *ptr, size_t size)
{
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    if (ptr == NULL) {
        return malloc(size);
    }

    struct mem_list *block = mem_list_find(ptr);

    if (block == NULL) {
        // ptr does not point to a valid block, equivalent to malloc(size)
        return malloc(size);
    }

    void *new_ptr = malloc(size);
    if (new_ptr == NULL) {
        // malloc failed, set errno and return NULL
        errno = ENOMEM;
        return NULL;
    }

    memcpy(new_ptr, ptr, block->len);
    free(ptr);

    return new_ptr;
}  
	

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
	return NULL;
}
