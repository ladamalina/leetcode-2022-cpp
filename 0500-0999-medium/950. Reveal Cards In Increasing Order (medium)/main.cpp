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
    static vi deckRevealedIncreasing(vi& deck) {
        const auto n = CI(deck.size());
        SORT(deck);
        vi res(n), ids(n);
        std::iota(RNG(ids), 0);
        auto i = 0, deck_i = 0;
        while (!ids.empty()) {
            const auto m = CI(ids.size());
            if (m == 1) {
                res[ids[0]] = deck[deck_i];
                break;
            }
            vi ids2;
            while (i < m) {
                res[ids[i]] = deck[deck_i];
                if (i > 0) ids2.push_back(ids[i-1]);
                if (i == m-2) ids2.push_back(ids[i+1]);
                i += 2;
                ++deck_i;
            }
            ids = std::move(ids2);
            i = (i-2==m-1) ? 1 : 0;
        }
        return res;
    }
};

[[maybe_unused]] void TestSolution() {
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        vi deck{17,13,11,2,3,5,7};
        const auto a_out = Solution::deckRevealedIncreasing(deck);
        const vi e_out{2,13,3,11,5,17,7};
        assert(a_out == e_out);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        vi deck{1,1000};
        const auto a_out = Solution::deckRevealedIncreasing(deck);
        const vi e_out{1,1000};
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
