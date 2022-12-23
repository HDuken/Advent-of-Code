#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <utility>
#include <climits>

using namespace std;
using Coord = pair<int, int>;
#define x first
#define y second

void solve()
{
    // Pre-check the size of the map (string.size() and count lines)
    // int const R = 5, C = 8;         // for test
    int const R = 41, C = 181;      // for real input

    int xe = 0, ye = 0;                 // End position
    char h[R][C];                       // height map
    int d[R][C];                        // distance map from start
    for (int row = 0; row < R; row++) {
        for (int col = 0; col < C; col++) {
            d[row][col] = INT_MAX;      // Initialize distance to MAX
        }
    }    

    // Read input
    for (int row = 0; row < R; row++) {
        for (int col = 0; col < C; col++) {
            cin >> h[row][col];
            if (h[row][col] == 'S') {
                h[row][col] = 'a';
            }   else if (h[row][col] == 'E') {
                ye = row;
                xe = col;
                h[row][col] = 'z';
            }
        }
    }

    // BFS - Breadth-first search
    vector<Coord> to_visit;
    // Initialize the list with all level-a points
    for (int row = 0; row < R; row++) {
        for (int col = 0; col < C; col++) {
            if (h[row][col] == 'a') {
                d[row][col] = 0;
                to_visit.push_back(make_pair(col, row));
            }
        }
    }

    // Lambda function to visit a cell and update the list
    auto visit = [&](int c0, int r0, int c, int r){
        if (r < 0 || r >= R ||          // Out of range
            c < 0 || c >= C ||          // Out of range
            d[r][c] != INT_MAX ||       // Already visited
            h[r][c] - h[r0][c0] > 1)    // Elevation too high
            return;
        d[r][c] = d[r0][c0] + 1;
        to_visit.push_back(make_pair(c, r));
    };

    while (!to_visit.empty()) {
        int x = to_visit.front().x, y = to_visit.front().y;
        visit(x, y, x, y-1);
        visit(x, y, x, y+1);
        visit(x, y, x+1, y);
        visit(x, y, x-1, y);
        to_visit.erase(to_visit.begin());
        if (d[ye][xe] != INT_MAX)
            break;
    }

    // Print the map (for fun)
    for (int row = 0; row < R; row++) {
        for (int col = 0; col < C; col++) {
            cout << d[row][col] << " ";
        }   
        cout << endl;
    }
    cout << d[ye][xe] << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
