---
title: 网络赛II Exponent题解
date: 2026-09-17 22:43:43
tags: 算法
mathjax: true
---
# 题意

给定n,求
$$\sum_{i=1}^n ord(i)$$
其中`ord(i)`指的是i在模n意义下的阶,也就是满足
$$i^x\equiv1 \ (\ mod \ n\ )$$
的最小x,不存在则为0

要做出这道题,需要三大块前置知识 : **卷积,群论,CRT(中国剩余定理)**

卷积知识看我之前法的卷积博客,这里不过多讲解

传送门:[卷积学习笔记](https://zestfulyk.github.io/ZestfulYK-blog/2026/08/31/%E5%8D%B7%E7%A7%AF%E5%AD%A6%E4%B9%A0/)
# 前置知识讲解1

群论的基本知识这里不赘述了,大学离散数学默认你学过了,这里只讲解一下群的阶
## 群的阶

首先定义群的阶为群的大小(元素个数),记为`|G|`

比如循环四元群的阶大小就是4
## 元素的阶

元素的阶就是`ord(i)`

根据拉格朗日定理可知,`ord(i) | |G|`

此外,`ord(i)`的倍数x都满足:
$$i^x\equiv1 \ (\ mod \ n\ )$$
这个看似废话的性质(设为**性质1**)正是后面转化的第一步

此外,若考虑的模n整数乘法群(所有与n互质的数构成的群),像题目中的这种的话,会有更多性质

首先这个循环群的阶显然等于$\varphi(n)$,因为定义告诉我们是所有互质的数构成的

因为`ord(i) | |G|`,并且`ord(i)`的倍数依然有效,所以所有的元素的阶小于$\varphi(n)$,并且是其一个因数

---

到这里,我们就能进行我们的第一步转化了
# 转化1

因为要求的是
$$\sum_{i=1}^n ord(i)$$
那么我们可以根据`ord(i)`来分类,统计其数量在乘以值

设:
$$A(d)=\#\{\ g\in G\ |\ ord(g)=d\ \}$$
其中#表示元素个数

所以转化为:
$$\sum_{d|\varphi(n)}d\cdot A(d)$$
接下来,再设:
$$F(m)=\#\{\ g\in G\ |g^m\equiv1 \ (\ mod \ n\ )\}$$
显然,满足`d|m`的A(d),都满足F(m)的要求(上文性质1),所以得到:
$$F(m)=\sum_{d|m}A(d)$$
然后两边同时卷上$\mu$,也就是进行一下莫反(熟悉莫反的请自动忽略以下步骤)
$$\begin{split}
F(m)&=\sum_{d|m}A(d)\\
F&=1 * A\\
\mu * F&=\mu * 1 * A\\
\mu * F&=\varepsilon \ * A\\
\sum_{m|d}\mu(\frac{d}{m})F(m)&=\sum_{m|d}\varepsilon(\frac{d}{m})A(m)\\
\sum_{m|d}\mu(\frac{d}{m})F(d)&=A(d)\\
A(d)&=\sum_{m|d}\mu(\frac{d}{m})F(m)\\
\end{split}$$
(注意此处的m已经不是原来的m了,卷积后带入的是d)

所以原式:
$$\begin{split}
&\sum_{i=1}^n ord(i)\\
=&\sum_{d|\varphi(n)}d\cdot A(d)\\
=&\sum_{d|\varphi(n)}d\sum_{m|d}\mu(\frac{d}{m})F(m)
\end{split}$$
接下来依旧是尝试交换求和顺序,如果改成先计算F(m),再看m被计算的次数.因此交换求和顺序的第一步应该得到:
$$\begin{split}
&\sum_{i=1}^n ord(i)\\
=&\sum_{d|\varphi(n)}d\sum_{m|d}\mu(\frac{d}{m})F(m)\\
=&\sum_{m|\varphi(n)}F(m)\sum_{d|\frac{\varphi(n)}{m}}\mu(\frac{d}{m})\cdot d
\end{split}$$
接下来设`d=mk`,所以
$$\begin{split}
&\sum_{i=1}^n ord(i)\\
=&\sum_{m|\varphi(n)}F(m)\sum_{d|\frac{\varphi(n)}{m}}\mu(\frac{d}{m})\cdot d\\
=&\sum_{m|\varphi(n)}m\cdot F(m)\sum_{k|\frac{\varphi(n))}{m}}\mu(\frac{mk}{m})\cdot mk\\
=&\sum_{m|\varphi(m)}m\cdot F(m)\sum_{k|\frac{\varphi(n)}{m}}k\mu(k)
\end{split}$$
# 补充知识讲解2

关键式子:
$$\sum_{m|M}m\mu(m)=\prod_{p|M}(1-p)$$
其中p是M的素因子

