#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <array>

#define DEBUG true

using namespace std;
using Coord = pair<int, int>;
#define x first
#define y second
const int N = 10;       // the number of knots

vector<Coord> get_trajectory()
{
    // Trajectory of the tail
    vector<Coord> traj = { make_pair(0, 0) };
    vector<Coord> knots(N, make_pair(0, 0));
    // Lambda function to check if a knot is in neighbor of its head
    auto in_neighbor = [&](int id) {
        int diff_x = knots[id].x - knots[id-1].x;
        int diff_y = knots[id].y - knots[id-1].y;
        if (diff_x > 1 || diff_x < -1 || diff_y > 1 || diff_y < -1)
            return false;
        return true;
    };
    // Lambda function to update knot's position based on its head
    auto update_pos = [&](int id){
        if (in_neighbor(id))            // skip if still in neighbor
            return;
        int x_head = knots[id-1].x;
        int y_head = knots[id-1].y;
        int diff_x = knots[id].x - x_head;
        int diff_y = knots[id].y - y_head;
        // Move diagonally first
        if (diff_x != 0 && diff_y != 0) {
            int diff = abs(diff_x) > abs(diff_y) ? abs(diff_y)-1 : abs(diff_x)-1;
            knots[id].x += (x_head > knots[id].x) ? diff : -diff;
            knots[id].y += (y_head > knots[id].y) ? diff : -diff;
            if (in_neighbor(id))        // skip if already in neighbor
                return;
            knots[id].x += (x_head > knots[id].x) ? 1 : -1;
            knots[id].y += (y_head > knots[id].y) ? 1 : -1;
        }
        if (in_neighbor(id))            // skip if already in neighbor
            return;
        // Move either horizontally or vertically
        if (x_head == knots[id].x) {
            knots[id].y = (y_head > knots[id].y) ? y_head - 1 : y_head + 1;
            return;
        }   else if (y_head == knots[id].y) {
            knots[id].x = (x_head > knots[id].x) ? x_head - 1 : x_head + 1;
            return;
        }
    };

    char c; int d;
    while (cin >> c) {
        cin >> d;
        // Update head position
        if (c == 'R')
            knots[0].x += d;
        else if (c == 'L')
            knots[0].x -= d;
        else if (c == 'U')
            knots[0].y += d;
        else if (c == 'D')
            knots[0].y -= d;
        // Update knots' positions
        for (int i = 1; i < N; i++) {
            if (!in_neighbor(i)) {
                update_pos(i);
            }
        }
        // Append new point to trajectory, if needed
        if (knots.back() != traj.back())
            traj.push_back(knots.back());   
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
    cout << "Range x: " << x_min << " " << x_max << endl;
    cout << "Range y: " << y_min << " " << y_max << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
