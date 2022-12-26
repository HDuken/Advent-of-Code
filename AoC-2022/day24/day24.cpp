#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>

using namespace std;
#define PART1 false

struct Coord
{
    int x_, y_;
    Coord(int x, int y) : x_(x), y_(y) {};
};

const char UP = '^', DOWN = 'v', LEFT = '<', RIGHT = '>';
const char ROCK = '#', FREE = '.';
using Grid = vector<vector<bool>>;

struct Blizzard
{
    Coord p_;
    char d_;

    Blizzard(int x, int y, char c) : p_(Coord(x, y)), d_(c) {};
    void move(const Grid &gridmap);
};

void read_input(Grid &gridmap, vector<Blizzard> &blizzards);
void clear(Grid &gridmap);
void print(const Grid &gridmap, const vector<Blizzard> &blizzards);
// Breadth first search
void BFS(Grid &reachable_cells,
    const Grid &gridmap, const vector<Blizzard> &blizzards);

void solve()
{
    Grid gridmap;
    vector<Blizzard> blizzards;
    read_input(gridmap, blizzards);

    Grid reachable_cells(gridmap);
    int round = 0;

    auto make_trip = [&](int xstart, int ystart, int xend, int yend)
    {
        clear(reachable_cells);
        reachable_cells[ystart][xstart] = true;
        do {
            round++;
            for (auto &b : blizzards)
                b.move(gridmap);
            BFS(reachable_cells, gridmap, blizzards);
        } while (!reachable_cells[yend][xend]);
    };

    make_trip(1, 0, gridmap[0].size()-2, gridmap.size()-1);
#if !PART1
    make_trip(gridmap[0].size()-2, gridmap.size()-1, 1, 0);
    make_trip(1, 0, gridmap[0].size()-2, gridmap.size()-1);
#endif

    cout << "Result = " << round << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}

void read_input(Grid &gridmap, vector<Blizzard> &blizzards)
{
    blizzards.clear();
    string line;
    stringstream ss;
    int y = 0;
    while (getline(cin, line)) {
        gridmap.push_back(vector<bool>(line.size(), true));
        for (size_t x = 0; x < line.size(); x++) {
            if (line[x] == '#' || line[x] == '.')
                continue;
            blizzards.push_back(Blizzard(x, y, line[x]));
        }
        y++;
    }
    int ROW = gridmap.size(), COL = line.size();
    for (int r = 0; r < ROW; r++) {
        gridmap[r][0] = false;
        gridmap[r][COL - 1] = false;
    }
    for (int c = 0; c < COL; c++) {
        gridmap[0][c] = false;
        gridmap[ROW - 1][c] = false;
    }
    gridmap[0][1] = true;
    gridmap[ROW - 1][COL - 2] = true;
}

void print(const Grid &gridmap, const vector<Blizzard> &blizzards)
{
    vector<vector<char>> grid_print(
        gridmap.size(), vector<char>(gridmap[0].size(), '.'));
    int ROW = gridmap.size(), COL = gridmap[0].size();
    for (int r = 0; r < ROW; r++) {
        grid_print[r][0] = '#';
        grid_print[r][COL - 1] = '#';
    }
    for (int c = 0; c < COL; c++) {
        grid_print[0][c] = '#';
        grid_print[ROW - 1][c] = '#';
    }
    grid_print[0][1] = '.';
    grid_print[ROW - 1][COL - 2] = '.';
    for (auto b : blizzards) {
        if (grid_print[b.p_.y_][b.p_.x_] == FREE)
            grid_print[b.p_.y_][b.p_.x_] = b.d_;
        else if (grid_print[b.p_.y_][b.p_.x_] == '2')
            grid_print[b.p_.y_][b.p_.x_] = '3';
        else if (grid_print[b.p_.y_][b.p_.x_] == '3')
            grid_print[b.p_.y_][b.p_.x_] = '4';
        else
            grid_print[b.p_.y_][b.p_.x_] = '2';
    }
    for (auto r : grid_print) {
        for (auto c : r) {
            cout << c;
        }
        cout << endl;
    }
}

void Blizzard::move(const Grid &gridmap)
{
    int ROW = gridmap.size(), COL = gridmap[0].size();
    do {
        if (d_ == UP)
            p_.y_ = (p_.y_ - 1 + ROW) % ROW;
        else if (d_ == DOWN)
            p_.y_ = (p_.y_ + 1) % ROW;
        else if (d_ == LEFT)
            p_.x_ = (p_.x_ - 1 + COL) % COL;
        else if (d_ == RIGHT)
            p_.x_ = (p_.x_ + 1) % COL;
    } while (!gridmap[p_.y_][p_.x_]);
}

void BFS(Grid &reachable_cells,
    const Grid &gridmap, const vector<Blizzard> &blizzards)
{
    int R = gridmap.size(), C = gridmap[0].size();

    Grid valid_cells(gridmap);
    for (auto b : blizzards) {
        valid_cells[b.p_.y_][b.p_.x_] = false;
    }

    vector<Coord> previous_valid_positions;
    for (int y = 0; y < R; y++) {
        for (int x = 0; x < C; x++) {
            if (reachable_cells[y][x]) {
                previous_valid_positions.push_back(Coord(x, y));
            }
        }
    }
    for (auto [x, y] : previous_valid_positions) {
        reachable_cells[max(y - 1, 0)][x] = true;
        reachable_cells[min(y + 1, R - 1)][x] = true;
        reachable_cells[y][max(x - 1, 0)] = true;
        reachable_cells[y][min(x + 1, C - 1)] = true;
    }

    for (int y = 0; y < R; y++) {
        for (int x = 0; x < C; x++) {
            reachable_cells[y][x] = reachable_cells[y][x] && valid_cells[y][x];
        }
    }
}

void clear(Grid &gridmap)
{
    int R = gridmap.size(), C = gridmap[0].size();
    vector<bool> row(C, false);
    for (int i = 0; i < R; i++)
        gridmap[i] = row;
}
