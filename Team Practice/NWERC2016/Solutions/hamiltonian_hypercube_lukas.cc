//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <bitset>
using namespace std;

typedef long long ll;
ll id(bitset<64> a, int pos)
{
    if (pos == 0) return a[0];

    if (a[pos])
        return (1LL << (pos + 1)) - 1 - id(a, pos - 1);
    return id(a, pos - 1);
}
int main()
{
    int n; string da, db;
    cin >> n >> da >> db;
    bitset<64> a(da), b(db);
    ll dist = id(a, n - 1) - id(b, n - 1);
    cout << abs(dist) - 1 << endl;
}
