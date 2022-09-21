# Leetcode / 985. Sum of Even Numbers After Queries (medium) using C++

[https://leetcode.com/problems/sum-of-even-numbers-after-queries/](https://leetcode.com/problems/sum-of-even-numbers-after-queries/)

You are given an integer array nums and an array queries where queries[i] = [vali, indexi].

For each query i, first, apply nums[indexi] = nums[indexi] + vali, then print the sum of the even values of nums.

Return an integer array answer where answer[i] is the answer to the ith query.

Constraints:

- `1 <= nums.length <= 10^4`
- `-10^4 <= nums[i] <= 10^4`
- `1 <= queries.length <= 10^4`
- `-10^4 <= vali <= 10^4`
- `0 <= indexi < nums.length`
