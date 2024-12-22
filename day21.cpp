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

vector<vector<long long>> grid1dp;
vector<vector<vector<long long>>> dp;

int maxlayers = 2;

// vector<pair<int, int>> directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
// vector<vector<int>> grid1
// {
//     {7, 8, 9},
//     {4, 5, 6},
//     {1, 2, 3},
//     {-1, 0, 10}
// };
// vector<vector<int>> grid2
// {
//     {-1, 0, 10},
//     {1, 2, 3}
// };

unordered_map<int, pair<int, int>> grid1 = {{0, {3, 1}}, {1, {2, 0}}, {2, {2, 1}}, {3, {2, 2}}, {4, {1, 0}}, {5, {1, 1}}, {6, {1, 2}}, {7, {0, 0}}, {8, {0, 1}}, {9, {0, 2}}, {10, {3, 2}}};
unordered_map<int, pair<int, int>> grid2 = {{0, {0, 1}}, {1, {1, 0}}, {2, {1, 1}}, {3, {1, 2}}, {4, {0, 2}}};

long long helper(int layer, int start, int dest) {
    if (layer == maxlayers) {
        if (grid1dp[start][dest] != -1) return grid1dp[start][dest];
    } else {
        if (dp[layer][start][dest] != -1) return dp[layer][start][dest];
    }

    auto& res = layer == maxlayers ? grid1dp[start][dest] : dp[layer][start][dest];
    res = 0;
    int di, dj;
    if (layer == maxlayers) {
        auto [i1, j1] = grid1[start];
        auto [i2, j2] = grid1[dest];
        di = i2 - i1;
        dj = j2 - j1;
    } else {
        auto [i1, j1] = grid2[start];
        auto [i2, j2] = grid2[dest];
        di = i2 - i1;
        dj = j2 - j1;
    }

    int curr = 4;
    if (dj < 0) {
        res += helper(layer-1, curr, 1);
        curr = 1;
        res += abs(dj) - 1;
    }
    if (di > 0) {
        res += helper(layer-1, curr, 2);
        curr = 2;
        res += abs(di) - 1;
    }
    if (dj > 0) {
        res += helper(layer-1, curr, 3);
        curr = 3;
        res += abs(dj) - 1;
    }
    if (di < 0) {
        res += helper(layer-1, curr, 0);
        curr = 0;
        res += abs(di) - 1;
    }
    res += helper(layer-1, curr, 4);

    return res;
}

long long single(string& s) {
    int index = 10;

    long long res = 0;
    for (int i = 0; i < s.size()-1; i++) {
        res += helper(maxlayers, index, s[i]-'0');
        index = s[i]-'0';
    }
    res += helper(maxlayers, index, 10);

    return res;
}

int main() {
    string curr;
    vector<string> strings;
    while (cin >> curr) strings.push_back(curr);

    grid1dp = vector<vector<long long>>(11, vector<long long>(11, -1));
    dp = vector<vector<vector<long long>>>(maxlayers, vector<vector<long long>>(5, vector<long long>(5, -1)));
    dp[0] = {
        {1, 3, 2, 3, 2},
        {3, 1, 2, 3, 4},
        {2, 2, 1, 2, 3},
        {3, 3, 2, 1, 2},
        {2, 4, 3, 2, 1}
    };

    // cout << helper(2, 3, 7) << endl;

    // cout << helper(1, 4, 0) << endl;
    // cout << 1 << endl;
    // cout << helper(1, 0, 1) << endl;
    // cout << 1 << endl;
    // cout << helper(1, 1, 4) << endl;
   


    // res += helper(layer-1, curr, 0);
    //     curr = 0;
    //     res += abs(di) - 1;
    // res += helper(layer-1, curr, 1);
    //     curr = 1;
    //     res += abs(dj) - 1;
    // res += helper(layer-1, curr, 4);

    long long res = 0;
    for (auto& s : strings) {
        // cout << helper(s) << endl;
        res += stoll(s.substr(0, s.size()-1)) * single(s);
    }

    cout << res << endl;
}