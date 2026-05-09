#include <bits/stdc++.h>
#include <cassert>

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

struct DLListNode {
  ll val = -1;
  int idx = -1;
  std::shared_ptr<DLListNode> prev = nullptr;
  std::shared_ptr<DLListNode> next = nullptr;
  DLListNode() = default;
  explicit DLListNode(const ll v, const int i) : val(v), idx(i) {}
};

struct QItem {
  ll sum = 0;
  int idx = -1;
  std::shared_ptr<DLListNode> node = nullptr;
  bool operator==(const QItem& rhs) const {
    return std::tie(sum, idx) == std::tie(rhs.sum, rhs.idx);
  }
  bool operator<(const QItem& rhs) const {
    return std::tie(sum, idx) < std::tie(rhs.sum, rhs.idx);
  }
};

class Solution {
public:
  int minimumPairRemoval(const vi& a) {
    auto n = SZ(a);
    if (n == 1) return 0;
    
    auto head = std::make_shared<DLListNode>(a[0], 0);
    auto tail = head;
    std::set<QItem> q{{CL(a[0]) + a[1], 0, head}};
    FOR(i, 1, n-1) {
      const auto node = std::make_shared<DLListNode>(a[i], i);
      tail->next = node;
      node->prev = tail;
      tail = node;
      if (i + 1 < n)
        q.emplace(CL(a[i]) + a[i+1], i, tail);
    }
    
    auto n_bad = 0, n_ops = 0;
    FOR(i, 0, n-2) n_bad += (a[i] > a[i+1]);
    
    const auto merge = [&](const QItem& q_item) {
      const auto m1 = q_item.node, m2 = q_item.node->next;
      const auto l = m1->prev, r = m2->next;
      n_bad -= (m1->val > m2->val);
      if (l || r) {
        const auto m = std::make_shared<DLListNode>(m1->val + m2->val, m1->idx);
        if (l) {
          q.erase({l->val + m1->val, l->idx});
          n_bad -= (l->val > m1->val);
          l->next = m;
          m->prev = l;
          q.emplace(l->val + m->val, l->idx, l);
          n_bad += (l->val > m->val);
        }
        if (r) {
          q.erase({m2->val + r->val, m2->idx});
          n_bad -= (m2->val > r->val);
          m->next = r;
          r->prev = m;
          q.emplace(m->val + r->val, m->idx, m);
          n_bad += (m->val > r->val);
        }
      }
      --n;
      ++n_ops;
    };
    
    while (n_bad > 0 && n > 1) {
      const auto item = *q.begin();
      q.erase(item);
      merge(item);
    }
    return n_ops;
  }
};


[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const vi nums{5,2,3,1};
    const auto a_out = Solution().minimumPairRemoval(nums);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const vi nums{1,2,2};
    const auto a_out = Solution().minimumPairRemoval(nums);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
  return 0;
#endif
  return 0;
}
