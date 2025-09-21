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
    static bool canChange(const std::string& s, const std::string& t) {
        const auto s_cnt_l = std::count(s.begin(), s.end(), 'L');
        const auto t_cnt_l = std::count(t.begin(), t.end(), 'L');
        if (s_cnt_l != t_cnt_l) return false;

        const auto s_cnt_r = std::count(s.begin(), s.end(), 'R');
        const auto t_cnt_r = std::count(t.begin(), t.end(), 'R');
        if (s_cnt_r != t_cnt_r) return false;

        const auto s_cnt_x = std::count(s.begin(), s.end(), '_');
        const auto t_cnt_x = std::count(t.begin(), t.end(), '_');
        if (s_cnt_x != t_cnt_x) return false;

        std::vector<int> s_l_bef(s.size()), s_r_bef(s.size()), s_x_bef(s.size());
        int s_cnt_l_bef = 0, s_cnt_r_bef = 0, s_cnt_x_bef = 0;
        for (auto i=0; i<s.size(); ++i) {
            if (s[i]=='L') ++s_cnt_l_bef;
            else if (s[i]=='R') ++s_cnt_r_bef;
            else ++s_cnt_x_bef;
            s_l_bef[i] = s_cnt_l_bef;
            s_r_bef[i] = s_cnt_r_bef;
            s_x_bef[i] = s_cnt_x_bef;
        }

        std::vector<int> t_l_bef(t.size()), t_r_bef(t.size()), t_x_bef(t.size());
        int t_cnt_l_bef = 0, t_cnt_r_bef = 0, t_cnt_x_bef = 0;
        for (auto i=0; i<t.size(); ++i) {
            if (t[i]=='L') ++t_cnt_l_bef;
            else if (t[i]=='R') ++t_cnt_r_bef;
            else ++t_cnt_x_bef;
            t_l_bef[i] = t_cnt_l_bef;
            t_r_bef[i] = t_cnt_r_bef;
            t_x_bef[i] = t_cnt_x_bef;
        }

        { // check L's
            auto s_it = std::find(s.begin(), s.end(), 'L');
            auto t_it = std::find(t.begin(), t.end(), 'L');
            while (s_it < s.end() && t_it < t.end()) {
                const auto si = s_it - s.begin();
                const auto ti = t_it - t.begin();
                if (s_x_bef[si] < t_x_bef[ti]) return false;
                if (s_r_bef[si] != t_r_bef[ti]) return false;
                s_it = std::find(s_it+1, s.end(), 'L');
                t_it = std::find(t_it+1, t.end(), 'L');
            }
        }

        { // check R's
            auto s_it = std::find(s.begin(), s.end(), 'R');
            auto t_it = std::find(t.begin(), t.end(), 'R');
            while (s_it < s.end() && t_it < t.end()) {
                const auto si = s_it - s.begin();
                const auto ti = t_it - t.begin();
                if (s_x_bef[si] > t_x_bef[ti]) return false;
                if (s_l_bef[si] != t_l_bef[ti]) return false;
                s_it = std::find(s_it+1, s.end(), 'R');
                t_it = std::find(t_it+1, t.end(), 'R');
            }
        }
        
        return true;
    }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{1,2,3},{4,5,6},{7,8,9}};
    const auto a_out = Solution::minFallingPathSum(grid);
    assert(a_out == 13);

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
