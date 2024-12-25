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
#include <cmath>
using namespace std;

int main() {
    string curr;
    vector<long long> input;
    while (cin >> curr) input.push_back(stoll(curr));

    vector<map<array<long long, 4>, int>> sequenceToPrices(input.size());

    for (int i = 0; i < input.size(); i++) {
        long long _1 = -1, _2 = -1, _3 = -1, _4 = -1;
        auto n = input[i];
        cout << i << "/" << input.size() << endl;
        for (int j = 0; j < 2000; j++) {
            n = ((n * 64) ^ n) % 16777216;
            n = ((n / 32) ^ n) % 16777216;
            n = ((n * 2048) ^ n) % 16777216;

            if (_1 != -1 && !sequenceToPrices[i].count({_2-_1, _3-_2, _4-_3, (n%10)-_4})) sequenceToPrices[i][{_2-_1, _3-_2, _4-_3, (n%10)-_4}] = n % 10;

            _1 = _2;
            _2 = _3;
            _3 = _4;
            _4 = n % 10;
        }
    }

    set<array<long long, 4>> visited;
    int res = 0;
    for (int z = 0; z < sequenceToPrices.size(); z++) {
        auto& mp = sequenceToPrices[z];
        cout << z << "//" << sequenceToPrices.size() << endl;;
        for (auto& [v, price] : mp) {
            if (visited.count(v)) continue;
            else visited.insert(v);
            // cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << " " << price << endl;
            int curr = 0;
            for (int i = 0; i < sequenceToPrices.size(); i++) {
                curr += sequenceToPrices[i][v];
            }
            res = max(res, curr);
        }
        // cout << endl;
    }

    cout << res << endl;
}