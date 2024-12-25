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
#include <stack>
using namespace std;

long long helper(unordered_map<string, int> wires, unordered_map<string, vector<array<string, 3>>>& gates, string& s1, string& s2, string& s3, string& s4) {
    queue<string> q;
    for (auto& [s, val] : wires) q.push(s);

    while(!q.empty()) {
        auto s = q.front();
        q.pop();
        for (auto [gate, other, output] : gates[s]) {
            // cout << s << " " << gate << " " << other << " " << output << endl;
            if (output == s1) output = s2;
            if (output == s2) output = s1;
            if (output == s3) output = s4;
            if (output == s4) output = s3;
            if (!wires.count(output) && wires.count(other)) {
                if (gate == "AND") {
                    wires[output] = wires[s] & wires[other];
                } else if (gate == "OR") {
                    wires[output] = wires[s] | wires[other];
                } else if (gate == "XOR") {
                    wires[output] = wires[s] ^ wires[other];
                } else cerr << "err" << endl;
                q.push(output);
            }
        }
    }

    // for (auto& [s, v] : gates) {
    //     for (auto& [a, b, c] : v) cout << s << " " << a << " " << b << " " << c << endl;
    // }
    // for (auto& [s, val] : wires) cout << s << " " << val << endl;

    long long res = 0;
    int currIndex = 0;
    while (true) {
        string num = to_string(currIndex);
        if (num.size() == 1) num = "0" + num;
        string key = "z" + num;
        if (!wires.count(key)) break;
        if (wires[key] == 1) res += pow(2, currIndex);
        currIndex++;
    }

    return res;
}

int main() {
    string curr;
    unordered_map<string, int> wires;
    while (getline(cin, curr)) {
        if (curr == "") break;
        stringstream ss(curr);
        string s1, s2;
        ss >> s1 >> s2;
        wires[s1.substr(0, s1.size()-1)] = stoi(s2);
    }

    vector<array<string, 4>> reference;

    unordered_map<string, vector<array<string, 3>>> gates;
    string wire1, gate, wire2, wire3;
    while (cin >> wire1) {
        cin >> gate >> wire2 >> curr >> wire3;
        gates[wire1].push_back({gate, wire2, wire3});
        gates[wire2].push_back({gate, wire1, wire3});
        reference.push_back({gate, wire1, wire2, wire3});
    }

    long long x = 0;
    int currIndex = 0;
    while (true) {
        string num = to_string(currIndex);
        if (num.size() == 1) num = "0" + num;
        string key = "x" + num;
        if (!wires.count(key)) break;
        if (wires[key] == 1) x += pow(2, currIndex);
        currIndex++;
    }

    long long y = 0;
    currIndex = 0;
    while (true) {
        string num = to_string(currIndex);
        if (num.size() == 1) num = "0" + num;
        string key = "y" + num;
        if (!wires.count(key)) break;
        if (wires[key] == 1) y += pow(2, currIndex);
        currIndex++;
    }

    for (int i1 = 0; i1 < reference.size(); i1++) {
        cout << i1 << "/" << reference.size() << endl;
        for (int i2 = 0; i2 < reference.size(); i2++) {
            cout << "sub " << i2 << "/" << reference.size() << endl;
            for (int i3 = 0; i3 < reference.size(); i3++) {
                for (int i4 = 0; i4 < reference.size(); i4++) {
                    unordered_set<int> indices{i1, i2, i3, i4};
                    if (indices.size() != 4) continue;
                    long long z = helper(wires, gates, reference[i1][3], reference[i2][3], reference[i3][3], reference[i4][3]);
                    if (z == x + y) {
                        vector<string> res;
                        for (int i : indices) res.push_back(reference[i][3]);
                        sort(res.begin(), res.end());
                        for (auto& s : res) cout << s << ",";
                        return 0;
                    }
                }
            }
        }
    }
}