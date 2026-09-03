class Solution {
public:
    int countZigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        long long MOD = 1e9 + 7;

        if (n == 1) return m % MOD;

        // dp_up[v]: number of valid prefixes of length i ending with value v, where the last step was UP
        // dp_down[v]: number of valid prefixes of length i ending with value v, where the last step was DOWN
        vector<long long> dp_up(m, 0), dp_down(m, 0);

        // For n = 2:
        // From any pair (u, v):
        // If u < v: that transition is UP.
        // If u > v: that transition is DOWN.
        for (int v = 0; v < m; v++) {
            dp_up[v] = v;          // number of u < v
            dp_down[v] = m - 1 - v; // number of u > v
        }

        // Transitions for length 3 to n
        for (int i = 3; i <= n; i++) {
            vector<long long> next_up(m, 0), next_down(m, 0);

            // next_up[v] needs sum of dp_down[u] for all u < v (Prefix sum)
            long long running_prefix = 0;
            for (int v = 0; v < m; v++) {
                next_up[v] = running_prefix;
                running_prefix = (running_prefix + dp_down[v]) % MOD;
            }

            // next_down[v] needs sum of dp_up[u] for all u > v (Suffix sum)
            long long running_suffix = 0;
            for (int v = m - 1; v >= 0; v--) {
                next_down[v] = running_suffix;
                running_suffix = (running_suffix + dp_up[v]) % MOD;
            }

            dp_up   = move(next_up);
            dp_down = move(next_down);
        }

        long long total = 0;
        for (int v = 0; v < m; v++) {
            total = (total + dp_up[v] + dp_down[v]) % MOD;
        }

        return total;
    }
};
