#include <algorithm>
#include <deque>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
    static TreeNode* sortedListToBST(ListNode* head) {
        std::deque<int> nums = getDequeFromList(head);
        return BuildBST(nums, 0, nums.size() - 1);
    }

    static TreeNode* BuildBST(std::deque<int>& nums, size_t leftIdx, size_t rightIdx) {
        size_t intervalSize = rightIdx - leftIdx + 1;
        if (intervalSize <= 0)
            return nullptr;
        if (intervalSize == 1)
            return new TreeNode(nums[leftIdx]);

        // intervalSize > 1
        size_t midIdx = leftIdx + intervalSize / 2;
        auto leftChild = BuildBST(nums, leftIdx, midIdx - 1);
        auto rightChild = BuildBST(nums, midIdx + 1, rightIdx);
        return new TreeNode(nums[midIdx], leftChild, rightChild);
    }

    static std::deque<int> getDequeFromList(ListNode* head) {
        std::deque<int> res;
        auto headPtr = head;
        while (headPtr != nullptr) {
            res.push_back(headPtr->val);
            headPtr = headPtr->next;
        }

        return res;
    }
};

int main() {
    auto l1_5 = ListNode(9);
    auto l1_4 = ListNode(5, &l1_5);
    auto l1_3 = ListNode(0, &l1_4);
    auto l1_2 = ListNode(-3, &l1_3);
    auto l1_1 = ListNode(-10, &l1_2);
    auto tree1 = Solution::sortedListToBST(&l1_1);

    return 0;
}
