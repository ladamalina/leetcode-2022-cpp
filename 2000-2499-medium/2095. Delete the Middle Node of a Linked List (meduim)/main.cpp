#include <iostream>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
 public:
  static ListNode* deleteMiddle(ListNode* head) {
    auto size = getSize(head);
    if (size == 1) {
      return nullptr;
    } // size >= 2
    auto n_to_delete = size / 2;
    auto [prev_node, node_to_delete] = getNthNode(head, n_to_delete);
    prev_node->next = node_to_delete->next;

    return head;
  }

  static size_t getSize(ListNode* head) {
    size_t size = 0;
    ListNode* current_node_ptr = head;
    while (current_node_ptr) {
      ++size;
      current_node_ptr = current_node_ptr->next;
    }

    return size;
  }

  // pair <prev_node, nth_node>
  static std::pair<ListNode*, ListNode*> getNthNode(ListNode* head, const size_t n) {
    assert(head);
    ListNode* current_node_ptr = head;
    ListNode* next_node_ptr = head->next;
    size_t current_n = 0;
    while (current_n < n - 1) {
      ++current_n;
      current_node_ptr = next_node_ptr;
      next_node_ptr = current_node_ptr->next;
    }

    return {current_node_ptr, next_node_ptr};
  }
};

void checkAssertion(ListNode* actual, const std::vector<int>& expected_values) {
  for (auto expected_val : expected_values)
    std::cout << expected_val << ' ';
  std::cout << std::endl;
  ListNode* current_node_ptr = actual;
  for (int expected_val : expected_values) {
    std::cout << "expected_val=" << expected_val << ", current_node_ptr->val=" << current_node_ptr->val << std::endl;
    assert(expected_val == current_node_ptr->val);
    current_node_ptr = current_node_ptr->next;
  }
  assert(!current_node_ptr);
}

int main() {
  {
    auto l_7 = ListNode(6);
    auto l_6 = ListNode(2, &l_7);
    auto l_5 = ListNode(1, &l_6);
    auto l_4 = ListNode(7, &l_5);
    auto l_3 = ListNode(4, &l_4);
    auto l_2 = ListNode(3, &l_3);
    auto l_1 = ListNode(1, &l_2);

    const std::vector<int> expected_values{1,3,4,1,2,6};
    auto actual = Solution::deleteMiddle(&l_1);
    checkAssertion(actual, expected_values);
  }
  {
    auto l_4 = ListNode(4);
    auto l_3 = ListNode(3, &l_4);
    auto l_2 = ListNode(2, &l_3);
    auto l_1 = ListNode(1, &l_2);

    const std::vector<int> expected_values{1,2,4};
    auto actual = Solution::deleteMiddle(&l_1);
    checkAssertion(actual, expected_values);
  }
  {
    auto l_2 = ListNode(1);
    auto l_1 = ListNode(2, &l_2);

    const std::vector<int> expected_values{2};
    auto actual = Solution::deleteMiddle(&l_1);
    checkAssertion(actual, expected_values);
  }
  {
    auto l_1 = ListNode(1);

    const std::vector<int> expected_values;
    auto actual = Solution::deleteMiddle(&l_1);
    checkAssertion(actual, expected_values);
  }

  return 0;
}
