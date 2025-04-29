#include <bits/stdc++.h>

using namespace std;
int main(){
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        a[i] = {l, r};
    }
    sort(a.begin(), a.end());
    vector<int> dist(n-1);
    for (int i = 1; i < n; ++i) {
        dist[i-1] = a[i].first - a[i-1].second;
    }
    sort(dist.begin(), dist.end(), greater<>());
    while(!dist.empty() && k >= dist.back()){
        k-=dist.back();
        dist.pop_back();
        n--;
    }
    cout << n << endl;
}
