#ifndef CACHE_H
#define CACHE_H

#include <cstddef>
#include <vector>

struct CacheLine {
    size_t tag;
    bool valid;
};

void cache_init(size_t l1_lines, size_t l2_lines, size_t block_size);
void cache_reset();
void cache_access(size_t addr);
void cache_stats();

#endif
