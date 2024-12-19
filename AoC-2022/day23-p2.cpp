#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <array>
#include <limits.h>

using namespace std;

enum Direction : int { NORTH = 0, SOUTH = 1, WEST = 2, EAST = 3 };
Direction get_next(const Direction &dir);

struct Coord
{
    int x_, y_;
    Coord(int x, int y) : x_(x), y_(y) {};
};
Coord operator+(const Coord &p1, const Coord &p2);
Coord operator-(const Coord &p1, const Coord &p2);
bool operator==(const Coord &p1, const Coord &p2);
Coord move(const Coord &p, const Direction &d);

using Coords = vector<Coord>;

struct Elf
{
    Coord p_, next_p_;
    Direction d_;
    Elf(int x, int y) : p_(Coord(x, y)), next_p_(p_), d_(NORTH) {};
};
vector<Elf> read_input();

// const int RANGE = 7;        // For sample
const int RANGE = 75;        // For actual test case
using GRIDMAP = array<array<bool, 3 * RANGE>, 3 * RANGE>;
struct Grid
{
    const int xmin = -RANGE, xmax = 2 * RANGE - 1;
    const int ymin = -RANGE, ymax = 2 * RANGE - 1;
    GRIDMAP grid_;

    Grid(const vector<Elf> &elves);
    void print() const;
    int shiftx(int x) const { return x - xmin; }
    int shifty(int y) const { return y - ymin; }
    int at(int x, int y) const { return grid_[shifty(y)][shiftx(x)]; }
    int at(Coord p) const { return at(p.x_, p.y_); }
    void set(Coord p);
    void unset(Coord p);
    bool no_neighbor(const Coord &p) const;
    bool is_valid(const Coord &p, const Direction &d) const;
};
const char FREE = '.', ELF = '#';

void move(vector<Elf> &elves, Grid &grid);
int get_result(const vector<Elf> elves);

void solve()
{
    vector<Elf> elves = read_input();
    Grid grid(elves);
    GRIDMAP grid_bak;

    int round = 0;
    do {
        round++;
        grid_bak = grid.grid_;
        move(elves, grid);
    } while (grid_bak != grid.grid_);
    // grid.print();
    cout << "Result = " << round << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}

Direction get_next(const Direction &dir) {
    return static_cast<Direction>((dir + 1) % 4);
}

Coord operator+(const Coord &p1, const Coord &p2) {
    return Coord(p1.x_ + p2.x_, p1.y_ + p2.y_);
}

Coord operator-(const Coord &p1, const Coord &p2) {
    return Coord(p1.x_ - p2.x_, p1.y_ - p2.y_);
}

bool operator==(const Coord &p1, const Coord &p2) {
    return p1.x_ == p2.x_ && p1.y_ == p2.y_;
}

vector<Elf> read_input()
{
    vector<Elf> output;
    string line;
    int y = 0;
    while (getline(cin, line)) {
        for (size_t x = 0; x < line.size(); x++) {
            if (line[x] == ELF)
                output.push_back(Elf(x, y));
        }
        y++;
    }
    return output;
}

Grid::Grid(const vector<Elf> &elves)
{
    array<bool, 3 * RANGE> row;
    row.fill(false);
    grid_.fill(row);
    for (auto elf : elves) {
        grid_[shifty(elf.p_.y_)][shiftx(elf.p_.x_)] = true;
    }
}

void Grid::print() const
{
    for (int i = 0; i < 3 * RANGE; i++) {
        for (int j = 0; j < 3 * RANGE; j++) {
            if (grid_[i][j])
                cout << ELF;
            else
                cout << FREE;
        }
        cout << endl;
    }
}

int get_result(const vector<Elf> elves)
{
    int xmin = INT_MAX, xmax = INT_MIN;
    int ymin = INT_MAX, ymax = INT_MIN;
    for (auto elf : elves) {
        xmin = (xmin < elf.p_.x_) ? xmin : elf.p_.x_;
        xmax = (xmax > elf.p_.x_) ? xmax : elf.p_.x_;
        ymin = (ymin < elf.p_.y_) ? ymin : elf.p_.y_;
        ymax = (ymax > elf.p_.y_) ? ymax : elf.p_.y_;
    }
    return (xmax - xmin + 1) * (ymax - ymin + 1) - elves.size();
}

bool Grid::no_neighbor(const Coord &p) const
{
    int count = 0;
    int x = p.x_, y = p.y_;
    count += at(x - 1, y - 1);
    count += at(x - 1, y);
    count += at(x - 1, y + 1);
    count += at(x + 1, y - 1);
    count += at(x + 1, y);
    count += at(x + 1, y + 1);
    count += at(x    , y - 1);
    count += at(x    , y + 1);
    return count == 0;
}

bool Grid::is_valid(const Coord &p, const Direction &d) const
{
    int count = 0;
    int x = p.x_, y = p.y_;
    if (d == NORTH) {
        count += at(x - 1,  y - 1);
        count += at(x + 1,  y - 1);
        count += at(x,      y - 1);
    }   else if (d == SOUTH) {
        count += at(x - 1,  y + 1);
        count += at(x + 1,  y + 1);
        count += at(x,      y + 1);
    }   else if (d == WEST) {
        count += at(x - 1,  y - 1);
        count += at(x - 1,  y);
        count += at(x - 1,  y + 1);
    }   else if (d == EAST) {
        count += at(x + 1,  y - 1);
        count += at(x + 1,  y);
        count += at(x + 1,  y + 1);
    }
    return count == 0;
}

Coord move(const Coord &p, const Direction &d)
{
    if (d == NORTH)
        return p - Coord(0, 1);
    else if (d == SOUTH)
        return p + Coord(0, 1);
    else if (d == WEST)
        return p - Coord(1, 0);
    else if (d == EAST)
        return p + Coord(1, 0);
    return p;
}

void Grid::set(Coord p) { grid_[shifty(p.y_)][shiftx(p.x_)] = true; }

void Grid::unset(Coord p) { grid_[shifty(p.y_)][shiftx(p.x_)] = false; }

void move(vector<Elf> &elves, Grid &grid)
{
    for (auto &elf : elves) {
        Direction curr_d = elf.d_;
        for (int i = 0; i < 4; i++) {
            if (grid.no_neighbor(elf.p_))
                break;
            if (grid.is_valid(elf.p_, curr_d)) {
                elf.next_p_ = move(elf.p_, curr_d);
                break;
            }
            curr_d = get_next(curr_d);
        }
        elf.d_ = get_next(elf.d_);
    }

    for (size_t i = 0; i < elves.size(); i++) {
        if (elves[i].p_ == elves[i].next_p_)
            continue;
        if (grid.at(elves[i].next_p_) == 0) {
            grid.set(elves[i].next_p_);
            grid.unset(elves[i].p_);
            elves[i].p_ = elves[i].next_p_;
        }   else {
            grid.unset(elves[i].next_p_);
            for (size_t j = i - 1; j >= 0; j--) {
                if (elves[j].p_ == elves[i].next_p_) {
                    elves[j].p_ = elves[i].next_p_ + elves[i].next_p_ - elves[i].p_;
                    elves[j].next_p_ = elves[j].p_;
                    grid.set(elves[j].p_);
                    break;
                }
            }
            elves[i].next_p_ = elves[i].p_;
        }
    }
}
