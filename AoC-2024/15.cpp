/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
stringstream ss;

char m[50][100];
vector<pii> boxes;
set<int> box_ids;
pii robot;
int n_row = 0, n_col = 0;
#if PART1
const char C_OBJ = 'O';
#else
const char C_OBJ = '[';
#endif  // PART1
string movements;
vector<pii> ds{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void read_input() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        copy(all(line), m[n_row]);
        n_row++;
        if (!n_col) n_col = line.size();
    }
    while (getline(cin, line)) movements += line;

#if PART2
    n_col *= 2;
    char m_temp[50][100];
    swap(m, m_temp);
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            if (m_temp[i][j] == '#') {
                m[i][2 * j] = '#';
                m[i][2 * j + 1] = '#';
            } else if (m_temp[i][j] == 'O') {
                m[i][2 * j] = '[';
                m[i][2 * j + 1] = ']';
            } else if (m_temp[i][j] == '.') {
                m[i][2 * j] = '.';
                m[i][2 * j + 1] = '.';
            } else if (m_temp[i][j] == '@') {
                m[i][2 * j] = '@';
                m[i][2 * j + 1] = '.';
            }
        }
    }
#endif  // PART2

    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            if (m[i][j] == C_OBJ) boxes.push_back(pii(i, j));
            if (m[i][j] == '@') robot = pii(i, j);
        }
    }
}

void solve() {
    for (char c : movements) {
        pii d, robot_new;
        if (c == '>') d = ds[0];
        else if (c == 'v') d = ds[1];
        else if (c == '<') d = ds[2];
        else if (c == '^') d = ds[3];

        // Move the robot
        robot_new = robot + d;
        // Case 1: hit the wall
        if (m[robot_new.ff][robot_new.ss] == '#') continue;
        // Case 2: move to empty place
        if (m[robot_new.ff][robot_new.ss] == '.') {
            m[robot.ff][robot.ss] = '.';
            robot = robot_new;
            m[robot.ff][robot.ss] = '@';
            continue;
        }
        // Case 3: hit objects
        box_ids.clear();
#if PART1
        while (m[robot_new.ff][robot_new.ss] == 'O') {
            box_ids.insert(find(all(boxes), robot_new) - boxes.begin());
            robot_new = robot_new + d;
        }
#else
        set<pii> move_spaces{robot_new};
        bool loop = true;
        bool blocked = false;

        while (loop && !blocked) {
            loop = false;
            int n_box = box_ids.size();
            int n_space = move_spaces.size();

            for (int box_id : box_ids) {
                pii p_box = boxes[box_id];
                if (c == '>') {
                    move_spaces.insert(p_box + d);
                    move_spaces.insert(p_box + 2 * d);
                } else if (c == 'v') {
                    move_spaces.insert(p_box + d);
                    move_spaces.insert(p_box + d + pii{0, 1});
                } else if (c == '<') {
                    move_spaces.insert(p_box + d);
                } else if (c == '^') {
                    move_spaces.insert(p_box + d);
                    move_spaces.insert(p_box + d + pii{0, 1});
                }
            }

            // Ensure the space of all objects are included
            for (pii p : move_spaces) {
                if (m[p.ff][p.ss] == '#') {
                    blocked = true;
                    break;
                } else if (m[p.ff][p.ss] == '[') {
                    move_spaces.insert(pii{p.ff, p.ss + 1});
                    box_ids.insert(find(all(boxes), p) - boxes.begin());
                } else if (m[p.ff][p.ss] == ']') {
                    move_spaces.insert(pii{p.ff, p.ss - 1});
                    box_ids.insert(find(all(boxes), pii{p.ff, p.ss - 1}) -
                                   boxes.begin());
                }
            }
            if (box_ids.size() > n_box) loop = true;
            if (move_spaces.size() > n_space) loop = true;
        }
#endif  // PART1

#if PART1
        // Case 3.1: still hit the wall
        if (m[robot_new.ff][robot_new.ss] == '#') continue;
        // Case 3.2: move all boxes along the way
        for (int id : box_ids) m[boxes[id].ff][boxes[id].ss] = '.';
        for (int id : box_ids) boxes[id] = boxes[id] + d;
        for (int id : box_ids) m[boxes[id].ff][boxes[id].ss] = 'O';
#else
        // Case 3.1: still hit the wall
        if (blocked) continue;
        // Case 3.2: move all boxes along the way
        for (int id : box_ids) {
            m[boxes[id].ff][boxes[id].ss] = '.';
            m[boxes[id].ff][boxes[id].ss + 1] = '.';
        }
        for (int id : box_ids) boxes[id] = boxes[id] + d;
        for (int id : box_ids) {
            m[boxes[id].ff][boxes[id].ss] = '[';
            m[boxes[id].ff][boxes[id].ss + 1] = ']';
        }
#endif  // PART1

        m[robot.ff][robot.ss] = '.';
        robot = robot + d;
        m[robot.ff][robot.ss] = '@';
    }

    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++)
            ans += (m[i][j] == C_OBJ) ? (i * 100 + j) : 0;
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
