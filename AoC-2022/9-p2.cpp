#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <array>

#define DEBUG false

using namespace std;
using Coord = pair<int, int>;
#define x first
#define y second
const int N = 10;       // the number of knots

void solve()
{
    vector<Coord> knots(N, make_pair(0, 0));

    // The range of the map (from day9-p2-get_size.cpp)
    const int X_MIN = -121, X_MAX = 37 + 121;
    const int Y_MIN = -68, Y_MAX = 456 + 68;
 
    // The grid map of visited cells
    bool visited[Y_MAX - Y_MIN + 1][X_MAX - X_MIN + 1];
    for (int y = 0; y < Y_MAX + 1; y++) {
        for (int x = 0; x < X_MAX + 1; x++) {
            visited[y][x] = false;
        }
    }

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
        if (in_neighbor(id))        // skip if still in neighbor
            return;
        int x_head = knots[id-1].x;
        int y_head = knots[id-1].y;
        int diff_x = knots[id].x - x_head;
        int diff_y = knots[id].y - y_head;
        // Move diagonally first
        if (diff_x != 0 && diff_y != 0) {
            knots[id].x += (x_head > knots[id].x) ? 1 : -1;
            knots[id].y += (y_head > knots[id].y) ? 1 : -1;
        }
        if (in_neighbor(id))        // skip if already in neighbor
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

    // Update the grid
    visited[-Y_MIN][-X_MIN] = true;     // start position
    int d = 0; char c;
    while (cin >> c) {
        cin >> d;
        while (d > 0) {                 // Move one step at a time
            if (c == 'R')
                knots[0].x += 1;
            else if (c == 'L')
                knots[0].x -= 1;
            else if (c == 'U')
                knots[0].y += 1;
            else if (c == 'D')
                knots[0].y -= 1;
            d--;
            // Update knots' positions
            for (int i = 1; i < N; i++) {
                if (!in_neighbor(i)) {
                    update_pos(i);
                }
            }
            // Mark visited (Shift the range)
            visited[knots.back().y - Y_MIN][knots.back().x - X_MIN] = true;
        }
    }

    // Count visited cells
    int result = 0;
    for (int y = 0; y < Y_MAX + 1; y++) {
        for (int x = 0; x < X_MAX + 1; x++) {
            if (visited[y][x])
                result++;
        }
    }
#if DEBUG
    // Print the visited grid map
    for (int y = Y_MAX; y >= 0; y--) {
        for (int x = 0; x < X_MAX + 1; x++) {
            if (y == -Y_MIN && x == -X_MIN) {
                cout << 's';
                continue;
            }
            if (visited[y][x])
                cout << '#';
            else
                cout <<'.';
        }
        cout << endl;
    }
#endif
    cout << result << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
