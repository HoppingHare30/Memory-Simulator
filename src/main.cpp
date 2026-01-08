#include "allocator.h"
#include "cache.h"
#include "stats.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    cout << "Memory Simulator\n";

    string cmd;
    while (true) {
        cout << "> ";
        if(!getline(cin, cmd)) break;
        if(cmd.empty()) continue;

        stringstream ss(cmd);
        string op;
        ss >> op;

        if(op == "exit") break;

        else if(op == "init") {
            size_t sz; ss >> sz;
            init_memory(sz);
        }

        else if(op == "set") {
            string p; ss >> p;
            if(p=="first") set_policy(FIRST_FIT);
            else if(p=="best") set_policy(BEST_FIT);
            else if(p=="worst") set_policy(WORST_FIT);
        }

        else if(op == "malloc") {
            size_t x; ss >> x;
            allocate(x);
        }

        else if(op == "free") {
            int id; ss >> id;
            free_block(id);
        }

        else if(op == "dump") {
            dump_memory();
        }

        else if(op == "stats") {
            report_stats();
        }

        else if(op == "cache") {
            string sub; ss >> sub;
            if(sub=="init") {
                size_t l1,l2,b; ss>>l1>>l2>>b;
                cache_init(l1,l2,b);
            } else if(sub=="reset") {
                cache_reset();
            }
        }

        else if(op == "access") {
            size_t addr; ss>>addr;
            cache_access(addr);
        }

        else if(op == "cache_stats") {
            cache_stats();
        }

        else {
            cout<<"Unknown command\n";
        }
    }
}
