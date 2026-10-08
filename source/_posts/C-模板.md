---
title: C++模板
date: 2026-01-23 15:37:48
tags: 算法
---

# 说明

这些是我平时攒下来的模板,现在送给大家!

# 代码

```C++
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <map>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <array>
#include <unordered_map>
#include <numeric>
#include <functional>
#include <iomanip>
#include <chrono>
#include <random>
#include <ctime>
using namespace std;
#define ll long long
#define int ll
#define i128 __int128
#define ld long double
#define pb push_back
#define fs first
#define sd second
#define fast ios::sync_with_stdio(false); cin.tie(0);
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define debug(a) cout<<a<<" ";
#define endl '\n'
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// ll lowerbit(ll x){return x&(-x);}
// ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}
// inline void read128(__int128&x){x=0;__int128 f=1;char ch=getchar();
// while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
// while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch =getchar();}}
// void print128(__int128 x){if(x<0){putchar('-');x=-x;}
// if(x>9)print128(x/10);putchar(x%10+'0');}
// const ld pi=atan2(0,-1);
// const ld eps=1e-6;
// const ll inf=1e9+1;
// const ll mod=998244353;

// 01back_pack
void back_pack01(){
    const ll INF=1e9;
    ll w[110],v[110],sum=0,n,f[100010],ans=0,W;
    cin>>n>>W;
    for(int i=1;i<=n;i++){
        cin>>w[i]>>v[i];
        sum+=v[i];
    }
    fill(f,f+100005,INF);
    f[0]=0;
    for(int i=1;i<=n;i++)
        for(int j=sum;j>=v[i];j--)
            if(f[j-v[i]]!=INF)
                f[j]=min(f[j],f[j-v[i]]+w[i]);
    for(int j=sum;j>=0;j--)
        if(f[j]<=W){
            ans=j;
            break;
        }
    cout<<ans<<endl;
}
/*仔细观察代码可以发现：对于当前处理的物品 𝑖
i 和当前状态 𝑓𝑖,𝑗
f_{i,j}，在 𝑗 ⩾𝑤𝑖
j\geqslant w_{i} 时，𝑓𝑖,𝑗
f_{i,j} 是会被 𝑓𝑖,𝑗−𝑤𝑖
f_{i,j-w_{i}} 所影响的。这就相当于物品 𝑖
i 可以多次被放入背包，与题意不符。
（事实上，这正是完全背包问题的解法）*/

// 01背包val_base
void val_base01(){
    const ll INF=1e9;
    ll w[110],v[110],sum=0,n,f[100010],ans=0,W;
    cin>>n>>W;
    for(int i=1;i<=n;i++){
        cin>>w[i]>>v[i];
        sum+=v[i];
    }
    fill(f,f+100005,INF);
    f[0]=0;
    for(int i=1;i<=n;i++)
        for(int j=sum;j>=v[i];j--)
            if(f[j-v[i]]!=INF)
                f[j]=min(f[j],f[j-v[i]]+w[i]);
    for(int j=sum;j>=0;j--)
        if(f[j]<=W){
            ans=j;
            break;
        }
    cout<<ans<<endl;
}

// 01bfs
void bfs01(){
    const int INF = 0x3f3f3f3f;
    const int MAXN = 1e5+1;
    vector<pair<int, int>> graph[MAXN];
    int n, m, source;
    deque<int> dq;
    vector<int> dist(n, INF);
    dist[source] = 0;
    dq.push_front(source);
    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        for (auto [v, w] : graph[u]) {
            if (w == 0 && dist[v] > dist[u]) {
                dist[v] = dist[u];
                dq.push_front(v);  // 边权0，加入前端
            } else if (w == 1 && dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                dq.push_back(v);   // 边权1，加入后端
            }
        }
    }
}

// 求背包方案数
void way_of_back_pack(){
  const ll mod=998244353;
  ll f[200010],c[200010];
  ll n,m; cin>>n>>m;
  for(int i=0;i<=m;i++){
    f[i]=0,c[i]=1;
  }
  /*
  for(int i=1;i<=m;i++) f[i]=-inf;
  f[0]=0,c[0]=1;
  恰好装满的方案数
  */
  for(int i=1;i<=n;i++){
    ll w,v; cin>>v>>w;
    // volum worth
    for(int j=m;j>=v;j--){
      if(f[j]<f[j-v]+w){
        f[j]=f[j-v]+w;
        c[j]=c[j-v];
      }
      else if(f[j]==f[j-v]+w){
        c[j]=(c[j]+c[j-v])%mod;
      }
    }
  }
  // for(int i=0;i<=m;i++) debug(f[i]); cout<<endl;
  // for(int i=0;i<=m;i++) debug(c[i]); cout<<endl;
  cout<<c[m]<<endl;
}

// 求具体方案
void ways_specific(){
  ll f[2010][2010],v[2010],w[2010];
  ll n,m,ans=0; cin>>n>>m;
  // f[i][j]表示,选i-n编号的物品,放入容量为j的背包中的最优解
  for(int i=1;i<=n;i++) cin>>v[i]>>w[i];
  for(int i=n;i>=1;i--){
    for(int j=0;j<=m;j++){
      f[i][j]=f[i+1][j];
      // 不选第i个物品的方案
      if(v[i]<=j)
        f[i][j]=max(f[i][j],f[i+1][j-v[i]]+w[i]);
    }
  }
  cout<<f[1][m]<<endl;
  for(int i=1,j=m;i<=n;i++){
    if(j>=v[i]&&f[i][j]==f[i][j-v[i]]+w[i]){
      cout<<i<<endl;
      j-=v[i];
    }
  }
}

// dsu std
struct dsu{// 并查集(路径压缩 + 按大小合并)
  vector<ll> fa,sz;
  dsu(ll n):fa(n+1),sz(n+1,1){
    for(int i=1;i<=n;++i) fa[i]=i;
  }
  ll find(ll x){return fa[x]==x?x:fa[x]=find(fa[x]);}
  void uni(ll x,ll y){// 合并 x,y 所在集合
    x=find(x);
    y=find(y);
    if(sz[x]<sz[y]) swap(x,y);
    fa[y]=x;
    sz[x]+=sz[y];
  }
};

// 单调队列
void decrease_queue(){
    int h=0,t=-1,q[1000010],n,a[1000010];
    ll n,m; cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        if(h<=t && q[h]<i-m+1) h++;
        while(h<=t && a[i]<=a[q[t]]) t--;
        q[++t]=i;
        if(i>m-1) printf("%d ",a[q[h]]);
    }
    cout<<endl;
}
/*对只除去开头元素来保证不过期的解释：
新的大元素会淘汰所有旧元素，
清空后新元素下标最大，确保不会漏掉过期检查
队列下标的**单调递增**保证了过期检测的简单性
使用方式：可以用于配合求区间最值，如区间和，
加上前缀和，减掉最小位置就行了
*/

// 单调栈
void decrease_stack(){
    stack<ll> s;
    ll N,ans[3000010],a[3000010];
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>a[i];
        while(!s.empty()&&a[i]>a[s.top()]){
            ans[s.top()]=i;
            s.pop();
        }
        s.push(i);
    }
    for(int i=1;i<=N;i++) cout<<ans[i]<<" ";
}

// 笛卡尔树
void DKE_tree(){
  const ll N=2e5+10;
  ll ls[N],rs[N],top,n,a[N],stk[N];
  for(int i=1;i<=n;i++)
    ls[i]=rs[i]=0;
  top=0;
  for(int i=1;i<=n;i++){
    ll now=top;
    while(now>0&&a[stk[now]]>a[i]) now--;
    if(now) rs[stk[now]]=i;
    if(now<top) ls[i]=stk[now+1];
    stk[++now]=i;
    top=now;
  }
}

// 多重背包
void muiltibackpack(){
    ll f[200010],n,V,q[200010],g[200010];
    cin>>n>>V;
    for(int i=1;i<=n;i++){
        memcpy(g,f,sizeof(f));
        ll v,w,s; cin>>w>>v>>s;  //vol worth shu
        for(int j=0;j<v;j++){
            ll h=0,t=-1;
            for(int k=j;k<=V;k+=v){
                if(h<=t && q[h]<k-s*v) h++;//处理过期元素
                if(h<=t) f[k]=max(g[k],g[q[h]]+(k-q[h])/v*w);//使用头部最大值
                while(h<=t && g[k]>=g[q[t]]+(k-q[t])/v*w) t--; //尾部值加上可能的价值还没现在这个大，那么就出队
                q[++t]=k;
            }
        }
    }
    cout<<f[V]<<endl;
}

// 二维背包
void two_dem_back_pack(){
    ll f[2010][2010],V,M,n;
    cin>>n>>V>>M;
    for(int i=1;i<=n;i++){
        ll v,m,w; cin>>w>>v>>m;
        for(int j=V;j>=v;j--)
            for(int k=M;k>=m;k--)
                f[j][k]=max(f[j-v][k-m]+w,f[j][k]);
    }
    cout<<f[V][M]<<endl;
}
/*w为价值
v为体积(第一维)
w为重量(第二维)
*/

// 分组背包
void fenzu_backpack(){
    ll f[200010],n,V,v[200010],w[200010]; //vol worth
    cin>>n>>V;
    for(int i=1;i<=n;i++){
        ll s;cin>>s;
        for(int j=1;j<=s;j++) cin>>v[j]>>w[j];
        for(int j=V;j>=1;j--){
            for(int k=1;k<=s;k++){
                if(j>=v[k])
                    f[j]=max(f[j],f[j-v[k]]+w[k]);
            }
        }
    }
    cout<<f[V]<<endl;
}
/*和01背包同理，需要从后往前计算保证每种物品只被计算一遍
*/


// 混合背包
struct mix_back_pack{
    ll f[200010],q[200010],g[200010];
    struct tree{
        ll vol,worth,shu;
    }t[200010];
    void dc(ll n,ll V){
        for(int i=1;i<=n;i++){
            memcpy(g,f,sizeof(f));
            ll v,w,s;   //vol worth shu
            v=t[i].vol;
            w=t[i].worth;
            s=t[i].shu;
            for(int j=0;j<v;j++){
                ll h=0,t=-1;
                for(int k=j;k<=V;k+=v){
                    if(h<=t && q[h]<k-s*v) h++;//处理过期元素
                    if(h<=t) f[k]=max(g[k],g[q[h]]+(k-q[h])/v*w);//使用头部最大值
                    while(h<=t && g[k]>=g[q[t]]+(k-q[t])/v*w) t--; //尾部值加上可能的价值还没现在这个大，那么就出队
                    q[++t]=k;
                }
            }
        }
    }
    void solve(){
        ll n; cin>>n;
        ll V; cin>>V;
        ll id=1;
        for(int i=1;i<=n;i++){
            ll vol,worth,shu; cin>>vol>>worth>>shu;
            if(shu!=0){//属于多重背包的情况
                t[id].vol=vol;
                t[id].worth=worth;
                t[id].shu=shu;
                id++;
            }
            else{
                for(int j=vol;j<=V;j++){
                    f[j]=max(f[j],f[j-vol]+worth);
                }
            }
        }
        dc(id-1,V);
        cout<<f[V]<<endl;
    }
};

// 浮点数精度阈值（根据题目要求调整，通常1e-8）
const double EPS = 1e-8;
// 符号函数：判断浮点数正负
int sgn(double x) {
    if (fabs(x) < EPS) return 0;
    return x > 0 ? 1 : -1;
}

// 点/向量结构体（二维）
struct Point {
    double x, y;
    // 构造函数
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    
    // 向量运算重载（核心）
    // 向量加法
    Point operator+ (const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    // 向量减法
    Point operator- (const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
    // 向量数乘（缩放）
    Point operator* (double k) const {
        return Point(x * k, y * k);
    }
    // 向量数除
    Point operator/ (double k) const {
        return Point(x / k, y / k);
    }
    // 浮点数相等判断（带精度）
    bool operator== (const Point& other) const {
        return sgn(x - other.x) == 0 && sgn(y - other.y) == 0;
    }
};

// 线段结构体
struct Segment {
    Point a, b; // 线段端点
    Segment() {}
    Segment(Point a_, Point b_) : a(a_), b(b_) {}
};

// 圆结构体
struct Circle {
    Point o; // 圆心
    double r; // 半径
    Circle() {}
    Circle(Point o_, double r_) : o(o_), r(r_) {}
}; 

struct Vector{
    double x,y;
    Vector(Point a,Point b):x(b.x-a.x),y(b.y-a.y) {}
};

// 向量点乘(a·b)
double dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}
/*用途：
计算向量夹角、投影长度、判断向量垂直；
公式：ab = |a||b|cos(theta)      （(theta)为两向量夹角）*/

//点乘延伸:
// 向量的模长（长度）平方（避免开根号，提升效率）
double len2(const Point& a) {
    return dot(a, a);
}

// 向量的模长（长度）
double len(const Point& a) {
    return sqrt(len2(a));
}

// 两点间距离
double dist(const Point& a, const Point& b) {
    return len(a - b);
}

// 向量投影长度：向量a在向量b上的投影长度 ( projection length（投影长度）)
double proj_len(const Point& a, const Point& b) {
    return dot(a, b) / len(b);
}

// 判断两向量垂直（带精度）
bool is_vertical(const Point& a, const Point& b) {
    return sgn(dot(a, b)) == 0;
}

// 向量叉乘（a×b）
double cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}
/*用途：
判断向量方向（顺时针 / 逆时针）、点在直线哪一侧；计算平行四边形 / 三角形面积；
公式：a×b = |a||b|sin(theta)     (theta) 为两向量夹角）。*/ 

// 三点构成的三角形面积（绝对值/2）
double triangle_area(const Point& a, const Point& b, const Point& c) {
    return fabs(cross(b - a, c - a)) / 2.0;
}

// 四点构成的四边形面积（平行四边形）
double parallelogram_area(const Point& a, const Point& b, const Point& c, const Point& d) {
    return fabs(cross(b - a, d - a));
}

//以下操作也可以由计算向量arctan值进行比较得到答案

// 判断点c在直线ab的左侧/右侧/线上
// 返回值：>0 左侧，<0 右侧，=0 线上 (记忆：左加右减)
int point_line_side(const Point& a, const Point& b, const Point& c) {
    return sgn(cross(b - a, c - a));//注意顺序
}

// 判断向量a是否在向量b的顺时针方向
bool is_clockwise(const Point& a, const Point& b) {
    return sgn(cross(a, b)) < 0;
}

// 判断向量a是否在向量b的逆时针方向
bool is_counter_clockwise(const Point& a, const Point& b) {
    return sgn(cross(a, b)) > 0;
}



// 点p到直线ab的距离
double point_line_dist(const Point& a, const Point& b, const Point& p) {
    return fabs(cross(b - a, p - a)) / len(b - a);
}

// 点p到线段ab的距离
double point_segment_dist(const Point& a, const Point& b, const Point& p) {
    if (a == b) return dist(a, p); // 线段退化为点
    // 投影参数t：判断垂足是否在线段上
    double t = proj_len(p - a, b - a);
    if (sgn(t) <= 0) return dist(p, a); // 垂足在a外侧
    if (sgn(t - len(b - a)) >= 0) return dist(p, b); // 垂足在b外侧
    return point_line_dist(a, b, p); // 垂足在线段内，返回点到直线距离
}

// 计算点p在直线ab上的垂足
Point foot_point(const Point& a, const Point& b, const Point& p) {
    Point ab = b - a;
    double t = dot(p - a, ab) / len2(ab); // 投影参数t（归一化）
    return a + ab * t;
}

// 判断点p是否在线段ab上（含端点）
bool point_on_segment(const Point& a, const Point& b, const Point& p) {
    // 1. p在直线ab上；2. p的坐标在a和b之间（投影在[0,1]）
    return sgn(cross(b - a, p - a)) == 0 
        && sgn(dot(p - a, p - b)) <= 0;
}

// 快速排斥：判断两线段的包围盒是否相交
bool rect_intersect(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    double min_x1 = min(a1.x, a2.x), max_x1 = max(a1.x, a2.x);
    double min_y1 = min(a1.y, a2.y), max_y1 = max(a1.y, a2.y);
    double min_x2 = min(b1.x, b2.x), max_x2 = max(b1.x, b2.x);
    double min_y2 = min(b1.y, b2.y), max_y2 = max(b1.y, b2.y);
    return max_x1 >= min_x2 - EPS && max_x2 >= min_x1 - EPS 
        && max_y1 >= min_y2 - EPS && max_y2 >= min_y1 - EPS;
}

// 跨立实验：判断线段ab是否跨立直线cd
bool cross_stand(const Point& a, const Point& b, const Point& c, const Point& d) {
    return sgn(cross(d - c, a - c)) * sgn(cross(d - c, b - c)) <= 0;
}

// 判断两线段是否相交（含端点）
bool segment_intersect(const Segment& s1, const Segment& s2) {
    Point a = s1.a, b = s1.b, c = s2.a, d = s2.b;
    // 快速排斥
    if (!rect_intersect(a, b, c, d)) return false;
    // 跨立实验（双向）
    return cross_stand(a, b, c, d) && cross_stand(c, d, a, b);
}

// 计算两直线ab和cd的交点（需保证直线不平行）
Point line_intersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    double s1 = cross(d - c, a - c);
    double s2 = cross(d - c, b - c);
    return (a * s2 - b * s1) / (s2 - s1);
}

// 计算两线段的交点（仅当相交时返回有效点）
Point segment_intersect_point(const Segment& s1, const Segment& s2) {
    return line_intersect(s1.a, s1.b, s2.a, s2.b);
}

// 判断点p与圆c的位置：>0 圆外，=0 圆上，<0 圆内
int point_circle_relation(const Point& p, const Circle& c) {
    double d2 = len2(p - c.o); // 距离平方（避免开根号）
    double r2 = c.r * c.r;
    return sgn(d2 - r2);
}

// 点p到圆c的切线长度
double tangent_len(const Point& p, const Circle& c) {
    double d = dist(p, c.o);
    if (sgn(d - c.r) <= 0) return 0.0; // 点在圆内/圆上，无切线
    return sqrt(d * d - c.r * c.r);
}

// 计算直线ab与圆c的交点（返回交点列表）
vector<Point> line_circle_intersect(const Point& a, const Point& b, const Circle& c) {
    vector<Point> res;
    Point foot = foot_point(a, b, c.o); // 圆心到直线的垂足
    double d = point_line_dist(a, b, c.o); // 圆心到直线的距离
    if (sgn(d - c.r) > 0) return res; // 无交点
    if (sgn(d - c.r) == 0) { // 相切，一个交点
        res.push_back(foot);
        return res;
    }
    // 相交，两个交点：垂足向两侧移动 len = sqrt(r² - d²)
    double Len = sqrt(c.r * c.r - d * d);
    Point dir = (b - a) / len(b - a); // 直线方向单位向量
    res.push_back(foot + dir * Len);
    res.push_back(foot - dir * Len);
    return res;
}

// 计算线段ab与圆c的交点（返回交点列表）
vector<Point> segment_circle_intersect(const Point& a, const Point& b, const Circle& c) {
    vector<Point> res, line_inter = line_circle_intersect(a, b, c);
    // 筛选交点是否在线段上
    for (auto& p : line_inter) {
        if (point_on_segment(a, b, p)) {
            res.push_back(p);
        }
    }
    return res;
}

// 计算多边形面积（顶点数组，闭合：最后一个点无需等于第一个）
double polygon_area(const vector<Point>& poly) {
    int n = poly.size();
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += cross(poly[i], poly[j]);
    }
    return fabs(area) / 2.0;
}

// 判断点p是否在多边形poly内（含边界）
bool point_in_polygon(const Point& p, const vector<Point>& poly) {
    int n = poly.size();
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        if (point_on_segment(a, b, p)) return true; // 在边界上
        // 射线法：判断射线与线段是否相交
        if (sgn(a.y - p.y) > sgn(b.y - p.y)) swap(a, b);
        if (sgn(b.y - p.y) <= 0) continue;
        if (sgn(cross(b - a, p - a)) > 0) cnt++;
    }
    return cnt % 2 == 1; // 奇数：内部，偶数：外部
}

// 向量a绕原点旋转rad弧度（逆时针为正，顺时针为负）
Point rotate(const Point& a, double rad) {
    double c = cos(rad), s = sin(rad);
    return Point(a.x * c - a.y * s, a.x * s + a.y * c);
}

// 向量a绕点p旋转rad弧度
Point rotate_point(const Point& a, const Point& p, double rad) {
    return rotate(a - p, rad) + p;
}

// 向量单位化（避免零向量）
Point normalize(const Point& a) {
    double l = len(a);
    if (sgn(l) == 0) return Point(0, 0);
    return a / l;
}

/*
使用注意事项
浮点数精度：所有比较必须通过 sgn 函数（或 EPS），避免直接用 ==/>/<；
零向量 / 零长度线段：提前判断，避免除 0 错误；
效率优化：尽量用长度平方（len2）代替长度（len），减少开根号；
坐标范围：若题目坐标是整数，可先用整数运算（避免浮点误差），最后转浮点。
*/

// 解方程
void cal_martix(){
  const double eps=1e-8;
  double a[110][110];
  ll n; cin>>n;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n+1;j++){
      cin>>a[i][j];
    }
  }
  for(int i=1;i<=n;i++){
    ll r=i;
    for(int k=i;k<=n;k++){
      if(fabs(a[k][i])>eps){// 找到非0行,换到最前面
        r=k;
        break;
      }
    }
    if(r!=i)
      swap(a[i],a[r]);
    if(fabs(a[i][i])<eps){//double不能直接和0比较，所以和一个非常小的数比较
      cout<<"No Solution"<<endl;//如果为0了，那么必然是没有唯一解的
      return;
    }
    for(int k=1;k<=n;k++){//把这一列除了a[i][i]全变为0
      if(k==i) continue;
      double t=a[k][i]/a[i][i];//计算倍数
      for(int j=i;j<=n+1;j++){//减去对应的数
        a[k][j]-=t*a[i][j];
      }
    }
  }
  for(int i=1;i<=n;i++){
    cout<<fixed<<setprecision(2)<<a[i][n+1]/a[i][i]<<endl;
  }
}

// 块状链表
#include <ext/rope>
using namespace __gnu_cxx;
void myrope(){
    rope<int> a;// 注意rope貌似不支持pair
    a.insert(1,10);
    a.push_back(10);
    a.erase(0);
    cout<<a[1]<<a.size()<<endl;
}
/*
rope的操作写起来和vector一模一样
但是rope的插入以及查询操作的时间复杂度均是log n的
所以要是插入操作多的话可以用这个
*/

// 主席树
struct zhuxi_tree{
    #define N 1000005
    #define mid ((l+r)>>1)

    ll ls[N*25], rs[N*25], val[N*25], lazy[N*25];
    ll root[N], tot = 0, n, m, a[N];

    // 创建新节点
    ll newNode(ll v = 0, ll lz = 0) {
        ls[tot] = rs[tot] = 0;
        val[tot] = v;
        lazy[tot] = lz;
        return tot++;
    }

    // 复制节点（创建新版本）
    ll copyNode(ll u) {
        ll new_node = newNode(val[u], lazy[u]);
        ls[new_node] = ls[u];
        rs[new_node] = rs[u];
        return new_node;
    }

    // 下推懒标记
    void pushDown(ll u, ll l, ll r) {
        if (lazy[u] != 0) {
            // 左子树
            if (ls[u] == 0) ls[u] = newNode(0, 0);
            ls[u] = copyNode(ls[u]);
            val[ls[u]] += lazy[u] * (mid - l + 1);
            lazy[ls[u]] += lazy[u];
            
            // 右子树
            if (rs[u] == 0) rs[u] = newNode(0, 0);
            rs[u] = copyNode(rs[u]);
            val[rs[u]] += lazy[u] * (r - mid);
            lazy[rs[u]] += lazy[u];
            
            lazy[u] = 0;
        }
    }

    // 建树
    void build(ll &u, ll l, ll r) {
        u = newNode();
        if (l == r) {
            val[u] = a[l];
            return;
        }
        build(ls[u], l, mid);
        build(rs[u], mid + 1, r);
        val[u] = val[ls[u]] + val[rs[u]];
    }

    // 区间增加
    void rangeAdd(ll &u, ll v, ll l, ll r, ll ql, ll qr, ll x) {
        u = copyNode(v);
        
        if (ql <= l && r <= qr) {
            val[u] += x * (r - l + 1);
            lazy[u] += x;
            return;
        }
        
        pushDown(u, l, r);
        
        if (ql <= mid) rangeAdd(ls[u], ls[v], l, mid, ql, qr, x);
        if (qr > mid) rangeAdd(rs[u], rs[v], mid + 1, r, ql, qr, x);
        
        val[u] = val[ls[u]] + val[rs[u]];
    }

    // 单点查询
    ll query(ll u, ll l, ll r, ll p) {
        if (l == r) return val[u];
        
        pushDown(u, l, r);
        
        if (p <= mid) return query(ls[u], l, mid, p);
        else return query(rs[u], mid + 1, r, p);
    }

    // 使用示例
    void solve() {
        // 初始化数组，注意索引从1开始
        n = 5;
        for (int i = 1; i <= n; i++) a[i] = i;
        
        // 建树，版本0
        build(root[0], 1, n);
        
        // 区间增加 [2,4] 加10，创建版本1
        rangeAdd(root[1], root[0], 1, n, 2, 4, 10);
        
        // 再次区间增加 [1,3] 加5，创建版本2  
        rangeAdd(root[2], root[1], 1, n, 1, 3, 5);
        
        // 查询不同版本
        cout << "Version 0, pos 3: " << query(root[0], 1, n, 3) << endl; // 3
        cout << "Version 1, pos 3: " << query(root[1], 1, n, 3) << endl; // 13
        cout << "Version 2, pos 3: " << query(root[2], 1, n, 3) << endl; // 18
        
        return 0;
    }
};

struct Tire{
    const ll INF=1e18,N=1e5+10;
    char s[N];
    int ch[N][26],cnt[N],idx=0;
    void insert(char *s){
        int p=0;
        for(int i=0;s[i];i++){
            int j=s[i]-'a';
            if(!ch[p][j]) ch[p][j]=++idx;
            p=ch[p][j];
        }
        cnt[p]++;
    }
    int query(char *s){
        int p=0;
        for(int i=0;s[i];i++){
            int j=s[i]-'a';
            if(!ch[p][j]) return 0;
            p=ch[p][j];
        }
        return cnt[p];
    }
};

// 组合数
struct C_{
    const ll N=2e6+10;
    ll mod=998244353;
    ll fact[N],inv[N];
    ll qpow(ll a,ll b){
        ll sum=1;
        while(b>0){
            if(b&1) sum=sum*a%mod;
            a=a*a%mod;
            b>>=1;
        }
        return sum;
    }
    // 预处理阶乘 fact 和阶乘逆元 inv
    void init(){
        ll n=N-5;
        fact[0]=1;
        for(int i=1;i<=n;i++)
            fact[i]=fact[i-1]*i%mod;
        inv[n]=qpow(fact[n],mod-2);
        for(int i=n;i>=1;i--)
            inv[i-1]=inv[i]*i%mod;
    }
    // 组合数 C(n,i)（n,i 需在预处理范围内）
    ll C(ll n,ll i){
        return fact[n]*inv[i]%mod*inv[n-i]%mod;
    }
};

// 最大流
struct max_flow{
    const ll MAXN=250;
    const ll inf=0x3f3f3f3f;
    struct Edge{// 有向边
        ll from,to,cap,flow;// 起点,终点,容量,流量
        Edge(ll u,ll v,ll c,ll f):from(u),to(v),cap(c),flow(f){};
    };
    struct EK{// Edmonds-Karp 最大流
        ll n,m;// 节点数和边数
        vector<Edge> edges;// 边
        vector<ll> g[MAXN];// 邻接表(存边下标)
        ll mf[MAXN],p[MAXN];
        // 点x->BFS过程中到达x的边的最大流量 / 到达x的边下标
        void AddEdge(ll from,ll to,ll cap){
            edges.pb(Edge(from,to,cap,0));
            edges.pb(Edge(to,from,0,0));
            m=edges.size();
            g[from].pb(m-2);
            g[to].pb(m-1);
        }
        ll Maxflow(ll s,ll t){
            ll flow=0;
            for(;;){
            memset(mf,0,sizeof(mf));
            queue<ll> q;
            q.push(s);
            mf[s]=inf;// 源点可以流出无限多
            while(!q.empty()){
                ll x=q.front();
                q.pop();
                for(int i=0;i<g[x].size();i++){
                    Edge&e=edges[g[x][i]];
                    if(!mf[e.to]&&e.cap>e.flow){
                        p[e.to]=g[x][i];// 记录到达e.to的边下标
                        mf[e.to]=min(mf[x],e.cap-e.flow);// 更新瓶颈流量
                        q.push(e.to);
                    }
                }
                if(mf[t]) break;// 碰到汇点t立即结束BFS
            }
            if(!mf[t]) break;
            for(int u=t;u!=s;u=edges[p[u]].from){
                    edges[p[u]].flow+=mf[t];
                    edges[p[u]^1].flow-=mf[t];
                }
                flow+=mf[t];
            }
            return flow;
        }
    };
};

// 最大区间和
void max_erea(){
    ll a[200010];
    ll n; cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    ll max_ending_here=a[1];
    ll max_so_far=a[1];
    for(int i=2;i<=n;i++){
        max_ending_here=max(a[i],max_ending_here+a[i]);
        max_so_far=max(max_so_far,max_ending_here);
    }
    cout<<max_so_far<<endl;
    ll sum=0;
    for(int i=1;i<=n;i++){
		sum=sum+a[i];
		max_so_far=max(max_so_far,sum);
		if(sum<0) sum=0;
	}
}

// 莫队
ll B;// 块大小,一般取 n/sqrt((m<<1)/3)
struct Q{ll l,r,id;};
bool cmp(Q x,Q y){
  if(x.l/B!=y.l/B) return x.l/B<y.l/B;
  if((x.l/B)%2) return x.r>y.r;// 奇偶块优化
  return x.r<y.r;
}
// add(pos): 加入位置 pos 的元素,并维护当前答案
// del(pos): 移除位置 pos 的元素,并维护当前答案
// 使用:
//   sort(q+1,q+m+1,cmp);
//   for(int i=1,l=1,r=0;i<=m;i++){
//     while(l>q[i].l) add(--l);
//     while(r<q[i].r) add(++r);
//     while(l<q[i].l) del(l++);
//     while(r>q[i].r) del(r--);
//     ans[q[i].id]=now;// now为当前答案
//   }

// 区间dp
void qj_dp(){
    ll n,a[410],ans[410][410],sum[410];
    cin>>n;
    memset(ans,0x3f,sizeof(ans));
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
        ans[i][i]=0;
    }
    for(int l=2;l<=n;l++){
        for(int i=1;i+l-1<=n;i++){
            ll j=i+l-1;
            for(int k=i;k<j;k++){
                ans[i][j]=min(ans[i][k]+ans[k+1][j]+sum[j]-sum[i-1],ans[i][j]);
            }
        }
    }
    cout<<ans[1][n]<<endl;
}

// 树链剖分
struct p_tree{
    const ll N=200010;
    ll dfn[N],leave[N],sz[N],hson[N],top[N];
    ll a[N],dep[N],fa[N];
    vector<ll> g[N];
    ll n,id=1,mod;
    struct Line_tree{// 线段树(区间加,区间和,lazy,带mod)
        vector<ll> a,tr,tag;
        Line_tree(ll n):a(n+1,0),tr(n*4+10,0),tag(n*4+10,0){}
        void build(ll nl,ll nr,ll now){
            if(nl==nr){tr[now]=a[nl];return;}
            ll m=nl+((nr-nl)>>1);
            build(nl,m,now*2);
            build(m+1,nr,now*2+1);
            tr[now]=(tr[now*2]+tr[now*2+1])%mod;
        }
        void push_down(ll nl,ll nr,ll now){
            ll m=nl+((nr-nl)>>1);
            ll lsz=m-nl+1,rsz=nr-m;
            tr[now*2]=(tr[now*2]+tag[now]*lsz%mod)%mod;
            tr[now*2+1]=(tr[now*2+1]+tag[now]*rsz%mod)%mod;
            tag[now*2]=(tag[now*2]+tag[now])%mod;
            tag[now*2+1]=(tag[now*2+1]+tag[now])%mod;
            tag[now]=0;
        }
        void update_add(ll ul,ll ur,ll nl,ll nr,ll now,ll add){
            if(ul<=nl&&nr<=ur){
            tr[now]=(tr[now]+(nr-nl+1)*add%mod)%mod;
            tag[now]=(tag[now]+add)%mod;
            return;
            }
            ll m=nl+((nr-nl)>>1);
            if(tag[now]&&nl!=nr) push_down(nl,nr,now);
            if(m<ur) update_add(ul,ur,m+1,nr,now*2+1,add);
            if(m>=ul) update_add(ul,ur,nl,m,now*2,add);
            tr[now]=(tr[now*2]+tr[now*2+1])%mod;
        }
        ll query_sum(ll ql,ll qr,ll nl,ll nr,ll now){
            ll now_ans=0;
            if(ql<=nl&&nr<=qr) return tr[now];
            ll m=nl+((nr-nl)>>1);
            if(tag[now]) push_down(nl,nr,now);
            if(m>=ql) now_ans=(now_ans+query_sum(ql,qr,nl,m,now*2))%mod;
            if(m<qr) now_ans=(now_ans+query_sum(ql,qr,m+1,nr,now*2+1))%mod;
            return now_ans;
        }
    };
    Line_tree xd(N);
    // 第一遍dfs:求 sz,dep,hson,fa
    void dfs1(ll last,ll now,ll d){
        sz[now]=1,dep[now]=d;
        ll p=0;
        for(int next:g[now]){
            if(next==last) continue;
            dfs1(now,next,d+1);
            fa[next]=now;
            sz[now]+=sz[next];
            if(sz[p]<sz[next]) p=next;
        }
        hson[now]=p;
    }
    // 第二遍dfs:求 top,dfn,leave,并把点权映射到线段树
    void dfs2(ll last,ll now,ll t){
        top[now]=t;
        xd.a[id]=a[now];
        dfn[now]=id++;
        if(hson[now]!=0) dfs2(now,hson[now],t);
        for(int next:g[now]){
            if(next==last) continue;
            if(next==hson[now]) continue;
            dfs2(now,next,next);
        }
        leave[now]=id-1;
    }
    // 树上路径 u->v 加 add
    void update_path(ll u,ll v,ll add){
        ll l,r;
        while(top[u]!=top[v]){
            if(dep[top[u]]<dep[top[v]]) swap(u,v);
            l=dfn[top[u]],r=dfn[u];
            xd.update_add(l,r,1,n,1,add);
            u=fa[top[u]];
        }
        l=min(dfn[u],dfn[v]),r=max(dfn[u],dfn[v]);
        xd.update_add(l,r,1,n,1,add);
    }
    // 树上路径 u->v 求和
    ll query_path(ll u,ll v){
        ll ans=0,l,r;
        while(top[u]!=top[v]){
            if(dep[top[u]]<dep[top[v]]) swap(u,v);
            l=dfn[top[u]],r=dfn[u];
            ans=(ans+xd.query_sum(l,r,1,n,1))%mod;
            u=fa[top[u]];
        }
        l=min(dfn[u],dfn[v]),r=max(dfn[u],dfn[v]);
        ans=(ans+xd.query_sum(l,r,1,n,1))%mod;
        return ans;
    }
    // 使用: 建图后 dfs1(0,root,1); dfs2(0,root,root); xd.build(1,n,1);
};

// 拓扑排序
bool toposort() {
    const ll MAXN=200010;
    ll n, m;
    vector<ll> G[MAXN];
    ll in[MAXN];  // 存储每个结点的入度
    vector<ll> L;
    queue<ll> S;
    for (int i = 1; i <= n; i++)
        if (in[i] == 0) S.push(i);
    while (!S.empty()) {
        int u = S.front();
        S.pop();
        L.push_back(u);
        for (auto v : G[u]) {
            if (--in[v] == 0) {
                S.push(v);
            }
        }
    }
    if (L.size() == n) {
        for (auto i : L) cout << i << ' ';
        return true;
    }
    return false;
}

// 凸包
struct Point{
  ld x,y;
  Point operator+(const Point&othor)const{return {x+othor.x,y+othor.y};}
  Point operator-(const Point&othor)const{return {x-othor.x,y-othor.y};}
  ld operator^(const Point&othor)const{return x*othor.y-y*othor.x;}
  ld operator*(const Point&othor)const{return x*othor.x+y*othor.y;}
};
Point o;
ld dis2(Point p1,Point p2){
  ld x=p1.x-p2.x,y=p1.y-p2.y;
  return x*x+y*y;
}
bool cmp(Point p1,Point p2){
  if(((p1-o)^(p2-o))!=0) return ((p1-o)^(p2-o))>0;
  return dis2(o,p1)<dis2(o,p2);
}
vector<Point> Graham(vector<Point> p){
  ll n=p.size(),id=0;
  for(int i=1;i<n;i++)
    if(p[id].y<p[i].y||(p[id].y==p[i].y&&p[id].x<p[i].x))
      id=i;
  swap(p[id],p[0]);
  o=p[0]; sort(p.begin()+1,p.end(),cmp);
  vector<ll> sta; sta.pb(0);
  for(int i=1;i<n;i++){
    while(sta.size()>=2&&
    ((p[sta.back()]-p[sta[sta.size()-2]])^(p[i]-p[sta.back()]))<=0)
      sta.pop_back();
    sta.pb(i);
  }
  vector<Point> ans;
  for(int i:sta) ans.pb(p[i]);
  return ans;
}
void solve_tb(){
  ll n; cin>>n;
  vector<Point> a(n);
  for(int i=0;i<n;i++) cin>>a[i].x>>a[i].y;
  a=Graham(a);
  ld ans=0; n=a.size();
  for(int i=1;i<n;i++)
    ans+=sqrt(dis2(a[i],a[i-1]));
  ans+=sqrt(dis2(a[0],a.back()));
  cout<<fixed<<setprecision(2)<<ans<<endl;
}

// 主席树
struct zx_tree{
    #define N 1000005
    #define mid ((l+r)>>1)
    ll ls[N*25],rs[N*25],val[N*25];
    ll root[N],tot=0,n,m,a[N];
    void build(ll &u,ll l,ll r){
        u=tot++;
        if(l==r){val[u]=a[l];return;}
        build(ls[u],l,mid);
        build(rs[u],mid+1,r);
    }
    void change(ll &u,ll v,ll l,ll r,ll p,ll x){//version position
        u=++tot;//now palce:u
        ls[u]=ls[v]; rs[u]=rs[v]; val[u]=val[v];
        if(l==r){val[u]=x;return;}
        if(p<=mid) change(ls[u],ls[v],l,mid,p,x);//=
        else change(rs[u],rs[v],mid+1,r,p,x);
    }
    ll query(ll u,ll l,ll r,ll p){
        if(l==r) return val[u];
        if(p<=mid) return query(ls[u],l,mid,p);
        else return query(rs[u],mid+1,r,p);
    }
    // int main(){
    //     std::ios::sync_with_stdio(false);
    //     cin.tie(0);
    //     cin>>n>>m;
    //     memset(a,0,sizeof(a));
    //     build(root[0],1,n);
    //     for(int i=1;i<=m;i++){
            
    //     }
    // }
};

// 最大流,最小费
struct MFMC{
    const ll inf=0x3f3f3f3f;
    const ll N=2010,M=500010;
    struct qxx{int nex,t,v,c;}e[M];
    ll h[N],cnt=1;
    void add_path(ll f,ll t,ll v,ll c){
        e[++cnt]=qxx{h[f],t,v,c},h[f]=cnt;
    }
    // 加一条 f->t 容量 v 费用 c 的边（自动加反向边）
    void add_flow(ll f,ll t,ll v,ll c){
        add_path(f,t,v,c);
        add_path(t,f,0,-c);
    }
    ll dis[N],pre[N],mf[N],s,t;
    bool vis[N];
    bool spfa(){
        memset(dis,0x3f,sizeof(dis));
        queue<ll> q;
        q.push(s); dis[s]=0,mf[s]=inf,mf[t]=0;
        while(!q.empty()){
            ll u=q.front(); q.pop();
            vis[u]=0;
            for(int i=h[u];i;i=e[i].nex){
            const ll &v=e[i].t,&w=e[i].v,&c=e[i].c;
            if(!w||dis[v]<=dis[u]+c) continue;
            dis[v]=dis[u]+c,mf[v]=min(w,mf[u]),pre[v]=i;
            if(!vis[v]) q.push(v),vis[v]=1;
            }
        }
        return mf[t];
    }
    ll maxflow,mincost;
    void update(){
        maxflow+=mf[t];
        for(int u=t;u!=s;u=e[pre[u]^1].t){
            e[pre[u]].v-=mf[t],e[pre[u]^1].v+=mf[t];
            mincost+=mf[t]*e[pre[u]].c;
        }
    }
// 使用: add_flow 建图, 设 s,t, 然后 while(spfa()) update();
// 答案: mincost(最小费用) / maxflow(最大流)
};

// dijkstra
void dij(){
    long long N;
    const long long INF=1e18;
    vector<pair<LL,LL>> g[10010];
    priority_queue<pair<LL, LL>, vector<pair<LL, LL>>, greater<pair<LL, LL>>> pq;vector<bool> vis(N+1, false);
    vector<LL> dis(N+1, INF);

    dis[1] = 0;
    pq.push({0, 1});

    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if(vis[u]) continue;
        vis[u] = true;
    
        for(auto [v, w] : g[u]) {
            if(!vis[v] && dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }
    }
}

// ex_kruskal
struct ex_kruskal{
    struct edge{
        ll u,v,w;
        bool operator<(const edge&othor){return w<othor.w;}
        bool operator>(const edge&othor){return w>othor.w;}
    };
    // 节点值,目前的最大编号,父节点
    ll val[200010],id,fa[200010],root;
    ll n,m;
    vector<ll> g[200010];
    ll find(ll x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    ll up[500010][20],depth[500010];
    void dfs(ll last,ll now,ll dep){
        up[now][0]=last;
        depth[now]=dep;
        for(int next:g[now]){
            if(next==last) continue;
            dfs(now,next,dep+1);
        }
    }
    // 一共有id个点,root为id
    void init_lca(){
        dfs(0,root,1);
        for(int k=1;k<20;k++){
            for(int i=1;i<=id;i++){
            if(up[i][k-1]!=0)
                up[i][k]=up[up[i][k-1]][k-1];
            }
        }
    }
    ll LCA_bz(ll u,ll v){
        if(depth[u]<depth[v]) swap(u,v);
        ll diff=depth[u]-depth[v];
        for(int i=19;i>=0;i--){
            if(diff&(1ll<<i)){
            u=up[u][i];
            }
        }
        for(int i=19;i>=0;i--){
            if(up[u][i]!=up[v][i]){
            u=up[u][i];
            v=up[v][i];
            }
        }
        if(u==v) return u;
        else return up[u][0];
    }
    void Ex_Kruskal(){
        vector<edge> e(m+1);
        for(int i=1;i<=m;i++)
            cin>>e[i].u>>e[i].v>>e[i].w;
        sort(e.begin()+1,e.end(),greater<>());
        for(int i=1;i<=2*n;i++) fa[i]=i;
        for(int i=1;i<=m;i++){
            edge nowe=e[i];
            ll fu=find(nowe.u),fv=find(nowe.v);
            if(fu!=fv){
                val[++id]=nowe.w;
                fa[fu]=fa[fv]=id;
                g[id].pb(fu); g[id].pb(fv);
            }
        }
        vector<ll> roots;
        for(int i=1;i<=id;i++){
            if(find(i)==i) roots.pb(i);
        }
        // 注意此处要把所有点连起来,因为不然后面查询会查不到
        if(roots.size()>1){
            id++;
            for(int i:roots) g[id].pb(i);
        }
    }
    void solve(){
        cin>>n>>m;
        id=n;
        Ex_Kruskal();
        root=id;
        init_lca();
        ll q; cin>>q;
        while(q--){
            ll x,y; cin>>x>>y;
            ll fx=find(x),fy=find(y);
            if(fx!=fy){
            cout<<-1<<endl;
            continue;
            }
            ll lca=LCA_bz(x,y);
            cout<<val[lca]<<endl;
        }
    }
};


// KMP
void KMP(){
    string t,p; cin>>t>>p;
    vector<ll> ans,pi(p.length());
    for(int i=1;i<p.length();i++){
        ll j=pi[i-1];
        while(j>0&&p[j]!=p[i]) j=pi[j-1];
        if(p[i]==p[j]) j++;
        pi[i]=j;
    }//上面是next函数，对pattern数据处理，方便查找长度
    for(int i=0,j=0;i<t.length();i++){
        while(j>0&&t[i]!=p[j]) j=pi[j-1];
        if(p[j]==t[i])j++;
        if(j==p.length()){
            ans.push_back(i-p.length()+1);
            j=pi[j-1];
        }
    }//计算可能的位置
    for(auto &i:ans) cout<<i+1<<endl;
    for(int i=0;i<p.length();i++) cout<<pi[i]<<" "; cout<<endl;
}
/*
关键点，比较时j会向前跳，pi[j]记录的依旧是长度
可以用计算前缀的函数来理解
最后记得要向前跳一位，因为不然下一次会直接认为是正确答案
而且跳不回去了，所以要j=pi[j-1]
*/

struct LCA{
    vector<ll> g[500010];
    ll n,m,root;
    ll up[500010][20],depth[500010];
    void dfs(ll last,ll now,ll dep){
        up[now][0]=last;
        depth[now]=dep;
        for(int next:g[now]){
            if(next==last) continue;
            dfs(now,next,dep+1);
        }
    }
    ll LCA_bz(ll u,ll v){
        dfs(0,root,1);
        for(int k=1;k<20;k++){
            for(int i=1;i<=n;i++){
            if(up[i][k-1]!=0)
                up[i][k]=up[up[i][k-1]][k-1];
            }
        }
        if(depth[u]<depth[v]) swap(u,v);
        ll diff=depth[u]-depth[v];
        for(int i=19;i>=0;i--){
            if(diff&(1ll<<i)){
            u=up[u][i];
            }
        }
        for(int i=19;i>=0;i--){
            if(up[u][i]!=up[v][i]){
            u=up[u][i];
            v=up[v][i];
            }
        }
        if(u==v) return u;
        else return up[u][0];
    }
    void solve(){
        cin>>n>>m>>root;
        for(int i=1;i<=n-1;i++){
            ll x,y; cin>>x>>y;
            g[x].pb(y);
            g[y].pb(x);
        }
    }
};

// LCS
void LCS(){
    ll f[3010][3010],p[3010][3010];
    string s,t;
    cin>>s>>t;
    ll m=s.length(),n=t.length();
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(s[i-1]==t[j-1]){
                f[i][j]=f[i-1][j-1]+1;
                p[i][j]=1;
            }
            else if(f[i][j-1]>f[i-1][j]){
                f[i][j]=f[i][j-1];
                p[i][j]=2;
            }
            else{
                f[i][j]=f[i-1][j];
                p[i][j]=3;
            }
        }
    }
    ll i,j,k; char ch[3010];
    i=m,j=n,k=f[m][n];
    while(i>0&&j>0){
        if(p[i][j]==1){
            ch[k--]=s[i-1];
            i--; j--;
        }
        else if(p[i][j]==2) j--;
        else i--;
    }
    for(int i=1;i<=f[m][n];i++)
        cout<<ch[i]; cout<<endl;
}

// manacher
void manacher(){
    const ll INF=1e18;
    ll p[22000010],mid=0,r=0,ans=1;
    string x; vector<char> s;
    s.push_back('~');s.push_back('#');
    cin>>x; ll len=x.length()*2+1;
    for(int i=0;i<x.length();i++){s.push_back(x[i]);
        s.push_back('#');}
    s.push_back('!');
    for(int i=2;i<len-1;i++){
        if(i<=r) p[i]=min(p[mid*2-i],r-i+1);
        else p[i]=1;
        while(s[i-p[i]]==s[i+p[i]]) p[i]++;
        if(i+p[i]-1>r){r=p[i]+i-1;mid=i;}
        ans=max(p[i],ans);
    }
    cout<<ans-1<<endl;
}

// 分解质因数
ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}
// 快速乘 (a*b mod m)，防止 64 位溢出
ll bmul(ll a,ll b,ll m){
  ull c=(ull)a*(ull)b-(ull)((long double)a/m*b+0.5L)*(ull)m;
  if(c<(ull)m) return c;
  return c+m;
}
// 快速幂（配合 bmul，mod 可能不是质数）
ll qpow(ll x,ll p,ll mod){
  ll ans=1;
  while(p){
    if(p&1) ans=bmul(ans,x,mod);
    x=bmul(x,x,mod);
    p>>=1;
  }
  return ans;
}
// Miller_Rabin 素性测试
bool Miller_Rabin(ll p){
  if(p<2) return false;
  if(p==2) return true;
  if(p==3) return true;
  ll d=p-1,r=0;
  while(!(d&1)) ++r,d>>=1;
  for(ll k=0;k<10;++k){
    ll a=rand()%(p-2)+2;
    ll x=qpow(a,d,p);
    if(x==1||x==p-1) continue;
    for(int i=0;i<r-1;++i){
      x=bmul(x,x,p);
      if(x==p-1) break;
    }
    if(x!=p-1) return false;
  }
  return true;
}
// Pollard_Rho 求 x 的一个非平凡因子
ll Pollard_Rho(ll x){
  ll s=0,t=0;
  ll c=(ll)rand()%(x-1)+1;
  int step=0,goal=1;
  ll val=1;
  for(goal=1;;goal*=2,s=t,val=1){
    for(step=1;step<=goal;++step){
      t=(bmul(t,t,x)+c)%x;
      val=bmul(val,abs(t-s),x);
      if((step%127)==0){
        ll d=gcd(val,x);
        if(d>1) return d;
      }
    }
    ll d=gcd(val,x);
    if(d>1) return d;
  }
}
ll max_factor;
// 求 x 的最大质因子，结果存入 max_factor
void fac(ll x){
  if(x<=max_factor||x<2) return;
  if(Miller_Rabin(x)){
    max_factor=max(max_factor,x);
    return;
  }
  ll p=x;
  while(p>=x) p=Pollard_Rho(x);
  while((x%p)==0) x/=p;
  fac(x),fac(p);
}

// Prim
bool prim(ll st){
    const ll inf=1e9+1;
    ll n,m,ans=0,cnt=0;
    ll d[200010],vis[200010];
    vector<pair<ll,ll>> g[200010];
    for(int i=0;i<=n;i++) d[i]=inf;
    d[st]=0;
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<>> q;
    q.push({0,st});
    while(!q.empty()){
        ll u=q.top().sd,cost=q.top().fs;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        ans+=d[u]; cnt++;
        for(auto[next,c]:g[u]){
            if(d[next]>c){
                d[next]=c;
                q.push({c,next});
            }
        }
    }
    return cnt==n;
}

// spfa
void spfa(){
    #define LL long long
    long long N;
    const long long INF=1e18;
    vector<pair<LL,LL>> g[10010];
    queue<LL> q;
    vector<bool> inQueue(N+1, false);
    vector<LL> dis(N+1, INF);

    dis[1] = 0;
    q.push(1);
    inQueue[1] = true;

    while(!q.empty()) {
        LL u = q.front(); q.pop();
        inQueue[u] = false;
    
        for(auto [v, w] : g[u]) {
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if(!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }
}

// Spaly Tree
struct splay_tree{
    const int N=1e5+10;
    struct node{
        int s[2];
        int p;
        int v;
        int cnt;
        int size;
        void init(int p1,int v1){
            p=p1; v=v1;
            cnt=size=1;
        }
    }tr[N];
    int root;
    int idx;
    void pushup(int u){
        tr[u].size=tr[tr[u].s[0]].size+tr[tr[u].s[1]].size+tr[u].cnt;//更新节点u的size,左右子树的size加上节点u的cnt
    }
    void rotate(int x){
        int y = tr[x].p,z = tr[y].p;
        int k = tr[y].s[1] == x;
        tr[z].s[tr[z].s[1]==y] = x;
        tr[x].p=z;
        tr[y].s[k] = tr[x].s[k^1];//把x的儿子给y
        tr[tr[x].s[k^1]].p = y;
        tr[x].s[k^1] = y;
        tr[y].p = x;
        pushup(y),pushup(x);
    }
    void splay(int x,int k){
        while(tr[x].p!=k){
            int y=tr[x].p,z=tr[y].p;
            if(z!=k) (tr[y].s[0]==x)^(tr[z].s[0]==y) ? rotate(x):rotate(y);
            rotate(x);
        }
        if(k==0) root=x;
    }
    void find(int v){
        int x=root;
        while(tr[x].s[v>tr[x].v]&&v!=tr[x].v) x=tr[x].s[v>tr[x].v];
        splay(x,0);
    }
    int get_pre(int v){
        find(v);
        int x=root;
        if(tr[x].v<v) return x;
        x=tr[x].s[0];
        while(tr[x].s[1])x=tr[x].s[1];
        splay(x,0);
        return x;
    }
    int get_suc(int v){
        find(v);
        int x=root;
        if(tr[x].v>v) return x;
        x=tr[x].s[1];
        while(tr[x].s[0])x=tr[x].s[0];
        splay(x,0);
        return x;
    }
    void del(int v){
        int pre=get_pre(v);
        int suc=get_suc(v);
        splay(pre,0),splay(suc,pre);
        int del=tr[suc].s[0];
        if(tr[del].cnt>1) tr[del].cnt--,splay(del,0);
        else tr[suc].s[0]=0,splay(suc,0);
    }
    int get_val(int k){
        int x=root;
        while(1){
            int y=tr[x].s[0];
            if(tr[y].size+tr[x].cnt<k){
                k-=tr[y].size+tr[x].cnt;
                x=tr[x].s[1];
            }
            else if(tr[y].size>=k) x=tr[x].s[0];
            else break;
        }
        splay(x,0);
        return tr[x].v;
    }
    void insert(int v){
        int x=root,p=0;
        while(x&&tr[x].v!=v) p=x,x=tr[x].s[v>tr[x].v];
        if(x) tr[x].cnt++;
        else{
            x=++idx;
            tr[p].s[v>tr[p].v]=x;
            tr[x].init(p,v);
        }
        splay(x,0);
    }
    int get_rank(int v){
        insert(v);
        int res=tr[tr[root].s[0]].size;
        del(v);
        return res;
    }
// int main(){
//     insert(-1e9),insert(1e9);
//     int n;
//     scanf("%d",&n);
//     while(n--){
//         int op,x;
//         scanf("%d%d",&op,&x);
//         if(op==1) insert(x);
//         if(op==2) del(x);
//         if(op==3) printf("%d\n",get_rank(x));
//         if(op==4) printf("%d\n",get_val(x+1));
//         if(op==5) printf("%d\n",tr[get_pre(x)].v);
//         if(op==6) printf("%d\n",tr[get_suc(x)].v);
//     }
// }
};

// ST表
struct ST{
    const ll N=3e5+10;
    ll a[N],Log[N],st[N][20];// a 下标从 1 开始
    // 对 a[1..n] 建 ST 表（区间最小值）
    void init_st(ll n){
        Log[1]=0;
        for(int i=2;i<=n+1;i++) Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++) st[i][0]=a[i];
        for(int j=1;(1ll<<j)<=n;j++)
            for(int i=1;i+(1ll<<j)-1<=n;i++)
            st[i][j]=min(st[i][j-1],st[i+(1ll<<(j-1))][j-1]);
    }
    // 查询 a[L..R] 最小值
    ll query_min(ll L,ll R){
        ll k=Log[R-L+1];
        return min(st[L][k],st[R-(1ll<<k)+1][k]);
    }
};

// string hash
struct string_hash{
    typedef unsigned long long ULL;
    const ll P=131;
    unordered_set<ll> a;
    ULL p[2200],h[2200];
    ll init(string s){
        p[0]=1,h[0]=0;
        for(int i=1;i<=s.length();i++){
            p[i]=p[i-1]*P;
            h[i]=h[i-1]*P+s[i-1];
        }
        return h[s.length()];
    }
    ll gethash(ll l,ll r){
        return h[r]-h[l-1]*p[r-l+1];
    }
    ll sbstr(ll l1,ll r1,ll l2,ll r2){
        return gethash(l1,r1)==gethash(l2,r2);
    }
}
/*
相当于生成了一个p进制先的多位数
然后计算前缀和时需要把前面一段的位数提高再减，得到正确的hash值
*/

// string_prefix
void prefix(){
    string s; cin>>s;
    for(int i=1;i<s.length();i++){
        ll j=pi[i-1];
        while(j>0&&s[j]!=s[i]) j=pi[j-1];//跳到子问题的最大值位置，即i-1那一段所能求得的前缀最大那一段
        if(s[i]==s[j]) j++;
        pi[i]=j;
    }
    for(int i=0;i<s.length();i++)cout<<pi[i]<<" "; cout<<endl;
}
/*
比如字符串为acaca...acacc
           01234      ^
               ^      |
               |      i
               j
j此时为4，判断下面这个等式，不成立，那么长度只能是p[j-1]的最大值
(p[j]是要比较的值，所以最大前缀值实际上是j-1)，这样就得到了第二小的值
如果合法，那么s[p[i]]==s[i+1]
因为长度为x的话，而是string从0开始的，
所以如果相等则符合要求，找到了一个位置可以+1
*/

struct tarjan_LCA{
    #define ll long long
    #define ld long double
    #define pb push_back
    const ll N=5e5+10;
    ll n,m,root;
    ll fa[N],vis[N],ans[N];
    vector<ll> g[N];
    vector<pair<ll,ll>> q[N];
    ll find(ll x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void tarjan(ll now){
        vis[now]=1;
        for(int next:g[now]){
            if(!vis[next]){
                tarjan(next);
                fa[next]=now;
            }
        }
        for(auto[othor,id]:q[now]){
            if(vis[othor]) ans[id]=find(othor);
        }
    }
    void solve(){
        cin>>n>>m>>root;
        for(int i=1;i<=n;i++) fa[i]=i;
        for(int i=1;i<n;i++){
            ll u,v; cin>>u>>v;
            g[u].pb(v); g[v].pb(u);
        }
        for(int i=1;i<=m;i++){
            ll u,v; cin>>u>>v;
            q[v].pb({u,i}); q[u].pb({v,i});
        }
        tarjan(root);
        for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
    }
};

// 树状数组
struct fenwick_tree{
    ll c[200010],n;//树状数组的常见写法
    int lowbit(int x){return x&-x;}
    int getsum(int x){  // a[1]..a[x]的和
        int ans=0;
        while(x>0){
            ans=ans+c[x];
            x=x-lowbit(x);
        }
        return ans;
    }
    void add(int x,int k){ // idx,val
        while(x<=n){  // 不能越界
            c[x]=c[x]+k;
            x=x+lowbit(x);
        }
    }
};

// fenwick_tree_prefix
struct fenwicktree_prefix{
    ll t1[1000005],t2[1000005],n;
    ll lowbit(int x) {return x&(-x);}
    void build(ll k,ll v){
        ll v1=v*k;
        while(k<n){
            t1[k]+=v;t2[k]+=v1;
            k+=lowbit(k);
        }
    }
    ll getsum(ll *t1,int k){
        ll sum=0;
        while(k>0){
            sum+=t1[k];
            k-=lowbit(k);
        }
        return sum;
    }
    void add(ll k,ll v){
        build(k,v);
    }
    void change(ll l,ll r,ll v){
        add(l,v);add(r+1ll,-v);
    }
    ll getsum1(ll l,ll r){
        return (r+1ll)*getsum(t1,r)+l*getsum(t1,l-1ll)-getsum(t2,r)-getsum(t2,l-1ll);
    }
};

struct Trie{
  // 字典树,字典树的根,节点数量
  ll root=0,cnt=0;
  vector<vector<ll>> t;
  vector<ll> num;// 字典树中的数字
  Trie(){t.emplace_back(2,0);}
  void insert(ll x){
    num.pb(x);
    ll p=root;
    for(int i=32;i>=0;i--){
      if(!t[p][(x>>i)&1]){
        t[p][(x>>i)&1]=++cnt;
        t.emplace_back(2,0);
      }
      p=t[p][(x>>i)&1];
    }
  }
  ll query_min(ll x){
    ll p=root,ans=0;
    for(int i=32;i>=0;i--){
      ll u=(x>>i)&1;
      ans=ans*2+(t[p][u]?u:!u);
      p=t[p][u]?t[p][u]:t[p][!u];
    }
    return ans;
  }
  ll query_max(ll x){
    ll p=root,ans=0;
    for(int i=32;i>=0;i--){
      ll u=(x>>i)&1;
      ans=ans*2+(t[p][!u]?!u:u);
      p=t[p][!u]?t[p][!u]:t[p][u];
    }
    return ans;
  }
  friend void merge(Trie&x,Trie&y){
    if(x.num.size()<y.num.size()) swap(x,y);
    for(ll i:y.num) x.insert(i);
    y=Trie();
  }
};



// Z func
void Z(){
    string t; cin>>t;
    vector<ll> zt(t.length());
    zt[0]=t.length();
    for(ll i=1,l=0,r=0;i<t.length();i++){
        if(i<=r)zt[i]=min(zt[i-l],r-i+1);
        while(t[zt[i]]==t[i+zt[i]]&&i+zt[i]<t.length()) zt[i]++;
        if(i+zt[i]-1>r) l=i,r=zt[i]+i-1;
    }
    for(auto &i:zt) cout<<i<<" "; cout<<endl;
}
/*
zt记录的是字符串中，每一个位置作为起点能和开头匹配上的最长长度
方法和马拉车算法类似，规定一个盒子，在盒子内的使用之前的数据，
但是注意可能会超出边界，因此要加上一个判断。
之后更新答案，这里没有判断在盒子外的才扩张是因为：
如果可以发生扩张，那么说明现在这个边界不是最优的，因此如果在盒子内不会进入while
因此这个算法和manacher一样是O(n),
除此之外这个算法就和之前的前缀算法没有太大区别了
*/
```