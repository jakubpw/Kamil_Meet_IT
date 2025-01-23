#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

const int N = 5e4+5;
const int M = 505;

int n, k;
long long ans = 0;

vector<pair<int, int>> anc[N];
vector<int> g[N];
int T[N];
int siz[N];
bool wyrzucone[N];

int dfs_siz(int u, int p){
    siz[u] = 1;
    for(int v : g[u]){
        if(v==p or wyrzucone[v]) continue;
        siz[u] += dfs_siz(v, u);
    }
    return siz[u];
}

void dfs_dist(int u, int p, int d, vector<int>& dist){
    if(d>k) return;
    ans += T[k-d];
    dist.push_back(d);
    for(int v : g[u]){
        if(v==p or wyrzucone[v]) continue;
        dfs_dist(v, u, d+1, dist);
    }
}

int find_centroid(int u, int p, int rozmiar){
    for(int v : g[u]){
        if(v==p or wyrzucone[v]) continue;
        if(siz[v]*2>rozmiar){
            return find_centroid(v, u, rozmiar);
        }
    }
    return u;
}

void dekompozycja(int u){
    int centroid = find_centroid(u, -1, dfs_siz(u, -1));
    T[0] = 1;
    for(int s : g[centroid]){
        if(wyrzucone[s]) continue;
        vector<int> dist;
        dfs_dist(s, centroid, 1, dist);
        for(int d : dist){
            T[d]++;
        }
    }
    wyrzucone[centroid] = true;
    for(int s : g[centroid]){
        if(wyrzucone[s])continue;
        for(int i = 0; i<N; i++) T[i] = 0;
        dekompozycja(s);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int a, b;
    cin >> n >> k;
    for(int i = 0; i<n-1; i++){
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dekompozycja(1);
    cout << ans;
}