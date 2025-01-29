    #include <bits/stdc++.h>

using namespace std;

const int N = 1e3+5;
const int inf = 1e9;

struct Edge{
    int x, y, cap, n;
};

vector<Edge> edges(N);
int e, head[N], dist[N], path[N], record[N];

void addEdge(int x, int y, int flow){
    edges[e].x = x, edges[e].y = y, edges[e].cap = flow;
    edges[e].n = head[x], head[x] = e++;
    edges[e].x = y, edges[e].y = x, edges[e].cap = 0;
    edges[e].n = head[y], head[y] = e++;
}

int FF(int s, int t){
    int flow = 0, x, y;
    while(true){
        memset(dist, 0, sizeof(dist));
        dist[s] =  inf;
        queue<int> Q;
        Q.push(s);
        while(!Q.empty()){
            x = Q.front();
            Q.pop();
            for(int i = head[x]; i != -1; i = edges[i].n){
                int y = edges[i].y;
                if(dist[y] == 0 and edges[i].cap > 0){
                    path[y] = x, record[y] = i;
                    dist[y] = min(dist[x], edges[i].cap);
                    Q.push(y);
                }
            }
            if(dist[t])break;
        }
        if(dist[t]==0) break;
        flow += dist[t];
        for(x = t; x != s; x = path[x]){
            int ri = record[x];
            edges[ri].cap -= dist[t];
            edges[ri^1].cap += dist[t];
        }
    }
    return flow;
}
int main(){
    int n, m, c = 1, t, k, x, y, ujscie;
    cin >> t;
    while(t--){
    	cin >> n >> m;
        e = 0, ujscie = n + m + 1;
        int karty[15][30] = { };
        edges.clear();
        for(int i = 0; i<N; i++) head[i] = -1;
        for(int i = 1; i <= n; i++){
        	cin >> x;
        	for(int j = 0; j < x; j++){
        		cin >> y;
                karty[i][y]++;
            }
        }
        for(int j = 1; j <= m; j++){
            addEdge(1, n+j, karty[1][j]);
            addEdge(n+j, ujscie, 1);
        }
        for(int i = 2; i <= n; i++){
        	for(int j = 1; j <= m; j++){
        		if(karty[i][j] > 1) addEdge(i, n+j, karty[i][j] - 1);
        		else if(karty[i][j] == 0) addEdge(n+j, i, 1);
        	}
        }
        int flow = FF(1, ujscie);
        cout << "Case #" << c << ": " << flow << '\n';
        c++;
    }
    return 0;
}