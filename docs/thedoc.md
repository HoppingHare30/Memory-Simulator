# Memory Management & Cache Simulator (C++)

## Overview
This project implements a simplified operating systems memory and cache simulator in C++. It models dynamic memory allocation strategies, fragmentation behavior, free and coalescing behavior, and a two-level cache hierarchy with FIFO replacement and hit/miss statistics. The goal is to demonstrate core OS memory concepts without relying on OS-level memory management.

## Architecture
The simulator contains two main components:

1. Allocation subsystem
2. Cache subsystem

A command-line REPL interface allows interactive testing and workloads.

---

## Allocation Subsystem
Memory is represented as a linear heap of user-defined size. Each segment is tracked using a vector of blocks containing:

• start address  
• size in bytes  
• free/used flag  
• allocation ID

After allocation or free, adjacent free blocks are coalesced.

### Supported Allocation Policies
1. First Fit — finds the first block large enough to satisfy the request.
2. Best Fit — selects the smallest free block that fits to reduce external fragmentation.
3. Worst Fit — selects the largest free block to preserve large spaces for future allocations.

Policies are selected at runtime using:  
`set <first|best|worst>`

### Freeing Strategy
`free <id>` marks a block as free and merges adjacent free blocks to reduce fragmentation.

---

## Fragmentation Metrics

### Internal Fragmentation
Internal fragmentation is effectively zero because allocation is byte-accurate.

### External Fragmentation
External fragmentation is reported as:
external = 1 - (largest_free / total_free)

### Utilization
utilization = used / total

Metrics are reported with:
`stats`

---

## Cache Subsystem
The simulator models a two-level cache hierarchy:

L1 → L2 → Memory

Each level is configurable by:
`cache init <l1_lines> <l2_lines> <block_size>`

### Address Mapping
Request addresses are aligned to block boundaries:
tag = addr - (addr % block_size)

### Replacement Policy
Both cache levels use FIFO replacement. On an L1 miss, L2 is probed. On an L2 miss, a memory fetch occurs. Miss propagation counters track these events.

### Cache Statistics
The simulator reports:
• L1 hit/miss
• L2 hit/miss
• hit ratios per level
• miss propagation to memory

Statistics reported via:
`cache_stats`

---

## REPL Commands
Supported commands:

init <bytes>  
set <first|best|worst>  
malloc <bytes>  
free <id>  
dump  
stats  
cache init <l1> <l2> <block>  
cache reset  
access <addr>  
cache_stats  
exit  

---

## Build & Run Instructions

Build:
make

Run:
./memsim

---

## Test Workloads
Test workloads simulate:
• allocation patterns
• fragmentation behavior
• spatial/temporal locality
• cache hit/miss dynamics

Workloads are located in the tests/ directory.

---

## Limitations
• No paging or virtual memory
• No TLB model
• No buddy allocator
• No associativity in caches
• No multi-threading

---

## Future Extensions
Potential future additions:
• Virtual memory + page tables
• TLB and page faults
• LRU or LFU cache replacement
• Set associative caches
• Buddy allocator

---

## Conclusion
This simulator demonstrates essential OS concepts: allocation strategies, fragmentation measurement, hierarchical caching, replacement policies, and workload-driven performance statistics. It provides a compact, controlled environment for understanding memory management behavior without kernel-level programming.
