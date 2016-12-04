#include <iostream>
#include <iomanip>
using namespace std;

typedef long double ld;

int l[100], u[100];
ld f[100];

int main(){

	ld x,y; cin>>x>>y;
	int s; cin>>s;
	int g = 0;
	ld m = 0;
//cout<<"x is "<<x<<", y is "<<y<<"\n";
	for(int i = 0; i < s; ++i) {
		cin>>l[i]>>u[i];
		cin>>f[i];
//cout<<"i="<<i<<", lower="<<l[i]<<", upper="<<u[i]<<", power="<<f[i]<<"\n";
		m = m + (l[i] - g);
//cout<<"m="<<m<<"\n";		
		g = u[i];
//cout<<"g is now="<<g<<'\n';
		ld d = u[i] - l[i];
		m = m + (f[i] * d);
//cout<<"m="<<m<<"\n";		
	}
	m = m + (y - g);
//cout<<"m="<<m<<"\n";
	cout.precision(10);
	cout<<x/m<<'\n';
}
