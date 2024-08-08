#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second

int DFS(int k, std::string& pref, int h, const std::string& n_str, int n_len, int& res) {
  if (k == 0) res = std::stoi(pref);
  
  const auto is_pref = n_str.starts_with(pref);
  if (is_pref && h == n_len) return 0;
  if (!is_pref && pref < n_str && h == n_len) return 0;
  if (!is_pref && pref > n_str && h == n_len-1) return 0;

  const auto min_d = (h==0) ? '1' : '0';
  const auto max_d = (h == n_len-1 && is_pref) ? n_str[h] : '9';
  auto curr_sum = 0;
  
  for (auto d = min_d; d <= max_d; ++d) {
    pref.push_back(d);
    int sub_sum = 0;
    if (n_str.starts_with(pref)) {
      sub_sum = 1 + DFS(k-1-curr_sum, pref, h+1, n_str, n_len, res);
    } else {
      const auto tree_h = (pref < n_str) ? n_len-h : n_len-1-h;
      const auto tree_k = (CI(std::pow(10, tree_h)) - 1)/9;
      sub_sum = tree_k;
      if (curr_sum < k && curr_sum + sub_sum >= k) {
        DFS(k-1-curr_sum, pref, h+1, n_str, n_len, res);
      }
    }
    curr_sum += sub_sum;
    pref.pop_back();
  }
  return curr_sum;
}

class Solution {
public:
  int findKthNumber(int n, int k) {
    if (k == 1) return 1;
    // k >= 2
    const auto n_str = std::to_string(n);
    const auto n_len = CI(n_str.size());
    std::string pref;
    int res = -1;
    DFS(k, pref, 0, n_str, n_len, res);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findKthNumber(13, 2);
    assert(a_out == 10);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findKthNumber(1, 1);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findKthNumber(10, 3);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findKthNumber(100, 10);
    assert(a_out == 17);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findKthNumber(4289384, 1922239);
    assert(a_out == 2730010);
  
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
