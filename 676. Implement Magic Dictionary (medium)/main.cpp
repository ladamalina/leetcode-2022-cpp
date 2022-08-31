#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

class Node {
public:
  bool is_end;
  std::unordered_map<char, Node*> children;
  Node() : is_end(false) {}
  Node(bool is_end) : is_end(is_end) {}
};

class MagicDictionary {
public:
  MagicDictionary() : root(new Node()) {}

  void buildDict(const std::vector<std::string>& dictionary) {
    for (const auto& word : dictionary)
      addWord(word);
  }

  void addWord(const std::string& word) {
    Node* current_node = root;
    for (size_t i = 0; i < word.size(); ++i) {
      const bool is_end = i == word.size()-1;
      if (current_node->children.count(word[i]) == 0) {
        auto child = new Node(is_end);
        current_node->children[word[i]] = child;
      }
      if (is_end)
        current_node->children[word[i]]->is_end = is_end;
      current_node = current_node->children[word[i]];
    }
  }

  bool search(const std::string& word) {
    auto current_node = root;
    for (size_t i = 0; i < word.size(); ++i) {
      const bool is_end = (i == word.size()-1);
      if (is_end) {
        return std::any_of(current_node->children.begin(), current_node->children.end(),
                           [&word, &i](const std::pair<char, Node*> child){
                             return child.second->is_end && child.first != word[i];
                           });
      }
      // is_end == false
      if (current_node->children.count(word[i]) == 0) {
        auto word_view = std::string_view(word).substr(i + 1, word.size() - 1 - i);
        return std::any_of(current_node->children.begin(), current_node->children.end(),
                           [&word_view](const std::pair<char, Node*> child){
                             return searchStrictlyFromNode(word_view, child.second);
                           });
      }
      // current_node->children.count(word[i]) == 1

      // try to skip current char
      auto word_view = std::string_view(word).substr(i + 1, word.size() - 1 - i);
      auto can_be_skipped = std::any_of(current_node->children.begin(), current_node->children.end(),
                                        [&word_view, &word, &i](const std::pair<char, Node*> child){
                                          return child.first != word[i] && searchStrictlyFromNode(word_view, child.second);
                                        });
      if (can_be_skipped)
        return true;

      current_node = current_node->children[word[i]];
    }

    return true;
  }

  static bool searchStrictlyFromNode(const std::string_view& word, Node* node) {
    Node* current_node = node;
    for (size_t i = 0; i < word.size(); ++i) {
      const bool is_end = i == word.size()-1;
      if (current_node->children.count(word[i]) == 0)
        return false;
      if (is_end && current_node->children[word[i]]->is_end != is_end)
        return false;
      current_node = current_node->children[word[i]];
    }

    return true;
  }

private:
  Node* root;
};

int main() {
  auto magicDictionary1 = new MagicDictionary();
  std::vector<std::string> dict1{"hello", "leetcode"};
  magicDictionary1->buildDict(dict1);
  assert(magicDictionary1->search("hello") == false);
  assert(magicDictionary1->search("hhllo"));
  assert(magicDictionary1->search("hell") == false);
  assert(magicDictionary1->search("leetcoded") == false);

  auto magicDictionary2 = new MagicDictionary();
  std::vector<std::string> dict2{"hello", "hallo", "leetcode"};
  magicDictionary2->buildDict(dict2);
  assert(magicDictionary2->search("hello"));
  assert(magicDictionary2->search("hhllo"));
  assert(magicDictionary2->search("hell") == false);
  assert(magicDictionary2->search("leetcoded") == false);

  return 0;
}
