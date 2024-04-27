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

constexpr int MAX_N = 1e5;
std::array<ll, MAX_N> psum;

class Solution {
    public:
    static vl minOperations(vi& nums, const vi& queries) {
        const auto n = CI(nums.size());
        SORT(nums);

        psum[0] = nums[0];
        FOR(i, 1, n-1) {
            psum[i] = psum[i-1]+nums[i];
        }

        const auto qn = CI(queries.size());
        vl res(qn);
        FOR(qi, 0, qn-1) {
            const auto it1 = std::lower_bound(RNG(nums), queries[qi]);
            const auto i1 = CI(it1 - nums.begin());
            const auto it2 = std::upper_bound(it1, nums.end(), queries[qi]);
            const auto i2 = CI(it2 - nums.begin());
            const auto cnt_bef = i1, cnt_aft = n-i2;
            const auto sum_bef = (i1==0) ? 0 : psum[i1-1];
            const auto sum_aft = i2-1>=0 ? (psum[n-1] - psum[i2-1]) : psum[n-1];
            res[qi] = CL(queries[qi])*cnt_bef - sum_bef + sum_aft - CL(queries[qi])*cnt_aft;
        }
        return res;
    }
};

[[maybe_unused]] void TestSolution() {
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        vi nums{3,1,6,8};
        const vi queries{1,5};
        const auto a_out = Solution::minOperations(nums, queries);
        const vl e_out{14,10};
        assert(a_out == e_out);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        vi nums{2,9,6,3};
        const vi queries{10};
        const auto a_out = Solution::minOperations(nums, queries);
        const vl e_out{20};
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
