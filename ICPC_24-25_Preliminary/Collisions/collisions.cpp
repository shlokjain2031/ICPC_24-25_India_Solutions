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
    ll n;
    cin >> n;
    vector<ll> c(n+1);
    vector<vector<ll>> cols(n+1);
    for (ll i = 1; i <= n; i++) cin >> c[i];
    for (ll i = 1; i <= n; i++) {
        cols[i].resize(c[i]);
        for (ll j = 0; j < c[i]; j++) cin >> cols[i][j];
        sort(cols[i].begin(), cols[i].end());
    }

    // Most important insight being that columns are affected by two possible collisions
    // One where the balls will intersect while moving and one after landing so for each
    // column we calculate that starting from bottom to top and increasing based on
    // the different cases
    vector<ll> step_1(n+1, 0), step_2(n+1, 0);
    for (ll i = 1; i < n; i++) {
        vector<ll> a = cols[i];
        vector<ll> b = cols[i+1];
        ll p = 0;
        ll q = 0;
        ll cnt = 0;
        while (p < a.size() && q < b.size()) {
            if (a[p] == b[q]) {
                ++cnt;
                ++p;
                ++q;
            }
            else if (a[p] < b[q]) ++p;
            else ++q;
        }
        step_1[i] = cnt;
    }
    for (ll i = 1; i + 2 <= n; i++) {
        vector<ll> a = cols[i];
        vector<ll> c = cols[i+2];
        ll p = 0, q = 0; ll cnt = 0;
        while (p < a.size() && q < c.size()) {
            if (a[p] == c[q]) {
                ++cnt;
                ++p;
                ++q;
            }
            else if (a[p] < c[q]) ++p;
            else ++q;
        }
        step_2[i] = cnt;
    }

    // Establish 0/1 DP which decides dp[ith position column we are at][(i-2)th direction][(i-1) direction] = number of collisions occured so far till ith pos
    // The transition is basically for the (i+1)th pos so b replaces a since we moved a step ahead and the curr direction becomes the last pos
    // It checks if setting the direction makes sense or not by adding the possible step_1 and step_2 collisions
    vector<vector<vector<ll>>> dp(n+1, vector<vector<ll>>(2, vector<ll>(2, INF)));

    dp[2][1][0] = step_1[1];
    dp[2][1][1] = 0;

    for (ll i = 2; i < n; i++) {
        for (ll a = 0; a < 2; a++) {
            for (ll b = 0; b < 2; b++) {
                if (dp[i][a][b] == INF) continue;
                for (ll cdir = 0; cdir < 2; cdir++) {
                    ll add = 0;
                    if (b == 1 && cdir == 0) add += step_1[i];
                    if (a == 1 && cdir == 0) add += step_2[i-1];
                    dp[i+1][b][cdir] = min(dp[i+1][b][cdir], dp[i][a][b] + add);
                }
            }
        }
    }

    // Since we know that the last column only moves left, we just need to account for the second last column moving left or right
    cout << min(dp[n][0][0], dp[n][1][0]) << "\n";

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
