#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

const int N = 1e4+5;
const int l = 15;
int timer = 1, L = 1, n;

//pomysl jest taki, zeby wierzcholek mial wartosc krawedzi prowadzacej go do rodzica
//pozniej sciezke (a, b) rozdzielic na (a, LCA(a, b)) i (b, LCA(a, b))

vector<pair<pair<int, int>, int>> g[N];
pair<int, int> id_edge[N]; // = {oryginalny_wierzcholek(w dol drzewa), waga}
pair<int, int> id_node[N]; // = {wierzcholek_HLD, waga}
int anc[N][l];
int depth[N];
int tree[4*N];
int siz[N];
int head[N];

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

void dfs_siz(int u, int p, int waga){
    anc[u][0] = p;
    depth[u] = depth[p]+1;
    siz[u] = 1;
    for(pair e : g[u]){
        int v = e.fi.fi;
        int w = e.fi.se; 
        int indeks = e.se; 
        if(v!=p){
            dfs_siz(v, u, w);
            id_edge[indeks].fi = v;
            id_node[v].se = w;
            siz[u] += siz[v];
        }
    }
}

void dfs_hld(int u, int p, int h){
	id_node[u].fi = timer++;
	head[u] = h;
	tree_update(1, n, id_node[u].fi, 1, id_node[u].se);
	int h_chi = -1, h_sz = -1;
	for(pair e : g[u]) {
        int v = e.fi.fi;
		if(v==p)continue;
		if(siz[v] > h_sz){
			h_sz = siz[v];
			h_chi = v;
		}
	}
	if(h_chi == -1) return;
	dfs_hld(h_chi, u, h);
	for(pair e : g[u]){
        int v = e.fi.fi;
		if(v == p or v == h_chi) continue;
		dfs_hld(v, u, v);
	}
}

void preprocess(int n){
    for(int j = 1; j<l; j++){
        for(int i = 1; i<=n; i++){
            anc[i][j] = anc[anc[i][j-1]][j-1];
        }
    }
}

int LCA(int a, int b){
    if(depth[a]>depth[b]) swap(a, b);
    int diff = depth[b]-depth[a];
    for(int i = 0; i<17; i++){
        if(diff&(1<<i)){
            b = anc[b][i];
        }
    }
    if(a==b) return a;
    for(int l = 16; l>=0; l--){
        if(anc[a][l]!=anc[b][l]){
            a = anc[a][l];
            b = anc[b][l];
        }
    }
    return anc[a][0];
}

int query(int a, int b){
    int res = 0;
    if(head[a]==head[b]){ //jesli sa w tej samej sciezce
        if(a>b) swap(a, b);
        res = max(res, tree_query(1, n, a, b, 1));
        return res;
    }
    int ancestor = LCA(a, b);
    if(ancestor==0) ancestor = 1; //stworzylem sztuczny wierzcholek na gorze, nie wiem czy potrzebny, ale problemow chyba nie robi
    while(true){
        res = max(res, tree_query(1, n, head[a], a, 1)); //head[a] zawsze bedzie <= a
        a = anc[head[a]][0]; //przesuniecie na rodzica przedstawiciela
        if(head[ancestor]==head[a]){ //sa w tej samej sciezce, wiec pozostala jeden przedzial do sprawdzenia
            res = max(res, tree_query(1, n, ancestor, a, 1));
            break;
        }
        else if(a==0)break; //head[a] to 1, ustawi sie na 0, wiec nie ma juz nic do sprawdzenia
    }//tak samo jak u gory
    while(true){
        res = max(res, tree_query(1, n, head[b], b, 1));
        b = anc[head[b]][0];
        if(head[ancestor]==head[b]){
            res = max(res, tree_query(1, n, ancestor, b, 1));
            break;
        }
        else if(b==0) break;
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, a, b, c;
    string x;
    cin >> t;
    while(t--){
        for(int i = 0; i<N; i++){ // czesc z tych tablic nie trzeba czyścić, ale na wszelki wypadek
            g[i].clear();
            id_edge[i] = {0, 0};
            id_node[i] = {0, 0};
            siz[i] = 0;
            depth[i] = 0;
            head[i] = 0;
            tree[i] = 0;
        }
        for(int i = N; i<4*N; i++) tree[i] = 0;
        L = 1; timer = 1;

        cin >> n;
        while(L<n) L*=2;
        for(int i = 1; i<=n-1; i++){
            cin >> a >> b >> c;
            g[a].push_back({{b, c}, i});
            g[b].push_back({{a, c}, i});
            id_edge[i].se = c;
        }
        
        preprocess(n);

        n = L;

        dfs_siz(1, 0, 0);
        dfs_hld(1, 0, 1);

        while(true){
            cin >> x;
            if(x[0] == 'D') break;
            cin >> a >> b;
            if(x[0] == 'Q') cout << query(id_node[a].fi, id_node[b].fi) << '\n';
            else tree_update(1, n, id_node[id_edge[a].fi].fi, 1, b);
        }
    }
    return 0;
}