#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll inf = 1'000'000'000;

struct SQRTDecomposition {

    int BLOCK_SIZE, SIZE;

    vector<int> pref_sum_in_block, add_to_block;

    explicit SQRTDecomposition(int maxV) {
        SIZE = maxV + 1;
        BLOCK_SIZE = static_cast<int>(sqrt(maxV)) + 1;
        pref_sum_in_block.assign(SIZE, 0);
        add_to_block.assign((SIZE - 1) / BLOCK_SIZE + 1, 0);
    }

    void upd(int i) {
        for (int j = i; j < SIZE && (j == i || j % BLOCK_SIZE != 0); ++j)
            ++pref_sum_in_block[j];

        int block_index = i / BLOCK_SIZE + 1;
        for (int j = block_index; j < add_to_block.size(); ++j)
            ++add_to_block[j];
    }

    int getPrefix(int r) {
        r = min(r, SIZE - 1);
        int block_index = r / BLOCK_SIZE;

        return pref_sum_in_block[r] + add_to_block[block_index];
    }

    int getSuffix(int l) {
        assert(l > 0);
        return getPrefix(SIZE - 1) - getPrefix(l - 1);
    }

};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> v(n), s(m);
    for (int i = 0; i < n; ++i) cin >> v[i];
    for (int i = 0; i < m; ++i) cin >> s[i];

    //convert s_i to distances (dist [0,s[0]] = s[0])
    for (int i = m - 1; i > 0; --i)
        s[i] = s[i] - s[i - 1];

    // record lengths and segments count
    vector<int> l;
    vector<ll> c;
    for (int i = 0; i < m;) {
        l.push_back(s[i]);
        c.push_back(0);
        while (i < m && s[i] <= l.back()) {
            ++c.back();
            ++i;
        }
    }
    // expected size for l and c <= sqrt(s) ~ 500

    SQRTDecomposition dec(*max_element(v.begin(), v.end()));
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < l.size(); ++j) {
            int r_limit = (int) min(inf, v[i] * (ll) l.back() / l[j]);
            sum += dec.getPrefix(r_limit) * c[j];

            int l_limit = (int) min(inf, v[i] * (ll) l[j] / l.back() + 1);
            sum += dec.getSuffix(l_limit) * c[j];
        }
        dec.upd(v[i]);
        cout << sum << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
