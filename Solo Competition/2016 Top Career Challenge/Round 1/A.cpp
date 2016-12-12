#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int length(int x)
{
    char s[16]={0};
    sprintf(s, "%d", x);
    return strlen(s);
}

void print(int n, int k)
{
    printf("+");
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<k; j++)
            printf("-");
            
        printf("+");
    }
    
    printf("\n");
}

void solution(vector<int> &a, int k)
{
    int n=a.size();
    int l=0;
    
    for(int i=0; i<n; i++)
        l=max(l, length(a[i]));
    
    print(min(n, k), l);
    
    for(int i=0; i<n; i+=k)
    {
        printf("|");
        
        for(int j=i; j<min(n, i+k); j++)
            printf("%*d|", l, a[j]);
        
        printf("\n");
        print(min(n-i, k), l);
    }
}

int main()
{
    for(; ; )
    {
        int n, k;
        scanf("%d%d", &n, &k);
        vector<int> a(n);
        
        for(int i=0; i<n; i++)
            scanf("%d", &a[i]);
        
        solution(a, k);
        printf("\n");
    }
}

/*

1 1
1000000000

5 1
111111 1111111 11111111 111111111 1000000000

12 4
4 35 80 123 12345 44 8 5 24 3 22 35

12 3
4 35 80 123 12345 44 8 5 24 3 22 35

12 10
4 35 80 123 12345 44 8 5 24 3 22 35

12 100
4 35 80 123 12345 44 8 5 24 3 22 35

*/