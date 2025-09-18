#include <cassert>
#include <vector>
#include <set>

class KthLargest {
public:
  KthLargest(int k, std::vector<int>& nums) : capacity(k) {
    for (auto& val : nums)
      add(val);
  }

  int add(int val) {
    if (nums_set.size() == capacity && val <= *nums_set.begin())
      return *nums_set.begin();

    nums_set.insert(val);
    if (nums_set.size() > capacity)
      nums_set.erase(nums_set.begin());

    return *nums_set.begin();
  }
private:
  std::multiset<int> nums_set;
  size_t capacity;
};

int main() {
  std::vector<int> nums1{4, 5, 8, 2};
  auto kthLargest1 = KthLargest(3, nums1);
  assert(kthLargest1.add(3)  == 4);
  assert(kthLargest1.add(5)  == 5);
  assert(kthLargest1.add(10) == 5);
  assert(kthLargest1.add(9)  == 8);
  assert(kthLargest1.add(4)  == 8);

  std::vector<int> nums2{0};
  auto kthLargest2 = KthLargest(2, nums2);
  assert(kthLargest2.add(-1) == -1);
  assert(kthLargest2.add(1)  == 0);
  assert(kthLargest2.add(-2) == 0);
  assert(kthLargest2.add(-4) == 0);
  assert(kthLargest2.add(3)  == 1);

  return 0;
}
