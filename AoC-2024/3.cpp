/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "../pch.hpp"

ll ans = 0;
regex regexp("mul\\([0-9]*\\,[0-9]*\\)");
regex d1("(.*?)don\\'t\\(\\)");
regex d2("do\\(\\)(.*?)don\\'t\\(\\)");
regex d3("do\\(\\)(.*?)");

void read_input() {
    string line;
    ll a, b;
    string s;

    while (getline(cin, line)) {
        LOG(line);
        replace(all(line), ' ', 'x');

        vector<string> lines;
        smatch temp_m;
        regex_search(line, temp_m, d1);
        LOG(temp_m.str());
        regex_search(line, temp_m, d2);
        LOG(temp_m.str());
        regex_search(line, temp_m, d3);
        LOG(temp_m.str());
        // lines.push_back(temp_m.str());
        // LOG(lines);
        // line = line.substr(lines.back().size());
        // LOG(line);
        LOG(lines);

        auto begin = std::sregex_iterator(all(line), regexp);
        auto end = std::sregex_iterator();
        for (std::sregex_iterator i = begin; i != end; ++i) {
            std::smatch match = *i;
            string instruction = match.str();

            instruction[3] = ' ';
            instruction.back() = ' ';
            replace(all(instruction), ',', ' ');
            LOG(instruction);
            stringstream ss(instruction);
            ss >> s >> a >> b;
            ans += a * b;
        }
    }
}

void solve() {
    // TODO(duck)
    LOG(ans);
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    return 0;
}
// 161085926
//  83950340
