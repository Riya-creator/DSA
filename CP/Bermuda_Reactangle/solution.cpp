#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

void solve() {
    ll S;
    int q;
    cin >> S >> q;

    vector<ll> d;
    for (ll i = 1; i * i <= S; i++) {
        if (S % i == 0) {
            d.push_back(i);
            if (i * i != S) {
                d.push_back(S / i);
            }
        }
    }
    sort(d.begin(), d.end());

    int k = d.size();
    // 1-indexed for convenience
    // d[i] for i = 1..k
    // h[i] = S / d[i]
    vector<ll> d_arr(k + 1, 0);
    vector<ll> h_arr(k + 1, 0);
    vector<ll> pref(k + 1, 0);

    for (int i = 1; i <= k; i++) {
        d_arr[i] = d[i - 1];
        h_arr[i] = S / d_arr[i];
        ll step_width = d_arr[i] - d_arr[i - 1];
        pref[i] = pref[i - 1] + step_width * h_arr[i];
    }

    //O(log k)
    while (q--) {
        ll x, y;
        cin >> x >> y;

        // blue shape does not extend past x = S
        x = min(x, S);

        // largest j such that d[j] <= S / y
        ll max_d = S / y;
        //basically uss y ke liye kitne x tak h blue portion
        int j = upper_bound(d_arr.begin() + 1, d_arr.end(), max_d) - d_arr.begin() - 1;

        if (x <= d_arr[j]) {
            cout << x * y << "\n";
            continue;
        }

        ll ans = d_arr[j] * y;

        // Find step m where x falls: x in (d_arr[m-1], d_arr[m]]
        int m = lower_bound(d_arr.begin() + 1, d_arr.end(), x) - d_arr.begin();

        //full steps between j and m-1
        if (m - 1 > j) {
            ans += pref[m - 1] - pref[j];
        }

        //last partial step m
        ans += (x - d_arr[m - 1]) * h_arr[m];

        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
