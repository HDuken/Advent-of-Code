#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
#define PART1 true

void solve()
{
    string line;
    const int N = 9;
    vector<vector<char>> crates(N);

    ifstream fileIn("day5.txt");
    if (fileIn.is_open()) {
        // Read the stacks order
        while (getline(fileIn, line)) {
            if (line.empty())
                break;
            for (int i = 0; i < N; i++) {
                if (line[1] == '1')
                    break;                
                if (line[1 + 4 * i] != ' ')
                    crates[i].push_back(line[1 + 4 * i]);
            }
        }

        // Read rearrangement procedure and apply it
        int num, id1, id2;
        while (fileIn >> line) {
            fileIn >> num >> line >> id1 >> line >> id2;
            id1--; id2--;
#if PART1
            for (int i = 0; i < num; i++) {
                crates[id2].insert(crates[id2].begin(), crates[id1].front());
                crates[id1].erase(crates[id1].begin());
            }
#else
            crates[id2].insert(crates[id2].begin(), crates[id1].begin(), crates[id1].begin() + num);
            crates[id1].erase(crates[id1].begin(), crates[id1].begin() + num);
#endif
        }
        fileIn.close();
    }   else cout << "Unable to open file" << endl;

    // Print result
    for (int i = 0; i < N; i++)
        cout << crates[i][0];
}

int main(int argc, char const *argv[])
{
    solve();
    cout << endl;
    return 0;
}
