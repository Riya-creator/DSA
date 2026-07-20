# LeetCode 128 - Longest Consecutive Sequence

> **Difficulty:** Medium  
> **Topics:** Array, Hash Table, Union Find  
> **Time Complexity:** O(n) (Average)  
> **Space Complexity:** O(n)

---

# Problem Statement

Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in **O(n)** time.

### Example

```cpp
Input: nums = [100,4,200,1,3,2]

Output: 4

Explanation:
The longest consecutive sequence is:
1 → 2 → 3 → 4

Length = 4
```

---

# First Thought (Sorting)

The very first idea that comes to mind is:

1. Sort the array.
2. Traverse once.
3. Count consecutive elements.
4. Keep updating the maximum length.

### Code

```cpp
sort(nums.begin(), nums.end());

curr = 1;

for(int i = 1; i < nums.size(); i++){

    if(nums[i] == nums[i-1])
        continue;

    if(nums[i] == nums[i-1] + 1)
        curr++;
    else
        curr = 1;

    ans = max(ans,curr);
}
```

---

## Complexity

Sorting takes

```
O(n log n)
```

Traversing takes

```
O(n)
```

Overall

```
O(n log n)
```

Although this solution is accepted, **it does not satisfy the follow-up requirement of O(n).**

---

# How can we avoid sorting?

Think about what sorting actually gives us.

Sorting only helps us answer one question:

> **"Does the next consecutive number exist?"**

For example,

```
1 2 3 4
```

Since the numbers are ordered, checking the next element becomes easy.

But...

Do we really need to sort just to know whether another number exists?

**No!**

A Hash Table can answer that in constant time.

---

# Why use an unordered_set?

`unordered_set` stores only **unique elements** and provides extremely fast lookup.

```cpp
unordered_set<int> st(nums.begin(), nums.end());
```

Now checking whether a number exists is simply

```cpp
st.find(x)
```

Average complexity:

```
O(1)
```

instead of scanning the entire array.

---

# Important Clarification

Many beginners think

> "find() takes linear time."

That is **true for vectors**, but **not for unordered_set**.

| Data Structure | find() Complexity |
|---------------|------------------|
| vector | O(n) |
| set | O(log n) |
| unordered_set | O(1) Average |

This is the main reason we use `unordered_set`.

It uses **hashing**, so elements can be found directly instead of checking one by one.

---

# The Main Observation

Suppose

```
nums = [100,4,200,1,3,2]
```

After inserting into the set

```
{100,4,200,1,3,2}
```

Now imagine starting from **every** number.

From 1

```
1 → 2 → 3 → 4
```

Length = 4

From 2

```
2 → 3 → 4
```

Length = 3

From 3

```
3 → 4
```

Length = 2

From 4

```
4
```

Length = 1

Notice something?

We are visiting the **same sequence multiple times.**

This is unnecessary work.

---

# The Trick

A sequence should only be started from its **first element**.

How do we know whether a number is the first element?

Simply check whether its previous number exists.

```
num - 1
```

If it exists

```
Skip it.
```

If it doesn't exist

```
Start counting.
```

---

## Example

```
{100,4,200,1,3,2}
```

Checking every number

```
100

99 doesn't exist

Start
```

---

```
4

3 exists

Skip
```

---

```
200

199 doesn't exist

Start
```

---

```
1

0 doesn't exist

Start

1
2
3
4
```

Length = 4

---

Every sequence is processed **exactly once.**

---

# Algorithm

```
Insert every element into unordered_set

For every number

    If previous number doesn't exist

        Start counting

        while(next number exists)

            increase length

Update answer

Return answer
```

---

# Code

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        unordered_set<int> st(nums.begin(), nums.end());

        int ans = 0;

        for(int num : st){

            if(st.find(num - 1) == st.end()){

                int curr = num;
                int len = 1;

                while(st.find(curr + 1) != st.end()){
                    curr++;
                    len++;
                }

                ans = max(ans, len);
            }
        }

        return ans;
    }
};
```

---

# Dry Run

Input

```
100 4 200 1 3 2
```

Hash Set

```
{100,4,200,1,3,2}
```

Loop

```
100

99 absent

Length = 1
```

---

```
4

3 present

Skip
```

---

```
200

199 absent

Length = 1
```

---

```
1

0 absent

Start

1
2
3
4

Length = 4
```

Maximum = 4

Answer

```
4
```

---

# Why don't we start from every number?

Because that repeats work.

Example

```
1 2 3 4
```

Without checking `num - 1`

```
1 → 2 → 3 → 4

2 → 3 → 4

3 → 4

4
```

The same sequence gets traversed **four times.**

Checking `num - 1` ensures only the first element starts the traversal.

---

# Why unordered_set instead of set?

| unordered_set | set |
|---------------|-----|
| Hash Table | Balanced BST |
| O(1) Average Lookup | O(log n) Lookup |
| No Ordering | Sorted |
| Faster for existence checking | Slower than hashing |

Since we never need the elements in sorted order, using `set` only makes the solution slower.

---

# Complexity Analysis

### Building the Hash Set

```
O(n)
```

### Every sequence is visited once

```
O(n)
```

Overall

```
O(n)
```

Space

```
O(n)
```

---

# Interesting Facts 💡

### 1. Why not sort?

Sorting destroys the O(n) requirement.

The problem is specifically designed to test your understanding of hashing.

---

### 2. Duplicates are automatically removed

Input

```
1 2 2 3 4
```

Hash Set becomes

```
1 2 3 4
```

No extra handling required.

---

### 3. Every element is expanded only once

Even though there is a nested `while` loop, the complexity **does not become O(n²).**

Why?

Because each element belongs to exactly one sequence and is visited only once during expansion.

Example

```
1 2 3 4 5
```

Expansion happens only from `1`.

```
1 → 2 → 3 → 4 → 5
```

When the loop later reaches `2`, `3`, `4`, or `5`, they are skipped.

Hence,

```
Total work = n
```

---

### 4. This is a common interview pattern

Whenever you see

- Find the longest chain
- Find connected consecutive values
- Check existence quickly

Think

> **Hash Table + Start only from the beginning of a chain**

This pattern appears in several array and graph interview questions.

---

# Key Takeaways

- Sorting is intuitive but costs **O(n log n)**.
- `unordered_set` provides **O(1)** average lookup.
- Start only from numbers having **no predecessor**.
- Each sequence is explored exactly once.
- This gives an overall **O(n)** solution.

---

## Interview One-Liner 🎯

> **A number can only be the beginning of a consecutive sequence if `num - 1` is absent. By expanding only from such numbers, every sequence is traversed exactly once, resulting in an O(n) solution using an `unordered_set`.**
