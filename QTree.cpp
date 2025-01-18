#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

const int N = 1e4+5;
int timer = 1, L = 1, n;

vector<pair<int, int>> v;

vector<pair<int, int>> g[N];

int heavy[N];
int sub[N];
int pa[N];
int head[N];
int cost[N];
int dep[N];

int tree[4*N];
int pos[N]; 

int tree_query(int l, int r, int ql, int qr, int x){
    if(r<ql or qr<l) return 0;
    if(ql<=l and r<=qr) return tree[x];
    int mid = (l+r)/2;
    return max(tree_query(l, mid, ql, qr, 2*x), tree_query(mid+1, r, ql, qr, 2*x+1));
}

void tree_update(int l, int r, int qp, int x, int val){
    if(r<qp or qp<l) return;
    if(l==r and qp==l){
        tree[x] = val;
        return;
    }
    int mid = (l+r)/2;
    if(qp<=mid) tree_update(l, mid, qp, 2*x, val);
    else tree_update(mid+1, r, qp, 2*x+1, val);
    tree[x] = max(tree[2*x], tree[2*x+1]);
}

void dfs_sub(int u, int p){
    pa[u] = p;
    sub[u] = 1;
    dep[u] = dep[p]+1;
    heavy[u] = -1;
    for(pair<int, int> e : g[u]){
        int v = e.fi;
        int w = e.se;
        if(v!=p){
            cost[v] = w;
            dfs_sub(v, u);
            sub[u] += sub[v];
            if(heavy[u] == -1 or sub[heavy[u]] < sub[v]) heavy[u] = v;
        }
    }
}

void dfs_hld(int u, int p, int h){
	pos[u] = timer++;
	head[u] = h;
	tree_update(1, n, pos[u], 1, cost[u]);
	int h_chi = -1, h_sz = -1;
	for(pair<int, int> e : g[u]) {
        int v = e.fi;
		if(v==p)continue;
		if(sub[v] > h_sz){
			h_sz = sub[v];
			h_chi = v;
		}
	}
	if(h_chi == -1) return;
	dfs_hld(h_chi, u, h);
	for(pair<int, int> e : g[u]){
        int v = e.fi;
		if(v == p or v == h_chi) continue;
		dfs_hld(v, u, v);
	}
}

int query(int u, int v){
    int ans = 0;
    while(head[u] != head[v]) {
        if(dep[head[u]] > dep[head[v]]) swap(u, v);
        ans = max(ans, tree_query(1, n, pos[head[v]], pos[v], 1));
        v = pa[head[v]]; 
    }
    if(dep[u] > dep[v]) swap(u, v);
    if(dep[heavy[u]] <= dep[v]) ans = max(ans, tree_query(1, n, pos[heavy[u]], pos[v], 1));
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, a, b, c;
    string x;
    cin >> t;
    while(t--){
        v.clear();
        for(int i = 0; i<N; i++){
            g[i].clear();
            tree[i] = 0;
        }for(int i = N; i<4*N; i++) tree[i] = 0;
        L = 1; timer = 1; v.push_back({-1, -1}); 

        cin >> n;
        while(L<n) L*=2;

        for(int i = 1; i<=n-1; i++){
            cin >> a >> b >> c;
            g[a].push_back({b, c});
            g[b].push_back({a, c});
            v.push_back({a, b});
        }
        dfs_sub(1, 1);
        for(int i = 1; i < n; i++) {
            if(pa[v[i].first] == v[i].second) swap(v[i].first, v[i].second);
        }
        n = L;
        dfs_hld(1, 1, 1);

        while(true){
            cin >> x;
            if(x[0] == 'D') break;
            cin >> a >> b;
            if(x[0] == 'Q') cout << query(a, b) << '\n';
            else tree_update(1, n, pos[v[a].second], 1, b);
        }
    }
    return 0;
}