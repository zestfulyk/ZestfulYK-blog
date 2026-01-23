---
title: C++几何计算(保姆级教程)
date: 2025-12-23 15:39:27
tags: 算法
mathjax: true
---
# 版权说明

此文章的所有代码均由qinye_leaf 勤叶大佬收集整理，感谢喵Orz Orz Orz

# 初始化

由于双精度和单精度存在精度问题，所以补能直接判断是否为0或者相等，那么怎么办呢？
我们可以取绝对值，然后和一个非常小的数字比较

代码示例：
```C++
// 浮点数精度阈值(根据题目要求调整，通常1e-8)
const double EPS = 1e-8;
```

# 符号函数

判断正负号的函数，但是是浮点数数版本的

```C++
// 符号函数：判断浮点数正负
int sgn(double x) {
    if (fabs(x) < EPS) return 0;
    return x > 0 ? 1 : -1;
}
```

# 构造函数介绍

解释一下**构造函数**的用法，这里可以直接赋初始值，方便初始化

```C++
Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
//那么我们可以这么来定义一个变量
Point p1(2.0,3.0);
Point p2;
```

如果不传参数，那么就是直接得到初始值0,0,要是有值的化就是直接赋值，这样就避免了先定义再赋值的痛点。
# 点

## 点的定义

点的定义我们使用结构体struct和重载操作符定义点的操作，这样我们就能直接计算两个点构成的向量
这里面最重要的是加减，但是既然定义了那么就完整定义

```C++
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
```

## 两点间的距离

根据上面的定义，相减以后得到向量，然后再套用下面的向量长度计算公式

```C++
// 两点间距离
double dist(const Point& a, const Point& b) {
    return len(a - b);
}
```

# 线段

只要这两个变量就能确定一个线段，所以存点

```C++
// 线段结构体
struct Segment {
    Point a, b; // 线段端点
    Segment() {}
    Segment(Point a_, Point b_) : a(a_), b(b_) {}
};
```

## 线段的旋转

这里的化，先转化为极坐标，得到：
设$\vec a$和x轴的夹角为$\alpha$,所以$a=(x,y)=(r\cos\alpha,r\sin\alpha)$
旋转后得到$a'=(r\cos(\alpha+\theta),r\sin(\alpha+\theta))$
展开得到
$a'=(r\cos(\alpha)\cos(\theta) - r\sin(\alpha)\sin(\theta), r\sin(\alpha)\cos(\theta) + r\cos(\alpha)\sin(\theta)$
带回坐标就得到公式了。
如果是原点，直接计算，如果不是，那么先平移一下再计算

```C++
// 向量a绕原点旋转rad弧度(逆时针为正，顺时针为负)
Point rotate(const Point& a, double rad) {
    double c = cos(rad), s = sin(rad);
    return Point(a.x * c - a.y * s, a.x * s + a.y * c);
}
// 向量a绕点p旋转rad弧度
Point rotate_point(const Point& a, const Point& p, double rad) {
    return rotate(a - p, rad) + p;
}
```

用处的化，要是一个几何图形，你一个一个转过去，最后再连起来，就是旋转后的图形了
# 圆

需要圆心和半径

```C++
// 圆结构体
struct Circle {
    Point o; // 圆心
    double r; // 半径
    Circle() {}
    Circle(Point o_, double r_) : o(o_), r(r_) {}
};
```
# 向量的计算

## 向量点乘

这里直接用Point来代替向量了，但是实际上差不多,不过是先处理一下而已。

```C++
// 向量点乘(a·b)
double dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}
```

用途：
计算向量夹角、投影长度、判断向量垂直；
公式：$\vec a · \vec b = |\vec a||\vec b|\cos(\theta)$   ($\theta$为两向量的夹角)

## 向量的单位化

计算$\frac{\vec a}{|\vec a|}$

```C++
// 向量单位化(避免零向量)
Point normalize(const Point& a) {
    double l = len(a);
    if (sgn(l) == 0) return Point(0, 0);
    return a / l;
}
```
## 求向量的模长和单纯平方

计算$|\vec a|$和$|\vec a|^2$

```C++
//点乘延伸:
// 向量的模长(长度)平方,(避免开根号，提升效率)
double len2(const Point& a) {
    return dot(a, a);
}
// 向量的模长(长度)
double len(const Point& a) {
    return sqrt(len2(a));
}
```

## 求$\vec a$在$\vec b$上的投影向量

公式 :
$$\frac{\vec a ·\vec b}{|\vec b|}$$

```C++
double proj_len(const Point& a, const Point& b) {
    return b * ( dot(a, b) / len2(b) );
}
```

