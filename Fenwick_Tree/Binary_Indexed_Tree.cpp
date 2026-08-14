#include <bits/stdc++.h>
using namespace std;

class FenwickTree {

    int n;
    vector<int> BIT;

public:

    FenwickTree(int n) {
        this->n = n;
        BIT.resize(n + 1, 0);
    }

    // Add delta to index i
    void update(int ind, int delta) {

        while(ind <= n) {

            BIT[ind] += delta;

            // Move to next Fenwick node containing index i
            ind += ind & -ind;
        }
    }

    // Sum from index 1 to i
    int prefixSum(int i) {

        int sum = 0;

        while(i > 0) {

            sum += BIT[i];

            // Move to previous Fenwick block
            i -= i & -i;
        }

        return sum;
    }

    // Sum from l to r
    int rangeSum(int l, int r) {

        return prefixSum(r) - prefixSum(l - 1);
    }
};
