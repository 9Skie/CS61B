I assume there's some take aways we can use from the previous anagram problem...

Since the most efficient method of comparing whether 2 strings are anagrams is still using the counting characters method, I'm guessing that we just do for every string.

The question them comes from how we can effectively do the comparison between strings and strings to group them up... I feel like we can take inspiration from two sum problem, where we use a hash map to somehow encode a string, and then for every string inside the list, it's encoding should be the same as the strings that are anagrams of it, and that allows us to group the similar count strings together.

I feel like there's a more generic takeaway here, **we can turn repeated comparisons into lookups by identifying a key that captures what makes items match**.


So, to talk about time complexity, let $m$ be the number of words and $n$ be the average word length.

Counting characters goes through $m$ words and an average of $n$ characters per word, taking $O(mn)$ time. Initializing the $26$ counters for $m$ words  also takes $O(26m) = O(m)$ time. Grouping goes through $m$ words again, while looking up its group and appending the word take constant time on average, giving $O(m)$.

The total is $O(mn + m + m) = O(mn + m)$, which simplifies to $O(mn)$.