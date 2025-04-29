#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <map>
#include <set>
#include <random>
#include <cassert>
#include <deque>

using namespace std;

inline void solve() {
    int n, k;
    cin >> n >> k;
    vector <pair <int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    vector <int> flex;
    for (int i = 0; i + 1 < n; ++i) {
        flex.push_back(a[i + 1].first - a[i].second);
    }
    sort(flex.begin(), flex.end());
    int ans = n;
    for (int i : flex) {
        if (i <= k) {
            k -= i;
            ans--;
        }
    }
    cout << ans;
}

signed main() {
    if (1) {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
    }
    int32_t t = 1;
//    cin >> t;
    while (t--) {
        solve();
    }
}

/*

 */
