#include <cctype>
#include <fstream>
#include <iterator>
#include <math.h>
#include <pthread.h>
#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

char BLANK = 'X';
string num_strs[] = {"one", "two", "three", "four", "five", "six",
    "seven", "eight", "nine"};
map<string, int> m{{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
    {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};


int is_num_str(const string& str, const int& id) {
    if (isdigit(str[id]))
        return str[id] - '0';
    for (string num_str : num_strs) {
        // Check if the remaining substring is too short
        if (num_str.size() > str.size() - id)
            continue;
        // Check if it is the same number string
        if (str.substr(id, num_str.size()) == num_str)
            return m[num_str];
    }
    return 0;
};

void solve()
{
    string line;
    int total_calibration_value = 0;
    ifstream fileIn("1.txt");
    if (fileIn.is_open()) {
        while (getline(fileIn, line)) {
            char c_start = BLANK, c_end = BLANK;
            for (char c : line) {
                if (isdigit(c)) {
                    c_start = c;
                    break;
                }
            }

            reverse(line.begin(), line.end()); 
            for (char c : line) {
                if (isdigit(c)) {
                    c_end = c;
                    break;
                }
            }
            total_calibration_value += 10 * (c_start - '0') + (c_end - '0');
        }
        fileIn.close();
    }   else cout << "Unable to open file" << endl;
    cout << total_calibration_value << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
