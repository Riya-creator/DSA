# Next Greater Element I — Concept Notes

## Core Idea

The task is to find the **first greater element to the right** for each element of `nums1` based on its position in `nums2`.

This problem belongs to the **Monotonic Stack pattern**.

The stack maintains a **monotonic decreasing order** so that the nearest greater element can be found efficiently.

Stack property:

Monotonic Decreasing Stack  
(bottom → top = decreasing values)

Meaning:

- The top of the stack always represents the **nearest greater candidate** for upcoming elements.
- Smaller elements that cannot serve as next greater elements are removed.

Stack rule used:

```
while stack not empty AND stack.top() ≤ current element
    pop
```

Then:

```
nextGreater = stack.top() if exists
otherwise -1
```

---

# Approach 1 — Full Preprocessing

### Idea

Compute the **Next Greater Element for every value in `nums2` first**, store it in a map, then answer queries for `nums1`.

This approach builds the entire mapping before answering queries.

### Behaviour

- Traverse `nums2` once
- Maintain monotonic decreasing stack
- Store mapping:

```
value → next greater value
```

Then fetch answers for `nums1`.

### Complexity

Time Complexity:

```
O(n2 + n1)
```

Space Complexity:

```
O(n2 + n1)
```

Breakdown:

| Structure | Size |
|---|---|
answer array | n1  
map | n2  
stack | n2  

### Characteristics

Pros

- Simpler implementation
- Predictable execution
- Clean logic
- Very interview friendly

Cons

- Computes answers for **all elements**, even those not needed by `nums1`

---

# Approach 2 — Incremental (Lazy Processing)

### Idea

Instead of computing all results upfront, **build the mapping only when required**.

Processing of `nums2` happens **incrementally**.

We maintain:

- a processing pointer in `nums2`
- stack state
- partial map of computed results

Whenever a query from `nums1` requires a value whose result is not computed yet, processing of `nums2` continues until that value is reached.

### Behaviour

The stack invariant **remains identical** to the standard solution.

Monotonic stack condition:

```
while stack.top() ≤ current element
    pop
```

Even though the computation is incremental, the stack always maintains the **same decreasing structure**.

### Complexity

Time Complexity:

```
O(n1 + n2)
```

Space Complexity:

```
O(n1 + n2)
```

Reason:

Each element of `nums2` is:

- pushed once
- popped at most once

Thus total stack operations remain linear.

### Characteristics

Pros

- Demonstrates **lazy evaluation**
- Computes only the required elements initially
- Interesting conceptual approach

Cons

- Implementation complexity increases
- More condition checks and branching
- Harder to debug
- Query order can force processing the entire array anyway

---

# Key Difference Between the Two Approaches

| Feature | Full Preprocessing | Incremental Processing |
|---|---|---|
Processing style | upfront computation | lazy / on-demand |
Implementation difficulty | easier | more complex |
Predictability | very predictable | depends on query order |
Interview suitability | highly preferred | rarely used |

---

# Why the Incremental Method *Feels Slower*

Even though both have the same theoretical complexity:

```
O(n1 + n2)
```

the incremental method often appears slower in practice.

Reasons:

### 1. Extra conditional checks

Every query requires:

- map lookup
- boundary checks
- conditional processing

which increases instruction count.

---

### 2. More branching

The algorithm repeatedly checks:

```
if value already computed
else extend processing
```

Branch-heavy logic increases constant factors.

---

### 3. Memory access pattern

Full preprocessing performs:

```
one sequential scan of nums2
```

which is very cache friendly.

Incremental processing jumps between:

```
nums1
nums2
map
stack
```

which may reduce cache efficiency.

---

# Important Insight

Even though incremental processing builds the solution **in parts**, the worst case still requires processing **all elements of `nums2`**.

Therefore the total work remains:

```
Linear
```

but the extra logic makes it appear slower.

---

# Pattern Recognition Tip

Whenever a problem asks for:

- next greater element
- next smaller element
- nearest greater to left/right
- daily temperatures
- stock span
- largest rectangle in histogram

the correct mental trigger should be:

```
Monotonic Stack
```

Recognizing this pattern makes an entire class of problems much easier to solve.
