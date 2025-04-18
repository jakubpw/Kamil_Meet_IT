#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 2e7+5;

int d[N], n[N], r[N];
bool prime[N], game[N];

void loop(int i){
	r[i] = 2;
	for(ll j = i*i; j<N; j+=i){
		prime[j] = true;
		if(d[j]!=0) continue;
		int counter = 0, number = j, p = 1;
		while(number%i==0){
			counter++;
			number/=i;
			p*=i;
		}
		d[j] = counter;
		n[j] = p;
	}
}

void preprocess(){
	r[1] = 1;
	game[1] = game[2] = 0;
	game[3] = 1;
	loop(2);
	for(ll i = 3; i*i<N; i+=2){
		if(!prime[i]) loop(i);
	}
	int prev = 3;
	for(int i = 4; i<N; i++){
		if(!prime[i]) r[i] = 2;
		else r[i] = (d[i]+1) * r[i/n[i]];
		if(i-prev<=r[i]) game[i] = 0;
		else{
			game[i] = 1;
			prev = i;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	preprocess();
	int T, x;
	cin >> T;
	while(T--){
		cin >> x;
		if(!game[x]) cout << "Ada\n";
		else cout << "Vinit\n";
	}
	return 0;
} 