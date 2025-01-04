#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const long long inf = 1e18;
long long d[202][202] = {0};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b, c;
    ll wynik = inf;
    cin >> n >> m;
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            if(i==j) continue;
            d[i][j] = inf;
        }
    }
    for(int i = 0; i<m; i++){
        cin >> a >> b >> c;
        d[a][b] = c;
    }
    for(int k = 1; k<=n; k++){
        for(int i = 1; i<=n; i++){
            for(int j = 1; j<=n; j++){
                d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
            }
        }
    }
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            if(i==j) continue;
            wynik = min(wynik, d[i][j]+d[j][i]);
        }
    }
    if(wynik==inf) cout << "NIE";
    else cout << wynik;
    return 0;
}