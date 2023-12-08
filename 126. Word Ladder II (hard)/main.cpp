//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<ld>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define F first
#define S second
#define PB push_back

class Solution {
  public:
  static std::vector<std::vector<std::string>> findLadders(const std::string& begin_w, const std::string& end_w,
      const std::vector<std::string>& w_list) {
    const auto n = CI(w_list.size());
    
    std::unordered_map<std::string_view, int> w_to_i;
    FOR(i, 0, n-1) {
      w_to_i[w_list[i]] = i;
    }
    if (!w_to_i.contains(end_w)) {
      return {};
    } // w_to_i.contains(end_w)
    const auto end_w_id = w_to_i.at(end_w);
    
    vi dist(n, INT_MAX);
    vvi prev_ids(n);
    std::priority_queue<ii, std::vector<ii>, std::greater<>> q; // <dist, i>
    const auto begin_w_it = w_to_i.find(begin_w);
    if (begin_w_it != w_to_i.end()) {
      dist[begin_w_it->S] = 0;
      q.emplace(0, begin_w_it->S);
    } else {
      q.emplace(0, -1);
    }

    while (!q.empty()) {
      const auto [v_dist, v_id] = q.top();
      q.pop();
      if (v_id != -1 && v_dist > dist[v_id]) {
        continue;
      }
      auto u_word = (v_id == -1) ? begin_w : w_list[v_id];
      FOR(j, 0, CI(u_word.size())-1) {
        const auto orig_ch = u_word[j];
        auto& upd_ch = u_word[j];
        upd_ch = 'a';
        while (upd_ch <= 'z') {
          if (upd_ch != orig_ch) {
            const auto u_it = w_to_i.find(u_word);
            if (u_it != w_to_i.end()) {
              if (v_dist+1 < dist[u_it->S]) {
                dist[u_it->S] = v_dist+1;
                prev_ids[u_it->S] = {v_id};
                q.emplace(dist[u_it->S], u_it->S);
              } else if (v_dist+1 == dist[u_it->S]) {
                prev_ids[u_it->S].PB(v_id);
              }
            }
          }
          ++upd_ch;
        }
        upd_ch = orig_ch;
      }
    }
    
    if (dist[end_w_id] == INT_MAX) {
      return {};
    }
    std::vector<std::vector<std::string>> res;
    std::deque<std::string_view> curr_res;
    std::function<void(int)> dfs = [&](int v_id) {
      if (v_id == -1) {
        curr_res.push_front(begin_w);
        res.emplace_back(RNG(curr_res));
        curr_res.pop_front();
        return;
      }
      curr_res.push_front(w_list[v_id]);
      if (!prev_ids[v_id].empty()) {
        for (const auto u_id : prev_ids[v_id]) {
          dfs(u_id);
        }
      } else {
        res.emplace_back(RNG(curr_res));
      }
      curr_res.pop_front();
    };
    dfs(end_w_id);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string beginWord{"hit"};
    const std::string endWord{"cog"};
    const std::vector<std::string> wordList{"hot","dot","dog","lot","log","cog"};
    const std::vector<std::vector<std::string>> e_out{{"hit","hot","dot","dog","cog"},{"hit","hot","lot","log","cog"}};
    const auto a_out = Solution::findLadders(beginWord, endWord, wordList);
    assert(a_out == e_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string beginWord{"hit"};
    const std::string endWord{"cog"};
    const std::vector<std::string> wordList{"hot","dot","dog","lot","log"};
    const std::vector<std::vector<std::string>> e_out;
    const auto a_out = Solution::findLadders(beginWord, endWord, wordList);
    assert(a_out == e_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string beginWord{"a"};
    const std::string endWord{"c"};
    const std::vector<std::string> wordList{"a","b","c"};
    const std::vector<std::vector<std::string>> e_out{{"a","c"}};
    const auto a_out = Solution::findLadders(beginWord, endWord, wordList);
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
