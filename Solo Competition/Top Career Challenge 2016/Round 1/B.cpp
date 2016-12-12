#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int solution(vector<int>& a)
{
    int n=a.size();
    vector<int> b=a;
    sort(b.begin(), b.end());
    int l, r;
    for(l=0; l<n && a[l]==b[l]; l++);
    for(r=n-1; r>=0 && a[r]==b[r]; r--);
    return max(r-l+1, 0);
}

int main()
{
    for(; ; )
    {
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        printf("%d\n", solution(a));
    }
}

/*

7
7 6 5 4 3 2 1

7
1 2 3 4 5 6 7

7
1 2 6 5 5 8 9

*/