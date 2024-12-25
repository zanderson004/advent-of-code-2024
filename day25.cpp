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
    vector<vector<int>> locks, keys;
    while (cin >> curr) {
        vector<string> grid(7);
        grid[0] = curr;
        for (int i = 0; i < 6; i++) cin >> grid[i+1];

        if (grid[0][0] == '#') {
            vector<int> curr(5);
            for (int i = 0; i < 5; i++) {
                int count = 0;
                for (int j = 1; j < 6; j++) {
                    if (grid[j][i] == '#') count++;
                }
                curr[i] = count;
            }
            locks.push_back(curr);
        } else {
            vector<int> curr(5);
            for (int i = 0; i < 5; i++) {
                int count = 0;
                for (int j = 1; j < 6; j++) {
                    if (grid[j][i] == '#') count++;
                }
                curr[i] = count;
            }
            keys.push_back(curr);
        }
    }

    // for (auto& lock : locks) {
    //     for (int i : lock) cout << i << " ";
    //     cout << endl;
    // }
    // cout << endl;
    // for (auto& key : keys) {
    //     for (int i : key) cout << i << " ";
    //     cout << endl;
    // }

    long long res = 0;
    for (auto& lock : locks) {
        for (auto& key : keys) {
            bool skip = false;
            for (int i = 0; i < 5; i++) {
                if (lock[i] + key[i] > 5) {
                    skip = true;
                    break;
                }
            }
            if (!skip) res++;
        }
    }
    cout << res << endl;
}