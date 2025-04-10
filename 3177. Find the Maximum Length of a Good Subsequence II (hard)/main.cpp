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
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

template<typename T>
class SegTree { // Дерево отрезков на максимум
public:
  explicit SegTree(const std::vector<T>& a)
      : MIN(std::numeric_limits<T>::min()) {
    while (size_ < CI(a.size())) size_ *= 2;
    t_.resize(size_ * 2 - 1, MIN);
    Init(a, 0, 0, size_);
  }

  T GetMax(int l, int r) {
    return GetMax(l, r, 0, 0, size_);
  }

  void Set(int i, T v) {
    Set(i, v, 0, 0, size_);
  }

private:
  std::vector<T> t_;
  int size_ = 1;
  const T MIN;

  void Init(const std::vector<T>& a, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      if (lx < CI(a.size())) t_[x] = a[lx];
    } else {
      const auto m = (lx + rx) / 2;
      Init(a, 2*x+1, lx, m);
      Init(a, 2*x+2, m, rx);
      t_[x] = std::max(t_[2*x+1], t_[2*x+2]);
    }
  }

  T GetMax(int l, int r, int x, int lx, int rx) {
    if (rx <= l || lx >= r) return MIN;
    if (rx <= r && lx >= l) return t_[x];
    const auto m = (lx + rx) / 2;
    return std::max(GetMax(l, r, 2*x+1, lx, m), GetMax(l, r, 2*x+2, m, rx));
  }

  void Set(int i, T v, int x, int lx, int rx) {
    if (lx + 1 == rx) {
      t_[x] = v;
      return;
    }
    const auto m = (lx + rx) / 2;
    if (i < m) Set(i, v, 2*x+1, lx, m);
    else Set(i, v, 2*x+2, m, rx);
    t_[x] = std::max(t_[2*x+1], t_[2*x+2]);
  }
};

