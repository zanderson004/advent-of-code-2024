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
using namespace std;

long long helper(string& s) {
    vector<vector<int>> grid1
    {
        {7, 8, 9},
        {4, 5, 6},
        {1, 2, 3},
        {-1, 0, 10}
    };

    vector<pair<int, int>> directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    vector<vector<int>> grid2
    {
        {-1, 0, 10},
        {1, 2, 3}
    };

    // int i1 = 3, j1 = 2;
    // int i2 = 0, j2 = 2;
    // int i3 = 0, j3 = 2;
    int total = 25;
    vector<pair<int, int>> indices(total+1, {0, 2});
    indices[0] = {3, 2};

    set<pair<vector<pair<int, int>>, int>> visited;
    queue<pair<vector<pair<int, int>>, array<int, 2>>> q;
    visited.insert({indices, 0});
    q.push({indices, {0, 0}});

    long long res = -1;
    while (!q.empty()) {
        auto [indices, v] = q.front();
        auto [index, dist] = v;
        cout << index << endl;
        // for (auto [i, j] : indices) cout << i << " " << j << " ";
        // cout << s[index] << " " << dist << endl;
        q.pop();

        for (auto [di, dj] : directions) {
            indices.back().first += di, indices.back().second += dj;
            if (indices.back().first >= 0 && indices.back().first < grid2.size() && indices.back().second >= 0 && indices.back().second < grid2[0].size() && grid2[indices.back().first][indices.back().second] != -1 && !visited.count({indices, index})) {
                visited.insert({indices, index});
                q.push({indices, {index, dist+1}});
            }
            indices.back().first -= di, indices.back().second -= dj;
        }

        bool skip = true;
        for (int iteration = total-1; iteration >= 0; iteration--) {
            auto [previ, prevj] = indices[iteration+1];
            auto& [i, j] = indices[iteration];
            if (grid2[previ][prevj] != 10) {
                auto [di, dj] = directions[grid2[previ][prevj]];
                i += di, j += dj;
                if (iteration != 0) {
                    if (i < 0 || i >= grid2.size() || j < 0 || j >= grid2[0].size() || grid2[i][j] == -1 || visited.count({indices, index})) break;
                } else {
                    if (i < 0 || i >= grid1.size() || j < 0 || j >= grid1[0].size() || grid1[i][j] == -1 || visited.count({indices, index})) break;
                }
                visited.insert({indices, index});
                q.push({indices, {index, dist+1}});
                break;
            }
            if (iteration == 0) skip = false;
        }
        if (skip) continue;
        auto [i1, j1] = indices[0];
        if (grid1[i1][j1] == (s[index]-'0') && !visited.count({indices, index+1})) {
            visited.insert({indices, index+1});
            q.push({indices, {index+1, dist+1}});
        } else if (grid1[i1][j1] == 10 && index == s.size()-1) return dist+1;
    }

    return -1;
}

int main() {
    string curr;
    vector<string> strings;
    while (cin >> curr) strings.push_back(curr);

    long long res = 0;
    for (auto& s : strings) {
        // cout << helper(s) << endl;
        res += stoll(s.substr(0, s.size()-1)) * helper(s);
        cout << "test" << endl;
    }

    cout << res << endl;
}