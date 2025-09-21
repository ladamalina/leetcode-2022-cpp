// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

using SVI = std::unordered_map<std::string_view, int>;

class Solution {
public:
  vs findAllRecipes(const vs& recipes, const vvs& ingredients, const vs& supplies) {
    SVI recipe_id;
    std::unordered_map<std::string_view, std::unordered_set<std::string_view>> g;
    FOR(i, 0, SZ(recipes)-1) {
      recipe_id[recipes[i]] = i;
      for (const auto& s : ingredients[i]) {
        g[recipes[i]].insert(s);
      }
    }
    std::unordered_set<std::string_view> sup_set(RNG(supplies));

    SVI color;
    SVI v_res;
    const std::function<bool(std::string_view)> dfs = [&](std::string_view v) {
      if (!recipe_id.contains(v)) {
        return sup_set.contains(v);
      }
      if (color.contains(v) && color.at(v) == 2) {
        return v_res[v] == 1;
      }
      if (color.contains(v) && color.at(v) == 1) {
        v_res[v] = 0;
        return false;
      }
      color[v] = 1;
      auto n_sup = 0;
      for (const auto& u : ingredients[recipe_id.at(v)]) {
        n_sup += dfs(u);
      }
      color[v] = 2;
      v_res[v] = (n_sup == SZ(ingredients[recipe_id.at(v)]));
      return v_res[v] == 1;
    };
    vs res;
    for (const auto& recipe : recipes) {
      if (dfs(recipe)) {
        res.push_back(recipe);
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs recipes{"ju","fzjnm","x","e","zpmcz","h","q"};
    const vvs ingredients{{"d"},{"hveml","f","cpivl"},
      {"cpivl","zpmcz","h","e","fzjnm","ju"},
      {"cpivl","hveml","zpmcz","ju","h"},
      {"h","fzjnm","e","q","x"},
      {"d","hveml","cpivl","q","zpmcz","ju","e","x"},
      {"f","hveml","cpivl"}};
    const vs supplies{"f","hveml","cpivl","d"};
    auto a_out = Solution().findAllRecipes(recipes, ingredients, supplies);
    vs e_out{"fzjnm","ju","q"};
    SORT(a_out);
    SORT(e_out);
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
