#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

#define fi first
#define se second

const int N = 1e6+5;
const int inf = 1e9;
int oh, h;

int dist[N];
set<int> g[N];
vector<pair<pair<int, int>, int>> cords;
vector<pair<pair<int, int>, int>> seg;
queue<int> q;

struct node{
    int val = 0;
    node *lewy = nullptr, *prawy = nullptr;
    node(){
    }
};

void dodaj(node *n, int lewo, int prawo){
    int mid = (lewo + prawo)/2;
    if(!n->lewy and lewo+1<=prawo){
        n->lewy = new node();
        n->prawy = new node();
    }
}

void dodaj_lewego(node *n, int lewo, int prawo){
    int mid = (lewo + prawo)/2;
    if(!n->lewy and lewo+1<=prawo){
        n->lewy = new node();
    }
}

void dodaj_prawego(node *n, int lewo, int prawo){
    int mid = (lewo + prawo)/2;
    if(!n->prawy and lewo+1<=prawo){
        n->prawy = new node();
    }
}


void ins(node *n, int lewo, int prawo, int &ql, int &qr, int &w){
    if(lewo>qr or prawo<ql or lewo>prawo) return;
    if(ql<=lewo and prawo<=qr){
        n->val = w;
        return;
    }
    if(n->val!=0){
        dodaj(n, lewo, prawo);
        n->lewy->val = n->val;
        n->prawy->val = n->val;
        n->val = 0;
    }
    int mid = (lewo+prawo)/2;
    if(mid>=ql){
        dodaj_lewego(n, lewo, prawo);
        ins(n->lewy, lewo, mid, ql, qr, w);
    }
    if(mid+1<=qr){
        dodaj_prawego(n, lewo, prawo);
        ins(n->prawy, mid+1, prawo, ql, qr, w);
    }
}

int que(node *n, int lewo, int prawo, int &x){
    if(x<lewo or x>prawo) return 0;
    if(n->val!=0) return n->val;
    if(lewo==prawo and lewo==x) return n->val;
    int mid = (lewo+prawo)/2;
    if(x<=mid){ 
        dodaj_lewego(n, lewo, prawo);
        return que(n->lewy, lewo, mid, x); 
    }
    else{
        dodaj_prawego(n, lewo, prawo);
        return que(n->prawy, mid+1, prawo, x);
    }
}

void bfs(int start){
    while(!q.empty()) q.pop();
    dist[start] = 1;
    q.push(start);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(int u : g[v]){
            if(dist[u]==-1){ 
                q.push(u);
                dist[u] = dist[v]+1;
            }
        }
    }
}

void edge(int &i, int &j){
    if(j==0 or i==0 or i==j or dist[i]==-999 or dist[j]==-999) return;
    g[i].insert(j);
    g[j].insert(i);
}

void punkt(int i, int j, int k){
    cords.push_back({{i, j}, k});
}

void testp(node *r, int s, int k){
    int p1 = que(r, 0, h, s);
    edge(k, p1);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int w, n, m, px, py, sx, sy, xd, yd, xg, yg, start, skarb, L=1, ind = 1, status = false, p;
    cin >> w >> h >> n >> m >> px >> py >> sx >> sy;
    for(int i = 1; i<=n; i++){
        dist[i] = -1;
        cin >> xd >> yd >> xg >> yg;
        if(xg<xd) swap(xg, xd);
        if(yg<yd) swap(yg, yd);
        punkt(xd, yd, 0);
        punkt(xd, yg, 0);
        punkt(xg, yg, inf);
    }
    for(int i = 0; i<m; i++){
        cin >> xd >> yd;
        punkt(xd, yd, -1);
    }
    punkt(px, py, -2); punkt(sx, sy, -3); sort(cords.begin(), cords.end());
    for(int i = 0; i<cords.size(); i++){ //numerowanie komnat 
        if(cords[i].se==inf or cords[i].se<0) continue;
        else{
            if(!status){status = true; cords[i].se = ind;}
            else{status = false; cords[i].se = ind; ind++;}
        }
    }
    reverse(cords.begin(), cords.end());
    ind = cords.size()-1;
    int prevx = cords[ind].fi.fi, prevy = cords[ind].fi.se, prevtyp = cords[ind].se, kom = 1, l = 0, r;
    cords.pop_back();
    status = true; oh = h;
    
    while(L<h)L*=2; h = L; h--;
    auto *root = new node();
    for(ind = cords.size()-1; ind>=0; ind--){
        int x = cords[ind].fi.fi, y = cords[ind].fi.se, typ = cords[ind].se;
        cords.pop_back();
        if((x==prevx and y==prevy) and (prevtyp == inf or typ==inf)){ 
            continue; 
        }
        if(typ==-1){
            dist[que(root, 0, h, y)] = -999;
            continue;
        }
        if(typ==-2){ 
            start = que(root, 0, h, y);
            continue;
        }
        if(typ==-3){
            skarb = que(root, 0, h, y);
            continue;
        }
        if(x==prevx){
            if(typ==inf){ 
                q.push(y); //"wciecia" miedzy dwoma punktami
                continue;
            }
            else{
                if(typ==prevtyp){
                    if(!status){ //rozpoczecie sciany
                        status = true;
                        kom = typ; 
                        l = y;
                    }
                    else if(status and typ==kom){ // drugi punkt sciany
                        r = y; status = false;
                        testp(root, r-1, kom);
                        while(!q.empty()){ //laczenie "wciec" - poprzednikow
                            testp(root, q.front()-1, kom);
                            q.pop();
                        }
                        seg.push_back({{l, r}, kom}); r--;
                        ins(root, 0, h, l, r, kom);
                    }
                }
                else{
                    status = true;
                    kom = typ;
                    l = y;
                }
            }
        }
        else{
            for(int i = seg.size()-1; i>=0; i--){ // laczenie sasiadow
                int l1 = seg[i].fi.fi, r1 = seg[i].fi.se, k1 = seg[i].se;;
                if(l1>0) testp(root, l1-1, k1); 
                if(r1<oh) testp(root, r1, k1);
                seg.pop_back();
            }

            status = true;
            kom = typ;
            l = y;
            if(x==w)break;
        }
        prevx = x;
        prevy = y;
        prevtyp = typ;
    }
    bfs(start);
    cout << dist[skarb];
    return 0;
}