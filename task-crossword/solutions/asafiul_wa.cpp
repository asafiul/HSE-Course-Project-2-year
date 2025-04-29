#include "bits/stdc++.h"

using namespace std;

#define sz(a) (int)a.size()

void solve() {
    vector<string> s(4);
    cin >> s[0] >> s[1] >> s[2] >> s[3];

    vector<int> ind{0, 1, 2, 3};

    do {
        string t[4];
        for (int i = 0; i < 4; ++i) {
            t[i] = s[ind[i]];
        }
        for (int p0 = 0; p0 < sz(t[0]); ++p0) {
            for (int p1 = 0; p1 < sz(t[1]); ++p1) {
                for (int p2 = 0; p2 < sz(t[2]); ++p2) {
                    if (t[0][p0] == t[2][p2]) {
                        for (int p2_next = p2 + 1; p2_next < sz(t[2]); ++p2_next) {
                            if (t[1][p1] == t[2][p2_next]) {
                                int d = p2_next - p2;
                                int p0_next = p0 + 1;
                                int p1_next = p1 + 1;
                                while (p0_next < sz(t[0]) && p1_next < sz(t[1])) {
                                    for (int m = 0; m + d < sz(t[3]); ++m) {
                                        if (t[3][m] == t[0][p0_next] && t[3][m + d] == t[1][p1_next]) {
                                            vector res(4, vector<int>(3));
                                            res[ind[0]][0] = res[ind[1]][0] = 1;
                                            res[ind[2]][0] = res[ind[3]][0] = 2;

                                            int row = 50;
                                            int col = 50;
                                            res[ind[0]][1] = row, res[ind[0]][2] = col - p0;
                                            res[ind[1]][1] = row + d, res[ind[1]][2] = col - p1;
                                            res[ind[2]][1] = row - p2, res[ind[2]][2] = col;
                                            res[ind[3]][1] = row - m, res[ind[3]][2] = col + (p0_next - p0);

                                            for (int i = 1; i <= 2; ++i) {
                                                int mn = min({res[ind[0]][i], res[ind[1]][i], res[ind[2]][i],
                                                              res[ind[3]][i]}) - 1;
                                                res[ind[0]][i] -= mn, res[ind[1]][i] -= mn, res[ind[2]][i] -= mn, res[ind[3]][i] -= mn;
                                            }

                                            vector<string> mat(18, string(18, '.'));
                                            for (int i = 0; i < 4; ++i) {
                                                int x = res[i][1];
                                                int y = res[i][2];
                                                int pos = 0;
                                                while (pos < sz(s[i])) {
                                                    mat[x - 1][y - 1] = s[i][pos];
                                                    if (res[i][0] == 1) {
                                                        ++y;
                                                    } else {
                                                        ++x;
                                                    }
                                                    ++pos;
                                                }
                                            }
                                            cout << "Yes\n";
                                            for (int i = 0; i < 18; ++i) {
                                                cout << mat[i] << "\n";
                                            }

                                            return;
                                        }
                                    }
                                    p0_next++, p1_next++;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (next_permutation(s.begin(), s.end()));

    cout << "No\n";
}


signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
