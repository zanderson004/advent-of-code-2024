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
#include <fstream>

int main() {
    string curr;
    vector<string> grid;

    while (cin >> curr) grid.push_back(curr);

    int startI, startJ, endI, endJ;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 'S') {
                startI = i;
                startJ = j;
            } else if (grid[i][j] == 'E') {
                endI = i;
                endJ = j;
            }
        }
    }

    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int startDir = 0;

    map<array<int, 3>, vector<array<int, 3>>> parents;
    map<array<int, 3>, int> distances;

    priority_queue<array<int, 7>> pq;
    unordered_set<int> visited;
    pq.push({0, startI, startJ, startDir, -1, -1});

    int res = -1;
    while (!pq.empty()) {
        auto [cost, i, j, dir, parentI, parentJ, parentDir] = pq.top();
        pq.pop();
        // cout << i << " " << j << " " << dir << " " << cost << endl;

        if (!distances.count({i, j, dir})) {
            distances[{i, j, dir}] = {-cost};
            parents[{i, j, dir}].push_back({parentI, parentJ, parentDir});
        }
        else if (distances[{i, j, dir}] == -cost) parents[{i, j, dir}].push_back({parentI, parentJ, parentDir});

        if (grid[i][j] == 'E') {
            res = -cost;
        }
        
        if (res != -1 and -cost > res) break;

        int key = grid[0].size()*4*i + 4*j + dir;
        if (visited.count(key)) continue;
        else visited.insert(key);

        auto [di, dj] = directions[dir];
        int newI = i + di, newJ = j + dj;
        if (newI >= 0 && newI < grid.size() && newJ >= 0 && newJ < grid[0].size() && grid[newI][newJ] != '#' && !visited.count(grid[0].size()*4*newI + 4*newJ + dir)) {
            pq.push({cost-1, newI, newJ, dir, i, j, dir});
        }
        if (!visited.count(grid[0].size()*4*i + 4*j + (dir+1)%4)) {
            pq.push({cost-1000, i, j, (dir+1)%4, i, j, dir});
        }
        if (!visited.count(grid[0].size()*4*i + 4*j + (dir+3)%4)) {
            pq.push({cost-1000, i, j, (dir+3)%4, i, j, dir});
        }
    }

    set<pair<int, int>> results;
    stack<array<int, 3>> stk;


    for (auto [i, j, dir] : parents[{endI, endJ, 0}]) {
        stk.push({i, j, dir});
    }
    for (auto [i, j, dir] : parents[{endI, endJ, 1}]) {
        stk.push({i, j, dir});
    }
    for (auto [i, j, dir] : parents[{endI, endJ, 2}]) {
        stk.push({i, j, dir});
    }
    for (auto [i, j, dir] : parents[{endI, endJ, 3}]) {
        stk.push({i, j, dir});
    }

    while (!stk.empty()) {
        auto [i, j, dir] = stk.top(); stk.pop();
        if (i == -1) continue;
        // cout << i << " " << j << " " << dir << endl;
        results.insert({i, j});
        for (auto [newI, newJ, newDir] : parents[{i, j, dir}]) stk.push({newI, newJ, newDir});
    }

    // for (auto [i, j] : results) cout << i << " " << j << endl;
    cout << results.size()+1 << endl;
}