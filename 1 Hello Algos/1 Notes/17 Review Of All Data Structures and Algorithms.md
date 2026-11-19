## 1 Complexity analysis foundations

Before reviewing individual data structures and algorithms, we need a way to describe how much work they do and how much memory they use.

**Complexity analysis** studies how these requirements grow as the input gets larger. 
- This helps us explain why an operation has a particular cost, instead of simply memorizing its complexity.

We first identify the **input size**. 
- For an array, $n$ usually means the number of elements. 
- For a graph, we often need two quantities: 
	- $V$, the number of vertices
	- $E$, the number of edges.


For **time complexity**, we count basic operations, such as comparing two values, updating a variable, or accessing an array element. 
- We treat these as constant-time operations when they work on fixed-size numbers or references.

We can express this work as a function $T(n)$, then describe its growth using **asymptotic notation**.
- If $T(n)=3n+5$, its growth is linear: the constant multiplier and extra five operations do not change that growth rate. We write $T(n)=\Theta(n)$. 

Basically:
- Big $O$ gives an upper bound on growth
- Big $\Omega$ gives a lower bound
- Big $\Theta$ gives a tight bound by describing both.

![[Pasted image 20261114200233.png|500]]

Inputs of the same size can still require different amounts of work. **Best-case**, **worst-case**, and **average-case** analysis describe the easiest input, the hardest input, and the expected cost under a stated distribution of inputs. 


For **space complexity**, we count the maximum amount of memory needed at the same time. We distinguish the storage occupied by a data structure from the **auxiliary space** an algorithm needs beyond its input. Temporary arrays and active recursive calls contribute to this extra space.

![[Pasted image 20261114200307.png|500]]

Throughout this review, we will derive these costs from the operations themselves: how often work repeats, how much work each repetition performs, and what must remain in memory. Loops, sums, and recurrence relations give us ways to express those counts.

- Input size: what $n$, $V$, $E$, and other parameters represent.
- Counting primitive operations.
- Sequential work, nested loops, and dependent loop bounds.
- Recursion: number of calls, work per call, and maximum recursion depth.
- Big $O$, Big $\Omega$, and Big $\Theta$.
- Best-case, average-case, and worst-case complexity.
- Storage space, auxiliary space, and recursion-stack space.
- How implementation choices affect complexity.

## 2 Data structures and their operations

| Data structure                          | Implementations and operations to review                                                                                                                                              |
| --------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Arrays**                              | Indexed access and update; size/capacity checks; traversal; append; insertion/deletion by shifting; copying; resizing                                                                 |
| **Linked list**                         | Node references; indexed access and update; traversal; size/empty checks; insertion; deletion; head/tail handling; finding a predecessor; copying                                     |
| **Doubly linked list**                  | Forward/backward traversal; indexed access/update; size/empty checks; insertion/deletion by reference or index; operations at either end; copying                                     |
| **Stack**                               | Array-backed and linked implementations; push; pop; peek; size; empty check; traversal/conversion                                                                                     |
| **Queue**                               | Linked implementation with front/rear pointers; circular-array implementation; enqueue; dequeue; peek; size; empty/full checks; wraparound                                            |
| **Deque**                               | Doubly linked and circular-array implementations; insertion, deletion, and peeking at both ends; size; empty/full checks; wraparound                                                  |
| **Hash table/map**                      | Hash computation; lookup; insertion/update; deletion; iteration; load factor; resizing and rehashing                                                                                  |
| **Separate chaining**                   | Bucket selection; searching a chain; inserting/updating entries; deleting entries                                                                                                     |
| **Open addressing with linear probing** | Probe sequences; insertion; lookup; deletion; handling removed slots                                                                                                                  |
| **Binary tree**                         | Node representation; construction; linking nodes                                                                                                                           |
| **Binary search tree**                  | Search; insertion; deletion with zero, one, or two children; minimum/maximum; successor/predecessor                                                                                   |
| **AVL tree**                            | Search, insertion, and deletion; stored heights; balance checks; single/double rotations; rebalancing                                                                                 |
| **B-tree**                              | Search; insertion; splitting and key promotion; deletion; borrowing/redistribution; merging; root changes                                                                             |
| **Binary heap**                         | Min-heaps and max-heaps; array indexing; peek; insertion; sift-up; extraction; sift-down; successive-insertion and bottom-up construction                                             |
| **Ordinary priority queue**             | Heap-backed insertion; peek-min/max; extract-min/max; size; empty check                                                                                                               |
| **Indexed priority queue**              | Heap and index/position mapping; insertion; membership; priority lookup; peek-min/max; decrease-key; increase-key; priority updates; deletion by index; extraction; size; empty check |
| **Graph: adjacency matrix**             | Construction; edge lookup; adding/removing edges and vertices; neighbor enumeration; storage                                                                                          |
| **Graph: adjacency list**               | Linked-neighbor and array-neighbor implementations; construction; edge lookup; adding/removing edges and vertices; neighbor enumeration; storage                                      |
| **Graph: edge list**                    | Construction; scanning; edge lookup; adding/removing edges; sorting edges                                                                                                             |

### 2.1 Arrays

An **array** stores elements in equal-sized slots next to one another in memory. Each slot has an index, so we can calculate an element's location directly.

- **Capacity $C$:** the number of slots in the current allocation. This capacity stays fixed until we replace that allocation.
- **Occupied size $n$:** the number of elements currently being used, where $0\le n\le C$. We track this separately when some slots are unused.
- **Indices:** the allocated slots run from $0$ to $C-1$. In the operations below, the occupied elements fill positions $0$ through $n-1$.
- **Storage space:** $\Theta(C)$ for fixed-size elements, including unused slots.

For example, `[12, 7, 20, _, _]` has capacity $C=5$ and occupied size $n=3$. The underscores represent unused slots. Inserting or deleting an element can change $n$ without changing the allocated capacity.

To hold more than $C$ elements, we need a larger allocation. An implementation can handle this automatically: when full, it allocates twice the capacity, copies the existing elements, and uses the new array. We use this doubling rule below, starting with at least one slot. Deletion does not automatically shrink capacity.

We assume that reading, writing, comparing, or copying one element takes constant time. Insertion and deletion preserve the order of the remaining elements.

![[array-structure-overview.png|500]]

#### Operations and time complexities

- **Access an element at a known index:** $\Theta(1)$.
- **Update an element at a known index:** $\Theta(1)$.
- **Read the stored size/capacity, check whether the array is empty/full:** $\Theta(1)$.
- **Traverse all $n$ occupied elements:** $\Theta(n)$.
- **Append an element:** $\Theta(1)$ with spare capacity; $\Theta(n)$ when growth is required.
- **Insert at index $i$:** $\Theta(n-i+1)$ without growth; $\Theta(n)$ when growth is required.
  - Insertion at the front takes $\Theta(n)$.
  - Insertion at the end takes $\Theta(1)$ if there is spare capacity.
- **Delete at index $i$, preserving order:** $\Theta(n-i)$.
  - Deletion at the front takes $\Theta(n)$.
  - Deletion at the end takes $\Theta(1)$.
- **Copy all $n$ occupied elements into an existing destination array:** $\Theta(n)$.
- **Replace the array with a larger, initialized array of capacity $C'$:** $\Theta(C'+n)$. Doubling a full array takes $\Theta(n)$.

#### Why each operation has this complexity

**1. Indexed access — $\Theta(1)$**

Because all slots have the same size and sit next to one another, the address of index $i$ is:

$\text{address}(A[i])=\text{base address}+i\times\text{element size}$

Calculating this address and reading the value take a fixed number of operations. Accessing the last element requires no traversal through the earlier elements, so the cost stays constant as the array grows.

![[Pasted image 20261114202551.png|500]]

**2. Indexed update — $\Theta(1)$**

Updating uses the same address calculation, then writes the new value into that slot. Replacing an existing value does not shift any elements or change the occupied size.

**3. Size, capacity, and empty/full checks — $\Theta(1)$**

When $n$ and $C$ are stored, retrieving either takes one read. Checking whether the array is empty compares $n$ with $0$; checking whether it is full compares $n$ with $C$.

**4. Traversal — $\Theta(n)$**

A full traversal visits every occupied element once. With constant work per visit, $n$ elements require $n$ visits, giving linear time. Scanning every allocated slot, including unused ones, would instead take $\Theta(C)$.

![[Pasted image 20261114202809.png|500]]

**5. Append — $\Theta(1)$ with spare capacity; $\Theta(n)$ when growth is required**

When $n<C$, we write the new element into slot $n$ and increment the size. No existing elements move, so this takes $\Theta(1)$ time.

When $n=C$, we first replace the array with one of capacity $2C$. Copying the $n$ existing elements and preparing the new storage take $\Theta(n)$ time because $C=n$. We then append the new element. That particular append therefore takes $\Theta(n)$ time.

![[dynamic-array-append.png|500]]

**6. Insertion — $\Theta(n-i+1)$ without growth; $\Theta(n)$ with growth**

To insert at index $i$, we shift the elements at indices $i$ through $n-1$ one position to the right, starting from the end so that we do not overwrite values we still need. This moves $n-i$ elements. We then write the new value and increment $n$.

With spare capacity, inserting at the front shifts all $n$ elements, giving $\Theta(n)$ time. Inserting at the end shifts none, giving $\Theta(1)$ time. If the array is full, allocating a larger array and copying the existing contents add $\Theta(n)$ work, even when inserting at the end.

Shift from right to left to make space, then write the new element. Capacity stays unchanged.

![[attachments/array-insertion-only.png|500]]

**7. Deletion — $\Theta(n-i)$**

Deleting the element at index $i$ leaves a gap. To preserve order and keep the occupied elements together, we shift the following $n-i-1$ elements one position to the left, then decrement $n$.

- Deleting the first element shifts $n-1$ elements, giving $\Theta(n)$ time.
- Deleting the last element, often called **pop**, requires no shifts, giving $\Theta(1)$ time.

Capacity stays unchanged under our no-shrink rule. The newly unused slot remains available for a later insertion.

Remove the value, shift later elements left, and reduce the size. Capacity stays unchanged.

![[attachments/array-deletion-only.png|500]]

**8. Copying — $\Theta(n)$**

Copying the occupied contents reads and writes each of the $n$ elements once. Constant work per element gives $\Theta(n)$ total work. This assumes that the destination already has enough allocated space. Unused slots do not need to be copied.

The destination already exists. Copy each occupied source element once; no allocation or initialization is included in this operation.

![[attachments/array-copy-only.png|500]]

