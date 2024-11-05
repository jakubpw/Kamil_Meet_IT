#include <iostream>
#include <cmath>
using namespace std;

const int N = 1e6+5;

int sq;
int tab[N] = {0};
int kubelki[1005] = {0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int d, n, ls, rs, ultram = 0;//zmienna ultram będzie trzymać maksymalną wysokość
    cin >> d >> n;
    sq = (int) sqrt(d + .0) + 1;
    for(int i = 0; i<n; i++){
        cin >> ls >> rs;
        int l = rs, r = rs+ls-1; // żeby uniknąć problemu gdy spadają bokami na to samo miejsce numerować "pomiędzy" kreskami
                                // od 0 do d-1
        int blok_l = l/sq, blok_r = r/sq, m = 0;
        //m służy do przechowania największego indeksu na który spadnie rozpatrywany klocek
        if(blok_l==blok_r){ // w tym samym bloku
            for(int j = l; j<=r; j++) m = max(m, tab[j]);
            m++; // nowa wartość po dołożeniu obecnego klocka
            for(int j = l; j<=r; j++) tab[j] = m; //zwiekszanie
            kubelki[blok_l] = m; // tak samo z obecnym kubełkiem
        }
        else{
            //to co w 1, tylko inne kubełki
            for(int j = l, end = (blok_l+1)*sq-1; j<=end; j++) m = max(m, tab[j]); // lewy ogonek
            for(int j = blok_l+1; j<=blok_r-1; j++) m = max(kubelki[j], m); // kubelki
            for(int j = blok_r*sq; j<=r; j++) m = max(m, tab[j]); //prawy ogonek
            m++;
            kubelki[blok_l] = m; //maks w kubelku lewym, nie byl rozpatrywany caly, tylko czesc
            for(int j = l, end = (blok_l+1)*sq-1; j<=end; j++) tab[j] = m; //lewy ogonek
            for(int j = blok_l+1; j<=blok_r-1; j++) kubelki[j] = m; // kubelki
            for(int j = blok_r*sq; j<=r; j++) tab[j] = m;// prawy ogonek
            kubelki[blok_r] = m;//tak jak z lewym
        }
        if(m>ultram)ultram = m;//jesli m jest wieksze, to mamy nowy najlepszy wynik
    }
    cout << ultram;
    return 0;
}