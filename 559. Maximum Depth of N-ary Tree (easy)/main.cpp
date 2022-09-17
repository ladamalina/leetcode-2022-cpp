#include <algorithm>
#include <vector>

class Node {
public:
    int val;
    std::vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, std::vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    int maxDepth(Node* root) {
        if (!root)
            return 0;
        maxDepthTraverse(root, 0);

        return maxD;
    }

    void maxDepthTraverse(Node* root, int prevD) {
        maxD = std::max(maxD, prevD + 1);
        for (auto& child : root->children)
            if (child)
                maxDepthTraverse(child, prevD + 1);
    }
private:
    int maxD = 0;
};

int main() {
    return 0;
}
