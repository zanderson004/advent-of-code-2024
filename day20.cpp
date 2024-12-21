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
using namespace std;

int main() {
    string curr;
    vector<string> grid;
    while (cin >> curr) grid.push_back(curr);

    int endI = -1, endJ = -1;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'E') {
                endI = i;
                endJ = j;
                break;
            }
        }
        if (endI != -1) break;
    }

    vector<vector<int>> distances(grid.size(), vector<int>(grid[0].size()));
    queue<array<int, 3>> q;
    unordered_set<int> visited;

    visited.insert(endI * grid[0].size() + endJ);
    q.push({endI, endJ, 0});

    vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

    while (!q.empty()) {
        auto [i, j, dist] = q.front();
        q.pop();
        for (auto [di, dj] : directions) {
            int newI = i + di, newJ = j + dj;
            if (newI >= 0 && newI < grid.size() && newJ >= 0 && newJ < grid[0].size() && grid[newI][newJ] != '#' && !visited.count(newI * grid[0].size() + newJ)) {
                distances[newI][newJ] = dist+1;
                visited.insert(newI * grid[0].size() + newJ);
                q.push({newI, newJ, dist+1});
            }
        }
    }

    // for (int i = 0; i < grid.size(); i++) {
    //     for (int j = 0; j < grid[0].size(); j++) {
    //         cout << distances[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    int res = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            for (int i2 = 0; i2 < grid.size(); i2++) {
                for (int j2 = 0; j2 < grid[0].size(); j2++) {
                    int dist = abs(i - i2) + abs(j - j2);
                    if (grid[i][j] != '#' && grid[i2][j2] != '#' && dist <= 20) {
                        if (distances[i][j] - distances[i2][j2] >= 100+dist) {
                            res++;
                            // cout << i << " " << j << " " << newI2 << " " << newJ2 << endl;
                        }
                    }
                }
            }
        }
    }

    cout << res << endl;
}