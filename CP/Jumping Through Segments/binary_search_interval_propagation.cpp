#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<long long, long long>> a(n);
    for (auto &p : a) cin >> p.first >> p.second;

    auto check = [&](long long k) {
        long long l = 0, r = 0;
        for (const auto &[seg_l, seg_r] : a) {
            l = max(seg_l, max(0LL, l - k));
            r = min(seg_r, r + k);
            if (l > r) return false;
        }
        return true;
    };

    long long low = 0, high = 1e9, ans = high;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
