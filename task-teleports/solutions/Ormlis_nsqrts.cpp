#pragma GCC optimize("Ofast")
#include "bits/stdc++.h"

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define ar array

using namespace std;

typedef long long ll;
using vi = vector<int>;
using vl = vector<ll>;

const int INFi = 2e9;
const ll INF = 2e18;

template<typename T>
bool ckmax(T &x, const T &y) {
    if (x < y) {
        x = y;
        return true;
    }
    return false;
}

template<typename T>
bool ckmin(T &x, const T &y) {
    if (x > y) {
        x = y;
        return true;
    }
    return false;
}

const int N = 1.5e5 + 5;
constexpr int B = 450;
constexpr int BS = (N - 1) / B + 1;

namespace FastGet {
    ll p[N];
    ll pb[BS];

    void Add(int i, ll x) {
        int j = i / B;
        int r = (j + 1) * B;
        for (int t = i; t < r; ++t) p[t] += x;
        for (int t = j + 1; t < BS; ++t) pb[t] += x;
    }

    ll Get(int i) {
        return i >= 0 ? p[i] + pb[i / B] : 0;
    }
}

namespace FastUpd {
    ll p[N];
    ll pb[BS];

    void Add(int i, ll x) {
        p[i] += x;
        pb[i / B] += x;
    }

    ll Get(int i) {
        ll r = 0;
        int j = i / B;
        for(int t = 0; t < j; ++t) r += pb[t];
        for(int t = j * B; t <= i; ++t) r += p[t];
        return r;
    }
}


// (d[m] / v[max], max) >= (d[i] / v[j], j)
// (d[m] * v[j], max) >= (d[i] * v[max], j)

void solve() {
    int n, m;
    cin >> n >> m;
    vi v(n);
    rep(i, n) cin >> v[i];
    vi d(m);
    rep(i, m) cin >> d[i];
    for (int i = m - 1; i >= 1; --i) d[i] -= d[i - 1];

    vi c(m);
    {
        int t = 0;
        for (int l = 0, r = 0; l < m; l = r) {
            while (r < m && d[r] <= d[l]) r++;
            d[t] = d[l];
            c[t] = r - l;
            t++;
        }
        m = t;
        c.resize(m);
        d.resize(m);
    }
    assert(d.size() <= 600); // O(sqrt(1e5))

    vector<ll> yy;
    rep(i, n) {
        yy.push_back(1ll * v[i] * d[m - 1]);
    }
    sort(all(yy));
    yy.resize(unique(all(yy)) - yy.begin());

    const int sz = yy.size();
    vector<vi> nxt(n, vi(m, yy.size()));

    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&] (const int &i, const int &j) {
        return v[i] < v[j];
    });
    vi reord(n);
    rep(i, n) reord[ord[i]] = i;
    vi vord(n);
    rep(i, n) vord[i] = v[ord[i]];

    rep(j, m) {
        int uk = 0;
        rep(p, yy.size()) {
            while (uk < n && 1ll * d[j] * vord[uk] < yy[p]) {
                nxt[uk++][j] = p;
            }
        }
    }

    ll ans = 0;
    rep(i, n) {
        // ans += #(j, k) d[j]/v[k] < d[m-1]/v[i]
        // for j in 0...m-1 ans += #(k) d[m-1]/v[k] >= d[j]/v[i]


        int p;
        int ii = reord[i];

        int pos = nxt[ii][m - 1];
        if (pos > 0 && yy[pos - 1] == 1ll * d[m - 1] * v[i]) pos--;
        ans += FastUpd::Get(pos);

        rep(j, m) {
            ll va = 1ll * d[j] * v[i];
            p = nxt[ii][j] - 1;
            ans += 1ll * c[j] * (i - FastGet::Get(p));

            FastUpd::Add(p + (int) (p == -1 || yy[p] < va), c[j]);
        }
        FastGet::Add(p, 1);

        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << setprecision(15) << fixed;
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
