---
title: 3-style简化版Orozco
date: 2026-10-08 17:55:04
tags: 魔方
---
# 说明

网上看到过好几个版本的,总结一下比较好的公式

# 角块

以下均为去`buffer`的公式
## 常规三交换

- `UFR>URB>UBL`: `[x R2: [D2, R U R']]`
- `UFR>URB>ULF`: `[x' R2: [R' U' R, D2]]`

这两个是标准的顶层三交换公式,没有区别
## 左侧上两片

- `UFR>URB>LUB`: `[R2: [R' U R, D]]`
- `UFR>URB>LFU`: `[R2: [D', R U' R']]`

这两个的关键点是使用了`R2`,把上变成下,便于操作
## 底层8片

- `UFR>URB>LDF`: `[R' D R, U]`
- `UFR>URB>LBD`: `[U', R D' R']`
- `UFR>URB>FDR`: `[D' R' D R, U]`
- `UFR>URB>FLD`: `[D R' D' R, U]`
- `UFR>URB>RDB`: `[U', R D R']`
- `UFR>URB>RFD`: `[R' D' R, U]`
- `UFR>URB>BDL`: `[U', D' R D R']`
- `UFR>URB>BRD`: `[U', D R D' R']`

中间这8个是最简单的公式,也就是底层的边上一圈的片转换
## 顶层左侧前后两片

- `UFR>URB>FUL`: `[R2: [R' U2 R, D]]`
- `UFR>URB>BLU`: `[R2: [D', R U2 R']]`

顶层一圈的两个特殊,使用了`U2`来完成转换
## 底层左侧

- `UFR>URB>DFL`: `[F2,R B R']`
- `UFR>URB>DLB`: `[R' F' R,B2]`

这两个使用我自己发现的公式,比原公式的`l`好记忆
记忆的关键点:公式中的三步的作用是交换`Buffer`和`Helper`
通过这个就可以记住方向问题
## 底层右侧

- `UFR>URB>DRF`: `(R' D R U') (R D' R' U) (R D R' U) (R' D' R U')`
- `UFR>URB>DBR`: `(U' R D' R') (U R' D R) (U R' D' R) (U' R D R')`

这两个最阴的公式,必须得记~~(或者偷懒,转到顶层做常规三角换)~~
# 棱块
## 常规部分
### 顶层

- `UF>UR>UB`: `M2 u' M' u2 M' u' M2`
- `UF>UR>UL`: `[M2 U: [M, U2]]`

这就是CFOP的三棱换

### 中间层

- `UF>UR>LF`: `[U', R' E R]`
- `UF>UR>FL`: `[U', R E2 R']`
- `UF>UR>LB`: `[U', R E' R']`
- `UF>UR>RB`: `[U2: [U', L' E L]]`
- `UF>UR>RF`: `[U2: [U', L E' L']]`
- `UF>UR>BL`: `L' U' L' U' L U L U L U'`(建议使用常规方案,非常简单)

这几个是常规解法,因为中间的可以直接一步到位进行交换
### 底层

- `UF>UR>RD`: `[U', R' E' R] or [U', R E R']`

这一个算常规的原因是,这个可以直接交换,算一个非常好记的
## LU

- `UF>UR>LU`: `[S', L F' L']`

这组公式的关键是看S那一步,因为交换的是左侧和前面的
可以通过这个来记忆去往的是`Buffer`还是`Helper`
## LD

- `UF>UR>LD`: `[M D M', U]`

这公式挺妙的,通过中间那一列保持不变的性质完成上下的交换,这一个转换机的原理还是比较明显的
## FR

- `UF>UR>FR`: `[M U M' U', R]`

没懂这个的转换机原理,为什么不直接把`FR`变`LF`,然后做常规公式
## FD

- `UF>UR>FD`: `[M', R U' R' U]`

这个也是,可以变`LD`
但是这一个的转换机还是比较明显的,类似M2OP方法里的操作
把`Buffer`的位置和`BR`交换了
## BU

- `UF>UR>BU`: `[M, R' U' R U]`

这一个的记忆是这样的,这个公式本质是OLL的H和鱼的解法,但是实际因为看不到,所以要想办法判断
注意到即将要去正确位置的那个棱块一定不是正确朝向的,而H和鱼总共就两种状态,这样就记住了
## BD

- `UF>UR>BD`: `U M U M' U M U M'`

2(左下左上)
## BR

- `UF>UR>BR`: `R U R U R U' R' U' R' U'`

公式很好记,就是左边的第二层的一种进槽的方案之一再加个右,有些公式书会采用这个当新手教程
原理没看懂,感觉就是把顶层的全部藏起来,进行一手调整
## 底层

- `UF>UR>DF`: `M U2 M U M' U2 M' U'`
- `UF>UR>DR`: `U R' U' R U R U R U' R' U2`
- `UF>UR>DB`: `[R': [M2, U' R U]]`
- `UF>UR>DL`: `U' L' U' L U L U L U' L`'

唯一一个我看懂的是DB,因为这个就是M2OP原公式,但是理论上,底层可以`setup`到顶层来交换
`DF`这个,有点类似桥式的解法,但又不完全是,在我背会之前,我决定先使用`setup`到顶层的方案
# 编码

![图片](magic_cube.png)

这里的循环和六步法的区别是,只要最后循环到同一个块上就行了,不需要片对上
然后如果是大循环加小循环,遇到要回到起点的,跳过起点,直接下一个

如果想把字母对配上中文词来记忆,可以参考我自己整理的 <a href="/ZestfulYK-blog/%E5%BD%B3%E4%BA%8D%E6%B3%95%E8%AF%8D%E8%A1%A8.html" target="_blank" rel="noopener">彳亍法词表</a>(24 字母、去掉 UV,共 506 个词)
# 特殊情况

含H或者I的三棱换编码,在中间插入一个G来操作,也就是先翻再做,这么说来棱块好像也是这个逻辑

比如遇到HE这个编码,采用HG+GE就行