#include <iostream>

typedef long long ll;

using namespace std;

ll idx(ll v, ll p, ll acc) {
	if (v == 0) return acc;

	ll r  = (v % 2) ? p + (p-acc-1) : acc;
	return idx(v / 2, p*2, r);
}

ll stob(string s){
	ll x = 0;
	for (int i = 0; i < s.size(); i++) x = x*2 + (s[i] - '0');
	return x;
}

int main(){
	ll n; string a,b;
	cin >> n >> a >> b;
	cout << (idx(stob(b),1,0) - idx(stob(a),1,0) - 1) << endl;
}
