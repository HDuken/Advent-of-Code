#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;
#define USE_SHARED_PTR false

struct Node
{
    int val_;
#if USE_SHARED_PTR
    shared_ptr<Node> prev_, next_;
#else
    Node *prev_, *next_;
#endif
    Node(const int &val)
    : val_(val), prev_(nullptr), next_(nullptr) {};
};

#if USE_SHARED_PTR
using LinkedList = vector<shared_ptr<Node>>;
#else
using LinkedList = vector<Node*>;
void clean(LinkedList &A);
#endif

LinkedList read_input();
void move(LinkedList &A, const int &id);
int get_result(const LinkedList &A);

void solve()
{
    LinkedList A = read_input();
    // Decrypt by mixing
    for (size_t i = 0; i < A.size(); i++)
        move(A, i);
    cout << get_result(A) << endl;
#if !USE_SHARED_PTR
    clean(A);
#endif
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
        for (int i = 0; i < iter1; i++) {
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
        for (int i = 0; i < iter2; i++) {
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
#if USE_SHARED_PTR
        A.push_back(make_shared<Node>(val));
#else
        A.push_back(new Node(val));
#endif

    // Set up the linked list
    int N = A.size();
    for (int i = 0; i < N; i++) {
        A[i]->next_ = A[(i + 1) % N];
        A[i]->prev_ = A[(i - 1 + N) % N];
    }
    return A;
}

int get_result(const LinkedList &A)
{
    vector<int> V;
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

#define TEST false
#if TEST
void print(const LinkedList &A)
{
    cout << "Order: ";
    auto test = A[0];
    int j = A.size();
    while (j > 0) {
        j--;
        cout << test->val_ << " ";
        test = test->next_;
    }
    cout << endl;
}
#endif

#if !USE_SHARED_PTR
void clean(LinkedList &A)
{
    for (auto &n : A)
        delete n;
}
#endif
