#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int s;

int tab[N] = {0};
int tww[N] = {0};
int wyniki[N] = {0};
bool mexy[N] = {0};
int ilosc[2*N];
map<int, int> kompresja;
vector<pair<int, pair<int, int>>> update; 
int g[N]; //g trzyma ostatnio wartosc na danym indeksie, bedzie potrzebne to vectora aktualizacji

struct query{
    int l;
    int r;
    int ind;
    int up;
};

bool comparator(query q1, query q2){
    const int p = s;
    int block_a = q1.l/p, block_b = q2.l/p;
    int block_1 = q1.r/p, block_2 = q2.r/p;
    if(block_a==block_b){
        if(block_1==block_2){
            return q1.up < q2.up;
        }
        return q1.r < q2.r;
    }
    return block_a < block_b;
}
//wszystkie dzialaja w O(1)
void add(int a){
    int zm = ilosc[a]+1;
    ilosc[a]++;
    mexy[zm] = true;
    tww[zm]++;
    tww[zm-1]--; 
    if(!tww[zm-1])mexy[zm-1] = false;
}

void sub(int a){
    int zm = ilosc[a]-1;
    ilosc[a]--;
    mexy[zm] = true;
    tww[zm]++; 
    tww[zm+1]--; 
    if(!tww[zm+1])mexy[zm+1] = false;
}

void ustaw(int i, int j){
    if(tab[i]==j)return; 
    sub(tab[i]); 
    tab[i] = j; 
    add(j); 
}

void funckja_aktualizacyjna(int &l, int &r, int &of, int &os){
    if(of>=l and of<=r) ustaw(of, os); //jesli jest w przedziale to aktualizujemy wynik
    else tab[of] = os; //jesli nie to tylko zmieniamy
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n, q, a, b, typ, upd = 0, in = 0, x, zmienna_kompresyjna = 1;
    cin >> n >> q;
    if(n==100000) s = 3000;
    else s = cbrt(n*n);
    for(int i = 1; i<=n; i++){ 
        cin >> x;
        if(!kompresja[x]){ //zeby funkcje dzialaly w O(1) a nie O(logn)
            kompresja[x]=zmienna_kompresyjna;
            x = zmienna_kompresyjna;
            zmienna_kompresyjna++;
        }
        else x = kompresja[x];
        tab[i] = x;
        g[i] = x;
    }
    query zap[q+5];
    update.push_back({0, {0, 0}});
    for(int i = 0; i<q; i++){
        cin >> typ >> a >> b;
        if(typ==1){
            zap[in].l = a;
            zap[in].r = b;
            zap[in].ind = in;
            zap[in].up = upd;
            in++;
        }
        else{
            if(!kompresja[b]){
                kompresja[b] = zmienna_kompresyjna;
                b = zmienna_kompresyjna;
                zmienna_kompresyjna++;
            }
            else b = kompresja[b];
            update.push_back({a, {b, g[a]}});
            g[a] = b;
            upd++;
        }
    }
    sort(zap, zap+in, comparator);
    int cur_l = 0, cur_r = -1, cur_up = 0;
    for(int i = 0; i<in; i++){
        int l = zap[i].l, r = zap[i].r, indeks = zap[i].ind, akt = zap[i].up;
        while(cur_l>l){
            cur_l--;
            if(cur_l!=0)add(tab[cur_l]);
        }
        while(cur_r<r){
            cur_r++;
            if(cur_r!=0)add(tab[cur_r]);
        }
        while(cur_l<l){
            if(cur_l!=0)sub(tab[cur_l]);
            cur_l++;
        }
        while(cur_r>r){
            if(cur_r!=0)sub(tab[cur_r]);
            cur_r--;
        }
        while(cur_up<akt){
            cur_up++;
            funckja_aktualizacyjna(l, r, update[cur_up].first, update[cur_up].second.first);
        }
        while(cur_up>akt){
            funckja_aktualizacyjna(l, r, update[cur_up].first, update[cur_up].second.second);
            cur_up--;
        }
        for(int j = 1; j<500; j++){
            if(!mexy[j]){
                wyniki[indeks] = j;
                break;
            }
        }
    }
    for(int i = 0; i<in; i++) cout << wyniki[i] << '\n';
    return 0;
}