//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<ld>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define F first
#define S second
#define PB push_back

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
  static bool hasCycle(ListNode* head) {
    if (!head)
      return false;

    auto link1 = head;
    auto link2 = head;
    while (true) {
      // move link1 1 step forward
      if (!link1->next)
        return false;
      link1 = link1->next;

      // move link2 2 steps forward
      if (!link2->next || !link2->next->next)
        return false;
      link2 = link2->next->next;

      if (link1 == link2)
        return true;
    }
    return false;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{1,3,5,4};
    const vi nums2{1,2,3,7};
    const auto a_out = Solution::minSwap(nums1, nums2);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{0,3,5,8,9};
    const vi nums2{2,1,4,6,9};
    const auto a_out = Solution::minSwap(nums1, nums2);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
