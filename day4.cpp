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

bool inBounds(vector<string>& grid, int i, int j) {
    return i >= 0 && j >= 0 && i < grid.size() && j < grid[0].size();
}

const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
const string str = "XMAS";

int count(vector<string>& grid, int i, int j) {
    int res = 0;
    for (auto [di, dj] : directions) {
        int newI = i, newJ = j;
        for (int z = 0; z < 4; z++) {
            if (!inBounds(grid, newI, newJ)) break;
            if (grid[newI][newJ] != str[z]) break;
            newI += di;
            newJ += dj;
            if (z == 3) res++;
        }
    }
    return res;
}

int main() {   
    string line;
    vector<string> grid;

    while (cin >> line) grid.push_back(line);

    // int res = 0;
    // for (int i = 0; i < grid.size(); i++) {
    //     for (int j = 0; j < grid[0].size(); j++) {
    //         res += count(grid, i, j);
    //     }
    // }

    int res = 0;
    for (int i = 1; i < grid.size()-1; i++) {
        for (int j = 1; j < grid.size()-1; j++) {
            if (grid[i][j] != 'A') continue;
            unordered_map<char, int> count;
            count[grid[i-1][j-1]]++;
            count[grid[i-1][j+1]]++;
            count[grid[i+1][j-1]]++;
            count[grid[i+1][j+1]]++;
            if (count['M'] == 2 && count['S'] == 2 && grid[i+1][j-1] != grid[i-1][j+1]) res++;
        }
    }

    cout << res << endl;
}