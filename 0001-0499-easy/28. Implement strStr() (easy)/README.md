# Leetcode / 28. Implement strStr() (easy) using C++

[https://leetcode.com/problems/implement-strstr/](https://leetcode.com/problems/implement-strstr/)

Implement strStr().

Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Clarification:

What should we return when needle is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().

```
Input: haystack = "hello", needle = "ll"
Output: 2
```

Constraints:

- `1 <= haystack.length, needle.length <= 10^4`
- haystack and needle consist of only lowercase English characters.
