#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve()
{
    int n_row = 0, n_col = 0;
    vector<vector<short>> grid;
    
    // Read the grid map
    string str;
    while (cin >> str) {
        if (!n_col)
            n_col = str.size();
        n_row++;
        grid.push_back(vector<short>(0));
        for (char c : str) {
            grid.back().push_back(c - '0');
        }
    }

    // The visibility of each grid cell
    vector<vector<bool>> visiblility(n_row, vector<bool>(n_col, false));
    // Init values on the edge
    for (int r = 0; r < n_row; r++) {
        visiblility[r][0] = true;
        visiblility[r][n_col - 1] = true;
    }
    for (int c = 0; c < n_col; c++) {
        visiblility[0][c] = true;
        visiblility[n_row - 1][c] = true;
    }
    // Check visibility in each row, view from left and right
    for (int r = 1; r < n_row - 1; r++) {
        auto check_visibility = [&](const int &begin, const int &end)
        {
            int id = begin, height = 0;
            while (id != end) {
                if (id == begin) {
                    height = grid[r][id];
                } else if (grid[r][id] > height) {
                    height = grid[r][id];
                    visiblility[r][id] = true;
                }
                id += (end > begin) ? 1 : -1;
            }
        };
        check_visibility(0, n_col - 1);
        check_visibility(n_col - 1, 0);
    }

    // Check visibility in each column, view from top and bottom
    for (int c = 1; c < n_col - 1; c++) {
        auto check_visibility = [&](const int &begin, const int &end)
        {
            int id = begin, height = 0;
            while (id != end) {
                if (id == begin) {
                    height = grid[id][c];
                } else if (grid[id][c] > height) {
                    height = grid[id][c];
                    visiblility[id][c] = true;
                }
                id += (end > begin) ? 1 : -1;
            }
        };
        check_visibility(0, n_row - 1);
        check_visibility(n_row - 1, 0);
    }

    // Count visible cells
    int count = 0;
    for (auto row : visiblility) {
        for (bool c : row) {
            count += c ? 1 : 0;
        }
    }
    cout << count << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
