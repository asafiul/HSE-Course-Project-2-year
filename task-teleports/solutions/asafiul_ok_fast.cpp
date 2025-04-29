#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1'000'000'000;

struct SQRTDecomposition {

    int b, n;

    vector<int> v, block, ind;
    vector<bool> mod;

    explicit SQRTDecomposition(int V) {
        n = V + 1;
        b = static_cast<int>(sqrt(V)) + 1;
        v.assign(n, 0);
        ind.assign(n + 1, 0);
        mod.assign(n + 1, false);
        block.assign((n - 1) / b + 1, 0);
        ind[n] = static_cast<int>(block.size());
        for (int i = 0; i < n; ++i) {
            mod[i] = i % b;
            ind[i] = i / b;
        }
    }

    void upd(int i) {
        do {
            ++v[i++];
        } while (mod[i]);

        i = ind[i];
        while (i < block.size())
            ++block[i++];
    }

    int getPrefix(int r) {
        r = min(r, n - 1);
        return v[r] + block[ind[r]];
    }

    int getSuffix(int l) {
        assert(l > 0);
        return getPrefix(n - 1) - getPrefix(l - 1);
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

    SQRTDecomposition dec(*max_element(v.begin(), v.end()));
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < l.size(); ++j) {
            int r_limit = (int) min(inf, v[i] * (ll) l.back() / l[j]);
            sum += dec.getPrefix(r_limit) * c[j];

            int l_limit = (int) min(inf, v[i] * (ll) l[j] / l.back() + 1);
            sum += dec.getSuffix(l_limit) * c[j];
        }
        dec.upd(v[i]);
        cout << sum << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
