#include "testlib.h"
#include <bits/stdc++.h>


using namespace std;

#define szof(x) ((int)x.size())

#define ll long long
const ll maxn = 150'000;
const ll maxm = 150'000;
const ll kMaxS = 150'000;
const ll maxv = 1'000'000'000;

ll maxs = kMaxS;

map <string, string> params;

long long get(string name, long long def = 0) {
    if (params.count(name)) {
        return stoll(params[name]);
    } else {
        return def;
    }
}

double get_double(string name, long long def = 0) {
    if (params.count(name)) {
        return stod(params[name]);
    } else {
        return def;
    }
}

vector<int> v;

void gen_v(int n) {
    int vmode = get("vmode");

    if (vmode == 1) { // vi equal
        int vi = get("vi", -1);
        for (int i = 0; i < n; ++i)
            v.push_back(vi);
    }
    if (vmode == 2) { // vi increasing
        for (int i = 1; i <= n; ++i)
            v.push_back(i);
    }
    if (vmode == 3) { // vi decreasing
        for (int i = n; i >= 1; --i)
            v.push_back(i);
    }
    if (vmode == 4) { // vi random <= vr
        int vr = get("vr", maxv);
        for (int i = 0; i < n; ++i)
            v.push_back(rnd.next(1, vr));
    }
    if (vmode == 5) {
        v = rnd.perm(n, 1);
    }

}

vector<int> s;

void fill(vector<int> &seq, int fill_r, long long sum, int m = -1) {
    vector <vector<int>> add_between(szof(seq));
    int cnt_s = szof(seq);
    while (sum < maxs && cnt_s < m) {
        int ind = rnd.next(0, szof(add_between) - 1);
        int xr = min((int) (maxs - sum), min(fill_r, seq[ind]));
        int x = rnd.next(1, xr);
        add_between[ind].push_back(x);
        cnt_s++;
        sum += x;
    }

    int cur = 0;
    for (int i = 0; i < szof(seq); ++i) {
        cur += seq[i];
        s.push_back(cur);
        for (auto x: add_between[i]) {
            cur += x;
            s.push_back(cur);
        }
    }
}

void gen_s(int &m) {
    int smode = get("smode");

    maxs = get("maxs", kMaxS);

    if (smode == 1) { // distances equal
        int s1 = get("s1", -1);
        m = min(m, (int) maxs / s1);
        for (int i = 0; i < m; ++i)
            s.push_back(s1 * (i + 1));
    }
    if (smode == 2) { // arithmetic seq straight to sr_seq, then fill <= min(segment,fill_r)
        int s1 = get("s1", 1);
        int step = get("step", 1);
        int sr_seq = get("sr_seq", maxs);
        int fill_r = get("fill_r", 1);
        int seq_times = get("seq_times", 1);
        vector<int> seq;
        ll sum = 0;
        while (sum + s1 <= sr_seq && szof(seq) < m) {
            int i = 0;
            while (szof(seq) < m && sum + s1 <= sr_seq && i < seq_times) {
                sum += s1;
                seq.push_back(s1);
                ++i;
            }
            s1 += step;
        }
        fill(seq, fill_r, sum, m);
    }
    if (smode == 3) { // geometric seq straight to sr_seq, then fill <= min(segment,fill_r)
        ll s1 = get("s1", 1);
        double step = get_double("step", -1);
        ll sr_seq = get("sr_seq", maxs);
        int fill_r = get("fill_r", 1);
        int seq_times = get("seq_times", 1);
        vector<int> seq;
        ll sum = 0;
        while (sum + s1 <= sr_seq && szof(seq) < m) {
            int i = 0;
            while (sum + s1 <= sr_seq && szof(seq) < m && i < seq_times) {
                sum += s1;
                seq.push_back(s1);
                ++i;
            }
            s1 = max((long long) (s1 * step), s1 + 1);
        }
        fill(seq, fill_r, sum, m);
    }
    if (smode == 4) { //random seq , then fill <= min(segment,fill_r)
        int wtimes = get("wtimes", 0); //if min, must be < 0
        int fill_r = get("fill_r", 1);
        ll sr_seq = get("sr_seq", maxs);
        int seq_times = get("seq_times", 1);
        vector<int> seq;
        ll sum = 0;
        int prev = 0;
        while (szof(seq) < m && sum < sr_seq) {
            ll xl = prev + 1;
            ll xr = sr_seq - sum;
            if (xl > xr)
                break;
            ll x = rnd.wnext(xl, xr, wtimes);
            int i = 0;
            while (szof(seq) < m && sum + x <= sr_seq && i < seq_times) {
                seq.push_back(x);
                sum += x;
                ++i;
            }
            prev = x;
        }
        fill(seq, fill_r, sum, m);
    }
    if (smode == 5) { // random
        int sr = get("sr", maxs);
        s = rnd.perm(sr, 1);
        s.resize(m);
        sort(s.begin(), s.end());
    }
    if (smode == 6) { // m=2
        ll inc = get("sr", 1);
        ll s1 = rnd.next(1ll, maxs);
        ll s2 = maxs - s1;
        if (s1 > s2)
            swap(s1, s2);
        if (inc && s1 > s2)
            swap(s1, s2);
        s2 += s1;
        s.push_back(s1);
        s.push_back(s2);
    }

}

void build_test() {
    int n = get("n", maxn), m = get("m", maxm);

    gen_v(n);
    gen_s(m);
    s.resize(min((int) s.size(), m));
    m = (int) s.size();
    cout << n << " " << m << "\n";
    println(v);
    println(s);
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    for (int i = 1; i < argc; i++) {
        string s = string(argv[i]);
        if (s.find("=") != string::npos) {
            auto pos = s.find("=");
            params[s.substr(0, pos)] = s.substr(pos + 1);
        } else {
            params[s] = "";
        }
    }

    build_test();

    return 0;
}
