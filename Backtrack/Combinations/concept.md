# LeetCode 77 — Combinations

## 📌 Problem Overview

The goal is to generate **all possible combinations** of `k` numbers chosen from the range `[1, n]`.

A **combination** focuses only on **which elements are selected**, **not the order** in which they are selected.

For example, if `n = 4` and `k = 2`:

✅ Valid combinations:

```text
[1,2]
[1,3]
[1,4]
[2,3]
[2,4]
[3,4]
```

Notice that:

```text
[1,2] == [2,1]
```

They represent the **same combination**, so only one of them should be included.

---

# 🧠 Core Concept Used

This problem is a classic application of **Backtracking** with a **Starting Index**.

Instead of trying every possible arrangement, we progressively build one combination while ensuring that we never revisit previously considered numbers.

The important idea is:

> Once a number has been chosen, every future choice must come only from the numbers after it.

This simple rule automatically avoids duplicates.

---

# 🌱 Why "Start Index" Works

Suppose we have already chosen:

```text
[2]
```

Now, should we again consider:

```text
1
```

No.

If we did,

```text
[2,1]
```

would simply be another ordering of

```text
[1,2]
```

which is already included.

Therefore, after choosing `2`, we only explore

```text
3
4
5
...
```

This is exactly why every recursive call carries a **starting index**.

---

# 🔄 Dry Run

Example:

```text
n = 4
k = 2
```

Start:

```text
[]
```

Choose `1`

```text
[1]
```

Remaining choices:

```text
2
3
4
```

Generate

```text
[1,2]
[1,3]
[1,4]
```

Backtrack.

---

Choose `2`

```text
[2]
```

Remaining choices:

```text
3
4
```

Generate

```text
[2,3]
[2,4]
```

Backtrack.

---

Choose `3`

```text
[3]
```

Remaining choices:

```text
4
```

Generate

```text
[3,4]
```

Backtrack.

---

Choose `4`

No numbers remain.

Algorithm finishes.

Final answer:

```text
[1,2]
[1,3]
[1,4]
[2,3]
[2,4]
[3,4]
```

Observe something interesting:

The algorithm **never even attempts**

```text
[2,1]
[3,1]
[4,2]
```

These states simply do not exist in the recursion tree.

This is much better than generating duplicates and removing them later.

---

# 🌳 Understanding the Recursion Tree

The recursion tree naturally grows only in the forward direction.

```text
                []
          /      |      |      \
        1        2      3       4
      / | \      | \     |
     2  3  4     3 4     4
```

Notice how:

- `2` never points back to `1`
- `3` never points to `1` or `2`
- Every level only moves forward

This forward-only traversal is the secret behind generating combinations efficiently.

---

# ⚠️ Common Mistake

One of the most common mistakes is to solve the problem exactly like a **Permutation** problem.

Many beginners think:

> "I'll keep a visited array so that no number is repeated."

Although this sounds reasonable, it actually generates **permutations**, not combinations.

For example,

```text
Choose 1 → Choose 2
```

produces

```text
[1,2]
```

Later,

```text
Choose 2 → Choose 1
```

produces

```text
[2,1]
```

Both represent the same combination.

The visited array only prevents choosing the **same element twice**.

It **does not prevent different orderings** of the same selection.

---

# 🎯 Combination vs Permutation

| Combination | Permutation |
|-------------|-------------|
| Order does **not** matter | Order matters |
| `[1,2]` and `[2,1]` are identical | `[1,2]` and `[2,1]` are different |
| Uses a **Starting Index** | Uses a **Visited Array** |
| Moves only forward | Can move anywhere |
| No duplicate orderings generated | Every ordering is generated |

---

# 💡 Mental Model

Imagine choosing students for a team.

You only care **who is selected**.

You do **not** care in which order you picked them.

```text
Alice
Bob
Charlie
```

is exactly the same team as

```text
Charlie
Alice
Bob
```

Now imagine arranging students on a stage.

Order suddenly matters.

```text
Alice Bob Charlie
```

is different from

```text
Charlie Alice Bob
```

That is the difference between combinations and permutations.

---

# 🚀 Why We Don't Need a Visited Array

Since every recursive call only moves forward,

```text
1 → 2 → 3
```

it is impossible to revisit

```text
2 → 1
```

Therefore,

- no duplicates occur
- no element is revisited
- no extra memory is needed for tracking visited elements

The recursion path itself guarantees correctness.

---

# 📈 Time Complexity

There are exactly

```
C(n, k)
```

possible combinations.

Since every combination contains `k` elements,

**Time Complexity**

```text
O(C(n,k) × k)
```

---

**Auxiliary Space**

The recursion depth is at most

```text
k
```

Hence,

```text
O(k)
```

excluding the output array.

---

# 🧩 Pattern Recognition

Whenever you encounter a problem that says:

- Choose `k` elements
- Pick some numbers
- Select a subset
- Team formation
- Group selection
- Choose any `k`
- Subsequences of fixed length

there is a very high chance that the solution uses:

- Backtracking
- Starting Index
- Forward traversal

---

# 🔍 Tech Tip

A simple interview trick:

Ask yourself one question.

> **Can the same set appear in different orders?**

If the answer is **No**, think **Combination**.

If the answer is **Yes**, think **Permutation**.

This one question can often help you choose the correct recursion strategy within seconds.

---

# 🧠 Memory Trick

Remember this rule forever:

```text
Permutation
=
Who is NOT used yet?
```

↓

Use a **Visited Array**

---

```text
Combination
=
Where should I start next?
```

↓

Use a **Starting Index**

---

# ✨ Key Takeaways

- Backtracking is used to explore every valid possibility.
- A starting index guarantees forward traversal.
- Forward traversal automatically removes duplicate orderings.
- A visited array is suitable for permutations, not combinations.
- The recursion tree itself enforces uniqueness.
- Understanding **why** duplicates disappear is more valuable than simply memorizing the implementation.
- When the problem asks to **select**, think combinations.
- When the problem asks to **arrange**, think permutations.

---

## 📚 Final Learning

The biggest lesson from this problem is not the recursion itself.

It is learning **how to model the search space**.

Instead of generating every possibility and filtering duplicates later, design the recursion so that **invalid states are never created in the first place**.

This mindset is widely used in advanced algorithms, competitive programming, and technical interviews because preventing unnecessary work is almost always more efficient than correcting it afterward.
