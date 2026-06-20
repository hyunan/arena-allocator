#include <cstdlib>
#include <new>

#include "arena.h"

Arena::Arena(std::size_t size) : buffer_{nullptr}, capacity_{size}, offset_{0} {
    // buffer_ = static_cast<char*>(std::aligned_alloc(32, size));
    buffer_ = static_cast<char*>(::operator new(capacity_, std::align_val_t{64})); // this is new way to allocate aligned memory in C++17
}

Arena::~Arena() {
    // std::free(buffer_);
    ::operator delete(buffer_, std::align_val_t{64});
    buffer_ = nullptr;
    capacity_ = 0;
    offset_ = 0;
}



void* Arena::alloc(std::size_t size) {
    if (capacity_ - offset_ < size)
        return nullptr;
    
    void* ptr = buffer_ + offset_;
    offset_ += size;
    return ptr;
}

void* Arena::alloc_aligned(std::size_t size, std::size_t alignment) {
    if (capacity_ - offset_ < size)
        return nullptr;

    size_t remain = offset_ % alignment;
    size_t padding = remain ? alignment - remain : 0;
    if (capacity_ - offset_ < size + padding)
        return nullptr;
    
    void* ptr = buffer_ + offset_ + padding;
    offset_ += size + padding;
    return ptr;
}

void Arena::reset() {
    offset_ = 0;
}

std::size_t Arena::used() const {
    return offset_;
}

std::size_t Arena::remaining() const {
    return capacity_ - offset_;
}

std::size_t Arena::capacity() const {
    return capacity_;
}

std::size_t Arena::offset() const {
    return offset_;
}
