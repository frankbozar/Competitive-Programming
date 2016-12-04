#include <iostream>
#include <cmath>
using namespace std;

typedef unsigned long long int uli;

uli gray_pos(int power, string pos, int idx) {
	uli max = pow(2, power);
	uli out = 0;
	
	if (power == 1) {
		out += pos[idx] == '1' ? 1 : 0;
	} else {
		if (pos[idx] == '1') {
			out += max - (gray_pos(power - 1, pos, idx+1) + 1); 
		} else {
			out += gray_pos(power - 1, pos, idx+1);
		}
	}

	return out;
}

int main(){

	int r; cin>>r;
	

	string from;cin>>from;
	string to; cin>>to;

	cout<<gray_pos(r, to, 0) - gray_pos(r, from, 0) - 1<<'\n';
}