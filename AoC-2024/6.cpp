/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;

char m[130][130];
char m_backup[130][130];
bool v[130][130][4];
int n_row = 0, n_col = 0;
int x = -1, y = -1, d = -1;
int xs = -1, ys = -1, ds = -1;
bool loop = false;
using pos = tuple<int, int, int>;

void read_input() {
    string line;
    // Possible starting char
    const char D[] = "^>v<";
    while (getline(cin, line)) {
        n_row++;
        if (!n_col) n_col = line.size();
        copy(all(line), m[n_row - 1]);

        // Find the starting position
        if (x == -1 || y == -1 || d == -1) {
            // Iterate over all possible starting char
            for (int i = 0; i < 4; i++) {
                if (line.find(D[i]) != string::npos) {
                    x = n_row - 1;
                    y = line.find(D[i]);
                    d = i;
                    break;
                }
            }
        }
    }

    // Backup the original map and starting position
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_row; j++) {
            m_backup[i][j] = m[i][j];
        }
    }
    xs = x;
    ys = y;
    ds = d;
}

// Initialize simulation with original map, empty visited map and no loop
void init_sim() {
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_row; j++) {
            m[i][j] = m_backup[i][j];
            for (int k = 0; k < 4; k++) {
                v[i][j][k] = false;
            }
        }
    }
    loop = false;
}

// Simulate the roll-out
void simulate() {
    // The next position
    int x_new, y_new;
    while (!loop) {
        // Mark visited positions
        if (v[x][y][d]) loop = true;
        else v[x][y][d] = true;

        // Update the next position
        x_new = x;
        y_new = y;
        if (d == 0) x_new--;
        else if (d == 1) y_new++;
        else if (d == 2) x_new++;
        else if (d == 3) y_new--;

        if (x_new < 0 || x_new == n_row || y_new < 0 || y_new == n_col) {
            // Break if get of the map
            break;
        } else if (m[x_new][y_new] == '#') {
            // Turn in place if hit obstacle
            d = (d + 1) % 4;
            x_new = x;
            y_new = y;
        } else {
            // Move forward
            x = x_new;
            y = y_new;
        }
    }
}

bool check_visited(const int &i, const int &j) {
    bool visited = false;
    for (int k = 0; k < 4; k++) visited = visited || v[i][j][k];
    return visited;
}

void solve() {
    init_sim();
    simulate();

    vector<pii> possible_obstacles;
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            if (!check_visited(i, j)) continue;
#if PART1
            // Count visited positions
            ans++;
#else
            // Find all possible positions to put obstacles and possible
            // starting poses
            if (i == xs && j == ys) continue;
            possible_obstacles.push_back(pii{i, j});
#endif  // PART1
        }
    }

#if !PART1
    // Brute force over all possible obstacles
    for (pii obs : possible_obstacles) {
        init_sim();
        // Add new obstacle
        m[obs.ff][obs.ss] = '#';
        // Set starting pose
        x = xs;
        y = ys;
        d = ds;
        simulate();
        if (loop) ans++;
    }
#endif  // !PART1
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
