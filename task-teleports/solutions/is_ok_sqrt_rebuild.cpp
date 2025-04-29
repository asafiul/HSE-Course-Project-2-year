#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define TIME (clock() * 1.0 / CLOCKS_PER_SEC)

const int M = (int)(1e5 + 239);
const int BS = 64;

int cnt[M], pref[M];

void build() {
    pref[0] = cnt[0];
    for (int i = 1; i < M; i++) pref[i] = pref[i - 1] + cnt[i];
}

int pref_sec[M];

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
    for (int i = 0; i < (int)nw.size(); i++) {
        pref_sec[nw[i].first] += nw[i].second;
    }
    for (int i = 1; i < M; i++) {
        pref_sec[i] += pref_sec[i - 1];
    }

    int from = 0;
    int cur_max = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int x = 0; x < (int)nw.size(); x++) {
            {
                ll pos = (ll)v[i] * nw.back().first / nw[x].first;
                if (pos < cur_max) {
                    ans += (ll)pref[(int)pos] * nw[x].second;
                } else {
                    ans += (ll)from * nw[x].second;
                }
            }
            {
                ll pos = (ll)v[i] * nw[x].first / nw.back().first;
                if (pos < cur_max) {
                    ans += (ll)(from - (ll)pref[(int)pos]) * nw[x].second;
                }
            }
        }
        for (int j = from; j < i; j++) {
            {
                ll pos = (ll)v[i] * nw.back().first / v[j];
                ans += pref_sec[(int)min(pos, (ll)M - 1)];
            }
            {
                ll pos = ((ll)v[j] * nw.back().first - 1) / v[i];
                ans += pref_sec[(int)min(pos, (ll)M - 1)];
            }
        }

        cnt[v[i]]++;
        if ((i + 1) % BS == 0) {
            build();
            from = i + 1;
        }
        cur_max = max(cur_max, v[i]);

        cout << ans << "\n";
    }
}

int main() {
#ifdef ONPC
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
