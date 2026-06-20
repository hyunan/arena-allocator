#include <cassert>
#include <cstdint>
#include <iostream>

#include "arena.h"

static bool is_aligned(void* ptr, std::size_t alignment) {
    return reinterpret_cast<std::uintptr_t>(ptr) % alignment == 0;
}

static void test_constructor() {
    Arena arena(128);

    assert(arena.capacity() == 128);
    assert(arena.used() == 0);
    assert(arena.remaining() == 128);
}

static void test_alloc() {
    Arena arena(128);

    void* ptr = arena.alloc(16);

    assert(ptr != nullptr);
    assert(arena.used() == 16);
    assert(arena.remaining() == 112);
}

static void test_alloc_multiple() {
    Arena arena(128);

    void* a = arena.alloc(16);
    void* b = arena.alloc(16);

    assert(a != nullptr);
    assert(b != nullptr);
    assert(a != b);

    assert(arena.used() == 32);
    assert(arena.remaining() == 96);
}

static void test_alloc_exact_capacity() {
    Arena arena(32);

    void* ptr = arena.alloc(32);

    assert(ptr != nullptr);
    assert(arena.used() == 32);
    assert(arena.remaining() == 0);
}

static void test_alloc_over_capacity() {
    Arena arena(32);

    void* a = arena.alloc(32);
    void* b = arena.alloc(1);

    assert(a != nullptr);
    assert(b == nullptr);

    assert(arena.used() == 32);
    assert(arena.remaining() == 0);
}

static void test_reset() {
    Arena arena(64);

    void* a = arena.alloc(32);
    assert(a != nullptr);
    assert(arena.used() == 32);

    arena.reset();

    assert(arena.used() == 0);
    assert(arena.remaining() == 64);

    void* b = arena.alloc(64);
    assert(b != nullptr);
    assert(arena.used() == 64);
}

static void test_alloc_aligned_basic() {
    Arena arena(128);

    void* ptr = arena.alloc_aligned(16, 8);

    assert(ptr != nullptr);
    assert(is_aligned(ptr, 8));
}

static void test_alloc_aligned_after_unaligned_alloc() {
    Arena arena(128);

    void* a = arena.alloc(1);
    void* b = arena.alloc_aligned(16, 8);

    assert(a != nullptr);
    assert(b != nullptr);
    assert(is_aligned(b, 8));

    assert(arena.used() >= 17);
}

static void test_alloc_aligned_multiple_alignments() {
    Arena arena(256);

    void* a = arena.alloc_aligned(4, 4);
    void* b = arena.alloc_aligned(8, 8);
    void* c = arena.alloc_aligned(16, 16);
    void* d = arena.alloc_aligned(32, 32);

    assert(a != nullptr);
    assert(b != nullptr);
    assert(c != nullptr);
    assert(d != nullptr);

    assert(is_aligned(a, 4));
    assert(is_aligned(b, 8));
    assert(is_aligned(c, 16));
    assert(is_aligned(d, 32));
}

static void test_alloc_aligned_exact_remaining_space() {
    Arena arena(16);

    void* ptr = arena.alloc_aligned(16, 8);

    assert(ptr != nullptr);
    assert(is_aligned(ptr, 8));
    assert(arena.used() == 16);
    assert(arena.remaining() == 0);
}

static void test_alloc_aligned_over_capacity() {
    Arena arena(16);

    void* a = arena.alloc(15);
    void* b = arena.alloc_aligned(2, 8);

    assert(a != nullptr);
    assert(b == nullptr);

    assert(arena.used() == 15);
    assert(arena.remaining() == 1);
}

static void test_alloc_aligned_does_not_advance_on_failure() {
    Arena arena(16);

    void* a = arena.alloc(15);
    assert(a != nullptr);

    std::size_t used_before = arena.used();

    void* b = arena.alloc_aligned(8, 8);

    assert(b == nullptr);
    assert(arena.used() == used_before);
}

static void test_destructor_runs() {
    {
        Arena arena(64);
        void* ptr = arena.alloc(16);
        assert(ptr != nullptr);
    }
}

int main() {
    test_constructor();

    test_alloc();
    test_alloc_multiple();
    test_alloc_exact_capacity();
    test_alloc_over_capacity();

    test_reset();

    test_alloc_aligned_basic();
    test_alloc_aligned_after_unaligned_alloc();
    test_alloc_aligned_multiple_alignments();
    test_alloc_aligned_exact_remaining_space();
    test_alloc_aligned_over_capacity();
    test_alloc_aligned_does_not_advance_on_failure();

    test_destructor_runs();

    std::cout << "All tests passed.\n";
}