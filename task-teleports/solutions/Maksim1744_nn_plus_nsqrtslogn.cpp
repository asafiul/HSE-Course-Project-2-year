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

    vector<ll> sums(n);
    vector<bool> on(n, false);

    for (int i = 0; i < n; ++i) {
        on[where[i]] = true;
        for (int j = 0; j + 1 < up.size(); ++j) {
            S s{(ll)v[i].first * up[j].first, v[i].second, up[j].second, j + 1 == up.size()};
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
            sums[r] += s.len;
        }

        ll ans = 0;
        ll cur = i + 1;
        for (int i = 0; i < n; ++i) {
            ans += sums[i] * (cur - 1);
            if (on[i]) {
                ans += checkpoints[i].len * (cur - 1);
                --cur;
            }
        }
        cout << ans << '\n';
    }

    // for (int pref = 1; pref <= n; ++pref) {
    //     shows;
    //     show(pref);
    //     vector<S> segs;
    //     for (int i = 0; i < n; ++i) {
    //         for (int j = 0; j < up.size(); ++j) {
    //             if (v[i].second < pref)
    //                 segs.pb(S{(ll)v[i].first * up[j].first, v[i].second, up[j].second, j + 1 == up.size()});
    //         }
    //     }

    //     sort(segs.begin(), segs.end(), [&](const auto& a, const auto& b) {
    //         return mp(a.sv, a.i) < mp(b.sv, b.i);
    //     });

    //     show(segs);

    //     ll cur = pref;
    //     ll ans = 0;
    //     for (const auto& s : segs) {
    //         ans += (cur - 1) * s.len;
    //         if (s.last)
    //             --cur;
    //     }
    //     cout << ans << '\n';
    // }

    return 0;
}
