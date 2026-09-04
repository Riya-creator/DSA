# LeetCode 12 — Integer to Roman

## 🧠 Problem Concept

The task is to convert an integer into its corresponding **Roman numeral representation**.

Roman numerals use a fixed set of symbols:

| Value | Symbol |
| ----: | :----: |
|  1000 |    M   |
|   900 |   CM   |
|   500 |    D   |
|   400 |   CD   |
|   100 |    C   |
|    90 |   XC   |
|    50 |    L   |
|    40 |   XL   |
|    10 |    X   |
|     9 |   IX   |
|     5 |    V   |
|     4 |   IV   |
|     1 |    I   |

The important observation is that Roman numerals are **not purely additive**.

For example:

* 8 → VIII
* 9 → IX
* 40 → XL
* 90 → XC
* 400 → CD
* 900 → CM

The values such as **4, 9, 40, 90, 400, and 900** represent the subtractive notation.

---

# 🔑 Core Idea — Greedy Approach

The key idea is:

> **Always take the largest Roman numeral value that can fit into the remaining number.**

For example, consider:

**58**

Start with the largest possible value:

* 50 → L
* remaining = 8
* 5 → V
* remaining = 3
* 1 → I
* remaining = 2
* 1 → I
* remaining = 1
* 1 → I

Result:

**LVIII**

This works because Roman numeral representation follows a structure where choosing the largest valid denomination first leads to the correct representation.

This is a classic **Greedy Algorithm** pattern.

---

# ⚡ The Important Trick

A very useful trick is to treat the subtractive combinations as if they were **individual denominations**.

Instead of thinking:

> "How do I construct 900 using C and M?"

Think:

> "900 is simply another valid Roman numeral unit: CM."

So your conceptual value list becomes:

**1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1**

Notice that it is already sorted in descending order.

This makes the problem almost mechanical:

1. Pick the largest value.
2. Use it as many times as possible.
3. Move to the next value.
4. Continue until nothing remains.

---

# 🎯 Why Descending Order Matters

Suppose you process the denominations from largest to smallest.

For every denomination:

> **How many times can this value fit into the remaining number?**

For example:

**1994**

Break it conceptually into:

* 1000 → M
* 900 → CM
* 90 → XC
* 4 → IV

Therefore:

**MCMXCIV**

The descending order prevents you from accidentally constructing a value using smaller symbols when a special subtractive representation should be used.

---

# 🧩 Important Pattern to Recognize

This problem teaches an extremely useful DSA pattern:

### Value → Representation Mapping

You have:

**number → corresponding symbol**

For example:

* 1000 → M
* 500 → D
* 100 → C
* ...

This is essentially a collection of **paired values and representations**.

Whenever you see a problem involving:

* fixed denominations
* fixed symbols
* repeated selection
* largest possible choice
* constructing a representation

you should consider whether a **greedy + ordered mapping** solution exists.

---

# 🚨 Common Mistake

A common mistake is to only consider:

**1000, 500, 100, 50, 10, 5, 1**

and ignore:

**900, 400, 90, 40, 9, 4**

That approach fails because subtractive notation is an important part of Roman numerals.

For example:

**9 ≠ VIIII**

The standard representation is:

**IX**

Therefore, the six subtractive combinations should be treated as first-class cases.

---

# 💡 Another Way to Think About It

You can imagine the problem as having **13 available "coins"**:

| Coin Value | Roman Representation |
| ---------: | :------------------: |
|       1000 |           M          |
|        900 |          CM          |
|        500 |           D          |
|        400 |          CD          |
|        100 |           C          |
|         90 |          XC          |
|         50 |           L          |
|         40 |          XL          |
|         10 |           X          |
|          9 |          IX          |
|          5 |           V          |
|          4 |          IV          |
|          1 |           I          |

Then the problem becomes:

> **Represent the number using these denominations, always choosing the largest possible denomination first.**

This is basically a **coin-change-like greedy problem**, except the denominations and their representations are fixed and the Roman numeral rules make the greedy choice valid.

---

# 🧠 Why This Problem Is Important

At first glance, Integer to Roman looks like a simple string-conversion problem.

But it teaches several concepts that appear repeatedly in DSA.

### 1. Greedy Thinking

You learn to ask:

> "Can I make the locally best choice and still reach the globally correct answer?"

Here, choosing the largest valid Roman value works.

---

### 2. Ordering as a Problem-Solving Tool

The descending order of denominations isn't just cosmetic.

It creates a natural processing order that makes the solution straightforward.

A lot of problems become easier when you find the **correct ordering** first.

---

### 3. Handling Special Cases Elegantly

Instead of creating a huge collection of conditions for:

* 4
* 9
* 40
* 90
* 400
* 900

you can incorporate them into the same general structure.

This is an important engineering lesson:

> **Try to represent special cases as data rather than hard-code them as separate logic.**

That makes the solution cleaner and easier to reason about.

---

### 4. Separating Data From Logic

The Roman numeral rules are essentially **data**:

> value ↔ symbol

The conversion procedure is the **logic**.

Keeping these concepts separate is a useful design principle far beyond this problem.

---

# 🔍 How to Detect This Pattern in Future Problems

When you encounter a conversion/construction problem, ask:

### Question 1

Are the possible values fixed?

If yes → consider storing them in an ordered structure.

### Question 2

Does choosing the largest available value make sense?

If yes → consider greedy.

### Question 3

Are there special combinations?

Instead of creating separate conditions, ask:

> Can I represent those special combinations as additional entries in my data?

### Question 4

Can the entire process be repeated using the same rule?

If yes → you may have found a simple greedy iteration.

---

# ⚙️ Complexity

Let **N** be the input number.

There are only **13 Roman numeral denominations** to consider.

Therefore, the number of denomination types is constant.

### Time Complexity

Effectively:

**O(number of Roman denominations + output length)**

Since the number of denominations is fixed, this is effectively:

**O(output length)**

### Space Complexity

Ignoring the output string:

**O(1)**

because only a fixed number of Roman numeral mappings are required.

---

# 🧪 Useful Examples

### Example 1

**3**

Breakdown:

3 × 1

→ III

---

### Example 2

**4**

Instead of:

1 + 1 + 1 + 1

use the subtractive representation:

4 → IV

---

### Example 3

**9**

9 → IX

---

### Example 4

**44**

Breakdown:

40 + 4

→ XL + IV

→ **XLIV**

---

### Example 5

**3999**

Breakdown:

3000 + 900 + 90 + 9

→ MMM + CM + XC + IX

→ **MMMCMXCIX**

---

# 💎 Key Takeaways

* Roman numerals have **7 basic symbols** but **13 useful denominations** for standard conversion.
* The six subtractive forms are crucial:

  * 4 → IV
  * 9 → IX
  * 40 → XL
  * 90 → XC
  * 400 → CD
  * 900 → CM
* Process denominations in **descending order**.
* Always choose the **largest denomination that fits**.
* This is a **greedy** pattern.
* Special cases can often be represented as **data instead of separate conditions**.
* The problem is a good example of turning a complicated-looking rule system into a simple repeated operation.

---

# 🚀 DSA Lesson

The biggest lesson from this problem isn't Roman numerals.

It's this:

> **When a problem has a fixed set of choices and repeatedly asks you to construct something, try ordering those choices and checking whether a greedy choice works.**

And one particularly useful habit:

> **Don't immediately write special-case `if/else` logic. First ask whether the special cases can be incorporated into your data representation.**

That habit will make your solutions significantly cleaner as you move toward harder DSA problems.
