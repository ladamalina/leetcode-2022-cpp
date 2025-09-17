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

class WordDictionary {
public:
  WordDictionary() : root(new Node()) {}

  void addWord(std::string word) {
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
    auto word_view = std::string_view(word);
    return searchFromNode(word_view, root);
  }

  bool searchFromNode(const std::string_view& word, Node* node) {
    Node* current_node = node;
    for (size_t i = 0; i < word.size(); ++i) {
      const bool is_end = i == word.size()-1;
      if (word[i] == '.') {
        if (is_end) {
          return std::any_of(current_node->children.begin(), current_node->children.end(),
                             [](const std::pair<char, Node*> child){ return child.second->is_end; });
        }
        auto word_view = word.substr(i + 1, word.size() - 1 - i);
        for (const auto& child_node : current_node->children) {
          auto found = searchFromNode(word_view, child_node.second);
          if (found)
            return true;
        }
        return false;
      }
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
  auto wordDictionary1 = new WordDictionary();
  wordDictionary1->addWord("bad");
  wordDictionary1->addWord("dad");
  wordDictionary1->addWord("mad");
  assert(wordDictionary1->search("pad") == false);
  assert(wordDictionary1->search("bad"));
  assert(wordDictionary1->search(".ad"));
  assert(wordDictionary1->search("b.."));

//  ["WordDictionary","addWord","addWord","search","search","search","search","search","search"]
//  [[],["a"],["a"],["."],["a"],["aa"],["a"],[".a"],["a."]]
//  [null,null,null,true,true,false,true,false,false]
  auto wordDictionary2 = new WordDictionary();
  wordDictionary2->addWord("a");
  wordDictionary2->addWord("a");
  assert(wordDictionary2->search("."));
  assert(wordDictionary2->search("a"));
  assert(wordDictionary2->search("aa") == false);
  assert(wordDictionary2->search("a"));
  assert(wordDictionary2->search(".a") == false);
  assert(wordDictionary2->search("a.") == false);

  return 0;
}
