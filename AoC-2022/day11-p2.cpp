#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>

using namespace std;
#define id first
#define val second

const int ROUND = 10000;
using LL = long long;

class Monkey
{
private:
    LL count;              // no. item inspection times
    vector<LL> items;
    char op;
    string op_val;
    LL val_test;
    int id_test_true, id_test_false;

public:
    Monkey(istream& infile);
    ~Monkey();
    vector<pair<int, LL>> inspect_and_throw(const int &MOD);
    void receive(const LL &val);
    LL get_count() const;
    LL get_div() const;
    void print() const;
};

void solve()
{
    // Read input
    vector<Monkey> monkeys;
    ifstream infile("day11.txt");
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            if (line.empty())
                continue;
            else if (line.find("Monkey") != string::npos) {
                Monkey m(infile);
                monkeys.push_back(m);
            }
        }
    }   else cout << "Unable to openfile";

    // 20 rounds of stuff-slinging simian shenanigans
    LL MOD = 1;
    for (auto &m : monkeys)
        MOD *= m.get_div();
    for (int i = 1; i <= ROUND; i++) {
        for (auto &m : monkeys) {
            auto vect = m.inspect_and_throw(MOD);
            for (auto [id, val] : vect) {
                monkeys[id].receive(val);
            }
        }
        // if (i == 1 || i == 20 || i == 1000) {
        //     cout << "== After round " << i << " =="<< endl;
        //     for (auto m : monkeys)
        //         m.print();
        //     cout << endl;
        // }
    }
    
    // Compute the level of monkey business
    vector<LL> counts;
    for (auto m : monkeys)
        counts.push_back(m.get_count());
    LL monkey_business;
    monkey_business = *max_element(counts.begin(), counts.end());
    counts.erase(max_element(counts.begin(), counts.end()));
    monkey_business *= *max_element(counts.begin(), counts.end());
    cout << monkey_business << endl;

    // cout << "== Final round " << ROUND << " =="<< endl;
    // for (auto m : monkeys)
    //     m.print();
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}

Monkey::Monkey(istream& infile)
{
    string str;
    stringstream ss;
    auto get_ss = [&](int pos){
        getline(infile, str);
        ss.clear();
        ss.str(str.substr(pos));
    };

    // Get items
    LL i; char c;
    get_ss(18);
    while (ss >> i) {
        items.push_back(i);
        ss >> c;
    }

    // Get operation
    get_ss(23);
    ss >> c >> str;
    op = c;
    op_val = str;

    // Get test values
    get_ss(21);
    ss >> val_test;
    get_ss(29);
    ss >> id_test_true;
    get_ss(30);
    ss >> id_test_false;

    count = 0;
}

Monkey::~Monkey() {}

void Monkey::print() const
{
    // cout << "Monkey:" << endl;
    // cout << "Items: ";
    // for (int i : items)
    //     cout << i << " ";
    // cout << endl;
    // cout << "Op: " << op << " " << op_val << endl;
    // cout << "Test: " << val_test << " "
    //      << id_test_true << " " << id_test_false << endl;
    cout << "Count: " << count << endl;
}

vector<pair<int, LL>> Monkey::inspect_and_throw(const int &MOD)
{
    vector<pair<int, LL>> result;
    LL val, d;
    while (!items.empty()) {
        count++;
        val = items.front();
        if (op_val == "old")
            d = val;
        else
            d = stoll(op_val);
        if (op == '*')
            val *= d;
        else if (op == '+')
            val += d;
        val = val % MOD;
        if (val % val_test == 0)
            result.push_back(make_pair(id_test_true, val));
        else
            result.push_back(make_pair(id_test_false, val));        
        items.erase(items.begin());
    }
    return result;
}

void Monkey::receive(const LL &val) { items.push_back(val); }

LL Monkey::get_count() const { return count; }

LL Monkey::get_div() const { return val_test; }
