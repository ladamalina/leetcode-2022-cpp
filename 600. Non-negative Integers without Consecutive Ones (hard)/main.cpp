//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

const std::vector<int> FIB{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55,
                           89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765,
                           10946, 17'711, 28'657, 46'368, 75'025, 121'393, 196'418, 317'811, 514'229, 832'040,
                           1'346'269, 2'178'309, 3'524'578, 5'702'887, 9'227'465};

class Solution {
 public:
  int findIntegers(int n) {
    int n_max_bit = 31 - __builtin_clz(n);
    int max_good_num = n;
    bool big_bit_fixed = false;
    for (auto bit = n_max_bit-1; bit >= 0; --bit) {
      if (!big_bit_fixed) {
        if ((max_good_num & (1 << (bit+1))) != 0 && (max_good_num & (1 << (bit))) != 0) { // prev and current bits are 1
          max_good_num &= ~(1 << bit);
          big_bit_fixed = true;
        }
      } else {
        if ((max_good_num & (1 << (bit+1))) != 0) { // prev bit is 1
          max_good_num &= ~(1 << bit); // set current to 0
        } else { // prev bit is 0
          max_good_num |= (1 << bit); // set current to 1
        }
      }
    }
    int max_cnt = 0;
    for (auto bit = n_max_bit; bit >= 0; --bit) {
      if ((max_good_num & (1 << (bit))) != 0) { // 1, may be set to 0
        auto cnt = FIB[bit+2];
        max_cnt += cnt;
      }
    }
    ++max_cnt;
    return max_cnt;
  }
};

int main() {
  {
    int n = 5;
    int a_out = 5;
    auto e_out = Solution().findIntegers(n);
    assert(e_out == a_out);
  }
  {
    int n = 934734257;
    int a_out = 2178309;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto e_out = Solution().findIntegers(n);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(e_out == a_out);
  }
  {
    int n = 974380079;
    int a_out = 2178309;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto e_out = Solution().findIntegers(n);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(e_out == a_out);
  }
}
