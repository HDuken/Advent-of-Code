#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;
enum ORIENTATION : int { RIGHT, DOWN, LEFT, UP };
enum BLOCK : char {
    ROCK = '#',
    FREE = '.',
    BLANK = ' ',
    U = '^',
    D = 'v',
    L = '<',
    R = '>'
};
ORIENTATION curr_direction = RIGHT;
BLOCK ori2block(ORIENTATION ori);
using Grid = vector<vector<BLOCK>>;

const int ROW = 12, COL = 16, LEN_CUBE = 4;
// const int ROW = 200, COL = 150, LEN_CUBE = 50;

Grid grid = Grid(ROW, vector<BLOCK>(COL, BLANK));

const char ROT_L = 'L', ROT_R = 'R';
using Command = pair<char, int>;
using Commands = vector<Command>;
Commands commands;

void read_input();
void print();
void rotate(const char &dir);
void get_next(const int &x, const int &y, int &x_next, int &y_next);

int main(int argc, char const *argv[])
{
    read_input();
    // Current / starting position
    int x = 0, y = 0;
    for (int j = 0; j < COL; j++) {
        if (grid[0][j] == FREE) {
            x = j;
            break;
        }
    }

    auto move = [&](char dir, int step)
    {
        rotate(dir);
        grid[y][x] = ori2block(curr_direction);
        int x_next = 0, y_next = 0;
        for (int s = 0; s < step; s++) {
            get_next(x, y, x_next, y_next);
            if (grid[y_next][x_next] == ROCK)
                break;
            x = x_next;
            y = y_next;
            grid[y][x] = ori2block(curr_direction);
        }  
    };

    for (auto [dir, step] : commands) {
        move(dir, step);
    }

    print();
    int result = 1000 * (y + 1) + 4 * (x + 1) + curr_direction;
    cout << result << endl;
    return 0;
}

void read_input()
{
    string line;
    for (int i = 0; i < ROW; i++) {
        getline(cin, line);
        for (size_t j = 0; j < line.size(); j++) {
            if (line[j] == ' ')
                continue;
            else if (line[j] == '.')
                grid[i][j] = FREE;
            else if (line[j] == '#')
                grid[i][j] = ROCK;
        }
    }
    getline(cin, line);     // blank line
    commands.clear();
    int step;
    char direction;
    cin >> step;
    commands.push_back(make_pair('X', step));
    while (cin >> direction) {
        cin >> step;
        commands.push_back(make_pair(direction, step));
    }
}

void print()
{
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++)
            cout << grid[i][j];
        cout << endl;
    }
    // for (auto [d, s] : commands) {
    //     cout << d << " " << s << endl;
    // }
}

void rotate(const char &dir)
{
    if (dir == 'X')
        return;
    int ori = curr_direction;
    if (dir == ROT_R)
        ori += 1;
    else if (dir == ROT_L)
        ori += 3;
    curr_direction = static_cast<ORIENTATION>(ori % 4);
}

BLOCK ori2block(ORIENTATION ori)
{
    if (ori == RIGHT)
        return R;
    else if (ori == LEFT)
        return L;
    else if (ori == UP)
        return U;
    else if (ori == DOWN)
        return D;
    return D;
}

// Sample
//       [A]
// [B][C][D]
//       [E][F]

// Test
//    [A][B]
//    [C]
// [D][E]
// [F]

// TODO
void get_next(const int &x, const int &y, int &x_next, int &y_next)
{
    x_next = x;
    y_next = y;
    auto step_forward = [&]()
    {
        if (curr_direction == UP)
            y_next = (y_next + ROW - 1) % ROW;
        else if (curr_direction == DOWN)
            y_next = (y_next + 1) % ROW;
        else if (curr_direction == LEFT)
            x_next = (x_next + COL - 1) % COL;
        else if (curr_direction == RIGHT)
            x_next = (x_next + 1) % COL;
    };
    do {
        step_forward();
    } while (grid[y_next][x_next] == BLANK);
}
