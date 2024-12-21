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

int main() {
    string line;
    unordered_map<int, unordered_set<int>> adjList;
    while (getline(cin, line)) {
        if (line == "") break;
        string snum1, snum2;
        bool sentinel = true;
        for (char c : line) {
            if (c != '|') {
                if (sentinel) snum1 += c;
                else snum2 += c;
            } else sentinel = false;
        }
        int num1 = stoi(snum1), num2 = stoi(snum2);
        adjList[num1].insert(num2);
    }

    vector<vector<int>> orders;
    while (cin >> line) {
        unordered_set<int> visited;
        vector<int> elements;
        string curr;
        for (char c : line) {
            if (c != ',') {
                curr += c;
            } else {
                elements.push_back(stoi(curr));
                curr = "";
            }
        }
        elements.push_back(stoi(curr));

        bool sentinel = true;
        for (int i : elements) {
            for (int j : visited) {
                if (adjList[i].count(j)) {
                    sentinel = false;
                    break;
                }
            }
            if (sentinel == false) break;
            visited.insert(i);
        }

        if (!sentinel) orders.push_back(elements);
    }

    int res = 0;
    for (auto& v : orders) {
        vector<int> sorted;
        unordered_set<int> elements(v.begin(), v.end());
        unordered_map<int, int> indegree;
        for (int i : v) {
            for (int j : adjList[i]) {
                if (elements.count(j)) indegree[j]++;
            }
        }

        queue<int> q;
        for (auto i : elements) {
            if (indegree[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            sorted.push_back(q.front());
            for (int i : adjList[q.front()]) {
                indegree[i]--;
                if (indegree[i] == 0) q.push(i);
            }
            q.pop();
        }

        res += sorted[sorted.size()/2];
    }

    cout << res << endl;
}