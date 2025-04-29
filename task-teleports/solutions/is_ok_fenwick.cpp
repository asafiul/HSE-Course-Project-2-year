#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define TIME (clock() * 1.0 / CLOCKS_PER_SEC)

const int M = (int)(1.5e5 + 239);

int tree[M];

void upd(int x) {
    for (; x < M; x |= x + 1) {
        tree[x]++;
    }
}

int getsum(int x) {
    int ans = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1) {
        ans += tree[x];
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<int> s(m);
    for (int i = 0; i < m; i++) {
        cin >> s[i];
    }
    for (int i = m - 1; i > 0; i--) {
        s[i] -= s[i - 1];
    }
    vector<pair<int, int>> nw;
    int mx = s[0];
    nw.emplace_back(mx, 0);
    for (int i = 0; i < m; i++) {
        if (s[i] <= mx) {
            nw.back().second++;
        } else {
            mx = s[i];
            nw.emplace_back(mx, 1);
        }
    }
    m = nw.size();

    int cur_max = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int x = 0; x < (int)nw.size(); x++) {
            {
                ll pos = (ll)v[i] * nw.back().first / nw[x].first;
                ans += (ll)getsum((int)min(pos, (ll)M - 1)) * nw[x].second;
            }
            {
                ll pos = (ll)v[i] * nw[x].first / nw.back().first;
                if (pos < cur_max) {
                    ans += (ll)(i - getsum((int)pos)) * nw[x].second;
                }
            }
        }

        upd(v[i]);
        cur_max = max(cur_max, v[i]);

        cout << ans << "\n";
    }
}

int main() {
#ifdef ONPC
    freopen("input", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
