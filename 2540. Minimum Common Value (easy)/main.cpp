// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vl = std::vector<ll>;
using vii = std::vector<ii>;

class Solution {
public:
  static int getCommon(const vector<int>& nums1, const vector<int>& nums2) {
    const int n1 = nums1.size();
    const int n2 = nums2.size();
    int i1 = 0;
    int i2 = 0;
    while (i1 < n1 && i2 < n2) {
      if (nums1[i1] < nums2[i2]) {
        ++i1;
      } else if (nums1[i1] > nums2[i2]) {
        ++i2;
      } else {
        return nums1[i1];
      }
    }
    return -1;
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution::countOfPairs(3, 1, 3);
    const vl e_out{6,0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
