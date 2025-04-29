#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1'000'000'000;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<ll> v(n), s(m);
    for (int i = 0; i < n; ++i) cin >> v[i];
    for (int i = 0; i < m; ++i) cin >> s[i];


    //convert s_i to distances (dist [0,s[0]] = s[0])
    for (int i = m - 1; i > 0; --i)
        s[i] = s[i] - s[i - 1];

//    assert(*min_element(s.begin(), s.end()) == *max_element(s.begin(), s.end()));

    for (ll i = 0; i < n; ++i) {
        cout << m * i * (i + 1) / 2 << "\n";
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
