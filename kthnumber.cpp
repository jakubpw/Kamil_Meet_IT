#include<bits/stdc++.h>

using namespace std;

#define mx 100005

int arr[mx];
vector<int>v;

struct Node{
    Node *lewy;
    Node *prawy;
    int sum;
    Node(int v = 0, Node *l = nullptr, Node *r = nullptr){
        sum = v;
        lewy = l;
        prawy = r;
    }
}*root[mx];

void build(Node* n, int lewo, int prawo){
    if(lewo==prawo){
        n->sum=0;
        return;
    }
    int mid=(lewo+prawo)/2;
    n->lewy=new Node();
    n->prawy=new Node();
    build(n->lewy, lewo, mid);
    build(n->prawy, mid+1, prawo);
}


void update(Node* p, Node* n, int lewo, int prawo, int ind){
    if(ind>prawo or ind<lewo or lewo>prawo) return;
    if(lewo==prawo){
        n->sum = 1;
        return;
    }
    int mid=(lewo+prawo)/2;
    if(ind<=mid){
        n->prawy = p->prawy;
        n->lewy = new Node();
        update(p->lewy, n->lewy, lewo, mid,ind);
    }
    else{
        n->lewy = p->lewy;
        n->prawy = new Node();
        update(p->prawy, n->prawy, mid+1, prawo, ind);
    }
    n->sum = n->lewy->sum + n->prawy->sum;
}

int query(Node* p, Node* n, int lewo, int prawo, int k){
    if(lewo==prawo) return lewo;
    int dif = n->lewy->sum - p->lewy->sum;
    int mid = (lewo+prawo)/2;
    if(dif>=k) return query(p->lewy, n->lewy, lewo, mid, k);
    else return query(p->prawy, n->prawy, mid+1, prawo, k-dif);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q, l, r, k;
    cin >> n >> q;
    for(int i = 1; i<=n; i++){
        cin >> arr[i];
        v.push_back(arr[i]);
    }
    sort(v.begin(),v.end());
    for(int i = 1; i<=n; i++){
        arr[i] = lower_bound(v.begin(), v.end(), arr[i]) - v.begin() + 1;
    }

    root[0] = new Node();
    build(root[0], 1, n);

    for(int i = 1; i<=n; i++){
        root[i] = new Node();
        update(root[i-1], root[i], 1, n, arr[i]);
    }

    for(int i = 0; i<q; i++){
        cin >> l >> r >> k;
        int indx = query(root[l-1], root[r], 1,n,k);
        cout << v[indx-1] << '\n';
    }
    return 0;
}