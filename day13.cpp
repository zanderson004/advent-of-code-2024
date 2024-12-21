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

const long long offset = 10000000000000;

// bool helper(array<int, 6>& v, int i) {
//     auto [ax, ay, bx, by, x, y] = v;

//     for (int j = 0; j <= i; j++) {
//         if ((i - j) % 3 != 0) continue;
//         int currX = (i-j)*ax/3 + j*bx;
//         int currY = (i-j)*ay/3 + j*by;
//         if (currX == x && currY == y) return true;
//     }

//     return false;
// }

int main() {
    string curr;

    vector<array<long long, 6>> input;
    while (cin >> curr) {
        cin >> curr;
        string axs, ays, bxs, bys;
        cin >> axs >> ays;
        cin >> curr >> curr;
        cin >> bxs >> bys;
        cin >> curr;
        string xs, ys;
        cin >> xs >> ys;

        // cout << axs << " " << ays << " " << bxs << " " << bys << " " << xs << " " << ys << endl;

        int ax, ay, bx, by, x, y;
        ax = stoi(axs.substr(1, axs.size()-2));
        ay = stoi(ays.substr(1));
        bx = stoi(bxs.substr(1, bxs.size()-2));
        by = stoi(bys.substr(1));
        x = stoi(xs.substr(2, xs.size()-3));
        y = stoi(ys.substr(2));
        input.push_back({ax, ay, bx, by, x+offset, y+offset});
    }

    long long res = 0;
    for (auto& v : input) {
        auto [ax, ay, bx, by, x, y] = v;
        long long det = ax * by - bx * ay;
        if (det == 0) {
            // if (ax/)

        } else {
            // cout << ax << " " << ay << " " << bx << " " << by << " " << x << " " << y << " " << det << endl;
            long long a = (by * x - bx * y)/det;
            long long b = (-ay * x + ax * y)/det;
            // cout << a << " " << b << endl;
            if (a*ax + b*bx == x && a*ay + b*by == y) res += a*3 + b;
        }
    }

    cout << res << endl;
}