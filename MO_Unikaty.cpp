#include <bits/stdc++.h>

using namespace std;

int tab[30005] = {0};
int licz[1000005] = {0};
int s, wyn = 0;
int wyniki[200005] = {0};

struct query{
    int l;
    int r;
    int ind;
};

bool comparator(query q1, query q2){
    int block_a = q1.l/s, block_b = q2.l/s;
    if(block_a==block_b){
        return q1.r < q2.r;
    }
    return block_a < block_b;
}

void add(int i){
    licz[i]++;
    if(licz[i]==1)wyn++;
}

void sub(int i){
    licz[i]--;
    if(licz[i]==0)wyn--;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q, a, b;
    cin >> n;
    s = sqrt(n);
    for(int i = 1; i<=n; i++) cin >> tab[i];
    
    cin >> q;
    query zap[q+5];
    for(int i = 0; i<q; i++){
        cin >> a >> b;
        zap[i].l = a;
        zap[i].r = b;
        zap[i].ind = i;
    }
    sort(zap, zap+q, comparator);
    int cur_l = 0, cur_r = -1;
    for(int i = 0; i<q; i++){
        while(cur_l>zap[i].l){
            cur_l--;
            add(tab[cur_l]);
        }
        while(cur_r<zap[i].r){
            cur_r++;
            add(tab[cur_r]);
        }
        while(cur_l<zap[i].l){
            sub(tab[cur_l]);
            cur_l++;
        }
        while(cur_r>zap[i].r){
            sub(tab[cur_r]);
            cur_r--;
        }
        //cout << cur_l << " " << cur_r << '\n';
        wyniki[zap[i].ind] = wyn;
    }
    for(int i = 0; i<q; i++) cout << wyniki[i] << '\n';
    return 0;
}