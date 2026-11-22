class Solution:
    def groupAnagrams(self, strs: list[str]) -> list[list[str]]:

        str_counts = [[0] * 26 for i in range(len(strs))]

        # convert each string into a list of counts of each letter
        for outer_index in range(len(strs)):
            for inner_index in range(len(strs[outer_index])):
                character = strs[outer_index][inner_index]
                alphabet_index = ord(character) - ord("a")
                str_counts[outer_index][alphabet_index] += 1

        anagrams = {}

        for outer_index in range(len(strs)):
            key = tuple(str_counts[outer_index]) # we need a unique key, which a list cannot be
            if anagrams.get(key) is None:
                anagrams[key] = []
            anagrams[key].append(strs[outer_index])
