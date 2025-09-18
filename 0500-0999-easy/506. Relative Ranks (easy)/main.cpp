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

const std::string S1 = "Gold Medal"s;
const std::string S2 = "Silver Medal"s;
const std::string S3 = "Bronze Medal"s;

class Solution {
    public:
    static vs findRelativeRanks(const vi& score) {
        const auto n = CI(score.size());
        vi ids(n);
        std::iota(RNG(ids), 0);
        std::sort(RNG(ids), [&](const int l, const int r) { return score[l] > score[r]; });
        vs res(n);
        FOR(i, 0, n-1) {
            if (i == 0) res[ids[i]] = S1;
            else if (i == 1) res[ids[i]] = S2;
            else if (i == 2) res[ids[i]] = S3;
            else res[ids[i]] = std::to_string(i+1);
        }
        return res;
    }
};

[[maybe_unused]] void TestSolution() {
    /*{
        const auto start_t = std::chrono::high_resolution_clock::now();

        vi people{1,2};
        const auto a_out = Solution::numRescueBoats(people, 3);
        assert(a_out == 1);

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
