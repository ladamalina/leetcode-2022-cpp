// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

[[maybe_unused]] constexpr ll MOD = 1e9 + 7;

class Solution {
public:
  int countPaths(const int n, const vvi& edges) {
    std::vector<vii> g1(n);
    for (const auto& e : edges) {
      g1[e[0]].emplace_back(e[1], e[2]);
      g1[e[1]].emplace_back(e[0], e[2]);
    }

    vvi g2(n);
    {
      vl dist(n, LLONG_MAX);
      std::priority_queue<std::pair<ll,ii>, std::vector<std::pair<ll,ii>>, std::greater<>> pq; // <dist, <v, parent>>
      pq.emplace(0, ii{0, -1});
      while (!pq.empty()) {
        const auto d = pq.top().F;
        const auto [v, p] = pq.top().S;
        pq.pop();
        if (d > dist[v]) continue;
        if (p != -1) g2[p].emplace_back(v);
        if (d == dist[v]) continue;
        dist[v] = d;
        for (const auto& [u, w] : g1[v]) {
          if (d + w <= dist[u]) {
            pq.emplace(d + w, ii{u, v});
          }
        }
      }
    }

    vl dp(n, -1);
    dp[n-1] = 1;
    const std::function<ll(int)> dfs = [&](const int v) {
      if (dp[v] != -1)
        return dp[v];
      dp[v] = 0;
      for (const auto u : g2[v]) {
        dp[v] = (dp[v] + dfs(u)) % MOD;
      }
      return dp[v];
    };
    const auto res = dfs(0);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const int n = 7;
    const vvi edges{{0, 6, 7}, {0, 1, 2}, {1, 2, 3}, {1, 3, 3}, {6, 3, 3}, {3, 5, 1}, {6, 5, 1}, {2, 5, 1}, {0, 4, 5},
                    {4, 6, 2}};
    const auto a_out = Solution().countPaths(n, edges);
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const int n = 2;
    const vvi edges{{1, 0, 10}};
    const auto a_out = Solution().countPaths(n, edges);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const int n = 18;
    const vvi edges{{0, 1, 3972}, {2, 1, 1762}, {3, 1, 4374}, {0, 3, 8346}, {3, 2, 2612}, {4, 0, 6786}, {5, 4, 1420},
                    {2, 6, 7459}, {1, 6, 9221}, {6, 3, 4847}, {5, 6, 4987}, {7, 0, 14609}, {7, 1, 10637}, {2, 7, 8875},
                    {7, 6, 1416}, {7, 5, 6403}, {7, 3, 6263}, {4, 7, 7823}, {5, 8, 10184}, {8, 1, 14418}, {8, 4, 11604},
                    {7, 8, 3781}, {8, 2, 12656}, {8, 0, 18390}, {5, 9, 15094}, {7, 9, 8691}, {9, 6, 10107},
                    {9, 1, 19328}, {9, 4, 16514}, {9, 2, 17566}, {9, 0, 23300}, {8, 9, 4910}, {9, 3, 14954},
                    {4, 10, 26060}, {2, 10, 27112}, {10, 1, 28874}, {8, 10, 14456}, {3, 10, 24500}, {5, 10, 24640},
                    {10, 6, 19653}, {10, 0, 32846}, {10, 9, 9546}, {10, 7, 18237}, {11, 7, 21726}, {11, 2, 30601},
                    {4, 11, 29549}, {11, 0, 36335}, {10, 11, 3489}, {6, 11, 23142}, {3, 11, 27989}, {11, 1, 32363},
                    {11, 8, 17945}, {9, 11, 13035}, {5, 11, 28129}, {2, 12, 33902}, {5, 12, 31430}, {6, 12, 26443},
                    {4, 12, 32850}, {12, 3, 31290}, {11, 12, 3301}, {12, 1, 35664}, {7, 13, 28087}, {13, 8, 24306},
                    {6, 13, 29503}, {11, 13, 6361}, {4, 13, 35910}, {13, 12, 3060}, {3, 13, 34350}, {13, 5, 34490},
                    {13, 2, 36962}, {10, 13, 9850}, {9, 13, 19396}, {12, 14, 8882}, {8, 14, 30128}, {14, 6, 35325},
                    {14, 5, 40312}, {1, 14, 44546}, {11, 14, 12183}, {15, 12, 13581}, {2, 15, 47483}, {4, 15, 46431},
                    {15, 10, 20371}, {15, 14, 4699}, {15, 6, 40024}, {15, 7, 38608}, {1, 15, 49245}, {11, 15, 16882},
                    {8, 15, 34827}, {0, 15, 53217}, {5, 15, 45011}, {15, 3, 44871}, {16, 2, 53419}, {16, 9, 35853},
                    {1, 16, 55181}, {16, 7, 44544}, {8, 16, 40763}, {0, 16, 59153}, {15, 16, 5936}, {16, 10, 26307},
                    {16, 6, 45960}, {12, 16, 19517}, {17, 2, 57606}, {17, 3, 54994}, {17, 14, 14822}, {17, 11, 27005},
                    {0, 17, 63340}, {17, 7, 48731}, {8, 17, 44950}, {17, 16, 4187}, {5, 17, 55134}, {17, 10, 30494},
                    {17, 9, 40040}, {17, 12, 23704}, {13, 17, 20644}, {17, 1, 59368}};
    const auto a_out = Solution().countPaths(n, edges);
    assert(a_out == 2891);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const int n = 39;
    const vvi edges{{0, 1, 5624}, {1, 2, 3696}, {2, 0, 9320}, {0, 3, 6879}, {4, 2, 1828}, {4, 5, 1621}, {6, 1, 9555},
                    {6, 3, 8300}, {6, 5, 2410}, {3, 7, 1420}, {0, 7, 8299}, {8, 5, 4954}, {0, 8, 17723}, {9, 5, 10995},
                    {2, 9, 14444}, {9, 0, 23764}, {4, 9, 12616}, {7, 9, 15465}, {8, 9, 6041}, {9, 3, 16885},
                    {9, 6, 8585}, {10, 6, 10219}, {5, 10, 12629}, {10, 8, 7675}, {0, 10, 25398}, {10, 1, 19774},
                    {10, 9, 1634}, {4, 10, 14250}, {10, 2, 16078}, {11, 0, 21192}, {8, 11, 3469}, {11, 7, 12893},
                    {11, 4, 10044}, {5, 11, 8423}, {12, 11, 6276}, {0, 12, 27468}, {5, 12, 14699}, {3, 12, 20589},
                    {1, 12, 21844}, {12, 9, 3704}, {12, 7, 19169}, {10, 12, 2070}, {2, 12, 18148}, {12, 6, 12289},
                    {13, 9, 238}, {2, 13, 14682}, {13, 7, 15703}, {2, 14, 14739}, {14, 0, 24059}, {9, 14, 295},
                    {11, 15, 10845}, {15, 5, 19268}, {15, 1, 26413}, {15, 7, 23738}, {14, 15, 7978}, {12, 15, 4569},
                    {15, 2, 22717}, {4, 15, 20889}, {15, 3, 25158}, {16, 13, 6248}, {5, 16, 17481}, {2, 16, 20930},
                    {16, 10, 4852}, {16, 7, 21951}, {14, 16, 6191}, {9, 16, 6486}, {16, 8, 12527}, {3, 16, 23371},
                    {17, 16, 4801}, {15, 17, 3014}, {9, 17, 11287}, {4, 17, 23903}, {18, 4, 30273}, {18, 16, 11171},
                    {18, 3, 34542}, {18, 12, 13953}, {17, 18, 6370}, {18, 13, 17419}, {0, 18, 41421}, {14, 18, 17362},
                    {18, 7, 33122}, {18, 9, 17657}, {1, 18, 35797}, {18, 5, 28652}, {18, 15, 9384}, {18, 11, 20229},
                    {18, 10, 16023}, {19, 2, 34046}, {19, 15, 11329}, {19, 9, 19602}, {18, 19, 1945}, {7, 19, 35067},
                    {19, 16, 13116}, {19, 10, 17968}, {19, 17, 8315}, {19, 4, 32218}, {19, 6, 28187}, {13, 19, 19364},
                    {19, 12, 15898}, {19, 3, 36487}, {5, 19, 30597}, {1, 19, 37742}, {0, 19, 43366}, {19, 14, 19307},
                    {8, 20, 33184}, {13, 20, 26905}, {20, 4, 39759}, {20, 18, 9486}, {6, 20, 35728}, {7, 20, 42608},
                    {2, 20, 41587}, {15, 20, 18870}, {20, 14, 26848}, {20, 1, 45283}, {21, 1, 50904}, {5, 21, 43759},
                    {3, 21, 49649}, {21, 16, 26278}, {17, 21, 21477}, {21, 9, 32764}, {20, 21, 5621}, {21, 19, 13162},
                    {21, 2, 47208}, {21, 8, 38805}, {15, 21, 24491}, {10, 21, 31130}, {13, 21, 32526}, {22, 14, 5348},
                    {22, 6, 14228}, {7, 22, 21108}, {22, 8, 11684}, {22, 11, 8215}, {0, 22, 29407}, {23, 12, 31705},
                    {23, 7, 50874}, {17, 23, 24122}, {2, 23, 49853}, {23, 6, 43994}, {23, 21, 2645}, {0, 23, 59173},
                    {15, 23, 27136}, {19, 23, 15807}, {23, 5, 46404}, {23, 11, 37981}, {24, 1, 56336}, {20, 24, 11053},
                    {13, 24, 37958}, {24, 6, 46781}, {5, 24, 49191}, {24, 7, 53661}, {24, 23, 2787}, {24, 17, 26909},
                    {10, 24, 36562}, {24, 15, 29923}, {22, 24, 32553}, {8, 24, 44237}, {24, 21, 5432}, {24, 14, 37901},
                    {12, 24, 34492}, {19, 24, 18594}, {18, 24, 20539}, {24, 9, 38196}, {2, 24, 52640}, {25, 23, 2951},
                    {25, 14, 38065}, {26, 16, 35855}, {23, 26, 6932}, {2, 26, 56785}, {17, 26, 31054}, {1, 26, 60481},
                    {27, 17, 32188}, {5, 27, 54470}, {26, 27, 1134}, {27, 1, 61615}, {27, 7, 58940}, {27, 25, 5115},
                    {27, 12, 39771}, {27, 21, 10711}, {20, 27, 16332}, {27, 14, 43180}, {22, 27, 37832}, {4, 27, 56091},
                    {8, 27, 49516}, {8, 28, 56382}, {28, 5, 61336}, {24, 28, 12145}, {2, 28, 64785}, {28, 26, 8000},
                    {4, 28, 62957}, {15, 28, 42068}, {28, 27, 6866}, {23, 28, 14932}, {10, 28, 48707}, {28, 17, 39054},
                    {8, 29, 57371}, {29, 15, 43057}, {19, 29, 31728}, {29, 22, 45687}, {6, 29, 59915}, {28, 29, 989},
                    {25, 29, 12970}, {10, 29, 49696}, {29, 13, 51092}, {18, 29, 33673}, {29, 7, 66795}, {29, 5, 62325},
                    {11, 29, 53902}, {12, 29, 47626}, {21, 29, 18566}, {26, 29, 8989}, {14, 29, 51035}, {29, 0, 75094},
                    {29, 2, 65774}, {29, 3, 68215}, {17, 29, 40043}, {27, 29, 7855}, {29, 23, 15921}, {9, 29, 51330},
                    {1, 29, 69470}, {28, 30, 8489}, {18, 31, 42782}, {23, 31, 25030}, {3, 31, 77324}, {31, 19, 40837},
                    {14, 31, 60144}, {30, 31, 1609}, {29, 31, 9109}, {4, 32, 56100}, {32, 26, 1143}, {32, 24, 5288},
                    {32, 20, 16341}, {8, 32, 49525}, {32, 0, 67248}, {2, 32, 57928}, {12, 32, 39780}, {21, 32, 10720},
                    {32, 15, 35211}, {32, 27, 9}, {32, 5, 54479}, {32, 7, 58949}, {14, 33, 6618}, {4, 33, 19529},
                    {34, 17, 46645}, {34, 16, 51446}, {23, 34, 22523}, {34, 27, 14457}, {24, 34, 19736}, {34, 2, 72376},
                    {34, 10, 56298}, {34, 12, 54228}, {34, 21, 25168}, {29, 34, 6602}, {28, 35, 11281}, {23, 35, 26213},
                    {25, 35, 23262}, {35, 6, 70207}, {13, 35, 61384}, {35, 34, 3690}, {4, 35, 74238}, {16, 35, 55136},
                    {27, 35, 18147}, {35, 3, 78507}, {35, 5, 72617}, {14, 35, 61327}, {35, 30, 2792}, {29, 35, 10292},
                    {35, 2, 76066}, {35, 8, 67663}, {35, 12, 57918}, {32, 35, 18138}, {35, 10, 59988}, {35, 0, 85386},
                    {17, 35, 50335}, {35, 24, 23426}, {36, 20, 37171}, {8, 36, 70355}, {36, 29, 12984}, {11, 36, 66886},
                    {36, 13, 64076}, {36, 14, 64019}, {21, 36, 31550}, {32, 36, 20830}, {36, 16, 57828}, {34, 36, 6382},
                    {22, 36, 58671}, {27, 36, 20839}, {36, 17, 53027}, {36, 1, 82454}, {36, 4, 76930}, {36, 18, 46657},
                    {30, 36, 5484}, {23, 36, 28905}, {36, 3, 81199}, {35, 36, 2692}, {33, 36, 57401}, {36, 37, 6780},
                    {30, 37, 12264}, {37, 25, 32734}, {32, 37, 27610}, {37, 1, 89234}, {37, 7, 86559}, {10, 37, 69460},
                    {22, 37, 65451}, {12, 37, 67390}, {37, 34, 13162}, {15, 37, 62821}, {38, 35, 6626}, {38, 2, 82692},
                    {38, 27, 24773}, {23, 38, 32839}, {30, 38, 9418}, {38, 8, 74289}, {10, 38, 66614}, {16, 38, 61762},
                    {38, 29, 16918}, {38, 31, 7809}, {38, 1, 86388}, {38, 19, 48646}, {4, 38, 80864}, {18, 38, 50591},
                    {13, 38, 68010}, {34, 38, 10316}, {38, 33, 61335}};
    const auto a_out = Solution().countPaths(n, edges);
    assert(a_out == 585596);

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