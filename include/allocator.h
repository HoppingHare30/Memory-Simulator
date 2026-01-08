#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>
#include <vector>
#include <string>

struct Block {
    size_t start;
    size_t size;
    bool free;
    int id;
};

enum FitPolicy {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};

void init_memory(size_t total);
void set_policy(FitPolicy p);
int allocate(size_t req);
bool free_block(int id);
void dump_memory();

extern std::vector<Block> memory;

#endif
