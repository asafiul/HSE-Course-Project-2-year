#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1'000'000'000;

void solve() {
    ll n, m;
    cin >> n >> m;

    vector<ll> v(n), s(m);
    for (int i = 0; i < n; ++i) cin >> v[i];
    for (int i = 0; i < m; ++i) cin >> s[i];

//    assert(*max_element(v.begin(), v.end()) <= 2);

    //convert s_i to distances (dist [0,s[0]] = s[0])
    for (int i = m - 1; i > 0; --i)
        s[i] = s[i] - s[i - 1];

    ll ind_max = max_element(s.begin(), s.end()) - s.begin();

    ll ind2_max_less_equal = 0;

    for (int i = 0; i < m; ++i)
        if (s[i] * 2 > s[ind_max]) {
            ind2_max_less_equal = i;
            break;
        }

    ll ind2_max_less = 0;

    for (int i = 0; i < m; ++i)
        if (s[i] * 2 >= s[ind_max]) {
            ind2_max_less = i;
            break;
        }

    vector<ll> cnt(3);
    ll ans = 0;
    for (auto &x: v) {
        ++cnt[x];

        ans += ind_max * (cnt[x] - 1) + (cnt[x] - 1) * ind_max + (cnt[x] - 1) * (m - ind_max);
        if (x == 1) {
            ans += cnt[2] * m;
            ans += cnt[2] * ind2_max_less_equal;
        } else {
            ans += cnt[1] * m;
            ans += cnt[1] * ind2_max_less;
        }

        cout << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
