#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

const int N = 1e5+5;

int KMR[N][20] = {0};
int suf[N] = {0};

vector<pair<int, int> > tad[N+2];
vector<pair<int, int> > rad[N+2];

string S;

void preprocess(int n){
    int alfabet = 0;
    for(int i = 0; i<n; i++) KMR[i][0] = S[i]-'0';
    pair<int, pair<int, int> > pomoc[n+2];
    int r = log2(n)+1, pot = 1;
    for(int x = 1; x<=r; x++){
        for(int i = 0; i<n; i++){
            if(i+pot>=n) pomoc[i] = make_pair(KMR[i][x-1], make_pair(-1, i));
            else pomoc[i] = make_pair(KMR[i][x-1], make_pair(KMR[i+pot][x-1], i));
            alfabet = max(alfabet, max(KMR[i][x-1], KMR[i+pot][x-1]));
        }
        alfabet++;
        for(int i = 0; i<n; i++){
            int e = pomoc[i].se.fi+1, s = pomoc[i].fi, ind = pomoc[i].se.se;
            tad[e].push_back({s, ind});
        }
        for(int e = 0; e<=alfabet; e++){
            for(auto a : tad[e]){ 
                int s = a.fi, ind = a.se;
                rad[s].push_back({e-1, ind});
            }
            tad[e].clear();
        }
        int c = 0;
        for(int s = 0; s<=alfabet; s++){
            for(auto a : rad[s]){
                int e = a.fi, ind = a.se;
                pomoc[c] = {s, {e, ind}}; 
                c++;
            }
            rad[s].clear();
        }
        pair<int, int> pom = make_pair(-1,-1);
        int ile = -1;
        for(int i = 0; i<n; i++){
            if(pom.fi != pomoc[i].fi or pom.se != pomoc[i].se.fi){
                pom = make_pair(pomoc[i].fi, pomoc[i].se.fi);
                ile++;
            }
            KMR[pomoc[i].se.se][x] = ile;
        }
        pot *= 2;
        
    }
    for(int i = 0; i<n; i++) suf[KMR[i][r]] = i;
    for(int i = 0; i<n; i++) cout << suf[i] << '\n';
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> S;
    preprocess(S.length());
    return 0;
}