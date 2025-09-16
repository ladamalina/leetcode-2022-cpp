//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

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

class Solution {
 public:
  int candy(const vi& ratings) {
    const auto n = SZ(ratings);
    vi candies(n, 1);
    std::priority_queue<ii, vii, std::greater<>> pq;
    
    FOR(i, 0, n-1) pq.emplace(ratings[i], i);
    while (!pq.empty()) {
      const auto [r, i] = pq.top();
      pq.pop();
      if (i-1 >= 0 && ratings[i-1] < ratings[i]) {
        candies[i] = std::max(candies[i], candies[i-1] + 1);
      }
      if (i+1 < n && ratings[i] > ratings[i+1]) {
        candies[i] = std::max(candies[i], candies[i+1] + 1);
      }
    }
    const auto res = std::accumulate(RNG(candies), 0);
    return res;
  }
};

int main() {
  {
    std::vector<int> ratings{1,0,2};
    int e_out = 5;
    auto a_out = Solution().candy(ratings);
    assert(a_out == e_out);
  }
  {
    std::vector<int> ratings{1,2,2};
    int e_out = 4;
    auto a_out = Solution().candy(ratings);
    assert(a_out == e_out);
  }
}
