#include <iostream>
#include <unordered_map>
#include <unordered_set>
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
    std::vector<int> findMode(TreeNode* root) {
        traverse(root);
        std::vector<int> modeVals(count_to_vals[maxCount].begin(), count_to_vals[maxCount].end());

        return modeVals;
    }
    void traverse(TreeNode* root) {
        int prev_count = val_to_count[root->val];
        int count = ++val_to_count[root->val];
        if (count > 1)
            count_to_vals[prev_count].erase(root->val);
        count_to_vals[count].insert(root->val);
        maxCount = std::max(maxCount, count);

        if (root->left)
            traverse(root->left);
        if (root->right)
            traverse(root->right);
    }
private:
    std::unordered_map<int, std::unordered_set<int>> count_to_vals;
    std::unordered_map<int, int> val_to_count;
    int maxCount = 0;
};

void checkAssertion(const std::vector<int>& actual, const std::vector<int>& expected) {
    std::cout << "expected: ";
    for (const auto expected_val: expected)
        std::cout << expected_val << ' ';
    std::cout << std::endl;

    std::cout << "actual_res: ";
    for (const auto expected_val: actual)
        std::cout << expected_val << ' ';
    std::cout << std::endl;

    assert(expected.size() == actual.size());
    for (int i = 0; i < expected.size(); ++i) {
        assert(expected[i] == actual[i]);
    }
}

int main() {
    auto n1_2_1 = TreeNode(2);
    auto n1_2_2 = TreeNode(2, nullptr, &n1_2_1);
    auto n1_1 = TreeNode(1, nullptr, &n1_2_2);
    auto mode1 = Solution().findMode(&n1_1);
    std::vector<int> expected1 = {2};
    checkAssertion(mode1, expected1);

    auto n2_0 = TreeNode(0);
    auto mode2 = Solution().findMode(&n2_0);
    std::vector<int> expected2 = {0};
    checkAssertion(mode2, expected2);

    return 0;
}
