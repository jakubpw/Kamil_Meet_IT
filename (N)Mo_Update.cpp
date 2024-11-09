#include <bits/stdc++.h>
using namespace std;

int Q; //odpowiedzia bedzie największe n(+1) dla którego n*(n+1)/2 <= rozmiaru tablicy, bo żeby je zwiększyć musi być 1 element x1, dwa elementy x2
//itd, ale to chyba nie ma znaczenia
const int N = 100005;
int s;

int tab[N] = {0};
int tw[N] = {0};  //tablica z ilościami wystąpień liczb
int tww[N] = {0}; // tablica z ilością wystąpień wystąpień liczby (ity element oznacza ile liczb wystepowalo i razy)
int wyniki[N] = {0};
set<int> mx; //set z wartosciami ktorych nie ma w zbiorze
vector<pair<int, pair<int, int>>> update; //{indeks, {zmiana wartosci}, poprzednia wartosc}
vector<int> g[N]; //bedzie trzymac wartosci kolejnych aktualizacji dla itego elementu

struct query{
    int l;
    int r;
    int ind;
    int up; //ilosc aktualizacji
};

bool comparator(query q1, query q2){
    int block_a = q1.l/s, block_b = q2.l/s;
    int block_1 = q1.r/s, block_2 = q2.r/s;
    if(block_a==block_b){
        if(block_1==block_2){
            return q1.up < q2.up;
        }
        return q1.r < q2.r;
    }
    return block_a < block_b;
}

void add(int a){
    if(a<Q){
        tw[a]++; //zwiekszenie ilosci liczby wystepowan
        mx.erase(tw[a]); //na pewno wieksza od 0, wiec wypada
        tww[tw[a]]++; //zwiekszenie ilosci wystepowan wystepowan nowej wartosci
        tww[tw[a]-1]--; //zmiejszenie ilosci wystepowan poprzedniej 
        if(tww[tw[a]-1]==0)mx.insert(tw[a]-1); //jesli teraz nie ma zadnej, to wrzucic na seta
        mx.erase(0); //na wypadek 
    }
}

void sub(int a){
    if(a<Q){
        tw[a]--; //zmniejszenie ilosci liczby wystepowan
        tww[tw[a]]++; //zwiekszenie ilosci wystepowan wystepowan nowej wartsci
        mx.erase(tw[a]); // wyrzucenie z seta nowej wartosci bo wiecej niz 0
        tww[tw[a]+1]--; // zmniejszenie wartosci wystepowan oryginalnej wartosci
        if(tww[tw[a]+1]==0)mx.insert(tw[a]+1); //jesli nie ma zadnej, to wrzucic na seta 
        mx.erase(0);
    }
}

void ustaw(int i, int j){
    if(tab[i]==j)return; //jesli wartosc ta sama nie ma po co cokolwiek zmieniac
    sub(tab[i]); //tak jak opisane wyzej
    tab[i] = j; //ustawic obecna wartosc na nowa
    add(tab[i]); //tak jak wyzej
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q, a, b, typ, upd = 0, in = 0;
    cin >> n >> q;
    Q = n+1;
    s = sqrt(n);
    for(int i = 1; i<=Q; i++) mx.insert(i);
    for(int i = 1; i<=n; i++){ 
        cin >> tab[i];
        g[i].push_back(tab[i]); // pierwsza "warstwa" bedzie oryginalna tablica
    }
    query zap[q+5];
    update.push_back({0, {0, 0}}); // aby indeksowac aktualizacje od 1
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
            upd++;
            update.push_back({a, {b, g[a][g[a].size()-1]}}); //na poprzednią wartość dawana jest ostatnia obecnie
            g[a].push_back(b); //po czym pchana jest obecna
        }
    }
    sort(zap, zap+in, comparator);
    int cur_l = 0, cur_r = -1, cur_up = 0;
    for(int i = 0; i<in; i++){
        while(cur_up<zap[i].up){
            ustaw(update[cur_up+1].first, update[cur_up+1].second.first);
            cur_up++;
        }
        while(cur_up>zap[i].up){
            ustaw(update[cur_up].first, update[cur_up].second.second);
            cur_up--;
        }
        
        while(cur_l>zap[i].l){
            cur_l--;
            if(cur_l!=0)add(tab[cur_l]);
        }
        while(cur_r<zap[i].r){
            cur_r++;
            if(cur_r!=0)add(tab[cur_r]);
        }
        while(cur_l<zap[i].l){
            if(cur_l!=0)sub(tab[cur_l]);
            cur_l++;
        }
        while(cur_r>zap[i].r){
            if(cur_r!=0)sub(tab[cur_r]);
            cur_r--;
        }
        wyniki[zap[i].ind] = *mx.begin();
    }
    for(int i = 0; i<in; i++) cout << wyniki[i] << '\n';
    return 0;
}