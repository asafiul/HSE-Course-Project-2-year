#include <bits/stdc++.h>

using namespace std;

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

        while (true) { //nm
            ll val = inf;
            int ind = -1;
            int cnt_passed = 0;

            for (int i = 0; i <= r; ++i) {
                if (last[i] == m) {
                    ++cnt_passed;
                    continue;
                }

                ll time = (s[last[i] + 1] - s[last[i]]) * v[i];
                if (time < val) {
                    val = time;
                    ind = i;
                }
            }

            if (ind == -1)
                break;

            sum += (r + 1) - cnt_passed - 1;
            ++last[ind];
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
