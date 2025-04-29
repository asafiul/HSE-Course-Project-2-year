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

struct fenwick {
    vector<ll> fenw;
    int n;

    void build(int k) {
        n = k;
        fenw.resize(n);
    }

    void upd(int i, ll x) {
        for (; i < n; i |= (i + 1)) fenw[i] += x;
    }

    ll get(int i) {
        ll r = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1) r += fenw[i];
        return r;
    }
};

// (d[m] / v[max], max) >= (d[i] / v[j], j)
// (d[m] * v[j], max) >= (d[i] * v[max], j)

struct Frac {
    int a, b;
};

bool operator<(const Frac &x, const Frac &y) {
    return 1ll * x.a * y.b < 1ll * y.a * x.b;
}

bool operator==(const Frac &x, const Frac &y) {
    return 1ll * x.a * y.b == 1ll * y.a * x.b;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vi v(n);
    rep(i, n) cin >> v[i];
    vi d(m);
    rep(i, m) cin >> d[i];
    for (int i = m - 1; i >= 1; --i) d[i] -= d[i - 1];

    vi c(m);
    ll sum_c = m;
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
    assert(d.size() <= 1000); // O(sqrt(1e5))

    vector<Frac> xx;
    vector<ll> yy;
    rep(i, n) {
        xx.push_back({d[m - 1], v[i]});
        yy.push_back(1ll * v[i] * d[m - 1]);
    }
    sort(all(xx));
    xx.resize(unique(all(xx)) - xx.begin());
    sort(all(yy));
    yy.resize(unique(all(yy)) - yy.begin());
    fenwick f, f2;
    f.build(xx.size());
    f2.build(yy.size());

    ll ans = 0;
    rep(i, n) {
        // ans += #(j, k) d[j]/v[k] < d[m-1]/v[i]
        // for j in 0...m-1 ans += #(k) d[m-1]/v[k] >= d[j]/v[i]

        rep(j, m) {
            Frac x = {d[j], v[i]};
            int pos = lower_bound(all(xx), x) - xx.begin();
            ll cnt_early = f.get(pos - 1); // can be done in O(1)
            ans += 1ll * (i - cnt_early) * c[j];
            if (j == m - 1) {
                f.upd(pos, 1);
            }
        }

        rep(j, m) {
            ll value = 1ll * d[j] * v[i];
            int pos = upper_bound(all(yy), value) - yy.begin();
            ans += 1ll * c[j] * (i - f2.get(pos - 1));
        }
        {
            int pos = lower_bound(all(yy), 1ll * v[i] * d[m - 1]) - yy.begin();
            f2.upd(pos, 1);
        }

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
