#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll N = 1000;
const ll M = 2e4;
const ll INF = 1e9;

ll s, t, n, T;

struct edge{
    ll a, b;
    ll cap, flow;
};

struct team{
    ll w;
    ll l;
}teams[30];

vector<edge> edges;
vector<ll> g[M];
ll a[30][30], d[N], ptr[M];

void add(ll from, ll to, ll cap){
    edge e1 = {from, to, cap, 0};
    edge e2 = {to, from, 0, 0};
    g[from].push_back(edges.size());
    edges.push_back(e1);
    g[to].push_back(edges.size());
    edges.push_back(e2);
}

bool bfs(){
    bool vis[N] = {false};
    queue<int> Q;
    Q.push(s);
    d[s] = 0;
    vis[s] = 1;
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        for(auto w : g[u]){
            ll id = w;
            ll to = edges[id].b;
            if(edges[id].flow < edges[id].cap and !vis[to]){
                vis[to] = true; 
                d[to] = d[u] + 1;
                Q.push(to);
            }
        }
    }
    return vis[t];
}

ll dfs(ll v, ll flow){
    if(v == t or flow == 0) return flow;
    ll flow2 = 0, pushed;
    for(; ptr[v]<g[v].size(); ptr[v]++){
        ll id = g[v][ptr[v]];
        ll to = edges[id].b;
        if(d[to] == d[v] + 1 and (pushed = dfs(to, min(flow, edges[id].cap - edges[id].flow)))>0){
            edges[id].flow += pushed;
            edges[id^1].flow -= pushed;
            flow2 += pushed;
            flow -= pushed;
            if(flow == 0) break;
        }
    }
    return flow2; 
}

ll dinic(){
    ll max_flow = 0;
    while(bfs()){
        for(ll i = 0; i < N; i++) ptr[i] = 0;
        max_flow += dfs(s, INF);
    }
    return max_flow;
}

void restart(){
    for(ll i = 0; i<M; i++) g[i].clear();
    edges.clear();
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    while(T--){
        cin >> n;
        s = 0; t = n*(n+1) + 2;
        for(ll i = 1; i<=n; i++) cin >> teams[i].w >> teams[i].l;
        for(ll i = 1; i<=n; i++){
            for(ll j = 1; j<=n; j++){
                cin >> a[i][j];
            }   
        }
        ll rec = 0, cnt = 1;
        for(ll i = 1; i<=n; i++) add(i, t, 0);
        for(ll i = 1; i<=n; i++){
            for(ll j = i+1; j<=n; j++){
                add(s, cnt+n, a[i][j]);
                rec += a[i][j];
                add(cnt+n, i, INF);
                add(cnt+n, j, INF);
                cnt++;
            }
        }
        bool flag = 0;
        for(ll i = 1; i<=n; i++){
            ll sum = teams[i].w, cap;
            for(ll j = 1; j<=n; j++) sum += a[i][j];
            for(ll j = 0; j<edges.size(); j++) edges[j].flow = 0;
            for(ll j = 0; j<2*n; j+=2){
                cap = sum - teams[(j/2)+1].w;
                if(cap<0){
                    cap = -1;
                    break;
                }
                edges[j].cap = cap;
            }
            if(cap==-1)continue;
            ll result = dinic();
            //cout << rec << " " << result << '\n';
            if(result == rec){
                if(flag) cout << " ";
                cout << i;
                flag = 1;
            }
        }
        cout << '\n';
        restart();
    }
    return 0;
}

/*
1
3
2 0 1 1 0 2
0 2 2 2 0 2 2 2 0
-----------------------

3
3
2 0 1 1 0 2
0 2 2 2 0 2 2 2 0
3
4 0 2 2 0 4
0 1 1 1 0 1 1 1 0
4
0 3 3 1 1 3 3 0
0 0 0 2 0 0 1 0 0 1 0 0 2 0 0 0

1 2 3
1 2
2 4

*/