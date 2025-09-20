#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

class Solution {
    public:
    static vi kthSmallestPrimeFraction(const vi& arr, int k) {
        const auto n = CI(arr.size());
        vii a;
        a.reserve((n*(n-1)/2));
        FOR(i, 0, n-2) {
            FOR(j, i+1, n-1) {
                a.emplace_back(arr[i], arr[j]);
            }
        }
        const auto cmp = [](const ii& l, const ii& r) {
            return (l.S == r.S) ? l.F < r.F : l.F*r.S < r.F*l.S;
        };
        std::sort(RNG(a), cmp);
        return {a[k-1].F, a[k-1].S};
    }
};

[[maybe_unused]] void TestSolution() {
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        const vi arr{1,2,3,5};
        const auto a_out = Solution::kthSmallestPrimeFraction(arr, 3);
        const vi e_out{2,5};
        assert(a_out == e_out);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        const vi arr{1,7};
        const auto a_out = Solution::kthSmallestPrimeFraction(arr, 1);
        const vi e_out{1,7};
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
