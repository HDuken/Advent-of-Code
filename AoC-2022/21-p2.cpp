#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>

using namespace std;
using LL = long long;
const LL UNDEFINED = -100'000'000;
const LL VAR = -200'000'000;
const int UNSET = -1;
const string HUMAN = "humn", ROOT = "root";
enum OP { ADD, SUB, MUL, DIV, EQU };

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
    static void propagate_up(Node* node);
    static void propagate_down(Node* node);
public:
    Tree();
    ~Tree();
    void set_node(const string &name, const LL &val);
    void set_node(const string &name, const char &c,
        const string &child1, const string &child2);
    LL get_val();
    void print() const;
};

Tree read_input();

void solve()
{
    Tree monkeys = read_input();
    cout << monkeys.get_val() << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}

Tree::Tree()
{
    nodes_.push_back(new Node(ROOT));
    nodes_.push_back(new Node(HUMAN, VAR));
}

Tree::~Tree()
{
    for (auto node_ptr : nodes_)
        delete node_ptr;
}

void Tree::set_node(const string &name, const LL &val)
{
    if (name == HUMAN)
        return;
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
    if (nodes_[id]->name_ == ROOT)
        nodes_[id]->op_ = EQU;
}

void Tree::propagate_up(Node* node)
{
    if (node->value_ != UNDEFINED)
        return;
    propagate_up(node->child1_);
    propagate_up(node->child2_);
    LL val_child1 = node->child1_->value_;
    LL val_child2 = node->child2_->value_;

    if (val_child1 == VAR || val_child2 == VAR) {
        node->value_ = VAR;
    }   else {
        if (node->op_ == ADD)
            node->value_ = val_child1 + val_child2;
        else if (node->op_ == MUL)
            node->value_ = val_child1 * val_child2;
        else if (node->op_ == SUB)
            node->value_ = val_child1 - val_child2;
        else if (node->op_ == DIV)
            node->value_ = val_child1 / val_child2;
    }
}

void Tree::propagate_down(Node* node)
{
    if (node->child1_ == nullptr && node->child2_ == nullptr)
        return;
    if (node->child1_->value_ == VAR) {
        LL val0 = node->value_, val = node->child2_->value_;
        if (node->op_ == EQU)
            node->child1_->value_ = val;
        else if (node->op_ == ADD)
            node->child1_->value_ = val0 - val;
        else if (node->op_ == SUB)
            node->child1_->value_ = val0 + val;
        else if (node->op_ == MUL)
            node->child1_->value_ = val0 / val;
        else if (node->op_ == DIV)
            node->child1_->value_ = val0 * val;
        propagate_down(node->child1_);
    }   else {  // node->child2_->value_ == VAR
        LL val0 = node->value_, val = node->child1_->value_;
        if (node->op_ == EQU)
            node->child2_->value_ = val;
        else if (node->op_ == ADD)
            node->child2_->value_ = val0 - val;
        else if (node->op_ == SUB)
            node->child2_->value_ = val - val0;
        else if (node->op_ == MUL)
            node->child2_->value_ = val0 / val;
        else if (node->op_ == DIV)
            node->child2_->value_ = val / val0;
        propagate_down(node->child2_);
    }
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
        else if (op_ == EQU)
            cout << "= ";
        cout << child2_->name_ << " ";
    }
    cout << value_ << endl;
}

void Tree::print() const
{
    cout << "No. nodes: " << nodes_.size() << endl;
    for (auto monkey : nodes_)
        monkey->print();
}

LL Tree::get_val()
{
    propagate_up(nodes_[0]->child1_);
    propagate_up(nodes_[0]->child2_);
    propagate_down(nodes_[0]);
    return nodes_[1]->value_;
}
