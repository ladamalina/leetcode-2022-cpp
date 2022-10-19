#include <cassert>
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
  static ListNode* rotateRight(ListNode* head, int k) {
    if (!head || k == 0) {
      return head;
    } // head not null && k >= 1
    auto list_len = getSize(head);
    if (list_len == 1) {
      return head;
    } // list_len >= 2
    size_t head_idx = list_len - k % list_len;
    if (head_idx == list_len) {
      return head;
    } // 0 <= head_idx < list_len

    auto [new_tail, new_head] = getNodeByIdx(head, head_idx);
    auto [_2, old_tail] = getNodeByIdx(head, list_len - 1);
    old_tail->next = head;
    new_tail->next = nullptr;

    return new_head;
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
  static std::pair<ListNode*, ListNode*> getNodeByIdx(ListNode* head, const size_t idx) {
    assert(head);
    ListNode* current_node_ptr = nullptr;
    ListNode* next_node_ptr = head;
    size_t current_n = 0;
    while (current_n < idx) {
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
    auto l_5 = ListNode(5);
    auto l_4 = ListNode(4, &l_5);
    auto l_3 = ListNode(3, &l_4);
    auto l_2 = ListNode(2, &l_3);
    auto l_1 = ListNode(1, &l_2);

    const std::vector<int> expected_values{5,1,2,3,4};
    auto actual = Solution::rotateRight(&l_1, 1);
    checkAssertion(actual, expected_values);
  }
  {
    auto l_5 = ListNode(5);
    auto l_4 = ListNode(4, &l_5);
    auto l_3 = ListNode(3, &l_4);
    auto l_2 = ListNode(2, &l_3);
    auto l_1 = ListNode(1, &l_2);

    const std::vector<int> expected_values{4,5,1,2,3};
    auto actual = Solution::rotateRight(&l_1, 2);
    checkAssertion(actual, expected_values);
  }
  {
    auto l_5 = ListNode(5);
    auto l_4 = ListNode(4, &l_5);
    auto l_3 = ListNode(3, &l_4);
    auto l_2 = ListNode(2, &l_3);
    auto l_1 = ListNode(1, &l_2);

    const std::vector<int> expected_values{1,2,3,4,5};
    auto actual = Solution::rotateRight(&l_1, 0);
    checkAssertion(actual, expected_values);
  }
  {
    auto l_5 = ListNode(5);
    auto l_4 = ListNode(4, &l_5);
    auto l_3 = ListNode(3, &l_4);
    auto l_2 = ListNode(2, &l_3);
    auto l_1 = ListNode(1, &l_2);

    const std::vector<int> expected_values{1,2,3,4,5};
    auto actual = Solution::rotateRight(&l_1, 5);
    checkAssertion(actual, expected_values);
  }
  {
    auto l_5 = ListNode(5);
    auto l_4 = ListNode(4, &l_5);
    auto l_3 = ListNode(3, &l_4);
    auto l_2 = ListNode(2, &l_3);
    auto l_1 = ListNode(1, &l_2);

    const std::vector<int> expected_values{4,5,1,2,3};
    auto actual = Solution::rotateRight(&l_1, 7);
    checkAssertion(actual, expected_values);
  }
  {
    ListNode* l_1 = nullptr;

    const std::vector<int> expected_values{};
    auto actual = Solution::rotateRight(l_1, 5);
    checkAssertion(actual, expected_values);
  }
  {
    ListNode* l_1 = nullptr;

    const std::vector<int> expected_values{};
    auto actual = Solution::rotateRight(l_1, 0);
    checkAssertion(actual, expected_values);
  }
  {
    auto l_1 = ListNode(1);

    const std::vector<int> expected_values{1};
    auto actual = Solution::rotateRight(&l_1, 5);
    checkAssertion(actual, expected_values);
  }
  {
    auto l_1 = ListNode(1);

    const std::vector<int> expected_values{1};
    auto actual = Solution::rotateRight(&l_1, 0);
    checkAssertion(actual, expected_values);
  }
  {
    auto l_1 = ListNode(1);

    const std::vector<int> expected_values{1};
    auto actual = Solution::rotateRight(&l_1, 7);
    checkAssertion(actual, expected_values);
  }

  return 0;
}
