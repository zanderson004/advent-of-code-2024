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

unordered_map<int, pair<int, int>> directions{{0, {-1, 0}}, {1, {0, 1}}, {2, {1, 0}}, {3, {0, -1}}};

bool check(vector<string>& grid) {
    int direction = 0;
    int currI, currJ;
    set<array<int, 3>> positions;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] != '#' && grid[i][j] != '.') {
                currI = i, currJ = j;
                if (grid[i][j] == '^') direction = 0;
                else if (grid[i][j] == '>') direction = 1;
                else if (grid[i][j] == 'v') direction = 2;
                else direction = 3;
                break;
            }
        }
    }

    while (currI >= 0 && currI < grid.size() && currJ >= 0 && currJ < grid[0].size()) {
        // cout << currI << " " << currJ << " " << direction << endl;
        auto [di, dj] = directions[direction];
        int newI = currI + di, newJ = currJ + dj;
        if (newI >= 0 && newI < grid.size() && newJ >= 0 && newJ < grid[0].size()) {
            if (grid[newI][newJ] == '#') {
                direction = (direction + 1) % 4;
                continue;
            }
        }
        if (positions.count({currI, currJ, direction})) return true;
        positions.insert({currI, currJ, direction});
        currI = newI, currJ = newJ;
    }

    return false;
}

int main() {
    string line;
    vector<string> grid;
    while (cin >> line) grid.push_back(line);

    int res = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            cout << i << " " << j << endl;
            if (grid[i][j] == '.') {
                grid[i][j] = '#';
                res += check(grid);
                grid[i][j] = '.';
            }
        }
    }

    cout << res << endl;
}