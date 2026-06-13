#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Arena {
    unsigned char *buffer;
    size_t capacity;
    size_t offset;
} Arena;

bool arena_init(Arena *arena, size_t capacity);

void *arena_alloc(Arena *arena, size_t size);

void *arena_alloc_aligned(Arena *arena, size_t size, size_t alignment);

void arena_reset(Arena *arena);

void arena_free(Arena *arena);

size_t arena_used(const Arena *arena);

size_t arena_remaining(const Arena *arena);

#endif
