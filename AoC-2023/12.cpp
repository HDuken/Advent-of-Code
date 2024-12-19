/*
 *   Copyright (c) 2023 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

int ans = 0;
string line;
vector<pair<string, vector<int>>> inputs;
using vi = vector<int>;

void read_input() {
    while (getline(cin, line)) {
        stringstream ss(line);
        string a;
        vi b;
        char c;
        int d;
        ss >> a >> d;
        b.push_back(d);
        while (ss >> c >> d) b.push_back(d);
#if PART1
        inputs.push_back({a, b});
#else   // PART2
        string str;
        vi groups;
        for (int i = 0; i < 5; i++) {
            str += a + '?';
            groups.insert(groups.end(), all(b));
        }
        str.pop_back();
        inputs.push_back({str, groups});
#endif  // PART1
    }
}

// Recursive search
int recursive_search(const string &str, const vector<int> &group) {
    cout << "Enter recursive search " << str << ' ' << group << endl;

    // Case: All '.', non-empty group
    if (str.find('#') == string::npos and str.find('?') == string::npos and
        !group.empty()) {
        print("All '.', non-empty group, return 0");
        return 0;
    }
    // Case: No '#', empty group, just . and ?
    if (str.find('#') == string::npos and group.empty()) {
        print("No '#', empty group, return 1");
        return 1;
    }
    // Case: There is '#' but no group
    if (str.find('#') != string::npos and group.empty()) {
        print("#, empty group, return 0");
        return 0;
    }

    // If the remaining string is too short for the required groups
    if (str.size() < accumulate(all(group), 0) + group.size() - 1) {
        print("str too short for required group");
        return 0;
    }

    // Shorten the string
    // If there is '.' in the beginning/end
    if (str.front() == '.' || str.back() == '.') {
        string str_short(str);
        while (str_short.front() == '.') str_short.erase(0, 1);
        while (str_short.back() == '.') str_short.pop_back();
        print("shorten str start .", str, str_short);
        return recursive_search(str_short, group);
    }

    // If there is '#' in the beginning
    if (str.front() == '#') {
        print("str start with #");
        for (int i = 0; i < group.front(); i++) {
            if (str[i] == '.') {
                print("has . -> return 0");
                return 0;
            }
        }
        if (str[group.front()] == '#') {
            print("has # -> return 0");
            return 0;
        }
        // New string
        string str_short(str);
        str_short.erase(0, group.front() + 1);
        // New group
        vector<int> group_short(group);
        group_short.erase(group_short.begin());
        cout << "shorten string with # " << str << ' ' << str_short << ' '
             << group_short << endl;
        return recursive_search(str_short, group_short);
    }
    // If there is '#' in the end
    if (str.back() == '#') {
        for (int i = 0; i < group.back(); i++) {
            if (str[str.size() - 1 - i] == '.') {
                return 0;
            }
        }
        if (str[str.size() - 1 - group.back()] == '#') {
            return 0;
        }
        // New string
        string str_short(str);
        str_short.erase(str_short.size() - 1 - group.back(), group.back() + 1);
        // New group
        vector<int> group_short(group);
        group_short.erase(group_short.end() - 1);
        print("shorten string with #", str, str_short, group_short);
        return recursive_search(str_short, group_short);
    }

    // Case: start with ?
    if (str.front() != '?') cerr << "WRONG " << str << endl;
    string str_1(str), str_2(str);
    str_1[0] = '#';
    str_2[0] = '.';
    print("Recursive part\n", 0, str, '\n', 1, str_1, '\n', 2, str_2);
    return recursive_search(str_1, group) + recursive_search(str_2, group);
}

void solve() {
    for (const auto &[str, list] : inputs) {
        int x = recursive_search(str, list);
        print("THE STRING", str, "n=", x, list);
        ans += x;
    }
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    LOG(ans);
    return 0;
}
