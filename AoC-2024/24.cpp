/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"

const int N_BIT = 46;
bitset<N_BIT> bs;
stringstream ss;
map<string, bool> m;
struct Ops {
    string a, b, c, op;

    Ops(string _a, string _b, string _op, string _c)
        : a(_a), b(_b), c(_c), op(_op) {}
};
vector<Ops> v_ops;

void read_input() {
    string line;
    string x, y, z, op;
    bool b;
    while (getline(cin, line)) {
        if (line.empty()) break;
        replace(all(line), ':', ' ');
        ss.clear();
        ss.str(line);
        ss >> x >> b;
        m[x] = b;
    }

    while (getline(cin, line)) {
        replace(all(line), '-', ' ');
        replace(all(line), '>', ' ');
        ss.clear();
        ss.str(line);
        ss >> x >> op >> y >> z;
        v_ops.push_back(Ops(x, y, op, z));
    }
}

void solve() {
#if PART1
    ll ans = 0;
    int cnt = 0;
    while (cnt < v_ops.size()) {
        for (auto op : v_ops) {
            if (m.count(op.c) || !m.count(op.a) || !m.count(op.b)) continue;

            if (op.op == "AND") m[op.c] = m[op.a] & m[op.b];
            else if (op.op == "XOR") m[op.c] = m[op.a] ^ m[op.b];
            else if (op.op == "OR") m[op.c] = m[op.a] | m[op.b];
            cnt++;
        }
    }

    bs.reset();
    for (int i = 0; i < N_BIT; i++) {
        string key{'z'};
        if (i < 10) key += '0';
        key += to_string(i);
        bs.set(i, m[key]);
    }
    ans = bs.to_ullong();
#else
    // https://www.reddit.com/r/adventofcode/comments/1hla5ql/2024_day_24_part_2_a_guide_on_the_idea_behind_the/
    string ans;
    set<string> s;

    for (auto op : v_ops) {
        // Case 1: if the output is gate z, the operaion has to be XOR, except
        // for the last bit, with which the op is OR
        if (op.c[0] == 'z' && op.op != "XOR" &&
            stoi(op.c.substr(1)) != N_BIT - 1)
            s.insert(op.c);

        // Case 2: if the output is NOT gate z, and the input is not x, y,
        // then the op can not be XOR
        if (op.c[0] != 'z' && op.op == "XOR" && op.a[0] != 'x' &&
            op.a[0] != 'y' && op.b[0] != 'x' && op.b[0] != 'y')
            s.insert(op.c);

        // Two cases below do not apply to x00 and y00
        // Case 3: if there is an XOR gate with x, y inputs, there must be a
        // follow-up XOR gate
        if ((op.a[0] == 'x' || op.a[0] == 'y') &&
            (op.b[0] == 'x' || op.b[0] == 'y') && op.op == "XOR" &&
            (op.a != "x00" && op.b != "x00")) {
            bool good = false;
            for (auto op_next : v_ops) {
                if (op_next.op != "XOR") continue;
                if (op_next.a != op.c && op_next.b != op.c) continue;
                good = true;
                break;
            }
            if (!good) s.insert(op.c);
        }

        // Case 4: if there is an AND gate, there must be a follow-up OR gate
        if (op.op == "AND" && op.c[0] != 'z' &&
            (op.a != "x00" && op.b != "x00")) {
            bool good = false;
            for (auto op_next : v_ops) {
                if (op_next.op != "OR") continue;
                if (op_next.a != op.c && op_next.b != op.c) continue;
                good = true;
                break;
            }
            if (!good) s.insert(op.c);
        }
    }

    for (string str : s) ans += str + ',';
    ans.erase(ans.end() - 1);

#endif  // PART1

    LOG(ans);
}

int main(int argc, char const *argv[]) {
    read_input();
    solve();
    return 0;
}
