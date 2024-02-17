#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

static std::random_device rd;
static std::mt19937 gen(rd());

class Solution {
 public:
  Solution(int n, vi& blacklist) : all_n_(0) {
    if (blacklist.empty()) {
      allowed_.emplace_back(0, n-1);
      pcnt_.emplace_back(n);
      return;
    }
    SORT(blacklist);
    const auto bl_n = CI(blacklist.size());
    if (blacklist.front() > 0)
      allowed_.emplace_back(0, blacklist.front()-1);
    FOR(i, 0, bl_n-2) {
      if (blacklist[i]+1 < blacklist[i+1])
        allowed_.emplace_back(blacklist[i]+1, blacklist[i+1]-1);
    }
    if (blacklist.back() < n-1)
      allowed_.emplace_back(blacklist.back()+1, n-1);
    for (const auto& lr : allowed_) {
      const auto cnt = lr.S - lr.F + 1;
      if (pcnt_.empty())
        pcnt_.emplace_back(cnt);
      else
        pcnt_.emplace_back(pcnt_.back() + cnt);
    }
  }

  [[nodiscard]] int pick() const {
    std::uniform_int_distribution<> dis_(1, pcnt_.back());
    const auto num_id = dis_(gen);
    const auto all_id = CI(std::lower_bound(RNG(pcnt_), num_id) - pcnt_.begin());
    if (all_id == 0) {
      return allowed_[all_id].F + (num_id-1);
    } else {
      const auto loc_id = num_id - pcnt_[all_id-1];
      return allowed_[all_id].F + (loc_id-1);
    }
  }
  
 private:
  int all_n_;
  vii allowed_;
  vi pcnt_;
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi blacklist{1,2,3,4,5};
    const Solution obj(6, blacklist);
    vi a_out;
    FOR(i, 1, 10) {
      a_out.push_back(obj.pick());
    }
    const vi e_out{0,0,0,0,0,0,0,0,0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const int n = 4;
    vi blacklist{0,2};
    const std::unordered_set<int> blacklist_set(RNG(blacklist));
    const Solution obj(n, blacklist);
    vi freq(n);
    FOR(i, 1, 1000) {
      const auto num = obj.pick();
      ++freq[num];
      assert(num >= 0 && num < n && !blacklist_set.contains(num));
    }
    /*FOR(i, 0, n-1) {
      std::cerr << i << ": " << freq[i] << '\n';
    }*/

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
