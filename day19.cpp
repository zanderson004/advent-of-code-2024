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

unordered_map<string, long long> dp;

long long helper(string& s, vector<string>& patterns) {
    if (dp.count(s)) return dp[s];
    dp[s] = 0;

    for (auto& pattern : patterns) {
        if (s.substr(0, pattern.size()) == pattern) {
            if (s.size() == pattern.size()) dp[s]++;
            else {
                string rem = s.substr(pattern.size());
                dp[s] += helper(rem, patterns);
            }
        }
    }

    return dp[s];
}

int main() {
    string curr;
    vector<string> patterns;
    vector<string> totals;

    getline(cin, curr);
    stringstream ss(curr);
    while (ss >> curr) patterns.push_back(curr.substr(0, curr.size()-1));
    patterns.back() += curr.back();

    while (cin >> curr) totals.push_back(curr);

    // for (auto& s : patterns) cout << s << endl;
    // cout << endl;
    // for (auto& s : totals) cout << s << endl;

    long long res = 0;
    for (auto& s : totals) {
        res += helper(s, patterns);
    }

    // for (auto& [s, st] : dp) {
    //     cout << s << ":\n";
    //     for (auto& v : st) {
    //         for (auto& s2 : v) cout << s2 << " ";
    //     }
    //     cout << endl;
    // }

    cout << res << endl;
}