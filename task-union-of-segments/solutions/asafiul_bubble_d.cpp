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

    vector<int> d(n - 1);
    for (size_t i = 0; i + 1 < n; ++i) {
        d[i] = segments[i + 1].first - segments[i].second;
    }

    {
        n--;
        for (int j = 1; j < n; j++) {
            int isSorted = 1;
            for (int i = 0; i < n - j; i++) {
                if (d[i] > d[i + 1]) {
                    swap(d[i], d[i + 1]);
                    isSorted = 0;
                }
            }
            if (isSorted) {
                break;
            }
        }
    }

    int ans = n + 1;
    for (auto x: d) {
        if (x <= k) {
            k -= x;
            --ans;
        }
    }

    cout << ans << "\n";
}


signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}