#include <cassert>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    static ListNode* deleteDuplicates(ListNode* head) {
        if (!head)
            return head;

        auto currentPtr = head;
        auto nextPtr = head->next;
        while (nextPtr) {
            if (currentPtr->val == nextPtr->val) {
                // delete next node
                currentPtr->next = nextPtr->next;
                nextPtr = nextPtr->next;
            } else { // currentPtr->val != nextPtr->val
                currentPtr = nextPtr;
                nextPtr = currentPtr->next;
            }
        }

        return head;
    }
};

void check(ListNode* head, std::vector<int>& expected) {
    if (expected.empty())
        assert(!head);

    for (int e : expected) {
        assert(head->val == e);
        head = head->next;
    }
}

int main() {
    auto l1_3 = ListNode(2);
    auto l1_2 = ListNode(1, &l1_3);
    auto l1_1 = ListNode(1, &l1_2);
    Solution::deleteDuplicates(&l1_1);
    std::vector<int> exp1 = {1,2};
    check(&l1_1, exp1);

    auto l2_5 = ListNode(3);
    auto l2_4 = ListNode(3, &l2_5);
    auto l2_3 = ListNode(2, &l2_4);
    auto l2_2 = ListNode(1, &l2_3);
    auto l2_1 = ListNode(1, &l2_2);
    Solution::deleteDuplicates(&l2_1);
    std::vector<int> exp2 = {1,2,3};
    check(&l2_1, exp2);

    auto l3_2 = ListNode(1);
    auto l3_1 = ListNode(1, &l3_2);
    Solution::deleteDuplicates(&l3_1);
    std::vector<int> exp3 = {1};
    check(&l3_1, exp3);

    auto l4_1 = ListNode(1);
    Solution::deleteDuplicates(&l4_1);
    std::vector<int> exp4 = {1};
    check(&l4_1, exp4);

    auto l5_5 = ListNode(1);
    auto l5_4 = ListNode(1, &l5_5);
    auto l5_3 = ListNode(1, &l5_4);
    auto l5_2 = ListNode(1, &l5_3);
    auto l5_1 = ListNode(1, &l5_2);
    Solution::deleteDuplicates(&l5_1);
    std::vector<int> exp5 = {1};
    check(&l5_1, exp5);

    auto l6_1 = nullptr;
    Solution::deleteDuplicates(l6_1);
    std::vector<int> exp6 = {};
    check(l6_1, exp6);

    return 0;
}
