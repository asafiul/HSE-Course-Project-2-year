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
#include <queue>
using namespace std;

inline void solve() {
    vector <string> a(4);
    for (int i = 0; i < 4; ++i) cin >> a[i];
    vector <int> p = {0, 1, 2, 3};
    //    23
    //    ||
    //0---01
    //1---23
    const int n = 18;
    do {
        for (int x1 = 0; x1 < n; ++x1) {
            for (int x2 = x1 + 1; x2 < n; ++x2) {
                int x_len = x2 - x1 + 1;
                for (int y1 = 0; y1 < n; ++y1) {
                    for (int y2 = y1 + 1; y2 < n; ++y2) {
                        int y_len = y2 - y1 + 1;
                        for (int len0 = 0; len0 <= y1 && len0 + y_len <= a[p[0]].size(); ++len0) {
                            for (int len1 = 0; len1 <= y1 && len1 + y_len <= a[p[1]].size(); ++len1) {
                                char mem[4];
                                mem[0] = a[p[0]][len0];
                                mem[1] = a[p[0]][len0 + y_len - 1];
                                mem[2] = a[p[1]][len1];
                                mem[3] = a[p[1]][len1 + y_len - 1];

                                int len2 = 0;
                                bool ok = false;
                                while (len2 <= x1 && len2 + x_len <= a[p[2]].size()) {
                                    if (mem[0] == a[p[2]][len2] && mem[2] == a[p[2]][len2 + x_len - 1]) {
                                        ok = true;
                                        break;
                                    }
                                    len2++;
                                }
                                if (!ok) continue;

                                int len3 = 0;
                                ok = false;
                                while (len3 <= x1 && len3 + x_len <= a[p[3]].size()) {
                                    if (mem[1] == a[p[3]][len3] && mem[3] == a[p[3]][len3 + x_len - 1]) {
                                        ok = true;
                                        break;
                                    }
                                    len3++;
                                }
                                if (!ok) continue;

                                vector <string> ans(n, string(n, '.'));

                                for (int i = 0; i < a[p[0]].size(); ++i) {
                                    ans[x1][y1 - len0 + i] = a[p[0]][i];
                                }

                                for (int i = 0; i < a[p[1]].size(); ++i) {
                                    ans[x2][y1 - len1 + i] = a[p[1]][i];
                                }

                                for (int i = 0; i < a[p[2]].size(); ++i) {
                                    ans[x1 - len2 + i][y1] = a[p[2]][i];
                                }

                                for (int i = 0; i < a[p[3]].size(); ++i) {
                                    ans[x1 - len3 + i][y2] = a[p[3]][i];
                                }

                                cout << "YES\n";
                                for (int i = 0; i < n; ++i) cout << ans[i] << "\n";
                                return;
                            }
                        }
                    }

                }
            }
        }
    } while (next_permutation(a.begin(), a.end()));
    cout << "NO\n";
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
4 3 1 4
15
1 2 10
2 3 12
3 4 8
 */
