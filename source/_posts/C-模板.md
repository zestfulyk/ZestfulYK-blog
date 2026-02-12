---
title: C++模板
date: 2026-01-23 15:37:48
tags: 算法
---

# 说明

这些是我平时攒下来的模板,现在送给大家!

# 火车头

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
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define debug(a) cout<<a<<" ";
#define endl '\n'
mt19937 rnd(time(nullptr));
ll lowerbit(ll x){return x&(-x);}
ll binary_min_palce(ll x){return(__builtin_ctz(x));}//返回二进制最后有几个0
ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}
void rad(ll h[],ll maxn,ll minn,ll n){default_random_engine e(time(0));
uniform_int_distribution<int> u(minn,maxn);for(int i=1;i<=n;i++)h[i]=u(e);}
template<typename T>void fast_erase(vector<T>& container,typename std::vector<T>::size_type index){
if(index>=container.size()) return;if(index!=container.size()-1)
container[index]=move(container.back());container.pop_back();}
inline void read128(__int128&x){x=0;__int128 f=1;char ch=getchar();
while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch =getchar();}}
void print128(__int128 x){if(x<0){putchar('-');x=-x;}
if(x>9)print128(x/10);putchar(x%10+'0');}
const ll inf=1e9+1;
const ll mod=998244353;
const ld pi=atan2(0,-1);
const ld eps=1e-6;
```
# 水印

```C++
/*0.注意vector的size是size_t不能直接减去一个数，要类型转换
1.深呼吸，不要紧张，慢慢读题，读明白题，题目往往比你想的简单。
2.暴力枚举:枚举什么，是否可以使用一些技巧加快枚举速度（预处理、前缀和、数据结构、数论分块）。
3.贪心:需要排序或使用数据结构（pq）吗，这么贪心一定最优吗。
4.二分：满足单调性吗，怎么二分，如何确定二分函数返回值是什么。
5.位运算：按位贪心，还是与位运算本身的性质有关。
6.数学题：和最大公因数、质因子、取模是否有关。
7.dp：怎么设计状态，状态转移方程是什么，初态是什么，使用循环还是记搜转移。
8.搜索：dfs 还是 bfs ，搜索的时候状态是什么，需要记忆化吗。
9.树上问题：是树形dp、树上贪心、或者是在树上搜索。
10.图论：依靠什么样的关系建图，是求环统计结果还是最短路。
11.组合数学：有几种值，每种值如何被组成，容斥关系是什么。
12.交互题：log(n)次如何二分，2*n 次如何通过 n 次求出一些值，再根据剩余次数求答案。
13.如果以上几种都不是，多半是有一个 point 你没有注意到，记住正难则反.
  _____  _____   ____    _____   _____   _   _   _      __   __  _  __
 |__  / | ____| / ___|  |_   _| |  ___| | | | | | |     \ \ / / | |/ /
   / /  |  _|   \___ \    | |   | |_    | | | | | |      \ V /  | ' /
  / /_  | |___   ___) |   | |   |  _|   | |_| | | |___    | |   | . \   |
 /____| |_____| |____/    |_|   |_|      \___/  |_____|   |_|   |_|\_\  |*/
