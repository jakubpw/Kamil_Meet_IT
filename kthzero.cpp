/*
Identyczne rozwiazanie, ale bez przerzucania vectorow w funkcjach, ktore wtedy byly zdefiniowane globalnie, przeszlo na 18.75. Nie wiem czemu tak sie dzialo, to przeszlo na 60(maks).
*/
#include <bits/stdc++.h>

using namespace std;

void budowanie(vector<int>& tree, vector<bool>& a, int index, int l, int r){
    if(l==r){
        if(a[l]==0) tree[index] = 0;
        else tree[index] = 1;
        return;
    } 
    int mid = (l+r)/2;
    budowanie(tree, a, index * 2, l, mid);
    budowanie(tree, a, index * 2 + 1, mid + 1, r);
    tree[index] = tree[index * 2] + tree[index * 2 + 1];
}

void update(vector<int>& tree, int index, int l, int r, int pos, bool v){
    if(l==r){
        if(v==0) tree[index] = 0;
        else tree[index] = 1;
        return;
    } 
    int mid = (l + r) / 2;
    if(pos<=mid) update(tree, 2*index, l, mid, pos, v);
    else update(tree, 2*index+1, mid+1, r, pos, v);
    tree[index] = tree[index * 2] + tree[index * 2 + 1];
}

int query(vector<int>& tree, int index, int l, int r, int k) {
    if(tree[index]<k) return -1;
    if(l==r) return l;
    int mid = (l+r)/2;
    if(tree[index * 2] >= k) return query(tree, 2*index, l, mid, k);
    else return query(tree, 2*index+1, mid+1, r, k-tree[2*index]);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, x;
    cin >> n >> m;
    vector<bool> a;
    vector<int> tree(4 * n + 1);
    for(int i = 0; i<n; i++){
        cin >> x;
        if(x==0)a.push_back(1);
        else a.push_back(0);
    }
    budowanie(tree, a, 1, 0, n - 1);
    for(int i = 0; i<m; i++){
        int type, k, pos, val;
        cin >> type;
        if(type==1){
            cin >> k;
            int ans = query(tree, 1, 0, n-1, k);
            if(ans == -1) cout << "NO\n";
            else cout << ans << "\n";
        }
        else{
            cin >> pos >> val;
            update(tree, 1, 0, n-1, pos, val==0);
        }
    }
    return 0;
}