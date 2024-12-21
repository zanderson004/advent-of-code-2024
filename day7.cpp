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

unordered_map<long long, unordered_map<long long, bool>> dp;

bool helper(vector<long long>& equation, int i, long long curr) {
    if (i >= equation.size()) return curr == equation[0];
    if (dp[i].count(curr)) return dp[i][curr];
    if (helper(equation, i+1, curr+equation[i]) || helper(equation, i+1, curr*equation[i])) return dp[i][curr] = true;
    string concat = to_string(curr) + to_string(equation[i]);
    if (helper(equation, i+1, stoll(concat))) return dp[i][curr] = true;
    return dp[i][curr] = false;
}

int main() {
    string line;
    vector<vector<long long>> equations;
    while (getline(cin, line)) {
        stringstream ss{line};
        string curr;
        ss >> curr;
        long long sum = stoll(curr.substr(0, curr.size()-1));
        equations.push_back({sum});
        while (ss >> curr) {
            equations.back().push_back(stoll(curr));
        }
    }

    long long res = 0;
    for (auto& v : equations) {
        dp.clear();
        if (helper(v, 2, v[1])) res += v[0];
    }

    cout << res << endl;
}