// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using vi = std::vector<int>;
using vvi = std::vector<vi>;

int dp[100][100];

class Solution {
  public:
  static int findRotateSteps(const std::string& ring, const std::string& key) {
    const auto ring_n = static_cast<int>(ring.size());
    const auto key_n = static_cast<int>(key.size());
    vvi pos(26);
    for (int i = 0; i < ring_n; ++i) {
      pos[ring[i]-'a'].push_back(i);
    }
    
    std::function<int(int,int)> rec = [&](int key_i, int prev_id) {
      if (key_i == key_n) return 0;
      auto& dp_res = dp[key_i][prev_id];

      if (dp_res == -1) {
        int res = INT_MAX;
        const auto& next_ids = pos[key[key_i]-'a'];
        const auto it = std::lower_bound(next_ids.begin(), next_ids.end(), prev_id);

        if (it != next_ids.end() && *it == prev_id) {
          const auto sub_res = rec(key_i+1, prev_id);
          res = std::min(res, 1 + sub_res);
        } else {
          const auto next_id_l = (it == next_ids.begin()) ? next_ids.back() : *std::prev(it);
          const auto dir_dist_l = std::abs(prev_id-next_id_l);
          const auto cost_l = 1 + std::min(dir_dist_l, ring_n-dir_dist_l);
          const auto sub_res_l = rec(key_i+1, next_id_l);
          res = std::min(res, cost_l + sub_res_l);
        
          const auto next_id_r = (it == next_ids.end()) ? next_ids.front() : *it;
          if (next_id_l != next_id_r) {
            const auto dir_dist_r = std::abs(prev_id-next_id_r);
            const auto cost_r = 1 + std::min(dir_dist_r, ring_n-dir_dist_r);
            const auto sub_res_r = rec(key_i+1, next_id_r);
            res = std::min(res, cost_r + sub_res_r);
          }
        }
        dp_res = res;
      }
      return dp_res;
    };

    memset(&dp, -1, sizeof(dp));
    const auto ans = rec(0, 0);
    return ans;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::findRotateSteps("godding", "gd");
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::findRotateSteps("godding", "godding");
    assert(a_out == 13);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::findRotateSteps("caotmcaataijjxi", "oatjiioicitatajtijciocjcaaxaaatmctxamacaamjjx");
    assert(a_out == 137);

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
