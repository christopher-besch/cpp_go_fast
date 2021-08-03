# C++ Go Fast

Based on [What Every Programmer Should Know About Memory](https://www.gwern.net/docs/cs/2007-drepper.pdf)

# What Programmers Can Do

## Bypassing the Cache (p. 47)

- non-temporal access(NTA) operations -> data will not be reused soon
- less cache pollution

## Cache Access (p. 49)

- better locality
    - spatial
        - keep often used data together
        - use full cache line more effectively
        - when binary generic -> biggest cache line size expected
    - temporal
        - keep often used data together
        - pull common expressions out of inner loops as far down as possible
    - `restrict` pointer -> promises that this pointer doesn't have any aliases
- align code and data
    - pahole program -> make structs align to cache lines
    - move struct elements most likely to be the critical word to beginning
    - access elements of struct in order of definition -> arrange elements in most likely accessed order
    - for bigger structs -> apply rules for each cache line-sized block
    - each data type has own alignment requirement
    - structs use largest alignment of elements -> allocated object might not be aligned to cache line
    - can be changed with variable attribute for object allocated by compiler `struct strtyype varialbe __attribute((aligned(64));`
    - or `struct strtype {...} __attribute(aligned(64));`
    - `posix_memalign` and `alignof` for dynamic allocation
    - might lead to fragmentation
- SIMD

### TLB

## Prefetching

### Hardware Prefetching

### Software Prefetching

### Speculation

### Helper Threads

### Direct Cache Access

## Multi-Thread

### Concurrency

### Atomicity

### Bandwidth

# Memory Performance Tools

- Perf
- Pahole

Chapter 6.5 NUMA Programming is missing.
