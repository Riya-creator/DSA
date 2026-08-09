# Stone Game II — Concepts & Approach

## 1. Problem Pattern

Stone Game II is a **two-player optimal game** problem.

At every turn:

* The current player can take between `1` and `2 × M` piles.
* After taking `X` piles, the next value of `M` becomes `max(M, X)`.
* Both players play optimally.
* We need the maximum number of stones the first player can collect.

The main difficulty is not choosing the piles itself, but correctly representing **whose score the recursive function returns**.

---

## 2. DP State

The important state is:

* `ind` → index of the first pile that is still available.
* `M` → current maximum allowed multiplier.

So the state can be thought of as:

> `score(ind, M)` = maximum score that the player whose turn it currently is can eventually obtain from this state.

### Important idea

We do **not** need separate states/functions for Alice and Bob.

The same function always represents:

> "Best possible score for the player whose turn it is."

Therefore:

* At the initial call, the function represents Alice.
* Inside the recursion, it represents Bob.
* Inside Bob's recursion, it represents Alice again.

This automatically handles alternating turns.

---

## 3. Why We Cannot Simply Add the Recursive Score

Suppose the current player chooses some number of piles.

There are now two parts:

1. Stones taken immediately by the current player.
2. Stones that remain for the opponent.

The recursive call represents the **opponent's best possible score**, not our score.

Therefore, we cannot do:

> Current player's stones + recursive score

because the recursive score belongs to the opponent.

Instead, we use the total remaining stones.

---

## 4. The `Total - Opponent` Trick

Suppose after our move there are `R` stones remaining.

The opponent can optimally collect:

> `OpponentScore`

Since every remaining stone must eventually belong to either player:

> Our future score = `R - OpponentScore`

Therefore:

> Our total score = stones taken now + remaining stones - opponent's optimal score

This is the central game-DP idea used here.

### General takeaway

For two-player problems where:

* all resources eventually belong to one of the two players, and
* the recursive function returns the current player's optimal score,

a very useful transformation is:

> **Current player's score = Total available − Opponent's optimal score**

This often eliminates the need to explicitly track player turns.

---

## 5. Why Suffix Sum Is Useful

We need to repeatedly calculate:

> How many stones are present from index `ind` until the end?

Doing this by repeatedly summing the remaining piles would make the recursion more expensive.

So we precompute **suffix sums**.

For every index:

> `suffix[i]` = total stones from `i` to the end.

Then after taking `X` piles starting at `ind`, the next state begins at:

> `ind + X`

Therefore:

> `suffix[ind + X]`

represents all the stones that remain after our move.

This allows the remaining total to be obtained in **O(1)** time.

---

## 6. Important Suffix Array Boundary Detail

A particularly important implementation detail is making the suffix array of size:

> `n + 1`

instead of only `n`.

Why?

Normally:

> `suffix[i]` = sum of piles from `i` onward.

But there is one perfectly valid situation where the current player takes **all remaining piles**.

If:

> `ind + X = n`

then there are no piles left.

It is extremely convenient for:

> `suffix[n]`

to represent:

> `0 remaining stones`

Therefore the suffix array should conceptually contain:

```text
suffix[0] ... suffix[n-1] suffix[n]
                              ↑
                         represents 0
```

This makes the boundary case natural rather than requiring a special condition.

### Why this matters

Suppose only two piles remain and the player is allowed to take both.

The next index becomes `n`.

If the suffix array only has indices `0 ... n-1`, accessing `suffix[n]` would be invalid.

By adding one extra position:

> `suffix[n] = 0`

the "take everything remaining" case works cleanly.

### General DP / prefix-sum lesson

Whenever a prefix/suffix array represents sums over ranges, it is often useful to allocate **one extra element**.

For example:

* Prefix sum → `prefix[0] = 0`
* Suffix sum → `suffix[n] = 0`

This makes boundary ranges such as:

> "everything before index 0"

or

> "everything after index n-1"

naturally represent zero.

---

## 7. Choosing `X` Piles

For a state `(ind, M)`, the current player may choose:

> `X = 1 ... 2M`

piles.

But there is another constraint:

> We cannot take more piles than actually remain.

Therefore the effective range is limited by both:

* `2M`
* number of remaining piles

### Boundary condition to remember

If:

> `ind + X = n`

then taking all remaining piles is valid.

So the condition must allow equality with `n`.

A common off-by-one mistake is requiring:

> `ind + X < n`

which incorrectly excludes the possibility of taking the final remaining piles.

---

## 8. Updating `M`

After taking `X` piles:

> `newM = max(M, X)`

This is an important part of the state transition.

Notice that `M` does **not** decrease.

Even if the player takes fewer piles than the current `M`, the next player still receives the existing `M`.

So:

> `M' = max(M, X)`

