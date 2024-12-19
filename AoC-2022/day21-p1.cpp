#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>

using namespace std;
using LL = long long;
const LL UNDEFINED = -1'000'000'000;
const int UNSET = -1;
enum OP { ADD, SUB, MUL, DIV };

struct Node
{
    string name_;
    LL value_ = UNDEFINED;
    OP op_ = ADD;
    Node *child1_ = nullptr, *child2_ = nullptr;

    Node(const string &name) : name_(name) {};
    Node(const string &name, const LL &val) : name_(name), value_(val) {};
    void print() const;
};

class Tree
{
private:
    vector<Node*> nodes_;
    static LL get_val(Node* node);
public:
    Tree();
    ~Tree();
    void set_node(const string &name, const LL &val);
    void set_node(const string &name, const char &c,
        const string &child1, const string &child2);
    LL get_val() { return get_val(nodes_[0]); };
    void print() const;
};

Tree read_input();

void solve()
{
    Tree monkeys = read_input();
    monkeys.print();
    cout << monkeys.get_val() << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}

Tree::Tree() { nodes_.push_back(new Node("root")); }

Tree::~Tree()
{
    for (auto node_ptr : nodes_)
        delete node_ptr;
}

void Tree::set_node(const string &name, const LL &val)
{
    for (auto &node_ptr : nodes_) {
        if (node_ptr->name_ == name) {
            node_ptr->value_ = val;
            return;
        }
    }
    nodes_.push_back(new Node(name, val));
}

void Tree::set_node(const string &name, const char &c,
    const string &name_child1, const string &name_child2)
{
    int id = UNSET, id_child1 = UNSET, id_child2 = UNSET;
    auto get_id = [&]()
    {
        for (size_t i = 0; i < nodes_.size(); i++) {
            if (nodes_[i]->name_ == name)
                id = i;
            else if (nodes_[i]->name_ == name_child1)
                id_child1 = i;
            else if (nodes_[i]->name_ == name_child2)
                id_child2 = i;
        }
    };

    get_id();
    if (id == UNSET)
        nodes_.push_back(new Node(name));
    if (id_child1 == UNSET)
        nodes_.push_back(new Node(name_child1));
    if (id_child2 == UNSET)
        nodes_.push_back(new Node(name_child2));
    get_id();
    // Set node's values
    nodes_[id]->child1_ = nodes_[id_child1];
    nodes_[id]->child2_ = nodes_[id_child2];
    if (c == '+')
        nodes_[id]->op_ = ADD;
    else if (c == '-')
        nodes_[id]->op_ = SUB;
    else if (c == '*')
        nodes_[id]->op_ = MUL;
    else if (c == '/')
        nodes_[id]->op_ = DIV;
}

LL Tree::get_val(Node* node)
{
    if (node->value_ != UNDEFINED)
        return node->value_;
    LL val_child1 = get_val(node->child1_);
    LL val_child2 = get_val(node->child2_);
    if (node->op_ == ADD)
        node->value_ = val_child1 + val_child2;
    else if (node->op_ == MUL)
        node->value_ = val_child1 * val_child2;
    else if (node->op_ == SUB)
        node->value_ = val_child1 - val_child2;
    else if (node->op_ == DIV)
        node->value_ = val_child1 / val_child2;
    return node->value_;
}

Tree read_input()
{
    Tree output;
    string name, name_child1, name_child2;
    char c;
    while (cin >> name) {
        name = name.substr(0, 4);
        cin >> name_child1;
        if (name_child1[0] - '0' > 9) {
            cin >> c >> name_child2;
            output.set_node(name, c, name_child1, name_child2);
        }   else {
            output.set_node(name, stoll(name_child1));
        }
    }
    return output;
}

void Node::print() const
{
    cout << "Node: " << name_ << " ";
    if (value_ != UNDEFINED) {
        cout << value_ << endl;
        return;
    }
    if (child1_ != nullptr && child2_ != nullptr) {
        cout << child1_->name_ << " ";
        if (op_ == ADD)
            cout << "+ ";
        else if (op_ == SUB)
            cout << "- ";
        else if (op_ == MUL)
            cout << "* ";
        else if (op_ == DIV)
            cout << "/ ";
        cout << child2_->name_ << " " << value_ << endl;
    }
}

void Tree::print() const
{
    cout << "No. nodes: " << nodes_.size() << endl;
    for (auto monkey : nodes_)
        monkey->print();
}
