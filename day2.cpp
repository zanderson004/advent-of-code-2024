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

bool isSafe(vector<int>& v) {
    bool sentinel = true;
    if (v[1] > v[0]) {
        for (int i = 0; i < v.size()-1; i++) {
            // if (i == skip || i+1 == skip) continue;
            if (v[i+1] - v[i] < 1 || v[i+1] - v[i] > 3) {
                sentinel = false;
                break;
            }
        }
    } else {
        for (int i = 0; i < v.size()-1; i++) {
            // if (i == skip || i+1 == skip) continue;
            if (v[i+1] - v[i] > -1 || v[i+1] - v[i] < -3) {
                sentinel = false;
                break;
            }
        }
    }
    return sentinel;
}

int main() {
    vector<vector<int>> reports;
    
    string line;
    while (getline(cin, line)) {
        stringstream stream(line);
        vector<int> curr;
        int currNum;
        while (stream >> currNum) {
            curr.push_back(currNum);
        }
        reports.push_back(curr);
    }

    int res = 0;

    for (auto& v : reports) {
        // for (int i : v) cout << i << " ";
        // cout << endl;
        if (isSafe(v)) {
            res++;
            continue;
        }
        for (int i = 0; i < v.size(); i++) {
            vector<int> copy = v;
            copy.erase(copy.begin()+i);
            if (isSafe(copy)) {
                res++;
                break;
            }
        }
    }

    cout << res << endl;
}