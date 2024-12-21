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

int main() {
    string curr;
    vector<array<int, 4>> input;

    while (cin >> curr) {
        int x, y, vx, vy;
        int comma = curr.find(',');
        x = stoi(curr.substr(2, comma - 2));
        y = stoi(curr.substr(comma+1));

        cin >> curr;
        comma = curr.find(',');
        vx = stoi(curr.substr(2, comma - 2));
        vy = stoi(curr.substr(comma+1));

        input.push_back({x, y, vx, vy});
    }

    // int width = 101, height = 103;
    // long long q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    // for (auto& v : input) {
    //     auto [x, y, vx, vy] = v;
    //     int finalX = (x + 100 * vx);
    //     int finalY = (y + 100 * vy);
    //     if (finalX < 0) finalX += width * (abs(finalX / width) + 1);
    //     if (finalY < 0) finalY += height * (abs(finalY / height) + 1);
    //     finalX %= width;
    //     finalY %= height;

    //     if (finalX < width/2) {
    //         if (finalY < height/2)  q1++;
    //         else if (finalY > height/2) q2++;
    //     } else if (finalX > width/2) {
    //         if (finalY < height/2) q3++;
    //         else if (finalY > height/2) q4++;
    //     }

    //     // cout << x << " " << y << " " << vx << " " << vy << " " << finalX << " " << finalY << endl;
    // }
    
    // // cout << q1 << " " << q2 << " " << q3 << " " << q4 << endl;
    // cout << q1*q2*q3*q4 << endl;

    ofstream myfile;
    myfile.open("day14.txt");

    vector<vector<vector<int>>> grid(103, vector<vector<int>>(101));
    for (int i = 0; i < input.size(); i++) {
        auto [x, y, vx, vy] = input[i];
        grid[y][x].push_back(i);
    }

    for (int z = 0; z < 10000; z++) {
        myfile << z << endl;
        for (auto& v : grid) {
            for (auto& i : v) {
                if (i.size() == 0) myfile << " ";
                else  myfile << "1";
            }
            myfile << endl;
        }
        myfile << endl << endl << endl << endl;

        vector<vector<vector<int>>> newgrid(103, vector<vector<int>>(101));
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                for (int a : grid[i][j]) {
                    auto [x, y, vx, vy] = input[a];
                    int newI = (i + vy + 103) % 103;
                    int newJ = (j + vx + 101) % 101;
                    newgrid[newI][newJ].push_back(a);
                }
            }
        }
        grid = newgrid;
    }

    myfile.close();
}