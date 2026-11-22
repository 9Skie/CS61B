class Solution:
    def containsDuplicate(self, nums: list[int]) -> bool:

        # a hash table exists in python by default, we do not need to write out some hash algorithm
        hashset = set()

        for index in range(len(nums)):
            value = nums[index]
            if value in hashset:
                return True
            hashset.add(value)

        return False
