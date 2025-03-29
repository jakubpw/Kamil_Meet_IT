#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
//dp[indeks][podzielność][suma] - ile jest liczb o długości D, podzielnych przez M, o sumie S
ll dp[210][210][210] = {0};
ll p[210] = {0};

const int S = 200;
const ll M = 1e18;

int s, m, q;

void preprocess(){
    p[0] = dp[0][0][0] = 1;
    for(int i = 1; i<=S; i++) p[i] = (p[i-1]*10)%m;

    for(int i = 0; i<=S; i++){
        for(int j = 0; j<=s; j++){
            for(int mod = 0; mod<m; mod++){
                for(int d = 0; d<=9; d++){
                    int new_mod = (mod+d*p[i])%m;
                    dp[i+1][new_mod][j+d] += dp[i][mod][j];
                    dp[i+1][new_mod][j+d] = min(dp[i+1][new_mod][j+d], M);
                }
            }
        }
    }
}

void query(ll k){
    
    if(dp[S][0][s]<k){
        cout << "NIE\n";
        return;
    }
    string res;

    int mod = 0;
    int suma = s;

    for(int i = S; i>0; i--){
        for(int d = 0; d<=9; d++){
            int new_mod = ((mod-d*p[i-1])%m + m)%m;
            if(dp[i-1][new_mod][suma-d]<k){
                k-=dp[i-1][new_mod][suma-d];
            }
            else{
                res += '0'+ d;
                suma -= d;
                mod = new_mod;
                break;
            }
        }
    }
    while(res[0]=='0'){
        res.erase(res.begin());
    }
    if(res.empty()){
        cout << 0 << '\n';
        return;
    }
    cout << res << '\n';
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll k;
    cin >> s >> m >> q;
    preprocess();
    while(q--){
        cin >> k;
        query(k);
    }
    return 0;
}
// 1 ≤ s ≤ 200, 1 ≤ m ≤ 200, 1 ≤ q ≤ 10 000, 1 ≤ k ≤ 10^18.