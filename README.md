# C++ Go Fast

Based on [What Every Programmer Should Know About Memory](https://www.gwern.net/docs/cs/2007-drepper.pdf)

# What Programmers Can Do

## Bypassing the Cache (p. 47)

- non-temporal access(NTA) operations -> data will not be reused soon
- less cache pollution

## Cache Access 

### L1d (p. 49)

- better locality:
    - spatial:
        - use full cache line more effectively -> for loops
        - when binary generic -> biggest cache line size expected
        - put often used elements together + keep not together used data apart -> less cache pollution
        - variables used together -> store together -> fewer conflict misses
    - temporal:
        - keep often used data together
        - pull common expressions out of inner loops as far down as possible
    - `restrict` pointer -> promises that this pointer doesn't have any aliases
- align code and data:
    - struct layout:
        - pahole program -> make structs align to cache lines
        - move struct elements most likely to be the critical word to beginning
        - access elements of struct in order of definition -> arrange elements in most likely accessed order
        - for bigger structs -> apply rules for each cache line-sized block
    - struct alignment:
        - each data type has own alignment requirement
        - structs use largest alignment of elements -> allocated object might not be aligned to cache line
        - can be changed with variable attribute for object allocated by compiler `struct strtyype varialbe __attribute((aligned(64));`
        - or `struct strtype {...} __attribute(aligned(64));`
        - `posix_memalign` and `alignof` for dynamic allocation
        - might lead to fragmentation
    - alignment requirements:
        - variable length arrays (VLAs) -> active alignment control -> slower
        - relaxed alignment requirement for tail functions (call no other functions) and no multimedia operations + functions only calling functions without alignment requirement
        - `-mpreferred-stack-boundary=2` -> stack will be aligned to 2^N bytes; default is N=4
        - can reduce code size; improve execution speed
- SIMD

### L1i (p. 55)

- reduce code footprint:
    - `-Os` good when loop unrolling and inlining not effective
    - `-finlinelimit` -> when function too large for inlining
    - `noinline` function attribute -> when function called often from different locations -> branch prediction may better -> branch prediction unit already saw code
- linear without bubbles:
    - loop unrolling, inlining -> `-02`/`-O3`
    - always inline function only called once -> `always_inline` function attribute
- branch prediction:
    - jumps bad; instructions cached in decoded form
    - jump target might not be static; even if static, memory fetch might miss all caches
    - lopsided conditional execution -> false static branch prediction -> bubbles in pipeline
    - profile-guided optimization
    - `#define unlikely(expr) __builtin_expect(!!expr), 0)` `#define likely(expr) __builtin_expect(!!expr), 1)` + `-freorder-blocks` (used by `-O2` + `-O3` but not by `-Os`) doesn't work with exception handling
    - compact loops have advantages
- align code when sensible:
    - instruction at beginning of cache line good
    - alignment good when:
        - at beginning of functions
        - blocks only reachable by jumps
        - sometimes at beginning of loops -> requires gap -> filled with no-op instructions or unconditional jump
        - `-falign-functions=N`, `-falign-jumps=N`, `-falign-loops=N` -> align all functions, jumps, loops to next power-of-two greater than N -> gap of N bytes
        - N=1 -> disable alignment or `-fno-align-functions`

### L2+

- working set size for more than one use matched to cache size -> work on bigger problems in smaller pieces
- hardcode cache line size
- higher level cache size can vary widely -> cod must adjust dynamically
- instructions and libraries use higher level cache too
- `/sys/devices/system/cpu/cpu*/cache` for safe lower limit (p. 59)

### TLB

- page optimization for both page faulst and TLB misses
- widely varying locations in address space -> more directories
- Address Space Layout Randomization (ASLR) slow

## Prefetching

### Hardware Prefetching (p. 60)

- at least two cache misses start prefetching
- can't cross page boundaries
- keep unrelated data out -> less cache pollution

### Software Prefetching (p. 61)

- `_mm_prefetch` intrinsic on pointer -> prefetch
- `-fprefetch-loop-arrays` -> prefetch if sensible -> bad for small arrays

### Speculation (p. 62)

### Helper Threads (p. 63)

### Direct Cache Access (p. 64)

## Multi-Thread

### Concurrency (p. 65)

- goal: fewer RFO messages
- grouping:
    - group "constant" variables (change very rarely) -> always mark with `const` if possible
    - group variables used together by same thread -> `int bar __attribute__((section(".data.ro"))) = 2;` -> ".data." prefix guarantees place together with other data sections; rest arbitrary
    - separate read-only, read-write (and read-mostly)
    - group read-write in struct -> only way of ensuring close memory locations
    - read-write often written by different threads own cache line -> padding
- TLS:
    - thread-local storage (TLS) `__thread int bar = 2;` -> stored separately for each thread -> costs time when thread created
    - thread-local variables are addressable by other threads but unless pointer passed, no way to find
    - shift over more expensive -> copy required
    - when only one thread uses variable -> wasted resources
    - good when multiple threads independent use

### Atomicity (p. 68)

- Bit Test
- Load Lock / Store Conditional (LL/SC)
- Compare-and-Swap (CAS) -> expensive
- Atomic Arithmetic -> still expensive (~200 cycles)

### Bandwidth (p. 70)

- place thread better -> thread affinity: assign thread to one or more cores

## NUMA (p. 72)

# Memory Performance Tools (p. 78)

- relate multiple counter to each other
- divisor is measure of processing time, number of clock cycles or number of instructions
- CPI (cycle per instruction):
    - not limited by memory bandwidth significantly below 1.0
    - L1d not large enough -> 3.0
    - L2 not sufficient -> 20.0
    - average over all instructions

- Perf
- Pahole
- pfmon

## oprofile

- systemwide

Chapter 6.5 NUMA Programming is missing.

## Requirements
  - python
    - numpy
    - pandas
    - matplotlib
  - c/c++
    - gcc/g++
  - OS
    - linux 
  