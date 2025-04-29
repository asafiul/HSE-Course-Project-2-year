#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define TIME (clock() * 1.0 / CLOCKS_PER_SEC)

const int M = (int)(1.5e5 + 239);
const int U = 9;
const int BS = (1 << U);
const int CNT = (M / BS) + 2;

ll bval[CNT], elem[M];

inline void add(int x, int val) {
    bval[x >> U] += val;
    elem[x] += val;
}

inline ll getsum(int x) {
    int b = x >> U;
    ll ans = 0;
    for (int i = 0; i < b; i++) ans += bval[i];
    for (int i = b * BS; i < x; i++) ans += elem[i];
    return ans;
}

pair<int, int> vals[M];
ll prod2[M];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) add(i, m);
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    vector<int> s(m);
    for (int i = 0; i < m; i++) cin >> s[i];
    for (int i = m - 1; i > 0; i--) s[i] -= s[i - 1];

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
    vector<int> sn(m);
    for (int i = 0; i < m; i++) sn[i] = nw[i].first;

    for (int i = 0; i < n; i++) {
        vals[i].first = v[i];
        vals[i].second = i;
    }
    sort(vals, vals + n);
    for (int i = 0; i < n; i++) {
        prod2[i] = (ll)vals[i].first * sn.back();
    }

    vector<int> ptr1(m), ptr2(m);
    vector<ll> ans(n);
    for (int pi = 0; pi < n; pi++) {
        ll prod1 = (ll)vals[pi].first * sn.back();
        for (int x = 0; x < m; x++) {
            while (ptr1[x] < n && (ll)vals[ptr1[x]].first * sn[x] <= prod1) {
                add(vals[ptr1[x]++].second, nw[x].second);
            }
            while (ptr2[x] < n && (ll)vals[pi].first * sn[x] >= prod2[ptr2[x]]) {
                add(vals[ptr2[x]++].second, -nw[x].second);
            }
        }
        ans[vals[pi].second] = getsum(vals[pi].second);
    }

    for (int i = 1; i < n; i++) ans[i] += ans[i - 1];
    for (int i = 0; i < n; i++) cout << ans[i] << "\n";
}

int main() {
#ifdef ONPC
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
