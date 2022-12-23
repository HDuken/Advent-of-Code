#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <utility>

using namespace std;
#define x first
#define y second
using Coord = pair<int, int>;
using CoordPair = pair<Coord, Coord>;
using LL = long long;

#define TEST false
#if TEST
const int RANGE = 20;
#else
const int RANGE = 4'000'000;
#endif

// Read input
vector<CoordPair> read_input();
// Get Manhattan distance between two points
int get_dist(const Coord &p1, const Coord &p2);
// Get Manhattan distance between point and a horizontal line
int get_dist(const Coord &p1, const int &y_val);

struct Interval
{
    int xmin = -1, xmax = -1;
    Interval(int a, int b) : xmin(a), xmax(b) {};
    bool empty() const;
};
vector<Interval> operator-(const Interval &in1, const Interval &in2);
vector<Interval> operator-(const vector<Interval> &ins, const Interval &in);

Interval get_interval(const Coord &p1, const int &dist, const int &y_val);

void solve()
{
    vector<CoordPair> sensor_beacons = read_input();

    // Scan each row at a time
    for (int i = 0; i <= RANGE; i++) {
        cout << "Row " << i << "/" << RANGE << endl;
        // Initialize interval
        vector<Interval> intervals(1, Interval(0, RANGE));
        for (auto &[s, b] : sensor_beacons) {
            int d = get_dist(s, b);
            Interval sub_interval = get_interval(s, d, i);
            if (sub_interval.empty())
                continue;
            intervals = intervals - sub_interval;
            if (intervals.empty())
                break;
        }
        if (!intervals.empty()) {
            cout << "Tuning frequency: "
                 << (LL)4'000'000 * intervals[0].xmin + i << endl;
            return;
        }
    }
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
        output.push_back(
            make_pair(make_pair(xs, ys), make_pair(xb, yb)));
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

int get_dist(const Coord &p1, const int &y_val)
{
    return (p1.y > y_val) ? p1.y -y_val : y_val - p1.y;
}

bool Interval::empty() const { return xmin == -1 && xmax == -1; }

vector<Interval> operator-(const Interval &in1, const Interval &in2)
{
    vector<Interval> output;
    if (in1.xmax < in2.xmin || in1.xmin > in2.xmax) {
        output.push_back(in1);      // No intersection
        return output;
    }
    if (in2.xmin > in1.xmin) {
        output.push_back(Interval(in1.xmin, in2.xmin - 1));
    }
    if (in2.xmax < in1.xmax) {
        output.push_back(Interval(in2.xmax + 1, in1.xmax));
    }
    return output;
}

vector<Interval> operator-(const vector<Interval> &ins, const Interval &in)
{
    vector<Interval> output;
    for (auto i : ins) {
        vector<Interval> sub = i - in;
        for (auto elem : sub) {
            output.push_back(elem);
        }
    }
    return output;
}

Interval get_interval(
    const Coord &p1, const int &dist, const int &y_val)
{
    int h = get_dist(p1, y_val);
    if (h > dist) {
        return Interval(-1, -1);
    }
    return Interval(p1.x - (dist - h), p1.x + (dist - h));
}
