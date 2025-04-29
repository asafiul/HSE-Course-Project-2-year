#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()

using namespace std;

inline int nxt() {
    int x;
    cin >> x;
    return x;
}

struct Pass {
    long long t;
    int cnt;
    int i;
    char last;

    weak_ordering operator <=>(const Pass& ot) const {
        return tie(t, i) <=> tie(ot.t, ot.i);
    }
};

template <typename Int>
struct FastAdd {
    int n;
    const int k;
    vector<Int> a;
    vector<Int> blocks;

    FastAdd(int _n): n(_n), k(round(sqrt(n))), a(_n), blocks((_n + k - 1) / k) {}

    void add(int pos, Int x) {
        a[pos] += x;
        blocks[pos / k] += x;
    }

    Int get(int pos) const {
        Int res = 0;
        while ((pos + 1) % k) {
            res += a[pos--];
        }
        pos = (pos + 1) / k;
        while (pos --> 0) {
            res += blocks[pos];
        }
        return res;
    }
};

template <typename Int>
struct FastGet {
    int n;
    const int k;
    vector<Int> a;
    vector<Int> blocks;

    FastGet(int _n): n(_n), k(round(sqrt(n))), a(_n), blocks((_n + k - 1) / k) {}

    void add(int pos, Int x) {
        do {
            a[pos] += x;
            ++pos;
        } while (pos < n && pos % k);
        if (pos < n) {
            pos /= k;
            while (pos < (int)blocks.size()) {
                blocks[pos] += x;
                ++pos;
            }
        }
    }

    Int get(int pos) const {
        return a[pos] + blocks[pos / k];
    }
};

void solve() {
    int n = nxt(), m = nxt();
    vector<int> v(n);
    generate(all(v), nxt);
    vector<int> s(m);
    generate(all(s), nxt);
    for (int i = m - 1; i > 0; --i) {
        s[i] -= s[i - 1];
    }
    vector<pair<int, int>> sc;
    for (int x : s) {
        if (sc.empty() || x > sc.back().first) {
            sc.push_back({x, 1});
        } else {
            sc.back().second += 1;
        }
    }
    m = sc.size();

    vector<long long> ans(n);
    FastAdd<long long> cur_cnt(n);
    FastGet<int> finished(n);

    vector<pair<int, int>> guys(n);
    for (int i = 0; i < n; ++i) {
        guys[i] = {v[i], i};
    }
    sort(all(guys));

    vector<int> ptr(m);
    for (int id_finished = 0; id_finished < n; ++id_finished) {
        const int i = guys[id_finished].second;
        const long long t = 1ll * v[i] * sc.back().first;
        for (int j = 0; j < m; ++j) {
            while (ptr[j] < n) {
                const long long curt = 1ll * guys[ptr[j]].first * sc[j].first;
                if (curt > t) {
                    break;
                }
                if (curt == t && guys[ptr[j]].second > i) {
                    break;
                }
                const int id = guys[ptr[j]].second;
                ans[id] += 1ll * sc[j].second * (id - finished.get(id));
                cur_cnt.add(id, sc[j].second);
                ++ptr[j];
            }
        }
        ans[i] += cur_cnt.get(i - 1);
        finished.add(i, 1);
    }

    for (int i = 1; i < n; ++i) {
        ans[i] += ans[i - 1];
    }
    for (auto x : ans) {
        cout << x << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1; // nxt();
    while (t--) {
        solve();
    }

    return 0;
}
