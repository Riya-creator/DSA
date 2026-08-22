# LeetCode 6 — Zigzag Conversion

## 1. Core Concept

The problem asks us to rearrange a string by writing it in a **zigzag pattern** across a given number of rows and then reading the rows from top to bottom.

The main challenge is not the string manipulation itself, but recognizing that the zigzag follows a **repeating pattern**.

The two useful approaches are:

1. **Simulation approach** — actually move down and diagonally up through the rows.
2. **Pattern/index approach** — mathematically calculate which characters belong to each row.

Both have:

* **Time:** O(n)
* **Space:** O(n)

The second approach mainly reduces unnecessary simulation rather than improving Big-O complexity.

---

# 2. Most Important Observation — Repeating Cycle

For `R` rows, one complete zigzag cycle contains:

**2 × (R − 1)** characters.

This is the most important formula in the problem.

Think of the movement as:

```text
DOWN → DOWN → ... → DOWN
                         ↘
                         UP → UP → ... → UP
```

The pattern repeats after reaching the bottom and coming back to the top.

### Example: 4 rows

The movement pattern is:

```text
0
1
2
3
2
1
0
1
2
3
...
```

The cycle length is:

**2 × (4 − 1) = 6**

So positions repeat every 6 characters.

---

# 3. Understanding the Rows

The first and last rows are special.

### First row

Characters occur once per cycle.

### Last row

Characters also occur once per cycle.

### Middle rows

Characters occur **twice per cycle**:

* One while moving downward.
* One while moving upward.

This is why the middle rows need two different gaps between characters.

---

# 4. The Gap Pattern

For a middle row, the distances between characters alternate.

The two gaps depend on:

* Number of rows
* Current row number
* Cycle length

The important conceptual point is:

> **The farther a row is from the top, the smaller its downward gap and the larger its upward gap.**

For example, with 4 rows:

```text
Row 0 → one large repeating gap

Row 1 → large gap, small gap, large gap, small gap...

Row 2 → small gap, large gap, small gap, large gap...

Row 3 → one large repeating gap
```

This symmetry is the key to deriving the direct mathematical solution.

---

# 5. Simulation vs Mathematical Approach

## Simulation

Actually maintain the current row and direction:

```text
↓
↓
↓
↑
↑
↑
↓
↓
...
```

Whenever the bottom is reached, change direction.

### Advantages

* Easier to derive.
* Easier to visualize.
* Less mathematical.
* Good approach to use initially in an interview.

### Disadvantage

You explicitly simulate the movement even though the pattern is predictable.

---

## Mathematical / Index Approach

Instead of moving through the zigzag, determine:

> Which positions belong to this row?

Then directly jump between those positions.

### Advantages

* More direct.
* No need to track direction.
* No need to simulate movement.
* Useful when the pattern is clearly periodic.

### Disadvantage

* The gap formulas are harder to derive initially.
* Easier to make an indexing mistake.

---

# 6. Why Both Are O(n)

A nested loop does **not automatically mean O(n²)**.

The important thing is:

> How many times is each character processed?

Every character is visited exactly once.

Therefore:

**Time = O(n)**

The answer itself contains `n` characters, so storing the result already requires:

**Space = O(n)**

This is a good example of why loop nesting should not be judged blindly.

---

# 7. Special Cases to Check

Always identify edge cases before implementing.

### One row

If there is only one row, there is no zigzag.

The answer is simply the original string.

### Number of rows ≥ string length

There aren't enough characters to form multiple meaningful rows.

Again, the original string is already the answer.

### Very small strings

Check empty/single-character behavior depending on the problem constraints.

---

# 8. How to Derive the Pattern Yourself

When you encounter a pattern-based problem, don't immediately memorize formulas.

Use this process:

### Step 1 — Draw a small example

Use 3 or 4 rows.

### Step 2 — Write indices

Instead of only writing characters, write:

```text
0
1
2
3
2
1
0
...
```

### Step 3 — Find repetition

Ask:

> After how many positions does the pattern repeat?

This gives the cycle.

### Step 4 — Pick one row

Track only the positions belonging to that row.

### Step 5 — Calculate the gaps

Look at the distance between consecutive positions.

### Step 6 — Generalize

Once the pattern is obvious, derive the formula.

This technique is much more reliable than trying to memorize formulas.

---

# 9. General Pattern-Recognition Technique

This problem teaches a broader algorithmic skill:

## Don't simulate a deterministic pattern blindly.

Whenever you see:

* Repeating movement
* Cyclic behavior
* Alternating gaps
* Periodic indices
* Repeated states
* Regular mathematical patterns

ask:

> **Can I jump directly to the next relevant position?**

This can turn complicated-looking simulations into simple index calculations.

---

# 10. Complexity Checklist

When analyzing similar problems, ask:

### Time

* How many times is each element visited?
* Are elements revisited?
* Is there sorting?
* Is there a nested loop?
* Does the inner loop process the same elements repeatedly?

### Space

* Am I creating another array/string?
* Am I storing all elements?
* Is the output itself counted?
* Am I using extra data structures?

Don't assume:

```text
nested loops = O(n²)
```

Instead, count the **total amount of work**.

---

# 11. Common Mistakes

### Mistake 1 — Forgetting the one-row case

The cycle formula becomes invalid when:

**R = 1**

because:

**2 × (R − 1) = 0**

which can cause an infinite loop.

---

### Mistake 2 — Mixing up row and index

Keep these concepts separate:

* `row` → which zigzag row you're processing.
* `i` → current position in the string.

---

### Mistake 3 — Incorrect middle-row gaps

The first and last rows have one character per cycle.

Middle rows have two.

Treating every row identically usually causes indexing bugs.

---

### Mistake 4 — Overcomplicating the problem

This is fundamentally a **pattern/indexing problem**, not a graph or DP problem.

Don't introduce unnecessary data structures.

---

# 12. Interview Strategy

A good progression during an interview is:

```text
Understand the zigzag
       ↓
Draw an example
       ↓
Identify the cycle
       ↓
Build simulation solution
       ↓
Analyze complexity
       ↓
If asked to optimize → derive direct indices
```

This is much safer than trying to immediately remember the mathematical formula.

---

# 13. Key Takeaways

### Remember these ideas:

* Zigzag movement is **periodic**.
* One cycle contains **2 × (rows − 1)** characters.
* First and last rows have one character per cycle.
* Middle rows have two characters per cycle.
* The gaps of middle rows alternate.
* Simulation and mathematical approaches are both **O(n)**.
* Output storage makes the solution **O(n) space**.
* Nested loops don't automatically imply O(n²).
* For periodic problems, look for a **cycle and jump between relevant indices**.
* When deriving formulas, use a small example and track **indices**, not characters.

---

## Pattern to Remember

The most valuable lesson from this problem isn't the exact formula.

It's this:

> **When a process follows a predictable repeating pattern, try to replace simulation with direct index jumps.**

That idea shows up again in array traversal, string manipulation, cyclic problems, mathematical simulations, and many competitive-programming problems.
