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

// Функция для суммирования двух чисел, представленных в виде строк
std::string SumStrings(const std::string& num1, const std::string& num2) {
  int i = SZ(num1) - 1; // Индекс для последнего символа в первой строке
  int j = SZ(num2) - 1; // Индекс для последнего символа во второй строке
  int carry = 0; // Перенос (десятки)
  std::string result; // Результирующая строка

  // Проходим по строкам с конца к началу
  while (i >= 0 || j >= 0 || carry) {
    int sum = carry; // Начинаем с переноса
    if (i >= 0) {
      sum += num1[i--] - '0'; // Добавляем цифру из первой строки
    }
    if (j >= 0) {
      sum += num2[j--] - '0'; // Добавляем цифру из второй строки
    }
    carry = sum / 10; // Вычисляем новый перенос
    result.push_back(sum % 10 + '0'); // Добавляем текущую цифру к результату
  }

  std::reverse(result.begin(), result.end()); // Разворачиваем строку, так как числа добавлялись с конца
  return result;
}

class Solution {
public:
  bool isAdditiveNumber(const std::string& s) {
    const auto n = SZ(s);
    if (n < 3)
      return false;

    const std::function<bool(int,const std::string&,const std::string&)> check =
        [&](const int i, const std::string& x1_str, const std::string& x2_str) {
      if (i == n)
        return true;
      const auto x3_str = SumStrings(x1_str, x2_str);
      if (s.substr(i).starts_with(x3_str)) {
        const auto sub_res = check(i + SZ(x3_str), x2_str, x3_str);
        return sub_res;
      }
      return false;
    };
    
    bool ok = false;
    FOR(len1, 1, n-2) {
      if (s[0] == '0' && len1 > 1)
        break;
      const auto x1_str = s.substr(0, len1);
      FOR(len2, 1, n-len1-1) {
        if (s[len1] == '0' && len2 > 1)
          break;
        const auto x2_str = s.substr(len1, len2);
        const auto res12 = check(len1 + len2, x1_str, x2_str);
        ok |= res12;
      }
    }
    return ok;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().isAdditiveNumber("112358");
    assert(a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().isAdditiveNumber("199100199");
    assert(a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().isAdditiveNumber("11111111111011111111111");
    assert(a_out);
  
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
