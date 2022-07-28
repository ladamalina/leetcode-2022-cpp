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
    static ListNode* addTwoNumbers(ListNode*& l1, ListNode*& l2) {
        auto l1p = l1;
        auto l2p = l2;
        int over_sum = 0;
        ListNode* l3p_head = nullptr;
        ListNode* l3p_tail = nullptr;
        while (l1p != nullptr || l2p != nullptr) {
            int l1val = 0;
            if (l1p != nullptr) {
                l1val = l1p->val;
            }
            int l2val = 0;
            if (l2p != nullptr) {
                l2val = l2p->val;
            }
            int current_sum = l1val + l2val + over_sum;
            if (current_sum >= 10) {
                over_sum = current_sum / 10;
                current_sum = current_sum % 10;
            } else {
                over_sum = 0;
            }
            appendVal(l3p_head, l3p_tail, current_sum);
            if (l1p != nullptr) {
                l1p = l1p->next;
            }
            if (l2p != nullptr) {
                l2p = l2p->next;
            }
        }
        if (over_sum > 0) {
            appendVal(l3p_head, l3p_tail, over_sum);
        }

        return l3p_head;
    }

    static void appendVal(ListNode*& l3p_head, ListNode*& l3p_tail, int& val) {
        auto l3p = new ListNode(val);
        if (l3p_head == nullptr) {
            l3p_head = l3p;
            l3p_tail = l3p;
        } else {
            l3p_tail->next = l3p;
            l3p_tail = l3p;
        }
    }
};

void checkAssertion(ListNode* lp, const std::vector<int>& expected_vals) {
    std::cout << "expected_vals: ";
    for (auto expected_val: expected_vals)
        std::cout << expected_val << ' ';
    std::cout << std::endl;
    ListNode* current_node_ptr = lp;
    for (int expected_val : expected_vals) {
        std::cout << "expected_val=" << expected_val << ", current_node_ptr->val=" << current_node_ptr->val << std::endl;
        assert(expected_val == current_node_ptr->val);
        current_node_ptr = current_node_ptr->next;
    }
    assert(current_node_ptr == nullptr);
}

int main() {
    auto l1_3 = new ListNode(3);
    auto l1_2 = new ListNode(4, l1_3);
    auto l1 = new ListNode(2, l1_2);
    auto l2_3 = new ListNode(4);
    auto l2_2 = new ListNode(6, l2_3);
    auto l2 = new ListNode(5, l2_2);
    ListNode* l3p = Solution::addTwoNumbers(l1, l2);
    std::vector<int> expected_vals1 = {7,0,8};
    checkAssertion(l3p, expected_vals1);
    std::cout << ".............................." << std::endl;

    auto l3_1 = new ListNode(0);
    auto l4_1 = new ListNode(0);
    ListNode* l5p = Solution::addTwoNumbers(l3_1, l4_1);
    std::vector<int> expected_vals2 = {0};
    checkAssertion(l5p, expected_vals2);
    std::cout << ".............................." << std::endl;

    auto l6_7 = new ListNode(9);
    auto l6_6 = new ListNode(9, l6_7);
    auto l6_5 = new ListNode(9, l6_6);
    auto l6_4 = new ListNode(9, l6_5);
    auto l6_3 = new ListNode(9, l6_4);
    auto l6_2 = new ListNode(9, l6_3);
    auto l6_1 = new ListNode(9, l6_2);

    auto l7_4 = new ListNode(9);
    auto l7_3 = new ListNode(9, l7_4);
    auto l7_2 = new ListNode(9, l7_3);
    auto l7_1 = new ListNode(9, l7_2);

    ListNode* l8p = Solution::addTwoNumbers(l6_1, l7_1);
    std::vector<int> expected_vals3 = {8,9,9,9,0,0,0,1};
    checkAssertion(l8p, expected_vals3);
    std::cout << ".............................." << std::endl;
}
