#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>

using namespace std;
using Coord = pair<int, int>;
#define x first
#define y second
using Path = vector<pair<int, int>>;
using Grid = vector<vector<char>>;
const char ROCK = '#', AIR = '.', SAND = 'o';
const int SOURCE = 500;
const int FALLING = 0, STOP = 1, OFFMAP = 2;

vector<Path> read_input()
{
    vector<Path> output;
    ifstream infile("day14.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            int x, y;
            string str;
            char c;
            Path p;
            stringstream ss(line);
            while (ss >> x) {
                ss >> c >> y >> str;
                p.push_back(make_pair(x, y));
            }
            output.push_back(p);
        }
    }   else cout << "Unable to openfile";

    return output;
}

void solve()
{
    vector<Path> paths = read_input();
    int xmin = SOURCE, xmax = 0, ymax = 0;
    for (auto p : paths) {
        for (auto pt : p) {
            xmin = (xmin > pt.x) ? pt.x : xmin;
            xmax = (xmax < pt.x) ? pt.x : xmax;
            ymax = (ymax < pt.y) ? pt.y : ymax;
        }
    }
    Grid grid(ymax + 2, vector<char>(xmax - xmin + 3, AIR));
    auto shift_x = [&](int pos_x){ return pos_x - (xmin - 1); };

    // Draw rock paths into the gridmap
    for (auto p : paths) {
        int n = p.size();
        auto draw_path = [&](Coord p1, Coord p2)
        {
            grid[p1.y][shift_x(p1.x)] = ROCK;
            grid[p2.y][shift_x(p2.x)] = ROCK;
            while (p1.x != p2.x || p1.y != p2.y) {
                grid[p1.y][shift_x(p1.x)] = ROCK;
                if (p1.x == p2.x)
                    p1.y += (p1.y < p2.y) ? 1 : -1;
                else if (p1.y == p2.y)
                    p1.x += (p1.x < p2.x) ? 1 : -1;
            }
        };
        for (int i = 1; i < n; i++) {
            draw_path(p[i-1], p[i]);
        }
    }

    // Lambda function for simulate falling sand unit
    auto sim_falling_sand = [&]()
    {
        int x = SOURCE, y = 0;
        auto fall = [&]() {
            if (x < xmin || x > xmax || y > ymax)
                return STOP;
            if (grid[y+1][shift_x(x)] != AIR &&
                grid[y+1][shift_x(x-1)] != AIR &&
                grid[y+1][shift_x(x+1)] != AIR)
                return STOP;
            y++;
            if (grid[y][shift_x(x)] == AIR)
                return FALLING;
            else if (grid[y][shift_x(x-1)] == AIR)
                x--;
            else if (grid[y][shift_x(x+1)] == AIR)
                x++;
            return FALLING;
        };
        while (true) {                  // Let it fall
            if(fall() == STOP)
                break;
        }
        // Check x, y to return STOP of OFFMAP
        if (x < xmin || x > xmax || y > ymax)
            return OFFMAP;
        grid[y][shift_x(x)] = SAND;
        return STOP;
    };
    // Run simulation
    while (true) {
        if (sim_falling_sand() == OFFMAP)
            break;
    }
    // Print the grid
    for (int y = 0; y < ymax + 2; y++) {
        for (int x = xmin - 1; x <= xmax + 1; x++) {
            cout << grid[y][shift_x(x)];
        }
        cout << endl;
    }
    // Count sand units
    int no_sand_units = 0;
    for (int y = 0; y < ymax + 2; y++) {
        for (int x = xmin - 1; x <= xmax + 1; x++) {
            if(grid[y][shift_x(x)] == 'o')
                no_sand_units++;
        }
    }
    cout << "Number of sand units: " << no_sand_units << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
