#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include <ranges>
#include <string>
#include <sstream>
#include <ctype.h>
#include <numeric>
#include <fstream>
#include <bitset>
#include <queue>
#include <cmath>
#include <stack>
using namespace std;

int main() {
    string curr;
    unordered_set<string> list;
    unordered_map<string, unordered_set<string>> graph;
    while (cin >> curr) {
        string s1 = curr.substr(0, 2), s2 = curr.substr(3, 2);
        graph[s1].insert(s2);
        graph[s2].insert(s1);
        list.insert(s1);
        list.insert(s2);
    }

    // int res = 0;
    // for (auto& [s1, st] : graph) {
    //     for (auto& s2 : st) {
    //         for (auto& [s3, st] : graph) {
    //             if ((s1[0] == 't' || s2[0] == 't' || s3[0] == 't') && graph[s1].count(s3) && graph[s2].count(s3)) res++;
    //         }
    //     }
    // }

    int bestSize = 1;
    set<string> best;
    set<set<string>> visited;
    stack<set<string>> stk;
    for (auto& s : list) {
        visited.insert({s});
        stk.push({s});
    }

    while (!stk.empty()) {
        auto curr = stk.top();
        // for (auto& s : curr) cout << s << " ";
        // cout << endl;
        stk.pop();
        for (auto& s : list) {
            if (curr.count(s)) continue;
            if (graph[s].size() < bestSize) continue;
            bool _break = false;
            bool skip = false;
            for (auto& s2 : curr) {
                if (graph[s2].size() < bestSize) {
                    _break = true;
                    break;
                }
                if (!graph[s2].count(s)) {
                    skip = true;
                    break;
                }
            }
            if (_break) break;
            if (skip) continue;
            curr.insert(s);
            if (!visited.count(curr)) {
                if (curr.size() > bestSize) {
                    bestSize = curr.size();
                    best = curr;
                }
                visited.insert(curr);
                stk.push(curr);
            }
            curr.erase(s);
        }
    }

    for (auto& s : best) cout << s << ",";
    cout << endl;
}