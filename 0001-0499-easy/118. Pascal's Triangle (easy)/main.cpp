#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<int>> generate(const int n) {
    auto cn = 1;
    vector<vector<int>> res{{1}};
    while (cn < n) {
      res.emplace_back(cn + 1, 1);
      auto& row = res.back();
      for (auto i = 1; i < cn; ++i) {
        row[i] = res[cn-1][i-1] + res[cn-1][i];
      }
      ++cn;
    }
    return res;
  }
};
