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
    static std::vector<std::vector<int>> levelOrder(Node* root) {
        if (root == nullptr)
            return {};
        std::vector<std::vector<int>> levelsToNums = {};
        levelsToNums.reserve(1000);

        std::deque<std::pair<Node*, int>> queue;
        queue.push_back(std::make_pair(root, 0));
        while (!queue.empty()) {
            std::pair node = queue.front();
            queue.pop_front();
            if (levelsToNums.size() < node.second + 1) {
                levelsToNums.emplace_back();
                levelsToNums[node.second].reserve(100);
            }
            levelsToNums[node.second].push_back(node.first->val);
            for (auto& child : node.first->children)
                queue.push_back(std::make_pair(child, node.second + 1));
        }

        return levelsToNums;
    }
};

int main() {
    auto n5 = Node(5);
    auto n6 = Node(6);
    std::vector<Node*> n3ch({&n5, &n6});
    auto n3 = Node(3, n3ch);


    auto n2 = Node(2);
    auto n4 = Node(4);
    std::vector<Node*> n1ch({&n3, &n2, &n4});
    auto n1 = Node(1, n1ch);

    std::vector<std::vector<int>> levelOrder1 = Solution::levelOrder(&n1);
    for (int l = 0; l < levelOrder1.size(); ++l) {
        std::cout << "level " << l << ": ";
        for (auto num : levelOrder1[l])
            std::cout << num << ", ";
        std::cout << std::endl;
    }

    return 0;
}
