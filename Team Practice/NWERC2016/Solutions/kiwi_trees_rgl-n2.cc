#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

struct vec2{
  ld x,y;
  vec2 operator-(vec2 const a)const{return {x-a.x,y-a.y};}
  ld cz(vec2 const a)const{return y*a.x-x*a.y;}
};
vec2 unit(vec2 const a){ld const l=hypotl(a.x,a.y);return {a.x/l,a.y/l};}
ld dot(vec2 const a,vec2 const b){return a.x*b.x+a.y*b.y;}

int main(){
  int n; cin>>n;
  vector<vec2> v(n); for (auto &i: v) cin>>i.x>>i.y;
  vector<int> cav,vex;
  for (int a=0,b=1,c=2,i=0; i<n; ++i,a=b,b=c,(++c)%=n){
    ((v[c]-v[b]).cz(v[b]-v[a])<=0? vex: cav).push_back(b);
  }
  vector<vec2> res;
  for (auto b: vex){
    int a=(b+n-1)%n,c=(b+1)%n;
    vec2 s=unit(v[a]-v[b]),t=unit(v[c]-v[b]),p={s.x+t.x,s.y+t.y};
    bool ok=true;
    for (auto i: cav)
      if ((v[i]-v[a]).cz(v[b]-v[a])<0 and
          (v[i]-v[b]).cz(v[c]-v[b])<0 and
          (v[i]-v[c]).cz(v[a]-v[c])<0) {ok=false;break;}
    if (ok){
      ld const m=(4000+1e-7L)/min(abs(p.cz(t)),abs(p.cz(s))); p.x*=m,p.y*=m;
      p.x+=v[b].x,p.y+=v[b].y;
      res.push_back(p);
    }
  }
  cout.precision(12);
  for (int i=res.size(); i--;)
    for (int j=i; j--;)
      if (hypotl(res[i].x-res[j].x,res[i].y-res[j].y)>(4000-1e-7L)*2){
        cout<<res[i].x<<" "<<res[i].y<<"\n"<<res[j].x<<" "<<res[j].y<<endl;
        return 0;
      }
  cout<<"impossible"<<endl;
}
