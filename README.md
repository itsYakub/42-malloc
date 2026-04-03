# malloc - A rather UNIX project

## Getting started

`malloc` - mini project about writing a dynamic allocation memory management library.

It includes standard C library functions for dealing with dynamic memory allocation:

- `malloc` - allocates n-number of bytes and returns a pointer to the allocated, uninitialized memory.
- `free` - frees the memory space pointed to by the pointer argument.
- `realloc` - re-allocated the memory pointer by the pointer argument by n-number of bytes and frees the old pointer.
- `show_alloc_mem` - mini memory-agnostics functions for showing the state of process's allocations and deallocations.

## General idea

Idea behind the allocator is pretty simple.

The hole idea behind it is as follows: *we allocate memory pool which then we fill with arbitraty data*.

Now let's break it down...

Allocator expects 3 kinds of input:

- `TINY` size - input from 1 to N number of bytes;
- `SMALL` size - input from N+1 to M number of bytes;
- `LARGE` size - input from M+1 to arbitrary number of bytes;

These sizes are defined using C preprocessor, as follows:
- `N` = `FT_MALLOC_TINY_SIZE`;
- `M` = `FT_MALLOC_SMALL_SIZE`;

The whole idea is based on data being stored in allocated metadata and the concept of "memory blocks" (subject.pdf calls it "zones").

Each memory block, instead of `LARGE` ones, allocates a memory pool that can fit at least 100 max-sized memory chunks.

"Memory chunk" is basically a segment of memory block's pool that consists of both metadata and pointed memory.

All the blocks and chunks are made using linked lists which points to another metadata of the same type. Purely to avoid reallocations of memory pool which would cause the whole allocator to break in an instant.

I've mentioned memory pools not being applied to `LARGE` blocks. It's due to the fact we don't know the max size of `LARGE` chunk.

Thus, `LARGE` block is basically a linked list of chunks, each `mmap`'ed on every call. It's crucial, because `TINY` and `SMALL` performs an allocation only when the new block is created.

It's made that way for a sake of performance; each call to `mmap` cuases "context-switch" from "user mode" to "kernel mode" and then back to "user mode". That's why memory pools are so handy.

Conceptually, this memory pool concept is similar to `arena`'s.

Deallocation isn't complicated either. For each `TINY` or `SMALL` chunk we simply memset the memory area to 0 and set the size to 0.

When there's no chunk in the block, we deallocate it using `munmap`.

Deallocating `LARGE` blocks is even simpler; just deallocate linked list's node. Occassionaly tinker with neighbouring nodes to not lose any data.

Worth mentioning is that I'm not reusing chunks. I've chosen it that way to not reuse invalid pointers and potentially cause working use-after-free scenario:

```c
/* ... */

int *a = malloc(4); /* let's say: allocate pointer at 0x7ff123 of size 4 */

int *b = malloc(8); /* let's say: allocate pointer at 0x7ff456 of size 8 */

free(a); /* now pointer 0x7ff123 should be unusable */

int *c = malloc(4); /* if I were to reuse memory, this would become 0x7ff123!!! */

free(b); /* then this would release 0x7ff456 */

free(c); /* and this would release 0x7ff123. which could be done using `free(a)` as well!!! */

/* ... */
```

## Licence

This project is licenced under the [GNU LESSER GENERAL PUBLIC LICENCE](./LICENCE).
