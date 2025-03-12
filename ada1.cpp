#include <bits/stdc++.h>

using namespace std;

int dp[10005][105]; 
int og;

vector<int> turn(int number){
	vector<int> res;
	int x = number, t = 1;
    while(t < 10000){
        int a = x%10;
        if(a==9)res.push_back(number-(t*9));
        else res.push_back(number+t);
        x /= 10;
        t *= 10;
    }
    return res;
}

bool gra(int number, bool kolej, int k){
	if(dp[number][k] != 2) return dp[number][k];
	if(k==0){
		if(number<=og)return 0;
		else return 1;
	}
	vector<int> turns = turn(number);
	for(int i = 0; i<turns.size(); i++){
		if(kolej and gra(turns[i], 1-kolej, k-1)) return dp[number][k] = 1;
		else if(!kolej and !gra(turns[i], 1-kolej, k-1)) return dp[number][k] = 0;
	}
	return dp[number][k] = 1-kolej;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T, t;
	cin >> T;
	while(T--){
		for(int i = 0; i<10005; i++){
			for(int j = 0; j<105; j++) dp[i][j] = 2;
		}
		cin >> og >> t;
		if(!gra(og, 1, t)) cout << "Vinit\n";
		else cout << "Ada\n";
	}
	return 0;
} 