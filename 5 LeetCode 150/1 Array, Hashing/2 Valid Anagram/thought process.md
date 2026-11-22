It feels kinda similar to check duplicate, but here we have to check whether all the characters in list (1) exist in list (2), which can be in a different order.

By default, I feel like something universal we can check is that whether the length of these 2 lists are the same, if they are not, then we instantly return otherwise.


Aside from the cheap check, I can think of a few ways.


We iterate through list (1) and keep a tally of each character.
- (this could be like a heuristic that we generate a list of length 26, that is the length of the english alphabet, and each index corresponds to a character individually, like index 0 corresponds to 'a', we can do this because the question said the inputs are restricted to lowercase english alphabet characters only)

Then we iterate through list (2) and keep a tally of each character, then we compare both lists and see if the counts match up.

For two strings of length $n$, we do $n$ tally updates for the first string, $n$ for the second, and up to $26$ comparisons. The total is $O(n + n + 26) = O(n)$ time. The two tally arrays use $O(1)$ extra space because they always have $26$ entries each.


A small improvement for the idea above in terms of space complexity, and just understandability is just storing 1 array instead of 2, where for every count of a letter in list (1) we add a count, and for every count of a letter in list (2) we subtract a count, and in the end only compare whether every value in the count list is 0.
- That wouldn't improve time complexity, or really a lot of space complexity.

Another similar idea is that, instead of a list, we can use a hash map where the key is the letter, and the value is the count of the occurrence of that letter.



Another idea is sorting through both lists, and then comparing each element respectively to see of they are the same.

For example, list (1) = "aab" and list (1) = "aba". After sorting, both become ['a', 'a', 'b']. We compare the characters at each index. Every pair matches, so we return True.

For two strings of length $n$, sorting each takes $O(n \log n)$ time in the worst case, and comparing the sorted lists takes up to $n$ comparisons. The total is $O(n \log n + n \log n + n) = O(n \log n)$ time.