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

    int m_right = opt<int>("mr");

    int v_right = opt<int>("vr");

    for (int test = test_left; test <= test_right; ++test) {
        startTest(test);

        int n = rnd.next(n_left, n_right);

        vector<int> v(n);
        for (int i = 0; i < n; ++i)
            v[i] = rnd.next(1, v_right);

        vector<int> d;
        int sum = 0;
        for (int i = 1; i + sum <= maxs && szof(d) + 1 <= m_right; ++i) {
            d.push_back(i);
            sum += i;
        }

        vector<int> cnt1(szof(d));
        while (szof(d) + 1 <= m_right && sum + 1 <= maxs) {
            int ind = rnd.next(0, szof(d) - 1);
            cnt1[ind]++;
            sum++;
        }

        int pnt = 0;
        vector<int> s;
        for (int i = 0; i < szof(d); ++i) {
            pnt += d[i];
            s.push_back(pnt);
            for (int j = 0; j < cnt1[i]; ++j) {
                pnt++;
                s.push_back(pnt);
            }
        }

        int m = szof(s);

        cout << n << " " << m << "\n";
        println(v);
        println(s);
    }

    return 0;
}
