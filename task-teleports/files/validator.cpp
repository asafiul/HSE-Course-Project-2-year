#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int kMaxN = 150'000;
const int kMaxM = 150'000;
const int kMaxS = 150'000;
const int kMaxvi = 1'000'000'000;
const int kN[14] = {kMaxN, 2, 50, 1000, 100'000, 100'000, 100, 100'000, 100'000,
                    10'000, 50'000, 100'000, 100'000, kMaxN};
const int kM[14] = {kMaxM, 50, 50, 5, 100'000, 100'000, 100'000, 100'000, 2,
                    100'000, 100'000, 100'000, kMaxM, kMaxM};

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    const int group = validator.group().empty() ? 0 : atoi(validator.group().c_str());

    int maxn = kN[group];
    int maxm = kM[group];

    int n = inf.readInt(2, maxn, "n");
    inf.readSpace();
    int m = inf.readInt(1, maxm, "m");
    inf.readEoln();

    int maxt = kMaxvi;
    if (group <= 11) {
        maxt = 100'000;
    }
    if (group == 7) {
        maxt = 2;
    }

    int maxs = kMaxS;
    if (group <= 11) {
        maxs = 100'000;
    }

    auto t = inf.readIntegers(n, 1, maxt, "t");
    inf.readEoln();

    auto s = inf.readIntegers(m, 1, maxs, "s");
    inf.readEoln();

    for (int i = 0; i + 1 < m; i++) {
        ensuref(s[i] < s[i + 1], "s should be increasing");
    }

    if (group == 4) {
        for (int i = 0; i + 1 < m; i++) {
            ensuref(s[i + 1] - s[i] == s[0], "s[i+1]-s[i]!=s[0]");
        }
    }
    if (group == 5) {
        for (int i = 0; i < n; i++) {
            ensuref(t[i] == t[0], "t_i should be equal");
        }
    }
    if (group == 8) {
        ensuref(m == 2, "m!=2");
    }

    inf.readEof();
    return 0;
}
