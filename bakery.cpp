#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MAX = 35005;

int N, K;
int rt[MAX], pos[MAX], a[MAX];
int dp[MAX][52];
map<int, int> cache[MAX];

struct Node{
    Node *lewy;
    Node *prawy;
    int sum;
    Node(int v = 0, Node *l = nullptr, Node *r = nullptr){
        sum = v;
        lewy = l;
        prawy = r;
    }
}*root[MAX*5];

void build(Node *n, int lewo, int prawo){
    if(lewo==prawo){
        n->sum=0;
        return;
    }
    int mid=(lewo+prawo)/2;
    n->lewy = new Node();
    n->prawy = new Node();
    build(n->lewy, lewo, mid);
    build(n->prawy, mid+1, prawo);
}

void update(Node *p, Node *n, int lewo, int prawo, int ind, int val){
    if(prawo<lewo) return;
    if(lewo==prawo){ 
        n->sum = val;
        return;
    }

    int mid = (lewo+prawo)/2;

    if(ind<=mid){
        n->prawy = p->prawy;
		n->lewy = new Node();
        update(p->lewy, n->lewy, lewo, mid, ind, val);
    }
    else{
        n->lewy = p->lewy;
		n->prawy = new Node();
        update(p->prawy, n->prawy, mid+1, prawo, ind, val);
    }
    n->sum = n->lewy->sum + n->prawy->sum;
}

int query(Node *n, int lewo, int prawo, int l, int r){
    if(prawo<lewo or r<lewo or prawo<l) return 0;
    if(l<=lewo and prawo<=r) return n->sum;

    int mid = (lewo+prawo)/2;

    int q1 = query(n->lewy, lewo, mid, l, r);
    int q2 = query(n->prawy, mid+1, prawo, l, r);

    return q1+q2;
}

int C(int l, int r){ 
    if(l > r) return 0;
    if(cache[l].count(r) == 0) cache[l][r] = query(root[rt[r]], 1, N, l, r);
    return cache[l][r];
}

void opt(int l, int r, int warstwa, int opt_l, int opt_r){
    if(l>r) return;
    int optk, res = 0, m = (l+r)/2;
    for(int k = opt_l; k <= min(m, opt_r); k++){
        int res2 = dp[k-1][warstwa-1] + C(k, m);
        if(res2>res){
            res = res2;
            optk = k;
        }
    }
    dp[m][warstwa] = res;
    opt(l, m-1, warstwa, opt_l, optk);
    opt(m+1, r, warstwa, optk, opt_r);
}

void process(){
    for(int i = 1; i<=N-K+1; i++) dp[i][1] = C(1, i);
    for(int j = 2; j<=K; j++){ 
        opt(1, N, j, 1, N);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> N >> K;

    root[0] = new Node();
    build(root[0], 1, N);

    int t = 1;

    for(int i = 1; i<=N; i++){
    	cin >> a[i];

    	int k = pos[a[i]];
		root[t] = new Node();

    	if(!k) update(root[t-1], root[t], 1, N, i, 1);
    	else{
    		update(root[t-1], root[t], 1, N, k, 0);
    		t++;
			root[t] = new Node();
    		update(root[t-1], root[t], 1, N, i, 1);
    	}
        t++;
    	rt[i] = t-1;
    	pos[a[i]] = i;
    }
    process();
    cout << dp[N][K];
    return 0;
}