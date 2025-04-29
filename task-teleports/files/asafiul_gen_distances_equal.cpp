#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int maxm = 200'000;
const int maxvi = 200'000;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int test_left = opt<int>("tl");
    int test_right = opt<int>("tr");

    int n_left = opt<int>("nl");
    int n_right = opt<int>("nr");

    int s_0_left = opt<int>("s0l");
    int s_0_right = opt<int>("s0r");

    int v_right = opt<int>("vr");

    for (int test = test_left; test <= test_right; ++test) {
        startTest(test);

        int n = rnd.next(n_left, n_right);
        int s_0 = rnd.next(s_0_left, s_0_right);
        int m = maxm / s_0;

        cout << n << " " << m << "\n";

        for (int i = 0; i < n; ++i) {
            cout << rnd.next(1, v_right);
            if (i + 1 < n)
                cout << " ";
            else
                cout << "\n";
        }

        for (int i = 0; i < m; ++i) {
            cout << s_0 * (i + 1);
            if (i + 1 < m)
                cout << " ";
            else
                cout << "\n";
        }
    }

    return 0;
}
