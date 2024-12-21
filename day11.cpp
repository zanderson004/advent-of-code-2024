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

vector<unordered_map<long long, long long>> dp(75);

long long helper(long long i, int iter = 0) {
    if (iter == 75) return 1;
    if (dp[iter].count(i)) return dp[iter][i];

    long long res = 0;
    if (i == 0) res += helper(1, iter+1);
    else if (to_string(i).size() % 2 == 0) {
        string curr = to_string(i);
        string left = curr.substr(0, curr.size()/2);
        string right = curr.substr(curr.size()/2, curr.size()/2);
        res += helper(stoll(left), iter+1);
        res += helper(stoll(right), iter+1);
    } else res += helper(i*2024, iter+1);

    return dp[iter][i] = res;
}

int main() {
    string curr;
    vector<long long> stones;
    while (cin >> curr) stones.push_back(stoll(curr));

    long long res = 0;
    for (long long i : stones) res += helper(i);

    cout << res << endl;
}