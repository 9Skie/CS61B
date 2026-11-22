This feels like, we can have a dumb way to do it, but I'm not sure if it can be sped up.


For example, given a list (1), i could create another list (2) and append values into it as we iterate through list (1), then, at every index of list (1), we would iterate through all of list (2) to check whether a duplicate exists in there.

If there is no duplicate, this value is unique in the current array that we've iterated through, if a duplicate is found, we return the result early.

This is $O(n^2)$ because if there are no duplicates, we have to scan the entire second list at each step. Its length grows from $0$ to $n-1$, so we make $0 + 1 + \cdots + (n-1) = \frac{n(n-1)}{2}$ comparisons.



Another idea is that we sort the list and then compare adjacent elements, for example:

- list = [1, 2, 3, 1]
- sort(list) = [1, 1, 2, 3]

After sorting, we can compare adjacent elements, so like list[0] and index[1], index[1] and index[2]... in conclusion we would have to compare every element of index[n] and index[n+1].

In this case, sorting takes $O(nlog(n))$ at best, iterating through each pair takes $O(n)$, so the total time complexity is $O(nlog(n) + n)$, which is $O(n \log n)$.



We could also use a hash table in this question, for example, for every element that we iterated though, put it in a hashing algorithm as the key, and the value for the key as the value itself.

As we iterate through the array, the hash table (assume link hash table in this case) will be slowly filled up, if there is a hash collision, we continue checking down the current hash chain index to see if there is a duplicate value or not.

Iterating through the array takes $n$ steps, and hashing each element once takes another $n$ operations.  We also have to count the comparisons inside the bucket chains. If we check an average of $c$ entries per element, that's $cn$ chain comparisons in total. 

Assuming the hash table keeps $c$ bounded by a constant, the total is $O(n + n + cn) = O(n)$.


