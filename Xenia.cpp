#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

const int N = 1e5+5;
const int inf = 1e9;

vector<int> g[N];
int siz[N];
int dist[N];
bool wyrzucone[N];
vector<pair<int, int>> anc[N];

int dfs_siz(int u, int p){
    siz[u] = 1;
    for(int v : g[u]){
        if(v==p or wyrzucone[v])continue;
        siz[u] += dfs_siz(v, u);
    }
    return siz[u];
}

int find_centroid(int x, int rozmiar, int par){
    for(int y : g[x]){
        if(y==par or wyrzucone[y]) continue;
        if(siz[y]*2>rozmiar){
            return find_centroid(y, rozmiar, x);
        }
    }
    return x;
}

void dystans(int x, int centroid, int par, int cdist){
    for(int y : g[x]){
        if(y==par or wyrzucone[y]) continue;
        cdist++;
        dystans(y, centroid, x, cdist);
        cdist--;
    }
    anc[x].push_back({centroid, cdist});
}

void dekompozycja(int x){
    int centroid = find_centroid(x, dfs_siz(x, -1), -1);
    for(int s : g[centroid]){
        if(wyrzucone[s])continue;
        dystans(s, centroid, centroid, 1);
    }
    wyrzucone[centroid] = true;
    for(int s : g[centroid]){
        if(wyrzucone[s])continue;
        dekompozycja(s);
    }
}

void paint(int x){
    for(pair e : anc[x]){
        int to = e.fi;
        int d = e.se;
        dist[to] = min(dist[to], d);
    }
    dist[x] = 0;
}

void query(int x){
    int ans = dist[x];
    for(pair e : anc[x]){
        int to = e.fi;
        int d = e.se;
        if(d==0)continue;
        ans = min(ans, d + dist[to]);
    }
    cout << ans << '\n';
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q, t, a, b;
    cin >> n >> q;
    for(int i = 0 ; i<n-1; i++){
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dekompozycja(1);
    for(int i = 0; i<N; i++) dist[i] = inf;
    paint(1);
    while(q--){
        cin >> t >> a;
        if(t==1) paint(a);
        else query(a);
    }
    return 0;
}