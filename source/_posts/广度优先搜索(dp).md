---
title: 广度优先搜索变形(dp)
date: 2025-2-24 23:56:00
tags: 算法
mathjax: true
---
用途:查询最短路,计算答案值范围较小的`dp`题目

最短路就不解释了,讲讲第二种是怎么回事

题目:给定两个数组a,b($a_i,b_i<2048$),长度为n$(1<n<2048)$,x初始为0,每次允许操作
$$\begin{cases}
x=max(0,x-a_i)\\ \\
x=x\oplus b[i]
\end{cases}
$$
求最后x的最大值

因为a对x的影响是减小,b是增大,异或b以后也不会超过2048,也就是最多2048个答案,那么可以用类似广搜的做法来计算每一步能取到的所有答案,这样就不需要`dfs`了


所以代码:

```C++
void solve(){
  ll n; cin>>n;
  vector<ll> a(n+1),b(n+1);
  for(int i=1;i<=n;i++) cin>>a[i];
  for(int i=1;i<=n;i++) cin>>b[i];
  set<ll> last; last.insert(0);
  for(int i=1;i<=n;i++){
    set<ll> now;
    for(int j:last){
      now.insert(max(0ll,j-a[i]));
      now.insert((j^b[i]));
    }
    last=now;
  }
  ll maxn=-1;
  for(int i:last) maxn=max(maxn,i);
  cout<<maxn<<endl;
}
```