class Solution {
public:
  int maximumLength(const vi& nums, const int max_k) {
    const auto n = CI(nums.size());

    std::set<int> x_set(RNG(nums));
    std::unordered_map<int, int> x_comp;
    for (const auto x : x_set) {
      x_comp[x] = SZ(x_comp);
    }
    const auto nx = SZ(x_comp);

    std::vector<SegTree<int>> k_dp(max_k+1, SegTree<int>(vi(nx)));
    vi i_dp(max_k+1);
    FOR(i, 0, n-1) {
      const auto x = x_comp[nums[i]];
      std::fill(RNG(i_dp), 0);
      i_dp[0] = 1;
      FOR(k, 0, max_k) {
        const auto max_eq = k_dp[k].GetMax(x, x+1);
        i_dp[k] = std::max(i_dp[k], max_eq + 1);
        if (k < max_k) {
          const auto max_uq = std::max(k_dp[k].GetMax(0, x), k_dp[k].GetMax(x+1, nx));
          i_dp[k+1] = std::max(i_dp[k+1], max_uq + 1);
        }
      }
      FOR(k, 0, max_k) {
        if (i_dp[k] > k_dp[k].GetMax(x,x+1))
          k_dp[k].Set(x, i_dp[k]);
      }
    }

    int max_res = 0;
    FOR(k, 0, max_k) {
      max_res = std::max(max_res, k_dp[k].GetMax(0, nx));
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1, 2, 1, 1, 3};
    const auto a_out = Solution().maximumLength(nums, 2);
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1, 2, 3, 4, 5, 1};
    const auto a_out = Solution().maximumLength(nums, 0);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{79, 241, 141, 207, 97, 80, 51, 105, 133, 162, 85, 167, 183, 32, 110, 97, 212, 213, 127, 142, 208, 206,
                  142, 109, 141, 226, 181, 130, 133, 163, 233, 78, 71, 190, 199, 49, 26, 229, 86, 77, 103, 245, 151, 32,
                  162, 160, 207, 56, 228, 87, 61, 50, 29, 62, 89, 212, 114, 53, 196, 166, 231, 107, 246, 174, 182, 25,
                  198, 114, 76, 141, 86, 202, 185, 249, 53, 116, 58, 183, 79, 186, 144, 219, 169, 93, 31, 74, 110, 243,
                  171, 138, 73, 162, 137, 210, 160, 202, 119, 136, 129, 166, 100, 189, 93, 122, 63, 155, 114, 94, 97,
                  45, 97, 194, 117, 169, 211, 49, 243, 118, 176, 185, 33, 142, 59, 122, 40, 238, 226, 170, 195, 122, 47,
                  228, 185, 195, 130, 133, 228, 164, 174, 77, 135, 30, 145, 61, 145, 239, 46, 96, 43, 74, 103, 247, 64,
                  203, 219, 186, 99, 82, 110, 62, 230, 120, 89, 30, 244, 28, 63, 88, 71, 179, 159, 70, 158, 165, 187,
                  218, 244, 197, 132, 81, 78, 197, 136, 237, 29, 68, 173, 123, 195, 39, 94, 53, 219, 152, 35, 146, 153,
                  198, 150, 227, 69, 77, 144, 204, 244, 57, 236, 81, 211, 249, 213, 94, 216, 216, 248, 211, 222, 207,
                  180, 43, 100, 181, 186, 115, 147, 246, 88, 51, 223, 84, 183, 58, 191, 106, 112, 27, 108, 102, 197, 27,
                  232, 221, 81, 156, 96, 179, 217, 42, 225, 114, 87, 56, 77, 105, 150, 115, 197, 196, 223, 164, 116,
                  236, 193, 58, 218, 141, 209, 237, 95, 59, 169, 148, 177, 68, 100, 130, 201, 172, 231, 174, 210, 141,
                  208, 87, 147, 118, 46, 195, 36, 130, 83, 61, 46, 106, 143, 170, 101, 112, 111, 125, 149, 249, 197,
                  106, 233, 178, 48, 230, 105, 206, 182, 118, 186, 123, 109, 157, 134, 65, 165, 34, 180, 228, 143, 54,
                  236, 105, 91, 178, 230, 39, 71, 53, 107, 135, 78, 202, 73, 150, 70, 91, 40, 240, 129, 250, 89, 84,
                  169, 57, 86, 145, 60, 128, 31, 60, 156, 100, 165, 194, 216, 211, 192, 159, 204, 69, 41, 93, 168, 61,
                  105, 153, 241, 111, 48, 151, 44, 223, 208, 177, 232, 55, 107, 159, 106, 118, 96, 173, 42, 236, 106,
                  131, 70, 224, 149, 71, 132, 63, 52, 132, 229, 126, 81, 104, 79, 95, 232, 189, 193, 150, 59, 196, 187,
                  120, 191, 233, 231, 131, 144, 192, 65, 207, 127, 96, 226, 96, 237, 169, 209, 74, 157, 166, 25, 59,
                  187, 56, 238, 123, 243, 202, 156, 136, 25, 228, 217, 175, 81, 66, 188, 36, 145, 202, 34, 218, 191,
                  244, 129, 156, 48, 160, 227, 167, 127, 106, 233, 135, 190, 230, 108, 113, 124, 174, 239, 84, 210, 50,
                  53, 143, 223, 247, 118, 171, 160, 222, 67, 224, 250, 122, 120, 76, 95, 208, 109, 72, 233, 194, 85, 67,
                  98, 196, 194, 212, 112, 173, 204, 125, 49, 55, 129, 223, 160, 46, 222, 138, 28, 166, 176, 107, 95, 46,
                  120, 114, 132, 115, 102, 115, 59, 159, 105, 161, 237, 203, 198, 157, 206, 225, 79, 218, 142, 143, 27,
                  188, 218, 112, 102, 111, 115, 223, 136, 53, 150, 90, 245, 70, 114, 155, 201, 144, 214, 58, 110, 68,
                  56, 109, 215, 229, 199, 194, 107, 134, 220, 167, 76, 184, 96, 70, 65, 112, 242, 32, 116, 104, 56, 236,
                  96, 113, 232, 162, 41, 204, 84, 55, 209, 208, 39, 189, 162, 229, 119, 243, 96, 94, 140, 159, 116, 53,
                  119, 169, 207, 50, 236, 171, 133, 196, 57, 75, 119, 33, 237, 90, 218, 26, 117, 181, 170, 63, 96, 172,
                  213, 103, 191, 189, 168, 172, 209, 215, 187, 207, 107, 45, 165, 202, 61, 75, 107, 213, 82, 229, 110,
                  173, 219, 87, 247, 122, 219, 73, 27, 54, 64, 207, 42, 198, 156, 107, 78, 67, 141, 69, 232, 204, 84,
                  65, 208, 224, 109, 210, 125, 212, 85, 78, 113, 247, 73, 116, 70, 213, 68, 91, 135, 227, 207, 149, 203,
                  189, 240, 164, 181, 128, 79, 89, 48, 90, 165, 116, 172, 155, 159, 242, 227, 107, 196, 209, 59, 248,
                  160, 84, 178, 43, 26, 80, 152, 96, 106, 199, 217, 98, 164, 129, 238, 115, 228, 128, 239, 242, 198,
                  237, 141, 248, 127, 191, 86, 75, 32, 117, 113, 119, 50, 26, 155, 85, 181, 210, 183, 104, 116, 47, 111,
                  43, 140, 201, 202, 227, 240, 172, 46, 39, 154, 216, 228, 109, 164, 80, 79, 132, 138, 68, 129, 208,
                  116, 201, 180, 185, 100, 200, 195, 39, 44, 127, 27, 121, 156, 92, 67, 241, 192, 186, 28, 143, 127, 88,
                  158, 114, 154, 50, 89, 237, 199, 56, 31, 228, 46, 124, 244, 138, 215, 102, 53, 52, 62, 182, 37, 82,
                  101, 158, 237, 62, 30, 239, 137, 171, 250, 159, 193, 214, 107, 222, 166, 172, 55, 250, 74, 157, 189,
                  136, 34, 49, 29, 217, 207, 175, 94, 51, 113, 177, 126, 38, 132, 170, 212, 188, 125, 239, 79, 133, 94,
                  90, 173, 81, 242, 38, 139, 137, 196, 111, 73, 116, 172, 248, 116, 26, 78, 61, 113, 130, 119, 140, 180,
                  174, 211, 123, 118, 197, 120, 139, 238, 115, 175, 198, 152, 175, 148, 77, 158, 230, 135, 184, 201, 59,
                  35, 28, 218, 143, 197, 69, 188, 124, 233, 81, 52, 51, 134, 150, 160, 96, 164, 172, 25, 74, 193, 111,
                  84, 53, 91, 124, 86, 53, 61, 167, 196, 194, 115, 166, 173, 133, 132, 141, 226, 96, 201, 48, 212, 84,
                  201, 94, 197, 199, 165, 75, 244, 105, 155, 220, 131, 30, 160, 54, 53, 42, 232, 177, 184, 129, 143,
                  146, 247, 83, 127, 210, 136, 146, 56, 102, 37, 143, 230, 245, 178, 67, 144, 155, 51, 178, 108, 154,
                  69, 135, 85, 38, 196, 28, 228, 231, 120, 227, 83, 52, 239, 153, 167, 38, 140, 63, 112, 38, 91, 145,
                  151, 208, 179, 229, 240, 55, 174, 85, 28, 216, 135, 132, 72, 180, 65, 85, 79, 141, 85, 177, 147, 157,
                  66, 242, 130, 226, 203, 97, 238, 127, 129, 67, 30, 210, 232, 32, 166, 75, 221, 109, 214, 167, 147,
                  158, 191, 219, 208, 66, 125, 73, 92, 234, 136, 39, 75, 94, 116, 70, 159, 35, 128, 206, 185, 37, 31,
                  110, 247, 241, 127, 166, 139, 121, 225, 155, 162, 119, 134, 164, 160, 84, 210, 191, 89, 197, 237, 143,
                  30, 75, 219, 179, 137, 103, 160, 182, 205, 53, 90, 183, 29, 93, 234, 70, 149, 198, 232, 29, 245, 175,
                  219, 102, 157, 186, 140, 131, 243, 124, 191, 75, 230, 142, 129, 78, 185, 53, 90, 187, 240, 46, 125,
                  190, 61, 242, 146, 184, 111, 245, 199, 155, 132, 138, 30, 65, 107, 235, 219, 38, 146, 209, 72, 110,
                  157, 181, 40, 75, 50, 185, 178, 133, 247, 191, 194, 71, 44, 190, 180, 207, 248, 187, 121, 218, 203,
                  236, 182, 79, 41, 32, 124, 138, 117, 202, 139, 147, 190, 207, 94, 124, 232, 128, 127, 96, 38, 178, 44,
                  243, 127, 76, 189, 27, 242, 193, 112, 247, 71, 160, 41, 138, 232, 53, 41, 64, 194, 25, 116, 234, 90,
                  133, 47, 222, 46, 36, 190, 202, 199, 99, 126, 109, 186, 226, 217, 40, 109, 202, 103, 27, 142, 125, 50,
                  159, 55, 91, 33, 169, 153, 236, 167, 237, 93, 41, 186, 130, 59, 225, 176, 123, 240, 166, 87, 203, 98,
                  152, 138, 207, 144, 65, 129, 165, 237, 133, 164, 81, 82, 200, 216, 216, 68, 214, 86, 221, 69, 41, 219,
                  128, 37, 128, 204, 246, 100, 74, 142, 203, 103, 215, 41, 196, 186, 64, 208, 93, 147, 143, 178, 159,
                  165, 72, 31, 223, 79, 130, 71, 240, 225, 88, 222, 153, 29, 179, 226, 53, 214, 248, 131, 118, 122, 157,
                  165, 214, 27, 183, 182, 153, 93, 230, 238, 227, 148, 160, 64, 63, 212, 245, 111, 64, 196, 243, 25,
                  103, 99, 150, 50, 189, 161, 154, 196, 32, 214, 96, 136, 92, 238, 39, 233, 221, 148, 141, 92, 149, 62,
                  180, 57, 48, 211, 111, 50, 50, 30, 160, 110, 187, 81, 73, 67, 74, 185, 62, 213, 211, 212, 47, 71, 65,
                  25, 243, 104, 151, 27, 61, 43, 212, 115, 178, 103, 139, 74, 51, 224, 220, 105, 99, 188, 245, 210, 119,
                  122, 196, 146, 233, 160, 78, 161, 210, 119, 173, 207, 168, 194, 231, 141, 129, 232, 117, 159, 212,
                  199, 126, 205, 96, 104, 145, 25, 70, 203, 105, 184, 70, 223, 35, 135, 94, 41, 241, 187, 115, 231, 33,
                  82, 234, 142, 157, 86, 209, 228, 37, 120, 88, 220, 200, 154, 214, 228, 231, 111, 149, 182, 213, 247,
                  33, 61, 171, 147, 70, 114, 239, 60, 224, 94, 30, 167, 65, 204, 94, 241, 127, 161, 104, 250, 146, 235,
                  25, 155, 179, 35, 237, 114, 133, 67, 212, 158, 108, 172, 84, 32, 99, 78, 157, 93, 36, 148, 187, 35,
                  188, 241, 243, 154, 93, 189, 155, 37, 238, 136, 223, 72, 180, 59, 98, 154, 69, 154, 107, 77, 80, 127,
                  54, 112, 216, 206, 124, 27, 215, 167, 66, 37, 67, 29, 193, 102, 177, 53, 181, 77, 141, 178, 69, 41,
                  44, 150, 249, 51, 163, 31, 122, 122, 26, 137, 223, 240, 99, 249, 100, 186, 61, 96, 150, 115, 53, 44,
                  94, 183, 134, 138, 90, 214, 229, 31, 145, 246, 131, 26, 176, 192, 66, 177, 112, 32, 237, 142, 78, 178,
                  56, 157, 83, 93, 103, 37, 38, 52, 236, 125, 63, 206, 245, 106, 133, 94, 84, 100, 81, 89, 84, 202, 148,
                  87, 66, 81, 180, 130, 172, 119, 228, 30, 114, 185, 233, 92, 73, 215, 114, 157, 121, 83, 250, 219, 57,
                  156, 177, 42, 159, 147, 110, 180, 157, 180, 44, 46, 121, 130, 143, 223, 145, 122, 134, 196, 181, 232,
                  137, 194, 71, 111, 228, 118, 101, 238, 85, 168, 161, 248, 139, 132, 241, 94, 114, 98, 143, 84, 30,
                  115, 233, 60, 75, 219, 46, 103, 137, 65, 85, 108, 194, 102, 218, 195, 46, 122, 164, 223, 180, 51, 144,
                  213, 228, 159, 207, 179, 91, 162, 112, 98, 172, 80, 244, 74, 66, 188, 107, 74, 199, 202, 205, 58, 146,
                  162, 29, 32, 137, 34, 197, 52, 236, 217, 162, 71, 119, 242, 197, 82, 118, 184, 189, 82, 125, 244, 111,
                  171, 47, 37, 227, 219, 172, 192, 177, 218, 207, 201, 96, 231, 205, 28, 48, 32, 203, 246, 199, 139, 56,
                  93, 135, 42, 74, 97, 162, 158, 39, 109, 132, 219, 52, 227, 72, 103, 181, 200, 155, 144, 221, 50, 138,
                  155, 84, 50, 183, 189, 239, 187, 82, 93, 58, 127, 52, 132, 206, 36, 115, 120, 35, 134, 39, 33, 185,
                  42, 60, 66, 106, 118, 181, 221, 156, 188, 35, 121, 96, 214, 96, 228, 64, 213, 115, 194, 195, 247, 123,
                  241, 57, 200, 219, 209, 80, 233, 214, 120, 212, 169, 143, 120, 30, 57, 64, 233, 166, 242, 228, 197,
                  204, 63, 158, 83, 40, 153, 222, 204, 117, 62, 65, 26, 127, 106, 117, 167, 64, 129, 41, 30, 225, 207,
                  248, 239, 231, 64, 196, 144, 219, 208, 90, 114, 174, 98, 109, 32, 66, 86, 53, 43, 111, 49, 89, 226,
                  234, 150, 106, 189, 155, 230, 233, 221, 232, 85, 142, 67, 86, 163, 154, 25, 160, 247, 43, 71, 60, 106,
                  98, 121, 173, 94, 143, 116, 125, 186, 90, 55, 58, 156, 181, 41, 239, 176, 242, 206, 114, 162, 77, 233,
                  205, 147, 112, 182, 230, 107, 125, 179, 150, 208, 201, 82, 65, 219, 36, 241, 173, 182, 71, 84, 212,
                  236, 70, 26, 88, 240, 239, 166, 32, 116, 132, 152, 167, 123, 50, 221, 109, 150, 196, 49, 225, 30, 164,
                  49, 194, 212, 74, 94, 194, 180, 96, 94, 154, 244, 121, 81, 236, 167, 170, 45, 48, 243, 45, 221, 162,
                  204, 212, 42, 147, 53, 71, 186, 57, 128, 160, 102, 116, 98, 234, 233, 70, 202, 136, 56, 122, 34, 174,
                  157, 166, 71, 242, 42, 207, 228, 160, 221, 134, 199, 101, 249, 55, 94, 94, 244, 192, 160, 239, 77, 29,
                  105, 104, 74, 219, 225, 69, 81, 31, 27, 237, 43, 106, 140, 175, 40, 88, 54, 142, 152, 104, 157, 182,
                  34, 207, 179, 210, 226, 215, 26, 250, 165, 238, 87, 156, 132, 148, 119, 44, 69, 174, 71, 113, 50, 168,
                  37, 86, 86, 247, 178, 230, 49, 193, 28, 168, 61, 196, 31, 109, 156, 227, 145, 114, 76, 43, 132, 171,
                  38, 39, 84, 27, 243, 121, 180, 210, 108, 80, 240, 159, 232, 162, 34, 214, 130, 173, 133, 131, 39, 44,
                  153, 220, 226, 94, 195, 154, 188, 180, 52, 160, 64, 201, 149, 220, 118, 33, 57, 133, 178, 129, 53, 44,
                  127, 123, 179, 87, 69, 73, 221, 53, 118, 27, 236, 53, 39, 247, 32, 194, 77, 82, 78, 142, 96, 207, 44,
                  149, 62, 35, 75, 243, 147, 54, 187, 194, 135, 162, 52, 120, 148, 48, 215, 66, 57, 51, 239, 47, 193,
                  246, 159, 239, 154, 230, 116, 26, 27, 49, 193, 171, 106, 56, 58, 208, 56, 148, 240, 191, 234, 208, 60,
                  180, 179, 112, 239, 33, 76, 136, 128, 77, 42, 159, 91, 201, 221, 82, 152, 132, 93, 25, 83, 195, 28,
                  30, 49, 199, 180, 196, 217, 95, 123, 128, 60, 221, 213, 244, 124, 146, 115, 64, 70, 70, 35, 204, 229,
                  92, 155, 96, 215, 112, 116, 214, 40, 174, 176, 117, 99, 157, 243, 246, 111, 104, 232, 159, 70, 137,
                  81, 240, 42, 162, 230, 91, 125, 54, 180, 70, 77, 158, 179, 61, 203, 112, 158, 116, 237, 240, 248, 177,
                  97, 133, 244, 195, 63, 122, 236, 178, 210, 61, 38, 224, 198, 61, 160, 41, 181, 159, 175, 72, 40, 223,
                  177, 191, 193, 176, 172, 81, 27, 68, 206, 177, 54, 85, 158, 231, 57, 160, 195, 73, 167, 202, 87, 69,
                  207, 93, 90, 228, 129, 37, 95, 226, 231, 179, 47, 145, 124, 110, 101, 87, 182, 242, 96, 240, 151, 96,
                  142, 70, 124, 231, 50, 226, 103, 126, 70, 164, 127, 246, 57, 85, 114, 52, 103, 151, 33, 177, 194, 168,
                  201, 197, 49, 99, 124, 145, 100, 222, 47, 107, 240, 174, 113, 41, 86, 218, 145, 181, 243, 170, 118,
                  57, 132, 127, 200, 140, 171, 93, 31, 47, 228, 245, 209, 98, 74, 231, 141, 173, 233, 67, 227, 194, 169,
                  89, 203, 154, 240, 192, 132, 229, 211, 181, 107, 142, 75, 74, 181, 112, 59, 207, 104, 169, 26, 169,
                  116, 154, 71, 173, 96, 186, 141, 162, 70, 79, 250, 231, 242, 235, 119, 105, 244, 175, 104, 164, 191,
                  46, 112, 187, 237, 123, 39, 74, 230, 144, 100, 249, 241, 117, 80, 108, 132, 126, 167, 236, 173, 184,
                  52, 62, 157, 205, 71, 95, 128, 129, 47, 210, 221, 123, 220, 171, 182, 119, 113, 73, 246, 142, 208, 92,
                  135, 221, 235, 107, 58, 127, 45, 79, 45, 213, 182, 160, 134, 222, 196, 248, 171, 63, 195, 40, 152, 71,
                  233, 79, 189, 101, 55, 146, 171, 86, 227, 198, 242, 243, 104, 150, 27, 67, 79, 31, 86, 125, 203, 200,
                  68, 187, 241, 108, 119, 239, 114, 200, 34, 245, 67, 199, 229, 87, 209, 115, 219, 207, 65, 73, 179,
                  234, 85, 215, 102, 126, 209, 229, 156, 61, 206, 195, 71, 107, 84, 179, 27, 149, 162, 95, 148, 216,
                  101, 58, 220, 132, 145, 199, 167, 71, 221, 123, 233, 198, 112, 105, 203, 205, 111, 152, 238, 220, 98,
                  67, 114, 88, 217, 139, 72, 156, 151, 101, 137, 210, 49, 168, 94, 62, 69, 209, 197, 144, 43, 211, 137,
                  127, 205, 156, 95, 125, 167, 246, 204, 85, 207, 229, 167, 214, 96, 220, 95, 207, 244, 189, 126, 134,
                  220, 59, 97, 35, 78, 99, 56, 191, 188, 208, 185, 140, 231, 117, 50, 121, 127, 112, 100, 111, 182, 46,
                  233, 51, 68, 144, 105, 245, 194, 85, 27, 125, 51, 247, 190, 247, 45, 61, 181, 115, 164, 71, 85, 166,
                  125, 38, 52, 208, 137, 27, 229, 250, 62, 228, 135, 146, 188, 49, 135, 145, 212, 29, 185, 201, 26, 68,
                  34, 151, 155, 106, 153, 186, 52, 119, 203, 144, 247, 163, 94, 200, 46, 166, 220, 102, 96, 25, 107,
                  138, 216, 91, 97, 203, 69, 201, 27, 153, 174, 244, 66, 115, 73, 132, 148, 244, 207, 144, 208, 122,
                  124, 200, 34, 184, 25, 174, 135, 207, 220, 54, 98, 181, 31, 53, 46, 179, 205, 234, 144, 105, 191, 73,
                  42, 136, 35, 58, 213, 28, 111, 247, 83, 142, 247, 51, 66, 178, 37, 199, 127, 146, 245, 131, 48, 106,
                  124, 242, 61, 39, 42, 60, 171, 100, 156, 238, 201, 195, 244, 40, 26, 57, 66, 168, 205, 108, 196, 46,
                  164, 78, 70, 123, 189, 69, 125, 147, 126, 76, 250, 115, 135, 148, 72, 122, 231, 196, 136, 73, 85, 60,
                  74, 130, 49, 246, 129, 39, 225, 82, 89, 108, 110, 202, 169, 172, 63, 238, 134, 186, 115, 211, 38, 219,
                  96, 76, 32, 68, 28, 28, 165, 231, 52, 199, 50, 91, 101, 181, 111, 69, 196, 54, 145, 110, 39, 247, 72,
                  109, 75, 215, 109, 168, 232, 43, 188, 162, 231, 68, 73, 161, 135, 76, 117, 234, 120, 105, 69, 137,
                  169, 153, 150, 138, 115, 105, 195, 123, 25, 43, 36, 74, 147, 229, 240, 186, 212, 81, 60, 232, 112, 88,
                  33, 100, 233, 153, 60, 130, 155, 114, 206, 151, 168, 27, 31, 179, 100, 130, 205, 180, 155, 117, 238,
                  208, 77, 212, 42, 203, 38, 192, 90, 168, 80, 134, 154, 199, 85, 62, 241, 131, 38, 34, 214, 94, 50,
                  235, 28, 83, 100, 96, 124, 46, 74, 185, 226, 47, 90, 233, 232, 49, 65, 235, 224, 92, 150, 91, 130,
                  191, 71, 124, 77, 183, 150, 80, 88, 114, 177, 89, 121, 196, 121, 63, 239, 80, 75, 52, 58, 35, 236,
                  233, 94, 82, 44, 222, 164, 203, 187, 217, 194, 102, 219, 65, 245, 219, 46, 57, 91, 223, 165, 136, 89,
                  208, 127, 125, 160, 40, 49, 182, 226, 37, 233, 203, 50, 25, 79, 151, 104, 50, 191, 182, 182, 121, 238,
                  117, 112, 87, 227, 159, 173, 86, 130, 32, 64, 133, 197, 211, 97, 220, 183, 191, 74, 143, 81, 102, 207,
                  155, 218, 194, 107, 166, 116, 115, 131, 179, 51, 140, 52, 115, 247, 119, 85, 132, 243, 54, 140, 216,
                  133, 211, 155, 248, 80, 41, 44, 162, 103, 189, 234, 168, 68, 201, 215, 215, 197, 27, 127, 45, 171, 41,
                  219, 220, 180, 147, 99, 219, 41, 122, 64, 241, 29, 158, 192, 77, 114, 128, 34, 186, 30, 139, 37, 227,
                  40, 146, 138, 137, 215, 60, 188, 165, 167, 83, 87, 100, 87, 194, 97, 201, 185, 157, 202, 59, 188, 227,
                  188, 52, 137, 178, 94, 52, 165, 73, 99, 98, 176, 151, 125, 243, 124, 101, 114, 45, 192, 206, 34, 175,
                  87, 208, 198, 220, 222, 96, 69, 141, 158, 232, 74, 228, 130, 84, 235, 172, 249, 161, 47, 119, 247,
                  195, 107, 191, 26, 70, 184, 144, 38, 240, 153, 49, 218, 207, 183, 154, 27, 108, 44, 248, 95, 46, 175,
                  178, 203, 100, 33, 156, 88, 245, 44, 154, 27, 237, 52, 144, 216, 63, 53, 74, 233, 102, 82, 176, 112,
                  139, 60, 156, 36, 101, 79, 216, 128, 149, 113, 52, 246, 169, 171, 37, 210, 170, 100, 103, 104, 69, 86,
                  189, 228, 88, 85, 230, 197, 73, 222, 185, 80, 37, 37, 118, 86, 247, 111, 46, 169, 134, 37, 210, 46,
                  68, 97, 58, 158, 106, 148, 214, 221, 116, 219, 110, 139, 74, 196, 186, 44, 176, 82, 133, 62, 86, 57,
                  211, 69, 74, 53, 94, 121, 124, 51, 203, 173, 210, 143, 191, 172, 28, 102, 162, 41, 74, 244, 224, 116,
                  185, 222, 217, 38, 91, 53, 32, 36, 93, 177, 142, 136, 60, 247, 202, 193, 196, 215, 186, 37, 75, 192,
                  122, 72, 76, 65, 93, 39, 27, 152, 63, 246, 210, 210, 214, 77, 228, 227, 210, 94, 83, 167, 235, 41,
                  224, 208, 102, 241, 144, 171, 228, 152, 113, 157, 227, 66, 239, 216, 62, 204, 166, 119, 143, 70, 231,
                  107, 25, 163, 242, 94, 57, 103, 69, 55, 211, 61, 42, 105, 237, 110, 111, 106, 83, 142, 153, 199, 144,
                  248, 187, 233, 36, 213, 140, 217, 26, 195, 181, 137, 47, 99, 29, 236, 194, 71, 84, 86, 55, 178, 108,
                  131, 102, 26, 149, 213, 124, 142, 35, 109, 46, 68, 50, 92, 239, 145, 89, 203, 166, 218, 83, 234, 230,
                  86, 185, 133, 218, 188, 49, 235, 136, 116, 162, 167, 85, 33, 198, 193, 64, 179, 63, 161, 233, 75, 177,
                  47, 90, 168, 209, 220, 34, 216, 85, 66, 95, 107, 95, 34, 209, 166, 51, 142, 188, 52, 183, 113, 28, 70,
                  177, 206, 93, 220, 213, 245, 52, 191, 120, 200, 114, 104, 31, 122, 248, 198, 66, 204, 248, 48, 142,
                  31, 250, 147, 116, 106, 212, 140, 184, 67, 185, 41, 73, 26, 115, 138, 250, 59, 178, 58, 228, 89, 133,
                  116, 42, 164, 101, 210, 160, 59, 81, 112, 234, 84, 210, 241, 245, 222, 237, 149, 144, 208, 61, 186,
                  33, 199, 157, 168, 115, 137, 249, 232, 209, 43, 69, 240, 230, 192, 31, 25, 106, 166, 220, 244, 155,
                  69, 122, 200, 116, 58, 93, 176, 167, 43, 111, 148, 179, 151, 37, 110, 149, 144, 167, 96, 180, 115,
                  125, 69, 174, 117, 237, 122, 83, 71, 108, 37, 135, 63, 45, 79, 26, 123, 173, 240, 177, 247, 95, 77,
                  235, 159, 89, 68, 244, 162, 48, 80, 230, 107, 74, 219, 38, 176, 184, 203, 99, 237, 242, 150, 39, 57,
                  89, 140, 167, 103, 60, 117, 45, 186, 216, 121, 216, 33, 153, 46, 218, 181, 219, 91, 225, 43, 184, 245,
                  248, 155, 116, 29, 149, 57, 34, 223, 248, 234, 96, 197, 233, 129, 84, 53, 96, 32, 140, 79, 230, 106,
                  229, 80, 166, 135, 117, 238, 108, 240, 222, 180, 136, 250, 151, 143, 88, 48, 211, 199, 135, 86, 151,
                  138, 42, 43, 204, 25, 168, 93, 231, 217, 113, 177, 155, 111, 41, 34, 235, 119, 213, 154, 221, 26, 108,
                  180, 91, 190, 226, 192, 237, 137, 116, 154, 180, 107, 89, 190, 215, 161, 96, 145, 135, 176, 87, 91,
                  49, 189, 28, 180, 64, 96, 89, 96, 250, 84, 110, 242, 207, 244, 196, 237, 79, 190, 72, 149, 158, 153,
                  84, 116, 148, 41, 134, 222, 27, 161, 163, 173, 196, 201, 187, 244, 33, 158, 123, 156, 35, 199, 175,
                  249, 64, 247, 220, 168, 114, 204, 37, 242, 33, 219, 250, 74, 117, 178, 144, 162, 245, 163, 136, 94,
                  30, 98, 34, 67, 149, 182, 214, 157, 34, 192, 182, 38, 103, 197, 135, 122, 44, 115, 228, 169, 118, 51,
                  120, 126, 186, 62, 157, 96, 195, 224, 145, 142, 199, 177, 239, 38, 225, 190, 192, 83, 151, 243, 78,
                  54, 167, 92, 233, 189, 101, 209, 136, 98, 61, 32, 130, 231, 112, 207, 202, 173, 132, 137, 48, 134,
                  159, 248, 143, 51, 119, 108, 230, 79, 59, 117, 180, 91, 222, 193, 61, 126, 250, 219, 203, 212, 86, 89,
                  94, 194, 61, 139, 95, 214, 90, 43, 126, 237, 109, 157, 27, 55, 51, 176, 119, 132, 188, 35, 56, 218,
                  238, 137, 229, 114, 238, 67, 62, 25, 249, 239, 243, 239, 61, 152, 45, 229, 121, 31, 75, 41, 139, 112,
                  92, 192, 49, 130, 68, 78, 217, 110, 181, 214, 199, 95, 89, 116, 189, 247, 184, 193, 206, 207, 202,
                  205, 55, 40, 140, 79, 148, 181, 31, 96, 153, 227, 160, 77, 144, 141, 249, 72, 42, 122, 129, 181, 199,
                  77, 160, 96, 64, 163, 150, 117, 118, 170, 82, 164, 249, 188, 39, 218, 149, 35, 37, 101, 158, 33, 52,
                  175, 40, 97, 203, 48, 190, 216, 164, 136, 160, 190, 121, 209, 116, 45, 245, 223, 116, 180, 114, 102,
                  107, 196, 183, 71, 161, 180, 149, 168, 56, 150, 31, 48, 149, 187, 201, 94, 169, 239, 144, 169, 239,
                  132, 154, 37, 168, 103, 213, 124, 149, 73, 79, 84, 205, 90, 49, 30, 126, 111, 205, 134, 98, 158, 163,
                  205, 166, 25, 97, 112, 51, 46, 111, 207, 168, 164, 248, 99, 95, 73, 246, 126, 165, 122, 61, 51, 197,
                  192, 174, 143, 131, 50, 172, 122, 119, 75, 231, 101, 219, 60, 122, 103, 94, 93, 233, 223, 115, 179,
                  92, 239, 143, 54, 133, 237, 236, 56, 236, 65, 143, 111, 53, 194, 245, 55, 101, 41, 143, 29, 132, 159,
                  187, 97, 87, 161, 128, 85, 217, 233, 72, 111, 32, 223, 89, 124, 36, 83, 188, 73, 103, 184, 212, 150,
                  182, 44, 145, 171, 211, 90, 173, 218, 97, 245, 154, 195, 133, 123, 136, 205, 47, 42, 161, 115, 235,
                  186, 119, 145, 72, 111, 225, 157, 201, 223, 44, 233, 181, 222, 215, 63, 118, 33, 101, 114, 119, 177,
                  198, 237, 110, 198, 220, 143, 76, 112, 207, 35, 95, 106, 179, 203, 210, 136, 84, 113, 71, 53, 155,
                  102, 182, 217, 227, 107, 236, 29, 162, 87, 191, 133, 245, 130, 97, 164, 76, 105, 207, 180, 169, 53,
                  185, 139, 180, 180, 159, 233, 141, 79, 229, 207, 85, 69, 187, 105, 74, 136, 47, 193, 93, 174, 115,
                  112, 174, 162, 180, 60, 203, 172, 245, 239, 91, 122, 68, 192, 198, 228, 139, 147, 40, 166, 152, 111,
                  33, 234, 188, 93, 246, 218, 229, 189, 139, 199, 211, 241, 157, 222, 210, 97, 110, 221, 41, 46, 191,
                  165, 44, 136, 78, 30, 183, 199, 145, 39, 48, 212, 211, 178, 112, 135, 243, 194, 231, 146, 58, 36, 113,
                  220, 198, 156, 32, 150, 102, 218, 164, 217, 220, 224, 176, 191, 110, 68, 204, 42, 214, 45, 134, 68,
                  60, 234, 178, 227, 210, 61, 46, 121, 144, 91, 139, 226, 227, 36, 173, 209, 149, 113, 238, 134, 140,
                  81, 69, 169, 235, 60, 208, 141, 208, 171, 97, 91, 61, 136, 178, 155, 169, 42, 68, 204, 157, 86, 27,
                  195, 136, 165, 25, 153, 75, 239, 227, 197, 161, 143, 199, 56, 117, 59, 53, 91, 59, 191, 81, 147, 178,
                  89, 30, 155, 59, 54, 68, 71, 52, 70, 90, 185, 37, 160, 74, 227, 240, 192, 141, 157, 27, 144, 103, 164,
                  99, 203, 213, 171, 239, 69, 33, 166, 103, 163, 243, 185, 60, 74, 125, 148, 217, 134, 156, 192, 166,
                  160, 232, 65, 213, 107, 178, 197, 187, 207, 178, 127, 38, 116, 182, 172, 198, 191, 183, 125, 210, 180,
                  196, 162, 82, 158, 125, 44, 132, 115, 175, 72, 174, 149, 110, 199, 130, 229, 61, 124, 51, 181, 59,
                  225, 143, 196, 91, 49, 225, 142, 148, 222, 142, 238, 166, 235, 53, 28, 139, 65, 42, 79, 131, 139, 250,
                  123, 107, 164, 137, 241, 182, 227, 59, 134, 238, 179, 145, 80, 62, 173, 205, 232, 102, 235, 167, 174,
                  182, 59, 199, 181, 175, 154, 114, 103, 70, 199, 184, 148, 204, 61, 213, 29, 89, 27, 52, 135, 175, 198,
                  111, 41, 37, 159, 51, 119, 71, 82, 204, 239, 152, 202, 228, 240, 217, 213, 146, 155, 220, 124, 55,
                  196, 80, 147, 57, 44, 200, 174, 228, 66, 55, 213, 215, 184, 136, 185, 144, 153, 37, 91, 69, 172, 80,
                  150, 246, 248, 223, 67, 110, 215, 69, 44, 153, 80, 159, 108, 230, 113, 240, 188, 55, 49, 52, 56, 66,
                  99, 93, 123, 244, 89, 233, 75, 231, 221, 92, 64, 140, 57, 48, 217, 171, 174, 84, 125, 91, 105, 147,
                  140, 227, 143, 217, 73, 124, 235, 49, 46, 152, 127, 36, 99, 165, 56, 212, 205, 221, 60, 104, 185, 157,
                  45, 240, 115, 102, 218, 175, 167, 133, 40, 69, 68, 219, 197, 46, 42, 243, 180, 145, 30, 89, 242, 249,
                  179, 112, 76, 204, 169, 125, 108, 135, 76, 26, 245, 57, 62, 144, 214, 173, 158, 34, 132, 174, 156,
                  117, 229, 88, 245, 173, 73, 100, 175, 244, 91, 157, 91, 184, 156, 193, 157, 188, 133, 227, 246, 42,
                  111, 236, 45, 110, 143, 136, 86, 203, 53, 120, 115, 183, 83, 179, 40, 78, 197, 178, 195, 249, 166, 67,
                  44, 165, 55, 238, 211, 226, 164, 189, 196, 140, 176, 173, 186, 202, 75, 76, 162, 184, 99, 206, 69,
                  114, 130, 49, 189, 234, 53, 148, 205, 108, 153, 159, 144, 98, 88, 100, 200, 52, 73, 151, 82, 235, 206,
                  45, 74, 72, 84, 177, 163, 130, 223, 69, 228, 93, 93, 133, 82, 89, 99, 120, 221, 73, 215, 88, 43, 193,
                  59, 52, 178, 102, 46, 155, 158, 211, 223, 33, 108, 148, 214, 74, 52, 140, 124, 135, 101, 233, 37, 201,
                  223, 151, 40, 204, 169, 27, 55, 248, 224, 30, 244, 95, 137, 167, 148, 165, 78, 237, 52, 164, 191, 176,
                  136, 125, 227, 167, 62, 164, 241, 217, 124, 105, 172, 219, 137, 190, 67, 136, 211, 50, 241, 99, 68,
                  145, 217, 205, 83, 142, 157, 61, 155, 65, 183, 50, 66, 53, 111, 162};
    const auto a_out = Solution().maximumLength(nums, 40);
    assert(a_out == 180);

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