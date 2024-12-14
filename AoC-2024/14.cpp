/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
stringstream ss;
char c;
int n_row = 103;
int n_col = 101;
int m[103][101];
// int n_row = 7;
// int n_col = 11;
// int m[7][11];
int t = 100;

struct Robot {
    pii p, v;
    Robot(pii _p, pii _v) : p(_p), v(_v) {}
};
vector<Robot> robots;

void read_input() {
    string line;
    int x, y;
    while (getline(cin, line)) {
        replace(all(line), '=', ' ');
        replace(all(line), ',', ' ');
        ss.clear();
        ss.str(line);
        ss >> c >> x >> y;
        pii p(x, y);
        ss >> c >> x >> y;
        pii v(x, y);
        robots.push_back(Robot(p, v));
    }
}

void solve() {
#if PART1
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    for (Robot &r : robots) {
        r.p = r.p + 100 * r.v;
        r.p.ff = ((r.p.ff % n_col) + n_col) % n_col;
        r.p.ss = ((r.p.ss % n_row) + n_row) % n_row;

        if (r.p.ss < n_row / 2 && r.p.ff < n_col / 2) q1++;
        else if (r.p.ss < n_row / 2 && r.p.ff > n_col / 2) q2++;
        else if (r.p.ss > n_row / 2 && r.p.ff < n_col / 2) q3++;
        else if (r.p.ss > n_row / 2 && r.p.ff > n_col / 2) q4++;
    }
    ans = q1 * q2 * q3 * q4;
#else
    ans = 6876;  // god damn it :)
    for (Robot &r : robots) {
        r.p = r.p + ans * r.v;
        r.p.ff = ((r.p.ff % n_col) + n_col) % n_col;
        r.p.ss = ((r.p.ss % n_row) + n_row) % n_row;
    }

    for (Robot r : robots) m[r.p.ss][r.p.ff]++;
    for (int i = 35; i < 75; i++) {
        for (int j = 14; j < 54; j++) {
            if (m[i][j] == 0) cout << '.';
            else cout << m[i][j];
        }
        cout << endl;
    }
    // for (int t = 6801; t < 6900; t++) {
    //     ofstream myfile;
    //     myfile.open("test/" + to_string(t) + ".txt");
    //     // Reset map
    //     for (int i = 0; i < n_row; i++)
    //         for (int j = 0; j < n_col; j++) m[i][j] = 0;
    //
    //     for (Robot &r : robots) {
    //         r.p = r.p + r.v;
    //         r.p.ff = ((r.p.ff % n_col) + n_col) % n_col;
    //         r.p.ss = ((r.p.ss % n_row) + n_row) % n_row;
    //     }
    //
    //     myfile << "t = " << t << endl;
    //     for (Robot r : robots) m[r.p.ss][r.p.ff]++;
    //     for (int i = 0; i < n_row; i++) {
    //         for (int j = 0; j < n_col; j++) {
    //             if (m[i][j] == 0) myfile << '.';
    //             else myfile << m[i][j];
    //         }
    //         myfile << endl;
    //     }
    //     myfile.close();
    // }
#endif  // PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
