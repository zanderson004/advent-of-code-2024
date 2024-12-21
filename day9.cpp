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

int main() {
    string line;
    cin >> line;

    // long long maxId = (line.size()-1)/2;
    // long long left = 0, right = line.size()-1;

    // long long res = 0;
    // long long i = 0;
    // long long currLeft = 0;
    // long long currRight = 0;
    // while (left < right) {
    //     if (line[left] == '0') {
    //         left++;
    //         continue;
    //     }
    //     if (line[right] == '0') {
    //         right -= 2;
    //         continue;
    //     }
    //     if (left % 2 == 0) res += i * left / 2;
    //     else {
    //         res += i * right / 2;
    //         currRight++;
    //         if (currRight == stoi(line.substr(right, 1))) {
    //             right -= 2;
    //             currRight = 0;
    //         }
    //     }
    //     i++;
    //     currLeft++;
    //     if (currLeft == stoi(line.substr(left, 1))) {
    //         left++;
    //         currLeft = 0;
    //     }
    // }
    // if (left == right)
    // while (currLeft < stoi(line.substr(left, 1)) - currRight) {
    //     res += i * left / 2;
    //     i++;
    //     currLeft++;
    // }

    map<long long, long long> indexToSpaces;
    map<long long, pair<long long, long long>> indexToFilelengths;
    long long index = 0;
    unordered_map<long long, long long> filenumToIndex;

    for (long long i = 0; i < line.size(); i++) {
        if (line[i] == '0') continue;
        long long num = stoll(line.substr(i, 1));
        if (i % 2 == 0) {
            indexToFilelengths[index] = {num, i/2};
            filenumToIndex[i/2] = index;
        }
        else indexToSpaces[index] = num;
        index += num;
    }

    // for (auto [idx, length] : indexToFilelengths) cout << idx << " " << length.first << " " << length.second << endl;
    // cout << endl;
    // for (auto [idx, length] : indexToSpaces) cout << idx << " " << length << endl;

    for (long long i = line.size()/2; i >= 0; i--) {
        long long index = filenumToIndex[i];
        for (auto [idx, length] : indexToSpaces) {
            if (idx < index && length >= indexToFilelengths[index].first) {
                int leftover = indexToSpaces[idx] - indexToFilelengths[index].first;
                if (leftover > 0) indexToSpaces[idx + indexToFilelengths[index].first] = leftover;
                indexToSpaces.erase(idx);
                indexToFilelengths[idx] = indexToFilelengths[index];
                indexToFilelengths.erase(index);
                break;
            }
        }
    }

    // cout << endl;
    // for (auto [idx, length] : indexToFilelengths) cout << idx << " " << length.first << " " << length.second << endl;

    long long res = 0;
    for (auto [idx, length] : indexToFilelengths) {
        for (long long i = 0; i < length.first; i++) {
            res += length.second * (idx + i);
        }
    }

    cout << res << endl;
}