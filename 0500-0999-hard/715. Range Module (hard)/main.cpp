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

constexpr int MAX_X = 1e9;

constexpr auto comp_by_end = [](const ii& lhs, const ii& rhs) {
  return std::tie(lhs.S, lhs.F) < std::tie(rhs.S, rhs.F);
};

class RangeModule {
 public:
  RangeModule() : uncov_beg_{{1, MAX_X}}, uncov_end_{{1, MAX_X}} {}

  void addRange(int left, int right) {
    --right;

    auto it_m = uncov_beg_.lower_bound({left, 0});
    while (it_m != uncov_beg_.end() && it_m->S <= right) {
      const auto rng = *it_m;
      uncov_beg_.erase(rng);
      uncov_end_.erase(rng);
      it_m = uncov_beg_.lower_bound({left, 0});
    }

    auto it_r = uncov_beg_.lower_bound({left, 0});
    if (it_r != uncov_beg_.end() && it_r->F <= right) {
      const auto rng = *it_r;
      uncov_beg_.erase(rng);
      uncov_end_.erase(rng);
      const ii upd_rng{right+1, rng.S}; // cut
      uncov_beg_.insert(upd_rng);
      uncov_end_.insert(upd_rng);
    }

    auto it_l = uncov_end_.lower_bound({0, left});
    if (it_l != uncov_end_.end() && it_l->F < left) {
      const auto rng = *it_l;
      uncov_beg_.erase(rng);
      uncov_end_.erase(rng);
      const ii upd_rng_l{rng.F, left-1}; // cut
      uncov_beg_.insert(upd_rng_l);
      uncov_end_.insert(upd_rng_l);
      const ii upd_rng_r{right+1, rng.S}; // cut
      if (upd_rng_r.F <= upd_rng_r.S) {
        uncov_beg_.insert(upd_rng_r);
        uncov_end_.insert(upd_rng_r);
      }
    }
  }

  [[nodiscard]] bool queryRange(int left, int right) const {
    --right;

    auto it_r = uncov_beg_.lower_bound({left, 0});
    if (it_r != uncov_beg_.end() && it_r->F <= right) {
      return false;
    }
    auto it_l = uncov_end_.lower_bound({0, left});
    if (it_l != uncov_end_.end() && it_l->F < left) {
      return false;
    }
    return true;
  }

  void removeRange(int left, int right) {
    --right;
    
    auto it_m = uncov_beg_.lower_bound({left, 0});
    while (it_m != uncov_beg_.end() && it_m->S <= right) {
      const auto rng = *it_m;
      uncov_beg_.erase(rng);
      uncov_end_.erase(rng);
      it_m = uncov_beg_.lower_bound({left, 0});
    }
    
    auto l = left, r = right;
    auto it_r = uncov_beg_.lower_bound({left, 0});
    if (it_r != uncov_beg_.end() && it_r->F <= right) {
      const auto rng = *it_r;
      uncov_beg_.erase(rng);
      uncov_end_.erase(rng);
      l = std::min(l, rng.F);
      r = std::max(r, rng.S);
    }
    auto it_l = uncov_end_.lower_bound({0, left});
    if (it_l != uncov_end_.end() && it_l->F < left) {
      const auto rng = *it_l;
      uncov_beg_.erase(rng);
      uncov_end_.erase(rng);
      l = std::min(l, rng.F);
      r = std::max(r, rng.S);
    }
    uncov_beg_.emplace(l, r);
    uncov_end_.emplace(l, r);
  }
  
 private:
  std::set<ii> uncov_beg_;
  std::set<ii, decltype(comp_by_end)> uncov_end_;
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    RangeModule obj{};
    obj.addRange(10, 20);
    obj.removeRange(14, 16);
    assert(obj.queryRange(10, 14));
    assert(!obj.queryRange(13, 15));
    assert(obj.queryRange(16, 17));

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    RangeModule obj{};
    obj.removeRange(4,8);
    obj.addRange(1, 10);
    assert(obj.queryRange(1, 7));
    obj.addRange(2, 3);
    obj.removeRange(2, 3);
    assert(obj.queryRange(8, 9));
    obj.addRange(2, 3);
    obj.removeRange(1, 8);

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
