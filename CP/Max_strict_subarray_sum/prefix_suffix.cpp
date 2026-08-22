#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Check prefix sums (excluding the entire array)
    long long prefix = 0;
    for (int i = 0; i < n - 1; ++i) {
        prefix += a[i];
        if (prefix <= 0) {
            cout << "NO\n";
            return;
        }
    }

    // Check suffix sums (excluding the entire array)
    long long suffix = 0;
    for (int i = n - 1; i > 0; --i) {
        suffix += a[i];
        if (suffix <= 0) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
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
