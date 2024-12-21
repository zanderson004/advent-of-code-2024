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

map<pair<int, int>, char> moves;
queue<pair<array<int, 4>, char>> q;

bool helper(vector<string>& grid, int i, int j, int di, int dj, char c) {
    while (!q.empty()) q.pop();
    q.push({{i, j, di, dj}, c});

    while (!q.empty()) {
        auto& [v, c] = q.front(); q.pop();
        auto [i, j, di, dj] = v;

        if (grid[i][j] == '.') {
            moves.insert({{i, j}, c});
        } else if (grid[i][j] == '[') {
            moves.insert({{i, j}, c});
            if (dj == 0 && !moves.count({i, j+1})) q.push({{i, j+1, di, dj}, '.'});
            q.push({{i+di, j+dj, di, dj}, '['});
        } else if (grid[i][j] == ']') {
            moves.insert({{i, j}, c});
            if (dj == 0 && !moves.count({i, j-1})) q.push({{i, j-1, di, dj}, '.'});
            q.push({{i+di, j+dj, di, dj}, ']'});
        } else return false;
    }

    return true;
}

int main() {
    string curr, instructions;
    vector<string> grid;

    while (cin >> curr && curr[0] == '#') grid.push_back(curr);
    instructions = curr;
    while (cin >> curr) instructions += curr;

    vector<string> tempgrid(grid.size());
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '.') tempgrid[i] += "..";
            else if (grid[i][j] == '#') tempgrid[i] += "##";
            else if (grid[i][j] == '@') tempgrid[i] += "@.";
            else tempgrid[i] += "[]";
        }
    }
    grid = tempgrid;

    int robotI = -1, robotJ = -1;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '@') {
                robotI = i;
                robotJ = j;
                break;
            }
        }
        if (robotI > -1) break;
    }

    unordered_map<char, pair<int, int>> directions = {{'<', {0, -1}}, {'^', {-1, 0}}, {'>', {0, 1}}, {'v', {1, 0}}};

    // for (auto& v : grid) {
    //     for (char c : v) cout << c;
    //     cout << endl;
    // }
    // cout << endl;

    for (int i = 0; i < instructions.size(); i++) {
        char c = instructions[i];
        auto [di, dj] = directions[c];
        moves.clear();
        bool move = helper(grid, robotI+di, robotJ+dj, di, dj, '@');
        if (move) {
            // cout << "true " << i << endl;
            grid[robotI][robotJ] = '.';
            robotI += di;
            robotJ += dj;
            for (auto [p, c] : moves) grid[p.first][p.second] = c;
        }

        // if (true) {
        //     cout << i << " " << c << endl;
        //     for (auto& v : grid) {
        //         for (char c : v) cout << c;
        //         cout << endl;
        //     }
        //     cout << endl;
        // }
    }

    long long res = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '[') {
                res += i * 100 + j;
            }
        }
    }

    cout << res << endl;
}