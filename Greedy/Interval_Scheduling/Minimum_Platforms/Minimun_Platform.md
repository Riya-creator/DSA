# **Minimum Platforms Required for Trains**

Problem Type: Greedy, Interval Scheduling, Sweep Line
Difficulty: Medium

📌 Problem Statement
-Given two arrays:
-arr[i] → arrival times of trains
-dep[i] → departure times of trains
-Find the minimum number of platforms required so that no train waits.

##**🧠 Approach 1 — Two Pointer / Sweep Line**
-Sort arrival and departure times separately.
-Traverse both timelines together.
-If a train arrives before the earliest departure, a new platform is needed
-Otherwise, a platform is freed.
-The maximum number of platforms used at any time is the answer.

**⏱ Complexity**
-Time: O(n log n)
-Space: O(1) auxiliary..

📄 Code
👉[Two Pointer Solution](Two_Pointer_(Sweep_Line).cpp)




## **🧠 Approach 2 — Priority Queue (Min Heap)**
-Pair (arrival, departure) times.
-Sort by arrival.
-Use a min-heap storing departure times of currently active trains.
-Before inserting a new train, remove all trains that have already departed.
-Heap size at any moment = number of platforms in use.

**⏱ Complexity**
-Time: O(n log n)
-Space: O(n).

📄 Code
👉[Min_Heap_Solution](Priority_Queue(Min_Heap).cpp)

# **🤔 When to Pick Which?**
-🔥 Two-Pointer Approach when:
You only need the maximum overlap count.
You want a memory-optimized solution.
-🔥 Heap Approach when:
You actually need to assign specific platforms to trains.
You want to extend the problem to:
“Which train goes to which platform?”
simulation-style scheduling.
You want a generalized pattern for problems like meeting rooms or runways.

# **📝 Notes to Self**
-Sweep line is the cleanest for counting overlaps.
-Heap version is more flexible for extensions.
-Always track peak concurrent intervals.
-Equality conditions (<= vs <) matter.
