#include <iostream>

using namespace std;

typedef long long ll;

const int N = 1e6+5;
const int INF = 10005;

struct node{
    ll max_pref;
    ll max_suf;
    ll sum;
    ll max_sum;
};

node tree[N];

node node_update(node l, node r){
    node p;
    p.sum = l.sum + r.sum;
    p.max_pref = max(l.max_pref, l.sum + r.max_pref);
    p.max_suf = max(r.max_suf, r.sum + l.max_suf);
    p.max_sum = max(max(l.max_sum, r.max_sum), l.max_suf + r.max_pref);
    return p;
}

void leaf_update(int i, int val){
    tree[i].max_pref = val;
    tree[i].max_suf = val;
    tree[i].sum = val;
    tree[i].max_sum = val;
}

void update(ll l, ll r, ll ind, ll pos, ll val){
    if(pos<l or pos>r) return;
    if(l==r){
        leaf_update(ind, val);
        return;
    }
    int mid = (l+r)/2;
    update(l, mid, 2*ind, pos, val);
    update(mid+1, r, 2*ind+1, pos, val);
    node x = tree[2*ind];
    node y = tree[2*ind+1];
    tree[ind] = node_update(x, y);
    
}

node query(ll l, ll r, ll ql, ll qr, ll ind){
    if(l>qr or r<ql or l>r) return tree[0];
    if(ql<=l and qr>=r){
        return tree[ind];
    }
    int mid = (l+r)/2;
    node x = query(l, mid, ql, qr, 2*ind);
    node y = query(mid+1, r, ql, qr, 2*ind+1);
    return node_update(x, y);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, L=1, t, x, y;
    cin >> n;
    leaf_update(0, -INF);
    while(L<n)L*=2;
    for(int i = L; i<L+n; i++){
        cin >> x;
        leaf_update(i, x);
    }
    for(int i = L-1; i>0; i--) tree[i] = node_update(tree[2*i], tree[2*i+1]);
    n = L;
    cin >> m;
    for(int i = 0; i<m; i++){
        cin >> t >> x >> y;
        if(!t){ 
            update(1, n, 1, x, y);
        }
        else cout << query(1, n, x, y, 1).max_sum << '\n';
    }
    return 0;
}