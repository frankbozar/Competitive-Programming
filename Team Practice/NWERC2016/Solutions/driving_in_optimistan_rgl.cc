#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef __int128 ll;

int n,dist[4000][4000];

ostream& operator<< (ostream& os, ll v){
    string s; do (s+=char((v%10)+'0')), v/=10; while (v);
    return os<<string(s.rbegin(),s.rend());
}

ll choose(ll n,ll k){return n? k? choose(n-1,k-1)*n/k: 1ll: !k;}

map<int,ll> child[2048];
ll card[2048];

void disambiguate(vector<int> const &v){
    if (v.size()<=1) return;

    int a=v[0],b=v[1+(rand()%(v.size()-1))];
    map<int,vector<int>> group;
    for (int z=0; z<2; z++)
        for (int i: v){
            int depth=(dist[i][a]+dist[i][b]-dist[a][b])/2;
            int offset=dist[i][a]-depth;
            switch (z){
                case 0: // first try to reuse an existing vertex
                    if (depth==0) group[offset]={i};
                    break;
                case 1: // if there wasn't an appropriate vertex, create one
                    if (group[offset].empty()) group[offset]={n++};
                    if (group[offset][0]!=i) group[offset].push_back(i);
                    dist[i][group[offset][0]]
                      =dist[group[offset][0]][i]
                      =depth;
                    break;
            }
        }

    auto j=&*group.begin();
    for (auto &i: group){
        if (j!=&i) child[j->second[0]][i.second[0]]=i.first-j->first;
        j=&i;
    }
    for (auto &i: group) disambiguate(i.second);
}

void cardinalise(int x){
    card[x]=1;
    for (auto j: child[x]) card[x]+=(cardinalise(j.first), card[j.first]+j.second-1);
}

ll vertices=0;

ll collect(int x,ll above_root){
    vertices+=1;
    ll res=0;
    for (auto const &j: child[x]){
        ll length=j.second;
        ll below=card[j.first];
        ll above=above_root+card[x]-below-length+1;

        res+=length*(above*below); // fully external
        res+=length*(length-1)/2*(above+below); // half-external
        res+=choose(length,3); // fully internal

        res+=collect(j.first,above_root+card[x]-card[j.first]);

        vertices+=length-1;
    }
    return res;
}

int main(){
    cin>>n;
    for (int i=0,z=0; i<n; (dist[i][i]=0), i++)
        for (int j=i+1; j<n; j++)
            cin>>dist[i][j], dist[j][i]=dist[i][j];

    vector<int> all(n);
    for (int i=n; i--;) all[i]=i;
    ll res=(disambiguate(all), cardinalise(0), collect(0,0));
    vertices=(vertices*(vertices-1))/2;
    cout.precision(16);
    cout<<fixed<<res/vertices+(res%vertices)/(long double)(vertices)<<endl;
}
