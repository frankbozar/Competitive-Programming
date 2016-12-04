#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

constexpr bool debug_edges=false;
constexpr bool debug_polygons=false;
constexpr bool debug_triangles=false;

constexpr ld epsilon=0.201L;

struct vec2{
  ld x,y;
  int id;
  bool operator<(vec2 const &a)const{
    return x!=a.x? x<a.x: y<a.y;
  }
  vec2 operator-(vec2 const a)const{return {x-a.x,y-a.y,id};}
  ld cz(vec2 const a)const{return y*a.x-x*a.y;}
  vec2 perp()const{return {y,-x};}
};
vec2 unit(vec2 const a){ld const l=hypotl(a.x,a.y);return {a.x/l,a.y/l};}
ld dot(vec2 const a,vec2 const b){return a.x*b.x+a.y*b.y;}

struct Line{
  static ld current_x;
  vec2 s,t;

  ld eval(ld x)const{
    cerr.precision(16);
    //cerr<<"evaluating "<<fixed<<s.x<<" "<<s.y<<" => "<<t.x<<" "<<t.y<<" @ "<<x<<" ("<<current_x<<")"<<endl;
    assert(s.x <= x+1e-8L and x <= t.x+1e-8L
        or t.x <= x+1e-8L and x <= s.x+1e-8L);
    return s.y + (t.y-s.y)*(x-s.x)/(t.x-s.x);
  }

  bool operator<(Line const &a)const{
    if (this==&a) return false;
    ld const xc=(max(min(s.x,t.x),min(a.s.x,a.t.x))+min(max(s.x,t.x),max(a.s.x,a.t.x)))/2.L;
    return eval(xc) < a.eval(xc);
  }
};
ld Line::current_x=0;

struct comp{
  bool operator()(Line const* const &a,Line const* const &b)const{
    //cerr<<"comparing "<<a<<" and "<<b<<endl;
    return a==b? false: (*a)<(*b);
  }
};

vec2 rotate(vec2 const v,ld const by){
  return {v.x*cosl(by)+v.y*sinl(by),
          v.y*cosl(by)-v.x*sinl(by)};
}

Line* gen_line(vec2 const a,vec2 const b){
  static Line lines[1000000];
  static int linen=0;
  return &(lines[linen++]={a,b});
}

ld angle(vec2 a,vec2 b,vec2 c){
  vec2 ab=unit(b-a);
  vec2 bc=unit(c-b);
  //a=unit(a), b=unit(b), c=unit(c);
  // Positive if BC is anticlockwise from AB
  // Negative if BC is clockwise from AB
  ld res=bc.cz(ab);
  if (dot(bc,ab)<0){
    if (res<0) res=-2-res;
    else res=2-res;
  }
  return res;
}

void print_triangles(vector<vec2> const &v, vector<tuple<int,int,int>> const &triangles){
  for (auto i: triangles){
    cerr<<"triangle: "<<get<0>(i)<<" "<<get<1>(i)<<" "<<get<2>(i)<<endl;
    cout<<v[get<0>(i)].x<<" "<<v[get<0>(i)].y<<"    "
        <<v[get<1>(i)].x<<" "<<v[get<1>(i)].y<<"    "
        <<v[get<2>(i)].x<<" "<<v[get<2>(i)].y<<endl;
    cerr<<v[get<0>(i)].x<<" "<<v[get<0>(i)].y<<"    "
        <<v[get<1>(i)].x<<" "<<v[get<1>(i)].y<<"    "
        <<v[get<2>(i)].x<<" "<<v[get<2>(i)].y<<" | "<<v[get<0>(i)].id<<endl;
  }
}

