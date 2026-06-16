#include <stdlib.h>

#include "arena.h"


bool arena_init(Arena *arena, size_t capacity) {
    arena->buffer = malloc(capacity);

    if (!arena->buffer)
        return false;

    arena->capacity = capacity;
    arena->offset = 0;

    return true;
}

void *arena_alloc(Arena *arena, size_t size) {
    if (!arena || arena->offset + size > arena->capacity)
        return NULL;
    
    void *ptr = arena->buffer + arena->offset;
    arena->offset += size;

    return ptr;
}

void *arena_alloc_aligned(Arena *arena, size_t size, size_t alignment) {
    if (!arena || alignment == 0)
        return NULL;

    size_t mod = arena->offset % alignment;
    size_t padding = mod ? alignment - mod : 0;
    if (arena->offset + padding + size > arena->capacity)
        return NULL;
    
    void *ptr = arena->buffer + arena->offset + padding;
    arena->offset += size + padding;

    return ptr;
}

void arena_reset(Arena *arena) {
    if (!arena)
        return;

    arena->offset = 0;
}

void arena_free(Arena *arena) {
    if (!arena)
        return;
    
    free(arena->buffer);
    arena->buffer = NULL;
    arena->capacity = 0;
    arena->offset = 0;
}

size_t arena_used(const Arena *arena) {
    return arena->offset;
}

size_t arena_remaining(const Arena *arena) {
    return arena->capacity - arena->offset;
}
