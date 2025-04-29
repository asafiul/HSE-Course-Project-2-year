#include "bits/stdc++.h"
#include "testlib.h"
 
using namespace std;
 
#define sz(a) (int)a.size()
 
const int m = 18;

const std::string YES = "yes";
const std::string NO = "no";
 
inline bool isLetter(char c) {
    return 'a' <= c && c <= 'z';
}
 
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    auto s = inf.readTokens(4);
    sort(s.begin(), s.end());

    auto readAns = [&](InStream& str) {
        std::string result = lowerCase(str.readToken("[a-zA-Z]{2,3}", "ans"));
        if (result != YES && result != NO) {
            str.quitf(_wa, "Unexpected token %s", result.c_str());
        }
     
        if (result == NO) {
            return false;
        }
     
        int sum = 0;
        for (auto &x: s) {
            sum += sz(x);
        }
     
        vector<string> mat(m);
        vector<pair<int, int>> letters;
        string fmt = string("[a-z.]{") + to_string(m) + string("}");
        mat = str.readTokens(m, fmt.c_str(), "ans matrix");
     
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                if (isLetter(mat[i][j])) {
                    letters.emplace_back(i, j);
                }
            }
        }
        str.quitif(sz(letters) != sum - 4, _wa, "the number of letters does not match, expected %d, found %d", sum - 4,
               sz(letters));
     
        for (auto [row1, col1]: letters) {
            for (auto [row2, col2]: letters) {
                if (row1 >= row2 || col1 >= col2) {
                    continue;
                }
                bool ok = true;
                for (int i = col1; i <= col2; ++i) if (!isLetter(mat[row1][i])) ok = false;
                for (int i = col1; i <= col2; ++i) if (!isLetter(mat[row2][i])) ok = false;
                for (int i = row1; i <= row2; ++i) if (!isLetter(mat[i][col1])) ok = false;
                for (int i = row1; i <= row2; ++i) if (!isLetter(mat[i][col2])) ok = false;
     
                if (!ok) {
                    continue;
                }
                vector<string> found_strings;
                {
                    //h1
                    int pos = col1;
                    while (pos >= 0 && isLetter(mat[row1][pos])) --pos;
                    ++pos;
                    string t;
                    while (pos < m && isLetter(mat[row1][pos])) {
                        t.push_back(mat[row1][pos++]);
                    }
                    found_strings.push_back(t);
                }
     
                {
                    //h2
                    int pos = col1;
                    while (pos >= 0 && isLetter(mat[row2][pos])) --pos;
                    ++pos;
                    string t;
                    while (pos < m && isLetter(mat[row2][pos])) {
                        t.push_back(mat[row2][pos++]);
                    }
                    found_strings.push_back(t);
                }
     
                {
                    //v1
                    int pos = row1;
                    while (pos >= 0 && isLetter(mat[pos][col1])) --pos;
                    ++pos;
                    string t;
                    while (pos < m && isLetter(mat[pos][col1])) {
                        t.push_back(mat[pos++][col1]);
                    }
                    found_strings.push_back(t);
                }
     
                {
                    //v2
                    int pos = row1;
                    while (pos >= 0 && isLetter(mat[pos][col2])) --pos;
                    ++pos;
                    string t;
                    while (pos < m && isLetter(mat[pos][col2])) {
                        t.push_back(mat[pos++][col2]);
                    }
                    found_strings.push_back(t);
                }
     
                sort(found_strings.begin(), found_strings.end());
                if (found_strings == s) {
                    return true;
                }
            }
        }
     
        str.quitf(_wa, "wrong crossword");
    };
    auto ans_jury = readAns(ans);
    auto ans_part = readAns(ouf);
    if (ans_jury == ans_part) {
        quitf(_ok, "ok, %s", (ans_jury ? "yes" : "no"));
    }
    if (ans_jury) {
        quitf(_wa, "jury found answer but participant didn't");
    }
    quitf(_fail, "participant found answer but jury didn't");
}