---

## 9. DP Transition Concept

For every possible `X`:

1. Take `X` piles.
2. Calculate the stones taken immediately.
3. Move to index `ind + X`.
4. Update `M` to `max(M, X)`.
5. Calculate the opponent's optimal score from the new state.
6. Subtract that opponent score from the remaining total.
7. Add the stones taken immediately.
8. Choose the maximum among all possible `X`.

Conceptually:

> **Current score = immediate score + remaining stones − opponent's best score**

and then:

> **Take the maximum over all valid choices.**

---

## 10. Why Memoization Is Needed

Without memoization, the same `(ind, M)` state can be reached through many different sequences of moves.

That causes repeated recursive calculations and leads to a very large number of calls.

The DP table stores:

> `dp[ind][M]`

so that once the best score for a state is calculated, it can be reused immediately.

This converts the problem from an exponential recursive search into polynomial DP.

---

## 11. Number of States

There are approximately:

* `O(n)` possibilities for `ind`
* `O(n)` possibilities for `M`

Therefore:

> Number of DP states = `O(n²)`

Not every theoretical state necessarily gets visited, but `O(n²)` is the safe complexity bound.

---

## 12. Time Complexity

For every DP state, we may try up to `2M` choices.

In the worst case:

> `M = O(n)`

so one state can take:

> `O(n)`

work.

There are:

> `O(n²)`

states.

Therefore:

> **Time Complexity = O(n³)**

The suffix sum ensures that calculating the remaining stones does not introduce another `O(n)` factor.

---

## 13. Space Complexity

The DP table contains approximately:

> `n × 2n`

entries.

Therefore:

> **DP Space = O(n²)**

Additional space:

* Suffix sum → `O(n)`
* Recursion stack → `O(n)`

The dominant term is the DP table.

Therefore:

> **Overall Space Complexity = O(n²)**

---

## 14. Common Loopholes / Mistakes

### 1. Forgetting whose score recursion returns

`score()` represents the **current player**, not a particular person.

The recursive call therefore represents the opponent.

---

### 2. Adding the opponent's score

Do not directly add the recursive result to your score.

Instead:

> Remaining stones − opponent's optimal score

gives your future score.

---

### 3. Off-by-one while taking piles

If `X` piles are taken starting from `ind`, the selected piles are:

> `ind ... ind + X - 1`

The next state begins at:

> `ind + X`

This distinction is extremely important.

---

### 4. Forgetting that taking all remaining piles is valid

If:

> `ind + X = n`

the player has taken every remaining pile.

This is a valid move whenever `X ≤ 2M`.

Do not accidentally exclude it with a strict `< n` condition.

---

### 5. Suffix array too small

Using only `n` elements makes `suffix[n]` invalid.

Using `n + 1` elements lets:

> `suffix[n] = 0`

represent "nothing remains."

This is a clean way to handle the terminal boundary.

---

### 6. Using the wrong `M` transition

After taking `X` piles:

> `M' = max(M, X)`

not simply `X`.

---

## 15. General Problem-Solving Template

When you encounter a similar two-player game problem, ask:

### Step 1 — What does my DP state represent?

Try to define:

> `dp[state] = best score for the player whose turn it is`

This often avoids maintaining a separate `player` dimension.

### Step 2 — What happens after my move?

Identify the state of the opponent after your choice.

### Step 3 — Can I use `Total - Opponent`?

If all resources eventually belong to one of the two players:

> Current player's eventual score = total available − opponent's optimal score.

### Step 4 — Are range sums being repeatedly calculated?

If yes, consider:

* prefix sums
* suffix sums

to make them `O(1)`.

### Step 5 — Check boundaries carefully

Especially ask:

> "Can the current move consume the entire remaining array?"

If yes, make sure your range-sum structure supports the state immediately after the array.

### Step 6 — Find repeated states

If the same `(index, parameter)` can occur through multiple paths, memoization is usually the natural next step.

---

## 16. Key Concepts Used

* Two-player optimal game DP
* Minimax-style reasoning
* Current-player perspective
* `Total - Opponent` transformation
* Memoization
* State compression
* Suffix sums
* Range-sum optimization
* Recursive state transition
* Off-by-one boundary handling
* `max(M, X)` state transition
* O(n²) state space
* O(n³) time complexity

---

## 17. The Biggest Takeaway

The most important conceptual shift is:

> **Don't think "Alice's DP" and "Bob's DP."**

Think:

> **"Whichever player's turn it is, this function tells me the maximum score that player can obtain."**

Then the opponent's recursive result can be converted into your score using:

> **Total remaining − opponent's best score**

Once this perspective clicks, the recursion becomes much easier to construct.

The suffix sum and the extra `n + 1` position then make the range calculations and "take all remaining piles" case clean and safe.
