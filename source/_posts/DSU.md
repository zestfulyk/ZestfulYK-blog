---
title: DSU模板
date: 2025-2-24 23:56:00
tags: 算法
mathjax: true
---
`DSU`是并查集的缩写

总共有三种操作

初始化,查找根节点和连接

代码如下:

```C++
struct dsu{//dsu std
  vector<ll> fa,sz;
  dsu(ll n):fa(n+1),sz(n+1,1){
    for(int i=1;i<=n;++i){
      fa[i]=i;
    }
  }
  ll find(ll x){return fa[x]==x?x:fa[x]=find(fa[x]);}
  void uni(ll x,ll y){
    if(sz[x]<sz[y]) swap(x,y);
    fa[y]=x;
    sz[x]+=sz[y];
  }
};
```

使用方法如下:

```C++
dsu dsu1(n);
ll fu=dsu1.find(u),fv=dsu2.find(v);
if(fu!=fv) uni(fv,fu);
```

加了一个`sz`数组来计算每片区域的大小,这样就能防止图退化成一条链