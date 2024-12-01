#include "../pch.hpp"

int ans = 0;
string line;
string card, num;
int id;
char c;
vector<vector<int>> vects_winning_nums, vects_nums;

void read_input() {
    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> card >> id >> c;
        vector<int> vect_winning_nums, vect_nums;
        while (ss >> num and num != "|") vect_winning_nums.push_back(stoi(num));
        while (ss >> num) vect_nums.push_back(stoi(num));
        vects_winning_nums.push_back(vect_winning_nums);
        vects_nums.push_back(vect_nums);
    }
}

#if PART1
void solve() {
    for (int i = 0; i < vects_winning_nums.size(); i++) {
        int pt = 0;
        for (const int &n : vects_nums[i]) {
            if (find(vects_winning_nums[i].begin(), vects_winning_nums[i].end(),
                     n) != vects_winning_nums[i].end()) {
                pt = max(pt + 1, pt * 2);
            }
        }
        ans += pt;
    }
    cout << ans << endl;
}
#else
void solve() {
    vector<int> cnt_match(vects_winning_nums.size(), 0);
    vector<int> cnt_card(vects_winning_nums.size(), 1);
    for (int i = 0; i < vects_winning_nums.size(); i++) {
        int num_match = 0;
        for (const int &n : vects_nums[i]) {
            if (find(vects_winning_nums[i].begin(), vects_winning_nums[i].end(),
                     n) != vects_winning_nums[i].end()) {
                num_match++;
            }
        }
        cnt_match[i] = num_match;
    }
    for (int i = 0; i < cnt_match.size(); i++) {
        if (!cnt_match[i]) continue;
        for (int j = 1; j <= cnt_match[i] and i + j <= cnt_match.size(); j++) {
            cnt_card[i + j] += cnt_card[i];
        }
    }
    ans = accumulate(cnt_card.begin(), cnt_card.end(), 0);
    cout << ans << endl;
}
#endif  // PART1

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    return 0;
}
