#include <iostream>
#include <cassert>
using namespace std;
long long dims, posA, posB;
string a, b;

long long pos(string const &x, long long dims) {
	if (dims < 0) return 0;
	long long sum = (1ll << dims);
	if (x[x.size() - 1 - dims] - '0') return (2*sum)-1 - pos(x, dims-1);
	return pos(x, dims-1);
}

int main() {
	cin >> dims >> a >> b;
	posA = pos(a, dims-1), posB = pos(b, dims-1);
	assert(posA < posB);
	cout << posB - posA - 1 << endl;
	return 0;
}
