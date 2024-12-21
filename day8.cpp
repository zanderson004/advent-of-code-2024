using namespace std;
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

int main() {
    string line;
    vector<string> grid;
    while (cin >> line) grid.push_back(line);

    unordered_map<char, vector<pair<int, int>>> frequencies;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] != '.') frequencies[grid[i][j]].push_back({i, j});
        }
    }

    // set<pair<int, int>> pos;
    // for (auto& [freq, v] : frequencies) {
    //     for (int i = 0; i < v.size(); i++) {
    //         for (int j = i+1; j < v.size(); j++) {
    //             int di = v[j].first - v[i].first, dj = v[j].second - v[i].second;
    //             int i1 = v[j].first + di, j1 = v[j].second + dj;
    //             int i2 = v[i].first - di, j2 = v[i].second - dj;
    //             if (i1 >= 0 && i1 < grid.size() && j1 >= 0 && j1 < grid[0].size()) pos.insert({i1, j1});
    //             if (i2 >= 0 && i2 < grid.size() && j2 >= 0 && j2 < grid[0].size()) pos.insert({i2, j2});
    //         }
    //     }
    // }

    set<pair<int, int>> pos;
    for (auto& [freq, v] : frequencies) {
        for (int i = 0; i < v.size(); i++) {
            for (int j = i+1; j < v.size(); j++) {
                int di = v[j].first - v[i].first, dj = v[j].second - v[i].second;
                int factor = gcd(di, dj);
                di /= factor; dj /= factor;

                int currI = v[j].first, currJ = v[j].second;
                while (currI >= 0 && currI < grid.size() && currJ >= 0 && currJ < grid[0].size()) {
                    pos.insert({currI, currJ});
                    currI += di;
                    currJ += dj;
                }

                currI = v[j].first, currJ = v[j].second;
                while (currI >= 0 && currI < grid.size() && currJ >= 0 && currJ < grid[0].size()) {
                    pos.insert({currI, currJ});
                    currI -= di;
                    currJ -= dj;
                }
            }
        }
    }

    cout << pos.size() << endl;
}