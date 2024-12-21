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
    string curr;
    vector<string> grid;
    while (cin >> curr) grid.push_back(curr);

    long long res = 0;

    unordered_set<int> visited, pvisited;
    queue<pair<int, int>> q;

    vector<pair<int, int>> directions{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            int key = i * grid[0].size() + j;

            if (!visited.count(key)) {
                visited.insert(key);
                q.push({i, j});

                int perimeter = 0, area = 0;

                while (!q.empty()) {
                    auto [I, J] = q.front(); q.pop();
                    area++;
                    int key = I * grid[0].size() + J;
                    pvisited.insert(key);
                    for (auto [di, dj] : directions) {
                        int newI = I + di, newJ = J + dj;
                        int newKey = newI * grid[0].size() + newJ;
                        if (newI >= 0 && newI < grid.size() && newJ >= 0 && newJ < grid[0].size() && grid[I][J] == grid[newI][newJ]) {
                            if (!visited.count(newKey)) {
                                visited.insert(newKey);
                                q.push({newI, newJ});
                            }
                        } else {
                            bool flag = true;
                            if (di != 0) {
                                int x = 1;
                                while (flag && J+x >= 0 && J+x < grid[0].size() && grid[I][J] == grid[I][J+x]) {
                                    int newKey2 = I * grid[0].size() + (J+x);
                                    if (I+di < 0 || I+di >= grid.size() || J+x < 0 && J+x >= grid[0].size() || grid[I+di][J+x] != grid[I][J+x]) {
                                        if (pvisited.count(newKey2)) {
                                            flag = false;
                                            break;
                                        }
                                    } else break;
                                    x++;
                                }
                                x = -1;
                                while (flag && J+x >= 0 && J+x < grid[0].size() && grid[I][J] == grid[I][J+x]) {
                                    int newKey2 = I * grid[0].size() + (J+x);
                                    if (I+di < 0 || I+di >= grid.size() || J+x < 0 && J+x >= grid[0].size() || grid[I+di][J+x] != grid[I][J+x]) {
                                        if (pvisited.count(newKey2)) {
                                            flag = false;
                                            break;
                                        }
                                    } else break;
                                    x--;
                                }
                            } else {
                                int x = 1;
                                while (flag && I+x >= 0 && I+x < grid.size() && grid[I][J] == grid[I+x][J]) {
                                    int newKey2 = (I+x) * grid[0].size() + J;
                                    if (I+x < 0 || I+x >= grid.size() || J+dj < 0 && J+dj >= grid[0].size() || grid[I+x][J+dj] != grid[I+x][J]) {
                                        if (pvisited.count(newKey2)) {
                                            flag = false;
                                            break;
                                        }
                                    } else break;
                                    x++;
                                }
                                x = -1;
                                while (flag && I+x >= 0 && I+x < grid.size() && grid[I][J] == grid[I+x][J]) {
                                    int newKey2 = (I+x) * grid[0].size() + J;
                                    if (I+x < 0 || I+x >= grid.size() || J+dj < 0 && J+dj >= grid[0].size() || grid[I+x][J+dj] != grid[I+x][J]) {
                                        if (pvisited.count(newKey2)) {
                                            flag = false;
                                            break;
                                        }
                                    } else break;
                                    x--;
                                }
                            }
                            // if (grid[I][J] == 'X') cout << I << " " << J << " " << newI << " " << newJ << " " << flag << endl;
                            perimeter += flag;
                        }
                    }
                }

                res += perimeter * area;
                // cout << grid[i][j] << " " << perimeter << " " << area << " " << perimeter*area << endl;
            }

        }
    }

    cout << res << endl;
}