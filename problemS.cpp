#include <bits/stdc++.h>

using namespace std;

const int N = 1e4+5;
const int mod = 1e9+7;

int dp[N][105][2] = {0};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int d;
    string k;
    cin >> k;
    cin >> d;
    int n = k.length();
    dp[n][0][0] = dp[n][0][1] = 1;
    for(int i = n-1; i>=0; i--){
        int pk = k[i]-'0';
        for(int p = 0; p<d; p++){
            for(int di = 0; di<=9; di++){
                int m = ((p-di)%d + d)%d;
                dp[i][p][0] += dp[i+1][m][0];
                dp[i][p][0] %=mod;
                if(di<pk){
                    dp[i][p][1] += dp[i+1][m][0];
                    dp[i][p][1]%=mod;
                } 
                else if(di==pk){
                    dp[i][p][1] += dp[i+1][m][1];
                    dp[i][p][1]%=mod;
                }
            }
        }
    }
    cout << (dp[0][0][1] - 1 + mod)%mod;
    return 0;
}