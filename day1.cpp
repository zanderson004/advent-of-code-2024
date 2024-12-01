using namespace std;
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include <ranges>

int main() {
    vector<int> list1, list2;
    int curr;
    
    while (cin >> curr) {
        if (list1.size() == list2.size()) list1.push_back(curr);
        else list2.push_back(curr);
    }

    ranges::sort(list1);
    ranges::sort(list2);

    long long res = 0;
    for (int i = 0; i <list1.size(); i++) {
        res += abs(list1[i] - list2[i]);
    }
    cout << res << endl;
    // cout << "test" << endl;

    unordered_map<int, int> counts;
    for (int i : list2) counts[i]++;

    long long res2 = 0;
    for (int i : list1) {
        res2 += i * counts[i];
    }
    cout << res2 << endl;

    return 0;
}