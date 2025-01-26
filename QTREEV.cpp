#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

const int N = 1e5+5;
const int inf = 1e9;

multiset<int> dist[N];
vector<pair<int, int>> anc[N];
vector<int> g[N];
bool wyrzucone[N];
bool painted[N] = {false};
int siz[N];

int dfs(int u, int p){
    siz[u] = 1;
    for(int v : g[u]){
        if(wyrzucone[v] or v==p) continue;
        siz[u] += dfs(v, u);
    }
    return siz[u];
}

int find_centroid(int x, int p, int rozmiar){
    for(int y : g[x]){
        if(wyrzucone[y] or y==p) continue;
        if(siz[y]*2>rozmiar){
            return find_centroid(y, x, rozmiar);
        }
    }
    return x;
}

void dystans(int x, int centroid, int p, int cdist){
    for(int y : g[x]){
        if(y==p or wyrzucone[y]) continue;
        cdist++;
        dystans(y, centroid, x, cdist);
        cdist--;
    }
    anc[x].push_back({centroid, cdist});
}

void decompose(int x){
    int centroid = find_centroid(x, -1, dfs(x, -1));
    wyrzucone[centroid] = true;
    for(int s : g[centroid]){
        if(wyrzucone[s]) continue;
        dystans(s, centroid, centroid, 1);
    }
    for(int s : g[centroid]){
        if(wyrzucone[s])continue;
        decompose(s);
    }
}

void color(int o){
    painted[o] = painted[o]^1; 
    if(painted[o])dist[o].insert(0);
    else dist[o].erase(0);
    for(auto u : anc[o]){
        int to = u.first;
        int d = u.second;
        if(painted[o])dist[to].insert(d);   
        else dist[to].erase(dist[to].find(d));
    }
}
    
void query(int o){
    if(painted[o]){cout << 0 << '\n'; return;}
    int ans = inf;
    if(dist[o].size()) ans = *dist[o].begin();
    for(auto u : anc[o]){
        int to = u.first;
        int d = u.second;
        if(dist[to].size()) ans = min(ans, d + *dist[to].begin());
    }
    if(ans==inf) cout << -1 << '\n';
    else cout << ans << '\n';
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q, a, b, t;
    cin >> n;
    for(int i = 0; i<n-1; i++){
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    decompose(1);
    cin >> q;
    while(q--){
        cin >> t >> a;
        if(t==0) color(a);
        else query(a);
    }
    return 0;
}