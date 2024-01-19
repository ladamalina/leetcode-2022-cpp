// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

constexpr int MAX_SZ = 2*1e5;
int vals_[MAX_SZ];

static std::random_device rd;
static std::mt19937 gen(rd());

class RandomizedSet {
  public:
  RandomizedSet() = default;
    
  bool insert(const int val) {
    if (ids_.contains(val)) {
      return false;
    }
    ids_[val] = sz_;
    vals_[sz_] = val;
    ++sz_;
    return true;
  }
    
  bool remove(const int val) {
    if (!ids_.contains(val)) {
      return false;
    }
    const auto i = ids_.at(val);
    if (i != sz_-1) {
      const auto new_val = vals_[sz_-1];
      vals_[i] = new_val;
      ids_[new_val] = i;
    }
    --sz_;
    ids_.erase(val);
    return true;
  }
    
  int getRandom() const {
    std::uniform_int_distribution<> dis(0, sz_-1);
    return vals_[dis(gen)];
  }

  private:
  int sz_ = 0;
  std::unordered_map<int, int> ids_;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

/*[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{5,2,2};
    const auto a_out = Solution::findMaximumLength(nums);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}*/

int main() {
#ifndef NDEBUG
  // TestSolution();
#endif
  return 0;
}
