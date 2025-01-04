#include <iostream>

using namespace std;

typedef long long ll;

const int N = 4e5 + 5;

ll tree[N];
ll lazy[N];

void push(ll ind, ll dl, ll dr){
    lazy[2*ind] += lazy[ind];
    tree[2*ind] += lazy[ind] * dl;
    lazy[2*ind+1] += lazy[ind];
    tree[2*ind+1] += lazy[ind] * dr;
    lazy[ind] = 0;
}

void update(ll l, ll r, ll ql, ll qr, ll ind, ll val){
    if(l>r or r<ql or l>qr) return;
    if(ql<=l and qr>=r){
        lazy[ind] += val;
        tree[ind] += val * (r-l+1);
        return;
    }
    ll mid = (l+r)/2;
    push(ind, mid-l+1, r-mid);
    update(l, mid, ql, qr, 2*ind, val);
    update(mid+1, r, ql, qr, 2*ind+1, val);
    tree[ind] = tree[2*ind] + tree[2*ind+1];
}

ll query(ll l, ll r, ll ql, ll qr, ll ind){
    if(l>r or r<ql or l>qr) return 0;
    if(ql<=l and qr>=r){
        return tree[ind];
    }
    ll mid = (l+r)/2;
    push(ind, mid-l+1, r-mid);
    return query(l, mid, ql, qr, 2*ind) + query(mid+1, r, ql, qr, 2*ind+1);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll testy, n, c, w, p, q, v;
    cin >> testy;
    for(ll i = 0; i<testy; i++){
        ll L = 1;
        cin >> n >> c;
        ll on = n;
        while(L<n) L*=2;
        n = L;
        for(ll j = 0; j<c; j++){
            cin >> w;
            if(w==0){
                cin >> p >> q >> v;
                update(1, n, p, q, 1, v);
            }
            else{
                cin >> p >> q;
                cout << query(1, n, p, q, 1) << '\n';
            }
        }
        for(ll j = 1; j<=on*4; j++){
            tree[j] = 0;
            lazy[j] = 0;
        }
    }
    return 0;
}