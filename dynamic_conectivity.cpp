#include <bits/stdc++.h>
    
using namespace std;
    
#define fi first
#define se second
#define ff fi.fi
#define ss se.se
#define fs fi.se
    
const int N = 3e5+5;
    
struct edge{
    int a, b, l, r;
};
    
typedef vector<edge> edges;
    
//WYNIK
int cnt[N], ans[N];
    
//DFS
vector<int> g[N];
int kolor[N], deg[N], vis[N];
    
void reset(int n){
    for(int i = 0; i<n; i++){
        g[i].clear();
        vis[i] = 0;
    }
}
    
void dfs(int a, int color){
    vis[a] = 1;
    kolor[a] = color;
    for(int b : g[a]){
        if(!vis[b]){
            dfs(b, color);
        }
    }
}
    
void dnd(int l, int r, edges &v, int mx, int rs){
    if(cnt[l] == cnt[r]) return;
    
    //PUSTA
    if(!v.size()){
        while(l<r) ans[l++] = mx + rs;
        return;
    }
    
    reset(mx);
    edges v1;
    
    //GRAF
    for(int i = 0; i<v.size(); i++){
        if(v[i].l <= l and r <= v[i].r){ //CAŁE
            g[v[i].a].push_back(v[i].b);
            g[v[i].b].push_back(v[i].a);
        }
        else if(l < v[i].r and v[i].l < r) v1.push_back(v[i]); //CZĘŚĆ
    }
    
    //SS
    int color = 0;
    for(int i = 0; i<mx; i++){
        if(!vis[i]){
            deg[color] = 0;
            dfs(i, color++);
        }
    }
    
    //PRZENUMEROWANIE 1
    for(int i = 0; i<v1.size(); i++){
        v1[i].a = kolor[v1[i].a];
        v1[i].b = kolor[v1[i].b];
        if(v1[i].a != v1[i].b) deg[v1[i].a]++, deg[v1[i].b]++;
    }
    
    //ILOŚĆ WIERZCHOŁKÓW + RESZTA
    mx = color; color = 0;
    for(int i = 0; i<mx; i++){
        vis[i] = color;
        if(deg[i]>0) color++;
        if(deg[i]==0) rs++;
    }
    
    //PRZENUMEROWANIE 2
    for(int i = 0; i<v1.size(); i++){
        v1[i].a = vis[v1[i].a];
        v1[i].b = vis[v1[i].b];
    }
    
    int mid = (l+r)/2;
    dnd(l, mid, v1, color, rs);
    dnd(mid, r, v1, color, rs);
}
    
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    #define NAME "connect"
    assert(freopen(NAME ".in", "r", stdin));
    assert(freopen(NAME ".out", "w", stdout));
    
    map<pair<int, int>, int> m;
    
    edges v;
    
    int n, k, a, b;
    char q;
    
    cin >> n >> k;
    
    for(int i = 0; i<k; i++){
        cin >> q;
        if(q == '-' or q == '+'){
            cin >> a >> b;
            a--; b--;
            if(a>b) swap(a, b);
            if(q == '+') m[{a, b}] = i;
            else{
                int j = m[{a, b}];
                v.push_back({a, b, j, i});
                m[{a, b}] = -1;
            }
        }
        else cnt[i + 1]++;
        cnt[i + 1] += cnt[i];
    }
    
    for(auto j : m){
        if(j.se!=-1){
            v.push_back({j.ff, j.fs, j.se, k});
        }
    }
    
    //for(auto e : v) cout << e.a << " " << e.b << " " << e.l << " " << e.r << '\n';
    
    dnd(0, k, v, n, 0);
    
    for(int i = 0; i<k; i++){
        if(cnt[i + 1] != cnt[i]) cout << ans[i] << '\n';
    }
    
    return 0;
}