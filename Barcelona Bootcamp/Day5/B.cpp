#include<cmath>
#include<cstdio>
#include<complex>
using namespace std;
typedef complex<double> cplx;
typedef long long lld;
const double PI=acos(-1);
const int MAXN=1<<21;
const int maxn=MAXN-1;

void FFT(cplx a[],int rev) {
    int n=MAXN;
    
    for(int i=0,j=0;i<n;++i) {
        if(i>j) std::swap(a[i],a[j]);
        for(int k=n>>1;(j^=k)<k;k>>=1);
    }
    
    for(int i=2;i<=n;i<<=1) {
        int m=i>>1;
        cplx g(cos(PI/m),rev*sin(PI/m));
        for(int j=0;j<n;j+=i) {
            cplx w(1.0,0.0);
            for(int k=0;k!=m;k++) {
                cplx z=a[j+m+k]*w;
                a[j+m+k]=a[j+k]-z;
                a[j+k]=a[j+k]+z;
                w=w*g;
            }
        }
    }
    
    if(rev==-1) {
        for(int i=0;i<n;i++) a[i]/=n;
    }
}

inline lld powmod(lld x, lld p, lld m)
{
    lld ans=1;
    
    for(; p>0; p>>=1)
    {
        if( p&1 )
            ans=ans*x%m;
        
        x=x*x%m;
    }
    
    return ans;
}

cplx a[MAXN+1]={0};
double b[MAXN+1]={0};

int main()
{
    
    
    //prefft();
    lld n, m;
    scanf("%lld%lld", &n, &m);
    
    for(lld i=1; i<m; i++)
        b[powmod(i, n, m)]++;
    
    for(int i=0; i<MAXN; i++)
        a[i]=b[i];
    
    FFT(a, 1);
    
    for(int i=0; i<MAXN; i++)
        a[i]*=a[i];
    
    FFT(a, -1);
    double ans=(round(a[0].real()+a[m].real()))*b[0];
    
    for(int i=1; i<m; i++)
    {
        ans+=b[(powmod(i, n, m)<<1)%m];
        ans+=(round(a[i].real()+a[i+m].real()))*b[i];
    }
    
    printf("%.0f\n", ans/2);
}

/*

1 3
2 4
3 5

*/
