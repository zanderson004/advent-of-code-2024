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

long long helper(int layer, int start, int dest) {

}

long long single(string& s) {
    int index = 0
    vector<int> indices(26, 4);
    indices[0] = 10

    long long res = 0;
    for (int i = 0; i < s.size()-1; i++) {
        res += helper(25, 10, )
    }

    return res;
}

int main() {
    string curr;
    vector<string> strings;
    while (cin >> curr) strings.push_back(curr);

    grid1dp = vector<vector<long long>>(11, vector<long long>(11, -1));
    dp = vector<vector<vector<long long>>>(25, vector<vector<long long>>(5, vector<long long>(5, -1)));
    dp[0] = {
        {0, 2, 1, 2, 1},
        {2, 0, 1, 2, 3},
        {1, 1, 0, 1, 2},
        {2, 2, 1, 0, 1},
        {1, 3, 2, 1, 0}
    };

    long long res = 0;
    for (auto& s : strings) {
        // cout << helper(s) << endl;
        res += stoll(s.substr(0, s.size()-1)) * single(s);
        cout << "test" << endl;
    }

    cout << res << endl;
}