#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

//const int maxm = 200'000;
const int maxs = 200'000;
const int maxvi = 200'000;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int test_left = opt<int>("tl");
    int test_right = opt<int>("tr");

    int n_left = opt<int>("nl");
    int n_right = opt<int>("nr");

    int v_right = opt<int>("vr");

    int inc = opt<bool>("inc");

    for (int test = test_left; test <= test_right; ++test) {
        startTest(test);

        int n = rnd.next(n_left, n_right);
        int m = 2;

        cout << n << " " << m << "\n";

        for (int i = 0; i < n; ++i) {
            cout << rnd.next(1, v_right);
            if (i + 1 < n)
                cout << " ";
            else
                cout << "\n";
        }

        int s0, s1;
        if (inc) {
            s0 = rnd.next(1, (maxs - 1) / 2);
            s1 = 2 * s0 + rnd.next(1, maxs - 2 * s0);
        } else {
            s0 = rnd.next(1, maxs);
            s1 = s0 + rnd.next(1, min(maxs - s0, s0));
        }
        cout << s0 << " " << s1 << "\n";
    }

    return 0;
}
