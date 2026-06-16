#ifndef ARENA_H
#define ARENA_H

#include <cstddef>

class Arena {
private:
    char* buffer_;
    std::size_t capacity_;
    std::size_t offset_;

public:
    Arena(std::size_t capacity);
    ~Arena(); // same as arena_free

    void* alloc(std::size_t size);
    void* alloc_aligned(std::size_t size, std::size_t offset);
    void reset();

    std::size_t used(const Arena& arena);
    std::size_t remaining(const Arena& arena);
};

#endif
