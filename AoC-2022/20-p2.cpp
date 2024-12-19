#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using LL = long long;
const LL KEY = 811'589'153;
const int ROUND = 10;

struct Node
{
    LL val_;
    Node *prev_, *next_;

    Node(const LL &val)
    : val_(val), prev_(nullptr), next_(nullptr) {};
};
using LinkedList = vector<Node*>;

LinkedList read_input();
void clean(LinkedList &A);
void move(LinkedList &A, const int &id);
LL get_result(const LinkedList &A);

void solve()
{
    LinkedList A = read_input();
    // Decrypt by mixing
    for (int r = 0; r < ROUND; r++) {
        for (size_t i = 0; i < A.size(); i++)
            move(A, i);
    }
    cout << get_result(A) << endl;
    clean(A);
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}

void move(LinkedList &A, const int &id)
{
    int N = A.size() - 1;
    int iter1 = (A[id]->val_ % N + N) % N;
    int iter2 = N - iter1;
    if (iter1 < iter2) {        // Move forward
        while (iter1 > 0) {
            iter1--;
            const auto prev = A[id]->prev_;
            const auto next = A[id]->next_;
            const auto next2 = A[id]->next_->next_;
            A[id]->prev_->next_ = next;
            A[id]->next_->next_->prev_ = A[id];
            A[id]->next_->prev_ = prev;
            A[id]->next_->next_ = A[id];
            A[id]->prev_ = next;
            A[id]->next_ = next2;
        }
    }   else {  // iter2 < iter1: Move backward
        while (iter2 > 0) {
            iter2--;
            const auto next = A[id]->next_;
            const auto prev = A[id]->prev_;
            const auto prev2 = A[id]->prev_->prev_;
            A[id]->next_->prev_ = prev;
            A[id]->prev_->prev_->next_ = A[id];
            A[id]->prev_->next_ = next;
            A[id]->prev_->prev_ = A[id];
            A[id]->prev_ = prev2;
            A[id]->next_ = prev;
        }
    }
}

LinkedList read_input()
{
    // Read input
    LinkedList A;
    int val;
    while (cin >> val)
        A.push_back(new Node(KEY * val));
    // Set up the linked list
    int N = A.size();
    for (int i = 0; i < N; i++) {
        A[i]->next_ = A[(i + 1) % N];
        A[i]->prev_ = A[(i - 1 + N) % N];
    }
    return A;
}

LL get_result(const LinkedList &A)
{
    vector<LL> V;
    auto test = A[0];
    int N = A.size();
    int id0 = 0;
    for (int i = 0; i < N; i++) {
        V.push_back(test->val_);
        if (test->val_ == 0)
            id0 = i;        
        test = test->next_;
    }
    return V[(id0 + 1000) % N] + V[(id0 + 2000) % N] + 
            V[(id0 + 3000) % N];
}

void clean(LinkedList &A)
{
    for (auto &n : A)
        delete n;
}
