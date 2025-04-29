#include <random>

#include "bits/stdc++.h"

using namespace std;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> segments(n);
    for (auto &[l, r]: segments) {
        cin >> l >> r;
    }
    cout << "1\n";
}


signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
