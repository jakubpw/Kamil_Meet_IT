#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

const int N = 1e3+5;
const int INF = 1e9;

int n;

vector<pair<int, int>> g[N];
long long D[N];
bool cykle[N];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m, Q, s, a, b, c;
    while(cin >> n >> m >> Q >> s){
        if(n==0 and m == 0 and Q == 0 and s == 0) return 0;
        for(int i = 0; i<N; i++){ D[i] = INF; cykle[i] = false;}
        for(int i = 0; i<N; i++){
            g[i].clear();
        }
        for(int i = 0; i<m; i++){
            cin >> a >> b >> c;
            g[a].push_back({b, c});
        }
        D[s] = 0;
        for(int i = 0; i<n-1; i++){
            for(int j = 0; j<n; j++){
                if(D[j]==INF) continue;
                for(pair e : g[j]){
                    int to = e.fi;
                    int waga = e.se;
                    D[to] = min(D[j] + waga, D[to]);
                }
            }
        }

        queue<int> q;

        for(int i = 0; i<n; i++){
            for(pair e : g[i]){
                int to = e.fi;
                int waga = e.se;
                if(D[i]+waga < D[to]) q.push(to);
            }
        }

        while(!q.empty()){
            int v = q.front();
            q.pop();
            cykle[v] = true;
            for(pair e : g[v]){
                int to = e.fi;
                if(cykle[to]) continue;
                q.push(to);
            }
        }

        for(int i = 0; i<Q; i++){
            cin >> a;
            if(D[a]==INF) cout << "Impossible\n";
            else if(cykle[a]) cout << "-Infinity\n";
            else cout << D[a] << '\n';
        }
        cout << '\n';
    }
    return 0;
}