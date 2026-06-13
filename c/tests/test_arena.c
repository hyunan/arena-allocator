#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include "arena.h"

static void test_init(void) {
    Arena arena;

    assert(arena_init(&arena, 128));
    assert(arena.buffer != NULL);
    assert(arena.capacity == 128);
    assert(arena.offset == 0);

    arena_free(&arena);
}

static void test_basic_alloc(void) {
    Arena arena;
    assert(arena_init(&arena, 128));

    void *ptr = arena_alloc(&arena, 32);
    assert(ptr != NULL);
    assert(arena_used(&arena) == 32);
    assert(arena_remaining(&arena) == 128 - 32);

    arena_free(&arena);
}

static void test_free_clears_arena(void) {
    Arena arena;
    assert(arena_init(&arena, 128));

    arena_free(&arena);

    assert(arena.buffer == NULL);
    assert(arena.capacity == 0);
    assert(arena.offset == 0);
}

static void test_alloc_over_capacity(void) {
    Arena arena;
    assert(arena_init(&arena, 128));

    void *ptr1 = arena_alloc(&arena, 120);

    assert(ptr1 != NULL);

    void *ptr2 = arena_alloc(&arena, 10);
    assert(ptr2 == NULL);
    assert(arena_used(&arena) == 120);

    arena_free(&arena);
}

static void test_arena_reset(void) {
    Arena arena;
    assert(arena_init(&arena, 128));
    void *ptr = arena_alloc(&arena, 64);
    assert(ptr != NULL);
    assert(arena.offset == 64);
    arena_reset(&arena);

    assert(arena.offset == 0);
    assert(arena_remaining(&arena) == 128);

    arena_free(&arena);
}

static void test_arena_alloc_aligned(void) {
    Arena arena;
    arena_init(&arena, 24);
    void *ptr = arena_alloc(&arena, 4);
    assert(arena.offset == 4);
    ptr = arena_alloc_aligned(&arena, 4, 16);
    assert(arena.offset == 20);
    assert((uintptr_t) ptr % 16 == 0);

    arena_free(&arena);
}

static void test_arena_alloc_aligned_over_capacity(void) {
    Arena arena;
    assert(arena_init(&arena, 16));
    void *a = arena_alloc(&arena, 15);
    assert(a != NULL);

    void *b = arena_alloc_aligned(&arena, 2, 8);
    assert(b == NULL);
    assert(arena.offset == 15);

    arena_free(&arena);
}

int main(void) {
    test_init();
    test_basic_alloc();
    test_free_clears_arena();
    test_alloc_over_capacity();
    test_arena_reset();
    test_arena_alloc_aligned();
    test_arena_alloc_aligned_over_capacity();

    printf("All arena tests passed!\n");
    return 0;
}