#include <algorithm>
#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    static std::vector<std::vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr)
            return {};

        std::vector<int> prevPath;
        return getPathesSum(root, targetSum, 0, prevPath);
    }

    static std::vector<std::vector<int>> getPathesSum(TreeNode* root, int targetSum, int prevSum, std::vector<int>& prevPath) {
        int currentSum = root->val + prevSum;

        if (root->left == nullptr && root->right == nullptr) { // leaf
            if (currentSum == targetSum) {
                auto currentPath = prevPath;
                currentPath.push_back(root->val);
                return {currentPath};
            } else {
                return {};
            }
        }
        // not leaf
        auto currentPath = prevPath;
        currentPath.push_back(root->val);

        std::vector<std::vector<int>> leftPathes;
        std::vector<std::vector<int>> rightPathes;

        if (root->left != nullptr)
            leftPathes = getPathesSum(root->left, targetSum, currentSum, currentPath);

        if (root->right != nullptr) {
            rightPathes = getPathesSum(root->right, targetSum, currentSum, currentPath);
        }

        leftPathes.insert(leftPathes.end(), rightPathes.begin(), rightPathes.end());

        return leftPathes;
    }
};

void checkAssert(std::vector<std::vector<int>>& actual, std::vector<std::vector<int>>& expected) {
    std::cout << "actual: ";
    for (int i = 0; i < actual.size(); ++i) {
        if (i == 0)
            std::cout << "[";
//        std::sort(actual[i].begin(), actual[i].end());
        for (int j = 0; j < actual[i].size(); ++j) {
            if (j == 0)
                std::cout << "[";
            std::cout << actual[i][j] << ", ";
            if (j == actual[i].size() - 1)
                std::cout << "]";
        }
        if (i == actual.size() - 1)
            std::cout << "]";
    }
    std::cout << std::endl;
    std::sort(actual.begin(), actual.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) {
                  return a[0] < b[0];
              });

    std::cout << "expected: ";
    for (int i = 0; i < expected.size(); ++i) {
        if (i == 0)
            std::cout << "[";
//        std::sort(expected[i].begin(), expected[i].end());
        for (int j = 0; j < expected[i].size(); ++j) {
            if (j == 0)
                std::cout << "[";
            std::cout << expected[i][j] << ", ";
            if (j == expected[i].size() - 1)
                std::cout << "]";
        }
        if (i == expected.size() - 1)
            std::cout << "]";
    }
    std::cout << std::endl;
    std::sort(expected.begin(), expected.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) {
                  return a[0] < b[0];
              });

    assert(actual.size() == expected.size());
    for (int i = 0; i < expected.size(); ++i) {
        assert(actual[i].size() == expected[i].size());
        for (int j = 0; j < expected[i].size(); ++j) {
            std::cout << "assert: " << actual[i][j] << " == " << expected[i][j] << std::endl;
            assert(actual[i][j] == expected[i][j]);
        }
    }
}

int main() {
    auto n7 = TreeNode(7);
    auto n2 = TreeNode(2);
    auto n11 = TreeNode(11, &n7, &n2);
    auto n4 = TreeNode(4, &n11, nullptr);

    auto n5 = TreeNode(5);
    auto n1 = TreeNode(1);
    auto n4_2 = TreeNode(4, &n5, &n1);

    auto n13 = TreeNode(13);
    auto n8 = TreeNode(8, &n13, &n4_2);

    auto n5_2 = TreeNode(5, &n4, &n8);

    std::vector<std::vector<int>> actualPathes = Solution::pathSum(&n5_2, 22);
    std::vector<std::vector<int>> expectedPathes = {{5,4,11,2},{5,8,4,5}};
    checkAssert(actualPathes, expectedPathes);

    return 0;
}
