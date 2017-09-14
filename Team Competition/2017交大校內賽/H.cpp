#include<cmath>
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef double lld;
#define point pair<lld,lld>
#define x first
#define y second
point a[1<<11];

lld f(const point& A, const point& B, const point& C)
{
    double a=B.x-A.x, b=B.y-A.y, c=C.x-A.x, d=C.y-A.y;
    return fabs(a*d-c*b);
    lld ans=0;
    ans+=A.x*B.y;
    ans+=B.x*C.y;
    ans+=C.x*A.y;
    ans-=B.x*A.y;
    ans-=C.x*B.y;
    ans-=A.x*C.y;
    return ans<0 ? -ans : ans;
}

int main()
{
    int N;

    for(cin>>N; N>0; N--)
    {
        int n;
        cin>>n;
        lld ans=0;

        for(int i=0; i<n; i++)
            cin>>a[i].x>>a[i].y;

        for(int i=0; i<n; i++)
        {
            for(int k=(i+1)%n, j=k; j!=i; j=(j+1)%n)
            {
                lld tmp=0;

                for(lld nxt; (k+1)%n!=i && tmp<=(nxt=f(a[i], a[j], a[(k+1)%n])); k=(k+1)%n)
                {
                    ans=max(ans, nxt);
                    tmp=nxt;
                }
printf("n=%d   %d %d %d %f\n", n, i, j, k, f(a[i], a[j], a[(k)%n]));
                ans=max(ans, tmp);
            }
        }
            printf("aaa %f\n", ans);
        srand(126);
        for(int l=0; l<60000000; l++)
            {
                int q=rand()%n, w=rand()%n, e=rand()%n;
                if(ans<f(a[q], a[w], a[e]))
                {
                    ans=f(a[q], a[w], a[e]);
                    printf("~~~%d %d %d\n", q, w, e);


                }
            }
            printf("aaa %f\n", ans);
        for(int i=0; i<n; i++)
            ans=max(ans, f(a[i], a[(i+1)%n], a[(i+2)%n]));
            printf("aaa %f\n", ans);


        /*
        for(int i=0; i<n-i-1; i++)
            swap(a[i], a[n-i-1]);

        for(int i=0; i<n; i++)
        {
            for(int k=(i+1)%n, j=k; j!=i; j=(j+1)%n)
            {
                lld tmp=0;

                for(lld nxt; (k+1)%n!=i && tmp<=(nxt=f(a[i], a[j], a[(k+1)%n])); k=(k+1)%n)
                {
                    ans=max(ans, nxt);
                    tmp=nxt;
                }

                ans=max(ans, tmp);
            }
        }

        printf("%.20f\n", ans/2);
*/
cout<<ans/2<<endl;

    }
}

/*

1
8
1 0
2 0
3 1
3 2
2 3
1 3
0 2
0 1

*/


/*

2

3
0.3 0.3
1.3 1.3
0.3 2.3

4
0 0
1 0
1 1
0 1

*/
