// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAP_ANONYMOUS 0x20

void *malloc(size_t size)
{
	if (size == 0) {
		return NULL;
	}
	//https://elixir.bootlin.com/musl/latest/source/src/malloc/mallocng/malloc.c
	//pentru liniile 19-21
	void *p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (p == MAP_FAILED)
		return NULL;

	if (mem_list_add(p, size) == -1) {
        // In caz de eșec la adaugare, elibereaza memoria si returneaza NULL.
        munmap(p, size);
        return NULL;
    }

	return p;
}
//https://danluu.com/malloc-tutorial/
//pentru calloc
void *calloc(size_t nmemb, size_t size)
{
	if (size == 0) {
		return NULL;
	}
	long total_size = nmemb * size;
    void *ptr = malloc(total_size);
    if (ptr != NULL) {
        memset(ptr, 0, total_size);
    }
    return ptr;
}

void free(void *ptr)
{
    if (ptr == NULL) {
        return;
    }
    struct mem_list *block = mem_list_find(ptr);
    if (block == NULL) {
        return;
    }
    mem_list_del(ptr);
    if (munmap(ptr, block->len) == -1) {
        return;
    }
}

//https://danluu.com/malloc-tutorial/ pentru realloc
void *realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return malloc(size);
	if (size == 0) {
		free(ptr);
		return NULL;
	}
	void *p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (p == MAP_FAILED)
		return NULL;
	memcpy(p, ptr, size);
	munmap(ptr, 0);
	return p;
}

//https://elixir.bootlin.com/musl/latest/source/src/malloc/reallocarray.c
void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	if (size && nmemb > -1 / size) {
		errno = ENOMEM;
		return 0;
	}
	return realloc(ptr, nmemb * size);
}
