//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

constexpr auto DELIMITER = static_cast<char>('z'+1);

class WordFilter {
  public:

  struct Node {
    Node* nested[27] = {nullptr};
    int id = -1;
    
    Node() = default;
    explicit Node(const int id_) : id(id_) {}
  };
  
  explicit WordFilter(const std::vector<std::string>& words) : root_(new Node()) {
    const auto words_n = static_cast<int>(words.size());
    for (int i = 0; i < words_n; ++i) {
      const auto& w = words[i];
      const auto w_len = static_cast<int>(w.size());
      for (int suff_len = 1; suff_len <= w_len; ++suff_len) {
        const auto dw = w.substr(w_len-suff_len, suff_len) + DELIMITER + w;
        InsertIntoTrie(dw, i, root_);
      }
    }
  }

  int f(const std::string& pref, const std::string& suff) {
    const auto word = suff + DELIMITER + pref;
    const auto w_len = static_cast<int>(word.size());

    auto node = root_;
    int i = 0;
    while (i < w_len) {
      auto& nested_ptr = node->nested[word[i]-'a'];
      if (!nested_ptr) {
        return -1;
      }
      node = nested_ptr;
      ++i;
    }
    return node->id;
  }

  private:
  Node* root_;

  void InsertIntoTrie(const std::string& word, const int id, Node* root) {
    const auto w_len = static_cast<int>(word.size());
    auto node = root;
    int i = 0;
    while (i < w_len) {
      auto& nested_ptr = node->nested[word[i]-'a'];
      if (!nested_ptr) {
        nested_ptr = new Node(id);
      }
      node = nested_ptr;
      node->id = std::max(node->id, id);
      ++i;
    }
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    WordFilter wordFilter({"apple"});
    assert(wordFilter.f("a", "e") == 0); // return 0, because the word at index 0 has prefix = "a" and suffix = "e".
    assert(wordFilter.f("a", "ple") == 0);
    assert(wordFilter.f("a", "ble") == -1);
    
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