## 求$\vec a$在$\vec b$上的投影向量的模长

```C++
// 向量投影长度：向量a在向量b上的投影长度 ( projection length（投影长度）)
double proj_len(const Point& a, const Point& b) {
    return dot(a, b) / len(b);
}
```

## 判断向量是否垂直

这个很好理解，因为$$\vec a·\vec b=0\iff\vec a\perp\vec b$$
```C++
// 判断两向量垂直
bool is_vertical(const Point& a, const Point& b) {
    return sgn(dot(a, b)) == 0;
}
```

# 向量的叉乘

## 叉乘的定义

首先叉乘的定义是什么说实话我也不知道该怎么解释，反正知道它的性质就能计算了
## 计算方式

$$\vec a\times \vec b=x_1*y_2-y_1*x_2$$

```C++
// 向量叉乘(a×b)
double cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}
```

## 长度(模长)
$$\vec a\times \vec b=|\vec a||\vec b|\sin<\vec a,\vec b>$$
## 叉乘的性质

### 方向的表示

根据我的理解叉乘的符号，表示了$\vec a$到$\vec b$的方向变化方式
从a到b：即$\vec a\times \vec b$
如果是正的，那么是逆时针转的
如果是负的，那么是顺时针转的

此处的额外要求是把向量的起点放到同一个位置，不过实际上你会发现把向量头尾衔接起来貌似更好理解。下面我都会详细讲解的，保证记住
示例：顺时针(对应负)从a到b

 ```txt
        b
        ^
        |
        |
a<-------
 ```
逆时针(对应正)从a到b

 ```txt
b
^
|
|
------->a
 ```

但是直接记结论貌似不简单？那么试试我的理解方式

首先先把向量整成头尾相接的形式，如下：

```txt
b
^
 \
  \
   \
    ^a
    |
    |
    |
```