要证明这个式子成立,依旧先证明这个是一个积性函数

设`f(M)`等于上述式子,再假设`gcd(a,b)=1`,所以`ab`的因数可以被唯一的写成a的因数`d1`和b的因数`d2`的乘积

所以
$$f(ab)=\sum_{d_1|a,d_2|b}(d_1d_2)\mu(d_1d_2)$$
而`ab`互质,所以`d1`和`d2`互质,所以可以使用$\mu$的积性的性质,化简为:
$$f(ab)=\sum_{d|ab}(d)\mu(d)$$
因此是积性函数

当$M=p^e$时
$$f(M)=\sum_{m|M}m\mu(m)=1\cdot 1+(-1)\cdot p=1-p$$
所以可以拆分n,然后再乘起来就行了,因此原式成立,这个也是莫比乌斯函数最重要的应用之一
# 计算F(m)

根据补充的这一个转化,原式可以进一步变形为:
$$\begin{split}
&\sum_{i=1}^n ord(i)\\
=&\sum_{m|\varphi(m)}m\cdot F(m)\sum_{k|\frac{\varphi(n)}{m}}k\mu(k)\\
=&\sum_{m|\varphi(m)}m\cdot F(m)\prod_{p|\frac{\varphi(n)}{m}}(1-p)
\end{split}$$
那么可以发现的是,上述式子中值剩下一个F(m)是计算困难的了

接下来考虑怎么计算`F(m)`就行了

看一下`F(m)`的定义:
$$F(m)=\#\{\ g\in G\ |\ g^m\equiv1 \ (\ mod \ n\ )\}$$
为了计算F(m),这里就不得不学习一下CRT(中国剩余定理)了
## 补充知识讲解3

中国剩余定理,用于解长这个样子的同余方程:
$$\begin{cases}x\equiv a_1\ (\ mod \ n_1\ )\\
x\equiv a_2\ (\ mod \ n_2\ )\\
\cdots\\
x\equiv a_k\ (\ mod \ n_k\ )\\
\end{cases}$$
此处,如果几个n互质,那么x是由唯一解的

换句话说,如果后面的模数是互质的,那么只要知道了余数A数组,就能唯一确定一个数;反过来,要是给定一个数,他对应的余数也是唯一确定的

因为$x^m\equiv1 \ (\ mod \ n\ )$,所以$n|x^m-1$,而n可以被拆分成为多个质数的乘积,所以$p_i^{e_j}|x^m-1$,也就是$x^m\equiv1 \ (\ mod \ p_i^{e_j}\ )$

而中国剩余定理告诉我们,只要知道余数就能确定唯一的x,所以我们只要知道有多少组余数解就行了

因此,只要知道满足单个方程的解的数量,全部乘在一起就是`F(m)`了
### 小例子

比如n=15,m=2时,

群G={1,2,4,7,8,11,13,14}

15可以被拆成3和5,接下来列出余数表:

| num | mod 3 | mod 5 | pair |
| --- | --- | --- | --- |
| 1   | 1     | 1     | 1,1  |
| 2   | 2     | 2     | 2,2  |
| 4   | 1     | 4     | 1,4  |
| 7   | 1     | 2     | 1,2  |
| 8   | 2     | 3     | 2,3  |
| 11  | 2     | 1     | 2,1  |
| 13  | 1     | 3     | 1,3  |
| 14  | 2     | 4     | 2,4  |
mod 3能取到的值是{1,2},而mod 5能取到的值是{1,2,3,4},根据表格显然数字和余数是一一对应的

再定义$F_n(m)$为在mod n意义下F(m)的值

根据刚刚的结论,要求$F_{15}(2)$,那么就要先求$F_3(2)$和$F_5(2)$,这两个分别是`2=#{1,2}`和`2=#{1,4}`,所以有四个,根据上面的表,倒推出是{1,4,11,14}
## 继续分析F(m)

根据上面的分析,得到的结论是
$$F(m)=\prod F_{p_j^{e_j}}(m)$$
额,也就是依旧先证明积性函数,然后下面显然要计算只含一个质数的函数值了(这套逻辑学习卷积的时候应该是非常熟悉了吧)

首先,当$n=p_j^{e_j}$时,可以得到这个群的阶大小是$\varphi(n)=p^{e-1}(p-1)$
### 奇素数

当p为奇素数时,整个群是一个循环群,这意味着可以按循环群的性质来处理

假设这个循环群的生成元是g,那么这个群里的每个数字显然都能被$g^k$次表达

因此满足
$$(g^k)^m=g^{km}\equiv 1\ (\ mod\ n\ )$$
设阶$\varphi(n)=N$,因为g的阶是N,那么
$$N|km$$
再设`d=gcd(m,N)`,给上述式子两边同时除以d得到:
$$\frac{N}{d}|k$$
在1-N中,满足要求的k显然有d个,所以单个方程解的数量是`gcd(m,N)`
### p=2

