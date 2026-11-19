As an intro to data structure/algos, an idea of learning these things is go dive head first into solving Leetcode questions.

But I like the big overview of things! Like, why do people give a shit about trees? Where does this algorithm show up? How did we generalize algorithms into categories? It's all stuff I wanted to know.

The main contents of this book are shown in Figure 0-1.

- **Complexity analysis:** Criteria and methods for evaluating data structures and algorithms, including how to calculate time and space complexity, common complexity classes, and examples.

- **Data structures:** Basic data types and ways to classify data structures. Definitions, advantages and disadvantages, common operations, common variants, typical applications, and implementations of arrays, linked lists, stacks, queues, hash tables, trees, heaps, graphs, and other data structures.

- **Algorithms:** Definitions, advantages and disadvantages, efficiency, use cases, problem-solving steps, and example problems for searching, sorting, divide and conquer, backtracking, dynamic programming, greedy algorithms, and more.

![[Hello Algos CN Python V1.3.jpg|500]]


And how do we algos after this book? Well, grind grind grind, and then... learn as you go.

---


We know algos without even learning them formally! A lot of the time.

Take the case of flipping open a dictionary and finding a word that starts with the letter R.

![[Pasted image 20260917102913.png|500]]

We probably flip the book to half, say it's m, we would keep flipping to the later part of the book, say if we over shot to u, we would flip back to earlier points of the book.
- You are doing somewhat of a binary search without knowing it yourself!

Or when you are playing some card game with other people, you likely don't like a messy hand, so you sort them out.

A simple idea is putting cards that are sorted and unsorted separately, and then we sort the cards that are unsorted one by one into the sorted pile.

![[Pasted image 20260917103459.png|500]]


## So What Is Algos/Data Structures?

In the above examples, we've already experienced both algos and data structures.
- algos: a way to formally solve a question with a series of steps in limited time.
- data structure: a way to formally structure and store data, usually for the easy of the execution of certain algorithms.

So, we can see how these concepts are intertwined. Algorithms often depend on data structures, and when designing data structures, we have to make compromises. If a data structure makes certain operations faster, it may make others slower. These are trade-offs.

- Data structures are the foundation of algorithms. Data structures provide algorithms with structured storage of data and methods for operating on data.

- Algorithms breathe life into data structures. Data structures themselves only store data information; combined with algorithms, they can solve specific problems.

- Algorithms can usually be implemented based on different data structures, but execution efficiency may vary greatly. Choosing the appropriate data structure is key.

![[Pasted image 20260917103929.png|500]]