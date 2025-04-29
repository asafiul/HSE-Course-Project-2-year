#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1'000'000'000;

struct Fenwick {
    int n;
    vector<int> f;

    explicit Fenwick(int maxV) {
        n = maxV + 1;
        f.assign(n, 0);
    }

    void upd(int i) {
        for (; i < n; i = (i | (i + 1)))
            f[i]++;
    }

    int getPrefix(int i) {
        i = min(i, n - 1);
        int res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res += f[i];
        return res;
    }

    int getSuffix(int i) {
        assert(i > 0);
        return getPrefix(n - 1) - getPrefix(i - 1);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> v(n), s(m);
    for (int i = 0; i < n; ++i) cin >> v[i];
    for (int i = 0; i < m; ++i) cin >> s[i];

    //convert s_i to distances (dist [0,s[0]] = s[0])
    for (int i = m - 1; i > 0; --i)
        s[i] = s[i] - s[i - 1];

    // record lengths and segments count
    vector<int> l;
    vector<ll> c;
    for (int i = 0; i < m;) {
        l.push_back(s[i]);
        c.push_back(0);
        while (i < m && s[i] <= l.back()) {
            ++c.back();
            ++i;
        }
    }
    // expected size for l and c <= sqrt(s) ~ 500

    Fenwick fen(*max_element(v.begin(), v.end()));
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < l.size(); ++j) {
            int r_limit = (int) min(inf, v[i] * (ll) l.back() / l[j]);
            sum += fen.getPrefix(r_limit) * c[j];

            int l_limit = (int) min(inf, v[i] * (ll) l[j] / l.back() + 1);
            sum += fen.getSuffix(l_limit) * c[j];
        }
        fen.upd(v[i]);
        cout << sum << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
