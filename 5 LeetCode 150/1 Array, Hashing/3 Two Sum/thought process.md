You may assume that each input would have **_exactly_ one solution**, and you may not use the _same_ element twice.

That's very helpful, but how would we do this?


I can think of a dumb solution first, that is, brute force test it, which means for every element in the list, test it's sum with every other element in the list, and when we find a match, we return their indexes.

The outer loop goes through $n$ elements. For each element, the inner loop checks up to $n$ other elements, doing one addition and one comparison per check. Multiplying the two loop counts gives $O(n \times n) = O(n^2)$.


We can skip redundant pairs by starting the inner loop at index $i + 1$. That means the inner loop runs $n - i - 1$ times at index $i$. For example, with $n = 5$ and $i = 1$, we only check indices $2$, $3$, and $4$.

This cuts the number of pair checks in half compared with checking every pair in both orders. The outer loop still runs $n$ times, and the inner loop averages about $n/2$ checks per iteration, so the time complexity is $O(n \times n/2) = O(n^2)$.



A more efficient approach is to use a hash map. First, we iterate through the list and store each number as a key and its index as the corresponding value.

Then we iterate through the list again. For each number, we subtract it from `target` to find the number we need to complete the pair. We look up that number in the hash map. If it exists and its stored index differs from the current index, we return both indices.

The first loop goes through $n$ elements and does one hash map insertion per element. The second loop goes through up to $n$ elements and does one subtraction and one hash map lookup per element, followed by an index check if the lookup succeeds.

With constant-time hash map operations on average, each pass takes $O(n)$ time. The passes run one after the other, so we add them: $O(n + n) = O(n)$.


A faster method instead of 2 passes, take 1 pass. We can build the hash map while searching for the pair. Start with an empty map. At each index `i`, subtract `nums[i]` from `target` and look up the remaining value. If it’s in the map, return its stored index and `i`. Otherwise, store `nums[i]` as the key and `i` as its value, then move to the next element.

Looking up the remaining value before inserting the current number ensures we only match against earlier indices. This combines the two passes into one and still takes $O(n)$ time on average.



Joke on the comment section.

Person A: Interview tip, If the interviewer asks something and you don't know the answer, just answer "a hash map should do the trick". 90% success rate 70% of the time.

Person B: Bad advice. I had an interview last week and they said, "tell me about yourself" and I replied "a hash map should do the trick". They all looked at me weird and ended the interview. Thanks for the bad advice.