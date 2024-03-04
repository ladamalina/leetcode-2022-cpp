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
  static int minRefuelStops(int target, int init_f, const vvi& stations) {
    if (init_f >= target) {
      return 0;
    }
    if (stations.empty()) {
      return init_f >= target ? 0 : -1;
    }

    const auto n = CI(stations.size());
    std::unordered_map<int, ll> dp{{0, init_f}};

    FOR(i, 0, n-1) {
      // i-th station – (i+1)th dp

      const auto i_dist = (i==0) ? stations[i][0] : (stations[i][0] - stations[i-1][0]);
      std::unordered_map<int, ll> dp2{};

      for (const auto& [prev_stops, prev_fuel] : dp) {
        if (prev_fuel >= i_dist) {
          // skip fuel
          auto it0 = dp2.find(prev_stops);
          if (it0 != dp2.end()) {
            it0->S = std::max(it0->S, prev_fuel-i_dist);
          } else {
            dp2[prev_stops] = prev_fuel-i_dist;
          }

          // take fuel
          auto it1 = dp2.find(prev_stops+1);
          if (it1 != dp2.end()) {
            it1->S = std::max(it1->S, prev_fuel-i_dist+stations[i][1]);
          } else {
            dp2[prev_stops+1] = prev_fuel-i_dist+stations[i][1];
          }
        }
      }
      dp = std::move(dp2);
    }

    int min_stops = INT_MAX;
    const auto target_dist = target - stations[n-1][0];
    for (const auto& [stops, fuel] : dp) {
      if (target_dist <= fuel) {
        min_stops = std::min(min_stops, stops);
      }
    }

    return (min_stops == INT_MAX) ? -1 : min_stops;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi stations{};
    const auto a_out = Solution::minRefuelStops(1, 1, stations);
    assert(a_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi stations{{10,100}};
    const auto a_out = Solution::minRefuelStops(100, 1, stations);
    assert(a_out == -1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi stations{{10,60},{20,30},{30,30},{60,40}};
    const auto a_out = Solution::minRefuelStops(100, 10, stations);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi stations{{5,82},{6,21},{7,97},{10,43},{12,93},{13,7},{15,77},{17,10},{18,17},{19,1},{23,41},{24,4},{25,16},{27,52},{29,57},{30,75},{35,94},{37,57},{39,45},{41,78},{43,74},{46,80},{47,8},{48,95},{51,79},{53,81},{54,38},{55,41},{57,2},{59,39},{64,37},{65,42},{69,35},{72,3},{75,84},{77,12},{78,24},{81,77},{85,53},{88,6},{89,10},{90,55},{91,76},{92,24},{95,58},{96,9},{98,15},{99,67},{100,42},{101,28},{103,60},{107,12},{108,23},{109,23},{112,93},{114,27},{115,2},{117,30},{118,48},{119,95},{122,41},{123,73},{127,6},{130,48},{131,31},{133,24},{135,67},{138,31},{139,77},{148,86},{149,58},{150,6},{154,8},{155,20},{158,78},{161,72},{163,64},{166,42},{168,77},{172,17},{175,26},{178,38},{179,31},{182,74},{183,86},{185,94},{186,43},{190,11},{191,56},{193,80},{194,6},{195,61},{196,56},{197,61},{198,16},{199,90},{200,7},{202,57},{203,81},{204,19},{205,19},{207,33},{210,60},{211,8},{212,87},{213,36},{215,82},{216,34},{217,60},{219,25},{221,35},{223,81},{224,40},{226,41},{228,49},{229,79},{230,58},{234,57},{235,54},{236,45},{237,48},{241,83},{242,25},{245,30},{246,26},{247,60},{248,71},{249,72},{250,45},{252,77},{253,94},{254,19},{256,90},{257,79},{259,81},{260,40},{261,52},{262,15},{264,79},{267,44},{268,54},{270,8},{273,32},{274,62},{275,87},{276,27},{280,69},{281,20},{282,39},{283,39},{285,54},{286,84},{291,21},{294,92},{295,79},{296,44},{303,79},{305,17},{306,67},{307,68},{308,77},{311,4},{312,26},{313,90},{320,37},{324,35},{325,44},{326,65},{327,92},{328,31},{330,78},{331,80},{334,53},{335,66},{336,64},{337,5},{338,79},{340,60},{342,30},{343,77},{345,94},{346,21},{348,58},{349,58},{350,40},{351,27},{353,34},{357,92},{359,8},{362,45},{365,82},{366,14},{367,51},{368,57},{369,93},{372,76},{373,44},{375,76},{377,92},{379,52},{380,41},{382,44},{383,69},{384,70},{385,17},{386,56},{387,26},{388,48},{391,85},{395,4},{397,57},{399,75},{400,70},{401,5},{402,57},{403,86},{405,45},{406,59},{409,38},{411,72},{413,68},{416,2},{417,72},{419,9},{420,34},{424,42},{425,95},{426,14},{427,1},{428,45},{429,85},{430,97},{431,94},{433,14},{434,67},{435,78},{436,72},{439,48},{443,49},{444,9},{445,6},{447,67},{448,25},{449,15},{452,85},{453,66},{454,28},{455,30},{458,25},{461,95},{463,89},{464,49},{465,40},{466,28},{467,31},{468,22},{472,47},{475,49},{478,52},{480,26},{481,60},{483,5},{484,60},{485,28},{487,54},{488,33},{494,6},{495,67},{496,50},{500,7},{501,89},{503,87},{506,14},{508,95},{511,35},{512,55},{514,11},{515,93},{516,60},{517,75},{521,17},{522,11},{524,50},{527,3},{529,83},{538,89},{540,93},{542,60},{543,12},{544,66},{550,44},{551,86},{552,87},{554,18},{556,63},{557,9},{563,38},{564,48},{566,84},{567,47},{569,4},{571,89},{572,56},{573,86},{579,26},{581,78},{584,24},{585,68},{587,91},{588,48},{589,19},{590,18},{591,28},{594,87},{596,3},{606,91},{610,22},{613,62},{618,97},{619,62},{620,83},{621,34},{622,17},{624,49},{626,16},{627,5},{628,35},{630,50},{631,44},{634,19},{635,3},{637,18},{640,83},{641,38},{642,28},{647,78},{648,30},{650,68},{651,7},{653,5},{655,86},{658,3},{659,39},{660,3},{661,59},{664,82},{666,30},{667,72},{670,90},{671,29},{672,57},{677,69},{678,61},{679,26},{684,6},{685,1},{686,2},{687,49},{692,91},{693,64},{695,96},{699,33},{702,87},{706,95},{713,9},{714,32},{716,37},{721,61},{723,39},{724,85},{725,58},{730,60},{733,96},{734,8},{735,78},{738,53},{741,30},{742,81},{743,69},{744,17},{745,47},{747,71},{748,30},{750,1},{752,25},{753,44},{754,19},{756,22},{757,71},{759,54},{761,17},{767,46},{768,55},{773,55},{774,30},{776,9},{777,35},{778,65},{781,76},{785,14},{786,71},{787,62},{789,26},{790,85},{799,76},{802,24},{805,34},{806,13},{808,60},{809,53},{810,97},{812,76},{815,24},{821,20},{824,87},{826,45},{827,85},{829,29},{830,3},{832,10},{833,41},{836,29},{837,4},{838,97},{839,89},{842,27},{846,30},{847,20},{849,57},{850,60},{853,50},{854,28},{856,74},{859,87},{860,51},{861,27},{865,94},{866,23},{867,15},{869,49},{870,10},{871,69},{874,57},{878,88},{879,63},{883,62},{884,70},{885,91},{886,34},{889,36},{892,56},{894,63},{895,38},{897,8},{900,97},{901,86},{902,1},{904,19},{905,83},{906,11},{908,45},{909,79},{911,5},{913,4},{919,44},{921,92},{922,32},{923,86},{924,76},{928,38},{930,36},{933,6},{937,18},{942,6},{943,86},{945,91},{947,12},{952,46},{954,59},{956,61},{960,84},{962,59},{964,32},{966,86},{967,67},{968,15},{969,75},{973,40},{974,44},{976,72},{979,92},{980,25},{981,91},{983,97},{984,92},{986,34},{988,90},{989,12},{990,23},{992,88}};
    const auto a_out = Solution::minRefuelStops(1000, 97, stations);
    assert(a_out == 10);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
