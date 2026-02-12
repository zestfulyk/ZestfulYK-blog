---
title: DP变种,n过大找规律题
date: 2025-2-12 09:26:45
tags: 算法
mathjax: true
---
- 题目:
要用`qcjjkkt`,和`td`构造字符串,每出现一个`qcjjkkt`获得a快乐度,每个`td`获得b快乐度
即只有三种物品,体积为2,7,8,价值为a,b,a+b,数量无限,n上限为$10^9$,求最大价值

- 方法:
完全背包

但是发现貌似超时,此时发现若n为56倍数很好解决,所以先提取完整的56,剩下部分单独计算.

然后发现`qcjjkkt`和`td`可以连接,要是前面56的循环选的是`qcjjkkt`最后如果剩下1位置,可以填入d,所以得加上特判,太麻烦了,所以改为计算最后112个就行

AC代码:

```C++
void solve(){
  ll n,a,b; cin>>n>>a>>b;
  vector<ll> dp(120,0);
  ll ans=0;
  if(n>112){
    ans=(n/56-1)*max({28*b,8*a,7*(a+b)});
    n-=(n/56-1)*56;
  }
  for(int i=2;i<=n;i++) dp[i]=max(dp[i-2]+b,dp[i]);
  for(int i=7;i<=n;i++) dp[i]=max(dp[i-7]+a,dp[i]);
  for(int i=8;i<=n;i++) dp[i]=max(dp[i-8]+b+a,dp[i]);
  cout<<ans+dp[n]<<endl;
}
```