/*
 *   Copyright (c) 2023 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
stringstream ss;
vector<vector<char>> grid(150, vector<char>(150, '.'));
vector<vector<int>> dist(150, vector<int>(150, 0));
pii S;
int n_row = 0, n_col = 0;
enum direction { up, down, left, right };
pii u(-1, 0), d(1, 0), l(0, -1), r(0, 1);
typedef pair<pii, direction> Point;
vector<pii> vertices;

void read_input() {
    string line;
    int j = 0;
    while (getline(cin, line)) {
        for (int i = 0; i < line.size(); i++) grid[n_row][i] = line[i];
        if (line.find('S') != string::npos) {
            j = line.find('S');
            S = pii{n_row, j};
        }
        n_row++;
        if (!n_col) n_col = line.size();
    }
}

bool good(const Point &pt) {
    const auto &[a, dir] = pt;
    if (a.ff < 0 or a.ff >= n_row) return false;
    if (a.ss < 0 or a.ss >= n_col) return false;
    char c = grid[a.ff][a.ss];
    if (c == 'S') return true;
    if (c == '.') return false;
    if (c == '|' and (dir != direction::up and dir != direction::down))
        return false;
    if (c == '-' and (dir != direction::left and dir != direction::right))
        return false;
    if (c == 'L' and (dir != direction::left and dir != direction::down))
        return false;
    if (c == 'J' and (dir != direction::right and dir != direction::down))
        return false;
    if (c == '7' and (dir != direction::up and dir != direction::right))
        return false;
    if (c == 'F' and (dir != direction::up and dir != direction::left))
        return false;
    return true;
}

Point get_next(const Point &pt) {
    const auto &[a, dir] = pt;
    char c = grid[a.ff][a.ss];
    if (c == 'S') {
        switch (dir) {
        case direction::up:
            return {a + u, direction::up};
        case direction::down:
            return {a + d, direction::down};
        case direction::left:
            return {a + l, direction::left};
        case direction::right:
            return {a + r, direction::right};
        }
    }
    if ((c == '|' and dir == direction::up) or
        (c == 'L' and dir == direction::left) or
        (c == 'J' and dir == direction::right))
        return {a + u, direction::up};
    if ((c == '|' and dir == direction::down) or
        (c == 'F' and dir == direction::left) or
        (c == '7' and dir == direction::right))
        return {a + d, direction::down};
    if ((c == '-' and dir == direction::left) or
        (c == 'J' and dir == direction::down) or
        (c == '7' and dir == direction::up))
        return {a + l, direction::left};
    if ((c == '-' and dir == direction::right) or
        (c == 'F' and dir == direction::up) or
        (c == 'L' and dir == direction::down))
        return {a + r, direction::right};
    return {a, direction::down};
}

void solve() {
    // 4 neighboring points
    vector<pair<pii, direction>> pts;
    pts.push_back({S, direction::up});
    pts.push_back({S, direction::down});
    pts.push_back({S, direction::left});
    pts.push_back({S, direction::right});

    pair<pii, direction> pt;

    for (auto pt : pts) {
        // Re-init dist matrix and answer
        for (int i = 0; i < n_row; i++) {
            for (int j = 0; j < n_col; j++) {
                dist[i][j] = 0;
            }
        }
        ans = 0;
        vertices.clear();

        // Depth-first search
        while (good(pt)) {
            vertices.push_back(pt.ff);
            if (pt.ff == S and ans != 0) {
                print("ans", "=", (ans + 1) / 2, ans);
                return;
            }
            dist[pt.ff.ff][pt.ff.ss] = ans;
            pt = get_next(pt);
            ans++;
        }
    }
}

void solve_2() {
    // Calculate the area of the polygon with Shoelace formula
    // https://en.wikipedia.org/wiki/Shoelace_formula
    int area = 0;
    for (int i = 0; i < vertices.size() - 1; i++) {
        area += vertices[i].ff * vertices[i + 1].ss;
        area -= vertices[i].ss * vertices[i + 1].ff;
    }

    // Calculate the number of interior points with Pick's theorem
    // https://en.wikipedia.org/wiki/Pick%27s_theorem
    area = abs(area) / 2;
    print("area =", area, "");
    ans = area + 1 - (vertices.size() - 1) / 2;
    print("ans =", ans, "");
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
#if PART2
    solve_2();
#endif  // PART2
    return 0;
}
