#include<map>
#include<queue>
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
#define name pair<string,string>
#define f first
#define s second
const int INF=1<<30;

struct dinic{
    struct edge{
        int t, c, r;
        edge(int _t, int _c, int _r): t(_t), c(_c), r(_r){}
    };
    vector<int> l;
    vector<vector<edge>> e;
    dinic(int n) : e(n+1){}
    void add(int u, int v, int w){//directed
        e[u].push_back(edge(v, w, e[v].size()));
        e[v].push_back(edge(u, 0, e[u].size()-1));
    }
    edge& rev(const edge& E){
        return e[E.t][E.r];
    }
    bool bfs(int s, int t){
        l.assign(e.size(), INF);
        l[s]=1;
        queue<int> Q;
        for(Q.push(s); !Q.empty(); Q.pop()){
            s=Q.front();
            for(const edge& E : e[s])
                if( E.c>0 && l[E.t]>l[s]+1 ){
                    l[E.t]=l[s]+1;
                    Q.push(E.t);
                }
        }
        return l[t]<INF;
    }
    int dfs(int s, int t, int num){
        if( s==t || num==0 ) return num;
        int ans=0;
        for(edge& E : e[s])
            if( E.c>0 && l[s]+1==l[E.t] ){
                int flow=dfs(E.t, t, min(num, E.c));
                rev(E).c+=flow, ans+=flow;
                E.c-=flow, num-=flow;
            }
        return ans>0 ? ans : l[s]=0;
    }
    int operator()(int s, int t){
        int ans=0, tmp=0;
        while( bfs(s, t) )
            while( (tmp=dfs(s, t, INF)) )
                ans+=tmp;
        return ans;
    }
};

vector<string> solve(const vector<name>& a, int n)
{
    map<string, int> M;
    int m=0;
    
    for(const name& t : a)
        M[t.f]=M[t.s]=0;
    
    for(auto& it : M)
        it.second=m++;
    
    int S=n+m+m, T=S+1;
    dinic D(T+1);
    
    for(int i=0; i<n; i++)
    {
        int u=M[ a[i].s ];
        int v=M[ a[i].f ];
        D.add(S, i, 1);
        D.add(i, n+u, 1);
        D.add(n+u, n+m+v, 1);
        D.add(i, n+m+v, 1);
    }
    
    for(int i=0; i<m; i++)
        D.add(n+m+i, T, 1);
    
    if( D(S, T)!=n )
        return vector<string>(0);
    
    vector<string> ans(n, "!!!");
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<name> a;
    
    for(int i=0; i<n; i++)
    {
        string s, t;
        cin >> s >> t ;
        a.push_back(name(s.substr(0, 3), s.substr(0, 2)+t.substr(0, 1)));
    }
    
    vector<string> ans=solve(a, n);
    cout << (ans.size()==n ? "YES\n" : "NO\n") ;
    
    for(const string& s : ans)
        cout << s << '\n' ;
}
