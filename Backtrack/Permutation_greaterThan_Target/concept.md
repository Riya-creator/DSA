
# LeetCode 3720 — Lexicographically Greater Permutation

## 1. Core Idea

The goal is to construct the **smallest permutation of the available characters that is strictly greater than the target string**.

The main idea is:

> Keep the prefix equal to the target for as long as possible.  
> If this cannot produce a strictly greater answer, backtrack and increase the **rightmost possible position**.

Once we make one position greater, the remaining characters should be placed in **ascending order** to make the overall answer as small as possible.

---

## 2. Greedy Thinking

Suppose we are currently at position `i`.

We want to keep the answer as close to the target as possible.

So we first try to choose:

```text
smallest available character >= target[i]
````

There are two cases.

### Case 1: Chosen character == target[i]

We are still equal to the target.

So we continue to the next position.

```text
target:  a b c ...
answer:  a b ...
```

This is desirable because keeping the prefix equal gives us the smallest possible answer.

### Case 2: Chosen character > target[i]

Now:

```text
answer[0 ... i-1] == target[0 ... i-1]
answer[i] > target[i]
```

Therefore:

```text
answer > target
```

is already guaranteed.

We no longer need to compare the suffix with the target.

So we simply arrange all remaining characters in ascending order.

---

## 3. Why the Suffix Is Sorted

Once we make one position greater:

```text
prefix + bigger_character
```

the answer is already greater than the target.

Therefore, the only remaining objective is:

> Make the suffix as small as possible.

The smallest permutation of the remaining characters is obtained by sorting them in ascending order.

For example:

```text
remaining:
c a b a

smallest suffix:
a a b c
```

So the final structure is:

```text
target prefix
+
smallest character that makes us greater
+
remaining characters in ascending order
```

---

## 4. Why the Forward Greedy Can Fail

The tricky situation is when we keep choosing characters equal to the target.

For example:

```text
target = a b a
answer = a b a
```

The answer is equal to the target, but the problem requires:

```text
answer > target
```

So this answer is invalid.

We need to go back and find a position where we can increase the character.

This is the **backtracking step**.

---

# 5. Why Backtrack From the Right

Suppose:

```text
target = a b c d
```

and we have already matched:

```text
a b c
```

If we can increase position `2`:

```text
a b e ...
```

that is better than increasing position `1`:

```text
a c ...
```

because:

```text
ab... < ac...
```

Therefore, to get the **smallest string greater than the target**, we should increase the **rightmost possible position**.

So:

```text
Start from the last position
        ↓
Move towards the beginning
        ↓
Find the first position that can be increased
```

This is one of the most important insights in the problem.

---

# 6. `lower_bound()` vs `upper_bound()`

This problem is a very good example of the difference between these two operations.

## `lower_bound(x)`

Returns the first element:

```text
>= x
```

Example:

```text
available = {a, c, f, k}

lower_bound(d)
        ↓
       f
```

because `f` is the smallest character that is at least `d`.

### Where we use it

During the forward greedy process:

```text
lower_bound(target[i])
```

because equality is allowed.

---

## `upper_bound(x)`

Returns the first element:

```text
> x
```

Example:

```text
available = {a, c, f, k}

upper_bound(c)
        ↓
       f
```

### Where we use it

During backtracking.

At that point we specifically need:

```text
character > target[i]
```

because we must make the answer strictly greater.

So:

```text
Forward pass → lower_bound()
Backtracking → upper_bound()
```

---

# 7. Why Use `map<char, int>`?

A `set<char>` might seem sufficient because we need ordered characters.

But there is an important problem:

### Duplicate characters

Suppose:

```text
s = "aabcc"
```

A set stores:

```text
{a, b, c}
```

The duplicate information is lost.

But when constructing a permutation, the number of occurrences matters.

Therefore we use:

```text
map<char, int>
```

Conceptually:

```text
a → 2
b → 1
c → 2
```

This gives us:

1. Character frequency
2. Sorted character order
3. `lower_bound()`
4. `upper_bound()`

So `map<char,int>` fits the problem nicely.

---

# 8. Consuming Characters

When we choose a character, its frequency decreases.

For example:

```text
a → 3
b → 1
c → 2
```

After using one `a`:

```text
a → 2
b → 1
c → 2
```

When a frequency becomes zero, the character can be removed from the map.

This keeps the map representative of the characters still available.

---

# 9. The Backtracking Problem

During the forward pass, we consume characters.

Suppose:

```text
target = a b a
```

and the available characters are:

```text
a a b
```

We first try to remain equal:

```text
a → equal
b → equal
a → equal
```

So we obtain:

```text
aba
```

But:

```text
aba == aba
```

which is invalid.

Now we need to backtrack.

---

# 10. Backtracking Example

At the last position:

```text
target[2] = a
```

We need a character:

```text
> a
```

But no such character is available.

So go to position `1`.

```text
target[1] = b
```

We need:

```text
> b
```

Again, nothing is available.

So go to position `0`.

```text
target[0] = a
```

Now:

```text
b > a
```

is possible.

Choose the smallest possible character greater than `a`:

```text
b
```

Then arrange everything remaining in ascending order:

```text
a a
```

Final result:

```text
baa
```

And:

```text
baa > aba
```

---

# 11. Why We Need the State Before Position `i`

When backtracking to position `i`, we need to know:

> Which characters were available before we chose the character at position `i`?

There are two possible approaches.

## Approach 1 — Store Every Map State

We could save a copy of the frequency map at every position.

Conceptually:

```text
state[0]
state[1]
state[2]
...
state[n]
```

This makes restoring state easy.

But it requires extra space proportional to the length of the string.

---

## Approach 2 — Reconstruct the Map

Instead of storing every state:

1. Recreate the frequency map from `s`.
2. Consume the characters used by the prefix before position `i`.
3. Now the map represents exactly the available characters at position `i`.

This uses much less memory.

Since the alphabet contains only a fixed number of characters, rebuilding the frequency information is cheap.

---

# 12. Space Optimization

A naive implementation might store:

```text
n copies of map<char,int>
```

which can use `O(n)` additional space.

Instead, we can keep only:

```text
one map
```

and reconstruct it when backtracking.

For lowercase English letters, there are only:

```text
26 possible characters
```

So the frequency structure is effectively constant-sized.

Therefore:

```text
Space ≈ O(26)
     = O(1)
