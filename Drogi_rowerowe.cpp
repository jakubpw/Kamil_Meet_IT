#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+5;
const int M = 1e6;

int n, m;
vector<int> g[N], revg[N];
vector<int> gscc[N];
int siz = 0; 
int ilspoj = 0;
int spojne[N], dp[N], k[N];
bool vis[N];
vector<int> st;

void dfs(int v){
	vis[v] = true;
	for(int s: g[v]){
		if(vis[s])continue;
		dfs(s);
	}
	st.push_back(v);
}

void dfs2(int v){
	vis[v] = true;
	spojne[v] = ilspoj;
	siz++;
	for(int s: revg[v]){
		if(vis[s])continue;
		dfs2(s);
	}
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i<m; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		revg[v].push_back(u);
	}
    //toposort
	for(int i = 1; i<=n; i++){
		if(!vis[i]) dfs(i);
	}
	for(int i = 1; i<=n; i++)vis[i] = false;
    //przydzielanie wierzcholkow do spojnych 
	while(!st.empty()){
		int v = st.back();
		st.pop_back();
		if(vis[v])continue;
		ilspoj++;
		siz = 0;
		dfs2(v);
		dp[ilspoj] = siz;
	}
	//tworzenie grafu scc
	for(int v = 1; v<=n; v++){//v
		for(int s: g[v]){//u
			if(spojne[v] != spojne[s]){
    			gscc[spojne[s]].push_back(spojne[v]); //jest odwrocony zeby pozniej obliczac dp 
    			k[spojne[v]]++; /*ile krawedzi bedzie mial dany wierzcholek */
            }
		}
	}
    //wyznaczanie startu/ów, tego/tych z ktorym/ch nie da sie przejsc dalej
	queue<int> Q;
	for(int i = 1; i<=ilspoj; i++){
		if(!k[i]) Q.push(i);
	}
    //idziemy "od tylu" jak wczesniej w komentarzach napisane
    while(!Q.empty()){
		int v = Q.front();
		Q.pop();
		for(int s: gscc[v]) {
			k[s]--; 
			dp[s] += dp[v]; //zbieramy rozmiary scc, bo do tamtych da sie dojsc
			if(!k[s])Q.push(s); //mozemy rozwazac kolejnego jak wezniemy wszystkie rozmiary poprzednich
		}
	}
	for(int i = 1; i <= n; i++) cout << dp[spojne[i]] - 1 << '\n';
    
    return 0;
}