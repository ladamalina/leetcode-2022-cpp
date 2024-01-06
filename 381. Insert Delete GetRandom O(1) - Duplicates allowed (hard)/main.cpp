//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

static std::random_device rd;
static std::mt19937 gen(rd());

class RandomizedCollection {
  public:
  RandomizedCollection() = default;
    
  bool insert(const int val) {
    const auto inserted = !idx_.contains(val);
    idx_[val].insert(sz_);
    nums_[sz_] = val;
    ++sz_;
    return inserted;
  }
    
  bool remove(const int val) {
    const auto present = idx_.contains(val);
    if (present) {
      auto& v_ids = idx_.at(val);
      if (nums_[sz_-1] == val) {
        --sz_;
        v_ids.erase(sz_);
      } else {
        const auto v_id = *v_ids.begin();
        v_ids.erase(v_ids.begin());

        const auto u = nums_[sz_-1];
        auto& u_ids = idx_.at(u);
        --sz_;
        nums_[v_id] = u;
        u_ids.erase(sz_);
        u_ids.insert(v_id);
      }
      if (v_ids.empty()) idx_.erase(val);
    }
    return present;
  }
    
  int getRandom() {
    std::uniform_int_distribution<> dis(0, sz_-1);
    return nums_[dis(gen)];
  }

  private:
  int nums_[int(2*1e5)];
  int sz_ = 0;
  std::unordered_map<int, std::unordered_set<int>> idx_;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

/*
[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    std::vector<int> nums{3,1,5,8};
    const auto e_out = Solution::maxCoins(nums);
    assert(e_out == 167);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    std::vector<int> nums{1,5};
    const auto e_out = Solution::maxCoins(nums);
    assert(e_out == 10);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}
*/

int main() {
#ifndef NDEBUG
  // TestSolution();
#endif
  return 0;
}
