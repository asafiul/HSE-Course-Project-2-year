#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define ll long long

/*
 * Params: alphabet (quantity),
 *
 * mode:
 * 1) random
 * 2) answer is -1
 *
 * */

struct Test {
    void print() {
    }
};

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    int alph = opt<int>("alph", 26);
    int mode = opt<int>("mode", 1);

    vector<int> d(4);
    d[0] = opt<int>("s1", 10);
    d[1] = opt<int>("s2", 10);
    d[2] = opt<int>("s3", 10);
    d[3] = opt<int>("s4", 10);

    string A = "abcdefghijklmnopqrstuvwxyz";

    shuffle(A.begin(), A.end());
    A.resize(alph);

    if (mode == 1) {
        while (true) {
            vector<string> s(4);
            for (int i = 0; i < 4; ++i) {
                s[i].assign(d[i], A[0]);
                for (int j = 0; j < d[i]; ++j) {
                    s[i][j] = A[rnd.next(0, alph - 1)];
                }
            }

            vector<string> t = s;
            sort(t.begin(), t.end());

            bool found = false;
            for (int i = 0; i < 3; ++i) {
                if (t[i] == t[i + 1]) {
                    found = true;
                }
            }
            if (found) {
                continue;
            }
            
            for (auto x: s) {
                cout << x << "\n";
            }
            break;
        }
    }

    return 0;
}