这个需要特殊讨论,因为当p=2,e>2时,这个群将不是一个循环群,必须额外讨论(怎么这么坏)

比如n=8,这个时候群为{1,3,5,7},{1,3}自己循环上了,整体却转不起来

从小的开始计算:

当e<=2时 : 可以套用循环群的公式

当e>2时:

此时群中的每个数字都能被唯一的表示为
$$x=(-1)^a5^b\equiv1 \ (\ mod \ n\ )$$
所以要满足方程也就是要满足
$$x^m=(-1)^{am}5^{bm}\equiv1 \ (\ mod \ n\ )$$
那么和前面中国剩余定理分解的过程差不多,只要求出a的数量和b的数量就行了
也就是求出满足
$$(-1)^{am}\equiv 1\ (\ mod\ n\ )$$
的a的数量,以及
$$5^{bm}\equiv 1\ (\ mod\ n\ )$$
的b的数量
而这两者在模$2^e$下又分别是循环群,其中,-1的阶是2,5的阶是$2^{e-2}$,可以套循环群公式
### 总公式

综上
$$F(m)=\begin{cases}
gcd(m,p^{e-1}(p-1))\ \ \ \ \ p\text{是奇素数}\\
1\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ p=2,e=1\\
2\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ p=2,e>2\\
gcd(m,2)gcd(m,2^{e-2})\ p=2,e=2\\
\end{cases}$$
# 优化计算实现

注意到原本使用的是$\varphi(n)$,这个范围太大了,可以缩小一点,这里可以引入卡米歇尔函数加速计算

卡米歇尔函数其实就是所有阶的最小公倍数,记作$\lambda(n)$,这个也是有计算公式的
$$\lambda(m)=\begin{cases}
p^{e-1}(p-1)\ \ \ \ \ p\text{是奇素数}\\
1\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ p=2,e=1\\
2\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ p=2,e=2\\
2^{e-2}\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ p=2,e>2\\
\end{cases}$$

所以到此整题结束,参考代码:(使用了一些我常用的宏定义)

```C++
ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}
const ll N=1e5+10;
vector<ll> prime;
ll spf[N];
void init(){
  for(int i=2;i<=N-10;i++){
    if(spf[i]==0){
      prime.push_back(i);
      spf[i]=i;
    }
    for(int p:prime){
      if(i*p>N) break;
      spf[i*p]=p;
      if(i%p==0) break;
    }
  }
}
ll qpow(ll base,ll exp){
  ll ans=1;
  while(exp){
    if(exp&1) ans=ans*base;
    base=base*base;
    exp>>=1;
  }
  return ans;
}
vector<pair<ll,ll>> fact(ll n){
  vector<pair<ll,ll>> ans;
  for(int p:prime){
    ll cnt=0;
    while(n%p==0) n/=p,cnt++;
    if(cnt) ans.pb({p,cnt});
    if(n==1) break;
  }
  if(n!=1) ans.pb({n,1});
  return ans;
}
void solve(){
  ll n,ans=0,lam=1; cin>>n;
  vector<pair<ll,ll>> fn=fact(n),flam;
  for(auto i:fn){
    if(i.fs!=2) lam*=qpow(i.fs,i.sd-1)*(i.fs-1);
    else if(i.sd==2) lam*=2;
    else if(i.sd>2) lam*=qpow(2,i.sd-2);
  }
  flam=fact(lam);
  ll len=flam.size();
  vector<ll> cnt(len+1,0);
  while(cnt[len]!=1){
    ll m=1,fm=1,pi=1,rem;
    for(int i=0;i<len;i++)
      m*=qpow(flam[i].fs,cnt[i]);
    for(auto i:fn){
      if(i.fs!=2) fm*=gcd(m,qpow(i.fs,i.sd-1)*(i.fs-1));
      else if(i.sd==2) fm*=gcd(m,2);
      else if(i.sd>2) fm*=gcd(m,2)*gcd(m,qpow(2,i.sd-2));
    }
    rem=lam/m;
    vector<pair<ll,ll>> tmp=fact(rem);
    for(auto i:tmp) pi*=1-i.fs;
    ans+=m*fm*pi;
    cnt[0]++;
    for(int i=0;i<len;i++)
      if(cnt[i]>flam[i].sd)
        cnt[i]=0,cnt[i+1]++;
  }
  cout<<ans<<endl;
}
signed main(){
  fast
  init();
  ll T; cin>>T;
  while(T--) solve();
  return 0;
}
```

要是有更好的解释方式或者有错误之处,欢迎指出