    #include <bits/stdc++.h>

using namespace std;

const int N = 3e5+5;

int o = 1, timer = 1, k = 0, SCC = 0, gleb = 1;

vector<int> g[N];
vector<int> gdfs[N];
vector<int> gtr[N];
vector<int> gspoj[N];
vector<int> top;
int vis[N] = {0};
int tin[N] = {0};
int parent[N] = {0};
int GSCC[N] = {0};
int depth[N] = {0};

void dfs(int u, int p){
    vis[u] = o;
    tin[u] = timer++;
    parent[u] = p;
    for(int v : g[u]){
        if(v!=parent[u]){
            if(vis[v]==o){
                if(tin[u]<tin[v]){
                    gdfs[v].push_back(u);
                    gtr[u].push_back(v);
                }
            }
            else{
                gdfs[u].push_back(v);
                gtr[v].push_back(u);
                dfs(v, u);
            }
        }
    }
}

void dfs2(int u){
    vis[u] = o;
    for(int v : gdfs[u]){
        if(vis[v]!=o){
            dfs2(v);
        }
    }
    top.push_back(u);
}

void dfs3(int u){
    vis[u] = o;
    GSCC[u] = SCC;
    for(int v : gtr[u]){
        if(vis[v]!=o) dfs3(v);
    }
}

void dfs4(int u, int p){
    depth[u] = depth[p]+1;
    if(depth[u]>depth[gleb]) gleb = u;
    for(int v : gspoj[u]){
        if(v!=p) dfs4(v, u);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b;
    cin >> n >> m;
    for(int i = 0; i<m; i++){
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, 0); 
    o++;
    dfs2(1); 
    o++;
    for(int i = top.size()-1; i>=0; i--){
        if(vis[top[i]]!=o){
            SCC++;
            dfs3(top[i]);
        }
    }
    for(int i = 1; i<=n; i++){
        for(int u : gdfs[i]){
            if(GSCC[u]!=GSCC[i]){
                gspoj[GSCC[u]].push_back(GSCC[i]);
                gspoj[GSCC[i]].push_back(GSCC[u]);
            }
        }
    }
    depth[0] = -1;
    dfs4(1, 0);
    dfs4(gleb, 0);
    cout << depth[gleb];
    return 0;
}