```

# INT128

```C++
// 字符串转 __int128
inline void read128(__int128 &x){
    x=0;
    __int128 f=1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
}
// __int128 转字符串（输出用）
void print128(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print128(x / 10);
    putchar(x % 10 + '0');
}
int main() {
    // 读取 __int128
    __int128 a; read128(a);
    __int128 b; read128(b);
    // 运算（和普通整数一样）
    __int128 sum = a + b;
    __int128 product = a * b;
    // 输出
    cout << "Sum: ";
    print128(sum);
    cout << "Product: ";
    print128(product);
    return 0;
}
```

# 01背包val_base

```c++
const ll INF=1e9;
ll w[110],v[110],sum=0,n,f[100010],ans=0,W;
int main(){
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
```

# 01背包

```C++
ll N,W,w[200010],v[200010],ans[200010];
int main(){
    cin>>N>>W;
    for(int i=1;i<=N;i++)
        cin>>w[i]>>v[i];
    for(int i=1;i<=N;i++){
        for(int l=W;l>=w[i];l--){
            ans[l]=max(ans[l-w[i]]+v[i],ans[l]);
        }
    }
    cout<<ans[W]<<endl;
}
/*仔细观察代码可以发现：对于当前处理的物品 𝑖
i 和当前状态 𝑓𝑖,𝑗
f_{i,j}，在 𝑗 ⩾𝑤𝑖
j\geqslant w_{i} 时，𝑓𝑖,𝑗
f_{i,j} 是会被 𝑓𝑖,𝑗−𝑤𝑖
f_{i,j-w_{i}} 所影响的。这就相当于物品 𝑖
i 可以多次被放入背包，与题意不符。
（事实上，这正是完全背包问题的解法）*/
```

# 01bfs

```C++
const int INF = 0x3f3f3f3f;
const int MAXN = 1e5+1;
vector<pair<int, int>> graph[MAXN];
int main(){
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
                dq.push_front(v);  // 边权0，加入前端
            } else if (w == 1 && dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                dq.push_back(v);   // 边权1，加入后端
            }
        }
    }
}
```

# 单调队列

```C++
int h=0,t=-1,q[1000010],n,a[1000010];
int main(){
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
加上前缀和，减掉最小位置就行了*/
```

# 单调栈

```C++
stack<ll> s;
ll N,ans[3000010],a[3000010];
int main(){
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
```

# 多重背包

```C++
ll f[200010],n,V,q[200010],g[200010];
int main(){
    cin>>n>>V;
    for(int i=1;i<=n;i++){
        memcpy(g,f,sizeof(f));
        ll v,w,s; cin>>w>>v>>s;  //vol worth shu
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
/*因为更新时是分为余数相同的v-1类的
因为当余数为j时，只会访问相同余数的情况，而且是有一定范围的(窗口)
每一类都可以单独用单调队列来优化，这样每次都可以取到最大值
从而优化代码的复杂度，不然相当于每种情况都在寻找最小值，不优*/
```

# 二维背包

```C++
ll f[2010][2010],V,M,n;
int main(){
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
w为重量(第二维)*/
```

# 分组背包

```C++
ll f[200010],n,V,v[200010],w[200010]; //vol worth
int main(){
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
/*和01背包同理，需要从后往前计算保证每种物品只被计算一遍*/
```

# 高斯约旦消元法

```C++
const double eps=1e-8;
double a[110][110];
void solve(){
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
```

# 快速幂

```C++
long long quickpow(ll a, ll b, ll m){
    ll sum=1;
    while(b>0){
        if(b&1)
            sum=sum*a%m;
        a=a*a%m;
        b>>=1;
    }
    return sum;
}
```

# 区间dp

```C++
ll n,a[410],ans[410][410],sum[410];
int main(){
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
/*首先，每个区间自己合并的代价是0，
之后枚举长度，枚举起点，计算每个区间的值，
记得加上区间的总值，即合并后所需的代价。*/
```

# 拓扑排序

```C++
const ll MAXN=200010;
ll n, m;
vector<ll> G[MAXN];
ll in[MAXN];  // 存储每个结点的入度
bool toposort() {
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
```

# 依赖背包

```C++
ll n,v[65],w[65],f[65][32010],V;
vector<ll> a[65];
void dfs(ll now){
    for(int i=v[now];i<=V;i++)
        f[now][i]=v[now];
    for(auto &s:a[now]){
        dfs(s);
        for(int j=V;j>=v[now];j--)
            for(int k=v[s];k+v[now]<=j;k++)
                f[now][j]=max(f[now][j],f[now][j-k]+f[s][k]);
    }
}
int main(){
    cin>>V>>n;
    for(int i=1;i<=n;i++){
        ll f; cin>>v[i]>>w[i]>>f;
        a[f].push_back(i);
    }
    dfs(0);
    cout<<f[0][V]<<endl;
}
/*循环时，从根往上计算，外层遍历体积，内层为决策，
看选择子树体积为k时是否合理来判断要不要选择。
f[i][j]表示选择i时体积为j的最大值*/
```

# 字典树

```C++
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
```

# 最大区间和

```C++
ll a[200010];
int main(){
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
```

# dijkstra

```C++
long long N;
const long long INF=1e18;
vector<pair<LL,LL>> g[10010];
int main(){
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
```

# 交互题

```C++
int main(){
    int T; cin>>T;
    while(T--){
        ll n,y; cin>>n;
        ll sum=n*(n+1)/2;
        cout<<"2 1 "<<n<<endl;
        cout.flush();
        cin>>y;
        ll len=y-sum,l=1,r=n;
        while(l<=r){
            ll mid=(l+r)>>1;
            cout<<"1 1 "<<mid<<endl;
            cout.flush();
            ll last; cin>>last;
            cout<<"2 1 "<<mid<<endl;
            cout.flush();
            ll now; cin>>now;
            ll f=now-last;
            if(f==0) l=mid+1;
            else r=mid-1;
        }
        cout<<"! "<<l<<" "<<l+len-1<<endl;
        cout.flush();
    }
}
```

# KMP

```C++
int main(){
    string t,p; cin>>t>>p;
    vector<ll> ans,pi(p.length());
    for(int i=1;i<p.length();i++){
        ll j=pi[i-1];
        while(j>0&&p[j]!=p[i]) j=pi[j-1];
        if(p[i]==p[j]) j++;
        pi[i]=j;
    }//上面是next函数，对pattern数据处理，方便查找长度
    for(int i=0,j=0;i<t.length();i++){
        while(j>0&&t[i]!=p[j])j=pi[j-1];
        if(p[j]==t[i])j++;
        if(j==p.length()){
            ans.push_back(i-p.length()+1);
            j=pi[j-1];
        }
    }//计算可能的位置
    for(auto &i:ans) cout<<i+1<<endl;
    for(int i=0;i<p.length();i++) cout<<pi[i]<<" "; cout<<endl;
}
/*关键点，比较时j会向前跳，pi[j]记录的依旧是长度
可以用计算前缀的函数来理解
最后记得要向前跳一位，因为不然下一次会直接认为是正确答案
而且跳不回去了，所以要j=pi[j-1]*/
```

# LCS

```C++
ll f[3010][3010],p[3010][3010];
string s,t;
int main(){
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
```

# Mabacher

```C++
const ll INF=1e18;
ll p[22000010],mid=0,r=0,ans=1;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
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
/*加入几个字符使得每一段都是奇数，然后记录的是半径，所以值为r-1
然后如果在已知最右范围之内，那么就先默认为对称值，之后再扩张更新
初始化时记得使用vector，因为用字符串的相加是需要O(n)时间复杂度*/
```

# SPFA

```C++
const long long INF=1e18;
vector<pair<LL,LL>> g[10010];
int main(){
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
```

# String Hash

```C++
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
```


# String prefix

```C++
ll pi[300010];
int main(){
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
           01234      ^
               ^      |
               |      i

               j

j此时为4，判断下面这个等式，不成立，那么长度只能是p[j-1]的最大值
(p[j]是要比较的值，所以最大前缀值实际上是j-1)，这样就得到了第二小的值
如果合法，那么s[p[i]]==s[i+1]
因为长度为x的话，而是string从0开始的，
所以如果相等则符合要求，找到了一个位置可以+1*/
```

# substr

```C++
int main() {
    std::string str = "Short";
    // 安全使用：检查位置是否有效
    size_t pos = 10;
    if (pos < str.length()) {
        std::string sub = str.substr(pos);
        std::cout << sub << std::endl;
    } else {
        std::cout << "位置超出字符串范围！" << std::endl;
    }
    // 如果长度超过字符串剩余部分，会自动调整
    std::string safe_sub = str.substr(2, 100); // 只会提取 "ort"
    std::cout << safe_sub << std::endl;
    std::string filename = "document.pdf";
    // 找到最后一个点的位置
    size_t dotPos = filename.find_last_of('.');
    if (dotPos != std::string::npos) {
        std::string extension = filename.substr(dotPos + 1);
        std::cout << "文件扩展名: " << extension << std::endl; // 输出 "pdf"
    }
    std::string str = "Hello, World!";
    // 提取前 5 个字符
    std::string sub3 = str.substr(0, 5);
    std::cout << sub3 << std::endl; // 输出 "Hello"
    return 0;
}
```

# 树状数组

```C++
ll c[200010],n;//树状数组的常见写法
int lowbit(int x){return x&-x;}
int getsum(int x){  // a[1]..a[x]的和
    int ans=0;
    while(x>0){
        ans=ans+c[x];
        x=x-lowbit(x);
    }
    return ans;
}
void add(int x,int k){ // idx,val
    while(x<=n){  // 不能越界
        c[x]=c[x]+k;
        x=x+lowbit(x);
    }
}
```

# 树状数组前缀和

```C++
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
```

# Z函数

```C++
int main(){
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
除此之外这个算法就和之前的前缀算法没有太大区别了*/
```

# 并查集

```C++
const int N = 2e5+5;
int fa[N];
int n, m;
int find(int x){
    if(fa[x] == x) return x;
    else return fa[x] = find(fa[x]); // 比起朴素代码只改了这里
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) fa[i] = i; // 初始化
    for(int i = 1; i <= m; ++i){
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 1){ // 合并操作
            x = find(x), y = find(y); // 查询各自的代表元素
            if(x == y) continue; // 如果已经在同一个集合，跳过
            fa[x] = y; // 这里的合并顺序可以任意
        }
        else{ // 查询操作的一种变形
            x = find(x), y = find(y); // 查询各自的代表元素
            if(x == y) cout << "Y" << endl; // 是否在同一个集合
            else cout << "N" << endl;
        }
    }
    return 0;
}
```

# 最小生成树

```C++
int fa[1010];  // 定义父亲
int n, m, k;
struct edge {
  int u, v, w;
};
int l;
edge g[10010];
void add(int u, int v, int w) {
  l++;
  g[l].u = u;
  g[l].v = v;
  g[l].w = w;
}
// 标准并查集
int findroot(int x) { return fa[x] == x ? x : fa[x] = findroot(fa[x]); }
void Merge(int x, int y) {
  x = findroot(x);
  y = findroot(y);
  fa[x] = y;
}
bool cmp(edge A, edge B) { return A.w < B.w; }
// Kruskal 算法
void kruskal() {
  int tot = 0;  // 存已选了的边数
  int ans = 0;  // 存总的代价
  for (int i = 1; i <= m; i++) {
    int xr = findroot(g[i].u), yr = findroot(g[i].v);
    if (xr != yr) {        // 如果父亲不一样
      Merge(xr, yr);       // 合并
      tot++;               // 边数增加
      ans += g[i].w;       // 代价增加
      if (tot == n - k) {  // 检查选的边数是否满足 k 个棉花糖
        cout << ans << '\n';
        return;
      }
    }
  }
  cout << "No Answer\n";  // 无法连成
}
int main() {
  cin >> n >> m >> k;
  if (n == k) {  // 特判边界情况
    cout << "0\n";
    return 0;
  }
  for (int i = 1; i <= n; i++) {  // 初始化
    fa[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    add(u, v, w);  // 添加边
  }
  sort(g + 1, g + m + 1, cmp);  // 先按边权排序
  kruskal();
  return 0;
}
```

# 欧拉筛

```C++
vector<int> pri;
bool not_prime[N];
void pre(int n) {
  for (int i = 2; i <= n; ++i) {
    if (!not_prime[i]) {
      pri.push_back(i);
    }
    for (int pri_j : pri) {
      if (i * pri_j > n) break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0) {
        // i % pri_j == 0
        // 换言之，i 之前被 pri_j 筛过了
        // 由于 pri 里面质数是从小到大的，所以 i 乘上其他的质数的结果一定会被
        // pri_j 的倍数筛掉，就不需要在这里先筛一次，所以这里直接 break
        // 掉就好了
        break;
      }
    }
  }
}
```

# 离散化

```C++
// std::vector<int> arr;
std::vector<int> tmp(arr);  // tmp 是 arr 的一个副本
std::sort(tmp.begin(), tmp.end());
tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
for (int i = 0; i < n; ++i)
  arr[i] = std::lower_bound(tmp.begin(), tmp.end(), arr[i]) - tmp.begin();
```

# 线段树

```C++
void build(int s, int t, int p) {
  // 对 [s,t] 区间建立线段树,当前根的编号为 p
  if (s == t) {
    d[p] = a[s];
    return;
  }
  int m = s + ((t - s) >> 1);
  // 移位运算符的优先级小于加减法，所以加上括号
  // 如果写成 (s + t) >> 1 可能会超出 int 范围
  build(s, m, p * 2), build(m + 1, t, p * 2 + 1);
  // 递归对左右区间建树
  d[p] = d[p * 2] + d[(p * 2) + 1];
}
int getsum(int l, int r, int s, int t, int p) {
  // [l, r] 为查询区间, [s, t] 为当前节点包含的区间, p 为当前节点的编号
  if (l <= s && t <= r)
    return d[p];  // 当前区间为询问区间的子集时直接返回当前区间的和
  int m = s + ((t - s) >> 1), sum = 0;
  if (l <= m) sum += getsum(l, r, s, m, p * 2);
  // 如果左儿子代表的区间 [s, m] 与询问区间有交集, 则递归查询左儿子
  if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
  // 如果右儿子代表的区间 [m + 1, t] 与询问区间有交集, 则递归查询右儿子
  return sum;
}
```

## 懒标记修改法

```C++
// [l, r] 为修改区间, c 为被修改的元素的变化量, [s, t] 为当前节点包含的区间, p
// 为当前节点的编号
void update(int l, int r, int c, int s, int t, int p) {
  // 当前区间为修改区间的子集时直接修改当前节点的值,然后打标记,结束修改
  if (l <= s && t <= r) {
    d[p] += (t - s + 1) * c, b[p] += c;
    return;
  }
  int m = s + ((t - s) >> 1);
  if (b[p] && s != t) {
    // 如果当前节点的懒标记非空,则更新当前节点两个子节点的值和懒标记值
    d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
    b[p * 2] += b[p], b[p * 2 + 1] += b[p];  // 将标记下传给子节点
    b[p] = 0;                                // 清空当前节点的标记
  }
  if (l <= m) update(l, r, c, s, m, p * 2);
  if (r > m) update(l, r, c, m + 1, t, p * 2 + 1);
  d[p] = d[p * 2] + d[p * 2 + 1];
}

  

int getsum(int l, int r, int s, int t, int p) {
  // [l, r] 为查询区间, [s, t] 为当前节点包含的区间, p 为当前节点的编号
  if (l <= s && t <= r) return d[p];
  // 当前区间为询问区间的子集时直接返回当前区间的和
  int m = s + ((t - s) >> 1);
  if (b[p]) {
    // 如果当前节点的懒标记非空,则更新当前节点两个子节点的值和懒标记值
    d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
    b[p * 2] += b[p], b[p * 2 + 1] += b[p];  // 将标记下传给子节点
    b[p] = 0;                                // 清空当前节点的标记
  }
  int sum = 0;
  if (l <= m) sum = getsum(l, r, s, m, p * 2);
  if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
  return sum;
}
```

## 直接修改为特定值

```C++
void update(int l, int r, int c, int s, int t, int p) {
  if (l <= s && t <= r) {
    d[p] = (t - s + 1) * c, b[p] = c, v[p] = 1;
    return;
  }
  int m = s + ((t - s) >> 1);
  // 额外数组储存是否修改值
  if (v[p]) {
    d[p * 2] = b[p] * (m - s + 1), d[p * 2 + 1] = b[p] * (t - m);
    b[p * 2] = b[p * 2 + 1] = b[p];
    v[p * 2] = v[p * 2 + 1] = 1;
    v[p] = 0;
  }
  if (l <= m) update(l, r, c, s, m, p * 2);
  if (r > m) update(l, r, c, m + 1, t, p * 2 + 1);
  d[p] = d[p * 2] + d[p * 2 + 1];
}
int getsum(int l, int r, int s, int t, int p) {
  if (l <= s && t <= r) return d[p];
  int m = s + ((t - s) >> 1);
  if (v[p]) {
    d[p * 2] = b[p] * (m - s + 1), d[p * 2 + 1] = b[p] * (t - m);
    b[p * 2] = b[p * 2 + 1] = b[p];
    v[p * 2] = v[p * 2 + 1] = 1;
    v[p] = 0;
  }
  int sum = 0;
  if (l <= m) sum = getsum(l, r, s, m, p * 2);
  if (r > m) sum += getsum(l, r, m + 1, t, p * 2 + 1);
  return sum;
}
```