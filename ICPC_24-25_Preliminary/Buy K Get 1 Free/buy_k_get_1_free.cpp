    //
    // Created by Shlok Jain on 28/08/25.
    //
    #include <chrono>
    #include <iostream>
    #include <map>
    #include <random>
    #include <unordered_map>
    #include <vector>
    #include <iomanip>
    #include <cstring>
    #include <algorithm>
    #include <functional>
    #include <climits>
    #include <queue>
    #include <bitset>
    #include <cassert>
    #include <set>
    #include <stack>
    #include <unordered_set>
    #include <string.h>

    using namespace std;
    using namespace std::chrono;

    typedef long long ll;
    typedef long double lld;

    const ll N = 2*(1e6);
    vector<ll> is_prime(N, 1);

    struct DSU {
        vector<ll> p, sz;

        DSU(ll n = 0) {
            p.resize(n+1);
            sz.assign(n+1,1);
            for(ll i = 1; i <= n; i++) p[i] = i;
        }

        ll find(ll x) {
            return p[x] == x ? x : p[x] = find(p[x]);
        }

        bool uni(ll a, ll b) {
            a = find(a);
            b = find(b);

            if(a == b) return false;

            if(sz[a] < sz[b]) swap(a,b);
            p[b] = a;
            sz[a] += sz[b];

            return true;
        }
    };

    void sieve_of_eratosthenes() {
        is_prime[0] = is_prime[1] = false;
        for (ll i = 2; i * i <= N; i++) {
            if (is_prime[i]) {
                for (ll j = i * i; j <= N; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }

    ll derangements(ll n, ll m, ll k) {
        vector<ll> dp(n + 1);

        dp[1] = 0;
        dp[2] = 1;

        for (ll i = 3; i <= n; i++) {
            dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
        }

        return dp[n];
    }

    long long binpow(long long a, long long b, long long m) {
        a %= m;
        long long res = 1;
        while (b > 0) {
            if (b & 1)
                res = res * a % m;
            a = a * a % m;
            b >>= 1;
        }
        return res;
    }
ll INF = LLONG_MAX;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> c(n+1);
    for (ll i = 1; i <= n; ++i) cin >> c[i];
    sort(c.begin() + 1, c.end());

    vector<ll> pref(n+1, 0);
    for (ll i = 1; i <= n; ++i) pref[i] = pref[i-1] + c[i];

    vector<ll> free(n+1, 0);
    for (ll m = 1; m <= n; ++m) {
        if (m >= k + 1) {
            free[m] = free[m - (k + 1)] + c[m - k];
        }
        else {
            free[m] = 0;
        }
    }

    for (ll m = 1; m <= n; ++m) {
        cout << pref[m] - free[m] << " ";
    }
    cout << endl;

}

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        // sieve_of_eratosthenes();
        // //
        // freopen("moobuzz.in", "r", stdin);
        // freopen("moobuzz.out", "w", stdout);

        ll tc = 1;
        // cin >> tc;
        for (ll t = 0; t < tc; t++) solve();
    }
