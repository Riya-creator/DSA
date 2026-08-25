# LeetCode 31 — Next Permutation

## 1. Core Concept

The goal is to transform a given permutation into the **next lexicographically greater permutation**.

Think of permutations like numbers:

```text
123 → 132 → 213 → 231 → 312 → 321
```

The task is to move exactly **one step forward** in this ordering.

If the current permutation is already the largest possible arrangement, we wrap around to the smallest arrangement.

Example:

```text
123 → 132
132 → 213
213 → 231
231 → 312
312 → 321
321 → 123
```

---

## 2. Main Intuition

The key idea is:

> **Make the permutation larger at the rightmost possible position, and increase it by the smallest possible amount.**

After doing that, make everything after that position as small as possible.

This naturally leads to three major operations:

1. Find the **pivot**
2. Swap it with the appropriate element
3. Reverse the suffix

---

## 3. Finding the Pivot

Start scanning from the **right side**.

Find the first position where:

```text
nums[i] < nums[i + 1]
```

This element is called the **pivot**.

Why?

Because everything to its right is in **decreasing order**.

Example:

```text
1 2 7 6 5 4 3
  ↑
 pivot
```

Here:

```text
2 < 7
```

So `2` is the pivot.

### Why scan from the right?

We want the **rightmost position that can be increased**.

Changing a position farther to the right causes a smaller overall change, which is exactly what we need for the **next** permutation rather than some much larger permutation.

---

## 4. What If No Pivot Exists?

Suppose we have:

```text
5 4 3 2 1
```

There is no position where:

```text
nums[i] < nums[i + 1]
```

The entire array is decreasing.

That means it is already the **largest possible permutation**.

Therefore, the next permutation wraps around to the smallest one:

```text
5 4 3 2 1
      ↓
1 2 3 4 5
```

So in this case, reverse the entire array.

---

## 5. Finding the Element to Swap

Once the pivot is found, we need to make it larger.

Suppose:

```text
1 2 7 6 5 4 3
  ↑
 pivot = 2
```

We need an element greater than `2`.

Search from the **right side**.

The first element greater than the pivot is:

```text
3
```

So we swap:

```text
1 2 7 6 5 4 3
  ↓           ↓

1 3 7 6 5 4 2
```

### Why the first greater element from the right?

Because the suffix is already in decreasing order.

Therefore, when scanning from the right, the first element greater than the pivot is the **smallest element greater than the pivot**.

This is important.

We don't just want:

> Any element greater than the pivot.

We want:

> **The smallest possible element greater than the pivot.**

That ensures we increase the permutation by the smallest possible amount.

---

## 6. Why Do We Reverse the Suffix?

After swapping:

```text
1 3 7 6 5 4 2
  ↑
 pivot position
```

The suffix is:

```text
7 6 5 4 2
```

This is still decreasing.

But remember our goal:

> Get the smallest permutation that is still greater than the original.

We have already made the number larger by changing:

```text
2 → 3
```

Now the prefix is fixed.

Therefore, everything after the pivot should be arranged in the **smallest possible order**.

The smallest arrangement of:

```text
7 6 5 4 2
```

is:

```text
2 4 5 6 7
```

Since the suffix is already decreasing, reversing it gives exactly that:

```text
7 6 5 4 2
        ↓
2 4 5 6 7
```

Final permutation:

```text
1 3 2 4 5 6 7
```

---

## 7. Why Not Sort the Suffix?

We could technically sort the suffix, but that is unnecessary.

The important observation is:

> After finding the pivot, the suffix is already in decreasing order.

Therefore:

```text
decreasing order
        ↓
     reverse
        ↓
increasing order
```

And increasing order is the **minimum possible arrangement** of those elements.

This saves us from using a sorting algorithm.

---

## 8. Complete Mental Model

The entire algorithm can be remembered as:

### Step 1 — Find where we can increase

Scan from the right and find:

```text
nums[i] < nums[i + 1]
```

This is the pivot.

### Step 2 — Increase it as little as possible

From the right, find the first element greater than the pivot.

Swap them.

### Step 3 — Minimize everything after it

Reverse the suffix after the pivot.

### Special Case

If no pivot exists:

```text
array is completely decreasing
        ↓
already the largest permutation
        ↓
reverse entire array
        ↓
smallest permutation
```

---

## 9. Important Reasoning Pattern

The problem is a nice example of **local change + global minimization**.

We do:

```text
1. Find the latest possible position to change
2. Increase it by the smallest possible amount
3. Minimize everything after it
```

This pattern is useful beyond this problem.

Whenever you see something like:

> "Find the next greater arrangement"

think:

**Make the smallest possible change as far right as possible.**

---

## 10. Why the Algorithm Works

The suffix after the pivot is decreasing.

Therefore:

* No permutation using only that suffix can be larger while keeping the prefix unchanged.
* The pivot is the rightmost position where an increase is possible.
* Choosing the smallest value greater than the pivot gives the smallest possible increase.
* Reversing the suffix produces its minimum arrangement.

Therefore, the resulting permutation is the **immediate next lexicographical permutation**.

---

## 11. Example Walkthrough

Consider:

```text
1 2 3 6 5 4
```

### Find pivot

From right:

```text
5 > 4
6 > 5
3 < 6  ← pivot
```

Pivot:

```text
3
```

### Find smallest greater element

From the right:

```text
4 > 3
```

Swap:

```text
1 2 4 6 5 3
```

### Reverse suffix

Suffix:

```text
6 5 3
```

Reverse:

```text
3 5 6
```

Result:

```text
1 2 4 3 5 6
```

This is the immediate next permutation.

---

## 12. Complexity

### Time Complexity

**O(n)**

There are at most three linear operations:

* Find the pivot → `O(n)`
* Find the swap element → `O(n)`
* Reverse the suffix → `O(n)`

Overall:

```text
O(n) + O(n) + O(n) = O(n)
```

Since constant factors are ignored:

**Time = O(n)**

### Space Complexity

**O(1)** extra space.

The transformation is performed **in-place**.

No additional array proportional to `n` is required.

---

## 13. Quick Revision

```text
NEXT PERMUTATION

1. Scan from RIGHT
2. Find first nums[i] < nums[i+1]
      ↓
   pivot

3. If no pivot:
      reverse everything

4. Otherwise:
      find first element > pivot from RIGHT
      ↓
      swap

5. Reverse everything AFTER pivot
```

### One-line memory trick

> **Find → Swap → Reverse**

Or even better:

> **Increase minimally → Minimize the suffix**

---

## 14. Common Mistakes

### Mistake 1: Finding any increasing pair

We need the **rightmost** valid pair, not just the first one from the left.

---

### Mistake 2: Choosing any greater element

We need the **smallest element greater than the pivot**.

Scanning from the right gives it automatically because the suffix is decreasing.

---

### Mistake 3: Reversing the entire array every time

Only reverse the entire array when **no pivot exists**.

Otherwise, reverse only the part **after the pivot**.

---

### Mistake 4: Sorting the suffix

Sorting works conceptually but is unnecessary.

The suffix is already decreasing, so a simple reversal produces the required increasing order.

---

## Final Mental Picture

```text
        Find the pivot
              ↓
    increase it minimally
              ↓
   make suffix as small as possible
              ↓
       NEXT PERMUTATION
```

**Core insight:**

> Find the rightmost place where the permutation can become larger, make the smallest possible increase there, then put everything after it into the smallest possible order.
