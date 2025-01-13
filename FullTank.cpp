//pair<pair<int, int>, int>> wywalal jakis blad przy odwolywaniu sie pq.top(), nie wiem czemu, dlatego sa tuple, normalnie nie uzywam ale teraz chyba zaczne bo wygodniejsze

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

const int N = 1e3+5;
const int inf = 1e9;

vector<pair<int, int>> g[N];
int price[N];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b, q, c, s, e;
    cin >> n >> m;
    for(int i = 0; i<n; i++) cin >> price[i];
    for(int i = 0; i<m; i++){
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    cin >> q;
    for(int i = 0; i<q; i++){
        cin >> c >> s >> e;
        vector<vector<int>> dist(n, vector<int>(c+1, inf)); //dp bedzie mial minimalny koszt dla danego miasta przy danym paliwie
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        dist[s][0] = 0;
        pq.push({0, 0, s});
        int res = inf;
        while(!pq.empty()){
            int koszt, paliwo, miasto;
            tie(koszt, paliwo, miasto) = pq.top();
            pq.pop();
            if(koszt>dist[miasto][paliwo])continue;
            if(miasto==e) res = min(res, koszt);
            if(paliwo<c){
                int npal = paliwo + 1;
                int nkos = koszt + price[miasto];
                if(nkos<dist[miasto][npal]){
                    dist[miasto][npal] = nkos;
                    pq.push({nkos, npal, miasto});
                }
            }
            for(pair e : g[miasto]){
                int to = e.fi;
                int droga = e.se;
                if(paliwo>=droga){
                    int npal = paliwo-droga;
                    if(koszt<dist[to][npal]){
                        dist[miasto][npal] = koszt;
                        pq.push({koszt, npal, to});
                    }
                }
            }
        }
        if(res>=inf) cout << "impossible\n";
        else cout << res << '\n';
    }
    return 0;
}