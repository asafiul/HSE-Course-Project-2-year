#include <bits/stdc++.h>
#include "testlib.h"


using namespace std;

#define szof(x) ((int)x.size())


//const int maxm = 200'000;
const int maxs = 200'000;
const int maxvi = 200'000;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int test_left = opt<int>("tl");
    int test_right = opt<int>("tr");

    int n_left = opt<int>("nl");
    int n_right = opt<int>("nr");

    int m_left = opt<int>("ml");
    int m_right = opt<int>("mr");

    int v_right = opt<int>("vr");

    int s_right = opt<int>("sr");


    for (int test = test_left; test <= test_right; ++test) {
        startTest(test);

        int n = rnd.next(n_left, n_right);
        int m = rnd.next(m_left, m_right);

        cout << n << " " << m << "\n";

        for (int i = 0; i < n; ++i) {
            int vi = rnd.next(1, v_right);
            cout << vi;
            if (i + 1 < n)
                cout << " ";
            else
                cout << "\n";
        }

        vector<int> p = rnd.perm(s_right, 1);
        p.resize(m);
        sort(p.begin(), p.end());

        println(p);
    }

    return 0;
}
