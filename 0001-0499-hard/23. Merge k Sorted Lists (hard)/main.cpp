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
  static ListNode* mergeKLists(const std::vector<ListNode*>& lists) {
    if (lists.empty()) {
      return nullptr;
    }
    if (lists.size() == 1u) {
      return lists[0];
    }
    return mergeKLists(lists, 0, lists.size() - 1);
  }

  static ListNode* mergeKLists(const std::vector<ListNode*>& lists, const size_t begin_i, const size_t end_i) {
    const size_t part_size = end_i - begin_i + 1;
    if (part_size == 0) {
      return nullptr;
    }
    if (part_size == 1u) {
      return lists[begin_i];
    }
    if (part_size == 2u) {
      return mergeTwoLists(lists[begin_i], lists[end_i]);
    }
    // part_size >= 3
    size_t mid_i = begin_i + part_size / 2;
    const auto merge_left = mergeKLists(lists, begin_i, mid_i);
    const auto merge_right = mergeKLists(lists, mid_i + 1, end_i);

    return mergeTwoLists(merge_left, merge_right);
  }

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
  {
    auto l1_3 = ListNode(5);
    auto l1_2 = ListNode(4, &l1_3);
    auto l1 = ListNode(1, &l1_2);

    auto l2_3 = ListNode(4);
    auto l2_2 = ListNode(3, &l2_3);
    auto l2 = ListNode(1, &l2_2);

    auto l3_2 = ListNode(6);
    auto l3 = ListNode(2, &l3_2);

    const std::vector<ListNode*> l_input{&l1, &l2, &l3};
    auto l_actual = Solution::mergeKLists(l_input);

    const std::vector<int> expected_values{1,1,2,3,4,4,5,6};
    checkAssertion(l_actual, expected_values);
  }
  std::cout << ".............................." << std::endl;
  {
    const std::vector<ListNode*> l_input;
    auto l_actual = Solution::mergeKLists(l_input);

    const std::vector<int> expected_values{};
    checkAssertion(l_actual, expected_values);
  }
  std::cout << ".............................." << std::endl;
  {
    ListNode* l1 = nullptr;

    const std::vector<ListNode*> l_input{l1};
    auto l_actual = Solution::mergeKLists(l_input);

    const std::vector<int> expected_values{};
    checkAssertion(l_actual, expected_values);
  }
  std::cout << ".............................." << std::endl;
}
