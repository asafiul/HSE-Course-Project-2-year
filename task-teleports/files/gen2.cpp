#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

vector<int> RandSet(int n, int k) {
    auto res = rnd.distinct(k, n);
    sort(res.begin(), res.end());
    return res;
}

vector<int> Divide(int n, int k) {
    if (k == 0) {
        return {};
    }
    if (k == 1) {
        return {n};
    }
    vector<int> pos = RandSet(n - 1, k - 1);
    vector<int> len;
    len.reserve(k);
    len.emplace_back(pos[0] + 1);
    for (int i = 0; i < k - 2; i++) {
        len.emplace_back(pos[i + 1] - pos[i]);
    }
    len.emplace_back(n - pos.back() - 1);
    return len;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int maxt = opt<int>("maxt", 100'000);
    int maxs = opt<int>("maxs", 100'000);
    int maxm = opt<int>("maxm", 100'000);
    int n = opt<int>("n");

    if (opt<bool>("f")) {
        maxm = 150000;
        maxs = 150000;
        maxt = 1'000'000'000;
    }

    int vmode = opt<int>("vmode");
    // 1 --> random
    // 2 --> random distinct
    // 3 --> random increasing
    // 4 --> random decreasing
    // 5 --> random permutation x const
    // 6 --> small number of different elements
    // 7 --> equal (random if not given)

    vector<int> v(n);
    if (vmode == 1) {
        for (int i = 0; i < n; i++) {
            v[i] = rnd.next(1, maxt);
        }
    } else if (vmode == 2) {
        v = rnd.distinct(n, 1, maxt);
    } else if (vmode == 3) {
        if (maxt >= n) {
            v = rnd.distinct(n, 1, maxt);
        } else {
            for (int i = 0; i < n; i++) {
                v[i] = rnd.next(1, maxt);
            }
        }
        sort(v.begin(), v.end());
    } else if (vmode == 4) {
        if (maxt >= n) {
            v = rnd.distinct(n, 1, maxt);
        } else {
            for (int i = 0; i < n; i++) {
                v[i] = rnd.next(1, maxt);
            }
        }
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());
    } else if (vmode == 5) {
        auto perm = rnd.perm(n);
        for (int& i : perm) i++;
        int mx = maxt / n;
        for (int& i : perm) i *= mx;
        v = perm;
    } else if (vmode == 6) {
        int sz = rnd.next(1, (int)sqrt(n));
        vector<int> elems = rnd.distinct(sz, 1, maxt);
        for (int i = 0; i < n; i++) {
            v[i] = rnd.any(elems);
        }
    } else if (vmode == 7) {
        int elem = rnd.next(1, maxt);
        if (has_opt("v1")) {
            elem = opt<int>("v1");
        }
        for (int i = 0; i < n; i++) {
            v[i] = elem;
        }
    }

    vector<int> s;

    int smode = opt<int>("smode");
    // 0 -> equal, s1 is given
    // 1 -> 1 2 3 4 ...
    // 2 -> k, k + 1, k + 2, ..., 2k
    // 3 -> 1 2 3 4 ... (sum = n/2 + filled with random)
    // 4 -> random division, the number of pieces is given
    // 5 -> random increasing/decreasing division, the number of pieces is maxm
    // 6 -> 1 2 3 4 ... (sum = n/2 + n/4 + filled with random)
    // 7 -> 1, maxs-1

    int left = 0;
    if (smode == 0) {
        int s1 = opt<int>("s1");
        maxm = min(maxm, (maxs / s1));
        for (int i = 0; i < maxm; i++) s.emplace_back(s1);
    } else if (smode == 1) {
        for (int k = 1; maxs >= k; k++) {
            s.emplace_back(k);
            maxs -= k;
        }
        left = maxs;
    } else if (smode == 2) {
        int start = 0;
        for (int x = 1; ; x++) {
            int sm = (x + 1) * (3 * x) / 2;
            if (sm <= maxs) {
                start = x;
            } else {
                break;
            }
        }
        left = maxs;
        for (int k = start; k <= 2 * start; k++) {
            s.emplace_back(k);
            left -= k;
        }
    } else if (smode == 3) {
        int x = (maxs / 2);
        for (int k = 1; x >= k; k++) {
            s.emplace_back(k);
            x -= k;
        }
        left = x + (maxs + 1) / 2;
    } else if (smode == 4) {
        int cnt = opt<int>("cnt", maxm);
        s = Divide(maxs, cnt);
    } else if (smode == 5) {
        for (int i = 1; i <= maxm; i++) {
            s.emplace_back(i);
            maxs -= i;
        }
        while (maxs > 0) {
            int pos = rnd.next(1, min(maxs, (int)s.size()));
            for (int i = (int)s.size() - pos; i < (int)s.size(); i++) {
                s[i]++;
                maxs--;
            }
        }
        if (opt<bool>("dec")) {
            reverse(s.begin(), s.end());
        }
    } else if (smode == 6) {
        int x = (maxs / 2);
        for (int k = 1; x >= k; k++) {
            s.emplace_back(k);
            x -= k;
        }
        left = x + (maxs + 1) / 2;
        s.emplace_back(left / 2);
        left -= left / 2;
    } else if (smode == 7) {
        s.emplace_back(1);
        s.emplace_back(maxs - 1);
    }

    if (left > 0) {
        auto mx = *max_element(s.begin(), s.end());
        auto dv = Divide(left, left / 2);

        left = 0;
        for (int& i : dv) {
            if (i > mx) {
                left += i - mx;
                i = mx;
            }
        }

        while (left > 0) {
            int x = rnd.next(1, min(left, mx));
            dv.emplace_back(x);
            left -= x;
        }

        shuffle(dv.begin(), dv.end());

        vector<pair<int, int>> loc;
        loc.emplace_back(s[0], 0);
        for (int i = 1; i < (int)s.size(); i++) {
            if (s[i] > loc.back().first) {
                loc.emplace_back(s[i], i);
            }
        }

        vector<vector<int>> after(s.size());
        for (int i : dv) {
            auto pos = lower_bound(loc.begin(), loc.end(), make_pair(i, -1))->second;
            after[rnd.next(pos, (int)s.size() - 1)].emplace_back(i);
        }

        vector<int> new_s;
        for (int i = 0; i < (int)s.size(); i++) {
            new_s.emplace_back(s[i]);
            for (int j : after[i]) {
                new_s.emplace_back(j);
            }
        }

        swap(s, new_s);
    }

#ifdef SHOW_DEBUG
    int mx = 0;
    for (int i : s) {
        if (i > mx) {
            cerr << i << "\n";
            mx = i;
        }
    }
#endif

    for (int i = 1; i < s.size(); i++) {
        s[i] += s[i - 1];
    }

    println(v.size(), s.size());
    println(v);
    println(s);

    return 0;
}
