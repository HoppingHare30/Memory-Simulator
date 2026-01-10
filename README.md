# Memory & Cache Simulator (C++)

## Overview
A simplified OS memory and cache simulator implemented in C++. It models allocation strategies, fragmentation behavior, free/coalescing, and a two-level cache hierarchy with FIFO replacement and hit/miss statistics. The goal is to demonstrate core OS concepts in a clean, testable environment.

## Demo Video Link: https://drive.google.com/file/d/17p1ryybO_k7kHhGOaLALfVS0RQ-6qf_C/view?usp=share_link

## Features
- First Fit, Best Fit, Worst Fit allocation
- Free + coalescing of adjacent blocks
- External fragmentation metrics
- Two-level cache (L1 → L2 → Memory)
- FIFO replacement policy
- Hit/miss ratios and miss propagation
- Interactive REPL interface
- Workload-based testing
- Clean modular code structure
- Statistics and reporting

## Build Instructions
Requires g++ with C++11.

Build:
make

Run:
./memsim

## Commands (REPL)
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

## Test Workloads
Located in tests/ directory:

alloc_workload.txt — allocation and fragmentation behavior  
cache_workload.txt — locality + hit/miss demonstration  
mixed_workload.txt — combined behavior

## Documentation
Design document available at:
docs/design.md

## Architecture Summary
Memory subsystem:
- Linear byte-addressable heap
- Vector-based block tracking
- Free + coalesce on deallocation

Cache subsystem:
- Two levels (L1/L2)
- FIFO replacement
- Block-aligned tag mapping
- Hit/miss counters
- Miss propagation statistics

## Limitations
- No paging or virtual memory
- No TLB
- No associativity
- No buddy allocator
- No multithreading

## Future Work
- Virtual memory + page tables
- TLB and paging faults
- LRU/LFU cache policies
- Buddy allocator
- Set associative caches

## Author
HoppingHare30 (GitHub)
