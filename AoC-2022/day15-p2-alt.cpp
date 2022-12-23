#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <array>

using namespace std;
#define x first
#define y second
#define sensor first
#define beacon second
using Coord = pair<int, int>;
using CoordPair = pair<Coord, Coord>;

#define TEST true
#if TEST
const int RANGE = 20;
#else
const int RANGE = 4'000'000;
#endif

// Read input
vector<CoordPair> read_input();
// Get Manhattan distance between two points
int get_dist(const Coord &p1, const Coord &p2);

struct Interval
{
    int xmin, xmax;
    Interval(int a, int b) : xmin(a), xmax(b) {};
};

vector<Interval> operator-(const Interval &in1, const Interval &in2);
vector<Interval> operator-(const vector<Interval> &ins, const Interval &in);
// vector<Interval> merge_interval(const Interval &i1, const Interval &i2);

void solve()
{
    vector<CoordPair> sensor_beacons = read_input();

    array<char, RANGE + 1> grid;
    grid.fill('#');

    // Scan each row at a time
    for (int i = 0; i <= RANGE; i++) {
        grid.fill('.');
        int cmin = 0, cmax = RANGE; // The min, max range of uncheck cells
        for (auto &[s, b] : sensor_beacons) {
            if (cmin > cmax)        // Already check every grid cell
                break;
            if (s.x >= 0 && s.x <= RANGE && s.y == i)
                grid[s.x] = 'S';    // Cell with sensor
            if (b.x >= 0 && b.x <= RANGE && b.y == i)
                grid[b.x] = 'B';    // Cell with beacon
            
            int d = get_dist(s, b);
            if (get_dist(s, make_pair(s.x, i)) > d)
                continue;           // Row is out of sensor reach

            int h = get_dist(s, make_pair(s.x, i));
            int xmin = (s.x - (d - h) >= 0) ? s.x - (d - h) : 0;
            int xmax = (s.x + (d - h) <= RANGE) ? s.x + (d - h) : RANGE;
            // Reduce the set range
            xmin = (xmin < cmin) ? cmin : xmin;
            xmax = (xmax > cmax) ? cmax : xmax;
            for (int j = xmin; j <= xmax; j++) {
                if (grid[j] == '.') {
                    grid[j] = '#';
                }
            }
            // Reduce the search range
            while (cmin <= cmax && grid[cmin] == '#') { cmin++; }
            while (cmin <= cmax && grid[cmax] == '#') { cmax--; }
        }

        // cout << i << "/" << RANGE << endl;
#if TEST
        // Print the grid
        cout << i << "\t";
        for (int j = 0; j <= RANGE; j++) {
            cout << grid[j];
        }   cout << endl;
#endif
        // Check if there is solution
        // for (int j = 0; j <= RANGE; j++) {
        //     if (grid[j] == '.') {
        //         cout << "Tuning frequency: "
        //              << 4'000'000 * j + i << endl;
        //         return;
        //     }
        // }
    }

    // for (int i = 0; i <= RANGE; i++) {
    //     cout << i << endl;
    //     for (int j = 0; j <= RANGE; j++) {
    //         if (grid[j] == '.') {
    //             cout << "Tuning frequency: "
    //                     << 4'000'000 * j + i << endl;
    //             return;
    //         }
    //     }
    // }
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

vector<Interval> operator-(const Interval &in1, const Interval &in2)
{

}

vector<Interval> operator-(const vector<Interval> &ins, const Interval &in)
{
    
}