int main(){
  ld const theta=1.L;

  int n; cin>>n;
  vector<vec2> v(n); for (auto &i: v) cin>>i.x>>i.y, i=rotate(i,epsilon);

  /* HACK because points are given CW but expected CCW */ {
    ld area=0.L;
    for (int i=0,j=v.size()-1; i<v.size(); j=i++){
      area+=v[i].cz(v[j]);
    }
    cerr<<"Polygon area is "<<(area>0?"POSITIVE, not flipping":"NEGATIVE, so flipping")<<endl;
    if (area<0){
      reverse(v.begin(),v.end());
      for (int i=0; i<n; i++) v[i].id=i;
    }
  }

  // The edges we'll insert for use in creating monotone polygons
  vector<set<int>> all_edges(n);
  for (auto &i: v){
    all_edges[i.id].insert((i.id+1)%v.size());
  }

  for (int rev=2; rev--;){
    vector<pair<vec2,Line*>> events;
    for (int i=0,j=n-1; i<n; j=i++){
      auto l=gen_line(v[j],v[i]);
      if (v[j].x<v[i].x){
        // It's a lower bound, so add it to the list of lines
        events.push_back({v[j]-vec2{1*1e-10L,0},l});
        events.push_back({v[i]-vec2{2*1e-10L,0},l});
        //cerr<<"line exists: "<<v[j].x<<" "<<v[i].x<<endl;
      }else{
        events.push_back({v[i]-vec2{1*1e-10L,0},l});
        events.push_back({v[j]-vec2{2*1e-10L,0},l});
      }
    }
    sort(events.rbegin(),events.rend());

    map<Line const*,vec2,comp> most_recent_on_line;
    vector<vec2> todo=v;
    sort(todo.begin(),todo.end());
    for (auto const &i: todo){
      int a=(i.id+v.size()-1)%v.size();
      int b=(i.id+v.size()+1)%v.size();
      // cerr<<"v="<<a<<" "<<i.id<<" "<<b<<endl;
      //cerr<<"   "<<v[a].x<<" "<<v[a].y<<" | "<<i.x<<" "<<i.y<<" | "<<v[b].x<<" "<<v[b].y<<endl;

      bool is_join=(v[a].x<=i.x and v[b].x<=i.x and angle(v[a],i,v[b])<=0); // >#
      bool is_finish=(v[a].x<=i.x and v[b].x<=i.x and not is_join); // #>
      bool is_fork=(v[a].x>=i.x and v[b].x>=i.x and angle(v[a],i,v[b])<=0); // #<
      bool is_start=(v[a].x>=i.x and v[b].x>=i.x and not is_fork); // <#
      // cerr<<"we have a vertex at "<<i.x<<" join="<<is_join<<" fork="<<is_fork<<" start="<<is_start<<" | angle="<<angle(v[a],i,v[b])<<endl;

      // Put the sweepline just before contemporary events if we're about to fork (since we need
      // the data structures in their state prior to having added those events),
      // or if we're not about to fork then just after is fine.
      ld const tox=(is_fork? i.x-1e-9L: i.x+1e-9L);

      // Process events that are now behind the sweepline.
      while (not events.empty() and events.back().first.x<=tox){
        Line::current_x=events.back().first.x;
        // cerr<<" Visiting line "<<events.back().second->s.x<<" "<<events.back().second->t.x<<" at "<<events.back().first.x<<endl;
        if (most_recent_on_line.count(events.back().second)){
          most_recent_on_line.erase(events.back().second);
          // cerr<<"  (removing)"<<endl;
        }else{
          // cerr<<"  (updating to "<<events.back().first.id<<")"<<endl;
          most_recent_on_line[events.back().second]=events.back().first;
        }
        events.pop_back();
      }
      Line::current_x=tox;

      // Anything interesting happening?
      if (most_recent_on_line.empty()){
        assert(is_finish);
        continue;
      }

      if (not is_fork and not is_join){
        continue;
      }

      // Find the closest line beneath this vertex.
      Line this_vertex{vec2{i.x-1,i.y+1e-9L},vec2{i.x+1,i.y+1e-9L}};
      auto lit=most_recent_on_line.upper_bound(&this_vertex);
      assert(lit!=most_recent_on_line.begin() or is_join);
      if (lit==most_recent_on_line.begin()) continue;
      --lit;
      if (is_join){
        // cerr<<"Hooking up "<<i.x<<" "<<i.y<<" to "<<lit->first->s.x<<" "<<lit->first->t.x<<endl;
      }

      if (is_fork){
        // Make a line between this and that vertex
        // add_edge(lit->second,i);
        int a=lit->second.id;
        int b=i.id;
        // cerr<<"add edge "<<a<<" "<<b<<": "<<v[a].x<<" "<<v[a].y<<"   "<<v[b].x<<" "<<v[b].y<<endl;
        all_edges[a].insert(b);
        all_edges[b].insert(a);
        assert(a!=b);
      }else{
        // Mark this vertex as most recent on its chain
        lit->second=i;
      }
    }

    // OK, we're done with the current run. Negate X and repeat in the other direction.
    // Note we also need to reverse the list to keep the same winding order.
    for (auto &i: v) i.x*=-1,i.y*=-1;
    //,i.id=v.size()-1-i.id;
    //reverse(v.begin(),v.end());
  }

  // Debug edge generation
  if (debug_edges){
    for (int i=0; i<n; i++)
      for (auto j: all_edges[i]){
        cout<<v[i].x<<" "<<v[i].y<<"    "<<v[j].x<<" "<<v[j].y<<endl;
      }
  }

  // Holder for results. Should have N-2 entries by the end.
  vector<tuple<int,int,int>> triangles;

  /* Step 2: retrieve the monotone polygons by walking all edges */ {
    set<pair<int,int>> edges_todo;
    for (int i=0; i<n; i++){
      for (int j: all_edges[i]){
        edges_todo.insert({i,j});
      }
    }

    while (not edges_todo.empty()){
      vector<vec2> polygon;
      /* choose starting edge */ {
        auto const it=edges_todo.begin();
        polygon.push_back(v[it->first]);
        polygon.push_back(v[it->second]);
        edges_todo.erase(it);
      }
      // cerr<<"==="<<endl;
      for (;;){
        vec2 const a=polygon[polygon.size()-2];
        vec2 const b=polygon[polygon.size()-1];
        assert(not all_edges[b.id].empty());
        vec2 best=a;
        // cerr<<"choosing from "<<a.x<<" "<<a.y<<" => "<<b.x<<" "<<b.y<<endl;
        for (auto x: all_edges[b.id]){
          if (x!=a.id and x!=b.id){
            //cerr<<"    "<<v[x].x<<" "<<v[x].y<<" has angle "<<angle(a,b,v[x])<<endl;
          }
            if (x!=a.id and x!=b.id and
                (best.id==a.id or best.id==b.id or angle(a,b,v[x]) > angle(a,b,best))){
            best=v[x];
          }
        }
        assert(best.id!=a.id);
        assert(edges_todo.count({b.id,best.id}));
        edges_todo.erase({b.id,best.id});
        all_edges[b.id].erase(best.id);
        if (best.id==polygon[0].id){
          break;
        }else{
          polygon.push_back(best);
        }
      }

      // Debug for monotonisation
      if (debug_polygons){
        cout.precision(20);
        for (auto i: polygon) /*i=rotate(i,-epsilon),*/ cout<<"   "<<i.x<<" "<<i.y;
        cout<<endl;
        cerr.precision(20);
        for (auto i: polygon) /*i=rotate(i,-epsilon),*/ cerr<<"   "<<i.x<<" "<<i.y;
        cerr<<endl;
      }

      constexpr int STACK_HI=1;
      constexpr int STACK_LO=2;
      constexpr int STACK_BOTH=3;
      set<vec2> chain_lo,chain_hi;
      for (int j=polygon.size()-1,i=0; i<polygon.size(); j=i++){
        if (polygon[i].x>polygon[j].x) chain_lo.insert(polygon[j]), chain_lo.insert(polygon[i]);
        else                           chain_hi.insert(polygon[j]), chain_hi.insert(polygon[i]);
      }
      // cerr<<"==="<<endl;
      vector<pair<int,vec2>> open;
      for (auto it1=chain_lo.begin(),it2=chain_hi.begin(); it1!=chain_lo.end() or it2!=chain_hi.end();){
        if (it2==chain_hi.end() or (it1!=chain_lo.end() and *it1<*it2)) open.push_back({STACK_LO, *(it1++)});
        else if (it1==chain_lo.end() or *it2<*it1)                      open.push_back({STACK_HI, *(it2++)});
        else                                                            open.push_back({STACK_BOTH, *(it1++)}), it2++;
        // cerr<<"  push "<<open.back().first<<": "<<open.back().second.x<<" "<<open.back().second.y<<endl;
        while (open.size()>=3){
          vec2 a=open[open.size()-3].second, b=open[open.size()-2].second, c=open[open.size()-1].second;
          if (open[open.size()-1].first==open[open.size()-2].first){
            ld const dirn=(open.back().first&STACK_LO? +1: -1);
            if ((c-b).cz(b-a)*dirn>0){
              // cerr<<"which makes a triangle"<<endl;
              triangles.emplace_back(a.id,b.id,c.id);
              open.erase(open.end()-2);
            }
            else break;
          }else{
            // cerr<<"so opposite"<<endl;
            for (int j=0; j+2<open.size(); j++){
              triangles.emplace_back(open[j].second.id,open[j+1].second.id,c.id);
              // cerr<<" and add "<<open[j].second.id<<" "<<open[j+1].second.id<<" "<<c.id<<endl;
            }
            open.erase(open.begin(),open.end()-2);
            open[0].first=STACK_BOTH;
            break;
          }
        }
      }
      // cerr<<" and now we have "<<triangles.size()<<" triangles"<<endl;
    }
  }

  // Debug for triangulation
  if (triangles.size() != n-2){
    cerr<<"triangles = "<<triangles.size()<<" / "<<n-2<<endl;
  }
  if (debug_triangles){
    print_triangles(v,triangles);
  }
  assert(triangles.size() == n-2);

  // Unrotate everything again for output
  for (auto &i: v) i=rotate(i,-epsilon);

  vector<int> ears;
  if (n == 3) {
    ears = {0,1,2};
  } else {
    /* ( ͡° ͜ʖ ͡°)=ε✄  time to cut off some ears! */
    for (auto const tri: triangles){
      int a=get<0>(tri);
      int b=get<1>(tri);
      int c=get<2>(tri);
      bool ab=((a+1)%n==b or (b+1)%n==a);
      bool ac=((a+1)%n==c or (c+1)%n==a);
      bool bc=((b+1)%n==c or (c+1)%n==b);
      if (ab and bc) {} else
      if (ab and ac) swap(a,b); else
      if (ac and bc) swap(c,b); else continue;
      ears.push_back(b);
    }
  }

  vector<vec2> circles;
  for (int b: ears){
    int a=(b+n-1)%n;
    int c=(b+n+1)%n;
    // cerr<<"found triangle "<<a<<" "<<b<<" "<<c<<endl;
    // cerr<<"angle = "<<180.L/M_PI*acosl(dot(unit(v[b]-v[a]),unit(v[b]-v[c])))<<endl;
    vec2 s=unit(v[a]-v[b]);
    vec2 t=unit(v[c]-v[b]);
    vec2 p={s.x+t.x,s.y+t.y};
    ld const m=4000./min(abs(p.cz(t)),abs(p.cz(s))); p.x*=m,p.y*=m;
    p.x+=v[b].x,p.y+=v[b].y;
    circles.push_back(p);
  }

  for (auto const &a: circles)
    for (auto const &b: circles)
      if (&a==&b) break; else{
        if (hypotl(a.x-b.x,a.y-b.y)<4000*2-1e-7L) continue;
        cout.precision(12);
        cout<<fixed<<a.x<<" "<<a.y<<"\n"<<b.x<<" "<<b.y<<endl;
        return 0;
      }
  cout<<"impossible"<<endl;
}
