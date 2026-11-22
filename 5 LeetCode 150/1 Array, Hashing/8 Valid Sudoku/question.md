# 36. Valid Sudoku

[LeetCode problem](https://leetcode.com/problems/valid-sudoku/description/)

## Problem

Check whether the filled cells of a `9 × 9` Sudoku board obey the rules. A digit may appear at most once per row, column, and aligned `3 × 3` box. The board can be partially filled, and its solvability is irrelevant.

## Examples

### Example 1

```text
Input
board = [
    ["5","3",".",".","7",".",".",".","."],
    ["6",".",".","1","9","5",".",".","."],
    [".","9","8",".",".",".",".","6","."],
    ["8",".",".",".","6",".",".",".","3"],
    ["4",".",".","8",".","3",".",".","1"],
    ["7",".",".",".","2",".",".",".","6"],
    [".","6",".",".",".",".","2","8","."],
    [".",".",".","4","1","9",".",".","5"],
    [".",".",".",".","8",".",".","7","9"]
]
Output: true
```

### Example 2

```text
Input
board = [
    ["8","3",".",".","7",".",".",".","."],
    ["6",".",".","1","9","5",".",".","."],
    [".","9","8",".",".",".",".","6","."],
    ["8",".",".",".","6",".",".",".","3"],
    ["4",".",".","8",".","3",".",".","1"],
    ["7",".",".",".","2",".",".",".","6"],
    [".","6",".",".",".",".","2","8","."],
    [".",".",".","4","1","9",".",".","5"],
    [".",".",".",".","8",".",".","7","9"]
]
Output: false
```

## Constraints

The board is exactly `9 × 9`. Each entry is `"."` or a string digit from `"1"` through `"9"`.
