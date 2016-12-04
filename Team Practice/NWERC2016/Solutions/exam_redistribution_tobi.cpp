#include <iostream>
#include <algorithm>

using namespace std;

int n, sum;
pair<int,int> students[100];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> students[i].first;
		students[i].second = i + 1;
		sum += students[i].first;
	}
	sort(students, students + n);
	if (sum - students[n-1].first < students[n-1].first) cout << "impossible" << endl;
	else {
		for (int i = 0; i < n; i++) cout << students[n-1 - i].second << " ";
		cout << endl;
	}
	return 0;
}
