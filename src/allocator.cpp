#include "allocator.h"
#include "stats.h"
#include <iostream>
#include <vector>
using namespace std;

vector<Block> memory;
static FitPolicy current_policy = FIRST_FIT;
static int next_id = 1;

void init_memory(size_t total) {
    memory.clear();
    memory.push_back({0, total, true, -1});
    next_id = 1;
    reset_stats();
    cout << "Initialized memory of size " << total << "\n";
}

void set_policy(FitPolicy p) {
    current_policy = p;
    cout << "Policy set to "
         << (p == FIRST_FIT ? "first" : p == BEST_FIT ? "best" : "worst")
         << "\n";
}

static int find_block(size_t req) {
    int idx = -1;

    if (current_policy == FIRST_FIT) {
        for (int i = 0; i < (int)memory.size(); i++)
            if (memory[i].free && memory[i].size >= req)
                return i;
        return -1;
    }

    if (current_policy == BEST_FIT) {
        size_t best_size = (size_t)-1;
        for (int i = 0; i < (int)memory.size(); i++) {
            if (memory[i].free && memory[i].size >= req && memory[i].size < best_size) {
                best_size = memory[i].size;
                idx = i;
            }
        }
        return idx;
    }

    if (current_policy == WORST_FIT) {
        size_t worst_size = 0;
        for (int i = 0; i < (int)memory.size(); i++) {
            if (memory[i].free && memory[i].size >= req && memory[i].size > worst_size) {
                worst_size = memory[i].size;
                idx = i;
            }
        }
        return idx;
    }

    return -1;
}

int allocate(size_t req) {
    int idx = find_block(req);
    if (idx == -1) {
        record_alloc(false);
        cout << "Allocation failed\n";
        return -1;
    }

    Block alloc = {memory[idx].start, req, false, next_id++};

    if (memory[idx].size > req) {
        Block rem = {memory[idx].start + req, memory[idx].size - req, true, -1};
        memory[idx] = alloc;
        memory.insert(memory.begin() + idx + 1, rem);
    } else {
        memory[idx] = alloc;
    }

    record_alloc(true);
    cout << "Allocated block id=" << alloc.id << "\n";
    return alloc.id;
}

bool free_block(int id) {
    bool found = false;
    for (auto &b : memory) {
        if (!b.free && b.id == id) {
            b.free = true;
            b.id = -1;
            found = true;
            cout << "Freed block id=" << id << "\n";
            break;
        }
    }
    if (!found) {
        cout << "Free failed: no such block\n";
        return false;
    }

    for (int i = 0; i < (int)memory.size() - 1; i++) {
        if (memory[i].free && memory[i+1].free) {
            memory[i].size += memory[i+1].size;
            memory.erase(memory.begin() + i + 1);
            i--;
        }
    }
    return true;
}

void dump_memory() {
    cout << "Memory Layout:\n";
    for (auto &b : memory) {
        cout << "[" << b.start << " - " << (b.start + b.size - 1) << "] "
             << (b.free ? "FREE" : ("USED (id=" + to_string(b.id) + ")"))
             << "\n";
    }
}
