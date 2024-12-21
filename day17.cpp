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

vector<int> program(long long a, long long b, long long c, vector<int> instructions) {
    auto combo = [&a, &b, &c](long long i) {
        if (i <= 3) return i;
        if (i == 4) return a;
        if (i == 5) return b;
        if (i == 6) return c;
        else return (long long)-1;
    };

    vector<int> output;

    for (int i = 0; i < instructions.size(); i += 2) {
        long long operand = instructions[i+1];
        // cout << i << " " << instructions[i] << " " << operand << " " << a << " " << b << " " << c << endl;
        switch (instructions[i]) {
            case 0:
                a = a / pow(2, combo(operand));
                break;
            case 1:
                b ^= combo(operand);
                break;
            case 2:
                b = combo(operand) % 8;
                b += 8;
                b %= 8;
                break;
            case 3:
                if (a != 0) i = operand - 2;
                break;
            case 4:
                b ^= c;
                break;
            case 5:
                output.push_back(((combo(operand) % 8) + 8) % 8);
                break;
            case 6:
                b = a / pow(2, combo(operand));
                break;
            case 7:
                c = a / pow(2, combo(operand));
                break;
        }
    }

    return output;
}

unordered_map<int, vector<array<int, 3>>> graph;

void helper(int a, int i, int index) {
    int b = a;
    b ^= 2;
    for (int c = 0; c < 8; c++) {
        int newb = b ^ c;
        newb ^= 7;
        // if (index == 15 && i == b % 8) cout << a << " " << b << " " << c << " " << i << endl;
        if (i == newb % 8) graph[index].push_back({a, b, c});
    }
}

int main() {
    int a, b, c;
    string temp;
    cin >> temp >> temp >> a >> temp >> temp >> b >> temp >> temp >> c >> temp >> temp;

    vector<int> instructions;
    for (int i = 0; i < temp.size(); i += 2) instructions.push_back(temp[i]-'0');

    // for (int i : instructions) cout << i << " ";

    for (int i = 0; i < instructions.size(); i++) {
        for (int a = 0; a < 8; a++) {
            helper(a, instructions[i], i);
        }
    }

    // for (auto& [i, v] : graph) {
    //     cout << i << endl;
    //     for (auto [a, b, c] : v) cout << a << " " << b << " " << c << endl;
    //     cout << endl;
    // }

    vector<vector<int>> paths;
    for (auto [a, b, c] : graph[15]) {
        if (a >> b == c) paths.push_back({a});
    }
    for (int i = 14; i >= 0; i--) {
        vector<vector<int>> newPaths;
        for (auto [a, b, c] : graph[i]) {
            for (auto& path : paths) {
                // for (int i : path) cout << i << " ";
                // cout << endl;
                int curr = 0;
                if (path.size() > 1) curr += path[path.size()-2];
                curr <<= 3;
                curr += path.back();
                curr <<= 3;
                curr += a;
                if ((curr >> b) % 8 == c) {
                    vector<int> newPath = path;
                    newPath.push_back(a);
                    newPaths.push_back(newPath);
                }
            }
        }
        paths = newPaths;
    }

    for (auto& path : paths) {
        for (int i : path) cout << i << " ";
        cout << endl;
    }
    cout << endl;

    vector<int> res = program(190384615275535, 0, 0, instructions);
    for (int i : res) cout << i << " ";
    cout << endl;
}