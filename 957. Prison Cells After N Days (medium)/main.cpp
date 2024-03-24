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
    static vi prisonAfterNDays(const vi& cells, int n) {
        auto init_st = 0;
        FOR(b, 0, 7) {
            if (cells[b]) init_st |= (1<<b);
        }
        
        vi states{init_st};
        vi st_ids(256, -1);
        st_ids[init_st] = 0;
        auto head_id = -1;
        
        FOR(i, 1, 255) {
            const auto st = states.back();
            auto next_st = 0;
            FOR(b, 1, 6) {
                const auto l_occ = (st & (1<<(b-1)))!=0;
                const auto r_occ = (st & (1<<(b+1)))!=0;
                const auto both_occ = l_occ && r_occ;
                const auto both_vac = !l_occ && !r_occ;
                if (both_occ || both_vac)
                    next_st |= (1<<b);
            }
            if (st_ids[next_st] != -1) {
                head_id = st_ids[next_st];
                break;
            }
            st_ids[next_st] = CI(states.size());
            states.push_back(next_st);
        }

        int id;
        if (n < CI(states.size())) {
            id = n;
        } else if (head_id == 0) {
            const auto states_n = CI(states.size()) - head_id;
            n -= states_n-1;
            const auto n_mod = n % states_n;
            id = (n_mod==0) ? CI(states.size())-1 : n_mod-1;
        } else {
            n -= head_id-1;
            const auto states_n = CI(states.size()) - head_id;
            const auto n_mod = n % states_n;
            id = (n_mod==0) ? CI(states.size())-1 : head_id+n_mod-1;
        }

        vi res(8);
        FOR(b, 0, 7) {
            if (states[id] & (1<<b)) res[b] = 1;
        }
        return res;
    }
};

[[maybe_unused]] void TestSolution() {
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        const vi cells{0,1,0,1,1,0,0,1};
        const auto a_out = Solution::prisonAfterNDays(cells, 7);
        const vi e_out{0, 0, 1, 1, 0, 0, 0, 0};
        assert(a_out == e_out);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        const vi cells{1,0,0,1,0,0,1,0};
        const auto a_out = Solution::prisonAfterNDays(cells, 1000000000);
        const vi e_out{0,0,1,1,1,1,1,0};
        assert(a_out == e_out);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        const vi cells{0,1,1,0,1,0,1,0};
        const auto a_out = Solution::prisonAfterNDays(cells, 8);
        const vi e_out{0,1,1,1,1,0,0,0};
        assert(a_out == e_out);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        const vi cells{0,0,1,1,1,1,0,0};
        const auto a_out = Solution::prisonAfterNDays(cells, 8);
        const vi e_out{0,0,0,1,1,0,0,0};
        assert(a_out == e_out);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        const vi cells{1,1,0,1,1,0,1,1};
        const auto a_out = Solution::prisonAfterNDays(cells, 6);
        const vi e_out{0,0,1,0,0,1,0,0};
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
