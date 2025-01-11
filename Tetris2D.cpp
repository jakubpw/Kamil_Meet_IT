#include <iostream>
#include <cmath>
using namespace std;

const int N = 1e6+5;

int sq;
int tab[N] = {0};
int kubelki[1005] = {0};
int ff[1005] = {0};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int d, n, ls, rs, ultram = 0;
    cin >> d >> n;
    sq = (int) sqrt(d + .0) + 1;
    for(int i = 0; i<n; i++){
        cin >> ls >> rs;
        int l = rs, r = rs+ls-1, blok_l = l/sq, blok_r = r/sq, m = 0;
        if(blok_l==blok_r){
            if(ff[blok_l]==0) for(int j = l; j<=r; j++){ m = max(m, tab[j]);}
            else m = ff[blok_l];

            m++;

            if(l%sq==0 and (r+1)%sq==0){ 
                ff[blok_l] = m;
                kubelki[blok_l] = m;
            }
            else{
                if(ff!=0){
                    for(int j = blok_l*sq; j<l; j++) tab[j] = ff[blok_l];
                    for(int j = r+1; j<(blok_r+1)*sq; j++) tab[j] = ff[blok_l];
                    ff[blok_l] = 0;
                }
                for(int j = l; j<=r; j++) tab[j] = m;
                kubelki[blok_l] = max(m, kubelki[blok_l]);
            }
        }
        else{
            //LEWY OGON
            if(ff[blok_l]==0) for(int j = l; j<=(blok_l+1)*sq-1; j++) m = max(m, tab[j]);
            else m = ff[blok_l];
            //SRODEK
            for(int j = blok_l+1; j<=blok_r-1; j++) m = max(kubelki[j], m); 
            //PRAWY OGON
            if(ff[blok_r]==0) for(int j = blok_r*sq; j<=r; j++) m = max(m, tab[j]);
            else m = max(ff[blok_r], m);

            m++;

            //DOPELNIENIA
            if(ff[blok_l]!=0){
                for(int j = blok_l*sq; j<l; j++) tab[j] = ff[blok_l];
                ff[blok_l] = 0;
            }
            if(ff[blok_r]!=0){
                for(int j = r+1; j<(blok_r+1)*sq; j++) tab[j] = ff[blok_r];
                ff[blok_r] = 0;
            }
            //LEWY OGON
            for(int j = l; j<=(blok_l+1)*sq-1; j++) tab[j] = m;
            //SRODEK
            for(int j = blok_l+1; j<=blok_r-1; j++){
                kubelki[j] = m;
                ff[j] = m;
            }
            //PRAWY OGON
            for(int j = blok_r*sq; j<=r; j++) tab[j] = m;

            kubelki[blok_l] = max(kubelki[blok_l], m);
            kubelki[blok_r] = max(kubelki[blok_r], m);
        }
        ultram = max(m, ultram);
    }
    cout << ultram;
    return 0;
}