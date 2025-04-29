#include <bits/stdc++.h>

using namespace std;


#define szof(x) ((int)x.size())

using ll = long long;
const ll inf = 1'000'000'000'000'000'000;


void solve() {
    int n, m;
    cin >> n >> m;

    vector<ll> v(n), s(m + 1);
    for (int i = 0; i < n; ++i) cin >> v[i];
    for (int i = 1; i <= m; ++i) cin >> s[i];

    for (int r = 0; r < n; ++r) {
        ll sum = 0;
        vector<int> last(r + 1, 0);

        set<pair<ll, int>> st;
        for (int i = 0; i <= r; ++i)
            st.insert({s[1] * v[i], i});

        while (!st.empty()) { //nm
            sum += szof(st) - 1;

            auto [val, ind] = *st.begin();
            st.erase(st.begin());

            ++last[ind];

            if (last[ind] < m)
                st.insert({(s[last[ind] + 1] -
                            s[last[ind]])
                           * v[ind], ind});

        }
        cout << sum << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
