#include "stats.h"
#include "allocator.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

static int alloc_success = 0;
static int alloc_fail = 0;

extern vector<Block> memory;

void reset_stats() {
    alloc_success = 0;
    alloc_fail = 0;
}

void record_alloc(bool success) {
    if (success) alloc_success++;
    else alloc_fail++;
}

void report_stats() {
    cout << "--- Statistics ---\n";
    cout << "Alloc success: " << alloc_success << "\n";
    cout << "Alloc fail: " << alloc_fail << "\n";

    if (memory.empty()) {
        cout << "(no memory)\n";
        return;
    }

    size_t total = memory.back().start + memory.back().size;
    size_t used = 0;
    size_t free = 0;
    size_t largest_free = 0;

    for (auto &b : memory) {
        if (b.free) {
            free += b.size;
            largest_free = max(largest_free, b.size);
        } else {
            used += b.size;
        }
    }

    double util = (double)used / total * 100.0;
    cout << "Used memory: " << used << "\n";
    cout << "Total memory: " << total << "\n";
    cout << "Utilization: " << util << "%\n";
    cout << "Internal fragmentation: 0% (byte-level)\n";

    double ext = 0.0;
    if (free > 0)
        ext = 1.0 - (double)largest_free / free;

    cout << "External fragmentation: " << ext * 100.0 << "%\n";
}
