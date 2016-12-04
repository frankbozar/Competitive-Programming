#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

struct Room {
	int number;
	int students;

	Room(int n, int s) : number(n), students(s) {}
};

struct largest_r {
	inline bool operator() (const Room& r1, const Room& r2) {
		return (r1.students > r2.students);
	}
};

struct sum_r {
	inline int operator() (int sum, const Room& r1) {
		return sum + r1.students;
	}
};


int main(){

	int r; cin>>r;
	vector<Room> s;

	for(int i = 0; i< r; ++i) {
		int st; cin>>st; 
		s.push_back(Room(i, st));
	}

	// sort the rooms.
	sort(s.begin(), s.end(), largest_r());

	int sum = std::accumulate(s.begin()+1, s.end(), 0, sum_r());

	if (s[0].students > sum) {
		cout<<"impossible\n";
	}
	else {
		for(int j = 0; j < r; j++) {
			cout<<(s[j].number + 1)<<' ';
		}
		cout<<'\n';
	}
}