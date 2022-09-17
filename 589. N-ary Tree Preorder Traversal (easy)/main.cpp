#include <iostream>
#include <deque>
#include <vector>

class Node {
public:
    int val;
    std::vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, std::vector<Node*>& _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    std::vector<int> preorder(Node* root) {
        if (!root)
            return {};

        preorderTraverse(root);
        std::vector<int> nodes(nodesQ.begin(), nodesQ.end());

        return nodes;
    }

    void preorderTraverse(Node* root) {
        nodesQ.push_back(root->val);
        if (!root->children.empty())
            for (auto& child : root->children)
                preorderTraverse(child);
    }
private:
    std::deque<uint16_t> nodesQ;
};

int main() {
    return 0;
}
