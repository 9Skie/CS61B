class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        hashmap = {}

        for index in range(len(nums)):
            value = nums[index]
            difference = target - value
            if difference in hashmap:
                return [hashmap[difference], index]
            hashmap[value] = index
