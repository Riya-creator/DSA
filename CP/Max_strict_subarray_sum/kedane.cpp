#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Standard Kadane's algorithm on a subrange [L, R]
long long kadane(const vector<long long>& a, int L, int R) {
    long long max_so_far = a[L];
    long long current_sum = a[L];

    for (int i = L + 1; i <= R; ++i) {
        current_sum = max(a[i], current_sum + a[i]);
        max_so_far = max(max_so_far, current_sum);
    }
    return max_so_far;
}

void solve() {
    int n;
    cin >> n;

    vector<long long> a(n);
    long long total_sum = 0;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        total_sum += a[i];
    }

    // Adel's best choice from proper subarrays
    long long adel_max = max(kadane(a, 0, n - 2), kadane(a, 1, n - 1));

    if (total_sum > adel_max) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
