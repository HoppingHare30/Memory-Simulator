#include "cache.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static vector<CacheLine> L1, L2;
static size_t block_sz = 4;
static size_t l1_hits = 0, l1_miss = 0;
static size_t l2_hits = 0, l2_miss = 0;
static size_t prop_mem = 0;

void cache_init(size_t l1, size_t l2, size_t b) {
    L1.clear();
for(size_t i = 0; i < l1; i++)
    L1.push_back({0, false});

L2.clear();
for(size_t i = 0; i < l2; i++)
    L2.push_back({0, false});

    block_sz = b;
    l1_hits = l1_miss = l2_hits = l2_miss = prop_mem = 0;
    cout << "Cache initialized: L1="<<l1<<" L2="<<l2<<" block="<<b<<"\n";
}

void cache_reset() {
    for (auto &c : L1) c.valid = false;
    for (auto &c : L2) c.valid = false;
    l1_hits = l1_miss = l2_hits = l2_miss = prop_mem = 0;
}

static size_t align_tag(size_t addr) {
    return addr - (addr % block_sz);
}

static bool access_cache(vector<CacheLine> &cache, size_t tag) {
    for (auto &line : cache)
        if (line.valid && line.tag == tag) return true;
    return false;
}

static void insert_fifo(vector<CacheLine> &cache, size_t tag) {
    for (auto &line : cache) {
        if (!line.valid) {
            line.valid = true;
            line.tag = tag;
            return;
        }
    }
    for (int i = cache.size()-1; i > 0; i--)
        cache[i] = cache[i-1];
    cache[0] = {tag, true};
}

void cache_access(size_t addr) {
    size_t tag = align_tag(addr);

    if (access_cache(L1, tag)) {
        l1_hits++;
        cout << "L1 hit\n";
        return;
    }

    l1_miss++;
    if (access_cache(L2, tag)) {
        l2_hits++;
        cout << "L1 miss, L2 hit\n";
        insert_fifo(L1, tag);
        return;
    }

    l2_miss++;
    prop_mem++;
    cout << "Miss, fetch from memory\n";
    insert_fifo(L2, tag);
    insert_fifo(L1, tag);
}

void cache_stats() {
    auto ratio = [](size_t h, size_t m){
        size_t t = h + m;
        return t ? (double)h/t*100.0 : 0.0;
    };

    cout << "--- Cache Stats ---\n";
    cout << "L1 hits="<<l1_hits<<" miss="<<l1_miss<<" ratio="<<ratio(l1_hits,l1_miss)<<"%\n";
    cout << "L2 hits="<<l2_hits<<" miss="<<l2_miss<<" ratio="<<ratio(l2_hits,l2_miss)<<"%\n";
    cout << "Miss propagation to memory: "<<prop_mem<<"\n";
}
