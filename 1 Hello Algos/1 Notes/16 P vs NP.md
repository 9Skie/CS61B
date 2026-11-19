https://www.bilibili.com/video/BV1Ntxr6xE7Y

So first of all, what is the `P = NP` problem?

Say we had an array of elements, and we were asked to do:
- summation
- find the smallest element
- sort them
- find two subsets that are equal

![[Screenshot 2026-11-12 at 8.39.45 PM.jpg|500]]


Summation is the simplest, we just keep a sum and add from the 1st element to the last.

![[Screen Recording 2026-11-12 at 8.43.49 PM.mov.gif|500]]


Finding the smallest is equivalently simple, we just start from the 1st element, and compare all the way until the last element.

![[Screen Recording 2026-11-12 at 8.44.28 PM.mov.gif|500]]


Sorting, on the other hand would be more complicated, for example, we would look at all the $n$ elements in the array, and put the smallest in the front, then look at the $n-1$ elements... until we are down to $0$ unsorted elements.

![[Screen Recording 2026-11-12 at 11.10.49 PM.mov.gif|500]]


But the sum being even on both sides for 2 different subsets... this is a different problem on its own, there's no real algorithmic way we can try to do this fast, and the best we can try is to just simply arrange numbers here and there until we hit both sides being equal.

![[Screenshot 2026-11-12 at 11.13.52 PM.jpg|500]]


For the computer, this is exactly what it does, for every number, it decides that 'should this number go in the left/right pile'? And since there are 10 of such decisions to make, this branches out more and more.

![[Screen Recording 2026-11-12 at 11.18.02 PM.mov.gif|500]]



So now, looking at these operations, we feel like they have different levels of complexity, in the sense that as the number of values, n, grows, how many more steps of computation are needed for these operations?

- It's roughly $n$ for sum / finding smallest
- It's roughly $n^2/2$ for sorting (there are better ones)
- It's roughly $2^n$ for the left = right problem


Why $2^n$? Well, every time we have a new number added, the work would double entirely.

![[Screen Recording 2026-11-12 at 11.42.50 PM.mov.gif|500]]



This is the beginning of again, revising time complexity of algorithms, complexity analysis.

There's always 3 cases for an algrorithm:
- best case, the fewest number of steps it possibly can take to achieve it's goal
- average case, 
- worst case, the most number of steps it possibly can take to achieve it's goal

![[Screenshot 2026-11-13 at 1.03.03 PM.jpg|500]]

It's almost like uh, gacha game gambling (or probability distributions), theoretically, you could get the in one pull, the community tested about on average it takes to get an character, and you have the worst case of eating pity.

![[Pasted image 20261113130248.png|500]]


But how do we actually describe the complexity of an algorithm? It could look like a very complicated equation, and in that case, how would we measure any of it?

![[Screenshot 2026-11-13 at 1.04.44 PM.jpg|500]]


Let's consider these 2 algorithms with the following complexities:

![[Screenshot 2026-11-13 at 1.08.05 PM.jpg|500]]


- $f(n) = 3n^2 \log_2 n + 5n + 7$
- $g(n) = n^3 - n$


