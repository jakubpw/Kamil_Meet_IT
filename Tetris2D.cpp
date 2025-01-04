#include <iostream>
#include <cmath>
using namespace std;

const int N = 1e6+5;

int sq;
int tab[N] = {0};
int kubelki[1005] = {0};
int ff[1005] = {0};

int bloki(int i){
    return i/sq;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int d, n, ls, rs, ultram = 0;
    cin >> d >> n;
    sq = (int) sqrt(d + .0) + 1;
    for(int i = 0; i<n; i++){
        cin >> ls >> rs;
        int l = rs, r = rs+ls-1;
        int blok_l = bloki(l), blok_r = bloki(r), m = 0;
        if(blok_l==blok_r){
            if(ff[blok_l]==0) m = kubelki[blok_l];
            else for(int j = l; j<=r; j++) m = max(m, tab[j]);
            m++;
            for(int j = blok_l*sq; j<l; j++) tab[j] = kubelki[blok_l];
            for(int j = l; j<=r; j++) tab[j] = m;
            for(int j = r+1; j<(blok_r+1)*sq; j++) tab[j] = kubelki[blok_l];
            kubelki[blok_l] = max(m, kubelki[blok_l]);
            ff[blok_l] = 1;
        }
        else{
            int lewo = l, prawo = r;
            if(ff[blok_l]==0) m = kubelki[blok_l];

            while(bloki(l)==blok_l){
                m = max(m, tab[l]);
                l++;
            }
            while(bloki(r)==blok_r){
                m = max(m, tab[r]);
                r--;
            }
            for(int j = blok_l+1; j<blok_r; j++) m = max(kubelki[j], m); 
            if(ff[blok_r]==0) m = max(kubelki[blok_r], m); 

            m++;
            ff[blok_l] = 1; ff[blok_r] = 1; l = lewo, r = prawo;

            //lewe dopelnienie
            for(int j = blok_l*sq; j<l; j++) tab[j] = kubelki[blok_l];
            //prawe dopelnienie
            for(int j = r+1; j<(blok_r+1)*sq; j++) tab[j] = kubelki[blok_l];
            //lewy ogon
            while(bloki(l)==blok_l){
                tab[l] = m;
                l++;
            }
            //prawy ogon
            while(bloki(r)==blok_r){
                tab[r] = m;
                r--;
            }
            //bloki
            for(int j = blok_l+1; j<blok_r; j++){
                kubelki[j] = m;
                ff[j] = 0;
            }
            kubelki[blok_l] = max(kubelki[blok_l], m);
            kubelki[blok_r] = max(kubelki[blok_r], m);
        }
        ultram = max(ultram, m);
    }
    cout << ultram;
    return 0;
}