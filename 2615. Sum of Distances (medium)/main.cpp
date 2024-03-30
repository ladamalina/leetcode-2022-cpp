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
    static vl distance(const vi& nums) {
        const auto n = CI(nums.size());
        std::unordered_map<int, vi> num_ids;
        FOR(i, 0, n-1) {
            num_ids[nums[i]].push_back(i);
        }
        vl res(n);
        for (const auto& [_, ids] : num_ids) {
            const auto ids_n = CI(ids.size());
            ll sum_bef = 0;
            ll sum_aft = std::accumulate(RNG(ids), 0ll);
            FOR(i, 0, ids_n-1) {
                const auto cnt_bef = i, cnt_aft = ids_n-1-i;
                sum_aft -= ids[i];
                res[ids[i]] = CL(ids[i])*cnt_bef - sum_bef + sum_aft - CL(ids[i])*cnt_aft;
                sum_bef += ids[i];
            }
        }
        return res;
    }
};

[[maybe_unused]] void TestSolution() {
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        const vi nums{1,3,1,1,2};
        const auto a_out = Solution::distance(nums);
        const vl e_out{5,0,3,4,0};
        assert(a_out == e_out);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        const vi nums{0,5,3};
        const auto a_out = Solution::distance(nums);
        const vl e_out{0,0,0};
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
