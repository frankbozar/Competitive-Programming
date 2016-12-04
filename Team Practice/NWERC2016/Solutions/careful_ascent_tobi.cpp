#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;
int x, y, n, shielded, shields[100][2];
double factor[100];

int main() {
	cin >> x >> y >> n;
	for (int i = 0; i < n; i++) {
		cin >> shields[i][0] >> shields[i][1] >> factor[i];
		shielded += shields[i][1] - shields[i][0];
	}
	double a = 0, o = abs(x)*100, mid = -1;
	for (int i = 0; i < 128; i++) {
		mid = (a+o)/2.;
		double pos = mid*(y-shielded);
		for (int j = 0; j < n; j++) pos += mid * factor[j] * (shields[j][1] - shields[j][0]);
		if (pos < abs(x)) a = mid;
		else o = mid;
	}
	cout << setprecision(12) << (x < 0 ? -mid : mid) << endl;
	return 0;
}
