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

class Trie {
public:
    Trie() : root(new Node()) {}

    void insert(const std::string& word) {
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
        Node* current_node = root;
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

    bool startsWith(const std::string& prefix) {
        Node* current_node = root;
        for (const auto& ch : prefix) {
            if (current_node->children.count(ch) == 0)
                return false;
            current_node = current_node->children[ch];
        }

        return true;
    }
private:
    Node* root;
};

int main() {
    auto trie = new Trie();
    trie->insert("apple");
    assert(trie->search("apple"));
    assert(trie->search("app") == false);
    assert(trie->startsWith("app"));
    trie->insert("app");
    assert(trie->search("app"));

    return 0;
}
