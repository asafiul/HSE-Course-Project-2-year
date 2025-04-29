#include <bits/stdc++.h>
#define endl '\n'
#define all(a) (a).begin(), (a).end()
#define len(a) (int) (a).size()
#define forn(i, n) for (int (i) = 0; (i) < (n); ++(i))
#define int int64_t
#ifdef LOCAL
#include "debug.h"
// #define dbg(...) 42
#else
#define dbg(...) 42
#endif
using namespace std;

void solve();

mt19937 rnd(2007);

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    swap(rng, rnd);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}


void solve() {
    int n, k; cin >> n >> k;
    vector<pair<int, int>> a(n);
    forn (i, n) {
        cin >> a[i].first >> a[i].second;
    }
    sort(all(a));
    vector<int> diffs;
    forn (i, n - 1) {
        diffs.push_back(a[i + 1].first - a[i].second);
    }
    sort(all(diffs));
    int ans = n;
    for (auto diff : diffs) {
        if (k >= diff) {
            k -= diff;
            --ans;
        }
    }
    cout << ans << endl;

}