#include<cstdio>

int main()
{
    int n;
    scanf("%d", &n);
    
    for(int i=n>>1; i<n; i++)
        printf("%d ", n-i);
    
    for(int i=n>>1; i<n; i++)
        printf(i==n-1 ? "%d\n" : "%d ", (1<<30)|(i<<12));
}
