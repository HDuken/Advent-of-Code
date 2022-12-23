#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <array>

using namespace std;
using Coord = pair<int, int>;
#define x first
#define y second

vector<Coord> get_trajectory()
{
    // Trajectory of the tail
    vector<Coord> traj = { make_pair(0, 0) };

    int x_head = 0, y_head = 0, x_tail = 0, y_tail = 0;

    // Lambda function to check if tail is in neighbor of head
    auto in_neighbor = [&]() {
        if (x_head - x_tail > 1 || x_head - x_tail < -1)
            return false;
        if (y_head - y_tail > 1 || y_head - y_tail < -1)
            return false;
        return true;
    };

    char c;
    int d;
    while (cin >> c) {
        cin >> d;
        // Update head position
        if (c == 'R')
            x_head += d;
        else if (c == 'L')
            x_head -= d;
        else if (c == 'U')
            y_head += d;
        else if (c == 'D')
            y_head -= d;
        // Update tail position, if needed
        if (!in_neighbor()) {
            x_tail = x_head;
            y_tail = y_head;
            if (c == 'R')
                x_tail = x_head - 1;
            else if (c == 'L')
                x_tail = x_head + 1;
            else if (c == 'U')
                y_tail = y_head - 1;
            else if (c == 'D')
                y_tail = y_head + 1;
            traj.push_back(make_pair(x_tail, y_tail));
        }
    }
    return traj;
}

void solve()
{
    vector<Coord> traj = get_trajectory();

    // Find the range of the map
    int x_min = 0, x_max = 0, y_min = 0, y_max = 0;
    for (auto const &pt : traj) {
        x_min = (pt.x < x_min) ? pt.x : x_min;
        x_max = (pt.x > x_max) ? pt.x : x_max;
        y_min = (pt.y < y_min) ? pt.y : y_min;
        y_max = (pt.y > y_max) ? pt.y : y_max;
    }
    // Shift the range
    for (auto &pt : traj) {
        pt.x -= x_min;
        pt.y -= y_min;
    }
    x_max -= x_min;
    y_max -= y_min;

    // The grid map of visited cells
    bool visited[y_max + 1][x_max + 1] = { false };
    for (int y = 0; y < y_max + 1; y++) {
        for (int x = 0; x < x_max + 1; x++) {
            visited[y][x] = false;
        }
    }

    // Update the grid using the trajectory
    visited[-y_min][-x_min] = true;
    int n = traj.size();
    for (int i = 1, x, y; i < n; i++) {
        x = traj[i - 1].x;
        y = traj[i - 1].y;
        if (traj[i].x != x && traj[i].y != y) {
            x += (traj[i].x > x) ? 1 : -1;
            y += (traj[i].y > y) ? 1 : -1;
        }
        while ((y != traj[i].y) || (x != traj[i].x)) {
            visited[y][x] = true;
            if (traj[i].x == x)
                y += (traj[i].y > y) ? 1 : -1;
            else
                x += (traj[i].x > x) ? 1 : -1;
        }
        visited[traj[i].y][traj[i].x] = true;
    }

    // Count visited cells
    int result = 0;
    for (int y = 0; y < y_max + 1; y++) {
        for (int x = 0; x < x_max + 1; x++) {
            if(visited[y][x])
                result++;
        }
    }
    cout << result << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
