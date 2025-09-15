#include <cassert>
#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    static ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1) {
            return list2;
        }
        if (!list2) {
            return list1;
        }
        ListNode* head_ptr = nullptr;
        ListNode* tail_ptr = nullptr;
        auto l1p = list1;
        auto l2p = list2;
        while (l1p && l2p) {
            int next_val;
            if (l1p->val <= l2p->val) {
                next_val = l1p->val;
                l1p = l1p->next;
            } else {
                next_val = l2p->val;
                l2p = l2p->next;
            }
            auto* new_node_ptr = new ListNode(next_val);

            if (!head_ptr) {
                head_ptr = new_node_ptr;
                tail_ptr = new_node_ptr;
            } else {
                tail_ptr->next = new_node_ptr;
                tail_ptr = new_node_ptr;
            }
        }
        if (l1p) {
            tail_ptr->next = l1p;
        }
        if (l2p) {
            tail_ptr->next = l2p;
        }
        return head_ptr;
    }
};

void checkAssertion(ListNode* lp, const std::vector<int>& expected_vals) {
    for (auto expected_val: expected_vals)
        std::cout << expected_val << ' ';
    std::cout << std::endl;
    ListNode* current_node_ptr = lp;
    for (int expected_val : expected_vals) {
        std::cout << "expected_val=" << expected_val << ", current_node_ptr->val=" << current_node_ptr->val << std::endl;
        assert(expected_val == current_node_ptr->val);
        current_node_ptr = current_node_ptr->next;
    }
    assert(!current_node_ptr);
}

int main() {
    auto l1_4 = ListNode(4);
    auto l1_2 = ListNode(2, &l1_4);
    auto l1 = ListNode(1, &l1_2);
    auto l2_4 = ListNode(4);
    auto l2_3 = ListNode(3, &l2_4);
    auto l2 = ListNode(1, &l2_3);
    ListNode* l3p = Solution::mergeTwoLists(&l1, &l2);
    std::vector<int> expected_vals1 = {1,1,2,3,4,4};
    checkAssertion(l3p, expected_vals1);
    std::cout << ".............................." << std::endl;

    ListNode* l4p = Solution::mergeTwoLists(nullptr, nullptr);
    std::vector<int> expected_vals2 = {};
    checkAssertion(l4p, expected_vals2);
    std::cout << ".............................." << std::endl;

    auto l5 = ListNode(0);
    ListNode* l6p = Solution::mergeTwoLists(nullptr, &l5);
    std::vector<int> expected_vals3 = {0};
    checkAssertion(l6p, expected_vals3);
    std::cout << ".............................." << std::endl;
}
