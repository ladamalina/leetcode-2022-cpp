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
  static vl countOfPairs(int n, int x, int y) {
    if (x > y) {
      std::swap(x, y);
    }
    const auto head = x-1;
    const auto tail = n-y;
    const auto ring = y-x+1;
    const auto half = ring/2;
    vl res(n);
    if (ring <= 2) {
      for (int k = 1; k <= n; ++k) {
        res[k-1] += (n-k)*2;
      }
      return res;
    }
    // cycle >= 3
    for (int k = 1; k <= n; ++k) {
      if (k <= half) {
        if (k < half) res[k-1] += ring*2;
        else if (ring%2 == 0) res[k-1] += half*2;
        else res[k-1] += ring*2;
        
        if (head >= k) {
          res[k-1] += (head-k+1)*2;
        }
        if (head > 0) {
          res[k-1] += std::min(head, k-1)*2*2;
        }
        if (tail >= k) {
          res[k-1] += (tail-k+1)*2;
        }
        if (tail > 0) {
          res[k-1] += std::min(tail, k-1)*2*2;
        }
      } else { // k > half
        if (head >= k) {
          res[k-1] += (head-k+1)*2;
        }
        if (head > 0 && head+half >= k) {
          if (ring%2 == 1) res[k-1] += std::min(std::min(half, head), head+half-k+1)*2*2;
          else res[k-1] += std::min(std::min(half-1, head), head+half-k)*2*2 + 2;
        }
        if (tail >= k) {
          res[k-1] += (tail-k+1)*2;
        }
        if (tail > 0 && tail+half >= k) {
          if (ring%2 == 1) res[k-1] += std::min(std::min(half, tail), tail+half-k+1)*2*2;
          else res[k-1] += std::min(std::min(half-1, tail), tail+half-k)*2*2 + 2;
        }
      }
      if (head > 0 && tail > 0 && head+tail+1 >= k && k >= 3) {
        res[k-1] += std::min(head+tail+1-k+1, std::min(k-2, std::min(head, tail)))*2;
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution::countOfPairs(3, 1, 3);
    const vl e_out{6,0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution::countOfPairs(5, 2, 4);
    const vl e_out{10,8,2,0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution::countOfPairs(4, 1, 1);
    const vl e_out{6,4,2,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution::countOfPairs(4, 1, 4);
    const vl e_out{8,4,0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution::countOfPairs(5, 1, 3);
    const vl e_out{10,6,4,0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution::countOfPairs(5, 2, 5);
    const vl e_out{10,8,2,0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution::countOfPairs(6, 1, 4);
    const vl e_out{12,10,6,2,0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution::countOfPairs(6, 1, 5);
    const vl e_out{12,14,4,0,0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution::countOfPairs(7, 5, 3);
    const vl e_out{14,12,10,4,2,0,0};
    assert(a_out == e_out);

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
