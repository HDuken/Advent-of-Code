/*
 *   Copyright (c) 2024 Duc Huu Nguyen
 *   All rights reserved.
 */

#include "../pch.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

int ans = 0; // Test
vector<int> d = {1, 2, 3};

vector<vector<int>> reports;

void read_input() {
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    vector<int> report;
    int temp;
    while (ss >> temp) {
      report.push_back(temp);
    }
    reports.push_back(report);
  }
}

vector<int> check_report(const vector<int> &report) {
  set<int> unique_id_errors;

  // If the distance between a pair is wrong
  for (int i = 0; i < report.size() - 1; i++) {
    if (find(all(d), abs(report[i] - report[i + 1])) == d.end()) {
      unique_id_errors.insert(i);
      unique_id_errors.insert(i + 1);
    }
  }

  for (int i = 1; i < report.size() - 1; i++) {
    if ((report[i] > report[i - 1] && report[i] > report[i + 1]) ||
        (report[i] < report[i - 1] && report[i] < report[i + 1])) {
      unique_id_errors.insert(i);
    }
  }

  vector<int> id_errors;
  id_errors.assign(all(unique_id_errors));
  return id_errors;
}

void solve() {
  for (auto report : reports) {
    vector<int> id_errors = check_report(report);

#if PART1
    if (id_errors.size() == 0)
      ans++;
#else
    if (id_errors.size() == 0) {
      ans++;
    } else {
      id_errors.push_back(0);
      id_errors.push_back(report.size() - 1);
      for (int i : id_errors) {
        vector<int> temp_report(report);
        temp_report.erase(temp_report.begin() + i);
        if (check_report(temp_report).size() == 0) {
          ans++;
          break;
        }
      }
    }
#endif // PART1
  }

  LOG(ans);
}

int main(int argc, char const *argv[]) {
  read_input();
  solve();
  return 0;
}
