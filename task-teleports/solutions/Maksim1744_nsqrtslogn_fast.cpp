/*
    author:  Maksim1744
    created: 07.04.2024 14:21:40
*/

#include "bits/stdc++.h"

using namespace std;

using ll = long long;
using ld = long double;

#define mp   make_pair
#define pb   push_back
#define eb   emplace_back

#define sum(a)     ( accumulate ((a).begin(), (a).end(), 0ll))
#define mine(a)    (*min_element((a).begin(), (a).end()))
#define maxe(a)    (*max_element((a).begin(), (a).end()))
#define mini(a)    ( min_element((a).begin(), (a).end()) - (a).begin())
#define maxi(a)    ( max_element((a).begin(), (a).end()) - (a).begin())
#define lowb(a, x) ( lower_bound((a).begin(), (a).end(), (x)) - (a).begin())
#define uppb(a, x) ( upper_bound((a).begin(), (a).end(), (x)) - (a).begin())

template<typename T>             vector<T>& operator--            (vector<T> &v){for (auto& i : v) --i;            return  v;}
template<typename T>             vector<T>& operator++            (vector<T> &v){for (auto& i : v) ++i;            return  v;}
template<typename T>             istream& operator>>(istream& is,  vector<T> &v){for (auto& i : v) is >> i;        return is;}
template<typename T>             ostream& operator<<(ostream& os,  vector<T>  v){for (auto& i : v) os << i << ' '; return os;}
template<typename T, typename U> pair<T,U>& operator--           (pair<T, U> &p){--p.first; --p.second;            return  p;}
template<typename T, typename U> pair<T,U>& operator++           (pair<T, U> &p){++p.first; ++p.second;            return  p;}
template<typename T, typename U> istream& operator>>(istream& is, pair<T, U> &p){is >> p.first >> p.second;        return is;}
template<typename T, typename U> ostream& operator<<(ostream& os, pair<T, U>  p){os << p.first << ' ' << p.second; return os;}
template<typename T, typename U> pair<T,U> operator-(pair<T,U> a, pair<T,U> b){return mp(a.first-b.first, a.second-b.second);}
template<typename T, typename U> pair<T,U> operator+(pair<T,U> a, pair<T,U> b){return mp(a.first+b.first, a.second+b.second);}
template<typename T, typename U> void umin(T& a, U b){if (a > b) a = b;}
template<typename T, typename U> void umax(T& a, U b){if (a < b) a = b;}

#ifdef HOME
#define SHOW_COLORS
#include "/mnt/c/Libs/tools/print.cpp"
#else
#define show(...) void(0)
#define debugf(fun)   fun
#define debugv(var)   var
#define mclock    void(0)
#define shows     void(0)
#define debug  if (false)
#define OSTREAM(...)    ;
#define OSTREAM0(...)   ;
#endif

struct S {
    ll sv;
    int i;
    int len;
    bool last;
};

OSTREAM(S, sv, i, len, last);

template<typename T>
struct fenwick {
    vector<T> tree;
    int n;
    int K;

    fenwick(int n = 0) : n(n) {
        tree.assign(n, 0);
        K = 0;
        while ((1 << K) <= n)
            ++K;
    }

    void add(int i, T k) {
        for (; i < n; i = (i | (i + 1)))
            tree[i] += k;
    }

    T ask(int r) {
        T res = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            res += tree[r];
        return res;
    }

    T ask(int l, int r) {
        if (l > r) return 0;
        return ask(r) - ask(l - 1);
    }

    // find first i such that sum[0..i] >= x
    int lower_bound(T x) {
        int cur = 0;
        T cur_sum = 0;
        for (int k = K - 1; k >= 0; --k) {
            int ind = cur | ((1 << k) - 1);
            if (ind >= n) continue;
            if (cur_sum + tree[ind] >= x) continue;
            cur_sum += tree[ind];
            cur |= (1 << k);
        }
        return cur;
    }
};

const int B = 350;
struct SumsTree {
    vector<ll> v;
    vector<ll> blocks;
    ll tot = 0;

