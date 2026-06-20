# Arena Allocator

An implementation of the Arena Allocator in C and C++.

## Why Arena Allocator?

Advantages:

- Very fast allocation
- No per-allocation heap overhead
- Easy bulk deallocation through reset

Tradeoffs:

- Individual allocations cannot be freed
- Memory is reclaimed all at once

Essentially reserves a whole block of memory and just uses pointer arithmetic rather than new allocations each call. This makes it much more efficient.

## Project Structure
```
├── c
│   ├── examples
│   │   └── main.c
│   ├── include
│   │   └── arena.h
│   ├── Makefile
│   ├── src
│   │   └── arena.c
│   └── tests
│       └── test_arena.c
├── c++
│   ├── arena_example
│   ├── arena_test
│   ├── examples
│   │   └── main.cpp
│   ├── include
│   │   └── arena.h
│   ├── Makefile
│   ├── src
│   │   └── arena.cpp
│   └── tests
│       └── test_arena.cpp
└── README.md
```

## Building and running

To build the arena file with my example, in either C or C++ directory:
```
make
```

You can also run the tests I made:
```
make test
```

## Example usage:
```C++
Arena arena(1024);

void* ptr = arena.alloc(64);

arena.reset();
```
