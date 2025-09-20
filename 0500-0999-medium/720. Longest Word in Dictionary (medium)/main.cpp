#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

class Node {
 public:
  char ch;
  bool is_end;
  std::unordered_map<char, Node*> children;
  Node(char ch) : ch(ch), is_end(false) {}
  Node(char ch, bool is_end) : ch(ch), is_end(is_end) {}
};

class Trie {
 public:
  Trie() : root(new Node(0)) {}

  void insert(const std::string& word) {
    Node* current_node = root;
    for (size_t i = 0; i < word.size(); ++i) {
      const bool is_end = (i == word.size()-1);
      if (current_node->children.count(word[i]) == 0) {
        auto child = new Node(word[i], is_end);
        current_node->children[word[i]] = child;
      }
      if (is_end)
        current_node->children[word[i]]->is_end = is_end;
      current_node = current_node->children[word[i]];
    }
  }

  std::string getLongestWord() {
    std::string initial_prefix;
    return getLongestWordFromNode(root, initial_prefix);
  }

 private:
  Node* root;

  static std::string getLongestWordFromNode(Node* node, std::string& prefix) {
    std::string word;
    if (node->ch > 0) { // not a root
      word = prefix + node->ch;
    }
    std::string longest_word = word;
    for (const auto& [child_ch, child_node] : node->children) {
      if (!child_node->is_end) {
        continue;
      }
      std::string child_longest_word = getLongestWordFromNode(child_node, word);
      if (child_longest_word.size() > longest_word.size()) {
        longest_word = child_longest_word;
      } else if (child_longest_word.size() == longest_word.size()) {
        longest_word = std::min(longest_word, child_longest_word);
      }
    }

    return longest_word;
  }
};

class Solution {
 public:
  static std::string longestWord(std::vector<std::string>& words) {
    Trie trie;
    for (const auto& word : words) {
      trie.insert(word);
    }
    std::string longest_word = trie.getLongestWord();

    return longest_word;
  }
};

int main() {
  std::vector<std::string> words1{"w","wo","wor","worl","world"};
  assert(Solution::longestWord(words1) == "world");

  std::vector<std::string> words2{"a","banana","app","appl","ap","apply","apple"};
  assert(Solution::longestWord(words2) == "apple");

  std::vector<std::string> words3{"a","banana","app","appl"};
  assert(Solution::longestWord(words3) == "a");

  return 0;
}
