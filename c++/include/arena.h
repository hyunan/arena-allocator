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

    Arena(const Arena& other) = delete;
    Arena& operator=(const Arena& other) = delete;

    Arena(Arena&& other) = delete;
    Arena& operator=(Arena&& other) = delete;

    void* alloc(std::size_t size);
    void* alloc_aligned(std::size_t size, std::size_t alignment);
    void reset();

    std::size_t used() const;
    std::size_t remaining() const;

    std::size_t capacity() const;
    std::size_t offset() const;
};

#endif