    SumsTree(int n) {
        v.assign(n, 0);
        blocks.assign((n + B - 1) / B, 0);
    }

    void add(int i, ll x) {
        blocks[i / B] += x;
        v[i] += x;
        tot += x;
    }

    ll pref_sum(int i) const {
        ll ans = 0;
        while (i >= 0 && i % B != B - 1) {
            ans += v[i];
            --i;
        }
        while (i >= 0) {
            ans += blocks[i / B];
            i -= B;
        }
        return ans;
    }
};

// const int B = 350;
struct OnsTree {
    vector<ll> v;
    vector<ll> blocks;

    OnsTree(int n) {
        v.assign(n, 0);
        blocks.assign((n + B - 1) / B, 0);
    }

    void add(int i, ll x) {
        while (i < v.size() && i % B != 0) {
            v[i] += x;
            ++i;
        }
        if (i == v.size()) return;
        i /= B;
        for (; i < blocks.size(); ++i)
            blocks[i] += x;
    }

    ll pref_sum(int i) const {
        if (i < 0) return 0;
        return blocks[i / B] + v[i];
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first;
        v[i].second = i;
    }
    vector<int> s(m);
    cin >> s;
    for (int i = m - 1; i >= 1; --i)
        s[i] -= s[i - 1];

    vector<pair<int, int>> up;
    int last = -1;
    for (int i = 0; i < m; ++i) {
        if (s[i] > last) {
            last = s[i];
            up.eb(s[i], 0);
        }
        up.back().second++;
    }

    vector<S> checkpoints;
    vector<int> where(n);
    for (int i = 0; i < n; ++i) {
        checkpoints.pb(S{(ll)v[i].first * up.back().first, v[i].second, up.back().second, true});
    }


    auto cmp = [&](const S& a, const S& b) {
        return mp(a.sv, a.i) < mp(b.sv, b.i);
    };
    sort(checkpoints.begin(), checkpoints.end(), cmp);
    for (int i = 0; i < n; ++i) {
        where[checkpoints[i].i] = i;
    }
    vector<pair<int, int>> cpvs(n);
    for (int i = 0; i < n; ++i) {
        cpvs[i] = {v[checkpoints[i].i].first, checkpoints[i].i};
    }
    vector<int> ptr(n);
    for (int i = 0; i < n; ++i) {
        ptr[i] = i;
    }
    const int N = cpvs.back().first + 5;
    vector<int> left(N, -1);
    for (int i = 0; i < n; ++i) {
        left[cpvs[i].first] = i;
    }
    for (int i = 1; i < left.size(); ++i) {
        if (left[i] == -1)
            left[i] = left[i - 1];
    }

    vector<ll> sums(n);
    vector<bool> on(n, false);

    OnsTree ons(n);
    SumsTree sums_tree(n);

    ll sm = up.back().first;
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        on[where[i]] = true;
        ons.add(where[i], 1);
        ans += sums_tree.pref_sum(where[i]);

        sums_tree.add(where[i], checkpoints[i].len);
        ans += (ll)checkpoints[i].len * (i + 1 - ons.pref_sum(where[i]-1));

        auto getind = [&](const S& s) {
            if (s.sv % sm != 0) {
                return left[s.sv / sm] + 1;
            }
            int l = -1, r = n;
            while (r - l > 1) {
                int c = (l + r) / 2;
                if (cmp(s, checkpoints[c])) {
                    r = c;
                } else {
                    l = c;
                }
            }
            assert(r != n);
            return r;
        };

        for (int j = 0; j + 1 < up.size(); ++j) {
            S s{(ll)v[i].first * up[j].first, v[i].second, up[j].second, j + 1 == up.size()};
            int r = getind(s);
            sums[r] += s.len;
            ans += (ll)s.len * (i + 1 - ons.pref_sum(r-1));
            sums_tree.add(r, s.len);
        }
        cout << ans - sums_tree.tot << '\n';
    }

    return 0;
}
