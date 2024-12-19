#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define TEST false

template<typename T>
struct triplet
{
    T x, y, z;
    triplet (const T &m1, const T &m2, const T &m3)
    : x(m1), y(m2), z(m3) {};
};
using Point = triplet<int>;
vector<Point> read_input();

enum BLOCK { LAVA, AIR, STEAM };
using Grid = vector<vector<vector<BLOCK>>>;
vector<int> get_grid_range(const vector<Point> &points);
// Print the grid slice by slice
void print_grid(const Grid &grid, const vector<int> &range);
void fill_grid(Grid &grid, const vector<Point> &points);
void fill_steam(
    Grid &grid, const vector<int> &range, int x, int y, int z);
int get_surface_area(const Grid &grid, const vector<Point> &points);


void solve()
{
    vector<Point> points = read_input();
    // Get the range for the 3D grid
    vector<int> range = get_grid_range(points);
    // The 3D grid
    Grid grid(
        range[1] - range[0] + 3, vector<vector<BLOCK>>(
            range[3] - range[2] + 3, vector<BLOCK>(
                range[5] - range[4] + 3, AIR))
    );
    fill_grid(grid, points);
    fill_steam(grid, range, range[0] - 1, range[2] - 1, range[4] - 1);

    int result = get_surface_area(grid, points);
    cout << "Exterior surface area: " << result << endl;
#if TEST
    print_grid(grid, range);
#endif
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}

vector<Point> read_input()
{
    vector<Point> points;
    int x, y, z;
    char c;
    while (cin >> x) {
        cin >> c >> y >> c >> z;
        points.push_back(triplet<int>(x, y, z));
    }
    return points;
}

vector<int> get_grid_range(const vector<Point> &points)
{
    int xmin = points[0].x, xmax = points[0].x;
    int ymin = points[0].y, ymax = points[0].y;
    int zmin = points[0].z, zmax = points[0].z;
    for (auto pt : points) {
        xmin = min(xmin, pt.x); xmax = max(xmax, pt.x);
        ymin = min(ymin, pt.y); ymax = max(ymax, pt.y);
        zmin = min(zmin, pt.z); zmax = max(zmax, pt.z);
    };
    return vector<int>{ xmin, xmax, ymin, ymax, zmin, zmax };
}

void print_grid(const Grid &grid, const vector<int> &range)
{
    auto cell = [&](const int &x, const int &y, const int &z) {
        return grid[x - range[0] + 1][y - range[2] + 1][z - range[4] + 1];
    };
    for (int x = range[0] - 1; x <= range[1] + 1; x++) {
        for (int y = range[2] - 1; y <= range[3] + 1; y++) {
            for (int z = range[4] - 1; z <=  range[5] + 1; z++) {
                if (cell(x, y, z) == LAVA)
                    cout << "#";
                else if (cell(x, y, z) == STEAM)
                    cout << "?";
                else
                    cout << ".";
            }   cout << endl;
        }   cout << endl;
    }
}

void fill_grid(Grid &grid, const vector<Point> &points)
{
    vector<int> range = get_grid_range(points);
    for (auto pt : points) {
        grid[pt.x - range[0] + 1][pt.y - range[2] + 1][pt.z - range[4] + 1] = LAVA;
    }
}

int get_surface_area(const Grid &grid, const vector<Point> &points)
{
    int result = 0;
    vector<int> range = get_grid_range(points);
    auto is_steam = [&](const int &x, const int &y, const int &z) {
        return grid[x - range[0] + 1][y - range[2] + 1][z - range[4] + 1] == STEAM;
    };

    // Check 6 neighbors for possible surface area
    auto check_cell = [&](const Point &p){
        int output = 0;
        output += is_steam(p.x - 1, p.y, p.z);
        output += is_steam(p.x + 1, p.y, p.z);
        output += is_steam(p.x, p.y - 1, p.z);
        output += is_steam(p.x, p.y + 1, p.z);
        output += is_steam(p.x, p.y, p.z - 1);
        output += is_steam(p.x, p.y, p.z + 1);
        return output;
    };

    for (auto pt : points) {
        result += check_cell(pt);
    }
    return result;
}

void fill_steam(
    Grid &grid, const vector<int> &range, int x, int y, int z)
{
    if (x < range[0] - 1 || x > range[1] + 1 ||
        y < range[2] - 1 || y > range[3] + 1 ||
        z < range[4] - 1 || z > range[5] + 1)
        return;
    BLOCK cell = grid[x - range[0] + 1][y - range[2] + 1][z - range[4] + 1];
    if (cell == LAVA || cell == STEAM)
        return;
    grid[x - range[0] + 1][y - range[2] + 1][z - range[4] + 1] = STEAM;
    fill_steam(grid, range, x - 1, y, z);
    fill_steam(grid, range, x + 1, y, z);
    fill_steam(grid, range, x, y - 1, z);
    fill_steam(grid, range, x, y + 1, z);
    fill_steam(grid, range, x, y, z - 1);
    fill_steam(grid, range, x, y, z + 1);
}
