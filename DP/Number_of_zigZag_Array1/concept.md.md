# LeetCode 3699 --- Number of ZigZag Arrays I

## 1. Core Idea

The problem asks us to count how many arrays can be formed such that:

-   Every element lies within the given range `[l, r]`.
-   Adjacent elements must be different.
-   We cannot have three consecutive elements strictly increasing.
-   We cannot have three consecutive elements strictly decreasing.

The important observation is that the validity of the **next element**
depends only on the most recent movement.

------------------------------------------------------------------------

## 2. Understanding the ZigZag Condition

Suppose the last two elements are:

-   `prev < current`

Then the previous movement was **UP**.

The next element cannot be greater than `current`, because that would
create:

`prev < current < next`

which is three consecutive strictly increasing elements.

Therefore, after an UP movement, the next movement must be **DOWN**.

Similarly:

-   `prev > current`

means the previous movement was **DOWN**.

The next movement must therefore be **UP**.

So the sequence effectively has to alternate its direction:

**UP → DOWN → UP → DOWN ...**

or

**DOWN → UP → DOWN → UP ...**

------------------------------------------------------------------------

## 3. Finding the DP State

A natural first thought is to store:

`index + previous value + current value`

because these values seem to determine what can happen next.

However, `previous value` itself is not actually required.

What matters about the previous value is only whether:

-   `previous < current` → last movement was UP
-   `previous > current` → last movement was DOWN

Therefore, we can compress the state to:

### `(index, current value, direction)`

Where:

-   `index` tells us how many positions have been processed.
-   `current value` tells us the value at the current position.
-   `direction` tells us whether the last movement was UP or DOWN.

This is the **minimum sufficient state**.

------------------------------------------------------------------------

## 4. Meaning of the DP State

Think of two DP categories:

### UP state

Represents the number of valid ways to reach the current value where the
last movement was:

`previous < current`

Because the last movement was UP, the next movement must be DOWN.

### DOWN state

Represents the number of valid ways to reach the current value where the
last movement was:

`previous > current`

Because the last movement was DOWN, the next movement must be UP.

------------------------------------------------------------------------

## 5. Transition Logic

Suppose we are currently at value `x`.

### If the last movement was UP

The next value must be **smaller than `x`**.

So all values:

`l ... x-1`

can become the next value.

The new state becomes DOWN.

### If the last movement was DOWN

The next value must be **greater than `x`**.

So all values:

`x+1 ... r`

can become the next value.

The new state becomes UP.

Notice that `x` itself is automatically excluded, satisfying the
requirement that adjacent elements must be different.

------------------------------------------------------------------------

## 6. Why We Don't Need the Previous Value

This is the main DP insight.

Suppose we have:

`3 → 7`

and another sequence:

`5 → 7`

The previous values are different, but in both cases:

`previous < current`

Therefore, from the perspective of choosing the next element, both
states behave identically.

In both cases, the next value must be less than `7`.

So storing the exact previous value would contain redundant information.

This is a common DP optimization:

> Store the information that affects future decisions, not every piece
> of historical information.

------------------------------------------------------------------------

## 7. Initialization

For the first element, there is no previous element, so there is no
direction yet.

Conceptually:

-   Every value from `l` to `r` can be chosen as the first element.
-   Once a second element is chosen, the direction becomes known.

For the second element:

-   Choosing a value greater than the first creates an UP state.
-   Choosing a value smaller than the first creates a DOWN state.

After that, every subsequent movement must alternate.

------------------------------------------------------------------------

## 8. The Performance Problem

A straightforward DP transition would consider every possible next
value.

For every current value `x`, we might examine:

-   all smaller values when we need DOWN
-   all larger values when we need UP

This can lead to roughly:

`O(n × range²)`

where:

`range = r - l + 1`

That is unnecessarily expensive.

------------------------------------------------------------------------

## 9. Prefix/Suffix Sum Optimization

The transition asks for a sum over a **range of values**.

For example:

> To create a DOWN state at `x`, add the counts from every value smaller
> than `x`.

Instead of repeatedly summing:

`dp[l] + dp[l+1] + ... + dp[x-1]`

we maintain cumulative sums.

### Prefix sum

Useful when we need:

`all values smaller than x`

### Suffix sum

Useful when we need:

`all values greater than x`

This changes the transition from:

**"sum many states every time"**

to:

**"look up the required cumulative sum in O(1)"**

after maintaining the cumulative information.

------------------------------------------------------------------------

## 10. Complexity

Let:

`m = r - l + 1`

be the number of possible values.

With the prefix/suffix-sum optimization:

### Time

`O(n × m)`

because each position processes every possible value once.

### Space

`O(m)`

if we only keep the DP information for the current and previous
positions.

There is no need to keep the entire `n × m` table.

------------------------------------------------------------------------

## 11. The Important Pattern to Remember

This problem is a great example of **state compression + cumulative-sum
optimization**.

The thought process is:

``` text
What determines the next move?
        ↓
Previous + Current
        ↓
Do we need the exact Previous?
        ↓
No — only its relation with Current matters
        ↓
Compress Previous into Direction
        ↓
State = (index, current value, direction)
        ↓
Transitions require sums over smaller/larger values
        ↓
Use prefix/suffix sums
        ↓
O(n × range)
```

------------------------------------------------------------------------

## 12. DP Recognition Trick

When solving similar problems, ask these questions:

### Question 1

**What information is needed to determine the next valid move?**

Do not automatically store the entire history.

### Question 2

**Can two different histories produce exactly the same future
possibilities?**

If yes, those histories can probably be represented by the same DP
state.

### Question 3

**Does the transition ask for the sum/min/max over a range of states?**

If yes, think about:

-   Prefix sums
-   Suffix sums
-   Sliding windows
-   Fenwick trees
-   Segment trees

depending on the operation and constraints.

------------------------------------------------------------------------

## 13. Key Takeaway

The biggest insight in this problem is **not the implementation**.

It is recognizing that:

> The exact previous value does not matter. Its relationship with the
> current value is what matters.

That turns a seemingly larger state:

`(index, previous, current)`

into the much cleaner:

`(index, current, direction)`

Then prefix/suffix sums make the transitions efficient.

This combination --- **identify the minimum state + optimize range
transitions** --- is a very useful DP pattern to recognize in future
problems.
