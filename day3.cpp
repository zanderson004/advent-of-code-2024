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
    string text, line;
    while (cin >> line) text += line;

    int res = 0;

    char state = 'm';
    string firstNum, secondNum;
    bool doState = true;
    for (char c : text) {
        if (c == 'd') state = 'd';
        if (doState){
        switch (state) {
            case 'm':
                if (c == state) state = 'u';
                break;
            case 'u':
                if (c == state) state = 'l';
                else state = 'm';
                break;
            case 'l':
                if (c == state) state = '(';
                else state = 'm';
                break;
            case '(':
                if (c == state) {
                    state = 0;
                    firstNum = "";
                }
                else state = 'm';
                break;
            case 0:
                if (isdigit(c)) firstNum += c;
                else if (c == ',') {
                    secondNum = "";
                    state = 1;
                }
                else state = 'm';
                break;
            case 1:
                if (isdigit(c)) secondNum += c;
                else if (c == ')') {
                    res += stoi(firstNum) * stoi(secondNum);
                    state = 'm';
                }
                else state = 'm';
                break;
            case 'd':
                if (c == state) state = 'o';
                else state = 'm';
                break;
            case 'o':
                if (c == state) state = 'n';
                else state = 'm';
                break;
            case 'n':
                if (c == state) state = '\'';
                else state = 'm';
                break;
            case '\'':
                if (c == state) state = 't';
                else state = 'm';
                break;
            case 't':
                if (c == state) state = 3;
                else state = 'm';
                break;
            case 3:
                if (c == '(') state = 4;
                else state = 'm';
                break;
            case 4:
                if (c == ')') {
                    state = 'd';
                    doState = false;
                }
                else state = 'm';
                break;
            default:
                cout << "err" << endl;
                break;
        }}
        else {
            switch (state) {
                case 'd':
                    if (c == state) state = 'o';
                    break;
                case 'o':
                    if (c == state) state = '(';
                    else state = 'd';
                    break;
                case '(':
                    if (c == state) state = ')';
                    else state = 'd';
                    break;
                case ')':
                    if (c == state) {
                        state = 'm';
                        doState = true;
                    }
                    else state = 'd';
                    break;
                default:
                    cout << "Err" << endl;
                    break;
            }
        }
    }

    cout << res << endl;
}