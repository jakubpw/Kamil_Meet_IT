#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define fi first
#define se second

const int N = 2e5+5;

multiset<pair<int,int>> miasta;
multiset<pair<int, int>> zbiory[N];
bool vis[N] = {false};
int parent[N];
int siz[N];
int drogi[N];

ll mst = 0, n, M, id, indeks, res;

int fajnd(int x){
    if(x!=parent[x]) parent[x] = fajnd(parent[x]);
    return parent[x];
}

void unjon(int a, int b){
    a = fajnd(a);
    b = fajnd(b);
    if(a==b)return;
    if(siz[a]>siz[b])swap(a, b);
    parent[a] = b;
    siz[b] += siz[a];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> M;
    for(int i = 1; i<=n; i++){
        cin >> drogi[i];
        siz[i] = 1;
        parent[i] = i;
        miasta.insert({drogi[i], i});
    }
    while(siz[fajnd(1)]!=n){
        for(int i = 1; i<=n; i++){vis[i] = false; zbiory[i].clear();}
        for(int i = 1; i<=n; i++){zbiory[fajnd(i)].insert({drogi[i], i});}
        for(int i = 1; i<=n; i++){
            if(vis[fajnd(i)]) continue; 
            vis[i] = true;
            id = fajnd(i); 
            
            for(auto miasto : zbiory[id]) miasta.erase(miasto);

            if(!miasta.empty()){
                res = miasta.begin()->fi + drogi[i];
                indeks = miasta.begin()->se;
                for(auto m : zbiory[id]){
                    if(m.fi+miasta.begin()->fi<res){
                        res = m.fi+miasta.begin()->fi;
                        indeks = m.se;
                    }
                    auto as = miasta.upper_bound({M-m.fi, 0});
                    if(as!=miasta.end() and m.fi + as->fi - M < res){
                        res = m.fi + as->fi - M;
                        indeks = as->se;
                    }
                }
            }
            mst+=res;
            vis[fajnd(indeks)] = true;
            unjon(id, indeks);
            for(auto miasto : zbiory[id]) miasta.insert(miasto);
        }
    }
    cout << mst;
    return 0;
}