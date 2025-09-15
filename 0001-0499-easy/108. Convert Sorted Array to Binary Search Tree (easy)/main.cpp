#include <algorithm>
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
    static TreeNode* sortedArrayToBST(std::vector<int>& nums) {
        return BuildBST(nums, 0, nums.size() - 1);
    }

    static TreeNode* BuildBST(std::vector<int>& nums, size_t leftIdx, size_t rightIdx) {
        size_t intervalSize = rightIdx - leftIdx + 1;
        if (intervalSize <= 0)
            return nullptr;
        if (intervalSize == 1)
            return new TreeNode(nums[leftIdx]);

        // intervalSize > 1
        size_t midIdx = leftIdx + intervalSize / 2;
        auto root = new TreeNode(nums[midIdx]);
        auto leftChild = BuildBST(nums, leftIdx, midIdx - 1);
        auto rightChild = BuildBST(nums, midIdx + 1, rightIdx);
        root->left = leftChild;
        root->right = rightChild;

        return root;
    }
};

int main() {
    std::vector<int> nums1 = {-10,-3,0,5,9};
    auto tree1 = Solution::sortedArrayToBST(nums1);

    return 0;
}
