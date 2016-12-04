#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define DBG(x)

int constexpr exp_catch = 100;
int constexpr exp_evolve = 500;
int constexpr egg_time = 1800;

struct MonsterTree{
  vector<ll> potential; // cumulative sweets for level X+1
  vector<ll> f; // sum of monsters <= i
  vector<ll> c; // count of monsters <= i
  vector<ll> s; // sum of x of monsters <= i
  int count;

  explicit MonsterTree(vector<int> const &ch){
    potential={0}; for (auto i: ch) potential.push_back(potential.back()+i);
    f=c=s=vector<ll>(potential.size());
    count=0;
  }

  void add_monster(int x){
    ++count;
    for (int i=x; i<f.size(); i|=i+1){
      f[i]+=potential[x];
      c[i]++;
      s[i]+=x;
    }
  }

  tuple<ll,ll,ll> get_total(int x){
    tuple<ll,ll,ll> res={};
    for (int i=x; i>=0; --(i&=i+1)){
      get<0>(res)+=f[i];
      get<1>(res)+=c[i];
      get<2>(res)+=s[i];
    }
    return res;
  }

  ll get_points(){
    return count*4-1;
  }

  int get_promotions(ll points){
    int baseline=-1;
    tuple<ll,ll,ll> pb;
    for (int rad=(1<<20); rad; rad>>=1) if (baseline+rad<potential.size()){
      int mid=(baseline+rad);
      auto pm=pb; get<0>(pm)+=f[mid]; get<1>(pm)+=c[mid]; get<2>(pm)+=s[mid];
      ll needed=potential[mid]*get<1>(pm)-get<0>(pm);
      if (needed<=points) baseline=mid, pb=pm;
    }
    assert(baseline>=0);
    auto p=pb;

    // How many do we have at exactly `baseline` now?
    int active=get<1>(p);

    // How many promotions did we make?
    int promoted=active*baseline-get<2>(p);

    // How many points do we have left?
    points-=(potential[baseline]*get<1>(p)-get<0>(p));

    // Use remaining points to promote as many as possible
    if (baseline+1<potential.size()){
      // Guaranteed not to promote all of them (or baseline would be higher)
      promoted+=points/(potential[baseline+1]-potential[baseline]);
    }

    return promoted;
  }
};

int main(){
  // Big book of monsters.
  map<string,pair<int,int>> monster_names;

  // Read in monster chains
  vector<vector<int>> chain;
  int chains; cin>>chains; chain.resize(chains);
  for (int i=0; i<chains; i++){
    int chen; cin>>chen;
    for (int j=0; j<chen; j++){
      int cost; if (j) cin>>cost, chain[i].push_back(cost);
      string nom; cin>>nom;
      monster_names[nom]={i,j};
    }
  }

  // Read in capture events
  int n_caught; cin>>n_caught;
  vector<pair<int,pair<int,int>>> event(n_caught);
  for (auto &i: event){
    int t; string nom; cin>>t>>nom;
    i={t,monster_names[nom]};
  }

  ll res=0;

  vector<MonsterTree> mash;
  for (auto &i: chain) mash.emplace_back(MonsterTree(i));

  ll answer_so_far=0;
  vector<ll> monster_answer(chain.size(),0ll);

  for (int i=0,j=0; i<event.size(); i++){
    while (j<event.size() and event[j].first<event[i].first+egg_time){
      int cid=event[j].second.first;
      int mid=event[j].second.second;
      mash[cid].add_monster(mid);

      // Update answer by parts.
      ll nanswer=mash[cid].get_promotions(mash[cid].get_points());
      answer_so_far+=(nanswer-monster_answer[cid]);
      monster_answer[cid]=nanswer;

      ++j;
    }

    ll have=exp_catch*(j-i) + 2*exp_evolve*answer_so_far;
    DBG(cerr<<"score for "<<event[i].first<<"..."<<event[i].first+egg_time<<": "<<have<<endl);
    // Save answer and try again with the next start position.
    res=max(res,have);
  }

  // According to statement: we have to catch them all.
  res+=exp_catch*event.size();
  cout<<res<<endl;
}
