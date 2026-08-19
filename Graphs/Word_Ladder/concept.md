# LeetCode 127 — Word Ladder

## 1. Problem Intuition

The problem asks for the **shortest transformation sequence** from `beginWord` to `endWord`.

A transformation is valid when:

* Only **one character** is changed at a time.
* The resulting word must exist in `wordList`.
* Every transformation must therefore move from one valid word to another valid word.

The important observation is:

> This is not primarily a string problem. It can be modeled as a **graph shortest-path problem**.

---

## 2. Convert the Problem into a Graph

Think of every word as a **node**.

Two words have an edge between them if they differ at **exactly one character**.

For example:

```text
hot ─── dot
│       │
lot     dog
│       │
log ─── cog
```

Conceptually:

* **Node** → a word
* **Edge** → one-character transformation
* **Edge cost** → 1
* **Goal** → shortest path from `beginWord` to `endWord`

This immediately suggests BFS.

---

# 3. Why BFS?

This is one of the most important DSA patterns.

The graph is **unweighted** because every transformation costs exactly `1`.

For an unweighted graph:

> **BFS gives the shortest path in terms of number of edges.**

BFS explores the graph level by level:

```text
Level 0
beginWord

Level 1
words 1 transformation away

Level 2
words 2 transformations away

Level 3
words 3 transformations away
```

Therefore, when BFS encounters `endWord` for the first time, the shortest distance has been found.

### Important distinction

Do **not** memorize:

> "DFS cannot find shortest paths."

That's false.

DFS can find a shortest path if it explores appropriate paths and keeps the minimum.

The difference is:

* **DFS** → explores paths; shortest answer requires additional work.
* **BFS** → naturally explores by increasing distance.

So BFS is the natural and efficient choice here.

---

# 4. Why Not Build the Entire Graph?

The obvious approach is:

1. Take every pair of words.
2. Compare their characters.
3. Add an edge if they differ by exactly one character.
4. Run BFS.

But this can become expensive.

If there are `N` words of length `L`:

* Number of word pairs ≈ `N²`
* Comparing two words costs `O(L)`

So explicit graph construction can approach:

**O(N² × L)**

This is unnecessary.

---

# 5. Implicit Graph

Instead of constructing every edge beforehand, generate neighbors **only when BFS needs them**.

For the word:

```text
hot
```

try changing each position:

```text
?ot
h?t
ho?
```

For every position, try the possible alphabet characters.

There are:

* `L` positions
* `26` possible characters

So one word generates approximately:

**26 × L candidates**

Since `26` is constant:

**O(L)** candidates per word.

This is called an **implicit graph**.

The graph exists conceptually, but its edges are generated dynamically.

### Reusable pattern

Whenever you see:

> "States are connected if I can perform one small operation"

ask:

> **Can I generate neighboring states directly instead of constructing the entire graph?**

This technique appears in many state-space search problems.

---

# 6. Hash Set for Fast Lookup

When generating a candidate word, you need to answer:

> "Does this word exist in the allowed dictionary?"

A hash set is ideal.

Average lookup:

**O(1)**

So instead of comparing the generated word against every dictionary word, simply perform a hash lookup.

This is the key optimization that changes the approach from roughly:

**O(N²L)**

to:

**O(NL)**

for the standard BFS approach.

---

# 7. Visited Handling

A word should not be processed repeatedly.

Otherwise, cycles can occur:

```text
hot → dot → hot → dot → ...
```

So once a word has been discovered, mark it as visited.

A useful optimization is to remove a discovered word from the dictionary itself.

Then the dictionary effectively represents:

> **words that have not yet been visited**

This eliminates the need for a separate visited set.

### General trick

Sometimes you can combine:

```text
available/unvisited
```

and

```text
visited
```

into one structure by deleting elements once they are processed.

---

# 8. BFS Level Tracking

The answer is the **number of words in the transformation sequence**, not simply the number of edges.

For example:

```text
hit → hot → dot → dog → cog
```

There are:

* 4 transformations/edges
* 5 words

So be very careful about what your BFS counter represents.

A clean mental definition is:

> **Current BFS level = number of words from the starting word to the current frontier.**

This avoids the classic off-by-one error.

---

# 9. Important Edge Cases

### `endWord` is absent

If `endWord` isn't present in `wordList`, no valid transformation sequence exists.

Return the problem's failure value immediately.

---

### `beginWord == endWord`

This is worth checking according to the exact problem definition before starting traversal.

Always clarify what the required sequence length represents.

---

### Same character replacement

When generating mutations, don't consider replacing a character with itself.

For example:

```text
hot → hot
```

is not a valid transformation because **zero** characters changed.

A valid neighboring word must differ at exactly one position.

---

### Different word lengths

Words of different lengths cannot be connected through a single-character replacement.

In this problem the input structure already gives equal-length words, but recognizing this constraint is useful when generalizing the technique.

---

# 10. Bidirectional BFS

The standard BFS searches from:

```text
beginWord
      ↓
      ↓
      ↓
endWord
```

But we can search from **both sides**:

```text
beginWord → → → X ← ← ← endWord
```

Maintain two frontiers:

```text
begin frontier
end frontier
```

