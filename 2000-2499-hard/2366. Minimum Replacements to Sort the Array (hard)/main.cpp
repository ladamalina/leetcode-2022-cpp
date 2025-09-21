#include <bits/stdc++.h>

class Solution {
 public:
  long long minimumReplacement(std::vector<int>& nums) {
    long long cnt = 0;
    const auto n = static_cast<int>(nums.size());
    for (int i = n-2; i >= 0; --i) {
      if (a[i] > a[i+1]) {
        const auto div = a[i] / a[i+1];
        const auto mod = a[i] % a[i+1];
        const auto k = (mod == 0) ? div : div + 1;
        cnt += k-1;
        a[i] /= k;
      }
    }
    return cnt;
  }
};
