class Solution:
    def isAnagram(self, s: str, t: str) -> bool:

        s_count = [0] * 26
        t_count = [0] * 26

        for index in range(len(s)):
            character = s[index]
            alphabet_index = ord(character) - ord("a")
            s_count[alphabet_index] += 1

        for index in range(len(t)):
            character = t[index]
            alphabet_index = ord(character) - ord("a")
            t_count[alphabet_index] += 1

        return s_count == t_count