```

with respect to the input length.

---

# 13. Important Lexicographical Property

Consider two strings:

```text
A = prefix + x + ...
B = prefix + y + ...
```

If:

```text
x > y
```

then:

```text
A > B
```

regardless of what comes after `x` and `y`.

For example:

```text
A = "abz..."
B = "acy..."
```

At the first different position:

```text
z > y
```

so:

```text
A > B
```

This property is exactly why, after making one position larger, we can freely minimize the suffix.

---

# 14. Why the Rightmost Increase Is Optimal

Suppose there are multiple positions that can be increased.

Consider:

```text
target = a b c
```

Option 1:

```text
a c ...
```

Option 2:

```text
b ...
```

The first difference from the target occurs earlier in Option 2.

Since earlier positions have greater influence on lexicographical order:

```text
a c... < b...
```

Therefore:

> Increase the latest possible position.

Then choose the **smallest possible character greater than the target character**.

This gives the smallest valid string greater than the target.

---

# 15. Complete Algorithm

The algorithm can be viewed as two phases.

## Phase 1 — Forward Greedy

Start from the first character.

For every position:

1. Find the smallest available character `>= target[i]`.
2. Consume it.
3. If it is greater than `target[i]`:

   * append all remaining characters in sorted order
   * return the answer.
4. Otherwise continue.

---

## Phase 2 — Backtracking

If the forward pass did not produce a strictly greater answer:

1. Start from the last matched position.
2. Reconstruct the available character frequencies for that position.
3. Find the smallest character `> target[i]`.
4. If none exists, move one position left.
5. Once one is found:

   * keep the prefix equal to the target
   * place the larger character
   * append the remaining characters in ascending order
   * return the answer.
6. If no position can be increased, return an empty string.

---

# 16. Data Structure Choice

| Requirement                   | Data Structure   |
| ----------------------------- | ---------------- |
| Unique sorted characters      | `set`            |
| Frequency + sorted characters | `map<char,int>`  |
| Frequency only                | `unordered_map`  |
| Fixed lowercase alphabet      | `int freq[26]`   |
| Smallest character `>= x`     | `lower_bound(x)` |
| Smallest character `> x`      | `upper_bound(x)` |

For this problem:

```text
map<char,int>
```

is a clean STL choice.

Because the alphabet is only 26 characters, a frequency array can also be used for an even simpler and more efficient implementation.

---

# 17. Complexity

Let:

```text
n = length of the string
```

For a fixed lowercase alphabet:

```text
Time:  O(n × 26)
Space: O(26)
```

Since `26` is constant:

```text
Time:  O(n)
Space: O(1)
```

in the asymptotic sense when the alphabet is fixed.

If using `map`, its ordered operations technically take:

```text
O(log 26)
```

which is still effectively constant.

---

# 18. General Pattern to Remember

This problem is not just about permutations.

It teaches a reusable **lexicographical greedy + backtracking pattern**:

```text
Try to stay equal
        ↓
If possible, continue
        ↓
If you become greater
        ↓
Minimize the suffix
```

If equality eventually fails:

```text
Backtrack
    ↓
Find the rightmost position
that can be increased
    ↓
Increase it by the smallest possible amount
    ↓
Minimize the suffix
```

The mental model is:

> **Stay equal as long as possible → increase as late as possible → minimize everything after it.**

---

# 19. STL Concepts to Remember

### `map<char,int>`

Stores:

```text
character → frequency
```

while keeping characters sorted.

### `lower_bound(x)`

Finds:

```text
first element >= x
```

Use when equality is allowed.

### `upper_bound(x)`

Finds:

```text
first element > x
```

Use when you must make the result strictly greater.

### Erasing zero frequency

When a character's count reaches zero, remove it from the map.

### Frequency reconstruction

Instead of storing every intermediate state, reconstruct the required state when needed.

This is a useful general space-optimization technique.

---

# 20. Biggest Takeaway

The hardest part of this problem is **not** finding the next character.

The real insight is combining:

* Greedy construction
* Lexicographical ordering
* Frequency counting
* Ordered search
* `lower_bound`
* `upper_bound`
* Right-to-left backtracking
* Minimizing the suffix
* Space optimization

The core thought process is:

```text
Can I stay equal?
       ↓
      Yes
       ↓
Continue

If not:
       ↓
Backtrack
       ↓
Can I make an earlier position larger?
       ↓
Yes
       ↓
Choose the smallest larger character
       ↓
Put remaining characters in ascending order
```

This pattern is worth remembering because it appears in many problems involving:

* Next permutation
* Lexicographically smallest/largest strings
* Rearrangement problems
* Constructing the smallest valid sequence
* Greedy + backtracking
* Frequency-based string construction
