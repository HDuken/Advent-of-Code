#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;
#define x first
#define y second
#define sensor first
#define beacon second
using Coord = pair<int, int>;
using CoordPair = pair<Coord, Coord>;

#define TEST false
#if TEST
const int Y = 10;
#else
const int Y = 2'000'000;
#endif

vector<CoordPair> read_input();

// Get Manhattan distance between two points
int get_dist(const Coord &p1, const Coord &p2);

void get_range(int &xmin, int &xmax, const vector<CoordPair> &vects);

void solve()
{
    vector<CoordPair> sensor_beacons = read_input();

    // Find the range to create the grid map
    int xmin = 0, xmax = 0;
    get_range(xmin, xmax, sensor_beacons);

    // The grid map (we only care about a single row)
    bool grid[xmax - xmin + 1] = { false };
    auto shift_x = [&](int x){ return x - xmin; };

    // Fill in the grid
    for (auto &[s, b] : sensor_beacons) {
        int x = s.x, xd = 0;
        int d = get_dist(s, b);
        if (get_dist(s, make_pair(x, Y)) > d)
            continue;
        while (get_dist(s, make_pair(x + xd, Y)) <= d) {
            grid[shift_x(x - xd)] = true;
            grid[shift_x(x + xd)] = true;
            xd ++;
        }
    }

#if TEST
    // Print the grid
    for (int i = 0; i < xmax - xmin + 1; i++) {
        if (grid[i])
            cout << '#';
        else
            cout << '.';
    }   cout << endl;
#endif

    int result = 0;
    for (int i = 0; i < xmax - xmin + 1; i++) {
        if (grid[i])
            result ++;
    }
    vector<Coord> beacons;
    for (auto &[s, b] : sensor_beacons) {
        if (b.y == Y && find(beacons.begin(), beacons.end(), b) == beacons.end())
            beacons.push_back(b);
    }
    cout << "Result = " << result - beacons.size() << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
} 

vector<CoordPair> read_input()
{
    vector<CoordPair> output;
    string str;
    char c;
    int xs, ys, xb, yb;     // x and y coordinates of sensor and beacon
    while (cin >> str) {
        cin >> str >> c >> c >> xs >> c;
        cin >> c >> c >> ys >> c;
        cin >> str >> str >> str >> str >> c >> c >> xb;
        cin >> c >> c >> c >> yb;
        output.push_back(make_pair(make_pair(xs, ys), make_pair(xb, yb)));
    }
    return output;
}

int get_dist(const Coord &p1, const Coord &p2)
{
    int result = 0;
    result += (p1.x > p2.x) ? (p1.x - p2.x) : (p2.x - p1.x);
    result += (p1.y > p2.y) ? (p1.y - p2.y) : (p2.y - p1.y);
    return result;    
}

void get_range(int &xmin, int &xmax, const vector<CoordPair> &vects)
{
    // Initialize random value
    xmin = vects[0].sensor.x;
    xmax = xmin;
    // Iterate over all sensor and beacon positions
    for (auto &[s, b] : vects) {
        int v1 = s.x - get_dist(s, b);
        int v2 = s.x + get_dist(s, b);
        xmin = (xmin > v1) ? v1 : xmin;
        xmax = (xmax < v2) ? v2 : xmax;
    }
}
