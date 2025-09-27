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
using ld = long double;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

constexpr int MAX_P = 1e5;
std::array<int, MAX_P> p_ts, p_src, p_dst;

using Packet = std::pair<int, ii>;
struct HashPacket {
  const int P = 37, P2 = P * P, P3 = P2 * P;
  size_t operator()(const Packet& x) const {
    return CL(x.F) * P + CL(x.S.F) * P2 + CL(x.S.S) * P3;
  }
};

class Router {
public:
  explicit Router(const int memory_limit) : capacity(memory_limit) {}
    
  bool addPacket(const int src, const int dst, const int ts) {
    const Packet packet{ts, ii{src, dst}};
    if (used.contains(packet)) return false;

    if (end - beg == capacity) {
      used.erase({p_ts[beg], ii{p_src[beg], p_dst[beg]}});
      ++dst_beg[p_dst[beg]];
      ++beg;
    }
    
    used.insert(packet);
    p_ts[end] = ts;
    p_src[end] = src;
    p_dst[end] = dst;
    ++end;
    dst_ts[dst].push_back(ts);
    return true;
  }
    
  vi forwardPacket() {
    if (beg == end) return {};
    used.erase({p_ts[beg], ii{p_src[beg], p_dst[beg]}});
    ++dst_beg[p_dst[beg]];
    ++beg;
    return vi{p_src[beg-1], p_dst[beg-1], p_ts[beg-1]};
  }
    
  int getCount(const int dst, const int st_t, const int en_t) {
    const auto& arr = dst_ts[dst];
    const int lo = std::lower_bound(arr.begin() + dst_beg[dst], arr.end(), st_t) - arr.begin();
    const int up = std::upper_bound(arr.begin() + dst_beg[dst], arr.end(), en_t) - arr.begin();
    return std::max(up - lo, 0);
  }

private:
  int capacity, beg = 0, end = 0;
  std::unordered_set<Packet, HashPacket> used;
  std::unordered_map<int, vi> dst_ts;
  std::unordered_map<int, int> dst_beg;
};

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    Router router(3);
    assert(router.addPacket(1, 4, 90));
    assert(router.addPacket(2, 5, 90));
    assert(!router.addPacket(1, 4, 90));
    assert(router.addPacket(3, 5, 95));
    assert(router.addPacket(4, 5, 105));
    {
      const auto a_out = router.forwardPacket();
      const vi e_out{2, 5, 90};
      assert(a_out == e_out);
    }
    assert(router.addPacket(5, 2, 110));
    assert(router.getCount(5, 100, 110) == 1);
    router.forwardPacket();
  
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
