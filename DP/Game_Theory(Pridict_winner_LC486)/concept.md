# LeetCode 486 - Predict the Winner

# Core Idea

This problem is one of the best introductions to **Game Theory + Minimax Dynamic Programming**.

Unlike normal DP problems where only one person is making decisions, here **two players** are playing **optimally**. Every move made by one player directly affects the choices available to the other player.

The biggest challenge is not writing the recursion—it is deciding **what the recursion should return.**

---

# Step 1 : Thinking Like a Brute Force

Initially, most people think like this:

* Keep track of Player 1's score.
* Keep track of Player 2's score.
* On every turn, choose either the left or right number.
* At the end compare both scores.

The recursive state naturally becomes

* Left Index
* Right Index
* Player 1 Score
* Player 2 Score
* Whose Turn

Conceptually,

```
solve(left, right, player1Score, player2Score, turn)
```

At every step,

* Current player chooses the left element.
* Current player chooses the right element.
* Continue recursively until no elements remain.

Finally,

```
Player1Score >= Player2Score
```

determines the answer.

---

# Why This Approach Is Not Practical

Although this matches our natural thinking, it creates a huge number of states.

The recursion depends on

* current left index
* current right index
* player1 score
* player2 score
* turn

If memoization is added, all of these become dimensions of the DP.

Even for small constraints, this becomes extremely expensive in both memory and time.

This is why we start searching for a better state representation.

---

# A Better Observation

Instead of storing both players' scores during recursion, ask a different question.

> "What is the maximum score Player 1 can still collect from the remaining array?"

Notice what changed.

Instead of carrying Player 1's score through recursion, the recursive function itself computes it.

The state now only needs

* left index
* right index
* whose turn

The current accumulated score no longer needs to be stored.

---

# New Meaning of the Recursive Function

The recursive function is now defined as

> **Maximum score Player 1 can obtain from the remaining subarray assuming both players play optimally.**

This single sentence defines the entire recursion.

Whenever writing recursive DP, always begin by answering:

> **"What exactly does my function return?"**

Everything else follows naturally from that definition.

---

# Understanding Player 1's Turn

When Player 1 gets a turn, they have two possible moves.

* Take the left element.
* Take the right element.

Since Player 1 wants the maximum possible score, they choose whichever option eventually gives them more points.

Therefore,

Player 1 performs a **maximum** operation.

---

# Understanding Player 2's Turn

This is where many beginners become confused.

Player 2 is **not trying to maximize Player 1's score.**

Player 2 wants Player 1 to end up with the smallest possible score.

Notice something important.

Whenever Player 2 picks a number,

Player 1 does **not** receive those points.

Player 2 simply removes one number from the array and leaves the remaining game for Player 1.

Therefore,

Player 2 performs a **minimum** operation.

This is exactly the Minimax principle.

* Maximizing player → chooses the maximum outcome.
* Minimizing player → chooses the minimum outcome.

---

# Recursive Implementation (Maximum Player 1 Score)

```cpp
class Solution {
    int solve(vector<int>& nums, int left, int right, bool player1Turn) {

        if (left > right)
            return 0;

        if (player1Turn) {

            int takeLeft =
                nums[left] + solve(nums, left + 1, right, false);

            int takeRight =
                nums[right] + solve(nums, left, right - 1, false);

            return max(takeLeft, takeRight);
        }
        else {

            int removeLeft =
                solve(nums, left + 1, right, true);

            int removeRight =
                solve(nums, left, right - 1, true);

            return min(removeLeft, removeRight);
        }
    }

public:

    bool PredictTheWinner(vector<int>& nums) {

        int total = 0;

        for (int x : nums)
            total += x;

        int player1 = solve(nums, 0, nums.size() - 1, true);

        int player2 = total - player1;

        return player1 >= player2;
    }
};
```

---

# Why Does This Work?

Think about what happens during Player 2's turn.

Suppose the remaining array is

```
[5, 8]
```

Player 2 chooses one element.

Whichever element Player 2 removes is **gone forever.**

Player 1 can only collect points from whatever remains.

So Player 2's decision directly affects how many points Player 1 can eventually earn.

Since Player 2 plays optimally,

they always choose the move that leaves Player 1 with the **smallest future score**.

That is why Player 2 uses **minimum**.

---

# Final Scores

After recursion finishes,

Player 1's score is already known.

Player 2's score can be computed easily because

```
Total Sum = Player1 + Player2
```

Therefore,

```
Player2 = Total Sum − Player1
```

Finally compare

```
Player1 >= Player2
```

---

# Time Complexity of This Recursive Version

Without memoization

```
O(2^n)
```

because every position branches into two choices.

With memoization

```
O(n² × 2)
```

since the state only depends on

* left
* right
* turn

which is approximately

```
O(n²)
```

---

# The Final Optimization (Concept Only)

Even this solution can be improved.

Notice that we are still carrying whose turn it is.

Instead of calculating

> "How many points can Player 1 collect?"

we can calculate

> "By how many points can the current player beat the other player?"

This single observation removes the need to track

* Player 1
* Player 2
* Turn

The recursion becomes dependent only on

* left index
* right index

The return value changes from

```
Maximum Score
```

to

```
Maximum Score Difference
```

This elegant transformation reduces the DP to only two dimensions while naturally handling alternating turns.

This is the standard optimal solution used for this problem.

---

# Pattern Recognition

Whenever a problem contains

* Two players
* Alternate turns
* Both players play optimally
* Each player chooses from a limited number of moves

immediately think about **Minimax**.

The first question should always be

> **What should my recursive function return?**

Possible choices include

* Can the first player win?
* Maximum score of the first player.
* Maximum score difference.
* Minimum loss.
* Maximum profit.

Choosing the correct return value often determines whether the DP becomes simple or impossible.

---

# Key Takeaways

* Never begin coding before defining the meaning of your recursive function.
* A good DP state stores only the information necessary to make future decisions.
* Returning accumulated scores usually creates unnecessarily large states.
* Minimax problems almost always involve one player maximizing while the other minimizes.
* Sometimes changing **what the recursion returns** is enough to reduce a five-dimensional DP into a two-dimensional DP.
* The famous score-difference solution is not a different algorithm—it is simply a smarter way of representing the same game.
