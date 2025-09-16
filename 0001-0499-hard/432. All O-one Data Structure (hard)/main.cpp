//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

class AllOne {
  public:
  AllOne() = default;
    
  void inc(const std::string& key) {
    if (str_2_freq_.contains(key)) {
      const auto old_freq = str_2_freq_.at(key);
      const auto new_freq = old_freq + 1;
      ++str_2_freq_.at(key);
      freq_2_str_.at(old_freq).erase(key);
      freq_2_str_[new_freq].insert(key);
      if (old_freq == min_freq_ && freq_2_str_.at(old_freq).empty()) {
        ++min_freq_;
      }
      if (old_freq == max_freq_) {
        ++max_freq_;
      }
      if (freq_2_str_.at(old_freq).empty()) {
        freq_2_str_.erase(old_freq);
        freqs_[old_freq] = false;
      }
      freqs_[new_freq] = true;
    } else {
      const auto new_freq = 1;
      ++str_2_freq_[key];
      freq_2_str_[new_freq].insert(key);
      if (min_freq_ == 0) {
        ++min_freq_;
      } else {
        min_freq_ = std::min(min_freq_, new_freq);
      }
      max_freq_ = std::max(max_freq_, new_freq);
      freqs_[new_freq] = true;
    }
  }
    
  void dec(const std::string& key) {
    const auto old_freq = str_2_freq_.at(key);
    const auto new_freq = old_freq - 1;
    if (new_freq > 0) {
      --str_2_freq_.at(key);
      freq_2_str_.at(old_freq).erase(key);
      freq_2_str_[new_freq].insert(key);
      if (old_freq == min_freq_) {
        --min_freq_;
      }
      if (old_freq == max_freq_ && freq_2_str_.at(old_freq).empty()) {
        --max_freq_;
      }
      if (freq_2_str_.at(old_freq).empty()) {
        freq_2_str_.erase(old_freq);
        freqs_[old_freq] = false;
      }
      freqs_[new_freq] = true;
    } else { // == 0
      str_2_freq_.erase(key);
      freq_2_str_.at(old_freq).erase(key);
      if (freq_2_str_.at(old_freq).empty()) {
        freqs_[old_freq] = false;
      }
      if (old_freq == min_freq_) {
        if (freq_2_str_.at(old_freq).empty()) {
          const auto min_freq_id = freqs_._Find_first();
          if (min_freq_id == freqs_.size()) {
            min_freq_ = 0;
          } else {
            min_freq_ = min_freq_id;
          }
        }
      }
      if (old_freq == max_freq_ && freq_2_str_.at(old_freq).empty()) {
        --max_freq_;
      }
      if (freq_2_str_.at(old_freq).empty()) {
        freq_2_str_.erase(old_freq);
      }
    }
  }
    
  [[nodiscard]] std::string getMaxKey() const {
    if (max_freq_ > 0) {
      return *freq_2_str_.at(max_freq_).begin();
    }
    return "";
  }
    
  [[nodiscard]] std::string getMinKey() const {
    if (min_freq_ > 0) {
      return *freq_2_str_.at(min_freq_).begin();
    }
    return "";
  }

  private:
  std::unordered_map<std::string, int> str_2_freq_;
  std::unordered_map<int, std::unordered_set<std::string>> freq_2_str_;
  std::bitset<int(1+5*1e4)> freqs_;
  int min_freq_ = 0;
  int max_freq_ = 0;
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    AllOne allOne;
    allOne.inc("hello");
    allOne.inc("hello");
    assert(allOne.getMaxKey() == "hello"); // return "hello"
    assert(allOne.getMinKey() == "hello"); // return "hello"
    allOne.inc("leet");
    assert(allOne.getMaxKey() == "hello"); // return "hello"
    assert(allOne.getMinKey() == "leet"); // return "leet"
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    AllOne allOne;
    allOne.inc("a");
    allOne.inc("b");
    allOne.inc("b");
    allOne.inc("c");
    allOne.inc("c");
    allOne.inc("c");
    allOne.dec("b");
    allOne.dec("b");
    assert(allOne.getMinKey() == "a");
    allOne.dec("a");
    assert(allOne.getMinKey() == "c");
    assert(allOne.getMaxKey() == "c");
    
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
