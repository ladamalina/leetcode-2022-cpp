// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

#define RNG(_l) (_l).begin(), (_l).end()
#define CI(_v) static_cast<int>(_v)
#define CD(_v) static_cast<double>(_v)

using vi = std::vector<int>;

double RecOdd(const vi& a, const vi& b, int half_len, int l, int r) {
  while (l < r) {
    const auto med = (l + r) / 2;

    const auto al_it = std::lower_bound(RNG(a), med);
    const auto au_it = std::upper_bound(RNG(a), med);

    const auto bl_it = std::lower_bound(RNG(b), med);
    const auto bu_it = std::upper_bound(RNG(b), med);

    const auto cnt_med = CI(au_it - al_it) + CI(bu_it - bl_it);

    const auto cnt_lt = CI(al_it - a.begin()) + CI(bl_it - b.begin());
    const auto cnt_gt = CI(a.end() - au_it) + CI(b.end() - bu_it);

    const auto max_lt = std::max((al_it==a.begin() ? INT_MIN : *std::prev(al_it)),
                                 (bl_it==b.begin() ? INT_MIN : *std::prev(bl_it)));
    const auto min_gt = std::min((au_it==a.end() ? INT_MAX : *au_it),
                                 (bu_it==b.end() ? INT_MAX : *bu_it));

    if (cnt_lt <= half_len && cnt_gt <= half_len) { // found
      return med;
    }
    if (cnt_lt + cnt_med == cnt_gt+1) { // found
      return (cnt_med > 0) ? med : max_lt;
    }
    if (cnt_lt+1 == cnt_med + cnt_gt) { // found
      return (cnt_med > 0) ? med : min_gt;
    }
    if (cnt_lt >= cnt_gt) {
      r = med-1;
    } else { // cnt_lt < cnt_gt
      l = med+1;
    }
  }
  return r;
}

double RecEven(const vi& a, const vi& b, int half_len, int l, int r) {
  while (l < r) {
    const auto med = (l + r) / 2;

    const auto al_it = std::lower_bound(RNG(a), med);
    const auto au_it = std::upper_bound(RNG(a), med);

    const auto bl_it = std::lower_bound(RNG(b), med);
    const auto bu_it = std::upper_bound(RNG(b), med);

    const auto cnt_med = CI(au_it - al_it) + CI(bu_it - bl_it);

    const auto cnt_lt = CI(al_it - a.begin()) + CI(bl_it - b.begin());
    const auto cnt_gt = CI(a.end() - au_it) + CI(b.end() - bu_it);

    const auto max_lt = std::max((al_it==a.begin() ? INT_MIN : *std::prev(al_it)),
                                 (bl_it==b.begin() ? INT_MIN : *std::prev(bl_it)));
    const auto min_gt = std::min((au_it==a.end() ? INT_MAX : *au_it),
                                 (bu_it==b.end() ? INT_MAX : *bu_it));

    if (cnt_lt < half_len && cnt_gt < half_len) { // found
      return med;
    }
    if (cnt_lt + cnt_med == cnt_gt) { // found
      return (cnt_med > 0) ? CD(med + min_gt)/2 : CD(max_lt + min_gt)/2;
    }
    if (cnt_lt == cnt_med + cnt_gt) { // found
      return (cnt_med > 0) ? CD(max_lt + med)/2 : CD(max_lt + min_gt)/2;
    }
    if (cnt_lt >= cnt_gt) {
      r = med-1;
    } else { // cnt_lt < cnt_gt
      l = med+1;
    }
  }
  return r;
}

class Solution {
 public:
  static double findMedianSortedArrays(const vi& a, const vi& b) {
    const auto n = CI(a.size());
    const auto m = CI(b.size());
    
    const auto mn = std::min((a.empty() ? INT_MAX : a.front()),
                             (b.empty() ? INT_MAX : b.front()));
    const auto mx = std::max((a.empty() ? INT_MIN : a.back()),
                             (b.empty() ? INT_MIN : b.back()));
    const auto half_len = (n+m)/2;
    const auto res = ((n+m)%2 == 0) ? RecEven(a, b, half_len, mn, mx) : RecOdd(a, b, half_len, mn, mx);
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{1,3};
    const vi nums2{2};
    const auto a_out = Solution::findMedianSortedArrays(nums1, nums2);
    assert(a_out == 2.0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{1,2};
    const vi nums2{3,4};
    const auto a_out = Solution::findMedianSortedArrays(nums1, nums2);
    assert(a_out == 2.5);

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