As we can see, once $n$ is sufficiently large enough (beyond a certain point $n_0$, $g(n)$ stays above $f(n)$, and the ratio $g(n)/f(n)$ grows without bound as $n$ increases.

![[Screen Recording 2026-11-13 at 1.18.24 PM.mov.gif|500]]


One way to compare how fast the two functions grow is to take the limit of $f(n)/g(n)$ as $n$ goes to infinity. 

For large $n$, the dominant terms are:
- $3n^2\log_2 n$ in $f(n)$
- $n^3$ in $g(n)$

So we get:
- $\lim_{n\to\infty}\frac{f(n)}{g(n)} = \lim_{n\to\infty}\frac{3n^2\log_2 n}{n^3} = \lim_{n\to\infty}\frac{3\log_2 n}{n} = 0$

This means $f(n)$ becomes arbitrarily small relative to $g(n)$ as $n$ increases, so $g(n)$ grows faster than $f(n)$.



Returning to our original questions about lists, we can now use Big O notation to describe the worst-case running times of these operations. Let $n$ be the number of elements in the list.

- Sum: $O(n)$
- Find Min/Max: $O(n)$
- Sort: $O(n^2)$

The thing in common of all of these time complexities is that they are all 'polynomial', like $n$, $n^2$, $n^3$... 
- More generally, we write these functions as $c \cdot n^k$

![[Screenshot 2026-11-13 at 5.34.54 PM.jpg|500]]

Functions with a higher order polynomial, like $n^4$, will always grow faster than a function with $n^3$ as it's highest order polynomial.

But those are not the only family of functions that description algorithm complexity growth, we could also have the exponential family curves, like $2^n$.

Compared to a polynomial function, $c \cdot n^k$, no matter how big we turn up the value of $c$ or $k$, $2^n$, at a certain point $n_0$, will inevitably become larger then  $c \cdot n^k$.

![[Screen Recording 2026-11-13 at 5.43.11 PM.mov.gif|500]]


And so, in 1965, with the discussion of computational complexity being more relevant as computer science develops as a field, they given this definition:
- If a problem can be solved in polynomial time, then it's considered `P: Polynomial Time`.
	- Like sum, finding min/max, sorting is all considered polynomial time


So, why is polynomial time considered efficient over exponential functions?

Polynomial time is considered efficient because of how the amount of work grows as the input gets larger.
- If an algorithm takes roughly $n^2$ steps, doubling the input size multiplies the work by $4$. 
- If it takes roughly $2^n$ steps, adding just **one** element doubles the work.


Also, polynomial time is **closed under these ways of combining algorithms**. This means that if the individual algorithms run in polynomial time, the combined algorithm still has a polynomial time bound.

- **Run them in sequence.** 
	- If two algorithms work on the same input and take at most $n^2$ and $n^3$ steps, the total is at most $n^2+n^3$ steps. Adding two polynomials gives another polynomial.
    
- **Run them in parallel.**
	- If both start at the same time and we wait for both to finish, the slower one determines the running time. Here the bound is $\max(n^2,n^3)=n^3$ for $n\ge1$.
    
- **Feed the output of one into the other.** 
	- Suppose the first algorithm takes at most $n^2$ steps and outputs at most $n^2$ items. The second takes at most $m^3$ steps on an input of $m$ items. Its input can now be as large as $n^2$, so we substitute $m=n^2$ into its time bound. The total is at most $n^2+(n^2)^3=n^2+n^6$ steps, which is still polynomial in the **original** input size $n$.

![[Screenshot 2026-11-13 at 6.18.44 PM.jpg|500]]


But... is the 'Equal-Sum Partition' a polynomial time problem? No, right? It seems like a non-polynomial time problem, as we just said that it's $2^n$, so it's not polynomial.

Though, could it be possible that we just haven't found a smarter idea that uses polynomial time?
- We don't have an answer for this problem yet lol


Sorting is one problem where we did find a faster algorithm. Selection sort repeatedly scans the remaining elements to find the smallest one, which takes $O(n^2)$ time. **Merge sort** sorts the same list in $O(n\log n)$ time even in the worst case.

The idea is to split the list in half, sort each half recursively, and then merge the two sorted halves. To merge them, we only need to compare the first remaining element of each half and take the smaller one. Across all the merges at a given level, we process $n$ elements. Since halving the list gives us about $\log_2 n$ levels, the total work is $O(n\log n)$.

![[Screen Recording 2026-11-13 at 7.08.19 PM.mov.gif|500]]

Linear programming is another example. The **simplex method** worked well in practice, but it could take exponential time in the worst case. In 1979, Khachiyan showed that the same problem could be solved in polynomial time using a different algorithm, the **ellipsoid method**.

This has happened with other problems too. For years, researchers doubted that some of these problems could be solved in polynomial time. Eventually, they discovered new algorithms that could.


To prove that Equal-Sum Partition is outside P, we would need to show that **every** algorithm that solves it lacks a polynomial worst-case time bound. That includes algorithms nobody has thought of yet.

There are infinitely many possible algorithms, so how could we prove something about all of them at once?

![[Screenshot 2026-11-13 at 7.27.03 PM.jpg|500]]

To show that Equal-Sum Partition is in P, we only need one algorithm that gives the correct answer on every input and runs in polynomial time even in the worst case.

To show that Equal-Sum Partition is outside P, we have to prove that every correct algorithm for the problem lacks a polynomial worst-case time bound. That includes algorithms nobody has thought of yet.


What if someone gives us a proposed split for Equal-Sum Partition? Once we know which pile each number goes in, we can add up the two piles and check whether their sums match.

Finding a solution and checking a proposed solution can take very different amounts of work. For some problems, checking an answer is easy even when finding one seems hard.

For example, suppose we’re asked to find two integers greater than $1$ whose product is $8{,}616{,}460{,}799$. Starting with just that number, we have to figure out what the factors could be. But if someone gives us $89{,}681$ and $96{,}079$, we can check their answer with a single multiplication.

![[Screenshot 2026-11-13 at 7.37.47 PM.jpg|500]]

The two tasks start with different information. To **find** a solution, we’re given the problem. To **verify** a solution, we’re given the problem and a candidate answer.


RSA encryption uses this asymmetry. Given two large prime numbers, we can quickly multiply them or check that they give a particular product. Given only the product, finding the original primes is believed to be hard for classical computers.

To set up RSA, we choose two large primes and multiply them. The product becomes part of the **public key**, which anyone can use to encrypt a message. We use the original primes to compute the **private key**, which lets us decrypt the message. Someone who could factor the public product could also compute the private key.

![[Pasted image 20261113194632.png|500]]


Now, this brings us to a more general question. Which problems let us verify a proposed solution in polynomial time, even when finding one seems much harder? That’s the idea that leads us to **NP**. **NP** stands for **nondeterministic polynomial time**. 

What does that mean? We have to understand a Turing machine.

A Turing machine has a tape divided into cells, a head that reads and writes one cell at a time, and an internal state. At each step, the machine looks up a rule using its current state and the symbol under its head. The rule tells it what to write, which way to move, and what state to enter next. 

![[Screen Recording 2026-11-13 at 9.36.27 PM.mov.gif|500]]

The table $\delta$ lists the machine’s rules. The **row** is the current state, and the **column** is the symbol under the head. Each cell tells us **what to write, which way to move, and what state to enter next**.
- $R$ means move one cell right
- $\sqcup$ means a blank cell.

|Current state|Reads $0$|Reads $1$|Reads $\sqcup$|
|---|---|---|---|
|$q_0$|$(0,R,q_0)$|$(0,R,q_1)$|$(\sqcup,R,q_{\mathrm{acc}})$|
|$q_1$|$(0,R,q_1)$|$(0,R,q_0)$|$(\sqcup,R,q_{\mathrm{rej}})$|


The machine starts in $q_0$ and scans from left to right.
- Reading a $0$ keeps it in the same state.
- Reading a $1$ switches it between $q_0$ and $q_1$.
- Reading a blank means it has reached the end. From $q_0$ it enters $q_{\mathrm{acc}}$ and accepts. From $q_1$ it enters $q_{\mathrm{rej}}$ and rejects.

For example, if the machine is in $q_0$ and reads a $1$, it follows $(0,R,q_1)$. It writes a $0$ over the $1$, moves right, and switches to $q_1$.


A simpler way to think about it is as a finite-state machine. We start in one state, and at each step, the current state and the symbol we read determine which state we go to next.


Now we can define **P** precisely. A decision problem is in **P** if there is a deterministic Turing machine and a fixed polynomial $p$ such that, for every input of length $n$, the machine halts within $p(n)$ steps and gives the correct **yes** or **no** answer.

For example, the machine in the table answers the question “Does this input contain an even number of $1$s?” It accepts for **yes** and rejects for **no**. It reads each of the $n$ bits once, then reads the blank and halts, so we can use $p(n)=n+1$.



In a **nondeterministic Turing machine**, the same current state and tape symbol can allow more than one rule. For example, if the machine is in $q_0$ and reads a $1$, one rule might keep it in $q_0$ while another sends it to $q_1$. Each allowed move starts a separate branch of the computation.

To decide whether the machine accepts, we ask whether **at least one branch** reaches the accept state. If every branch rejects, the machine rejects. The rule table gives us the possible moves, and acceptance depends only on whether an accepting branch exists.

A decision problem is in **NP** if a nondeterministic Turing machine gives the correct yes-or-no answer this way and **every branch** halts within $p(n)$ steps for some fixed polynomial $p$, where $n$ is the input length.

![[Screenshot 2026-11-13 at 10.20.28 PM.jpg|500]]

Imagine that whenever the machine has multiple possible moves, it splits into copies, one for each move. Each copy follows its own path, as if all the possibilities were being explored at the same time. If any copy accepts, the machine answers **yes**. If all copies reject, it answers **no**.


A **deterministic Turing machine** has one next move at each step, so it follows a single path to a yes-or-no answer. A **nondeterministic Turing machine** can have several possible moves at a step, so its computation can branch. It answers **yes** if any branch accepts and **no** if all branches reject.

An algorithm runs in **polynomial time** if a fixed polynomial $p(n)$ bounds its running time on every input of length $n$. If the worst-case running time has no polynomial upper bound, it is **non-polynomial**. The two machine models count steps differently.
- **P** contains the decision problems a deterministic machine can decide in polynomial time. Its single path must finish within $p(n)$ steps.
- **NP** contains the decision problems a nondeterministic machine can decide in polynomial time. Every branch must finish within $p(n)$ steps, so the bound applies to the longest branch.

A deterministic machine can simulate a nondeterministic machine by exploring its branches one at a time. Even if each branch takes polynomial time, there can be exponentially many branches, so this simulation can take exponential time. A different deterministic algorithm might decide the same problem in polynomial time.

That’s what **P vs. NP** asks. **Does every problem that a nondeterministic machine can decide in polynomial time also have a deterministic polynomial-time algorithm?** 
- To prove $P=NP$, we need to establish this for **every** problem in NP. 
- To prove $P\ne NP$, we need to find **one** problem in NP and prove that every deterministic algorithm that decides it takes non-polynomial time in the worst case.


There are infinitely many problems in NP. Could one problem capture the difficulty of all of them, so that determining whether it has a deterministic polynomial-time algorithm would settle the entire question?

![[Screenshot 2026-11-13 at 10.56.31 PM.jpg|500]]


Well, there's this idea that, we can convert an NP problem A into the format of another NP problem B. Then, in solving B, we automatically get a solution for A since A can be converted into a format written in B.

![[Screenshot 2026-11-13 at 11.54.33 PM.jpg|500]]

Therefore, we can take take all these different kinds of questions in NP and convert them into instances of the same problem using **polynomial-time reductions**.

![[Screenshot 2026-11-13 at 11.53.44 PM.jpg|500]]

Now, is there some problem which all possible NP problems can be reduced to? If there is, then we just need to prove that this one can be solved in $P$, or that it can't be solved in $P$ and that's it!


![[Screenshot 2026-11-13 at 11.56.43 PM.jpg|500]]

A problem like such is called an NP complete problem. But does it exist? Yes, it's called the SAT.


**SAT**, or **Boolean satisfiability**, is a decision problem about Boolean logic. We are given an expression containing variables connected by **AND** ($\land$), **OR** ($\lor$), and **NOT** ($\neg$). Each variable can be assigned either **true** ($1$) or **false** ($0$).

The question is: **Is there some assignment of values to the variables that makes the entire expression true?** If we imagine writing out its truth table, SAT asks whether **at least one row has a final output of $1$**. If such an assignment exists, the expression is called **satisfiable**, and the answer is **yes**. Otherwise, the answer is **no**.


**3-SAT** is SAT with a specific structure: **groups joined by AND, with three literals joined by OR inside each group**. Each group is called a **clause**, and a literal is a variable such as $x$ or its negation $\neg x$.

For example:

$(x\lor\neg y\lor z)\land(\neg x\lor y\lor w).$

We ask whether some assignment makes the entire expression true. This requires **at least one literal in every clause to be true**. The “3” refers to the literals per clause; there can be many variables and clauses.

Any SAT instance can be converted into a 3-SAT instance in polynomial time while preserving whether it is satisfiable. Therefore, **3-SAT is also NP-complete**.



The significance of **SAT and 3-SAT** is that **every problem in NP can be reduced to either of them in polynomial time**. If we found a polynomial-time algorithm for SAT or 3-SAT, we could convert another NP problem into that format and solve it. Since both the conversion and the solving take polynomial time, the entire process would take polynomial time.

Therefore, we would have polynomial-time algorithms for **every problem in NP**, proving **$P=NP$**.

NP-complete problems appear across many fields, including:
- **Operations planning and scheduling**
- **Chip design**
- **Biology**
- **Economics**
- **Voting-system design**

Although these problems describe very different situations, polynomial-time reductions connect their computational difficulty. A polynomial-time algorithm for SAT or 3-SAT would give us a way to solve the NP-complete problems in all these fields.

---

## In Conclusion

The **P vs. NP** question asks whether **every decision problem in NP can be solved by a deterministic algorithm in polynomial time**. Equivalently, is there a deterministic algorithm that solves **every instance of SAT or 3-SAT** in polynomial time?

The definitions are:

- **P:** Decision problems that a **deterministic Turing machine** can solve in polynomial time.
    
- **NP:** Decision problems that a **nondeterministic Turing machine** can solve in polynomial time. Equivalently, a **yes** answer has a polynomial-length certificate that a deterministic machine can verify in polynomial time.
    
- **NP-complete:** Problems that **belong to NP** and that **every problem in NP can be reduced to in polynomial time**. They therefore capture the difficulty of all NP problems.
    

If SAT or 3-SAT has a deterministic polynomial-time algorithm, then **$P=NP$**. If that algorithm is also fast in practice, it could provide practical solutions to many difficult problems across different fields. It would also threaten much of modern cryptography, which depends on specific computations being easy to perform but difficult for an attacker to reverse.


----

## A Bonus

A stronger conjecture is the **Exponential Time Hypothesis (ETH)**. It proposes that **solving 3-SAT requires exponential time in the worst case**, measured in the number of variables. No matter how clever the algorithm is, it cannot avoid exponential growth on the hardest inputs.
- This does **not** mean that an algorithm must literally test all $2^n$ assignments. It might reduce the running time to something like $1.3^n$, but that is still exponential.

However, on**October 26, 2026**, OpenAI announced a **claimed disproof of the Exponential Time Hypothesis**. The proposed algorithm can count exactly how many assignments satisfy a 3-SAT formula.

It has a running time as:
- $2^{n/\sqrt{\log n}}$

Although it is still written as a power of $2$, its exponent grows more slowly than $n$. Consequently, it grows more slowly than **every fixed exponential $c^n$, where $c>1$**. That makes it **subexponential**.

If correct, this would refute ETH, but it would not settle $P$ vs. $NP$ (yet). The claimed running-time bound is still superpolynomial. It would show that 3-SAT can be solved faster than ETH allows, without establishing a polynomial-time algorithm or a practically fast solver.

If correct, this would show that **there is more room for faster algorithms for 3-SAT and some related NP problems than ETH suggested**. Its techniques could inspire further improvements and provide new directions for research.

However, **this remains compatible with $P\ne NP$**: a problem could be solvable in subexponential time while still having no polynomial-time algorithm. Whether these ideas can eventually lead to polynomial-time solutions remains an open question. The result would challenge our understanding of **how difficult** these problems are, without establishing that $P=NP$ is within reach.









