# 347. Top K Frequent Elements

[LeetCode problem](https://leetcode.com/problems/top-k-frequent-elements/description/)

## Problem

Return the `k` distinct values with the highest occurrence counts in `nums`. The set of qualifying values is unique, and the output order is flexible.

## Examples

### Example 1

```text
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
```

### Example 2

```text
Input: nums = [1], k = 1
Output: [1]
```

### Example 3

```text
Input: nums = [1,2,1,2,1,2,3,1,3,2], k = 2
Output: [1,2]
```

## Constraints

`1 ≤ len(nums) ≤ 10^5`, `-10^4 ≤ nums[i] ≤ 10^4`. The value of `k` is at least 1 and at most the number of distinct values.

## Follow-up

Can you do better than `O(n log n)` time?
