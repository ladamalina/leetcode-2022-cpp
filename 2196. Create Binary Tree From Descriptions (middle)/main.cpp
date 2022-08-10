#include <unordered_map>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    static TreeNode* createBinaryTree(std::vector<std::vector<int>>& descriptions) {
        std::unordered_map<int, TreeNode*> nodes;
        nodes.reserve(descriptions.size());
        std::unordered_map<int, TreeNode*> possibleRoots;
        possibleRoots.reserve(descriptions.size());

        for (auto& descr : descriptions) {
            if (nodes.find(descr[0]) == nodes.end()) { // check if parent exists
                nodes[descr[0]] = new TreeNode(descr[0]);
                // add parent to set of possible roots
                possibleRoots.insert({descr[0], nodes[descr[0]]});
            }
            if (nodes.find(descr[1]) == nodes.end()) // check if child exists
                nodes[descr[1]] = new TreeNode(descr[1]);
            else // remove child from set of possible roots
                possibleRoots.erase(descr[1]);

            if (descr[2]) // append child to parent
                nodes[descr[0]]->left = nodes[descr[1]];
            else
                nodes[descr[0]]->right = nodes[descr[1]];
        }

        return possibleRoots.begin()->second;
    }
};

int main() {
    std::vector<std::vector<int>> d1 = {{1,2,1},{2,3,0},{3,4,1}};
    auto tree1 = Solution::createBinaryTree(d1);

    std::vector<std::vector<int>> d2 = {{20,15,1},{20,17,0},{50,20,1},{50,80,0},{80,19,1}};
    auto tree2 = Solution::createBinaryTree(d2);

    return 0;
}