Expand both toward each other.

When a newly generated word appears in the opposite frontier:

> The two searches have met.

The shortest transformation has been found.

---

# 11. Why Bidirectional BFS Is Faster

Suppose the shortest path has depth `D`.

Normal BFS explores outward for approximately `D` levels.

Bidirectional BFS divides the search:

```text
begin → → D/2
              ← ← end
```

The theoretical worst-case complexity remains in the same asymptotic family, but the number of states explored can be dramatically smaller because graph branching grows rapidly with depth.

This is why bidirectional BFS is especially useful when:

* The graph is large.
* You know both the source and destination.
* Edges can be generated efficiently.
* You only need to know whether/when the two sides connect.

---

# 12. Expanding the Smaller Frontier

A particularly useful optimization is:

> Always expand the smaller frontier.

Suppose:

```text
begin frontier = 500 words
end frontier   = 10 words
```

Expanding 10 words is much cheaper.

So the two sides can effectively switch roles whenever necessary.

This is a very useful bidirectional-search optimization.

---

# 13. Standard BFS vs Bidirectional BFS

| Feature                | BFS                | Bidirectional BFS      |
| ---------------------- | ------------------ | ---------------------- |
| Search direction       | One side           | Both sides             |
| Implementation         | Simpler            | More complex           |
| Shortest path          | Yes                | Yes                    |
| Neighbor generation    | Dynamic            | Dynamic                |
| Worst-case complexity  | O(NL)              | Same asymptotic family |
| Practical search space | Larger             | Usually much smaller   |
| Best when              | Simplicity matters | Search space is huge   |

---

# 14. Complexity

Let:

* `N` = number of words
* `L` = length of each word

For each visited word:

```text
L positions × 26 characters
```

So:

**Time:**

```text
O(N × L × 26)
```

Since `26` is constant:

**O(NL)**

### Space

The dictionary and BFS/frontier structures can contain up to `N` words.

Therefore:

**Space: O(N)**

There is also temporary storage proportional to the word length, giving:

**O(N + L)**

which is generally simplified to:

**O(N)**

when `L` is bounded.

---

# 15. Why Trie Is Not the Natural Choice

Your initial Trie idea was reasonable because this is a **word problem**.

But ask what operation the problem actually needs.

Trie is great for:

* Prefix searching
* Prefix grouping
* Dictionary word lookup by prefixes
* Autocomplete
* Pattern-like prefix queries

Word Ladder needs:

> Find words at **Hamming distance 1**.

The important relationship is not the prefix.

Therefore, a hash set + generated mutations is much more direct.

### General lesson

Don't choose a data structure just because the input happens to be strings.

Choose it based on the **operation you need to perform**.

---

# 16. Why Word Search Is Different

Your initial Word Search intuition was also understandable.

Word Search has:

```text
current cell
    ↓
adjacent cells
    ↓
visited cells
```

Word Ladder has:

```text
current word
    ↓
one-character mutations
    ↓
unvisited words
```

Both are **state-space searches**, but their state transitions are different.

This is the useful abstraction:

> Don't focus on whether the input looks like a string/grid/array. Focus on **what constitutes a state and how you can move to another state**.

---

# 17. Important DSA Pattern

This problem combines several extremely reusable ideas:

### Pattern 1 — Implicit Graph

Don't construct edges if neighbors can be generated cheaply.

### Pattern 2 — BFS Shortest Path

For an unweighted graph:

```text
Shortest number of edges → BFS
```

### Pattern 3 — Hash Set Membership

When repeatedly asking:

```text
Does X exist?
```

use a hash-based structure when appropriate.

### Pattern 4 — State Deduplication

Never repeatedly process the same state.

### Pattern 5 — Bidirectional Search

When both source and destination are known:

```text
Search from both ends
```

can massively reduce practical work.

---

# 18. Mental Template for Similar Problems

When you see a problem like this, ask:

```text
1. What is a state?
        ↓
2. What makes two states neighbors?
        ↓
3. Is every transition equally costly?
        ↓
4. Do I need the shortest number of transitions?
        ↓
5. Can I generate neighbors without building the whole graph?
        ↓
6. Can I check valid states quickly with hashing?
        ↓
7. Can I avoid revisiting states?
        ↓
8. Do I know both the start and destination?
        ↓
9. Would bidirectional BFS reduce the search?
```

For Word Ladder:

```text
State
  ↓
word

Neighbor
  ↓
word differing by exactly one character

Edge cost
  ↓
1

Graph
  ↓
unweighted

Traversal
  ↓
BFS

Optimization
  ↓
implicit graph + hash set

Further optimization
  ↓
bidirectional BFS
```

---

# 19. Biggest Takeaways

The most important thing you should take away isn't the specific implementation.

It's this chain of thought:

```text
Words
  ↓
States

One-character change
  ↓
Edges

All edges cost 1
  ↓
Unweighted graph

Need minimum transformations
  ↓
BFS

Don't construct every edge
  ↓
Generate neighbors dynamically

Need fast dictionary lookup
  ↓
Hash set

Need fewer states
  ↓
Bidirectional BFS
```

**That thought process is far more valuable than memorizing the Word Ladder solution.**
