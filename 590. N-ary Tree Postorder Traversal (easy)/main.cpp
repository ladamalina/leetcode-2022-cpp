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
    std::vector<int> postorder(Node* root) {
        if (!root)
            return {};
        postorderTraverse(root);
        std::vector<int> nodes(nodesQ.begin(), nodesQ.end());

        return nodes;
    }

    void postorderTraverse(Node* root) {
        if (!root->children.empty())
            for (auto& child : root->children)
                postorderTraverse(child);
        nodesQ.push_back(root->val);
    }
private:
    std::deque<uint16_t> nodesQ;
};

int main() {
    return 0;
}