**9. Replacing the array with a larger one — $\Theta(C'+n)$**

The current allocation does not grow in place. We create a separate array with capacity $C'$, initialize its slots, copy the $n$ existing elements, and update the reference to use the new array. The occupied size stays the same during this replacement.

Initialization takes $\Theta(C')$ and copying takes $\Theta(n)$, so the combined cost is $\Theta(C'+n)$. When we double a full array, $C'=2C=2n$, and this simplifies to $\Theta(n)$.

![[Pasted image 20261114204009.png|500]]

### 2.2 Linked list

A **linked list** stores its elements in nodes. Each node contains a **value** and a **next reference** pointing to the following node. The nodes do not need to sit next to one another in memory; the references determine their order.

- **Head:** a reference to the first node. An empty list has `head = null`.
- **Last node:** its `next` reference is `null`, marking the end.
- **Size $n$:** the number of nodes containing elements.
- **Optional stored fields:** a `tail` reference gives direct access to the last node, and a size counter avoids recounting the nodes.
- **Storage space:** $\Theta(n)$ for fixed-size values and references.

For example, `head → 12 → 7 → 20 → null` represents three nodes connected in that order. Index $2$ means the third node, but its memory address cannot be calculated from the head's address.

![[linked-list-structure-overview.png|500]]

#### Operations and time complexities

- **Access an element at index $i$ by walking from the head:** $\Theta(i+1)$, or $\Theta(n)$ in the worst case. Access through an existing node reference takes $\Theta(1)$.
- **Update an element:** $\Theta(1)$ with its node reference; $\Theta(i+1)$ when first locating index $i$ from the head.
- **Check whether the list is empty:** $\Theta(1)$. **Read its size:** $\Theta(1)$ with a stored counter; $\Theta(n)$ if the nodes must be counted.
- **Traverse all $n$ nodes:** $\Theta(n)$.
- **Insert at the head:** $\Theta(1)$.
- **Insert after a known node:** $\Theta(1)$.
- **Append at the end:** $\Theta(1)$ with a maintained tail reference; $\Theta(n)$ without one in the worst case.
- **Delete the head:** $\Theta(1)$.
- **Delete the node after a known predecessor:** $\Theta(1)$.
- **Insert or delete at index $i$, starting from the head:** $\Theta(i+1)$, or $\Theta(n)$ in the worst case. Finding the predecessor of a known node can also take $\Theta(n)$.
- **Delete the last node:** $\Theta(n)$ in the worst case, even with a tail reference.
- **Copy the list into separate nodes:** $\Theta(n)$, using a running tail reference while building the copy.

#### Why each operation has this complexity

**1. Access — $\Theta(i+1)$ from the head; $\Theta(1)$ with a node reference**

To reach index $i$, we start at the head and follow `next` exactly $i$ times, then read the value. This gives $\Theta(i+1)$ work. The first element takes constant time to access; reaching the last from the head takes linear time.

If we already have a reference to the required node, we can read its value directly. A stored tail reference similarly allows direct access to the last node.

![[linked-list-access.png|500]]

**2. Update — depends on whether the node is already known**

Replacing a known node's value takes $\Theta(1)$ time and leaves every link unchanged. If only an index is provided, walking to that node adds $\Theta(i+1)$ work. Updating the value is cheap; reaching it determines the total cost.

**3. Empty and size checks — depend on stored information**

Checking `head == null` takes $\Theta(1)$ time. Reading a maintained size counter also takes $\Theta(1)$, and updating that counter after insertion or deletion adds only constant work. Without the counter, obtaining the size requires visiting all $n$ nodes, taking $\Theta(n)$ time.

**4. Traversal — $\Theta(n)$**

Starting at the head, we visit each node and follow its `next` reference until reaching `null`. There are $n$ visits, each requiring constant work, so the total is linear.

**5. Insertion at the head — $\Theta(1)$**

Set the new node's `next` reference to the current head, then change `head` to the new node. The existing nodes stay where they are in memory and keep their links. These changes take constant time regardless of the list's length. If the list was empty and we maintain a tail, the new node becomes the tail too.

**6. Insertion after a known node — $\Theta(1)$**

Suppose `p` is the node after which we want to insert. First set `new.next = p.next`, preserving the link to the rest of the list. Then set `p.next = new`. Only two references change, so the insertion takes constant time. If `p` was the tail, update the tail reference as well.

![[linked-list-insert.png|500]]

**7. Append — $\Theta(1)$ with a tail; $\Theta(n)$ without one**

With a maintained tail reference, appending is insertion after that known node: link the old tail to the new node, whose `next` is `null`, then update the tail. An empty list instead sets both head and tail to the new node.

Without a tail reference, we must first follow links from the head until finding the last node. That walk takes $\Theta(n)$ time; attaching the new node afterward takes $\Theta(1)$.

**8. Deleting the head — $\Theta(1)$**

Move `head` to `head.next`. This removes the first node from the chain without moving any others. If it was the only node, the list becomes empty, and a maintained tail must also become `null`.

**9. Deletion after a known predecessor — $\Theta(1)$**

Suppose `p` is immediately before the node to remove. Let `removed = p.next`, then set `p.next = removed.next`. This makes the chain bypass the removed node. Only a constant number of references change. If the removed node was the tail, the new tail is `p`.

![[linked-list-delete.png|500]]

**10. Insertion or deletion by index — $\Theta(i+1)$ from the head**

For an operation at index $i>0$, first walk to index $i-1$, the predecessor. Then perform the constant-time link changes described above. The walk determines the overall cost. At index $0$, we use the head operations directly.

Having only a reference to a node we want to remove does not generally give us its predecessor: the node stores only `next`. We may need to walk from the head until finding the node whose `next` points to the target, which takes $\Theta(n)$ in the worst case.

**11. Deleting the last node — $\Theta(n)$ in the worst case**

Even with a tail reference, we need the node immediately before the tail so that we can set its `next` to `null` and make it the new tail. There is no link pointing backward from the old tail. Finding that predecessor requires walking from the head, so removing the last node can take linear time. If its predecessor is already known, this becomes the constant-time operation in item 9.

The tail reference gives the last node, but finding its predecessor still requires walking from the head: $\Theta(n)$ in the worst case. Once found, changing one link and the tail reference takes $\Theta(1)$.

![[attachments/linked-list-tail-deletion.png|500]]

**12. Copying — $\Theta(n)$**

Visit each source node once, create a corresponding destination node, and link it after the previous destination node. Keeping a reference to the last node of the growing copy makes each attachment constant-time, giving $\Theta(n)$ total time and $\Theta(n)$ new storage. Merely copying the head reference would still refer to the original nodes.

### 2.3 Doubly linked list

A **doubly linked list** stores a value and two references in each node: **next** points to the following node, and **prev** points to the preceding node. We can follow the chain in either direction.

- **Head and tail:** stored references to the first and last nodes.
- **Ends:** `head.prev = null` and `tail.next = null`. An empty list has both `head = null` and `tail = null`.
- **Size $n$:** a maintained counter of the stored nodes.
- **Storage space:** $\Theta(n)$ for fixed-size values and references.

For example, `12 ↔ 7 ↔ 20` contains three nodes. From the node holding `7`, we can directly reach both neighbors. Reaching that node from an index may still require walking through the list.

We assume constant-time operations on values and references, including allocating or releasing one fixed-size node. Indexed operations start from whichever end is nearer.

![[doubly-linked-list-structure-overview.png|500]]

#### Operations and time complexities

- **Access a known node or either of its neighbors; peek at either end:** $\Theta(1)$.
- **Access index $i$, where $0\le i<n$:** $\Theta(\min(i,n-1-i)+1)$; $\Theta(n)$ in the worst case.
- **Update a value:** $\Theta(1)$ with its node reference; $\Theta(\min(i,n-1-i)+1)$ when locating index $i$ first.
- **Read the size or check whether the list is empty:** $\Theta(1)$.
- **Traverse all nodes forward or backward:** $\Theta(n)$.
- **Insert at either end:** $\Theta(1)$.
- **Insert before or after a known node:** $\Theta(1)$.
- **Delete a known node:** $\Theta(1)$.
- **Delete either end:** $\Theta(1)$.
- **Insert at position $i$, where $0\le i\le n$:** $\Theta(\min(i,n-i)+1)$; $\Theta(n)$ in the worst case.
- **Delete index $i$:** $\Theta(\min(i,n-1-i)+1)$; $\Theta(n)$ in the worst case.
- **Copy the list into separate nodes:** $\Theta(n)$, using a running tail reference.

#### Why each operation has this complexity

**1. Known-node and end access — $\Theta(1)$**

A node reference gives direct access to its value, `prev`, and `next`. Stored head and tail references give the same direct access to the end nodes. Each operation performs a fixed number of reads.

**2. Indexed access — $\Theta(\min(i,n-1-i)+1)$**

Index $i$ is $i$ links from the head and $n-1-i$ links from the tail. We take the shorter route, then read the value. Both ends are directly accessible, but reaching a node near the middle still takes linear time.

**3. Update — depends on whether the node is known**

Replacing a known node's value takes $\Theta(1)$ time without changing its links. If only an index is given, locating the node adds the walking cost from item 2.

**4. Size and empty checks — $\Theta(1)$**

Reading the stored size takes one read; checking whether it equals zero takes one comparison. Incrementing or decrementing the counter after a change also takes constant time.

**5. Traversal — $\Theta(n)$**

Starting at the head, follow `next` through all nodes. Starting at the tail, follow `prev` instead. Either direction visits each of the $n$ nodes once, with constant work per visit.

**6. Insertion at either end — $\Theta(1)$**

At the front, connect the new node to the old head in both directions, then update head. At the back, connect it to the old tail and update tail. An empty list sets both references to the new node. Only a fixed number of references change.

**7. Insertion beside a known node — $\Theta(1)$**

To insert after `p`, save `q = p.next`. Set `new.prev = p` and `new.next = q`, then set `p.next = new` and, if `q` exists, `q.prev = new`. If `q` is null, update tail instead. Insertion before a known node uses the corresponding links on its other side. Neither operation walks through the list.

**8. Deleting a known node — $\Theta(1)$**

For node `x`, its neighbors are immediately available as `p = x.prev` and `q = x.next`. Connect `p.next` to `q` and `q.prev` to `p`, skipping either assignment when that neighbor is null. Update head or tail when removing an end. These constant-time changes bypass `x` in both directions.

![[doubly-linked-list-delete.png|500]]

**9. Deleting either end — $\Theta(1)$**

Removing the head makes `head.next` the new head and clears its `prev` if it exists. Removing the tail makes `tail.prev` the new tail and clears its `next` if it exists. Removing the only node sets both head and tail to null. The backward reference makes finding the tail's predecessor immediate.

**10. Insertion by position — $\Theta(\min(i,n-i)+1)$**

First reach the insertion position from the nearer end, then perform the constant-time link changes from item 7. The end positions $0$ and $n$ are handled directly. Middle insertion costs time because of the walk, not because existing nodes must move.

**11. Deletion by index — $\Theta(\min(i,n-1-i)+1)$**

First locate index $i$ using item 2, then unlink that known node using item 8. Unlinking is constant-time; locating the node determines the total cost.

**12. Copying — $\Theta(n)$**

Visit each source node, create its copy, and connect the destination nodes in both directions. Maintaining the copy's tail makes each attachment constant-time. There are $n$ nodes to copy, giving $\Theta(n)$ time and $\Theta(n)$ new storage.

### 2.4 Stack

A **stack** follows **Last In, First Out (LIFO)**: the most recently added element is the first one removed. Both insertion and removal happen at the **top**. For example, pushing `12`, then `7`, then `20` makes `20` the top; successive pops return `20`, `7`, and `12`.

- **Linked-list representation:** the head is the top. Each node points to the element below it.
- **Array representation:** the last occupied position is the top. With $n$ elements, its index is $n-1$; capacity $C$ includes unused slots.
- **Stored information:** maintain the top reference or index and the current size. An array also stores its capacity.
- **Storage space:** $\Theta(n)$ for linked nodes; $\Theta(C)$ for an array.

We assume constant-time operations on individual values and references, including allocating or releasing one fixed-size node. An array can have a fixed capacity or double when full. We assume **no automatic shrinking after a pop**.

![[stack-structure-overview.png|500]]

#### Operations and time complexities

- **Push:** $\Theta(1)$ with linked nodes or spare array capacity; $\Theta(n)$ when the array must grow.
- **Pop:** $\Theta(1)$.
- **Peek at the top without removing it:** $\Theta(1)$.
- **Read size or check whether empty:** $\Theta(1)$.
- **Check whether a bounded array stack is full:** $\Theta(1)$.
- **Traverse all elements or copy their contents into a separate sequence:** $\Theta(n)$.

#### Why each operation has this complexity

**1. Push — $\Theta(1)$, or $\Theta(n)$ when an array grows**

With linked nodes, make the new node point to the old top, then update the top reference and size. Only a fixed number of references change, regardless of how many elements are already present.

With spare array capacity, write the new value at index $n$ and increment the size. Existing elements stay in place, so this also takes constant time.

If a resizable array is full, allocating a doubled array and copying the $n$ existing elements takes $\Theta(n)$ time. The new element is then added at the end. A fixed-capacity stack instead rejects a push when full; checking that condition takes constant time.

**2. Pop — $\Theta(1)$**

With linked nodes, save the top value, advance the top reference to the next node, and decrement the size. With an array, save the value at index $n-1$ and decrement the size. The remaining elements require no shifting. Because the array does not shrink automatically, neither representation needs to copy the remaining contents.

![[stack-push-pop.png|500]]

**3. Peek — $\Theta(1)$**

Peek reads the top node's value or the array value at index $n-1$. The top is directly available, so no traversal is needed. The stack remains unchanged. Both peek and pop first check whether the stack is empty; an empty stack has no value to return.

**4. Size, empty, and full checks — $\Theta(1)$**

Reading a stored size takes constant time. An array stack can also derive it from its top index. Empty means $n=0$, and a bounded array stack is full when $n=C$. Each check compares stored values; it does not examine the elements.

**5. Traversal and copying — $\Theta(n)$**

Visiting all contents requires examining every element once. For linked nodes, follow references from the top downward; for an array, visit its $n$ occupied positions. Building a separate sequence takes $\Theta(n)$ time and $\Theta(n)$ additional storage when each element is copied once into allocated output space. Reversing that sequence to present the opposite order adds another linear pass, leaving the total $\Theta(n)$. Returning a reference to existing storage does not create an independent copy.

### 2.5 Queue

A **queue** follows **First In, First Out (FIFO)**: elements join at the rear and leave from the front. The element that has waited longest is removed first.

- **Front:** the oldest element, which the next dequeue removes.
- **Rear:** the newest element, after which the next enqueue adds a value.
- **Size $n$:** a stored count of the elements currently in the queue.
- **Linked implementation:** maintain both a front/head reference and a rear/tail reference. The nodes occupy $\Theta(n)$ space.
- **Circular-array implementation:** use an array of capacity $C\ge1$, a front index $f$, and the occupied size $n$. Its storage is $\Theta(C)$, and indices wrap around at the end.

We assume constant-time operations on individual values, indices, and references, including allocating or releasing one fixed-size node. The circular-array queue here has fixed capacity and rejects insertion when full. Growing it is a separate implementation choice.

![[queue-structure-overview.png|500]]

#### Operations and time complexities

- **Enqueue at the rear:** $\Theta(1)$ for the linked queue or a circular array with spare capacity. Rejecting an enqueue into a full bounded array also takes $\Theta(1)$.
- **Dequeue from the front:** $\Theta(1)$.
- **Peek at the front:** $\Theta(1)$.
- **Read the stored size or check whether the queue is empty:** $\Theta(1)$. Checking whether the circular array is full also takes $\Theta(1)$.
- **Traverse or copy the $n$ queued elements in FIFO order:** $\Theta(n)$.
- **Optional growth of a full circular array by doubling:** $\Theta(n)$ for that enqueue.

#### Why each operation has this complexity

**1. Enqueue — $\Theta(1)$ without growth**

In a linked queue, the maintained rear reference already identifies the last node. Create a new node, link it after the rear, then update the rear reference and increment $n$. If the queue was empty, both front and rear point to the new node. No traversal is needed.

In a circular array with spare capacity, the next insertion position is $(f+n)\bmod C$. Write the value there and increment $n$. The modulo operation wraps the position back to the beginning when necessary, allowing space freed by earlier dequeues to be reused. Calculating one index and writing one element take constant time.

**2. Dequeue — $\Theta(1)$**

In a linked queue, read the front value, move `front` to `front.next`, and decrement $n$. If the removed node was the only node, set both front and rear to `null`. Only a fixed number of references change.

In a circular array, read `A[f]`, set `f = (f + 1) % C`, and decrement $n$. The other elements stay in their existing slots: changing which index marks the front removes the need to shift them. An empty queue rejects the operation after a constant-time check.

![[queue-wraparound.png|500]]

**3. Peek — $\Theta(1)$**

After checking that the queue is nonempty, read the linked front node's value or the circular array's `A[f]`. Neither implementation changes any links, indices, or elements. The stored front gives direct access.

**4. Size, empty, and full checks — $\Theta(1)$**

Reading the maintained counter gives $n$ directly. The queue is empty when $n=0$; the bounded circular array is full when $n=C$. These checks require only a read and a comparison, rather than counting elements.

**5. Traversal and copying — $\Theta(n)$**

For a linked queue, follow `next` from the front, visiting each node once. For a circular array, the element at logical position $j$ is `A[(f + j) % C]`, for $j=0,1,\ldots,n-1$. This visits the elements in FIFO order even when they cross the end of the array.

There are $n$ visits, each with constant work. Copying adds one value copy per visit into a destination array, or creates nodes while maintaining a destination tail. Both take $\Theta(n)$ time; a separate copy also needs $\Theta(n)$ new storage.

**6. Optional growth — $\Theta(n)$ when the array is full**

A growing implementation can replace a full array with one of capacity $2C$. Copy the queued values in logical order: place `A[(f + j) % C]` into `B[j]`, then reset $f$ to $0$. The next enqueue writes at index $n$.

Because the old array is full, $n=C$. Initializing the doubled array and copying all $n$ elements take $\Theta(n)$ total time. This cost applies only when growth is supported; the fixed-capacity implementation rejects the enqueue instead.

A wrapped queue is copied in logical order, not physical array order. Here the old indices $2,3,0,1$ become new indices $0,1,2,3$. Initializing $2n$ slots and copying $n$ values takes $\Theta(n)$.

![[attachments/circular-array-growth.png|500]]

### 2.6 Deque

A **deque**, pronounced “deck,” is a **double-ended queue**: elements can be added or removed at either the front or the rear. Using only one end gives stack behavior; adding at one end and removing at the other gives queue behavior.

- **Doubly linked representation:** maintain front and rear references. Each node has both `next` and `prev`, so either end can reach its neighbor directly.
- **Circular-array representation:** maintain an array of capacity $C\ge1$, a front index $f$, and the size $n$. The rear element is at index $(f+n-1)\bmod C$ when the deque is nonempty.
- **Size:** a maintained count of the stored elements.
- **Storage space:** $\Theta(n)$ for linked nodes; $\Theta(C)$ for an array.

We assume constant-time operations on individual values, indices, and references, including allocating or releasing one fixed-size node. A bounded array rejects insertion when full. A growing version can double its capacity; we assume it does not shrink automatically after removal.

![[deque-structure-overview.png|500]]

#### Operations and time complexities

- **Push at the front or rear:** $\Theta(1)$ with linked nodes or spare array capacity; $\Theta(n)$ when a full array grows.
- **Pop from the front or rear:** $\Theta(1)$.
- **Peek at the front or rear:** $\Theta(1)$.
- **Read size or check whether empty:** $\Theta(1)$.
- **Check whether a bounded array deque is full:** $\Theta(1)$.
- **Traverse or copy all elements in order:** $\Theta(n)$.

#### Why each operation has this complexity

**1. Push at the front — $\Theta(1)$ without growth**

With linked nodes, connect the new node to the old front in both directions, then update front. If the deque was empty, the new node becomes both front and rear.

With a circular array, move the front index backward using $f=(f-1+C)\bmod C$, then write the new value at `A[f]`. This wraps from index $0$ to index $C-1$ when necessary. Increment $n$. Existing elements stay in place, so no shifting is required.

**2. Push at the rear — $\Theta(1)$ without growth**

With linked nodes, connect the new node after the old rear in both directions, then update rear. Again, an empty deque sets both end references.

With a circular array, write at index $(f+n)\bmod C$, then increment $n$. This is the next free slot after the current rear. Both representations change only a fixed number of values or references.

![[deque-both-ends.png|500]]

**3. Pop from the front — $\Theta(1)$**

With linked nodes, save the front value, advance front to `front.next`, and clear the new front's `prev` if it exists. With a circular array, save `A[f]` and advance $f$ to $(f+1)\bmod C$. Decrement $n$.

No elements need to move. In the linked representation, removing the only node sets both front and rear to `null`.

**4. Pop from the rear — $\Theta(1)$**

With linked nodes, save the rear value, move rear to `rear.prev`, and clear the new rear's `next` if it exists. The backward reference gives immediate access to the predecessor; there is no walk from the front. Removing the only node clears both ends.

With a circular array, save the value at index $(f+n-1)\bmod C$, then decrement $n$. The front index stays unchanged. Without automatic shrinking, neither implementation copies or shifts the remaining contents.

**5. Peek at either end — $\Theta(1)$**

Read the linked front or rear node's value, or the array at index $f$ or $(f+n-1)\bmod C$. Each endpoint is directly available. Peek and pop first check that the deque is nonempty.

**6. Size, empty, and full checks — $\Theta(1)$**

Read the maintained size. Empty means $n=0$; a bounded array is full when $n=C$. Comparing these stored values does not require traversing the deque.

**7. Traversal and copying — $\Theta(n)$**

Follow `next` from the linked front, or visit `A[(f + j) % C]` for $j=0,1,\ldots,n-1$. Each method visits all $n$ elements in order. Building an independent copy adds constant work per element and uses $\Theta(n)$ additional storage. A linked copy maintains its own rear reference while attaching nodes.

**8. Growth — $\Theta(n)$ when a full array doubles**

Copy the elements in logical order into an array of capacity $2C$, starting at index $0$, and reset $f=0$. Since the old array was full, $n=C$, so allocating the new storage and copying the elements take $\Theta(n)$ time. Then perform the requested front or rear insertion using the rules above. A bounded deque instead rejects insertion when full.

The wrapped-array growth diagram in [[#2.5 Queue|Queue]] shows the same copying step.

### 2.7 Hash table

A **hash table**, or **hash map**, stores key-value pairs. Given a key, we compute a position in a bucket array, then locate the matching entry using the table's collision-handling rule. Each key has one associated value; storing that key again replaces its value.

- **Capacity $C$:** the number of buckets or slots, with $C\ge1$.
- **Size $n$:** the number of stored key-value pairs.
- **Bucket index:** $h(k)=\operatorname{hash}(k)\bmod C$.
- **Collision:** different keys produce the same bucket index. Their entries must remain distinguishable.
- **Load factor $\alpha=n/C$:** the number of entries relative to the available buckets.
- **Storage space:** $\Theta(C+n)$ with linked chains; $\Theta(C)$ with open addressing.

For example, with $h(k)=k\bmod5$, `20:C` belongs to bucket $0$, `12:A` to bucket $2$, and `8:B` to bucket $3$.

We assume fixed-size keys and constant-time hashing, equality checks, and value operations. Hashing a string of length $L$ can instead take $\Theta(L)$, and comparing strings can also depend on their lengths. The expected bounds for individual key operations require suitable hashing and a controlled load factor, and exclude rebuilding the table.

![[hash-table-overview.png|500]]

#### Operations and time complexities

- **Compute a bucket index:** $\Theta(1)$ under the stated key assumptions.
- **Look up a key or test membership:** expected $\Theta(1)$; worst-case cost depends on collision handling.
- **Insert a new key or update an existing key:** expected $\Theta(1)$ without rebuilding.
- **Remove an entry by key:** expected $\Theta(1)$ without rebuilding.
- **Read size, capacity, or load factor; check whether empty:** $\Theta(1)$.
- **Visit or collect all entries, keys, or values:** $\Theta(C+n)$ with linked chains; $\Theta(C)$ with open addressing.
- **Rebuild into capacity $C'$:** expected $\Theta(C+C'+n)$ for the implementations below; their worst-case bounds differ.

#### Why each operation has this complexity

**1. Bucket calculation — $\Theta(1)$**

For a fixed-size key, computing its hash and reducing it modulo $C$ require a fixed amount of work. The resulting index gives direct access to a bucket.

**2. Lookup and membership — expected $\Theta(1)$**

After finding the bucket, compare actual keys while following the collision rule. A matching hash alone does not establish that two keys are equal. With suitable hashing and controlled occupancy, the expected number of inspected entries is constant. Long chains or probe sequences increase the cost.

**3. Insertion and update — expected $\Theta(1)$**

First check whether the key already exists. If it does, replace its value without increasing $n$. Otherwise, store a new entry and increment $n$. The collision-handling work determines the total; the final value or reference update takes constant time.

**4. Removal — expected $\Theta(1)$**

Locate the matching key, then remove it using the representation's deletion rule and decrement $n$. Removing an absent key leaves the table unchanged. The following sections explain why linked chains and probe sequences require different deletion rules.

**5. Stored information — $\Theta(1)$**

Read the maintained values of $n$ and $C$. Empty means $n=0$, and the load factor is one division, $n/C$. No entries need to be counted again.

**6. Traversal — includes scanning the bucket array**

To visit every entry, inspect the table's $C$ positions. With chaining, also follow all $n$ linked entries, giving $\Theta(C+n)$. Open addressing keeps entries directly in the slots, giving $\Theta(C)$.

**7. Rebuilding — entries need new positions**

Changing capacity changes the bucket calculation. Rebuilding prepares $C'$ destination slots, scans the old storage, and places every entry according to the new capacity. Moving entries requires collision handling again, so the rebuild bound depends on the method used.

The rehashing diagram in [[#2.8 Separate-chaining hash table|Separate-chaining hash table]] shows why entries need new bucket positions.

### 2.8 Separate-chaining hash table

**Separate chaining** stores a linked list of entries at each bucket. Keys with the same bucket index coexist in that list. Each node holds a key, its value, and a reference to the next entry.

- **Bucket array:** $C$ head references; an empty bucket contains `null`.
- **Size $n$ and load factor $\alpha$:** maintain $n$ and $C$, with $\alpha=n/C$.
- **Selected chain length $b$:** the number of entries in the bucket used by an operation.
- **Storage space:** $\Theta(C+n)$ for bucket heads and entry nodes.

For $h(k)=k\bmod5$, bucket $2$ can contain `12:A → 7:B → 22:C → null`. Chaining allows $n$ to exceed $C$: buckets can hold multiple entries. We assume constant-time operations on individual keys, values, and nodes.

![[hash-chaining-overview.png|500]]

#### Operations and time complexities

- **Lookup or membership:** expected $O(1+\alpha)$; $\Theta(n)$ in the worst case.
- **Insert a key or update its value:** expected $O(1+\alpha)$ without resizing; $\Theta(n)$ in the worst case.
- **Prepend an entry whose key is already known to be absent:** $\Theta(1)$.
- **Remove an entry by key:** expected $O(1+\alpha)$; $\Theta(n)$ in the worst case. Unlinking after its predecessor is known takes $\Theta(1)$.
- **Read size, capacity, or load factor; check whether empty:** $\Theta(1)$.
- **Traverse all entries:** $\Theta(C+n)$.
- **Rehash directly into capacity $C'$:** $\Theta(C+C'+n)$, using constant-time prepending without duplicate checks. This is $\Theta(n)$ when $C,C'=\Theta(n)$.

The expected key-operation bounds assume well-distributed hashing. If $\alpha$ stays bounded by a constant, each operation takes expected $\Theta(1)$ time: the upper bound is constant, and even accessing a bucket requires constant work.

#### Why each operation has this complexity

**1. Lookup and membership — depend on the selected chain**

Compute the bucket index, then follow its nodes while comparing keys. An immediate match takes $\Theta(1)$; checking an entire chain of length $b$ takes $\Theta(1+b)$. With well-distributed hashing, the expected chain work is bounded by a constant multiple of $1+\alpha$. If all $n$ keys collide, one chain can contain every entry, giving a linear worst case.

**2. Insertion and update — check the chain first**

A normal map insertion must check for an existing key. On a match, replace the value. If the key is absent, create and link a new entry, then increment $n$. The check can examine all $b$ entries, even though the final linking takes constant time. Our linked implementation appends after completing this walk; prepending afterward has the same overall bound.

**3. Known-new insertion — $\Theta(1)$**

If we already know that the key is absent, set the new node's `next` to the bucket's head and replace the head with the new node. Computing the bucket and changing these references take constant time. This shortcut does not include checking whether the key exists.

**4. Removal — locate, then unlink**

Walk through the selected chain while retaining the previous node. On a match, make that predecessor bypass the removed node. Removing the first node instead updates the bucket head. Unlinking and decrementing $n$ take constant time; locating the key gives the expected $O(1+\alpha)$ and worst-case $\Theta(n)$ costs.

**5. Size, empty, and load checks — $\Theta(1)$**

Reading the maintained counters and computing $n/C$ require constant work. A nonempty bucket does not mean the table is full: another node can be linked into its chain.

**6. Traversal — $\Theta(C+n)$**

Inspect all $C$ bucket heads and visit every linked entry once. There are $n$ entry visits altogether, regardless of how unevenly they are distributed. Empty buckets still contribute to the bucket scan.

**7. Direct rehashing — $\Theta(C+C'+n)$**

Prepare the new bucket array and scan the old one. For each entry, save its old `next`, compute its new bucket, and prepend it to that bucket. The existing keys are already unique, so duplicate checks are unnecessary.

Each node moves once with constant work, even if every key lands in one new chain. The total is the old scan, new bucket preparation, and $n$ moves. Calling ordinary `put` for every entry can instead repeat chain scans and take quadratic time under severe collisions.

Rehashing scans the $C$ old buckets, prepares $C'$ new buckets, and moves each of the $n$ entries once using direct prepending. That gives $\Theta(C+C'+n)$; the bucket index must be recomputed using the new capacity.

![[attachments/chained-hash-rehash.png|500]]

### 2.9 Open-addressing hash table: linear probing

**Open addressing** keeps entries directly in an array. With **linear probing**, a collision makes us inspect the next slot, wrapping around at the end: $h(k),(h(k)+1)\bmod C,(h(k)+2)\bmod C,\ldots$.

- **EMPTY:** no entry has occupied this slot since the last rebuild. It ends an unsuccessful lookup.
- **LIVE:** the slot contains a current key-value pair.
- **DELETED:** a removed entry left a **tombstone**. Lookups continue past it; insertions may reuse it.
- **Counts:** $n$ live entries, $d$ tombstones, and capacity $C$. Maintaining these counts allows constant-time size and occupancy checks.
- **Occupancy:** the live load is $n/C$; $(n+d)/C$ also matters because tombstones do not stop probing.
- **Storage space:** $\Theta(C)$.

With $h(k)=k\bmod7$, inserting `10:A`, `17:B`, and `24:C` places them at slots $3$, $4$, and $5$. Deleting `17` leaves a tombstone at $4$, so a lookup for `24` can still reach slot $5$.

We assume fixed-size keys and constant-time slot operations. Expected constant-time bounds require suitable hashing and live-plus-tombstone occupancy kept below a fixed threshold less than $1$. Adjacent occupied slots form clusters that can lengthen probes even when the live load looks modest.

![[hash-linear-probing-overview.png|500]]

#### Operations and time complexities

- **Lookup or membership:** expected $\Theta(1)$ under those conditions; $\Theta(C)$ in the worst case.
- **Insert or update:** expected $\Theta(1)$ without rebuilding; $\Theta(C)$ in the worst case.
- **Delete by key:** expected $\Theta(1)$ without rebuilding; $\Theta(C)$ in the worst case. Marking a known live slot deleted takes $\Theta(1)$.
- **Read size, capacity, load, or tombstone count; check whether empty/full:** $\Theta(1)$ with maintained counts.
- **Traverse all live entries:** $\Theta(C)$.
- **Rebuild into capacity $C'$:** expected $\Theta(C+C'+n)$ with suitable hashing and destination load; collision-heavy reinsertion can take $O(C+C'+n^2)$.

#### Why each operation has this complexity

**1. Lookup and membership — count the probes**

Start at the key's hash index. At a LIVE slot, compare the stored key with the requested key. Continue past nonmatching entries and tombstones. A matching live entry succeeds; EMPTY proves that the key is absent along this probe sequence.

Stop after at most $C$ inspected slots even if no EMPTY slot appears. Wrapping back to the starting position means a full cycle has been checked. Each probe takes constant time, so a probe sequence of length $p$ costs $\Theta(p)$ and the worst case is $\Theta(C)$.

**2. Insertion and update — remember a tombstone, but continue**

During probing, remember the first DELETED slot. Continue comparing live keys: the same key may already exist later in the sequence. If found, update its value without changing $n$.

After reaching EMPTY, insert into the remembered tombstone if there is one; otherwise use that empty slot. A full cycle can also establish absence, allowing reuse of a remembered tombstone. If all slots are LIVE and the key is absent, insertion must fail or trigger growth. Reusing a tombstone increments $n$ and decrements $d$.

A tombstone is only a possible insertion position. Continue probing to find an existing key or establish absence at an empty slot; then update the match or reuse the remembered tombstone. The final write is constant work, but finding its position costs the number of probes.

![[attachments/probing-insert-past-tombstone.png|500]]

**3. Deletion — preserve the probe path**

Locate the key using the lookup rule, then change its slot from LIVE to DELETED, decrement $n$, and increment $d$. Clearing it to EMPTY could make a later lookup stop before reaching a displaced entry. Locating the slot determines the cost; changing its state takes constant time.

![[hash-probing-tombstone.png|500]]

**4. Stored counts — $\Theta(1)$**

Read $n$, $d$, and $C$ directly. Empty means $n=0$; no insertion space remains when $n=C$. Having no EMPTY slots is different: if tombstones exist, they can still be reused after checking for a duplicate key.

**5. Traversal — $\Theta(C)$**

Inspect every slot and process only LIVE entries. EMPTY and DELETED slots are skipped, but still inspected. Consequently, traversal depends on capacity even if few live entries remain.

**6. Clustering and rebuilding**

Linear probing forms contiguous runs of entries. Keys hashing into a run must walk through it, and new insertions can extend or join runs. This **primary clustering** is why the expected bounds depend on the hash behavior and occupancy; they are not guaranteed for every table state.

Rebuilding scans all $C$ old slots, prepares $C'$ new slots, and reinserts only the $n$ live entries. Tombstones disappear. With suitable hashing and a controlled destination load, reinserting each entry takes expected constant time, giving $\Theta(C+C'+n)$ overall.

Under severe collisions, successive insertions may probe $1,2,\ldots,n$ slots. Their sum is quadratic, giving $O(C+C'+n^2)$ for rebuilding. This differs from directly prepending nodes during a chained-table rehash.

### 2.10 Binary tree

A **binary tree** stores values in nodes, each with a **left** and a **right** child reference. Either reference can be `null`, so a node has at most two children. A plain binary tree imposes no ordering on its values.

- **Root:** the top node; `root = null` means the tree is empty.
- **Size $n$:** the number of nodes.
- **Height $h$:** the number of edges on the longest root-to-leaf path. A single-node tree has height $0$.
- **Depth of a node:** the number of edges from the root to that node; the root has depth $0$.
- **Storage space:** $\Theta(n)$ for fixed-size values and references.

We assume constant-time operations on individual values and references, including releasing one fixed-size node. Direct link changes below assume that the relevant references are already known and that the resulting structure remains a tree.

![[binary-tree-overview.png|500]]

#### Operations and time complexities

- **Read or update a known node's value; follow one child reference:** $\Theta(1)$.
- **Attach or detach a subtree through a known child reference:** $\Theta(1)$ for the link change. Releasing all $k$ detached nodes takes $\Theta(k)$.
- **Check whether the tree is empty:** $\Theta(1)$. **Read its size:** $\Theta(1)$ with a stored counter; $\Theta(n)$ if counting the nodes.
- **Compute the tree's height:** $\Theta(n)$. Reading a correctly maintained height field takes $\Theta(1)$.
- **Compute all node depths or the tree's maximum depth:** $\Theta(n)$.

#### Why each operation has this complexity

**1. Access and update through known references — $\Theta(1)$**

A node reference gives direct access to its value and child fields. Reading a value, replacing it, or following `left` or `right` requires a fixed number of operations. Reaching a node from the root is separate work; nodes have no array-style index from which their addresses can be calculated.

**2. Attaching and detaching — $\Theta(1)$ for the link change**

Attaching a subtree sets one child reference to its root. Detaching it sets that reference to `null`. The subtree's nodes remain where they are in memory. If those nodes must also be released, every one of the $k$ nodes needs processing, taking $\Theta(k)$ time. Counting them to adjust a size counter also takes $\Theta(k)$ unless that count is already known.

**3. Empty and size checks — depend on stored information**

Checking `root == null` or reading a maintained size counter takes constant time. Without the counter, obtaining the size requires visiting and counting all $n$ nodes.

**4. Computing height — $\Theta(n)$**

A node's **height** is the number of edges on its longest downward path to a leaf. The **height of the whole tree** is the height of its root. We count edges: a path containing three nodes has two edges, so its height is $2$.

A leaf has height $0$, because there are no edges below it. To calculate an internal node's height, first calculate the heights of its children:

$h(\text{node})=1+\max(h(\text{left}),h(\text{right})).$

The **maximum** chooses the longer downward path. The **$+1$** counts the edge from the current node to the child on that path. We assign an empty subtree (`null`) height $-1$, so a leaf correctly gives $1+\max(-1,-1)=0$.

We apply the same procedure recursively:

1. If the current node is `null`, return $-1$.
2. Calculate the left child's height using this procedure, then calculate the right child's height.
3. Return one plus the larger result.

The calls begin at the root, but the answers are worked out **from the leaves upward**: a parent cannot calculate its height until its children's heights are known.

For the tree drawn above:

- Leaves `30`, `2`, and `20` each have height $0$.
- Node `7` has height $1+\max(0,0)=1$.
- Root `12` has height $1+\max(1,0)=2$. Therefore, the tree's height is **$2$**.

![[tree-height-calculation.png|500]]

Without stored heights, we must examine both subtrees to determine which path is longest. Every node is processed once, with constant work combining its children's results, giving **$\Theta(n)$ time**. The recursive calls use $O(n)$ stack space in the worst case: the tree can form a single chain of $n$ nodes, keeping $n$ calls active.

If heights are already correctly stored, **reading** a height takes $\Theta(1)$. **Refreshing one node's height** also takes $\Theta(1)$ when its children's stored heights are correct; changes may still require refreshing ancestors.

For a tree with more than two children per node, use the same rule: one plus the maximum height among all children.

**5. Computing depth — $\Theta(n)$ for all nodes**

A node's **depth** is the number of edges from the root to that node. The root has depth $0$, its children have depth $1$, and their children have depth $2$.

We calculate depth **from the root downward**. Whenever we follow an edge to a child, add one:

$d(\text{root})=0,\qquad d(\text{child})=d(\text{parent})+1.$

To calculate every node's depth and the tree's **maximum depth**:

1. Start at the root with depth $0$ and a maximum of $0$.
2. At the current node, compare its depth with the maximum and keep the larger value.
3. Repeat steps 2–3 for each existing child, passing the current depth plus one. When all nodes have been processed, return the largest depth recorded.

For the tree above:

- Root `12` has depth $0$.
- Nodes `7` and `20` have depth $1$.
- Nodes `30` and `2` have depth $2$.

![[tree-depth-calculation.png|500]]

The maximum depth is therefore **$2$**. For a nonempty tree, **maximum node depth equals the tree's height**, since both count the edges on a longest root-to-leaf path. With our convention, an empty tree returns $-1$ before starting this procedure.

Depth and height can differ at an individual node: node `20` has depth $1$, but height $0$ because it is a leaf. Also, the levels in the original notes start at $1$, so a node's level is its depth plus one.

Computing all depths, or finding the maximum this way, processes each node once with constant work, giving **$\Theta(n)$ time**. The recursive calls use $O(n)$ stack space in the worst case, for the same chain-shaped tree described in the height calculation. This calculation passes depths downward; the earlier height calculation combines child heights upward.

### 2.11 Binary search tree

A **binary search tree (BST)** adds an ordering rule to the binary-tree structure: every key in a node's **left subtree is smaller** than its key, and every key in its **right subtree is larger**. This applies to entire subtrees, not just the immediate children.

- **Keys:** we use distinct keys; inserting an existing key leaves the tree unchanged.
- **Root and children:** a root reference and each node's left/right references describe the tree.
- **Size $n$:** a maintained count of the nodes.
- **Height $h$:** measured in edges, as above. It determines how far a comparison-guided operation may travel.
- **Storage space:** $\Theta(n)$ for fixed-size keys and references.

We assume constant-time key comparisons and node operations. This BST does not automatically balance itself. Its height can be logarithmic when well balanced, or $n-1$ when the nodes form one long path. Therefore, a path operation has an $O(h+1)$ bound: it is not automatically $O(\log n)$.

![[binary-search-tree-overview.png|500]]

#### Operations and time complexities

- **Search for a key:** $O(h+1)$; a match at the root takes $\Theta(1)$.
- **Access a known node or update its associated payload:** $\Theta(1)$. Changing its key requires preserving the ordering rule, normally through deletion and insertion.
- **Read the stored size or check whether the tree is empty:** $\Theta(1)$.
- **Insert a key:** $O(h+1)$.
- **Delete a key:** $O(h+1)$, covering nodes with zero, one, or two children.
- **Find the minimum or maximum:** $O(h+1)$.
- **Find a node's successor or predecessor:** $O(h+1)$, using parent links or a path from the root.

#### Why each operation has this complexity

**1. Searching — $O(h+1)$**

Compare the target key with the current node. Equality finds the key; a smaller target continues left, and a larger target continues right. The ordering rule eliminates the other subtree. Reaching `null` means the key is absent.

The walk follows one path and inspects at most $h+1$ nodes. It can finish sooner, so this is an upper bound. A balanced tree limits the path to $O(\log n)$ nodes; an unbalanced tree can require $\Theta(n)$ visits.

**2. Direct access and payload updates — $\Theta(1)$**

With a node reference, reading its fields takes constant time. If entries also have associated payloads, changing a payload leaves their key order intact. Arbitrarily changing the key can violate that order, so replacing a key generally requires deleting the old key and inserting the new one.

**3. Empty and size checks — $\Theta(1)$**

Check whether the root is `null`, or read the stored node count. Successful insertion increments the count, and successful deletion decrements it. Duplicate insertion and deletion of an absent key leave the count unchanged.

**4. Insertion — $O(h+1)$**

Follow the same comparison-guided path as searching. If the key already exists, stop. Otherwise, the first `null` child reference identifies where the new node belongs. Attaching it takes constant time; locating that position determines the overall cost. In an empty tree, the new node becomes the root.

**5. Deletion — $O(h+1)$**

First locate the key and retain its parent. The remaining changes depend on its children:

- **Zero children:** set the parent's corresponding child reference to `null`.
- **One child:** make the parent point directly to that child, bypassing the removed node.
- **Two children:** find the smallest key in the right subtree by moving right once, then repeatedly left. This is the inorder successor. Copy its key and any associated payload into the target node, then remove the successor from its original position.

The successor has no left child, so its removal reduces to one of the first two cases. When removing the root, update the root reference instead of a parent's child reference. The link changes take constant time, while locating the target and any successor takes $O(h+1)$ total time.

![[bst-delete-two-children.png|500]]

**6. Minimum and maximum — $O(h+1)$**

The minimum is the leftmost node: keep following `left` until no left child remains. The maximum similarly follows `right`. Each operation follows one path, whose length is bounded by the height.

**7. Successor and predecessor — $O(h+1)$**

The successor is the next larger key. If a right subtree exists, take its minimum. Otherwise, ascend to the first ancestor whose left subtree contains the node. Parent links allow this ascent; without them, a search from the root can retain the relevant ancestor candidate. The predecessor reverses left and right to find the next smaller key. Either procedure follows a bounded number of tree paths and may finish before reaching height $h$.

### 2.12 AVL tree

An **AVL tree** is a binary search tree that keeps the heights of each node's two subtrees within one of each other. Rotations restore this condition after insertion or deletion while preserving the ordering of the keys. Consequently, the tree's height remains $O(\log n)$ even in the worst case.

- **Node contents:** a key, left and right child references, and a stored height.
- **Height convention:** an empty subtree has height $-1$; a leaf has height $0$.
- **Balance factor:** $h(\text{left})-h(\text{right})$. Every node must have balance factor $-1$, $0$, or $1$ after an operation finishes.
- **Storage:** $\Theta(n)$ for $n$ nodes. A recursive operation or recorded ancestor path uses up to $O(\log n)$ additional space.

We assume distinct keys, constant-time comparisons and node operations, and correctly maintained heights. A stored total-size counter is optional.

![[avl-tree-overview.png|500]]

#### Operations and time complexities

- **Search, minimum/maximum, successor/predecessor:** $O(\log n)$ worst-case time.
- **Insert or delete a key:** $O(\log n)$ worst-case time.
- **Read a stored height, compute a balance factor, or refresh one node's height:** $\Theta(1)$.
- **Perform one single or double rotation:** $\Theta(1)$.
- **Traverse all nodes:** $\Theta(n)$.
- **Check whether empty:** $\Theta(1)$. **Read total size:** $\Theta(1)$ with a maintained counter; $\Theta(n)$ by counting nodes.

#### Why each operation has this complexity

**1. Height and balance information — $\Theta(1)$ per node**

Refresh a node's height using $1+\max(h(\text{left}),h(\text{right}))$. Both child heights are already stored, so this takes constant time. Computing the balance factor also reads two stored values. Repeatedly traversing the subtrees to calculate their heights would lose this advantage.

The balance rule forces a tall tree to contain many nodes. If $N(h)$ is the smallest possible node count at height $h$, its children must have heights at least $h-1$ and $h-2$, giving $N(h)=1+N(h-1)+N(h-2)$. This grows exponentially with $h$, so height can grow only logarithmically with $n$.

**2. Search and ordered queries — $O(\log n)$**

Search follows the ordinary BST comparisons down one path. Minimum follows left children; maximum follows right children. Successor and predecessor use the corresponding subtree or an ancestor candidate, just as in a BST. Each operation follows at most a constant number of height-length paths. The AVL height bound makes their worst-case cost logarithmic.

If upward movement is needed, use parent references, a recorded ancestor path, or a search from the root. A node reference alone does not provide its ancestors.

**3. Rotations — $\Theta(1)$**

A right rotation raises a node's left child, moves the old node below it on the right, and transfers the raised child's old right subtree to the old node's left. Only a few references change; the transferred subtree is not traversed. Reconnect the new subtree root to its parent and refresh the affected heights from the bottom upward. A left rotation mirrors these steps.

Choose the repair from the unbalanced node and its taller child:

- **Left-left:** balance $+2$, left child's balance $\ge0$; rotate right.
- **Left-right:** balance $+2$, left child's balance $<0$; rotate that child left, then the node right.
- **Right-right:** balance $-2$, right child's balance $\le0$; rotate left.
- **Right-left:** balance $-2$, right child's balance $>0$; rotate that child right, then the node left.

A double rotation is two constant-time rotations, so it also takes $\Theta(1)$.

![[avl-right-rotation.png|500]]

**4. Insertion — $O(\log n)$**

Find the insertion position as in a BST, attach the new leaf, and work back toward the root, refreshing heights and checking balance. Linking the leaf takes constant time once its parent is known; locating that parent and checking ancestors determine the total cost.

Insertion needs at most one rebalancing site: a single or double rotation at the lowest unbalanced ancestor restores that subtree's previous height. Higher ancestors therefore need no further rotations. The search and height checks still take $O(\log n)$ time.

**5. Deletion — $O(\log n)$**

Use the BST cases: remove a leaf, replace a one-child node with its child, or replace a two-child node's key with its successor/predecessor and remove that replacement key from its original position. Then refresh heights and repair balance along the affected ancestor path.

Deletion can shorten a repaired subtree, so several ancestors may need rotations. There are only $O(\log n)$ ancestors, and each repair costs $\Theta(1)$. The entire operation therefore remains $O(\log n)$, including locating the key and any replacement.

After deleting $50$, node $30$ is left-heavy while its left child is right-heavy. A left rotation at $10$ followed by a right rotation at $30$ repairs this subtree in $\Theta(1)$ work. Deletion can require checking and repairing ancestors along an $O(\log n)$ path.

![[attachments/avl-deletion-double-rotation.png|500]]

**6. Traversal and size — $\Theta(n)$ or a stored $\Theta(1)$ query**

An inorder traversal visits every node once and produces sorted keys. Other full traversals also take $\Theta(n)$. Counting during traversal has the same cost; reading a maintained total-size counter takes $\Theta(1)$. Checking whether the root is `null` also takes $\Theta(1)$.

### 2.13 B-tree

A **B-tree** stores several sorted keys in each node. An internal node with $k$ keys has $k+1$ children, whose key ranges are separated by those keys. All leaves have the same depth, so every root-to-leaf path has the same length.

Let the tree's **order $m\ge3$** be its maximum number of children per internal node:

- **Non-root nodes:** between $\lceil m/2\rceil-1$ and $m-1$ keys after an operation finishes.
- **Root:** at least one key when nonempty, and at most $m-1$ keys. A non-leaf root has at least two children; an empty tree can have an empty leaf root.
- **Internal children:** exactly one more than the node's key count; non-root internal nodes therefore have between $\lceil m/2\rceil$ and $m$ children.
- **Height:** $h=O(\log_{\lceil m/2\rceil}(n+1))$, where $n$ counts all keys.
- **Storage:** $\Theta(n)$ for fixed $m$, including spare capacity inside nodes.

For example, order $5$ allows at most four keys per node and requires at least two in every non-root node. We use distinct keys and ignore duplicate insertions. Assume constant-time key comparisons and array storage within nodes. Distinguish **visiting a node** from **processing its keys**: one node may occupy one disk page, but scanning or shifting its contents can take $O(m)$ CPU work.

![[b-tree-overview.png|500]]

#### Operations and time complexities

- **Search:** $O(h+1)$ node visits; $O(m(h+1))$ time with linear scans inside nodes.
- **Minimum/maximum:** $O(h+1)$ time and node visits.
- **Successor/predecessor from a key:** $O(m(h+1))$ with linear scans.
- **Insert/delete:** $O(h+1)$ page accesses; $O(m(h+1))$ CPU time.
- **Split, borrow, or merge:** $O(m)$ CPU work per repair; a constant number of affected nodes.
- **Traverse all keys:** $\Theta(n)$.
- **Read stored size/height:** $\Theta(1)$; otherwise count keys in $\Theta(n)$ or follow one root-to-leaf path for height in $\Theta(h+1)$.

For fixed $m$, the search and update bounds simplify to $O(\log n)$.

#### Why each operation has this complexity

**1. Search and ordered queries — one path through the levels**

Compare the target with the current node's sorted keys. Either find it there or choose the child whose range contains it. At most $h+1$ nodes are visited, with up to $O(m)$ comparisons per node. Binary search within each node reduces search to $O((\log m)(h+1))$ comparisons, but does not remove the shifting work needed by updates.

Minimum and maximum follow the first or last child, then select the leaf's first or last key. Successor/predecessor can require locating the key, descending into an adjacent subtree, or following an ancestor candidate. Recording the path avoids needing to rediscover ancestors.

The height stays small because every non-root internal node has at least $\lceil m/2\rceil$ children. Each additional level therefore requires many more keys. When nodes occupy disk pages, this reduces the number of page accesses.

**2. Splitting and insertion — $O(m)$ work per visited level**

Find the appropriate leaf and insert the key in sorted order. If it now contains $m$ keys, it has overflowed. Split it around a middle key, promote that key into the parent, and keep the smaller and larger keys in separate nodes. Divide child references accordingly when splitting an internal node. Each resulting node satisfies the minimum key count.

For order $5$, an overflowing node `[5, 10, 15, 20, 25]` splits into `[5, 10]` and `[20, 25]`, promoting `15`. Moving keys and references, including shifts in the parent, takes $O(m)$ time.

The promoted key may overflow the parent, so repeat upward. If the root overflows, split it beneath a new root; this increases the height by one. At most one split occurs at each level, giving $O(m(h+1))$ CPU time and $O(h+1)$ page accesses.

![[b-tree-overflow-split.png|500]]

**3. Borrowing and merging — $O(m)$ per repair**

Deletion can leave a node below its minimum key count. If an adjacent sibling has more than its minimum, borrow through the parent: move the separating parent key down, move the sibling's boundary key up, and transfer a child reference when needed. Array entries may shift, costing $O(m)$.

If no adjacent sibling can spare a key, merge the deficient node with one sibling and their parent separator. The combined keys fit within the maximum. Remove that separator and the redundant child reference from the parent. Moving and shifting these arrays also costs $O(m)$; being local does not make the operation independent of node capacity.

With order $m=5$, each non-root node needs $2$–$4$ keys. After deleting $10$, the left leaf has only $1$ key. Borrowing moves separator $20$ down and sibling key $25$ up; shifting the affected key arrays costs $O(m)$.

![[attachments/b-tree-borrow-through-parent.png|500]]

**4. Deletion — $O(m(h+1))$**

For a leaf key, remove it and shift the later keys left. For an internal key, replace it with its predecessor or successor, then remove that replacement key from its original leaf. This preserves the ordering of the subtrees, but the leaf may now have too few keys.

Repair an underfull node by borrowing or merging. Borrowing ends that deficiency; merging removes a separator from the parent, which may then become underfull too. Continue upward as necessary. If the root loses its last key and has one child, that child becomes the root, decreasing the height.

Only a constant number of nodes are repaired at each level, giving the stated time and page-access bounds.

The sibling is already at its $2$-key minimum, so it cannot lend. Merge the deficient leaf, separator, and sibling into one $4$-key node. The empty root is replaced by its only child. Each repair costs $O(m)$ and can move upward through $h+1$ levels.

![[attachments/b-tree-merge-root-shrink.png|500]]

**5. Traversal and metadata**

An ordered traversal alternates between each node's children and separating keys, visiting only occupied entries. Every key is processed once, giving $\Theta(n)$ time. A maintained total-key counter and height can be read in $\Theta(1)$; height changes only when the root splits or shrinks. Recursive traversal uses $O(h+1)$ call frames, excluding any output sequence.

### 2.14 Binary heap

A **binary heap** keeps its tree filled from left to right, one level at a time, and stores those positions consecutively in an array. In a **min-heap**, every parent is at most its children; in a **max-heap**, every parent is at least its children. There is no ordering rule between siblings.

- **Size $n$:** the number of occupied array positions. Capacity $C$ may include unused positions.
- **Root:** index $0$, holding the minimum or maximum.
- **Children of index $i$:** $2i+1$ and $2i+2$, if those indices are below $n$.
- **Parent of index $i>0$:** $\lfloor(i-1)/2\rfloor$.
- **Storage:** $\Theta(C)$ for the allocated array; $\Theta(n)$ when capacity is proportional to size.

For example, the min-heap from the original notes has array `[0, 3, 1, 9, 4]`. Both `3` and `1` are at least their parent `0`; they do not need to be ordered relative to each other. Filling levels keeps every root-to-node path within $O(\log n)$ steps. We assume constant-time comparisons and no automatic shrinking after removal. For the array-backed structures below, growth replaces a full array with one of proportional capacity, such as doubling.

![[attachments/binary-heap-overview.png|500]]

#### Operations and time complexities

- **Peek, read size, or check whether empty:** $\Theta(1)$.
- **Read a known array position or calculate a parent/child index:** $\Theta(1)$.
- **Sift up or sift down:** $O(\log n)$; an immediate stop takes $\Theta(1)$.
- **Insert:** $O(\log n)$ with spare capacity; $\Theta(n)$ if a full backing array must grow.
- **Extract the root:** $O(\log n)$.
- **Change or remove an entry at a known heap index:** $O(\log n)$.
- **Build by successive insertions:** $O(n\log n)$ worst case with enough allocated capacity.
- **Build by bottom-up heap construction:** $\Theta(n)$.

#### Why each operation has this complexity

**1. Direct access and metadata — $\Theta(1)$**

The root is `A[0]`, and the size is stored. Parent and child locations require only arithmetic, so no pointer walk is needed to find an immediate relative.

**2. Insertion and sift-up — $O(\log n)$ without array growth**

Place the new element at index $n$, the next available tree position. In a min-heap, swap it with its parent while it is smaller. Stop when the parent is no larger or the element reaches the root. Each swap moves up one level and costs constant time. There are only logarithmically many levels. A max-heap reverses the comparisons.

If the array is full, allocating a larger array and copying its $n$ entries takes $\Theta(n)$ for that insertion. The subsequent sift-up does not change that linear bound.

Here the new value follows parent indices $6\to2\to0$. Each swap moves up one level; even the longest such path has only $O(\log n)$ levels.

![[attachments/heap-sift-up-steps.png|500]]

**3. Extraction and sift-down — $O(\log n)$**

Save the root value, move the last element into index $0$, and reduce the size. Compare the replacement with its children. In a min-heap, swap with the smaller child when necessary; choosing the larger child could leave a heap-order violation with the smaller one. Continue downward until the order is restored. At most a constant number of comparisons and one swap occur per level. Removing the only element takes constant time.

Removing the root leaves one displaced value. It follows indices $0\to2\to5$, swapping with the smaller child each time. The repair touches one path, not every node.

![[attachments/heap-sift-down-steps.png|500]]

**4. Updating or deleting a known position — $O(\log n)$**

After changing a priority, repair upward if it now precedes its parent; otherwise repair downward if a child should precede it. To remove an arbitrary known position, replace it with the last entry, reduce the size, and repair in the appropriate direction. Knowing the index avoids a separate search for the entry.

Deleting a known entry does not shift the rest of the array. Move the last entry into its place, then repair one path. Here the replacement is smaller than its new parent, so it moves upward.

![[attachments/heap-delete-known-position.png|500]]

**5. Building a heap — two different costs**

Successive insertion can move each new element through logarithmically many levels, giving $O(n\log n)$ worst-case work.

Bottom-up construction starts at index $\lfloor n/2\rfloor-1$, the last node with children, and sifts each node down while moving backward toward the root. Its child subtrees are already heaps when it is processed. About half the nodes are leaves and need no repair, about a quarter can move only one level, and about an eighth can move only two. The work is bounded by a constant multiple of $n(1/4+2/8+3/16+\cdots)$, giving $\Theta(n)$ total time. Iterative sift-down uses $\Theta(1)$ auxiliary space when rearranging the existing array.

In this 15-node heap, the maximum downward moves add to $8\cdot0+4\cdot1+2\cdot2+1\cdot3=11$. Most nodes are close to the leaves, so they cannot each cost $\log n$. The same weighted sum grows linearly with $n$.

![[attachments/heap-build-weighted-levels.png|500]]

### 2.15 Ordinary priority queue

A **priority queue** removes the entry with the highest priority, rather than the earliest arrival. A min-priority queue treats smaller numbers as better priorities; a max-priority queue treats larger numbers as better. Here it is implemented with a binary heap of `(item, priority)` entries.

- **Root:** the next entry to remove.
- **Size $n$:** the number of queued entries.
- **Storage:** $\Theta(n)$ when heap capacity is proportional to size.
- **Equal priorities:** their removal order is unspecified unless we also compare an insertion counter to break ties.

This ordinary queue has no maintained item-to-heap-position mapping. It can contain multiple entries for the same item, as in lazy Dijkstra.

![[attachments/priority-queue-overview.png|500]]

#### Operations and time complexities

- **Peek at the best entry; read size; check whether empty:** $\Theta(1)$.
- **Insert:** $O(\log n)$ with spare capacity; $\Theta(n)$ if the backing array grows.
- **Extract the best entry:** $O(\log n)$ without shrinking.
- **Locate an arbitrary item before changing its priority:** $\Theta(n)$ in the worst case; repairing its known heap position then takes $O(\log n)$.
- **Build a queue from $n$ entries using bottom-up heap construction:** $\Theta(n)$.

#### Why each operation has this complexity

**1. Peek and metadata — $\Theta(1)$**

The heap root already contains the best priority. Reading it or a stored size requires constant work. Peeking does not remove the entry.

**2. Insert and extract — $O(\log n)$ for heap repair**

Insertion appends an entry and sifts upward. Extraction replaces the root with the last entry and sifts downward. Their costs follow directly from the binary heap's logarithmic number of levels. Array growth remains a separate linear-cost event for insertion.

The sift-up and sift-down diagrams in [[#2.14 Binary heap|Binary heap]] show these same repairs.

**3. Updating an arbitrary item's priority — locating it can dominate**

Heap order identifies the best entry, but does not tell us where an arbitrary item is stored. Without an index mapping, locating that item may inspect all $n$ entries. Once found, changing its priority and repairing the heap takes $O(\log n)$, so the complete operation can still take $\Theta(n)$.

One alternative is to insert a new entry and let the consuming algorithm discard the older one later. That is the lazy approach used in the graph notes; it can increase the number of queue entries. The indexed queue below instead locates the existing entry directly.

### 2.16 Indexed priority queue

An **indexed priority queue** combines a binary heap with a mapping from each item ID to its current heap position. It supports direct membership and priority updates without creating duplicate entries for that ID.

- **`heap[i]`:** the item ID at heap position $i$.
- **`pos[id]`:** that item's heap position, or $-1$ if absent.
- **`priority[id]`:** the item's current priority.
- **Invariant:** `pos[heap[i]] = i`. Every heap swap must update both affected positions.

Assume IDs are integers in a fixed range $0,\ldots,U-1$, so the mapping uses directly indexed arrays. There are $n\le U$ queued items. Storage is $\Theta(U)$ for these arrays and a heap capacity of at most $U$. This is the representation used to explain eager Dijkstra's priority updates.

![[attachments/indexed-priority-queue-overview.png|500]]

#### Operations and time complexities

- **Membership, priority lookup, peek, size, or empty check:** $\Theta(1)$.
- **Insert an absent ID or extract the best entry:** $O(\log n)$.
- **Decrease-key, increase-key, or arbitrary priority update:** $O(\log n)$.
- **Delete an entry by ID:** $O(\log n)$.
- **Grow an exhausted backing array or ID range:** linear in the storage copied; excluded from the bounds above.

#### Why each operation has this complexity

**1. Membership and lookup — $\Theta(1)$**

Read `pos[id]` to check presence and find the entry's position. Read `priority[id]` for its priority. The best ID is `heap[0]`. These are direct array accesses, not walks through the heap.

**2. Insertion and extraction — $O(\log n)$**

For insertion, store the priority, put the ID at the heap's end, record its position, and sift upward. For extraction, remove the root ID and mark its position absent. If other entries remain, move the last ID to the root, set `pos[lastID] = 0`, reduce the size, and sift downward. Removing the only entry simply empties the queue. The initial position update is necessary even if no swap follows; every subsequent swap updates both affected mapping entries, adding constant work per level.

**3. Decrease-key and increase-key — $O(\log n)$**

In a min-priority queue, decreasing an item's priority can violate the order with its parent, so use `pos[id]` and sift upward. Increasing the priority can violate the order with its children, so sift downward. A general update chooses the direction from the change. A max-priority queue reverses these directions. Direct location plus a logarithmic repair gives the total bound.

Decreasing ID 0's priority from 7 to 1 causes one swap. Updating the two affected `pos` entries takes constant work. Repeating this along at most $O(\log n)$ levels keeps the whole update logarithmic.

![[attachments/indexed-queue-swap-update.png|500]]

**4. Deletion by ID — $O(\log n)$**

Locate the item through `pos`. If it is already last, shorten the heap and mark that ID absent. Otherwise, move the last ID into the vacated position and immediately set `pos[lastID]` to that position. Reduce the size, mark the removed ID absent, and repair the replacement upward or downward as needed. Updating the mapping before repair keeps it correct even when no swap is needed. Direct location avoids a linear search; repair follows one heap path.

The known-position deletion diagram in [[#2.14 Binary heap|Binary heap]] shows the replacement and repair; here, `pos` supplies that position directly.

### 2.17 Graph as an adjacency matrix

A graph has **$V$ vertices** and **$E$ edges**. An **adjacency matrix** stores a $V\times V$ array: `A[u][v]` records whether edge $u\to v$ exists, or records its weight.

- **Undirected graph:** store both `A[u][v]` and `A[v][u]`.
- **Weighted graph:** use a distinct no-edge marker; a weight of zero may be a real edge.
- **Vertex IDs:** directly identify rows and columns.
- **Storage:** $\Theta(V^2)$, even when few edges exist.

The example drawings use an undirected graph with edges `A–B`, `A–C`, and `B–D`. Preparing its matrix from a vertex list and edge list takes $\Theta(V^2+E)$: every matrix cell must be prepared, then the edges are recorded.

![[attachments/graph-adjacency-matrix-overview.png|500]]

#### Operations and time complexities

- **Check, add, remove, or change the weight of a known edge:** $\Theta(1)$.
- **Enumerate a vertex's neighbors:** $\Theta(V)$.
- **Inspect all possible edges:** $\Theta(V^2)$.
- **Add a vertex:** $\Theta(V)$ when existing rows have spare capacity; $\Theta(V^2)$ when matrix storage must be copied.
- **Remove a vertex by shifting rows and columns to preserve vertex order:** $\Theta(V^2)$ in the worst case.
- **Read maintained vertex/edge counts:** $\Theta(1)$.

#### Why each operation has this complexity

**1. Edge operations — $\Theta(1)$**

The endpoints directly identify a cell. Lookup reads it; insertion, removal, and weight changes write it. An undirected edge changes two cells, which is still constant work. A maintained edge count changes only when an edge actually appears or disappears.

**2. Neighbor enumeration — $\Theta(V)$**

Scan the vertex's entire row, checking every possible neighbor. Even a vertex with one neighbor still has $V$ possible positions to inspect. Scanning all rows costs $\Theta(V^2)$.

The same query does different amounts of work in each representation. To list C's neighbors, the matrix checks all $V$ positions, the adjacency list follows only C's entries, and the edge list checks every edge record.

![[attachments/graph-neighbor-scan-costs.png|500]]

**3. Adding a vertex — depends on allocation**

The new vertex needs a row and a column, together containing $2V+1$ new cells. If row arrays already have room, writing these cells takes $\Theta(V)$, matching the logical operation illustrated in the notes. If rows or a packed matrix must be replaced, copying the existing $V^2$ entries can make that insertion $\Theta(V^2)$. Adding a row and column does not guarantee that physical copying is free.

**4. Removing a vertex — $\Theta(V^2)$ worst case**

Delete its row and column. When preserving vertex order, later rows and column entries move to close the gaps. Removing a column near the beginning shifts up to $V$ entries in each of $V$ rows, producing quadratic work. Vertex-index changes must remain consistent with the vertex list.

Deleting B removes its row and column. Preserving the order forces later column entries to shift in every remaining row. Up to $V$ moves per row across $V$ rows gives $\Theta(V^2)$ worst-case work.

![[attachments/matrix-vertex-deletion-work.png|500]]

### 2.18 Graph as an adjacency list

An **adjacency list** stores one collection of neighbors per vertex. An entry can hold a neighbor ID and an edge weight. Neighbor collections may be linked lists or arrays; they do not need to use hashing.

- **Degree $d(u)$:** the number of entries in vertex $u$'s neighbor collection; for directed graphs this is its outdegree.
- **Undirected edges:** each edge appears in both endpoints' lists, giving $2E$ entries in total.
- **Directed edges:** each edge appears in its source's list, giving $E$ entries.
- **Storage:** $\Theta(V+E)$ when array capacities are proportional to their contents, or when using linked entries.

We use an array of vertex records with direct ID access, and ordinary linked or array neighbor lists. Building from $V$ vertices and $E$ edges takes $\Theta(V+E)$ with linked insertion or suitably reserved array storage. The following edge-removal bounds describe simple graphs without parallel edges.

![[attachments/graph-adjacency-list-overview.png|500]]

#### Operations and time complexities

- **Check whether $u\to v$ exists:** $O(d(u)+1)$; worst case scans the whole list.
- **Add a known-absent edge:** $\Theta(1)$ with linked insertion or spare array capacity. Checking for a duplicate first adds a list scan.
- **Grow a full neighbor array:** $\Theta(d(u)+1)$ for that insertion at $u$.
- **Remove $u\to v$ by endpoints:** $O(d(u)+1)$; for an undirected edge, $O(d(u)+d(v)+1)$.
- **Enumerate neighbors of $u$:** $\Theta(d(u)+1)$.
- **Inspect all vertices and edges:** $\Theta(V+E)$.
- **Add an isolated vertex:** $\Theta(1)$ with spare vertex-record capacity; $\Theta(V)$ if that array grows.
- **Remove a vertex and its incident edges:** $\Theta(V+E)$ worst case without a separate incoming-edge index.

#### Why each operation has this complexity

**1. Lookup and insertion — distinguish checking from attaching**

Locate vertex $u$ directly, then compare neighbor IDs until finding $v$ or reaching the end. The list may contain $d(u)$ entries. If an edge is already known to be absent, prepending a linked entry takes constant time; an array append does too when space is available. Requiring uniqueness means checking the list before attaching the new entry.

**2. Removal — find the entry before removing it**

With linked neighbors, retain the predecessor while locating the edge, then unlink it in constant time. With array neighbors, locating the entry and shifting later entries can each take linear time in that list's length. For an undirected graph, repeat at the other endpoint. The cost depends on the affected degrees, rather than automatically scanning every edge in the graph.

**3. Enumeration — inspect only stored neighbors**

Visiting one neighbor list takes constant setup plus one operation per entry. Across all vertices, the setup costs $V$ and the entries total $E$ or $2E$. Therefore, a complete scan takes $\Theta(V+E)$.

The neighbor-scan comparison in [[#2.17 Graph as an adjacency matrix|Graph as an adjacency matrix]] shows the different amounts of work for the same query.

**4. Vertex changes — incident edges matter**

Adding an isolated vertex attaches an empty neighbor collection. Removing a vertex also requires removing references to it from other collections. Without an incoming-edge index, scan the vertex records and neighbor entries, removing or compacting them in a pass. This takes $\Theta(V+E)$ in the worst case. If compact vertex IDs are renumbered, updating affected IDs can be included in the same scan.

Removing B also removes references to B from other vertices. Without an incoming-edge index, finding those references requires scanning the vertex lists and their entries: $\Theta(V+E)$ in the worst case. An edge list similarly filters all its records.

![[attachments/graph-vertex-deletion-scans.png|500]]

### 2.19 Graph as an edge list

An **edge list** stores the edges themselves as records such as `(u, v)` or `(u, v, weight)`. It keeps no per-vertex neighbor collection. Store a separate vertex list when isolated vertices must also be represented.

- **Storage:** $\Theta(V+E)$ for vertex records and an edge array whose capacity is proportional to $E$.
- **Undirected edges:** one record per edge is sufficient.
- **Directed edges:** the order of the endpoints specifies direction.

For edges `A–B`, `A–C`, and `B–D`, the edge list is `[(A,B), (A,C), (B,D)]`. This representation fits algorithms that repeatedly examine all edges, such as Bellman–Ford, or sort them, such as Kruskal.

![[attachments/graph-edge-list-overview.png|500]]

#### Operations and time complexities

- **Read an edge at a known array index:** $\Theta(1)$.
- **Check for an edge or enumerate a vertex's neighbors:** $\Theta(E+1)$ in the worst case.
- **Append a known-new edge:** $\Theta(1)$ with spare capacity; $\Theta(E+1)$ if storage grows.
- **Remove an edge by endpoints:** $\Theta(E+1)$ worst case. Removing a known index by swapping with the last edge takes $\Theta(1)$ if order need not be preserved.
- **Scan all edges:** $\Theta(E)$ for nonempty lists.
- **Add an isolated vertex:** $\Theta(1)$ with spare vertex-list capacity; $\Theta(V)$ on growth.
- **Remove a vertex and its incident edges:** $\Theta(V+E)$ worst case with compact vertex records.
- **Comparison-sort edges by weight:** $O(E\log(E+1))$ using an appropriate comparison sort.

#### Why each operation has this complexity

**1. Edge lookup and neighbor enumeration — scan the records**

An edge's endpoints do not identify its array position. Compare records until a match is found or the list ends. To enumerate all neighbors of a vertex, inspect every edge and keep the incident ones. An undirected query checks either endpoint; a directed outgoing-neighbor query checks the source.

**2. Insertion and deletion — array costs apply**

Appending writes one new record when capacity is available. Checking for duplicates first requires a scan. To delete by endpoints, first locate the record. Once its index is known, either shift later edges to preserve order or replace it with the last edge and shorten the list. The latter changes a constant number of entries, but does not eliminate the earlier lookup cost.

**3. Vertex deletion — filter incident edges**

Scan the edge array once, retaining records that do not touch the removed vertex. Compact the vertex list and update endpoint IDs if that representation renumbers them. Vertex and edge processing together take $\Theta(V+E)$ in the worst case.

The vertex-deletion diagram in [[#2.18 Graph as an adjacency list|Graph as an adjacency list]] includes this edge-record filtering step.

**4. Full scans and sorting — work is organized by edges**

An entire pass examines each of the $E$ edge records once. Sorting compares weights and rearranges those records; merge sort or heap sort gives $O(E\log(E+1))$ time. Once sorted, Kruskal can consider edges in increasing weight order.

## 3 Searching sorting and traversal algorithms

| Algorithm | Procedures and variants to review |
|---|---|
| **Linear search** | Sequential comparison until a match or the end |
| **Binary search** | Iterative and recursive implementations |
| **Selection sort** | Repeated minimum selection and swapping |
| **Insertion sort** | Searching backward through the sorted prefix; shifting and inserting |
| **Bubble sort** | Adjacent comparisons/swaps; repeated passes; early termination |
| **Quicksort** | Partitioning; recursive sorting; first/last-element, random, and median-of-three pivot choices |
| **Merge sort** | Recursive splitting; merging sorted subarrays |
| **Heap sort** | Bottom-up heap construction; root/end swaps; shrinking the heap; sift-down |
| **Bucket sort** | Distributing elements; sorting within buckets; concatenating results |
| **Counting sort** | Frequency counting; cumulative counts; placement into output |
| **Radix sort** | Repeated digit/key-position passes; stable sorting within each pass |
| **Binary-tree level-order traversal** | Queue-based BFS |
| **Binary-tree depth-first traversals** | Preorder; inorder; postorder |

The structure-specific procedures—hash-table operations, BST operations, AVL rotations, B-tree repairs, and heap operations—are included under their structures above.

Here, $n$ is the number of array elements or tree nodes. Array indexing, comparisons, arithmetic on fixed-size values, and counter updates take constant time. Auxiliary space excludes the input but includes temporary arrays and recursive calls. The sorting bounds describe the algorithm with demonstration printing turned off. A **stable** sort preserves the original relative order of records with equal keys.

### 3.1 Linear search

**Linear search** checks elements one at a time until it finds the target or reaches the end. The data does not need to be sorted. A left-to-right search that stops immediately returns the first matching position when duplicates exist.

Compare one position at a time and stop at the first match. This search makes four comparisons; an absent target would require all $n$.

![[attachments/linear-search-step-trace.png|500]]

#### Time and space complexities

- **Best case:** $\Theta(1)$ time.
- **Worst case:** $\Theta(n)$ time.
- **Average successful search:** $\Theta(n)$ if the matching position is equally likely to be anywhere.
- **Auxiliary space:** $\Theta(1)$ for the iterative version.

#### Why

If the first element matches, one comparison finishes the search. If the target is absent or first appears at the last position, all $n$ elements are compared. More generally, stopping after $k$ inspected elements costs $\Theta(k)$.

Under the stated average-case assumption, the search examines $(n+1)/2$ positions on average. Half the array still grows linearly with $n$. No extra collection is needed: the algorithm retains the target and current position. Unlike minimum/maximum search, finding one matching element is enough to stop.

### 3.2 Binary search

**Binary search** uses the order of a sorted array to discard about half the remaining positions after each comparison. Keep a lower and upper index, inspect the midpoint, and compare its value with the target. A smaller midpoint value rules out everything through that midpoint; a larger value rules out everything from it onward.

The iterative version updates these bounds in a loop. The recursive version calls itself on the one remaining interval. A match ends the search; an empty interval means the target is absent.

The active interval shrinks from seven entries to three, then one. Three midpoint comparisons find $16$; repeated halving gives the logarithmic bound.

![[attachments/binary-search-three-step-trace.png|500]]

#### Time and space complexities

- **Best case:** $\Theta(1)$ time.
- **Worst case:** $\Theta(\log n)$ time for either version.
- **Iterative auxiliary space:** $\Theta(1)$.
- **Recursive auxiliary space:** $O(\log n)$, reaching $\Theta(\log n)$ in the worst case.

#### Why

The remaining sizes are approximately $n,n/2,n/4,\ldots$. After $k$ reductions, at most about $n/2^k$ positions remain. Reaching one position takes about $\log_2 n$ reductions, each with constant-time array access and comparisons. If the first midpoint matches, the search instead finishes immediately.

Only one half is searched after each comparison. Searching both halves would lose the benefit of using the sorted order. Iteration retains a fixed number of indices; recursion retains one call for each interval along this shrinking sequence. These bounds assume index ranges, without copying array slices.

Sorting the data beforehand is a separate cost. The logarithmic bound describes a search on an already sorted array with constant-time indexed access. It does not mean that moving to the middle of a linked list is constant time, or that an arbitrary matching midpoint is necessarily the first duplicate.

### 3.3 Selection sort

**Selection sort** grows a sorted prefix. Scan the unsorted part to find its smallest element, swap that element into the next position of the prefix, and repeat. Once $n-1$ positions are settled, the remaining element is already in its place.

Remember the smallest candidate while scanning; swap only after the scan finishes. This first pass makes three comparisons and one final swap.

![[attachments/selection-minimum-scan-swap.png|500]]

#### Time and space complexities

- **Best, average, and worst time:** $\Theta(n^2)$.
- **Auxiliary space:** $\Theta(1)$; the sort rearranges the original array.
- **Stability:** the usual swapping version is unstable.

#### Why

The first round compares the current candidate with $n-1$ other elements. The next makes $n-2$ comparisons, continuing down to one. Therefore, the comparison count is

$(n-1)+(n-2)+\cdots+1=\dfrac{n(n-1)}2.$

Each row counts comparisons in one pass. Here they total $5+4+3+2+1=15$; in general, the triangular total is $\Theta(n^2)$.

![[attachments/selection-comparison-work.png|500]]

This work happens even when the array is already sorted. The algorithm still scans the remaining interval to establish which element belongs next. Saving its index and exchanging two values require only constant space.

The note's version records the minimum and performs one final swap per round. The practice code swaps whenever it finds a better candidate. That variation can perform more swaps, but its fixed comparison loops still give $\Theta(n^2)$ time.

A long-distance swap can change the order of equal keys. For example, swapping the final `1` into the first position of `[2a, 2b, 1]` produces `[1, 2b, 2a]`. The values are sorted, but the two records with key `2` have reversed order.

### 3.4 Insertion sort

**Insertion sort** also grows a sorted prefix, but inserts the next unsorted element into that prefix. Save its value, walk backward through larger elements, shift them one position right, and place the saved value in the gap. The first element alone forms the initial sorted prefix.

Keep $3$ aside while shifting $6$ and $4$ right, then write $3$ into the gap. One insertion costs one comparison per inspected predecessor and one move per shifted element.

![[attachments/insertion-shift-key-trace.png|500]]

#### Time and space complexities

- **Best time:** $\Theta(n)$ when the array is already sorted.
- **Average time:** $\Theta(n^2)$ for a uniformly random ordering of distinct keys.
- **Worst time:** $\Theta(n^2)$, for example with reverse-sorted distinct keys.
- **Auxiliary space:** $\Theta(1)$.
- **Stability:** stable when only strictly larger elements are shifted.

#### Why

When inserting the element at index $i$, at most $i$ earlier elements need to move. In the worst case, each new element belongs at the beginning, so the shifts total

$1+2+\cdots+(n-1)=\dfrac{n(n-1)}2.$

For already sorted input, the first comparison at each insertion shows that the new value belongs where it is. There are still $n-1$ insertions to check, but each uses constant work, giving $\Theta(n)$.

The work follows how far elements must move backward. A nearly sorted array can therefore require far fewer shifts than a reverse-sorted one. Random order usually leaves a substantial fraction of each earlier prefix larger than the next element, producing quadratic expected work.

Only the saved value and a few positions are needed. Shifting a value right frees the next position to its left, so no temporary array is required. Stopping at an equal key places the new record after existing equal records, preserving their original order.

### 3.5 Bubble sort

**Bubble sort** compares neighboring elements and swaps them if they are out of order. During an ascending pass, the largest remaining value moves to the right end. The next pass can stop one position earlier because that final position is settled.

Each comparison checks one adjacent pair. The passes make $3$, then $2$, then $1$ comparisons as the completed suffix grows.

![[attachments/bubble-adjacent-pass-trace.png|500]]

An early-termination version also remembers whether the pass made any swaps. If a complete pass makes none, the array is sorted and the remaining passes can be skipped.

#### Time and space complexities

- **Practice code without early termination:** $\Theta(n^2)$ in all cases.
- **With early termination:** best $\Theta(n)$; average and worst $\Theta(n^2)$.
- **Auxiliary space:** $\Theta(1)$.
- **Stability:** stable when equal neighbors are not swapped.

#### Why

The full sequence of passes performs $(n-1)+(n-2)+\cdots+1$ adjacent comparisons. The practice code always runs these loops, so already sorted input saves swaps but does not save comparisons.

With a swap flag, already sorted input needs only the first pass: its $n-1$ comparisons establish that every neighboring pair is in order. In a reverse-sorted array, many elements must cross many others, and adjacent swaps move them only one position at a time. The total remains quadratic. The usual average bound assumes a random ordering of distinct keys.

The algorithm holds only loop positions, a possible swap flag, and temporary swap values. Two equal records can exchange relative order only by crossing each other; refusing to swap equal neighbors prevents that crossing and preserves stability.

### 3.6 Quicksort

**Quicksort** chooses a pivot value, partitions the array around it, then recursively sorts the resulting parts. In the two-pointer partition, move the left pointer past suitably small values and the right pointer past suitably large ones. Swap misplaced values, advance the pointers, and continue until they cross.

Common pivot choices are the **first or last element**, a **random element**, or the **median of the first, middle, and last values**. The practice code uses a random pivot value and returns two remaining index ranges; it does not require one distinguished pivot element to finish at a fixed final index.

The pointers scan inward, swap the misplaced pair, and advance again. Here they finish at $L=4$ and $R=2$, leaving recursive ranges $0..2$ and $4..6$.

![[attachments/quicksort-two-pointer-trace.png|500]]

#### Time and space complexities

- **Partitioning $n$ elements:** $\Theta(n)$ time; $\Theta(1)$ working space.
- **Balanced partitions:** $\Theta(n\log n)$ total time.
- **Random pivots:** expected $\Theta(n\log n)$ time, with the standard distinct-key analysis.
- **Worst time:** $\Theta(n^2)$.
- **Recursive auxiliary space:** $O(\log n)$ with balanced partitions; $O(n)$ in the worst case.
- **Stability:** the swapping implementation is unstable.

#### Why

During one partition, each pointer moves in one direction through its interval. Together they inspect only a linear number of positions, even though the code contains several loops.

With roughly equal splits, the total partition work across one recursion level is $\Theta(n)$. Repeated halving produces $\Theta(\log n)$ levels, giving $\Theta(n\log n)$. Random pivot choices give this bound in expectation over those choices; they do not guarantee balanced partitions on every run.

If each pivot leaves one nearly full part, the work becomes $n+(n-1)+\cdots+1$, or $\Theta(n^2)$. First/last pivots can behave this way on sorted distinct input. Median-of-three often improves the split, but still provides no worst-case balance guarantee.

Each block represents a subproblem that needs a linear scan. Balanced splits give $O(n)$ work per level over $O(\log n)$ levels; one-sided splits repeatedly scan nearly the whole remainder, giving $\Theta(n^2)$.

![[attachments/sorting-recursion-work.png|500]]

The recursive code keeps one frame per unfinished partition along its current path. Balanced paths are logarithmic; a sequence that removes only one element at a time can produce a linear stack. Equal values are handled by advancing both pointers after swaps, so they do not trap the partition in an endless loop. Long-distance swaps can nevertheless reorder equal records.

### 3.7 Merge sort

**Merge sort** splits an array into halves until each piece has at most one element. It then combines neighboring sorted pieces into progressively larger sorted pieces.

![[attachments/merge-sort-overview.png|500]]

To merge, keep one position in each sorted half. Compare their first remaining elements, take the smaller, and advance only that side. Once one half is exhausted, copy the rest of the other half. For `[3, 7]` and `[2, 6]`, the selected values are `2, 3, 6`, followed by the remaining `7`.

Only the two first remaining values are compared. Each selection advances one pointer and writes one output entry, so merging $n$ entries takes $\Theta(n)$ work.

![[attachments/merge-two-way-output-trace.png|500]]

#### Time and space complexities

- **Merging two sorted parts with $n$ elements altogether:** $\Theta(n)$ time.
- **Best, average, and worst sorting time:** $\Theta(n\log n)$ for the studied version.
- **Auxiliary space:** $\Theta(n)$, including temporary storage and the smaller $O(\log n)$ recursion stack.
- **Stability:** stable when ties take the element from the left half first.

#### Why

A merge does not sort its inputs again. Each half is already ordered, so its first remaining value is the only candidate needed from that half. Every selection advances a position; copying the remaining values also processes each one once. Copying a range into temporary storage and back adds further linear passes, keeping the merge cost linear.

At each recursion level, the merged ranges together cover $n$ elements. Halving creates $\Theta(\log n)$ levels, so the total is $\Theta(n\log n)$. The implementation still splits and merges already sorted input, giving the same asymptotic best-case bound.

The practice code reuses one scratch array of length $n$. Memory is measured by what is needed simultaneously, so repeated use of that buffer does not make the space $\Theta(n\log n)$. Recursive calls add only a logarithmic stack. Taking the left record on a tie keeps it before an equal record that originally appeared in the right half.

### 3.8 Heap sort

**Heap sort** first rearranges the array into a max-heap. Its root holds the largest remaining value. Swap the root with the last position of the active heap, shorten the heap by one, and sift the replacement root downward to restore the heap property. The excluded suffix grows in sorted order.

Bottom-up construction begins at the last parent and works backward to the root. Children are already valid heaps when their parent is repaired. This is the implementation in note 11.6; the separate practice-code file is still unfinished.

#### Time and space complexities

- **Bottom-up heap construction:** $\Theta(n)$.
- **One root/end swap:** $\Theta(1)$; the following sift-down takes $O(\log n)$.
- **Whole sort:** worst $\Theta(n\log n)$; with distinct keys, best and average are also $\Theta(n\log n)$.
- **All-equal input:** $\Theta(n)$ for the note's sift-down, which stops when no child is larger.
- **Auxiliary space:** $\Theta(1)$ with iterative sift-down.
- **Stability:** unstable.

#### Why

Heap construction does not pay a full logarithmic sift at every position. About half the positions are leaves and need no sift. About a quarter can move down only one level, an eighth only two, and so on. Summing these contributions gives linear work: the many short repairs outweigh the few long ones near the root.

During sorting, there are $n-1$ extractions. Each replacement root can travel through at most logarithmically many levels of the remaining complete tree. This gives an $O(n\log n)$ upper bound, and inputs exist that require that much work. Merely starting with sorted distinct values does not remove these repeated heap repairs.

After moving the maximum into the sorted suffix, the replacement travels down one branch. One repair takes $O(\log n)$; repeating it for $n-1$ removals gives $O(n\log n)$ sorting time.

![[attachments/heap-sort-extraction-work.png|500]]

If every key is equal, each repair stops after checking the children, so the repeated rounds take only linear time. The sort stores its heap and sorted suffix in the original array, using only indices and swap values. Root/end swaps can move equal records past each other, so their original order is not preserved.

### 3.9 Bucket sort

**Bucket sort** divides the value range into ordered intervals. Put each value into its interval's bucket, sort each bucket, then concatenate the buckets in interval order. Values in an earlier bucket already belong before values in a later one; only order within a bucket remains to be resolved.

![[attachments/bucket-sort-overview.png|500]]

The practice code finds the minimum and maximum, chooses an integer bucket width, and computes a bucket index from the value's offset above the minimum. The subtraction also permits negative values. Let $k$ be the number of buckets.

#### Time and space complexities

- **Distribution and collection:** $\Theta(n+k)$.
- **Textbook version with insertion sort inside buckets:** expected $\Theta(n+k)$ when $k=\Theta(n)$ and independent inputs distribute uniformly among buckets.
- **Worst case with insertion-sort buckets:** $\Theta(n^2+k)$, or $\Theta(n^2)$ when $k=O(n)$.
- **Practice version using built-in sorting:** worst $O(n\log n+k)$.
- **Auxiliary space:** $\Theta(n+k)$.
- **Stability:** requires preserving arrival order and using a stable sort within each bucket.

#### Why

Finding the range and distributing the values each take linear time. Reading the buckets in order visits $k$ buckets and $n$ stored values. The remaining cost depends on the bucket sizes.

With insertion sort, a bucket containing $m$ elements can require $\Theta(m^2)$ work. Uniform independent distribution across a number of buckets proportional to $n$ keeps the expected total sorting work linear. More generally, the expected bound is $O(n+k+n^2/k)$ under that model. Uniformity alone does not justify a linear bound if too few buckets are used.

If many values cluster in one interval in a difficult order, one insertion sort may receive nearly all $n$ values and take quadratic time. The practice code instead calls the built-in sort for each bucket, so its worst-case bound follows that sorting method rather than insertion sort's quadratic bound.

With insertion sort inside the buckets, three two-item buckets need three shifts here; one reverse-ordered six-item bucket needs 15. Concentrating the values can restore quadratic work.

![[attachments/bucket-imbalance-work.png|500]]

All buckets together store $n$ values or references, plus $k$ bucket headers. Appending values in input order and sorting ties stably preserves the order of equal keys, which always enter the same bucket.

### 3.10 Counting sort

**Counting sort** uses integer values as positions in a frequency array. Let the smallest value be $a$, the largest be $b$, and the range size be $K=b-a+1$. Value $x$ uses count position $x-a$, so negative values work through the same offset.

![[attachments/counting-sort-overview.png|500]]

After counting occurrences, the practice code writes each value back as many times as its count specifies. The stable textbook version adds **cumulative counts**: each count then tells us how many input elements have that value or a smaller one. This identifies the end of that value's output range.

#### Time and space complexities

- **Time:** $\Theta(n+K)$, regardless of the input's existing order.
- **Frequency reconstruction for plain integers:** $\Theta(K)$ auxiliary space.
- **Stable placement into an output array:** $\Theta(n+K)$ auxiliary space.
- **Stability:** provided by the output-placement procedure below.

#### Why

Counting visits $n$ elements, while the frequency and cumulative-count passes process $K$ positions. Writing the result places exactly $n$ elements. These passes add to $\Theta(n+K)$; they do not multiply into $nK$.

For stable placement, scan the input from right to left. The cumulative count for the current value gives its next output position, after subtracting one for zero-based indexing. Place the complete record there and decrement that count. The next equal record encountered belongs immediately before it. Since later equal records were processed first and placed farther right, their original relative order is preserved.

Each record is placed once, with $2a$ staying before $2b$. The $n$ placements and the $K$ count positions add to $\Theta(n+K)$ work.

![[attachments/counting-stable-placement.png|500]]

The count array uses $K$ slots, and the stable version also retains $n$ output records. Reconstructing plain integer values needs no separate output array, but does not retain attached records as stable placement does.

The range size matters as much as the number of inputs: a few integers spread over a huge range can require a huge count array. Counting sort becomes linear in $n$ when $K=O(n)$. It uses values as array indices, so its bound is not restricted to what sorting through comparisons alone can achieve.

### 3.11 Radix sort

**Radix sort** sorts one digit position at a time. The studied version starts with the least significant digit, then processes increasingly significant digits. Each pass moves complete values or records according to that digit, preserving the order of equal digits.

Let $D$ be the maximum number of digit positions and $B$ the base: decimal digits use $B=10$. Missing leading digits are treated as zero. The practice code accepts nonnegative integers and implements each stable pass with digit buckets, appending in input order and reading buckets from `0` through `9`.

Append records to each digit bucket in arrival order, then read buckets in digit order. Keeping that arrival order preserves the lower-digit ordering between passes.

![[attachments/radix-stable-digit-buckets.png|500]]

#### Time and space complexities

- **One stable counting or digit-bucket pass:** $\Theta(n+B)$ time.
- **All $D$ digit passes:** $\Theta(D(n+B))$ time.
- **Auxiliary space:** $\Theta(n+B)$, reused between passes.
- **Stability:** stable when every digit pass is stable.

#### Why

One pass inspects the current digit of every value, organizes the $B$ possible digit values, and writes out $n$ complete entries. Repeating that work for $D$ positions multiplies the cost by $D$. With a fixed base, this is $\Theta(Dn)$; it is linear in $n$ when the number of digits is also bounded.

Stability is necessary for correctness. After the units pass, values are ordered by their units digit. A stable tens pass groups them by tens while retaining units order among equal tens. The same argument repeats: each new pass establishes order on the next digit while preserving the ordering already established on less significant digits.

For example, `12` must remain before `13` after sorting their equal tens digits. An unstable pass could destroy the units ordering and leave the final numbers unsorted.

The temporary entries and digit buckets are reused, so space is not multiplied by $D$. These bounds assume extracting a digit takes constant time. The code skips digit passes for all-zero input, but finding its maximum still takes $\Theta(n)$. Its final reversal for descending output would reverse equal records too; the ascending digit passes themselves are stable.

### 3.12 Binary-tree level-order traversal

**Level-order traversal** visits the root, then its children, then the next level, working from left to right within each level. Use a queue: add the root if it exists, repeatedly remove the front node, visit it, and add its existing left and right children to the back.

Each row removes the front node, visits it, then adds its children at the back. Every node enters and leaves the queue once, giving $\Theta(n)$ time.

![[attachments/tree-bfs-queue-output-trace.png|500]]

![[attachments/tree-traversal-orders.png|500]]

#### Time and space complexities

- **Time:** $\Theta(n)$.
- **Queue space:** $O(n)$, reaching $\Theta(n)$ for sufficiently wide trees.
- **Stored traversal output:** an additional $\Theta(n)$ if all visited values are collected.

#### Why

Every node enters the queue once and leaves once. Visiting it and checking its two child references take constant work. A queue with constant-time operations at both required ends therefore gives linear total time. The note uses a deque; repeatedly removing index zero from an array would introduce shifting work and could make the traversal quadratic.

The queue holds nodes whose turn has not yet arrived. A tree can have a bottom level containing a constant fraction of all its nodes, so that waiting collection can grow linearly with $n$. A tree that is just a single path keeps only one node queued at a time, but the worst-case space remains $O(n)$.

The broad tree leaves four of its seven nodes waiting in the queue; the chain keeps seven recursive calls active. Both can require $O(n)$ auxiliary space, although each traversal visits every node only once.

![[attachments/tree-traversal-memory-work.png|500]]

An empty root produces an empty traversal. The output order reflects the tree's current levels; it does not generally recover the order in which nodes were inserted. Saving every visited value requires linear output space even when the queue itself remains small.

### 3.13 Binary-tree depth-first traversals

**Depth-first traversal** finishes exploring a subtree before moving to the next subtree. The three common forms differ in when they visit the current node:

- **Preorder:** current node, left subtree, right subtree.
- **Inorder:** left subtree, current node, right subtree.
- **Postorder:** left subtree, right subtree, current node.

Each recursive call handles one node and returns immediately if its node reference is empty. The ordering of the visit relative to the two recursive calls determines which traversal is performed.

Choose when to emit each node: on entry for preorder, after the left call for inorder, or before return for postorder. The same recursive walk produces the three different sequences.

![[attachments/tree-dfs-enter-return-emission.png|500]]

#### Time and space complexities

- **All three traversals:** $\Theta(n)$ time.
- **Recursive stack:** $O(n)$ in the worst case; $O(\log n)$ for a balanced tree.
- **Stored traversal output:** an additional $\Theta(n)$ if all visited values are collected.

#### Why

Every real node is visited once and has its two child references examined. Although each call can make two recursive calls, they process different subtrees. They do not each repeat the work of traversing the whole tree, so the total remains linear. Empty-child calls also contribute only constant work per missing reference.

The stack stores unfinished ancestors along the current branch. If the tree is one long chain, as many as $n$ calls can be active. In a balanced tree, a branch contains only logarithmically many nodes. Completed calls return before sibling subtrees are explored, so the stack does not retain a separate frame for every node already visited.

Preorder processes a parent before its descendants, which is useful when constructing a corresponding copy. Inorder outputs keys in sorted order when the tree is a BST; an arbitrary binary tree has no such guarantee. Postorder completes both children before their parent, making it useful when a parent's work depends on its children's results. These differences change the sequence and purpose, while leaving the linear traversal time unchanged.

## 4 Graph algorithms

| Algorithm | Procedures and variants to review |
|---|---|
| **Breadth-first search** | Queue-based traversal; visited tracking |
| **Depth-first search** | Recursive traversal; visited tracking |
| **Directed-cycle detection** | Tracking vertices on the active DFS path |
| **DFS-based topological sort** | Finishing order and reversal |
| **Kahn’s algorithm** | Indegree counting; processing zero-indegree vertices |
| **Tarjan’s SCC algorithm** | Discovery indices; low links; stack tracking; component extraction |
| **Lazy Dijkstra** | Edge relaxation; duplicate queue entries; skipping stale entries |
| **Eager Dijkstra** | Edge relaxation; indexed priority queue; decrease-key |
| **A\*** | Accumulated cost plus heuristic estimate; priority updates |
| **Bellman–Ford** | Repeated edge relaxation; early termination; reachable negative-cycle detection and affected vertices |
| **Floyd–Warshall** | All-pairs shortest paths through intermediate vertices |
| **Eulerian existence checks** | Degree conditions; connectivity requirements; choosing a starting vertex |
| **Hierholzer’s algorithm** | Constructing an Eulerian path or circuit |
| **Prim’s algorithm** | The lazy priority-queue implementation |
| **Kruskal’s algorithm** | Sorting edges; selecting edges in order; rejecting edges that create cycles |

### 4.1 Breadth-first search

For these graph algorithms, $V$ is the number of vertices and $E$ is the number of edges. We use adjacency lists and indexed arrays for per-vertex information. An undirected edge appears in two adjacency lists, which changes the count by a constant factor. Auxiliary-space bounds exclude storage for the input graph. With an adjacency matrix, a full BFS/DFS-style scan instead checks $V$ possible neighbours for each vertex, taking $\Theta(V^2)$ time.

**Breadth-first search (BFS)** explores a graph outward from a starting vertex, one distance layer at a time. It visits neighbours first, then vertices reachable through two edges, then three, and so on. For an unweighted graph, these layers give the minimum number of edges from the starting vertex.

Mark the starting vertex as discovered and put it in a queue. Repeatedly remove the front vertex, process it, and inspect its neighbours. Whenever a neighbour is undiscovered, **mark it immediately before adding it to the queue**. Marking at insertion prevents several vertices from adding the same neighbour before its turn arrives.

![[attachments/graph-bfs-steps-only.png|500]]

The queue's FIFO order ensures that vertices discovered earlier are processed first. Neighbours within a layer may appear in different orders depending on the adjacency-list order; this does not change their distance layer. One run reaches only vertices reachable from its start. To visit the entire graph, scan the vertex list and start another BFS whenever an undiscovered vertex remains, keeping the same discovery array.

- **Time for the full graph:** $\Theta(V+E)$.
- **Auxiliary space:** $O(V)$ for discovery information and the queue.

**Why these costs:** Each vertex is enqueued and dequeued at most once. These queue operations take constant time, giving $O(V)$ total work. When a vertex is processed, its adjacency list is scanned once; across the graph, those lists contain $E$ directed entries or $2E$ undirected entries. This contributes $\Theta(E)$ work rather than another factor of $V$.

The outer loop and discovery-array setup contribute $\Theta(V)$, so disconnected components do not change the total bound. The queue can contain many vertices from a broad layer, but never more than $V$ distinct vertices. Running BFS only from one source scans only its reachable vertices and their outgoing edges, although setting up a full discovery array still takes $\Theta(V)$ time.

### 4.2 Depth-first search

**Depth-first search (DFS)** follows an unexplored branch as far as possible before returning to explore another branch. The next neighbour is chosen according to an order, such as its position in the adjacency list; the algorithm does not require a random choice.

When entering a vertex, mark it as discovered before inspecting its edges. For each undiscovered neighbour, make a recursive call. That call explores everything it can before returning, after which the current call continues with its next neighbour. If a neighbour is already discovered, skip the recursive call to it. This prevents cycles from causing endless revisits.

Returning from a call means that vertex has finished examining all its outgoing edges. The recursion stack therefore remembers the chain of unfinished calls and where each should resume. An explicit stack can serve the same purpose, provided it preserves this exploration state.

As with BFS, a run from one vertex reaches only the vertices accessible from it. To cover the entire graph, use an outer loop over all vertices and start DFS from each one that is still undiscovered. Do not reset the discovery information between these starts.

- **Time for the full graph:** $\Theta(V+E)$.
- **Auxiliary space:** $O(V)$ for discovery information and the recursion stack.

**Why these costs:** Each vertex starts one DFS call, and that call scans its adjacency list once. Calls contribute $\Theta(V)$ work; examining the adjacency entries contributes $\Theta(E)$. A recursive call suspends the parent's scan and later resumes it, so returning does not mean rescanning the parent's list from its beginning.

Each vertex starts once and each adjacency entry is scanned once: $\Theta(V+E)$.

![[attachments/graph-dfs-steps-only.png|500]]

The stack depth depends on the longest chain of active calls. A graph can force a chain containing all $V$ vertices, giving $O(V)$ stack space. The graph's total number of edges does not determine stack depth: many edges simply lead to vertices already discovered. The outer loop adds only one check per vertex, so covering disconnected regions still takes linear time in the graph's representation.

### 4.3 Directed-cycle detection

A **directed cycle** follows directed edges back to its starting vertex. DFS can detect one by distinguishing a vertex that is currently being explored from one whose exploration has finished.

Maintain three states: **unvisited**, **active**, and **finished**. A vertex becomes active when its DFS call starts, and finished only after all its outgoing edges have been checked. The active vertices are exactly the vertices on the current recursion path.

When examining an edge $u\to v$, recurse if $v$ is unvisited. If $v$ is active, report a cycle: the active path already leads from $v$ down to $u$, and this edge closes the route back to $v$. An edge to a finished vertex does not by itself establish a cycle. That vertex may belong to a branch that has already been completely explored.

For example, $A\to B\to C\to A$ encounters active vertex $A$ while processing $C$. A self-loop $A\to A$ also reaches an active vertex and is detected. A single visited/not-visited flag would not make the necessary distinction between active and finished vertices.

![[attachments/graph-cycle-detection-only.png|500]]

Start another DFS from each unvisited vertex so that a cycle in a separate region is not missed. These rules are for directed edges; they rely on the direction of the return edge.

- **Worst-case time:** $\Theta(V+E)$; finding a cycle may permit earlier termination.
- **Auxiliary space:** $O(V)$ for vertex states and the recursion stack.

**Why these costs:** Changing or checking a state takes constant time. Each vertex becomes active once and finishes at most once, while its outgoing edges are inspected once. Therefore, adding cycle detection to DFS does not change its full-scan bound. A graph with no directed cycle requires completing the scan before answering that none exists.

The active state is stored in one array entry per vertex; it does not require searching through the recursion stack whenever an edge is examined. Both the state array and the deepest possible chain of recursive calls occupy $O(V)$ space.

### 4.4 DFS-based topological sort

A **topological ordering** of a directed graph places every vertex before the vertices that depend on it: for every edge $u\to v$, $u$ appears before $v$. Such an ordering exists exactly when the graph has no directed cycle, making it a **directed acyclic graph (DAG)**. Several valid orders may exist.

Run DFS with the active/finished states used for cycle detection. Finish exploring every outgoing neighbour of a vertex before placing that vertex into the result. There are two equivalent ways to record this: append vertices as their calls finish and reverse the list once, or fill an output array from its last position toward its first.

The second approach matches the notes. When a vertex finishes, put it into the next free position working right to left. Continue DFS from unvisited vertices until every vertex has been included. If an edge reaches an active vertex, stop and report that no topological ordering exists.

Why does finishing order work? For an edge $u\to v$ in a DAG, DFS must finish $v$ before it finishes $u$. Either it explores $v$ from $u$, or $v$ has already finished. The remaining possibility—$v$ still being active—would produce a cycle. Reversing finish order therefore puts $u$ before $v$.

State checks and finish events add constant work per edge or vertex: $\Theta(V+E)$.

![[attachments/graph-topological-finish-only.png|500]]

- **Time:** $\Theta(V+E)$ for a DAG; $O(V+E)$ when cycle detection may stop early.
- **Auxiliary space:** $O(V)$ for states, the recursion stack, and the ordering.

**Why these costs:** DFS processes every vertex and adjacency entry once. Placing each finished vertex into a preallocated position takes constant time, adding $\Theta(V)$ work overall. Alternatively, appending all finish events and reversing the completed list takes another $\Theta(V)$ pass.

Repeatedly inserting at the front of an ordinary array would shift existing entries and add unnecessary quadratic work. Filling from right to left avoids those shifts. The outer loop handles disconnected regions without repeating completed searches, while the result and bookkeeping each hold at most $V$ entries.

### 4.5 Kahn's algorithm

**Kahn's algorithm** constructs a topological ordering by repeatedly selecting a vertex with no remaining incoming edges. An incoming edge represents a dependency that must be processed first.

![[attachments/topological-order-overview.png|500]]

First count every vertex's **indegree**, the number of incoming edges. Put all zero-indegree vertices into a queue. Remove one vertex from the front, append it to the ordering, and examine its outgoing edges. For each edge $u\to v$, decrease the stored indegree of $v$ by one. If that count becomes zero, immediately add $v$ to the queue.

This treats $u$ and its outgoing edges as removed from consideration, but the graph itself need not be modified. The indegree counters record the remaining dependencies. Only the neighbours affected by the current vertex need checking; there is no need to scan every vertex again after each removal.

Three edges cause three decrements; each vertex enters the queue once: $\Theta(V+E)$.

![[attachments/graph-kahn-decrements.png|500]]

Count how many vertices enter the ordering. If the queue empties after processing all $V$ vertices, the result is valid. If fewer than $V$ were processed, the remaining graph contains a directed cycle. Every remaining vertex has an incoming edge from another remaining vertex; following such dependencies backward in a finite graph must eventually repeat a vertex.

Starting with all zero-indegree vertices also includes separate components and isolated vertices. When several vertices are ready together, queue order chooses one of the possible valid topological orders.

- **Time:** $\Theta(V+E)$.
- **Auxiliary space:** $O(V)$ for indegrees, the queue, and the ordering.

**Why these costs:** Computing indegrees scans all adjacency lists once, taking $\Theta(V+E)$ time. The initial search for zero-indegree vertices takes $\Theta(V)$. Each vertex is enqueued and removed at most once, and each outgoing edge of a processed vertex causes one constant-time decrement.

Even if a cycle prevents some vertices from being processed, the initial indegree pass has already scanned the input. There is no extra factor for repeatedly removing dependencies: each edge contributes one increment during counting and at most one decrement during processing. Stored counts and a queue containing at most $V$ vertices keep the extra memory linear.

### 4.6 Tarjan's SCC algorithm

A **strongly connected component (SCC)** is a maximal group of vertices in which every vertex can reach every other by directed paths. A component can contain several overlapping cycles, and a single vertex can form an SCC even without a self-loop. Tarjan's algorithm finds all SCCs during one DFS over the graph.

![[attachments/strongly-connected-components-overview.png|500]]

Assign each newly discovered vertex $u$ a unique increasing **index**, and initially set `low[u] = index[u]`. Push $u$ onto a component stack and mark `onStack[u] = true`. This stack contains discovered vertices whose SCC has not yet been completed. It is different from the recursion stack: a vertex can finish its DFS call and remain on the component stack.

The **low** value records how far back the unfinished exploration can connect, using these update rules for each edge $u\to v$:

- If $v$ is unvisited, explore it first, then set `low[u] = min(low[u], low[v])`.
- If $v$ was already visited and is still on the component stack, set `low[u] = min(low[u], index[v])`.
- If $v$ was already visited and has left that stack, its SCC is complete; ignore that edge for low-value updates.

After checking all outgoing edges of $u$, compare its low value with its own discovery index. If `low[u] == index[u]`, $u$ is the root of a completed SCC. Pop vertices from the component stack until $u$ itself is popped, marking every popped vertex as off-stack. Those popped vertices form one component.

Five pushes, five component-stack pops, and six edge checks: $\Theta(V+E)$.

![[attachments/graph-tarjan-low-stack.png|500]]

The stack boundary matters: an edge into an already completed SCC does not prove that the other SCC can reach back. Likewise, low values are not simply the smallest vertex labels reachable anywhere in the graph. They use discovery indices and the unfinished-component rules above. Obtain components from the stack pops, rather than grouping vertices merely because a temporary low value happens to match.

Use an outer loop to begin DFS at every still-unvisited vertex, so components outside the first reachable region are included.

- **Time:** $\Theta(V+E)$.
- **Auxiliary space:** $O(V)$ for indices, low values, stack-membership flags, the component stack, and recursive calls.

**Why these costs:** Each vertex receives an index once and its adjacency list is scanned once. Each edge causes a constant-time state check and at most one minimum update after any recursive call returns. Together, these account for $\Theta(V+E)$ work.

Popping a large SCC may perform many operations at one return, but every vertex is pushed and popped exactly once across the entire run. The combined cost of all component pops is therefore $\Theta(V)$, not a separate linear scan for every vertex. Both stacks hold at most $V$ vertices, and having two linear-size stacks still gives $O(V)$ auxiliary space.

### 4.7 Lazy Dijkstra

**Dijkstra's algorithm** computes shortest distances from one source $s$ in a graph with **nonnegative edge weights**. It repeatedly selects the unsettled vertex with the smallest known distance and uses its outgoing edges to improve other distance estimates.

![[attachments/dijkstra-priority-update.png|500]]

Set `dist[s] = 0` and every other distance to infinity. Insert the source with priority zero into a binary min-heap. When processing an edge $u\to v$ with weight $w$, compute `candidate = dist[u] + w`. If this is **strictly smaller** than `dist[v]`, replace the estimate. This comparison and possible improvement is called **relaxation**.

The **lazy** version inserts a new heap entry whenever a distance improves. It leaves the older entry in the heap, so several entries can refer to the same vertex. For example, if an estimate improves from $9$ to $4$, both priorities may remain until they are removed.

When extracting an entry, discard it if its vertex is already settled or its stored distance is larger than the current `dist` value. Make these checks **before scanning outgoing edges**. Otherwise, settle the vertex and relax its outgoing edges to unsettled neighbours. Nonnegative weights ensure that the minimum current distance is final when the vertex is settled. Equal-distance alternatives do not require another insertion because relaxation uses a strict improvement test.

Continue until the heap is empty. Vertices unreachable from $s$ retain infinity; no extra starting vertices are needed for this single-source problem.

- **Time with a binary heap:** $O\bigl(V+(E+1)\log(E+2)\bigr)$.
- **For a simple graph:** this is commonly bounded by $O((V+E)\log V)$.
- **Auxiliary space:** $O(V+E)$, including potentially many outdated heap entries.

**Why these costs:** Setting up distance and settled arrays takes $\Theta(V)$ time. Every reachable vertex is settled at most once, and its outgoing edges are then scanned once. Each successful edge relaxation creates one entry, so there are at most $O(E+1)$ insertions and removals, including the initial source entry.

The heap can hold $O(E+1)$ entries. Each insertion or removal takes $O(\log(E+2))$ time; checking and discarding an outdated entry afterward takes constant time. This gives the stated bound. In a simple graph, $E$ is at most quadratic in $V$, allowing the logarithmic factor to be expressed using $V$.

More precisely, if only $E_r$ outgoing edges belong to vertices reachable from $s$, the bound is $O\bigl(V+(E_r+1)\log(E_r+2)\bigr)$. The $V$ term remains because the full distance array is prepared. Skipping stale entries is essential to this analysis: processing their adjacency lists again would invalidate the claim that each vertex's edges are scanned once.

### 4.8 Eager Dijkstra

**Eager Dijkstra** uses the same nonnegative-weight assumption, distance estimates, and relaxation rule. Its difference is how it handles an improved estimate: an **indexed min-priority queue** updates an existing entry instead of leaving an outdated duplicate behind.

The queue holds at most one entry for each discovered, unsettled vertex. Its index mapping tells us whether a vertex is present and where its entry is stored. Begin with the source at distance zero. Repeatedly extract the vertex with minimum distance, settle it, and inspect its outgoing edges to unsettled neighbours.

For an edge $u\to v$, compare `dist[u] + w` with `dist[v]`. If the candidate is strictly smaller, save it. If $v$ already has a queue entry, call **decrease-key** to lower that entry's priority. Otherwise, insert $v$ with its new distance. A vertex that has already been settled does not re-enter the queue.

Lowering a priority may move the entry upward in the heap. The index mapping is updated as entries move, preserving direct access to each vertex's current position. There are no older duplicate entries to extract later. The algorithm ends when the queue is empty, leaving unreachable vertices at infinity.

Decrease-key replaces the existing priority: A changes from 10 to 3, then T changes from 9 to 4. Each unsettled vertex has only one queue entry.

![[attachments/graph-eager-dijkstra-steps.png|500]]

- **Time with a binary indexed heap:** $O((V+E)\log V)$.
- **Auxiliary space:** $O(V)$ for distances, settled states, the heap, and its index mapping.

**Why these costs:** A vertex is inserted at most once and extracted at most once, giving $O(V)$ heap operations of those types. Every reachable edge is examined once and can cause at most one successful decrease-key. There are therefore at most $O(E)$ decreases.

The heap contains at most $V$ entries. Insertion, extraction, and decrease-key each take $O(\log V)$ time, while queue-membership checks through the index mapping take $\Theta(1)$. Adding the edge scans and initial array setup yields $O((V+E)\log V)$ time; trivial one-vertex cases take constant time.

The smaller queue is the main structural difference from the lazy version: its storage depends on the number of vertices rather than the number of successful relaxations. Both versions still examine the graph's edges and obey the same distance-selection rule. Their actual speed also depends on the work needed to maintain their respective queue representations.

The decrease-key diagram in [[#2.16 Indexed priority queue|Indexed priority queue]] shows the heap swap and both position-map updates.

### 4.9 A*

**A\*** finds a shortest route from a start vertex to a particular goal by combining the distance already travelled with an estimate of the distance remaining. As in our map example, straight-line distance can guide the exploration toward the destination, provided it is compatible with the edge costs.

- $g(v)$ is the smallest start-to-$v$ cost found so far.
- $h(v)$ estimates the remaining cost from $v$ to the goal.
- The priority is $f(v)=g(v)+h(v)$.

Set the start's $g$ to zero and the other values to infinity. Repeatedly extract the smallest-$f$ vertex and relax its outgoing edges. If going through it improves a neighbour's $g$, update that neighbour's priority. With the conditions below, extracting the goal establishes its shortest distance; exhausting the queue means it is unreachable.

An **admissible** heuristic never overestimates the true remaining cost. A **consistent** heuristic additionally satisfies $h(u)\le w(u,v)+h(v)$ on every edge, with $h(\text{goal})=0$. Consistency makes a vertex's distance final when it is extracted, so it need not be expanded again. Straight-line distance is consistent when each edge's distance cost is at least the straight-line distance between its endpoints.

With consistency: at most $V$ expansions and $E$ relaxations; indexed-heap updates cost $O(\log V)$.

![[attachments/graph-astar-queue.png|500]]

#### Time and auxiliary space

- **Indexed binary heap:** $O((V+E)\log(V+1))$ time and $O(V)$ auxiliary space.
- **Ordinary heap with duplicate entries:** $O(V+E\log(E+1))$ time and $O(V+E)$ auxiliary space.
- These bounds assume a finite, explicitly represented graph, nonnegative edge costs, constant-time heuristic evaluation, and consistency. Input graph storage is excluded.

#### Why these bounds hold

Each vertex is expanded at most once, so all adjacency-list scans inspect at most $E$ directed edges, or $2E$ entries for an undirected graph. An indexed heap contains at most $V$ vertices; up to $E$ improvements and $V$ extractions each cost $O(\log(V+1))$.

With a duplicate-entry heap, push a new record whenever a distance improves. On extraction, skip records whose saved distance no longer matches the current $g$, and skip already expanded vertices. There can be $O(E)$ records, so heap work is bounded using $\log(E+1)$. Check for a stale record before treating an extracted goal as final.

A useful heuristic can reduce the explored region, but the worst-case graph bounds still apply. With $h=0$, the priorities become Dijkstra's. Admissibility without consistency can require reopening vertices when their distances improve; the one-expansion argument then fails. An arbitrary heuristic may also lose shortest-path correctness, so these bounds and guarantees must not be attached to every possible heuristic.

### 4.10 Bellman–Ford

**Bellman–Ford** finds distances from one source while allowing negative edge weights. It repeatedly improves distance estimates by scanning all edges, rather than selecting the smallest current distance with a priority queue.

![[attachments/negative-cycle-effects.png|500]]

Set $D[s]=0$ and all other distances to $+\infty$. For an edge $u\to v$ of weight $w$, relax it when $D[u]$ is finite and $D[u]+w<D[v]$. Perform up to $V-1$ complete passes. If an entire pass makes no change, the distances have settled and the algorithm can stop early.

Without an affecting negative cycle, a shortest route can be chosen without repeating a vertex, so it uses at most $V-1$ edges. Each pass guarantees that routes using one more edge have been accounted for. Depending on the edge order, one pass may propagate improvements across several edges; $V-1$ is a sufficient bound, not a claim that each pass advances exactly one edge.

Each of the $V-1$ rounds checks all $E$ edges: $O(VE)$.

![[attachments/graph-bellman-passes.png|500]]

#### Time and auxiliary space

- **Relaxation and cycle check:** $O(VE)$ time, or $O(V+VE)$ including initialization and the zero-edge case.
- **Marking every affected vertex:** an additional $O(V+E)$ traversal.
- **Auxiliary space:** $O(V)$ for distances, marking information, and a traversal stack or queue, excluding graph storage.
- **Early termination:** fewer passes can improve a particular run; the worst-case bound remains unchanged.

#### Why these bounds hold

One full edge pass performs constant work per edge, costing $\Theta(E)$. Up to $V-1$ passes therefore cost $O(VE)$. The distance array has one entry per vertex. An existing edge list supports this scan directly. With adjacency lists, first collect the vertices whose outgoing lists are nonempty in one $O(V)$ pass, using $O(V)$ space. Later passes scan only these lists, so their setup and edge visits together cost $O(E)$ per pass.

After the passes, inspect every edge once more. If a finite $D[u]$ still permits an improvement to $D[v]$, a negative cycle reachable from the source affects that region. Use these improvable destinations as starting points for a forward traversal. Every vertex reached from them has distance $-\infty$: going around an affecting cycle repeatedly can make its route cost arbitrarily small. Unreachable vertices remain $+\infty$; other vertices retain finite shortest distances.

The forward traversal visits each marked vertex and its outgoing edges at most once, adding $O(V+E)$ work. It replaces repeated rounds of propagating $-\infty$ through the whole edge list. The extra cycle-check pass is necessary even when $V=1$ and self-loops are allowed, because a negative self-loop is already a negative cycle.

### 4.11 Floyd–Warshall

**Floyd–Warshall** computes distances between every ordered pair of vertices. It uses a distance matrix and gradually expands the set of vertices permitted as intermediate stops.

![[attachments/floyd-warshall-update.png|500]]

Begin with $D[i][j]=+\infty$ for unavailable connections and $D[i][i]=0$. For every direct edge, retain the minimum of its weight and the current entry. This handles parallel edges and preserves a negative self-loop instead of overwriting it with zero.

For each vertex $k$, consider every starting vertex $i$ and destination $j$, updating

$D[i][j]=\min(D[i][j],D[i][k]+D[k][j]).$

Only form the candidate sum when both component routes exist. The loop over $k$ must enclose the loops over $i$ and $j$ in this formulation.

#### Time and auxiliary space

- **Main computation:** $\Theta(V^3)$ time.
- **Preparing the matrix from an edge representation:** $\Theta(V^2+E)$ time; total $\Theta(V^3+E)$, normally written $\Theta(V^3)$ for a simple graph.
- **Distance matrix:** $\Theta(V^2)$ storage, serving as both working storage and output.
- **In-place main loops:** $\Theta(1)$ additional space beyond that matrix.
- **Checking and marking negative-cycle-affected pairs:** at most another $O(V^3)$ pass.

#### Why these bounds hold

Before stage $k$, the distances account for paths whose intermediate vertices come from the earlier stages. Allowing $k$ introduces two possibilities: the best route avoids $k$, or it consists of an $i$-to-$k$ route followed by a $k$-to-$j$ route. Taking the minimum considers both. With no negative cycles, this invariant gives the shortest distances after all vertices have been allowed.

There are $V$ stages, each examining $V^2$ ordered pairs. Each examination uses constant-time arithmetic and comparison, producing $\Theta(V^3)$ work. Updating the same matrix avoids storing a separate matrix for every stage. Having few edges does not remove these pairwise checks in the ordinary implementation.

$V$ stages × $V^2$ pairs gives $\Theta(V^3)$ work; one $\Theta(V^2)$ matrix is reused.

![[attachments/graph-floyd-layers.png|500]]

Negative edges are allowed, but a negative cycle can make some distances unbounded below. After the computation, $D[k][k]<0$ identifies a vertex with a negative-cost closed route. A pair $(i,j)$ is affected precisely when some such $k$ is reachable from $i$ and can reach $j$. Mark those pairs $-\infty$; leave unreachable pairs at $+\infty$ and unaffected distances finite.

Testing every pair against every negative-diagonal vertex costs at most $O(V^3)$ more. A negative cycle does not make every pair invalid: the cycle must lie on a route from that particular source to that particular destination.

### 4.12 Eulerian existence checks

An **Eulerian path** uses every edge exactly once; vertices may appear repeatedly. An **Eulerian circuit** also ends where it started. Degree counts identify possible endpoints, but the edge-containing part of the graph must also be connected in the appropriate sense.

For an **undirected graph**, require all vertices with nonzero degree to lie in one connected component:

- A circuit exists when every degree is even.
- An open path exists when exactly two vertices have odd degree; those are its endpoints.
- A path allowing either outcome therefore requires zero or two odd-degree vertices.

For a **directed graph**, first require the vertices incident to edges to be connected when edge directions are ignored:

- A circuit exists when every vertex has equal indegree and outdegree.
- An open path exists when one start vertex has $\text{outdegree}-\text{indegree}=1$, one end vertex has difference $-1$, and all others have difference zero.

Together with these degree conditions, that underlying connectivity is sufficient. Isolated vertices do not prevent a route that uses all edges.

Degree conditions identify the endpoints, while connectivity determines whether one route can cover all edges. Balanced degrees alone do not join disconnected components.

![[attachments/graph-eulerian-existence-cases-v2.png|500]]

#### Time and auxiliary space

- **Degree counting, endpoint checks, and connectivity:** $\Theta(V+E)$ time using adjacency lists.
- **Auxiliary space:** $O(V)$ for counts, visited flags, and traversal state when the needed incident-edge access is available.
- **Directed connectivity check:** constructing an undirected adjacency view, if needed, uses another $O(V+E)$ temporary storage.

#### Why these bounds hold

Every arrival at an internal point of the route needs a departure. In an undirected circuit, edge uses therefore pair up at each vertex. An open route leaves one unmatched edge at each endpoint. In a directed route, incoming and outgoing uses similarly balance everywhere except its start and end.

Scan the edges once to accumulate counts, then inspect the $V$ vertices. An undirected self-loop contributes two to degree; a directed self-loop contributes one to indegree and one to outdegree. Parallel edges count separately. The degree work is linear, and one connectivity traversal contributes another $O(V+E)$.

For an undirected open path, start at either odd-degree vertex. For a directed open path, use the vertex with one extra outgoing edge. For a circuit with edges, choose a vertex incident to an edge—one with an outgoing edge in the directed case. Starting at an isolated vertex would fail to reach the edge-containing component.

When $E=0$, a single available vertex gives a trivial closed route with no edges. Handle this case separately rather than demanding a nonzero-degree starting vertex. If there are no vertices either, the result can be represented as an empty route.

### 4.13 Hierholzer's algorithm

**Hierholzer's algorithm** constructs an Eulerian path or circuit by following unused edges and recording vertices while backtracking. Use the preceding degree and connectivity conditions to choose a valid starting vertex.

![[attachments/eulerian-circuit-overview.png|500]]

Push the start onto a stack. Look at the vertex on top: if it has an unused outgoing edge, consume that edge and push its destination. Otherwise, pop the vertex and append it to a result sequence. Continue until the stack is empty, then reverse the result. The backtracking order joins the additional closed excursions into one route.

This process tracks **used edges**, not visited vertices. Returning to a vertex is permitted and may be necessary. For an undirected graph, both adjacency-list entries representing the same edge must share an edge ID; marking that ID used prevents consuming the edge twice. Parallel edges need distinct IDs.

#### Time and auxiliary space

- **Degree checks and construction:** $O(V+E)$ time.
- **Cursors, used-edge information, and walk stack:** $O(V+E)$ auxiliary space.
- **Returned vertex sequence:** $\Theta(E+1)$ space for a successful route.
- These bounds use adjacency lists with constant-time access to each next entry. Used entries may need to be skipped, but the cursors ensure that each entry is examined only once.

#### Why these bounds hold

Maintain a cursor for each vertex so that its adjacency list is scanned forward rather than restarted. Every directed entry is examined once. In an undirected representation there are two entries per edge, and each is still inspected at most once, including entries skipped because their shared edge ID is already marked.

Each consumed edge causes one push. Each stack entry is eventually popped once, so there are $O(E+1)$ pushes, pops, and result appends. Reversing the sequence costs another $\Theta(E+1)$. Adding the $O(V)$ metadata work gives the linear bound.

Each edge adds one stack entry; each entry is popped once; one final reversal keeps the work $O(V+E)$.

![[attachments/graph-hierholzer-stack.png|500]]

The walk stack can contain $E+1$ vertices because the same vertex may occur repeatedly; its size is not limited to the number of distinct vertices. The used-edge flags take $O(E)$ space and the adjacency cursors take $O(V)$.

The notes place completed vertices at the front of a linked result list, which also supports constant-time insertion. If the result is an array, append and reverse instead: repeatedly inserting at its front would shift existing entries and could make the result-building work quadratic.

Finally, confirm that exactly $E$ edges were consumed, equivalently that the route contains $E+1$ vertices. Together with the degree checks, this rejects a run that exhausted only one edge-containing component. The zero-edge case returns the chosen trivial route directly.

### 4.14 Prim's algorithm with a lazy priority queue

**Prim's algorithm** grows a minimum spanning tree of a weighted, undirected graph. Begin at any vertex and repeatedly choose the lightest edge connecting the growing tree to a vertex outside it. Edge weights may be negative; the objective is to minimize the total weight of the chosen tree edges.

![[attachments/minimum-spanning-tree-overview.png|500]]

The notes use a **lazy edge priority queue**. Mark the starting vertex visited and add its edges to unvisited neighbours to a min-heap. Extract the lightest candidate. If its destination is already visited, discard it; otherwise, accept the edge, mark that destination, and add its edges to remaining unvisited neighbours.

Old candidates remain in the heap until extracted. They can become unusable when another edge brings their destination into the tree, which is why the visited check is necessary.

#### Time and auxiliary space

- **Lazy binary-heap implementation:** $O(V+E\log(E+1))$ time.
- **Connected simple graph:** this is commonly written $O(E\log V)$.
- **Auxiliary space:** $O(V+E)$ for visited flags, the candidate heap, and the selected edges, excluding the input graph.
- **Selected-edge output:** at most $V-1$ edges; a disconnected graph produces a minimum spanning forest.

#### Why these bounds hold

Each vertex is added once, so its adjacency list is scanned once. Across an undirected graph, these lists contain $2E$ entries. An edge is queued when its first endpoint enters the tree while the other endpoint remains outside; it need not be queued again from the opposite direction. Thus there are at most $O(E)$ heap insertions and extractions.

The heap can hold $O(E)$ candidates, making each operation $O(\log(E+1))$. Discarding a stale candidate still incurs its extraction cost, so counting only the $V-1$ accepted edges would underestimate the work. Initializing flags and checking all vertices contribute $O(V)$.

The cheapest crossing edge is safe to add. Consider a minimum spanning tree containing the edges accepted so far. If it lacks the chosen edge, adding that edge creates a cycle. That cycle contains another edge crossing the same cut; removing this other edge restores a spanning tree. Its weight cannot be smaller than our cheapest crossing edge, so the exchange does not increase the total. This argument allows negative weights and ties. Different tie choices can produce different minimum spanning trees with the same total cost.

For a connected graph, stop after accepting $V-1$ edges. If the heap empties sooner, that run has finished only the start's component. To obtain a minimum spanning forest, continue an outer loop over unvisited vertices and begin the same process in each remaining component. Isolated vertices form components with no selected edges, and the overall bounds are unchanged.

Starting at A, the queue eventually contains stale edges AC and BD. Both are extracted and skipped before DE is accepted; these discarded entries still contribute heap work.

![[attachments/graph-prim-queue-only.png|500]]

### 4.15 Kruskal's algorithm

**Kruskal's algorithm** considers all edges of a weighted, undirected graph in increasing weight order. Accept an edge exactly when adding it would not form a cycle with the edges already chosen. The selected edges form a growing forest, which may initially contain several separate pieces.

For an edge $u-v$, a cycle would appear exactly when the current forest already contains a route from $u$ to $v$. If no such route exists, accepting the edge joins two pieces. Continue until a connected graph has $V-1$ selected edges, or until all edges have been considered. A disconnected input yields a minimum spanning forest. Negative weights and ties are allowed.

#### Time and auxiliary space

- **Sort the edges:** $O(E\log(E+1))$ comparison time.
- **Explicit DFS cycle-checking variant:** $O(V)$ per considered edge; $O(V+E\log(E+1)+EV)$ total time.
- **Common optimized implementation:** $O(V+E\log(E+1))$ total time when efficient component tracking keeps connectivity checks within that bound.
- **Auxiliary space for the DFS variant:** $O(V+E)$ when retaining a separately sorted edge sequence; $O(V)$ for the forest and traversal state apart from that sequence.

#### Why these bounds hold

Sorting puts the lightest remaining candidate first. The greedy choice is safe when it connects different pieces: it is a lightest available edge across a cut separating those pieces, so it can be included without increasing the best achievable total weight. An edge whose endpoints are already connected would close a cycle and is rejected.

For the explicit review variant, store the selected forest as adjacency lists. Before accepting $u-v$, run DFS from $u$ through that forest and check whether $v$ is reached. This traversal must use the **selected edges**, not the original graph: connectivity in the original graph would not tell us whether the new edge closes a cycle in our current selection.

The selected forest has at most $V-1$ edges. Its DFS therefore costs $O(V)$, including resetting visited flags, and there can be $E$ such checks. This contributes $O(EV)$ beyond sorting. An accepted edge adds only two adjacency entries and does not create a denser forest.

Kruskal considers the sorted edges and rejects AC and BD because their endpoints are already connected in the selected forest. Checking each candidate with DFS can add $O(EV)$ traversal work.

![[attachments/graph-kruskal-cycles-only.png|500]]

The usual faster bound comes from keeping connectivity information as edges are accepted, avoiding a fresh DFS for every candidate. The greedy edge order is the same, but the cost of cycle checking changes. Consequently, sorting alone does not establish the optimized bound for the DFS implementation.

## 5 Algorithm design methods and selected problems

| Method                                       | Problem and material to cover                                                                                                                                              |
| -------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Divide and conquer → Tower of Hanoi**      | Dividing into smaller problems; recursive algorithm; base case; sequence of moves; recurrence; time and recursion-stack space                                              |
| **Backtracking → N-Queens**                  | State representation; choices; conflict checking; exploring; undoing choices; pruning; time and space                                                                      |
| **Dynamic programming → 0–1 knapsack**       | States; take/skip recurrence; base cases; top-down memoization; bottom-up two-dimensional tabulation; computation order; time and space                                    |
| **Dynamic programming → Unbounded knapsack** | Reusing an item; modified recurrence; bottom-up two-dimensional tabulation; computation order; time and space                                                              |
| **Greedy algorithms → Fractional knapsack**  | Greedy-choice property; optimal substructure; sorting by value-to-weight ratio; taking whole items and fractions; correctness through an exchange argument; time and space |

---

An algorithm-design method describes how to organize a solution. It does not have one fixed time complexity: the cost depends on how many subproblems, states, or choices the particular algorithm processes, and the work required for each one.

### 5.1 Divide and conquer — Tower of Hanoi

**Divide and conquer** solves a problem through smaller instances of the same problem, then combines their results. In **Tower of Hanoi**, move $n$ disks from rod $A$ to rod $C$, using $B$ as temporary storage. Move only one top disk at a time, and never place a larger disk on a smaller one. Disk $1$ is the smallest.

Reduce the problem to smaller instances, solve down to a base case, then combine the answers.

![[attachments/divide-conquer-method.png|500]]

To transfer $n$ disks from a source to a destination:

1. Transfer the top $n-1$ disks from the source to the spare rod, using the destination as temporary storage.
2. Move the largest remaining disk from the source to the destination.
3. Transfer those $n-1$ disks from the spare rod to the destination, using the source as temporary storage.

For $n=0$, return without moving anything. For $n=1$, this leaves just one disk move. The recursive transfers must happen in order: each starts from the rod configuration left by the preceding steps.

For three disks, starting with all disks on $A$:

| Move | Disk | Transfer |
|---|---|---|
| 1 | 1 | $A\to C$ |
| 2 | 2 | $A\to B$ |
| 3 | 1 | $C\to B$ |
| 4 | 3 | $A\to C$ |
| 5 | 1 | $B\to A$ |
| 6 | 2 | $B\to C$ |
| 7 | 1 | $A\to C$ |

Moves $1$–$3$ transfer the two smaller disks to $B$; move $4$ transfers the largest; moves $5$–$7$ rebuild the smaller stack on $C$.

The two smaller-disk transfers surround the largest-disk move: $3+1+3=7$. In general, this gives $M(n)=2M(n-1)+1$.

![[attachments/hanoi-three-disk-moves.png|500]]

#### Why the algorithm works

Assume we can legally transfer $n-1$ disks. The first transfer uncovers the largest disk. We can then move it to the destination and legally place the smaller stack above it. The zero-disk base case starts this reasoning. Combining the results means performing these move sequences in order.

#### Time and auxiliary space

- **Moves:** $M(0)=0$, $M(n)=2M(n-1)+1=2^n-1$.
- **Time:** $\Theta(2^n)$, assuming constant-time disk moves.
- **Recursion stack:** $\Theta(n)$.
- **Saving every move:** an additional $\Theta(2^n)$ output space.

#### Why these costs

Each transfer makes two smaller transfers plus one move: $T(n)=2T(n-1)+\Theta(1)$. Doubling the preceding work gives exponential growth. However, only one descending sequence of calls is active at a time, with sizes $n,n-1,\ldots,0$, so the stack grows linearly. Returning releases calls before the next transfer begins. Reporting moves as they occur avoids retaining their entire sequence.

### 5.2 Backtracking — N-Queens

**Backtracking** builds a candidate solution, explores the consequences of each choice, and undoes choices before trying alternatives. In **N-Queens**, place $n$ queens on an $n\times n$ board so that no two share a row, column, or diagonal.

Explore a choice; if it fails, undo it to restore the previous state before trying the next choice.

![[attachments/backtracking-method.png|500]]

Place one queen per row. Using zero-based indices, store its column in `q[r]`. Three Boolean arrays track conflicts:

- `column[c]`: whether column $c$ is occupied.
- `difference[r-c+n-1]`: whether the diagonal with constant $r-c$ is occupied.
- `sum[r+c]`: whether the diagonal with constant $r+c$ is occupied.

The column array has $n$ entries; each diagonal array has $2n-1$. The offset $n-1$ makes difference-diagonal indices nonnegative. Checking the three entries takes constant time.

At row $r$, try columns from left to right:

1. Reject a column if any corresponding conflict entry is marked.
2. Otherwise, set `q[r]`, mark its column and both diagonals, and explore row $r+1$.
3. After that recursive call returns, clear those three marks and remove the current choice before trying the next column.

When $r=n$, all queens are placed: copy the column vector as a solution. Continue to enumerate solutions, or stop after the first. If no column works in a row, return to the previous row. A valid placement uses three previously unmarked lines, so clearing its marks does not erase another queen's protection.

#### A four-queen search

Each list below gives the chosen columns for consecutive rows, starting at row $0$.

Start with `[0,2]`: queens occupy $(0,0)$ and $(1,2)$. Row $2$ has no legal choice. Columns $0$ and $2$ are occupied; columns $1$ and $3$ are attacked diagonally by the second queen. Undo $(1,2)$, clearing column $2$, difference entry $2$, and sum entry $3$, while retaining the first queen's marks.

Undo removes the latest queen and clears exactly its column and two diagonal marks. The earlier queen's marks remain, so checking and reversing a choice each take constant time.

![[attachments/queens-conflict-marks-undo.png|500]]

Next try `[0,3,1]`. Row $3$ cannot use occupied columns $0,3,1$, and its remaining column $2$ is diagonal to $(2,1)$. Undo choices and exhaust the remaining alternatives under the first queen at column $0$.

Move the first queen to column $1$. The choices `[1] → [1,3] → [1,3,0] → [1,3,0,2]` reach a solution: queens at $(0,1),(1,3),(2,0),(3,2)$.

Failed branches undo earlier choices. The successful path selects columns $[1,3,0,2]$, placing one nonattacking queen in each row.

![[attachments/queens-four-row-search.png|500]]

#### Why the algorithm works

Each accepted choice preserves the rule that placed queens cannot attack one another. Reaching row $n$ therefore gives a valid arrangement. Trying every legal column and restoring the previous state ensures that no valid completion is skipped. A rejected placement cannot be repaired by adding queens to later rows.

#### Time and auxiliary space

- **Search time:** a safe, loose upper bound of $O(n\cdot n!)$ for this all-columns loop; pruning often reduces it.
- **Search workspace:** $O(n)$ for the column vector, Boolean arrays, and recursive calls.
- **Saving $S$ solution vectors:** an additional $\Theta(nS)$ time and space.
- **Producing full boards:** $\Theta(n^2)$ time per board; retaining $S$ boards uses $\Theta(n^2S)$ output space.

#### Why these costs

Ignoring diagonals, a partial placement with $r$ queens uses distinct columns, giving at most $n!/(n-r)!$ possibilities. Across all depths there are $O(n!)$ such states. Each unfinished state checks all $n$ columns with constant-time tests, giving the stated upper bound. It is not a tight claim about every search. At most $n$ queens and a linear chain of calls are active simultaneously; storing the board as a column vector keeps search memory linear.

### 5.3 Dynamic programming — 0–1 knapsack

**Dynamic programming** stores answers to smaller subproblems so that repeated requests can reuse them. The useful conditions are **overlapping subproblems**, where different choices lead to the same remaining problem, and **optimal substructure**, where an optimal answer can be built from optimal answers to those smaller problems. The state must describe everything needed to solve the remaining problem; the particular history that led there should not change its answer.

Different choices can reach the same state. Solve its smaller states, store the best answer, and reuse it whenever that state returns.

![[attachments/design-dynamic-programming-concept.png|500]]

In **0–1 knapsack**, we have $n$ items. Item $i$ has weight $w_i$ and value $v_i$, and the bag has capacity $W$. We want the greatest total value whose total weight is at most $W$. Each item can be taken **at most once**: take it or skip it. Assume positive integer weights, a nonnegative integer capacity, and nonnegative values. The bounds below count arithmetic and comparisons on these values as constant-time operations.

#### State, choices, and base cases

Let $dp[i,c]$ be the greatest value obtainable using the **first $i$ items**, with capacity $c$. Here, $i$ tells us which items remain available, and $c$ tells us how much weight they may use. The final answer is $dp[n,W]$.

For item $i$, there are two possibilities. **Skip it**, keeping capacity $c$ and using only the first $i-1$ items. Or **take it**, gaining $v_i$ and leaving capacity $c-w_i$ for those same first $i-1$ items. Both branches reduce $i$, so the item cannot be taken again:

$$
dp[i,c]=
\begin{cases}
dp[i-1,c], & w_i>c,\\
\max\bigl(dp[i-1,c],\;v_i+dp[i-1,c-w_i]\bigr), & w_i\le c.
\end{cases}
$$

With no available items or zero capacity, the answer is zero: $dp[0,c]=0$ and $dp[i,0]=0$. Positive weights make the zero-capacity base case valid. The recurrence is exhaustive because every solution either includes item $i$ or excludes it. Within either choice, replacing a remaining selection with a better feasible selection would improve the total. Therefore, the remaining selection can be chosen optimally.

#### Top-down memoization

Start by requesting $dp[n,W]$ and recursively request the smaller states it needs. Before solving a state, check its entry in `mem`. An unknown entry means we must calculate the answer; a recorded value can be returned immediately. Store the answer for **every solved non-base state**, including a forced skip when the item is too heavy. An unknown marker must be distinguishable from zero, which is a valid answer.

For a small overlap example, take four items with weights $(2,3,2,2)$, values $(3,4,3,3)$, and capacity $6$. Starting from $(4,6)$, skipping item $4$ and taking item $3$ reaches $(2,4)$. Taking item $4$ and skipping item $3$ reaches that same state. Both requests ask for the best value from the first two items with capacity $4$, which is $4$. After the first request stores that answer, the second reads it instead of exploring its choices again.

Two histories reach the same state $(2,4)$. Compute its answer once, then read it from the memo table.

![[attachments/design-knapsack-memo-overlap.png|500]]

The already selected items contribute value outside the recursive call; the call itself returns only the best **additional** value available from its state. This is why different selection histories can share the same stored answer.

#### Bottom-up two-dimensional tabulation

Tabulation uses the same recurrence and fills a table with rows $0$ through $n$ and columns $0$ through $W$. Set row $0$ and column $0$ to zero. Complete the row for item $1$, then item $2$, and continue through item $n$. Within each row, visit capacities $1$ through $W$. Both candidate answers come from the **previous row**, which is already complete.

For the worked table, use three items with $(\text{weight},\text{value})$ equal to $(2,3)$, $(3,4)$, and $(4,5)$, and capacity $W=6$. Their completed rows are shown below. Each entry is the best value for that row's available items and that column's capacity.

| Available items / capacity $c$ | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| None | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| Item 1: $(2,3)$ | 0 | 0 | 3 | 3 | 3 | 3 | 3 |
| Items 1–2; new item $(3,4)$ | 0 | 0 | 3 | 4 | 4 | 7 | 7 |
| Items 1–3; new item $(4,5)$ | 0 | 0 | 3 | 4 | 5 | 7 | 8 |

Consider the last cell. Skipping item $3$ gives $dp[2,6]=7$. Taking it gives $5+dp[2,2]=5+3=8$. We write the larger value, $dp[3,6]=8$. Items $1$ and $3$ achieve it: their weights total $6$, and their values total $8$. Reading the previous row in the take branch ensures that this newly taken item is not available again.

Each 0–1 update reads the previous row. Three item rows and six positive capacities give $18$ constant-work updates.

![[attachments/design-knapsack-zero-one-table.png|500]]

#### Time and auxiliary space

- **Memoization:** $O(nW)$ time and $O(nW)$ table space, plus $O(n)$ recursion-stack space, for $n,W\ge1$.
- **Two-dimensional tabulation:** $\Theta(nW)$ time and $\Theta(nW)$ auxiliary space, for $n,W\ge1$.

There are $(n+1)(W+1)$ possible states. Each computed non-base state makes at most two smaller-state requests and performs a constant amount of arithmetic and comparison. Memoization computes each such state once; later requests read its recorded value. A full memo table also takes time proportional to its size to prepare, even when recursion reaches only some states. Every recursive branch decreases $i$, so at most $n+1$ calls are active together.

Tabulation explicitly processes $nW$ non-base cells, with constant work per cell. The two-dimensional table retains $(n+1)(W+1)$ entries, and iteration requires no recursion stack. Including boundary cases, table allocation and storage are $\Theta((n+1)(W+1))$.

The dependence on $W$ makes this **pseudopolynomial** time. $W$ is the capacity's numerical value; its binary representation takes only $\Theta(\log(W+1))$ bits for positive $W$. A table with $W+1$ columns can therefore be exponentially large in the number of bits used to write the capacity.

### 5.4 Dynamic programming — Unbounded knapsack

**Unbounded knapsack** keeps the same capacity constraint and maximizes the same total value, but each item type can be selected any number of times. Continue to assume positive integer weights: taking an item must reduce the remaining capacity. The state $dp[i,c]$ now means the best value obtainable using any number of copies of the first $i$ item types, within capacity $c$.

#### What changes in the recurrence

Skipping item type $i$ still moves to $dp[i-1,c]$. Taking one copy gains $v_i$ and reduces capacity to $c-w_i$, but **keeps $i$ available**. We can take another copy if it fits:

$$
dp[i,c]=
\begin{cases}
dp[i-1,c], & w_i>c,\\
\max\bigl(dp[i-1,c],\;v_i+dp[i,c-w_i]\bigr), & w_i\le c.
\end{cases}
$$

Only the take branch changes: $dp[i-1,c-w_i]$ becomes $dp[i,c-w_i]$. A solution either uses no copies of item $i$, or contains a copy whose removal leaves a smaller-capacity problem in which item $i$ is still permitted. The base cases remain $dp[0,c]=0$ and $dp[i,0]=0$.

#### Bottom-up table and computation order

Fill rows in increasing item order and capacities **from small to large** within each row. The skip branch reads the completed previous row. The take branch reads a smaller capacity in the **current row**. Because $w_i>0$, that cell is to the left and has already been computed. This left-to-right order allows repeated copies of the current item to build on one another.

Use the same three item types $(2,3)$, $(3,4)$, and $(4,5)$ with capacity $6$. When processing item $1$, capacity $2$ gives value $3$. At capacity $4$, taking another copy uses the current row's capacity-$2$ answer: $3+dp[1,2]=6$. At capacity $6$, another copy gives $3+dp[1,4]=9$. These are three successive updates in the same row.

The take branch reads leftward within the current row. Repeated copies come from stored answers, while each cell still takes constant work.

![[attachments/design-knapsack-unbounded-table.png|500]]

| Available types / capacity $c$ | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| None | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| Type 1: $(2,3)$ | 0 | 0 | 3 | 3 | 6 | 6 | 9 |
| Types 1–2; new type $(3,4)$ | 0 | 0 | 3 | 4 | 6 | 7 | 9 |
| Types 1–3; new type $(4,5)$ | 0 | 0 | 3 | 4 | 6 | 7 | 9 |

The final answer is $9$, obtained by taking three copies of type $1$. The final cell still compares two choices: skipping type $3$ gives $dp[2,6]=9$, while taking it gives $5+dp[3,2]=8$. The earlier value wins. Allowing repetition changes the available solutions, while each individual cell still compares only two candidates.

#### Time and auxiliary space

- **Two-dimensional tabulation:** $\Theta(nW)$ time and $\Theta(nW)$ auxiliary space for $n,W\ge1$; including boundary cases, $\Theta((n+1)(W+1))$ for table allocation and storage.

Unlimited copies do not add another loop over all possible copy counts. One transition takes one copy and uses a stored answer that already allows more copies. There are still $nW$ non-base cells, and each requires a constant number of table reads, one addition when the item fits, and a comparison. The whole table has $(n+1)(W+1)$ entries. This bound is pseudopolynomial for the same reason as in 0–1 knapsack: the number of capacity columns depends on the numerical value of $W$.

### 5.5 Greedy algorithms — Fractional knapsack

A **greedy algorithm** commits to the best available choice under a particular rule, then solves the remaining problem. It does not undo that choice later. The rule needs a correctness argument: a choice that looks best now is not automatically part of an optimal solution.

Two properties justify this approach. The **greedy-choice property** says that at least one optimal solution can begin with our chosen move. **Optimal substructure** says that, after making that move, an optimal solution to the remaining problem completes an optimal overall answer.

Rank the available choices, commit to the best allowed choice, then repeat on the remaining problem. The rule needs a proof that these choices preserve an optimal solution.

![[attachments/greedy-method.png|500]]

#### Problem and greedy choice

There are $n$ items. Item $i$ has weight $w_i>0$ and value $v_i\ge0$, and the bag holds at most weight $W$. Each item is available once, but we may take a fraction $x_i$ between $0$ and $1$. Taking that fraction uses weight $x_iw_i$ and earns value $x_iv_i$.

We want to maximize $\sum_i x_iv_i$ while keeping $\sum_i x_iw_i\le W$. Because fractions are allowed, each unit of capacity can go to the remaining item with the highest **value per unit weight**, $\rho_i=v_i/w_i$.

#### How to solve it

1. Compute each item's ratio and sort the items from highest ratio to lowest.
2. Keep the remaining capacity $R$, initially $W$, and total value, initially $0$.
3. Take weight $t=\min(w_i,R)$ from the next item. Add $t\rho_i$ to the value and subtract $t$ from $R$.
4. Stop when $R=0$ or no items remain. If all items fit, taking all of them is valid even when capacity remains unused.

For items $A=(10,60)$, $B=(20,100)$, and $C=(30,120)$, the ratios are $6,5,4$. With capacity $50$, take all of A and B, then $20/30$ of C. The weights are $10+20+20=50$, and the value is $60+100+80=240$.

Use the highest value per unit weight first. The final item is split to use exactly the remaining capacity.

![[attachments/fractional-knapsack-take-trace.png|500]]

#### Why the greedy choice is correct

Suppose a proposed solution uses some weight from a lower-ratio item while a higher-ratio item remains available. Replace a small weight $\delta$ of the lower-ratio item with the same weight of the higher-ratio one. The total weight stays unchanged, and the value changes by

$\delta(\rho_{\text{high}}-\rho_{\text{low}})\ge0.$

This **exchange argument** shows that taking the higher-ratio item first cannot reduce the best attainable value. Repeating the exchange produces the greedy arrangement. After fixing each choice, the remaining capacity and items form another fractional-knapsack problem. Equal ratios can be processed in either order.

The permission to split items is essential. With the same items and capacity in **0–1 knapsack**, ratio order takes A and B for value $160$, leaving too little room for C. Taking B and C instead gives $220$. That exchange cannot be repaired by taking only part of C when items must remain whole.

#### Time and auxiliary space

- **Compute ratios:** $\Theta(n)$ time.
- **Comparison-sort by ratio:** $O(n\log n)$ worst-case time.
- **Take items in sorted order:** $O(n)$ time; $\Theta(n)$ if every item is considered.
- **Total:** $O(n\log n)$ worst-case time for this sorting-based algorithm.
- **Auxiliary space:** $O(n)$ for the item records and sorting workspace in the implementation from the notes. The remaining-capacity and total-value counters alone use $\Theta(1)$ space.

#### Why these bounds hold

Every item gets one ratio and is considered at most once after sorting. Taking an item or a fraction uses constant-time arithmetic; it does not loop over its weight or the bag's capacity. Sorting therefore dominates the linear preparation and selection passes. If the items are already supplied in ratio order, the selection pass needs only $O(n)$ time. These bounds use the same constant-time arithmetic assumption as the rest of the review.
