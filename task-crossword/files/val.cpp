#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    vector<string> s(4);
    for (int i = 0; i < 4; ++i) {
        s[i] = inf.readToken("[a-z]{2,10}", to_string(i + 1) + " word");

        for (int j = 0; j < i; ++j) {
            ensuref(s[i] != s[j], "Found same words in input : %s and %s", s[i].data(), s[j].data());
        }
        inf.readEoln();
    }
    inf.readEof();
}
