#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define ll long long

/*
 *  params: n,k
 *  optional params: maxRi, s, d, dec
 *  s - equal segments
 *  d - equal distances
 *  decrease - decreasing d
 *
 *  mode:
 *  1: random (default)
 *
 */

int n, k, maxR, mode, s, d, decrease;

struct Test {
    int n, k;
    vector<int> segments, distances;

    void print() {
        println(n, k);
        ensure((int) segments.size() == n && segments.size() == distances.size() + 1);
        int sum = accumulate(segments.begin(), segments.end(), 0) + accumulate(distances.begin(), distances.end(), 0);
        int cur = rnd.next(0, maxR - sum);
        
        vector<pair<int, int>> res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = {cur, cur + segments[i]};
            if (i + 1 < n) {
                cur += segments[i] + distances[i];
            }
        }
        
        shuffle(res.begin(), res.end());
        for (auto [l, r]: res) {
            println(l, r);
        }
    }
};

struct Node {
    int l = -1, r = -1, parent = -1;
};

Test test;

map<int, Node> mp;

int find(int v) {
    ensure(mp.contains(v) && mp[v].parent != -1);
    if (mp[v].parent == v) {
        return v;
    }
    return (mp[v].parent = find(mp[v].parent));
}

int merge_dsu(int u, int v) {
    assert(mp.contains(u) || mp.contains(v));
    if (!mp.contains(u)) {
        return v;
    }
    if (!mp.contains(v)) {
        return u;
    }
    
    u = find(u);
    v = find(v);
    mp[u].parent = v;
    mp[v].l = min(mp[v].l, mp[u].l);
    mp[v].r = max(mp[v].r, mp[u].r);
    return v;
}

void add_node(int v) {
    mp[v] = {v - 1, v + 1, v};
    int u = merge_dsu(v, v - 1);
    merge_dsu(u, v + 1);
}

void full_random() {
    ensure(d == 0 || s == 0);
    int R = maxR;
    R = R - 1 - (n - 1) * (d == 0 ? 1 : d) - n * (s == 0 ? 0 : s - 1);
    int last = R;

    for (int i = 0; i < n; ++i) {
        int v = rnd.next(0, last);
        if (!mp.contains(v)) {
            add_node(v);
        } else {
            v = find(v);
            int l = mp[v].l;
            int r = mp[v].r;
            ensure(l >= 0 || r <= last);

            add_node(l >= 0 ? l : r);
        }
    }

    int sum = 0;
    int prev = mp.begin()->first;
    for (auto it = ++mp.begin(); it != mp.end(); ++it) {
        sum += (s == 0 ? 0 : s - 1) + (d == 0 ? 1 : d);
        int curl = it->first + sum;
        
        if (s) {
            test.segments.push_back(s);
            test.distances.push_back(curl - prev - s);
        }
        
        if (d) {
            test.segments.push_back(curl - prev - d);
            test.distances.push_back(d);
        }
        
        if (!d && !s) {
            int seg = rnd.next(1, curl - prev - 1);
            test.segments.push_back(seg);
            test.distances.push_back(curl - prev - seg);
        }
        prev = curl;
    }
    
    if (s) {
        test.segments.push_back(s);
    } else {
        test.segments.push_back(rnd.next(1, maxR - prev));
    }
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    n = opt<int>("n");
    k = opt<int>("k");
    maxR = opt<int>("maxR", 1'000'000'000);
    mode = opt<int>("mode", 1);
    s = opt<int>("s", 0);
    d = opt<int>("d", 0);
    decrease = opt<int>("decrease", 0);

    test.n = n;
    test.k = k;

    ensure((ll) max(s, 1) * n + (ll) max(d, 1) * (n - 1) <= maxR);

    if (d && s) {
        for (int i = 0; i < n; ++i) {
            test.segments.push_back(s);
        }
        for (int i = 0; i + 1 < n; ++i) {
            test.distances.push_back(d);
        }
    } else {
        if (mode == 1) {
            full_random();
        }
    }

    shuffle(test.segments.begin(), test.segments.end());
    shuffle(test.distances.begin(), test.distances.end());

    if (decrease) {
        sort(test.distances.rbegin(), test.distances.rend());
    }

    test.print();

    return 0;
}
