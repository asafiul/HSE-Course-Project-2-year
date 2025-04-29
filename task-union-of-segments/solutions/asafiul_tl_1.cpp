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

    for (int i = 0; i + 1 < n; ++i) {
        d[i] = segments[i + 1].first - segments[i].second;
    }

    int ans = n;
    while (k > 0) {
        int found = -1;
        for (int i = 0; i + 1 < n; ++i) {
            if (d[i] != -1 && (found == -1 || d[i] < d[found])) {
                found = i;
            }
        }
        if (found == -1 || d[found] > k) {
            break;
        }
        k -= d[found];
        d[found] = -1;
        --ans;
    }
    cout << ans << "\n";

}


signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
