/*
 *   Copyright (c) 2022 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

#if !PART1
void update_top3(int arr[3], const int &val) {
    if (val <= arr[0]) return;
    if (val <= arr[1]) {
        arr[0] = val;
        return;
    }
    arr[0] = arr[1];
    if (val <= arr[2]) {
        arr[1] = val;
        return;
    }
    arr[1] = arr[2];
    arr[2] = val;
}
#endif

void solve() {
    string line;
    int sum = 0;
#if PART1
    int max = 0;
#else
    int top3_vals[3] = {0};
#endif

    ifstream fileIn("day1.txt");
    if (fileIn.is_open()) {
        while (getline(fileIn, line)) {
            if (line.empty()) {
#if PART1
                max = (max < sum) ? sum : max;
#else
                update_top3(top3_vals, sum);
#endif
                sum = 0;
            } else {
                sum += stoi(line);
            }
        }
        fileIn.close();
    } else cout << "Unable to open file" << endl;

#if PART1
    max = (max < sum) ? sum : max;
    cout << max << endl;
#else
    update_top3(top3_vals, sum);
    cout << top3_vals[0] + top3_vals[1] + top3_vals[2] << endl;
#endif
}

int main(int argc, char const *argv[]) {
    solve();
    return 0;
}
