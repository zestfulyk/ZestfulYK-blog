---
title: opencv入门
date: 2026-09-28 13:32:41
tags:
---
# OpenCV 入门教程(C++ 版)

> 面向零基础入门，所有示例均为**完整可编译**的 C++ 代码。
> 作者的本机环境：Windows + MinGW (GCC) + OpenCV 4.12.0

---

## 目录

- [OpenCV 入门教程(C++ 版)](#opencv-入门教程c-版)
  - [目录](#目录)
  - [0. 环境与编译方式](#0-环境与编译方式)
    - [0.1 编译命令](#01-编译命令)
    - [0.2 头文件](#02-头文件)
    - [0.3 命名空间](#03-命名空间)
  - [1. 第一个程序](#1-第一个程序)
    - [必记的三个窗口函数](#必记的三个窗口函数)
  - [2. Mat：OpenCV 的核心数据结构](#2-matopencv-的核心数据结构)
    - [2.1 创建](#21-创建)
    - [2.2 类型命名规则 `CV_<位深><有无符号><通道数>`](#22-类型命名规则-cv_位深有无符号通道数)
    - [2.3 浅拷贝 vs 深拷贝(重点)](#23-浅拷贝-vs-深拷贝重点)
    - [2.4 访问像素的三种方式](#24-访问像素的三种方式)
      - [2.4.1 Vec3b和uchar](#241-vec3b和uchar)
    - [2.5 多通道分离/合并与混合](#25-多通道分离合并与混合)
    - [2.6 通道转置：reshape](#26-通道转置reshape)
  - [3. 读写与显示图像](#3-读写与显示图像)
  - [4. 颜色空间与通道操作](#4-颜色空间与通道操作)
    - [4.1 补充:HSV是什么](#41-补充hsv是什么)
  - [5. ROI：感兴趣区域](#5-roi感兴趣区域)
  - [6. 绘图与文字](#6-绘图与文字)
  - [7. 图像算术与位运算](#7-图像算术与位运算)
    - [7.1 加减乘除、混合](#71-加减乘除混合)
      - [7.1.1 逐句解释](#711-逐句解释)
    - [7.2 位运算与掩码](#72-位运算与掩码)
  - [8. 几何变换](#8-几何变换)
  - [9. 图像平滑(滤波去噪)](#9-图像平滑滤波去噪)
  - [10. 阈值与二值化](#10-阈值与二值化)
  - [11. 形态学操作](#11-形态学操作)
  - [12. 边缘检测](#12-边缘检测)
  - [13. 轮廓检测与应用](#13-轮廓检测与应用)
  - [14. 直方图与均衡化](#14-直方图与均衡化)
  - [15. 视频与摄像头](#15-视频与摄像头)
    - [15.1 读摄像头](#151-读摄像头)
    - [15.2 写视频](#152-写视频)
    - [15.3 定时器与帧率](#153-定时器与帧率)
  - [16. 性能测量](#16-性能测量)
  - [17. 常见坑与速查表](#17-常见坑与速查表)
    - [17.1 新手最容易踩的坑](#171-新手最容易踩的坑)
    - [17.2 速查表](#172-速查表)
    - [17.3 学习路线建议](#173-学习路线建议)
    - [17.4 参考](#174-参考)

---

## 0. 环境与编译方式

这个网上有视频,请自行学习

### 0.1 编译命令

在任务中选择task,然后选择opencv的release运行程序

### 0.2 头文件

最省事(加载全部模块，编译稍慢)：

```cpp
#include <opencv2/opencv.hpp>
```

只加载需要的模块(编译更快)：

```cpp
#include <opencv2/core.hpp>     // Mat、基本类型
#include <opencv2/imgproc.hpp>  // 图像处理(滤波、边缘、轮廓…)
#include <opencv2/highgui.hpp>  // 显示窗口、读写图片
#include <opencv2/videoio.hpp>  // 视频读写
```

### 0.3 命名空间

几乎所有类/函数都在 `cv` 命名空间里，演示代码里默认：

```cpp
using namespace cv;
using namespace std;
```

> 工程中更推荐显式写 `cv::Mat`，避免命名冲突，但学习阶段用 `using namespace cv;` 更方便。

---

## 1. 第一个程序

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main() {
    cout << "OpenCV version: " << CV_VERSION << endl;   // 宏，直接可用

    // 1. 创建一张 400x600 的深灰色图(CV_8UC3 = 3 通道 8 位无符号)
    Mat img(400, 600, CV_8UC3, Scalar(40, 40, 40));     // 注意是 BGR 顺序

    // 2. 在上面写字
    putText(img, "Hello OpenCV " CV_VERSION, Point(60, 200),
            FONT_HERSHEY_SIMPLEX, 1.2, Scalar(0, 255, 0), 2);

    // 3. 显示
    imshow("window", img);
    int key = waitKey(0);        // 0 = 无限等待按键；返回按下的键值
    cout << "你按下了键: " << key << endl;

    destroyAllWindows();         // 关闭所有窗口
    return 0;
}
```

### 必记的三个窗口函数

| 函数 | 作用 |
| --- | --- |
| `imshow("名字", mat)` | 把 Mat 显示在名为 "名字" 的窗口里 |
| `waitKey(ms)` | 等待键盘：`0` 表示一直等，`>0` 表示等 ms 毫秒，返回按键 ASCII 码 |
| `destroyAllWindows()` | 关闭所有 OpenCV 窗口 |

> **没有 `waitKey`，`imshow` 的窗口会一闪而过甚至根本不刷新**，这是新手第一大坑。
> 所以这两个必须要写

---

## 2. Mat：OpenCV 的核心数据结构

`Mat` = Matrix,是图像也是矩阵。它内部是**引用计数 + 数据指针**，拷贝时默认是"浅拷贝"(共用数据).

### 2.1 创建

```cpp
Mat a;                                            // 空矩阵
Mat b(300, 500, CV_8UC3);                         // 行数, 列数, 类型(内容随机)
Mat c(300, 500, CV_8UC3, Scalar(255, 0, 0));      // 纯蓝色 (B=255,G=0,R=0)
Mat d = Mat::zeros(300, 500, CV_8UC1);            // 全 0(黑)
Mat e = Mat::ones(300, 500, CV_8UC1) * 255;       // 全 255(白)
Mat f = Mat::eye(3, 3, CV_64F);                   // 3x3 单位矩阵，双精度
```

### 2.2 类型命名规则 `CV_<位深><有无符号><通道数>`

一共需要三个参数:
- 位深 存储的数字的bit长度
- U/F 有无符号unsigned还是float
- 通道数 比如C1就是灰度图,只有灰色;BGR就是常规图;BGRA还多了个透明度

这里,用于显示的是前三种,后面的只是拿来计算使用的

| 写法 | 含义 | 常见用途 |
| --- | --- | --- |
| `CV_8UC1` | 8 位无符号单通道 | 灰度图 / 掩码 |
| `CV_8UC3` | 8 位无符号三通道 | 彩色图(BGR) |
| `CV_8UC4` | 8 位无符号四通道 | 带 Alpha 的图(BGRA) |
| `CV_32FC1` | 32 位 float 单通道 | 滤波中间结果、深度图 |
| `CV_64F` | 64 位 double 单通道 | 数学计算矩阵 |

常用属性:

```cpp
Mat img(400, 600, CV_8UC3);
img.rows;          // 400  高(行数)
img.cols;          // 600  宽(列数)
img.total();       // 240000 元素个数
img.channels();    // 3
img.depth();       // CV_8U
img.type();        // CV_8UC3
img.elemSize();    // 3  每个像素字节数
img.step;          // 600*3 = 1800  每行字节数(含内存对齐时可能更大！)
img.empty();       // 是否为空
img.size();        // Size(600, 400)，注意是 (宽, 高)
```

> **行列顺序**：`Mat(rows, cols, type)`。访问像素用 `at<T>(y, x)` 或 `at<T>(Point(x, y))`。
> 搞混 x/y 是第二个大坑。

### 2.3 浅拷贝 vs 深拷贝(重点)

```cpp
Mat a = Mat::zeros(100, 100, CV_8UC1);
Mat b = a;              // 浅拷贝：b 和 a 指向同一块数据
Mat c = a.clone();      // 深拷贝：c 是独立副本
Mat d; a.copyTo(d);     // 深拷贝：同上

b.setTo(255);           // 改 b
// 结果：a 也变成 255，c、d 仍是 0
```

**写原地算法前务必 `clone()`**，否则会破坏原图。
一定要先复制了再操作哼哼哼啊啊啊

### 2.4 访问像素的三种方式

```cpp
Mat img(100, 100, CV_8UC3, Scalar(10, 20, 30));

// 方式一：at<>(最直观，较慢)
Vec3b px = img.at<Vec3b>(y, x);      // Vec3b = 3 个 uchar
uchar B = px[0], G = px[1], R = px[2];
img.at<Vec3b>(y, x) = Vec3b(255, 0, 0);   // 写成蓝色；也可写 img.at<Vec3b>(Point(x,y))

// 方式二：ptr<> 按行拿指针(推荐，很快)
for (int y = 0; y < img.rows; ++y) {
    uchar* row = img.ptr<uchar>(y);           // 指向该行第一个像素
    for (int x = 0; x < img.cols; ++x) {
        row[x * 3 + 0] = 0;                   // B
        row[x * 3 + 1] = 0;                   // G
        row[x * 3 + 2] = 0;                   // R
    }
    // 或者写成:
    Vec3b*row1=img.ptr<Vec2b>(y);
    for(int x=0;x<img.cols;x++){
        row1[x][0]=0;                         // B
        row1[x][1]=0;                         // G
        row1[x][2]=0;                         // R
    }
}

// 方式三：迭代器(泛型安全，`.begin<Vec3b>()` 需指定类型)
MatIterator_<Vec3b> it = img.begin<Vec3b>(), end = img.end<Vec3b>();
for (; it != end; ++it) (*it)[1] = 0;         // 把所有 G 通道清零
```

灰度图用 `img.at<uchar>(y, x)`，float 图用 `img.at<float>(y, x)`。

#### 2.4.1 Vec3b和uchar

为什么上面的程序有的使用的是uchar,而有的使用的是Vec3b呢?

这里我们就需要知道在电脑中,程序是如何存储这个矩阵的了

存储方式be like:

```text
B  G  R | B  G  R | B  G  R
 像素1     像素2      像素3
```

每一个像素是由三个uchar(unsined char)组成的,而单个字符使用了三个byte,所以称之为Vec3b(Vector 3 byte)
所以这实际上就是一个三维数组,每个小数组也算一维,根据需要确定所需的类型

### 2.5 多通道分离/合并与混合

```cpp
Mat img = imread("a.jpg");
Mat bgr[3];
split(img, bgr);                       // 拆成 3 个单通道 Mat
// merge(bgr, 3, img);                 // 再合并,其实这里相当于回去,单纯演示流程

Mat mixed;
Mat zero = Mat::zeros(img.size(), CV_8UC1);
Mat ch[3] = { bgr[0], zero, zero };    // 只保留 B 通道
merge(ch, 3, mixed);                   // 得到一张"纯蓝色调"的图
```

标准流程是,先拆分得到三个单独通道的深浅BRG,然后把另外两个灰度设为了0,也就是相当于图片只剩蓝色了
最后再合并,就得到了一个带蓝色滤镜的图片了

### 2.6 通道转置：reshape

```cpp
// 把 HxW 的 3 通道图摊平成 H x (W*3) 的单通道矩阵(不动数据，只改"解释方式")
Mat flat = img.reshape(1, img.rows);
```

---

## 3. 读写与显示图像

```cpp
// 读
Mat img = imread("D:/test.jpg", IMREAD_COLOR);   // 默认：转成 3 通道 BGR
if (img.empty()) { cerr << "读取失败！检查路径" << endl; return -1; }

Mat g1 = imread("t.jpg", IMREAD_GRAYSCALE);      // 1 通道灰度
Mat g2 = imread("t.jpg", IMREAD_UNCHANGED);      // 原样保留(含 alpha 通道)

// 写(按扩展名决定格式)
imwrite("out.png", img);
imwrite("out.jpg", img, { IMWRITE_JPEG_QUALITY, 90 });   // 质量 0~100
```

`imread` 的 flags 也可以直接写数字：`1` 彩色、`0` 灰度、`-1` 原样。

窗口控制：

```cpp
namedWindow("big", WINDOW_NORMAL);      // 可自由缩放/拖动
resizeWindow("big", img.clos, img.rows);// 重新定义窗口的大小
imshow("big", img);                     // 显示图片
moveWindow("big", 100, 100);            // 让窗口出现显示器的哪里,左上角是0,0
```

**路径注意**：Windows 下 C++ 字符串里的 `\` 是转义字符，请用 `/` 或 `\\`：
`imread("D:/data/a.jpg")` 或 `imread("D:\\data\\a.jpg")`。

---

## 4. 颜色空间与通道操作

```cpp
Mat gray, hsv, rgb;
cvtColor(img, gray, COLOR_BGR2GRAY);    // 灰度
cvtColor(img, hsv,  COLOR_BGR2HSV);     // HSV：H 0~179, S 0~255, V 0~255
cvtColor(img, rgb,  COLOR_BGR2RGB);     // 用于把图交给别的库(如 Qt)

Mat back;
cvtColor(hsv, back, COLOR_HSV2BGR);
```

### 4.1 补充:HSV是什么

HSV 表达彩色图像的方式由三个部分组成:

- Hue(色调、色相)
- Saturation(饱和度、色彩纯净度)
- Value(明度)

HSV 做颜色分割比 BGR 稳得多(亮度变化影响小)。例：提取"黄色"区域:

```cpp
Mat hsv, mask;
cvtColor(img, hsv, COLOR_BGR2HSV);
inRange(hsv, Scalar(20, 100, 100), Scalar(35, 255, 255), mask);  // mask: 0/255
```

> 注意 OpenCV 的 H 通道范围是 **0~179**(不是 0~360)。

---

## 5. ROI：感兴趣区域

ROI 是"视图"，**不复制数据**，修改 ROI 会改到原图。

```cpp
// Rect(左上角x, 左上角y, 宽, 高)
Mat roi = img(Rect(100, 50, 200, 150));   // x=列, y=行

img(Rect(0, 0, 100, 100)) = Scalar(0, 0, 255);   // 直接给左上角涂红

Mat copy = roi.clone();                   // 想独立操作就 clone
copy.convertTo(copy, -1, 1.2, 0);         // 提亮 ROI 副本
copy.copyTo(img(Rect(100, 50, 200, 150))); // 贴回去

// 用 Range 切片：Range(起始, 结束) —— 左闭右开
Mat part = img(Range(0, 100), Range(0, 200));  // 前 100 行、前 200 列
```

程序解释:Rect是Rectangle的缩写,这里`Rect`函数相当于切片,取出一部分
`Scalar`相当选色,然后直接把这个颜色强制赋值给了`img`的左上角的区域,所以相当于涂红了
`convertTo`是一个转换函数,参数分别为:图像,数据类型,乘值,加值,后面的讲解有详细公式
`copyTo`就是字面意思,复制回去罢了

---

## 6. 绘图与文字

所有绘图函数都**原地修改**传入的 Mat。

```cpp
Mat canvas(500, 700, CV_8UC3, Scalar(255, 255, 255));   // 白底

line(canvas, Point(20, 20), Point(300, 200), Scalar(255, 0, 0), 2, LINE_AA);
rectangle(canvas, Rect(50, 50, 200, 120), Scalar(0, 255, 0), 3);          // 边框
rectangle(canvas, Point(300, 60), Point(500, 180), Scalar(0, 0, 255), -1); // 实心(-1)
circle(canvas, Point(400, 320), 70, Scalar(0, 165, 255), 2, LINE_AA);
ellipse(canvas, Point(200, 380), Size(120, 60), 30, 0, 360, Scalar(128, 0, 128), 2);

// 多边形
vector<Point> pts = { Point(560, 300), Point(660, 320), Point(620, 430), Point(540, 400) };
polylines(canvas, vector<vector<Point>>{pts}, true, Scalar(0, 0, 0), 2);

// 文字
putText(canvas, "OpenCV", Point(60, 470), FONT_HERSHEY_SIMPLEX,
        1.5, Scalar(0, 0, 0), 3, LINE_AA);

// 虚线：自带实线，虚线要自己画
for (int x = 0; x < 700; x += 20) line(canvas, Point(x, 240), Point(x + 10, 240), Scalar(0,0,0), 1);
```

| 参数 | 说明 |
| --- | --- |
| `Scalar(B,G,R)` | 颜色，顺序是 BGR(灰度图传一个数即可) |
| `thickness` | 线宽；`-1` 或 `FILLED` 表示填充 |
| `lineType` | `LINE_8`(默认) / `LINE_AA`(抗锯齿，更平滑) |


---

## 7. 图像算术与位运算

### 7.1 加减乘除、混合

```cpp
Mat a = imread("a.jpg"), b = imread("b.jpg");

// OpenCV 的 add 会自动饱和到 255(不会溢出回绕)，比 a+b 安全
Mat dst;
add(a, b, dst);
add(a, Scalar(50, 50, 50), dst);       // 整体提亮
subtract(a, b, dst);
absdiff(a, b, dst);                    // 绝对差(找两帧不同处常用)
multiply(a, b, dst, 1.0 / 255);        // 乘法 + 缩放系数
divide(a, b, dst, 255.0);

// 线性混合：dst = α·a + β·b + γ
double alpha = 0.6, beta = 1 - alpha;
addWeighted(a, alpha, b, beta, 0.0, dst);

// 对比度/亮度：dst = α·src + β  (α 对比度, β 亮度)
Mat bright;
a.convertTo(bright, -1, 1.5, 30);      // -1 表示保持原类型

// 逐元素取反
Mat inv; bitwise_not(a, inv);
```

#### 7.1.1 逐句解释

```cpp
add(a,b,dst);
substract(a,b,dst);
absdiff(a, b, dst);
```

- `add`这句的作用是,每个像素点的每个量单独增加,实现两张图的叠加(若加出了>255的,则变为255)
- `substract`这句的作用是相减(若减出负数,变为0)
- `absdiff`这句的作用是算绝对值,计算两图每个像素的绝对值差

```cpp
multiply(a, b, dst, 1.0 / 255);
divide(a, b, dst, 255.0);
```

- `multiply`这句的作用是计算`a*b*1.0/255`
- `divide`这句的作用是计算`a/b*255`

```cpp
double alpha = 0.6, beta = 1 - alpha;
addWeighted(a, alpha, b, beta, 0.0, dst);
```

- 这一段是线性混合,根据比例将两张图叠加,公式是`dst = a * alpha + b * beta + gamma`

```cpp
Mat bright;
a.convertTo(bright, -1, 1.5, 30);
```

- 这句就是按照公式计算了,用于提升亮度,此处计算要是超了,也会自动截断到255

```cpp
Mat inv; bitwise_not(a, inv);
```

这句话的作用是取反,用255去减所有的像素点,每个点变为补色

> `Mat` 的运算符 `+ - * /` 也重载了(`a + b`)，但它们**不做饱和**，且不能加标量，
> 实际工程里建议用 `add/subtract/addWeighted`,这样更加安全

### 7.2 位运算与掩码

```cpp
Mat mask = Mat::zeros(img.size(), CV_8UC1);
circle(mask, Point(200, 200), 100, Scalar(255), -1);   // 圆形白色区域

Mat masked;
bitwise_and(img, img, masked, mask);   // 只保留 mask 为 255 的地方，其余变黑
bitwise_or(a, b, dst);
bitwise_xor(a, b, dst);

img.setTo(Scalar(0, 0, 0), mask);      // 把 mask 区域涂黑
Mat sub; img.copyTo(sub, mask);        // 带掩码拷贝

// 掩码取反
Mat invMask; bitwise_not(mask, invMask);
```

**掩码规则**：单通道 `CV_8UC1`，非 0 即"有效"。

---

## 8. 几何变换

```cpp
Mat dst;
resize(img, dst, Size(300, 200));                        // 缩放到指定大小
resize(img, dst, Size(), 0.5, 0.5);                      // 缩小一半(fx,fy)
resize(img, dst, Size(), 2.0, 2.0, INTER_CUBIC);         // 放大用三次插值

flip(img, dst, 1);        // 1=水平镜像  0=垂直翻转  -1=水平+垂直
rotate(img, dst, ROTATE_90_CLOCKWISE);   // 90/180/270 度旋转
transpose(img, dst);      // 转置(行列互换)

// 任意角度旋转：绕中心点转 30°，不缩放
Point2f center(img.cols / 2.0f, img.rows / 2.0f);
Mat M = getRotationMatrix2D(center, 30.0, 1.0);      // 正数 = 逆时针
warpAffine(img, dst, M, img.size());

// 仿射变换：由 3 组点确定(平移、旋转、缩放、剪切)
Point2f srcPts[3] = { {0,0}, {float(img.cols-1),0}, {0,float(img.rows-1)} };
Point2f dstPts[3] = { {30,50}, {float(img.cols-1),20}, {10,float(img.rows-1)} };
Mat A = getAffineTransform(srcPts, dstPts);
warpAffine(img, dst, A, img.size());

// 透视变换：4 组点(文档扫描矫正、车牌矫正)
Point2f srcQ[4] = { {56,65}, {351,52}, {28,379}, {389,390} };
Point2f dstQ[4] = { {0,0}, {300,0}, {0,400}, {300,400} };
Mat P = getPerspectiveTransform(srcQ, dstQ);
warpPerspective(img, dst, P, Size(300, 400));
```

**缩放插值怎么选**：

| flag | 适用 |
| --- | --- |
| `INTER_NEAREST` | 最快，有锯齿(用于标签图/掩码) |
| `INTER_LINEAR` | 默认，放大够用 |
| `INTER_AREA` | **缩小首选**，无摩尔纹 |
| `INTER_CUBIC` / `INTER_LANCZOS4` | 放大质量最好，较慢 |

---

## 9. 图像平滑(滤波去噪)

```cpp
Mat dst;
blur(img, dst, Size(5, 5));                          // 均值滤波(会糊)
boxFilter(img, dst, -1, Size(5, 5));                 // 方框滤波
GaussianBlur(img, dst, Size(5, 5), 1.5);             // 高斯滤波(最常用)
medianBlur(img, dst, 5);                             // 中值滤波(去椒盐噪声，核必须是奇数)
bilateralFilter(img, dst, 9, 75, 75);                // 双边滤波(保边去噪，慢)

// 自定义卷积核(可以自己做锐化)
Mat k = (Mat_<float>(3, 3) << 0, -1, 0,
                             -1, 5, -1,
                              0, -1, 0);
filter2D(img, dst, -1, k);
```

| 滤波器 | 特点 |
| --- | --- |
| 均值 / 高斯 | 通用平滑，会模糊边缘 |
| 中值 | 对**椒盐噪声**效果极好，保边较好 |
| 双边 | 保边去噪，适合美颜预处理，速度慢 |

---

## 10. 阈值与二值化

```cpp
Mat gray, bin;
cvtColor(img, gray, COLOR_BGR2GRAY);

// 固定阈值
threshold(gray, bin, 127, 255, THRESH_BINARY);        // >127 -> 255，否则 0
threshold(gray, bin, 127, 255, THRESH_BINARY_INV);    // 反相
threshold(gray, bin, 127, 255, THRESH_TRUNC);         // 截断
threshold(gray, bin, 127, 255, THRESH_TOZERO);        // 小的归零

// Otsu 自动阈值(双峰直方图效果好)；用按位或加上 THRESH_OTSU，thresh 随便填
double t = threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
cout << "自动阈值 = " << t << endl;                    // 返回值即算出的阈值

// 自适应阈值：局部窗口决定阈值，适合光照不均(如拍照文档)
adaptiveThreshold(gray, bin, 255, ADAPTIVE_THRESH_MEAN_C,
                  THRESH_BINARY, 11, 2);              // blockSize 必须奇数, C 为偏移
```

---

## 11. 形态学操作

形态学 = 用"结构元"在二值图上做腐蚀/膨胀组合，常用于去噪、连断、分离。

```cpp
Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));   // 也可 MORPH_ELLIPSE / MORPH_CROSS

erode(bin, dst, kernel);      // 腐蚀：白色区域变小，去掉小噪点
dilate(bin, dst, kernel);     // 膨胀：白色区域变大，填补小洞

morphologyEx(bin, dst, MORPH_OPEN, kernel);      // 开运算 = 先腐蚀后膨胀：去小噪点
morphologyEx(bin, dst, MORPH_CLOSE, kernel);     // 闭运算 = 先膨胀后腐蚀：填小洞/连断
morphologyEx(bin, dst, MORPH_GRADIENT, kernel);  // 梯度 = 膨胀-腐蚀：得到轮廓
morphologyEx(bin, dst, MORPH_TOPHAT, kernel);    // 顶帽 = 原图-开运算：提亮细节
morphologyEx(bin, dst, MORPH_BLACKHAT, kernel);  // 黑帽 = 闭运算-原图：提暗细节
```

口诀：**开运算去白噪点，闭运算补黑洞**。

---

## 12. 边缘检测

```cpp
Mat gray, gx, gy, absx, absy, grad, edges, lap;
cvtColor(img, gray, COLOR_BGR2GRAY);
GaussianBlur(gray, gray, Size(5, 5), 1.5);   // 先降噪，边缘更干净

// Sobel：对 x / y 方向求一阶导
Sobel(gray, gx, CV_16S, 1, 0, 3);            // CV_16S 防止负值溢出
Sobel(gray, gy, CV_16S, 0, 1, 3);
convertScaleAbs(gx, absx);                   // 取绝对值并转回 8 位
convertScaleAbs(gy, absy);
addWeighted(absx, 0.5, absy, 0.5, 0, grad);  // 合成梯度幅值

// Laplacian：二阶导，对噪声敏感
Laplacian(gray, lap, CV_16S, 3);
convertScaleAbs(lap, lap);

// Canny：工业界最常用，输出干净的 1 像素宽边缘(二值图)
Canny(gray, edges, 50, 150);                 // 低阈值, 高阈值(推荐 1:2 或 1:3)
Canny(gray, edges, 50, 150, 3, true);        // 最后一个参数 true = 用更精确的 L2 梯度
```

**Canny 阈值调参经验**：小阈值→边缘多但杂；大阈值→边缘少但可能断裂。
可用滑动条实时调：

```cpp
namedWindow("canny");
// 注意：OpenCV 4.12 起给 createTrackbar 传 &变量 会有 deprecated 警告，
// 推荐第三参传 0，再用 getTrackbarPos 读取当前值。
createTrackbar("low",  "canny", 0, 255);
createTrackbar("high", "canny", 0, 255);
setTrackbarPos("low",  "canny", 50);
setTrackbarPos("high", "canny", 150);

while (true) {
    int lo = getTrackbarPos("low",  "canny");
    int hi = getTrackbarPos("high", "canny");
    Mat e; Canny(gray, e, lo, hi);
    imshow("canny", e);
    if (waitKey(30) == 27) break;   // ESC 退出
}
```

---

## 13. 轮廓检测与应用

轮廓处理是"目标检测/测量"的基础，流程一般是：
**灰度 → 二值化 → 形态学 → findContours → 逐个分析**。

```cpp
Mat gray, bin;
cvtColor(img, gray, COLOR_BGR2GRAY);
GaussianBlur(gray, gray, Size(5, 5), 1.5);
threshold(gray, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

vector<vector<Point>> contours;     // 每个轮廓是一串点
vector<Vec4i> hierarchy;            // [next, prev, child, parent]
findContours(bin, contours, hierarchy,
             RETR_EXTERNAL,          // 只取最外层(RETR_TREE 取全部层级)
             CHAIN_APPROX_SIMPLE);   // 压缩共线点

Mat out = img.clone();
drawContours(out, contours, -1, Scalar(0, 0, 255), 2);   // -1 = 画全部

for (size_t i = 0; i < contours.size(); ++i) {
    double area = contourArea(contours[i]);
    if (area < 100) continue;                       // 过滤噪点

    Rect r = boundingRect(contours[i]);             // 正矩形
    rectangle(out, r, Scalar(0, 255, 0), 2);
    putText(out, to_string((int)area), r.tl(), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1);

    double peri = arcLength(contours[i], true);     // 周长, true=闭合
    RotatedRect rr = minAreaRect(contours[i]);      // 最小面积旋转矩形
    Point2f c; float radius;
    minEnclosingCircle(contours[i], c, radius);     // 最小外接圆

    // 多边形逼近：用于判断形状
    vector<Point> approx;
    approxPolyDP(contours[i], approx, 0.02 * peri, true);
    if (approx.size() == 3)      putText(out, "Triangle", r.tl(), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1);
    else if (approx.size() == 4) putText(out, "Quad",     r.tl(), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1);
    else if (approx.size() > 6)  putText(out, "Circle",   r.tl(), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1);

    // 凸包
    vector<Point> hull;
    convexHull(contours[i], hull);
    polylines(out, hull, true, Scalar(255, 0, 255), 2);
}
imshow("contours", out);
waitKey(0);
```

**关键点**：

- `findContours` 会**修改输入的二值图**(OpenCV 4 里其实不会了，但仍建议传 `bin.clone()`)。
- 点集用 `vector<vector<Point>>`，OpenCV 4 不再需要 `vector<Mat>`。
- `RETR_EXTERNAL`：只关心最外层轮廓；`RETR_LIST`：全部列出且无父子关系；`RETR_TREE`：完整树。
- 面积过滤 `area < 阈值` 是去掉小噪声最常用的手段。

---

## 14. 直方图与均衡化

```cpp
Mat gray; cvtColor(img, gray, COLOR_BGR2GRAY);

// 计算灰度直方图
int histSize = 256;
float range[] = {0, 256};
const float* histRange = {range};
Mat hist;
calcHist(&gray, 1,           // 图像数组 + 个数
         nullptr,            // 使用的通道(灰度自动)，多通道需指定 int channels[] = {0}
         Mat(),              // 掩码，空 = 全图
         hist, 1, &histSize, &histRange);

// 把直方图画出来(归一化到画布高度)
int h = 300, w = 512;
int binW = w / histSize;
Mat canvas(h, w, CV_8UC3, Scalar(255, 255, 255));
normalize(hist, hist, 0, h, NORM_MINMAX);
for (int i = 0; i < histSize; ++i) {
    int v = cvRound(hist.at<float>(i));
    rectangle(canvas, Rect(i * binW, h - v, binW, v), Scalar(0, 0, 0), FILLED);
}

// 直方图均衡化：增强对比度，仅对单通道有效
Mat eq;
equalizeHist(gray, eq);

// 彩色图均衡化：转 YCrCb，只对 Y(亮度)通道做
Mat ycrcb, ch[3];
cvtColor(img, ycrcb, COLOR_BGR2YCrCb);
split(ycrcb, ch);
equalizeHist(ch[0], ch[0]);
merge(ch, 3, ycrcb);
cvtColor(ycrcb, eq, COLOR_YCrCb2BGR);

// CLAHE：限制对比度的自适应均衡，效果通常比全局均衡好
Ptr<CLAHE> clahe = createCLAHE(2.0, Size(8, 8));
Mat claheImg; clahe->apply(gray, claheImg);
```

---

## 15. 视频与摄像头

### 15.1 读摄像头

```cpp
VideoCapture cap(0);                 // 0 = 默认摄像头；填文件名/video.mp4 可读视频
if (!cap.isOpened()) { cerr << "摄像头打开失败" << endl; return -1; }

cap.set(CAP_PROP_FRAME_WIDTH, 1280);
cap.set(CAP_PROP_FRAME_HEIGHT, 720);
cap.set(CAP_PROP_FPS, 30);

Mat frame;
while (true) {
    cap >> frame;                    // 等价于 cap.read(frame)
    if (frame.empty()) break;        // 视频播放完毕，或读取失败

    // ...在这里处理 frame...
    imshow("camera", frame);

    int key = waitKey(30);           // 约 30ms ≈ 33fps，同时给窗口刷新时间
    if (key == 27) break;            // ESC 退出
}
cap.release();                       // 释放资源
destroyAllWindows();
```

### 15.2 写视频

```cpp
VideoCapture cap("in.mp4");
int w = (int)cap.get(CAP_PROP_FRAME_WIDTH);
int h = (int)cap.get(CAP_PROP_FRAME_HEIGHT);
double fps = cap.get(CAP_PROP_FPS);
if (fps <= 0) fps = 30;

VideoWriter writer("out.avi",
                   VideoWriter::fourcc('M', 'J', 'P', 'G'),   // 编码器
                   fps, Size(w, h));
if (!writer.isOpened()) { cerr << "VideoWriter 打开失败" << endl; return -1; }

Mat frame;
while (cap.read(frame)) {
    writer.write(frame);
}
writer.release();
cap.release();
```

> 常用 fourcc：`MJPG`(.avi 通用)、`XVID`、`mp4v`(.mp4)。
> 尺寸必须和写入帧一致，否则会写失败或产出损坏文件。

### 15.3 定时器与帧率

```cpp
double t0 = (double)getTickCount();
// ...处理...
double dt = ((double)getTickCount() - t0) / getTickFrequency();
cout << "耗时 " << dt * 1000 << " ms, FPS = " << 1.0 / dt << endl;
```

---

## 16. 性能测量

```cpp
// 方法一：getTickCount(OpenCV 自带，精度高)
double t = (double)getTickCount();
heavyFunction();
t = ((double)getTickCount() - t) / getTickFrequency();
cout << "耗时: " << t * 1000 << " ms" << endl;

// 方法二：C++ 标准库
auto s = chrono::high_resolution_clock::now();
heavyFunction();
auto e = chrono::high_resolution_clock::now();
cout << chrono::duration<double, milli>(e - s).count() << " ms" << endl;
```

**优化思路**(按收益排序)：

1. 能在**灰度图**上做就别用彩色图(数据量 1/3)；
2. 先 `resize` 缩小再处理；
3. 用 ROI 只处理关心的区域；
4. 访问像素用 `ptr<>` 而不是 `at<>`；
5. 避免在循环里 `clone()`；
6. 打开编译优化(`build_opencv.bat` 的 release 模式已带 `-O2`)。

---

## 17. 常见坑与速查表

### 17.1 新手最容易踩的坑

| 坑 | 现象 | 解决 |
| --- | --- | --- |
| 忘了 `waitKey` | 窗口不显示/一闪而过 | `imshow` 后必须 `waitKey(0)` |
| x/y 搞反 | ROI 位置错乱 | `Rect(x, y, w, h)`，`at<>(y, x)` |
| 忘了 `clone` | 原图被改坏 | 原地处理前先 `clone()` / `copyTo` |
| 路径用了 `\` | 读取失败 | 用 `/` 或 `\\` |
| 忘了判 `empty()` | 后面崩溃 | `imread` 后必判 |
| 忘记 `release()` | 摄像头被占用 | `cap.release()` |
| `Size` 和 `Rect` 顺序 | 尺寸错误 | `Size(宽, 高)`，`Rect(x, y, 宽, 高)` |
| 类型不符 | 断言失败/花屏 | 灰度 `CV_8UC1`，彩色 `CV_8UC3`，不要混 |
| 出现 `CV_16S` 需求 | `Sobel` 报错 | 导数结果必须用 `CV_16S`，再 `convertScaleAbs` |
| 找不到 DLL | 双击 exe 报错 | 用 `build_opencv.bat`(会自动复制 DLL) |

### 17.2 速查表

**结构体**

| 类型 | 含义 |
| --- | --- |
| `Point(x, y)` / `Point2f` | 点(整数 / float) |
| `Size(w, h)` | 尺寸 |
| `Rect(x, y, w, h)` | 矩形 |
| `Scalar(B, G, R)` | 颜色 / 四元组 |
| `Vec3b` | 3 个 uchar(一个彩色像素) |
| `Vec4i` | 4 个 int(轮廓层级) |
| `RotatedRect` | 带角度的矩形 |

**高频函数**

```cpp
// 读写显示
imread / imwrite / imshow / waitKey / namedWindow / destroyAllWindows
// 颜色 / 通道
cvtColor / split / merge / inRange
// 算术
add / subtract / multiply / divide / absdiff / addWeighted / convertTo
// 位运算
bitwise_and / bitwise_or / bitwise_not / bitwise_xor / setTo / copyTo(mask)
// 几何变换
resize / flip / rotate / transpose / warpAffine / warpPerspective
// 滤波
blur / GaussianBlur / medianBlur / bilateralFilter / filter2D
// 阈值 / 形态学
threshold / adaptiveThreshold / erode / dilate / morphologyEx / getStructuringElement
// 边缘
Sobel / Laplacian / Canny
// 轮廓
findContours / drawContours / contourArea / arcLength / boundingRect / minAreaRect / approxPolyDP / convexHull
// 直方图
calcHist / normalize / equalizeHist / createCLAHE
// 视频
VideoCapture / VideoWriter / get / set
```

### 17.3 学习路线建议

1. **基础**：读写显示 → Mat 与像素访问 → ROI → 绘图(第 1~6 节)
2. **图像处理**：颜色空间 → 滤波 → 阈值 → 形态学 → 边缘(第 4、9~12 节)
3. **应用**：轮廓分析(做形状计数、尺寸测量)→ 模板匹配 → 特征点(SIFT/ORB)
4. **进阶**：`dnn` 模块跑深度学习模型(YOLO 目标检测等)

### 17.4 参考

- 官方文档：<https://docs.opencv.org/4.x/>
- 官方教程(C++)：<https://docs.opencv.org/4.x/d9/df8/tutorial_root.html>