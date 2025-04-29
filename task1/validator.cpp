#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 200'000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 1'000'000'000, "k");
    inf.readEoln();
    vector<pair<int, int>> t(n);
    for (int i = 0; i < n; ++i) {
        t[i].first = inf.readInt(0, 1'000'000'000, "l_" + to_string(i + 1));
        inf.readSpace();
        t[i].second = inf.readInt(t[i].first + 1, 1'000'000'000, "r_" + to_string(i + 1));
        inf.readEoln();
    }
    sort(t.begin(), t.end());
    for (size_t i = 0; i + 1 < t.size(); ++i) {
        ensure(t[i].second < t[i + 1].first);
    }
    inf.readEof();
}
