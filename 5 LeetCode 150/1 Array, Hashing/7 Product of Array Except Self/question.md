# 238. Product of Array Except Self

[LeetCode problem](https://leetcode.com/problems/product-of-array-except-self/description/)

## Problem

Return an array whose entry at index `i` is the product of every entry of `nums` other than the one at index `i`. Use linear time and avoid division.

## Examples

### Example 1

```text
Input: nums = [1,2,3,4]
Output: [24,12,8,6]
```

### Example 2

```text
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
```

## Constraints

`2 ≤ len(nums) ≤ 10^5`, `-30 ≤ nums[i] ≤ 30`. All prefix products, suffix products, and output values fit in signed 32-bit integers.

## Follow-up

Can you use constant extra space when the output array is excluded?
