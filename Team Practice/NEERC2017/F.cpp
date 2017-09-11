#include<cstdio>
#include<map>
using namespace std;
const int INF=1<<30;
#define data pair<int,int>
#define x first
#define y second

int sol(int W, int H, int w, int h)
{
    if( W>w || H>h )
        return INF;
    else if( W==w && H==h )
        return 0;
    
    static map<data, int> M;
    data key(w, h);
    
    if( M.find(key)==M.end() )
    {
        int &ans=M[key];
        ans=INF;
        ans=min(ans, sol(W, H, max(W, w-(w>>1)), h)+1);
        ans=min(ans, sol(W, H, w, max(H, h-(h>>1)))+1);
        ans=min(ans, sol(W, H, h, max(H, w-(w>>1)))+1);
        ans=min(ans, sol(W, H, max(W, h-(h>>1)), w)+1);
    }
    
    return M[key];
}

int main()
{
    freopen("folding.in", "rb", stdin);
    freopen("folding.out", "wb", stdout);
    int w, h, W, H;
    scanf("%d%d%d%d", &w, &h, &W, &H);
    int ans=min(sol(W, H, w, h), sol(W, H, h, w));
    printf("%d\n", ans>=INF ? -1 : ans);
}
