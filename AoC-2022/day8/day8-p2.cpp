#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int get_scenic_score(
    const int &idr, const int &idc, const vector<vector<short>> &grid)
{
    int n_row = grid.size(), n_col = grid[0].size();
    if ((idr == 0) || (idr == n_row-1) || (idc == 0) || (idc == n_col-1))
        return 0;

    int height = grid[idr][idc];
    // Number of trees in view for 4 directions
    int view_l = 0, view_r = 0, view_t = 0, view_b = 0;

    for (int r = idr + 1; r < n_row; r++) {
        view_b++;
        if (grid[r][idc] >= height)
            break;
    }
    for (int r = idr - 1; r >= 0 ; r--) {
        view_t++;
        if (grid[r][idc] >= height)
            break;
    }
    for (int c = idc + 1; c < n_col; c++) {
        view_r++;
        if (grid[idr][c] >= height)
            break;
    }
    for (int c = idc - 1; c >= 0 ; c--) {
        view_l++;
        if (grid[idr][c] >= height)
            break;
    }
    return view_l * view_r * view_b * view_t;
}

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

    int best_score = 0;
    for (int r = 1; r < n_row - 1; r++) {
        for (int c = 1, score; c < n_col - 1; c++) {
            score = get_scenic_score(r, c, grid);
            best_score = (score > best_score) ? score : best_score;
        }
    }
    
    cout << best_score << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
