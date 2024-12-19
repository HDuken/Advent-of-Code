#pragma GCC optimize("O2,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
#define TEST false
const string CD = "$ cd";
const string LS = "$ ls";
const int SIZE_LIMIT = 100'000;
using LL = long long;

struct File
{
    string name_;
    LL size_;
    File(const string &name, const LL &size)
    : name_(name), size_(size) {};
};

struct Dir
{
    string name_;
    LL size_;
    Dir* parent_;
    vector<Dir*> subdirs_;
    vector<File*> files_;

    Dir(const string &name, const LL &size, Dir* parent)
    : name_(name), size_(size), parent_(parent) {};

    void add_file(const string &name, const LL &s);
    void add_dir(const string &name);
    Dir* cd_subdir(const string &name);
};

class FileTree
{
private:
    Dir *root_;
    static void clean_up(Dir *dir);
    static void print(Dir *dir);
    static void propagate_size(Dir *dir);
    static void sum_size(Dir *dir, LL &sum);

public:
    FileTree() : root_(new Dir("/", 0, nullptr)) {};
    ~FileTree() {  clean_up(root_); };
    void print() const { print(root_); };
    Dir* get_root() const { return root_; };
    void propagate_size() { propagate_size(root_); };
    void sum_size(LL &sum) const { sum_size(root_, sum); };
};

FileTree read_input();

void solve()
{
    FileTree tree = read_input();
    tree.propagate_size();

    LL result = 0;
    tree.sum_size(result);
    cout << result << endl;
}

int main(int argc, char const *argv[])
{
    solve();
    return 0;
}

FileTree read_input()
{
    FileTree tree;
    Dir* current_dir = tree.get_root();
#if TEST
    ifstream infile("test.txt");
#else
    ifstream infile("day7.txt");
#endif
    if (infile.is_open()) {
        string line;
        stringstream ss;
        string str, name;
        char c;
        LL size;
        while (getline(infile, line)) {
            if (line.find(CD) != string::npos) {
                ss.clear();
                ss.str(line);
                ss >> c >> str >> name;
                if (name == "/") {
                    current_dir = tree.get_root();
                }   else if (name == "..") {
                    current_dir = current_dir->parent_;
                }   else {
                    current_dir = current_dir->cd_subdir(name);
                }
            }   else if (line.find(LS) != string::npos) {
                continue;
            }   else {
                ss.clear();
                ss.str(line);
                ss >> str;
                if (str == "dir") {
                    ss >> name;
                    current_dir->add_dir(name);
                }   else {
                    size = stoll(str);
                    ss >> name;
                    current_dir->add_file(name, size);
                }
            }
        }
    }   else cout << "Unable to open file" << endl;
    return tree;
}

void Dir::add_file(const string &name, const LL &size)
{
    File *file = new File(name, size);
    files_.push_back(file);
}

void Dir::add_dir(const string &name)
{
    Dir *dir = new Dir(name, 0, this);
    subdirs_.push_back(dir);
}

Dir* Dir::cd_subdir(const string &name)
{
    for (auto subdir : subdirs_) {
        if (subdir->name_ == name) {
            return subdir;
        }
    }
    return nullptr;
}

void FileTree::clean_up(Dir *dir)
{
    for (auto file : dir->files_) {
        delete file;
    }
    for (auto subdir : dir->subdirs_) {
        clean_up(subdir);
    }
    delete dir;        
}

void FileTree::print(Dir *dir)
{
    cout << dir->name_ << " (dir, size = " << dir->size_ << ")" << endl;
    for (auto subdir : dir->subdirs_) {
        print(subdir);
    }
    for (auto file : dir->files_) {
        cout << file->name_ << " (file, size = " << file->size_ << ")" << endl;
    }
}

void FileTree::propagate_size(Dir *dir)
{
    LL size = 0;
    for (auto file : dir->files_) {
        size += file->size_;
    }
    for (auto subdir : dir->subdirs_) {
        propagate_size(subdir);
        size += subdir->size_;
    }
    dir->size_ = size;
}

void FileTree::sum_size(Dir *dir, LL &sum)
{
    if (dir->size_ <= SIZE_LIMIT) {
        sum += dir->size_;
    }
    for (auto subdir : dir->subdirs_) {
        sum_size(subdir, sum);
    }
}
