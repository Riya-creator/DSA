// 1931E codeforces
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    int total_len = 0;
    vector<int> trailing_zeros;
    trailing_zeros.reserve(n);

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        // Count trailing zeros
        int zeros = 0;
        int temp = x;
        while (temp % 10 == 0) {
            zeros++;
            temp /= 10;
        }
        trailing_zeros.push_back(zeros);

        // Count total digits
        int digits = 0;
        temp = x;
        while (temp > 0) {
            digits++;
            temp /= 10;
        }
        total_len += digits;
    }

    // Anna greedily removes the maximum trailing zeros available
    sort(trailing_zeros.rbegin(), trailing_zeros.rend());

    for (int i = 0; i < n; i += 2) {
        total_len -= trailing_zeros[i];
    }

    // If remaining length >= m + 1, value is >= 10^m
    if (total_len >= m + 1) {
        cout << "Sasha\n";
    } else {
        cout << "Anna\n";
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
