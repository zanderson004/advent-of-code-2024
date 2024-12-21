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
#include <bitset>

bool reachable(set<pair<int, int>>& bytes) {
    int edge = 70;
    int i = 0, j = 0;

    queue<array<int, 3>> q;
    set<pair<int, int>> visited;
    visited.insert({0, 0});
    q.push({0, 0, 0});

    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    int res = -1;
    while (!q.empty()) {
        auto [i, j, dist] = q.front();
        q.pop();
        if (i == edge && j == edge) {
            return true;
        }

        for (auto [di, dj] : directions) {
            int newI = i+di, newJ = j+dj;
            if (newI >= 0 && newI <= edge && newJ >= 0 && newJ <= edge && !visited.count({newI, newJ}) && !bytes.count({newI, newJ})) {
                visited.insert({newI, newJ});
                q.push({newI, newJ, dist+1});
            }
        }
    }

    return false;
}

int main() {
    string curr;
    set<pair<int, int>> bytes;

    while (cin >> curr) {
        // cout << bytes.size() << endl;
        for (int j = 0; j < curr.size(); j++) {
            if (curr[j] == ',') {
                int first = stoi(curr.substr(0, j));
                int second = stoi(curr.substr(j+1));
                bytes.insert({first, second});
                break;
            }
        }

        if (reachable(bytes) == false) {
            cout << bytes.size() << endl;
            break;
        }
    }
}