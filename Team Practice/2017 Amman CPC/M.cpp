#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;

void update(vector<int>& a, int p, int n)
{
    multiset<int> S(a.begin(), a.end()), T;
        
    for(int x : a)
        if( S.find(x-p)==S.end() )
            T.insert(x);
    
    a.assign(T.begin(), T.end());
}

int main()
{
    int N;
    
    for(scanf("%d", &N); N>0; N--)
    {
        int n, s=0, l=0;
        scanf("%d", &n);
        vector<int> a;
        
        for(int i=0; i<n*(n-1)/2; i++)
        {
            int x;
            scanf("%d", &x);
            a.push_back(x);
            l=max(l, x);
        }
        
        printf("0");
        
        for(int k=n-1; k>0; k--)
        {
            int p=l;
            n=a.size();
            /*
            for(int x : a)
                printf(" %d", x);
            printf("\n");
            */
            for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    if( i!=j && a[i]!=0 && a[i]+a[j]==l )
                        p=min(p, a[i]);
            
            l-=p;
            s+=p;
            printf(" %d", s);
            update(a, p, k-1);
        }
        
        printf("\n");
    }
}
