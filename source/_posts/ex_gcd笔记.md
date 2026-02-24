---
title: 拓展欧几里得算法
date: 2025-2-24 23:56:00
tags: 算法
mathjax: true
---
拓展欧几里得算法用于在计算`gcd`的同时计算形如
$$ax+by=gcd(a,b)$$
方程的答案

怎么计算呢?

首先考虑一个类似的方程:
$$bx_2+(a\ mod\ b)y_2=gcd(b,a\ mod\ b)$$
要是能得到这个方程的解,上面那个也行
因为
$$a-\lfloor \frac{a}{b}\rfloor*b=a\ mod\ b$$
所以
$$bx_2+(a-\lfloor \frac{a}{b}\rfloor*b)y_2=b*(x_2-\lfloor \frac{a}{b}\rfloor y_2)+ay_2$$
因为
$$gcd(a,b)==gcd(b,a\ mod\ b)$$
两个系数相同的方程有相同的解,那么解对应相等
$$\begin{cases}x_1=y_2
\\ y_1=x_2-\lfloor \frac{a}{b}\rfloor y_2
\end{cases}$$
接下来只要一直往下递归计算就能得到答案了

边界条件是b=0的时候,在C++内默认`gcd(a,0)=a`,所以最后一步的方程为
$$ax+0*y=a$$
因此一般返回值是1,0

最后就能得到一组特解和`gcd(a,b)`了

代码:

```C++
i128 exgcd(i128 a,i128 b,i128 &x,i128 &y){
//也可以当正常的gcd函数使用,相当于同时计算了一下方程的解
  if(b==0){//最后递归到b=0时,得到ax=a,所以返回1,0
    x=1;y=0;
    return a;
  }
  i128 d=exgcd(b,a%b,x,y);
  i128 t=x;x=y;y=t-(a/b)*y;
  return d;
}
i128 ceil_div(i128 p,i128 q){
  if(p>=0) return (p+q-1)/q;//-1的目的是,万一刚好是整数倍,ceil不变
  else return p/q;//负数去掉小数相当于向上取整
}
i128 floor_div(i128 p,i128 q){
  if(p>=0) return p/q;//向下取整的逻辑恰好相反
  else return (p+q-1)/q;
}
```

那么怎么得到通解呢?

实际上特解变化一下就行,考虑x增大的情况,为了保持不变,y得减小
所以这个步长实际上就是b和a,反过来就行,因为这样才能保持等式的成立
但是既然我们算出了`gcd(a,b)`,那么再除一下化简

这样就得到了特解

注意:只有等号右边的常数为`gcd(a,b)`的倍数时,方程才有解,因为不然上面的方法就失效了,哪来的解