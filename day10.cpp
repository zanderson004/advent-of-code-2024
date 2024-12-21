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

vector<pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int helper(vector<string>& grid, int i, int j) {
    unordered_map<int, int> visited;
    queue<pair<int, int>> q;
    int res = 0;

    visited[grid[0].size()*i + j] = 1;
    q.push({i, j});

    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();
        for (auto [di, dj] : directions) {
            int newI = i + di, newJ = j + dj;
            if (newI >= 0 && newI < grid.size() && newJ >= 0 && newJ < grid[0].size() && grid[newI][newJ] == grid[i][j]+1) {
                if (!visited.count(newI * grid[0].size() + newJ)) q.push({newI, newJ});
                visited[newI * grid[0].size() + newJ] += visited[grid[0].size()*i + j];
                if (grid[newI][newJ] == '9') res += visited[grid[0].size()*i + j];
            }
        }
    }

    return res;
}

int main() {
    string line;
    vector<string> grid;
    while (cin >> line) grid.push_back(line);

    long long res = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '0') res += helper(grid, i, j);
        }
    }

    cout << res << endl;
}