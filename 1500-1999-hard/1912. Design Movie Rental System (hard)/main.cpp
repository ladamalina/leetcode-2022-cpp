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
using ld = long double;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

[[maybe_unused]] constexpr int MAX_N = 3 * 1e5;
std::array<std::unordered_map<int, int>, MAX_N> shop_movie_price;

class MovieRentingSystem {
public:
  MovieRentingSystem(const int n, const vvi& entries) {
    std::fill(shop_movie_price.begin(), shop_movie_price.begin() + n, std::unordered_map<int, int>{});
    for (const auto& e : entries) {
      const auto shop = e[0], movie = e[1], price = e[2];
      shop_movie_price[shop][movie] = price;
      unrented_movie_price_shop[movie].emplace(price, shop);
    }
  }

  [[nodiscard]] vi search(const int movie) const {
    const auto movie_it = unrented_movie_price_shop.find(movie);
    if (movie_it == unrented_movie_price_shop.end())
      return {};
    vi res;
    auto price_shop_it = movie_it->S.begin();
    while (SZ(res) < 5 && price_shop_it != movie_it->S.end()) {
      res.push_back(price_shop_it->S);
      ++price_shop_it;
    }
    return res;
  }

  void rent(const int shop, const int movie) {
    const auto price = shop_movie_price[shop][movie];
    unrented_movie_price_shop[movie].erase({price, shop});
    rented_price_shop_movie.emplace(price, ii{shop, movie});
  }

  void drop(int shop, int movie) {
    const auto price = shop_movie_price[shop][movie];
    rented_price_shop_movie.erase({price, ii{shop, movie}});
    unrented_movie_price_shop[movie].emplace(price, shop);
  }

  [[nodiscard]] vvi report() const {
    vvi res;
    auto it = rented_price_shop_movie.begin();
    while (SZ(res) < 5 && it != rented_price_shop_movie.end()) {
      res.push_back({it->S.F, it->S.S});
      ++it;
    }
    return res;
  }

private:
  std::unordered_map<int, std::set<ii>> unrented_movie_price_shop;
  std::set<std::pair<int, ii>> rented_price_shop_movie;
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi entries{vi{0, 1, 5}, vi{0, 2, 6}, vi{0, 3, 7}, vi{1, 1, 4}, vi{1, 2, 7}, vi{2, 1, 5}};
    MovieRentingSystem obj(3, entries);
    {
      const vi e_out{1, 0, 2};
    }
  
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
