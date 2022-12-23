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

const int ROUND = 20;

class Monkey
{
private:
    int count;              // no. item inspection times
    vector<int> items;
    char op;
    string op_val;
    int val_test, id_test_true, id_test_false;

public:
    Monkey(istream& infile);
    ~Monkey();
    vector<pair<int, int>> inspect_and_throw();
    void receive(const int &val);
    int get_count() const;
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
    for (int i = 0; i < ROUND; i++) {
        for (auto &m : monkeys) {
            auto vect = m.inspect_and_throw();
            for (auto [id, val] : vect) {
                monkeys[id].receive(val);
            }
        }
    }
    
    // Compute the level of monkey business
    vector<int> counts;
    for (auto m : monkeys)
        counts.push_back(m.get_count());
    int monkey_business;
    monkey_business = *max_element(counts.begin(), counts.end());
    counts.erase(max_element(counts.begin(), counts.end()));
    monkey_business *= *max_element(counts.begin(), counts.end());
    cout << monkey_business << endl;
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
    int i; char c;
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
    cout << "Monkey:" << endl;
    cout << "Items: ";
    for (int i : items)
        cout << i << " ";
    cout << endl;
    cout << "Op: " << op << " " << op_val << endl;
    cout << "Test: " << val_test << " "
         << id_test_true << " " << id_test_false << endl;
    cout << "Count: " << count << endl;
}

vector<pair<int, int>> Monkey::inspect_and_throw()
{
    vector<pair<int, int>> result;
    int val, d;
    while (!items.empty()) {
        count++;
        val = items.front();
        if (op_val == "old")
            d = val;
        else
            d = stoi(op_val);
        if (op == '*')
            val *= d;
        else if (op == '+')
            val += d;
        val /= 3;
        if (val % val_test == 0)
            result.push_back(make_pair(id_test_true, val));
        else
            result.push_back(make_pair(id_test_false, val));        
        items.erase(items.begin());
    }
    return result;
}

void Monkey::receive(const int &val) { items.push_back(val); }

int Monkey::get_count() const { return count; }
