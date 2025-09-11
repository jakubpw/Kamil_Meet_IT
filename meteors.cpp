#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;

const int N = 3e5+5;

int n, m, k, akt = 0;

vector<int> o[N];

vector<int> p;

ll tree[1<<20];

int lef[N], rig[N], val[N], res[N], required[N]; 

ll query(int q, int l, int r, int ind){
    if(l>r) return 0;
    if(l==r) return tree[ind];

    int mid = (l+r)/2;
    tree[ind*2] += tree[ind];
    tree[ind*2+1] += tree[ind];
    tree[ind] = 0;

    if(q<=mid) return query(q, l, mid, ind*2);
    else return query(q, mid+1, r, ind*2+1);
}

void u(int ql, int qr, int l, int r, int a, int ind){
    if(l>r or r<ql or l>qr) return;
    if(ql<=l and r<=qr){
        tree[ind] += a;
        return;
    }
    int mid = (l+r)/2;
    u(ql, qr, l, mid, a, ind*2);
    u(ql, qr, mid+1, r, a, ind*2+1);
}

void u_check(int v, int i){
    if(lef[i]<=rig[i]) u(lef[i], rig[i], 1, m, v, 1);
    else{
        u(1, rig[i], 1, m, v, 1);
        u(lef[i], m, 1, m, v, 1);
    }
}

void bsearch(int l, int r, vector<int> &p, int &akt){
    if(p.empty()) return;

    int mid = (l+r)/2;

    while(akt<mid){
        akt++;
        u_check(val[akt], akt);
    }

    while(akt>mid){
        u_check(-val[akt], akt);
        akt--;
    }

    vector<int> les;
    vector<int> mor;

    for(int w : p){
        ll samples = 0;
        for(int owned : o[w]){
            samples += query(owned, 1, m, 1);
            if(samples>=required[w]) break;
        }
        if(samples>=required[w]){
            les.push_back(w);
            res[w] = r;
        }
        else mor.push_back(w);
    }
    p.clear();
    if(l<r){
        bsearch(l, mid, les, akt);
        bsearch(mid+1, r, mor, akt);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    int x;

    for(int i = 1; i<=m; i++){
        cin >> x;
        o[x].push_back(i);
    }

    for(int i = 1; i<=n; i++){
        cin >> required[i];
        p.push_back(i);
    }

    cin >> k;

    for(int i = 1; i<=k; i++) cin >> lef[i] >> rig[i] >> val[i];

    bsearch(1, k, p, akt);

    for(int i = 1; i<=n; i++) res[i] ? (cout << res[i] << '\n') : (cout << "NIE\n");
}