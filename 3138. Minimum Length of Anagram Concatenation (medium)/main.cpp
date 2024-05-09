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

template<typename T>
std::set<T> GetFactors(T x) {
    std::set<T> factors;
    const auto x_sqrt = std::sqrt(x);
    for (T i = 1; i <= x_sqrt; ++i) {
        if (x % i == 0) {
            factors.insert(i);
            factors.insert(x/i);
        }
    }
    return factors;
}

bool CheckLen(int len, int sn, const std::string& s) {
    std::array<int, 26> freq0{};
    FOR(i, 0, len-1) {
        ++freq0[s[i]-'a'];
    }
    const auto steps = sn / len;
    FOR(step, 1, steps-1) {
        std::array<int, 26> freq{};
        FOR(i, step*len, step*len+len-1) {
            ++freq[s[i]-'a'];
        }
        if (freq != freq0) return false;
    }
    return true;
}

class Solution {
    public:
    static int minAnagramLength(const std::string& s) {
        const auto sn = CI(s.size());
        const auto s_factors = GetFactors(sn);
        int min_len = sn;
        for (const auto len : s_factors) {
            if (len == sn) continue;
            if (CheckLen(len, sn, s)) min_len = std::min(min_len, len);
        }
        return min_len;
    }
};

[[maybe_unused]] void TestSolution() {
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        const std::string s("abba"s);
        const auto a_out = Solution::minAnagramLength(s);
        assert(a_out == 2);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        const std::string s("cdef"s);
        const auto a_out = Solution::minAnagramLength(s);
        assert(a_out == 4);

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
