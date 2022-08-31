#include <cassert>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
  static ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    auto len_a = getLength(headA);
    auto len_b = getLength(headB);
    while (len_a > len_b) {
      --len_a;
      headA = headA->next;
    }
    while (len_a < len_b) {
      --len_b;
      headB = headB->next;
    }
    // len_a == len_b
    while (headA != headB) {
      if (headA == nullptr || headB == nullptr)
        return nullptr;
      headA = headA->next;
      headB = headB->next;
    }

    return headA;
  }

  static size_t getLength(ListNode* head) {
    size_t len = 0;
    while (head != nullptr) {
      ++len;
      head = head->next;
    }
    return len;
  }
};

int main() {
  auto e1_c3 = ListNode(3);
  auto e1_c2 = ListNode(2, &e1_c3);
  auto e1_c1 = ListNode(1, &e1_c2);

  auto e1_l1_a2 = ListNode(2, &e1_c1);
  auto e1_l1_a1 = ListNode(1, &e1_l1_a2);

  auto e1_l2_b3 = ListNode(3, &e1_c1);
  auto e1_l2_b2 = ListNode(3, &e1_l2_b3);
  auto e1_l2_b1 = ListNode(3, &e1_l2_b2);

  assert(Solution::getIntersectionNode(&e1_l1_a1, &e1_l2_b1) == &e1_c1);

  auto e2_l1_4 = ListNode(4);
  auto e2_l1_6 = ListNode(6, &e2_l1_4);
  auto e2_l1_2 = ListNode(6, &e2_l1_6);

  auto e2_l2_5 = ListNode(5);
  auto e2_l2_1 = ListNode(1, &e2_l2_5);

  assert(Solution::getIntersectionNode(&e2_l1_2, &e2_l2_1) == nullptr);
}