然后拿出你的右手，手心向着左边，手掌的走向和a一致，手指的走向和b一致，那么再看看你的大拇指是什么方向呢？朝上对不对？所以是正的。
那么我们就记住了正对应逆时针。易如反掌
实际操作时，只要摆对手心和手指的方向就彳亍了，你总不会把手指掰到反面吧 (
找到舒服的那一侧就是正确的摆法，总之重要的还是记住方向和正负号的关系。

下面给出代码：

```C++
// 判断向量a是否在向量b的顺时针方向
bool is_clockwise(const Point& a, const Point& b) {
    return sgn(cross(a, b)) < 0;
}
// 判断向量a是否在向量b的逆时针方向
bool is_counter_clockwise(const Point& a, const Point& b) {
    return sgn(cross(a, b)) > 0;
}
//直接使用的话是这样的:
// 判断向量b相对于向量a的方向
double val = cross(a, b);
if (val > 0) {
    // b在a的逆时针方向
} else if (val < 0) {
    // b在a的顺时针方向
} else {
    // a和b共线(同向或反向)
}
```

所以下面我们就可以延申到对点和直线关系的判断上了

首先我们判断点和直线关系的本质还是看顺逆时针的变化，构造一条直线，连接向量的尾和这个点，看顺逆时针的变化，所以代码就很理解了

值得注意的是，这里是相对向量的方向而言的，主要作用是为后面点和多边形关系做铺垫

```C++
// 判断点c在直线ab的左侧/右侧/线上
// 返回值：>0 左侧，<0 右侧，=0 线上
int point_line_side(const Point& a, const Point& b, const Point& c) {
    return sgn(cross(b - a, c - a));//注意顺序
}
```

### 和面积的关系

因为叉乘的模长定义为了
$$\vec a\times \vec b=|\vec a||\vec b|\sin<\vec a,\vec b>$$
也就是
$$2*\frac{1}{2}|\vec a||\vec b|\sin<\vec a,\vec b>$$
那么就是这三个顶点构成的三角形面积的两倍，或者说，是向量构成的平行四边形的面积

于是我们的三角形的计算公式就有了，下面给出对应的代码

```C++
// 三点构成的三角形面积(绝对值/2)
double triangle_area(const Point& a, const Point& b, const Point& c) {
    return fabs(cross(b - a, c - a)) / 2.0;
}
```

四边形的计算方法如下：因为我们只要两个向量就彳亍了，这里选择的是$\vec {AB}$和$\vec {AD}$，

```C++
// 四点构成的四边形面积（平行四边形）
double parallelogram_area(const Point& a, const Point& b, const Point& d) {
    return fabs(cross(b - a, d - a));
}
```

### 叉乘的运算规律

加法的左分配律
$$a\times(b+c)=a\times b+a\times c$$
加法的右分配律
$$(a+b)\times c=a\times c+b\times c$$
标量乘法
$$(\lambda a)\times b=\lambda(a\times b)=a\times(\lambda b)$$

## 计算点到直线的距离

因为能表示面积，所以能拿来计算距离，具体的推导如下：
$$\vec a\times \vec b=|\vec a||\vec b|\sin<\vec a,\vec b>=h_1*|\vec a|=h_2*|\vec b|$$
所以计算点到直线的距离也可以这么来拆分：
首先画出三角形，计算这个三角形的面积，然后乘2再除以AB的长度，化简一下就是：
$$d=\frac{\vec{AP}\times\vec{AB}}{|\vec{AB}|}$$
```C++
// 点p到直线ab的距离
double point_line_dist(const Point& a, const Point& b, const Point& p) {
    return fabs(cross(b - a, p - a)) / len(b - a);
}
```

那么有人会问了，要是是线段怎么办？
其实差不多

```C++
// 点p到线段ab的距离

double point_segment_dist(const Point& a, const Point& b, const Point& p) {
    if (a == b) return dist(a, p); // 线段退化为点
    // 投影参数t：判断垂足是否在线段上
    double t = proj_len(p - a, b - a);
    if (sgn(t) <= 0) return dist(p, a); // 垂足在a外侧
    if (sgn(t - len(b - a)) >= 0) return dist(p, b); // 垂足在b外侧
    return point_line_dist(a, b, p); // 垂足在线段内，返回点到直线距离
}
```

# 计算点在线段上的垂足

首先先计算一下投影向量，然后加上起点a就彳亍啦

```C++
// 计算点p在直线ab上的垂足
Point foot_point(const Point& a, const Point& b, const Point& p) {
    Point ab = b - a;
    double t = dot(p - a, ab) / len2(ab); // 投影参数t(归一化)
    return a + ab * t;
}
```

# 判断点是否在线段上

这里有两个要求，
首先p得在这条线上，可以通过计算$\vec {AP}$和$\vec {BP}$的叉乘得到，叉乘必须为0；
其次，需要两个向量方向相反，那么点乘为负。

```C++
// 判断点p是否在线段ab上（含端点）
bool point_on_segment(const Point& a, const Point& b, const Point& p) {
    // 1. p在直线ab上；2. p的坐标在a和b之间
    return sgn(cross(b - a, p - a)) == 0 && sgn(dot(p - a, p - b)) <= 0;
}
```

# 判断两直线是否相交

这里我们引入一下包围盒的概念，包围盒的意思是能吧图形包围进去的最小的矩阵，且这个矩阵的边界得和坐标轴平行。

例如：
```txt
-----B
|   /|
|  / |
| /  |
|/   |
A-----
```

上面这个就是AB的包围盒

那么有什么用呢？要是包围盒都不相交，那么一定不相交

所以代码如下：

```C++
// 快速排斥：判断两线段的包围盒是否相交
bool rect_intersect(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    double min_x1 = min(a1.x, a2.x), max_x1 = max(a1.x, a2.x);
    double min_y1 = min(a1.y, a2.y), max_y1 = max(a1.y, a2.y);
    double min_x2 = min(b1.x, b2.x), max_x2 = max(b1.x, b2.x);
    double min_y2 = min(b1.y, b2.y), max_y2 = max(b1.y, b2.y);
    return max_x1 >= min_x2 - EPS && max_x2 >= min_x1 - EPS
        && max_y1 >= min_y2 - EPS && max_y2 >= min_y1 - EPS;
}
```

要是严格判定的话，需要用叉乘，实际上，保证A，B在CD异侧就彳亍了
要是线段AB相交于直线CD的话，那么AC，CD的叉积符号必然和BC，CD的符号相反

这样得到的图实际上可能是这样的：

```txt
      C
     ^|^
    / | \
   /  v  \
  /   D   \
 /         \
A-----------B
```

那么我们就发现了，AC到CD和BC到CD的方向一定是不一样的，但是不适用与线段的情况

```C++
// 跨立实验：判断线段ab是否跨立直线cd
bool cross_stand(const Point& a, const Point& b, const Point& c, const Point& d) {
    return sgn(cross(d - c, a - c)) * sgn(cross(d - c, b - c)) <= 0;
}
```

但是要是都是线段的话，还要保证C，D在AB异侧，所以代码：
也就是保证CD和AB也有类似的关系，那么化工图发现这样的一定相交

```C++
// 判断两线段是否相交（含端点）

bool segment_intersect(const Segment& s1, const Segment& s2) {
    Point a = s1.a, b = s1.b, c = s2.a, d = s2.b;
    // 快速排斥
    if (!rect_intersect(a, b, c, d)) return false;
    // 跨立实验(双向)
    return cross_stand(a, b, c, d) && cross_stand(c, d, a, b);
}
```

# 求直线或者线段的交点

首先先保证相交再来计算

建议在使用函数之前先调用一下上面的相交函数

下面是交点函数的证明：

```txt
             A
            /|
           / |h1
C---------E---------------D
    h2|  /
      | /
      |/
      B
```

我们先计算A和B分别到CD的距离，记作$h_1\text{和} h_2$
那么先相似一下，然后再比例得到E的坐标
$$E=\frac{h_1}{h_1+h_2}\times\vec{AB}+A$$
然后，前面刚讲过，高可以由面积得到，那么直接用叉乘代替高就得到计算公式了
设$s_1=\vec{CD}\times\vec{CA},s_2=\vec{CD}\times\vec{CB}$
由于符号相反，所以可以这么写：
$$E=\frac{s_1}{s_1-s_2}\times\vec{AB}+A$$

但是上面考虑的时AB在CD的异侧时的情况
那么我们来考虑一下如果AB在CD的同侧该怎么计算

```txt
	             A
	            /|
	           / |h1
		      /  |
	         B   |
	         |   |
	         |h2 |
C---------E---------------D
    
```

我们用叉乘的话可以发现，叉乘符号相同，那么发现公式还是上面那个，统一一下，所以代码写起来就简单了
然后我们把点带入得到：
$$E=\frac{s_1}{s_1-s_2}\times(B-A)+A=\frac{B*s_1-A*s_2}{s_1-s_2}$$
```C++
// 计算两直线ab和cd的交点（需保证直线不平行）
Point line_intersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    double s1 = cross(d - c, a - c);
    double s2 = cross(d - c, b - c);
    return (a * s2 - b * s1) / (s2 - s1);
}
```

线段的话，可以先算出交点，然后判断交点是不是在线段上

```C++
// 计算两线段的交点（仅当相交时返回有效点）

Point segment_intersect_point(const Segment& s1, const Segment& s2) {
    return line_intersect(s1.a, s1.b, s2.a, s2.b);
}
```
# 圆相关的计算

## 判断点和圆的关系

为了保证精度，所以采用平方

```C++
// 判断点p与圆c的位置：>0 圆外，=0 圆上，<0 圆内
int point_circle_relation(const Point& p, const Circle& c) {
    double d2 = len2(p - c.o); // 距离平方(避免开根号)
    double r2 = c.r * c.r;
    return sgn(d2 - r2);
}
```


## 点到圆的切线长度

这个很好理解，就是勾股定理

```C++
// 点p到圆c的切线长度
double tangent_len(const Point& p, const Circle& c) {
    double d = dist(p, c.o);
    if (sgn(d - c.r) <= 0) return 0.0; // 点在圆内/圆上，无切线
    return sqrt(d * d - c.r * c.r);
}
```

## 求直线与圆的交点

首先先计算垂足，判断交点个数的情况，要是有两个交点的话，计算方式是，垂足+垂足到交点的距离乘上直线AB的单位向量

```C++
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
```

## 线段与圆的交点

首先先算直线和圆的交点，然后再判断这个点是否在线段上

```C++
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
```

# 多边形的计算

## 多边形的面积计算

这个由于我们已经有了一个很好的工具，叉乘，那么我们划分一下面积再计算
比较好理解的方法是，以$P_0$为每个三角形的顶点，依次计算，
所以公式
$$\frac{1}{2}\sum_{i=1}^n(P_i-P_0)\times(P_{i+1}-P_0)$$
但是注意到我们的叉乘具有向量加法的左右分配律，所以展开上面这个式子
$$\begin{split}
&\ \ \ \ \ \frac{1}{2}\sum_{i=1}^nP_i\times P_{i+1}-P_i\times P_0-P_0\times P_{i+1}+P_0\times P_0\\
&=\frac{1}{2}\sum_{i=1}^nP_i\times P_{i+1}
\end{split}$$
首先$P_0\times P_0$一定是等于0的，其次，因为所有点都遍历了，那么$\sum_{i=1}^nP_i\times P_0=-\sum_{i=1}^nP_0\times P_{i+1}$相当于只是后移了一位，但是结果一样，所以直接遍历点的叉乘就可以计算了。

```C++
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
```

## 判断点是否在多边形内部

首先做一条射线，向右射出，计算这条射线和多边形的交点数量，奇数则在内部，偶数则在外部

```C++
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
```

**感谢看完这篇文章！要是有什么想法或者建议，欢迎来交流讨论！**