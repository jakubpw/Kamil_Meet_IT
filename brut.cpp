#include <iostream>
#include <cmath>
using namespace std;

const int N = 1e6+5;

int tab[N] = {0};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int d, n, ls, rs, m = 0, ultram = 0;
    cin >> d >> n;
    for(int i = 0; i<n; i++){
        cin >> ls >> rs;
        int l = rs, r = rs+ls-1;
        for(int j = l; j++; j<=r){
            m = max(tab[j], m);
        }m++;
        if(m>ultram) ultram = m;
        for(int j = l; j++; j<=r){
            tab[j] = m;
        }
    }
    cout << ultram;
    return 0;
}