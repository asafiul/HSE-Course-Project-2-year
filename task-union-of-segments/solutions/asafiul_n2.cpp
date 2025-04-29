#include "bits/stdc++.h"

using namespace std;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> segments(n);
    for (auto &[l, r]: segments) {
        cin >> l >> r;
    }

    sort(segments.begin(), segments.end());

    vector<int> dp(n, -1);
    dp[0] = k;
    for (int i = 0; i + 1 < n; ++i) {
        int d = segments[i + 1].first - segments[i].second;
        for (int j = n - 1; j >= 1; --j) {
            if (dp[j - 1] >= d) {
                dp[j] = max(dp[j], dp[j - 1] - d);
            }
        }
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[i] >= 0) {
            res = i;
        }
    }
    cout << n - res << '\n';
}


signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
