---
title: OpenCV新手教程
date: 2026-10-08 23:08:00
tags: OpenCV
---
# 查看函数用法

这个必须得学会!!!
因为openCV是个开源项目,所以函数都是公开的,必须自己学会查看,这个看我前面发的文章就行了
# 显示窗口

首先是namedWindow,创建一个新的窗口,并命名
然后imshow,展示图片,后面要你给一个矩阵,写0就行(空矩阵)
最后是waitKey,用于接收鼠标和键盘的指令,同时延时,保持窗口,填入0则一直显示
`destroyAllWindows`关闭所有窗口

标准写法:

```C++
int main(){
  namedWindow("new",WINDOW_NORMAL|WINDOW_KEEPRATIO);
  resizeWindow("new",640,480);
  imshow("new",0);
  char key=waitKey(0);
  if(key=='q') destroyAllWindows();
}
```

waiKey实际返回的是16位的整数值,所以如果是和char比较,一个取低8位,
也就是写成:

```C++
key&(0xFF)
```

F是16进制下的15,所以F的二进制就是1111,两个即为8低位:`11111111`
# Windows下访问图片

```C++
\\ D:\\X\\X\\XXX.jpg
```

# 获取视频

```C++
int main(){
  namedWindow("video",WINDOW_AUTOSIZE);// 创建窗口
  VideoCapture cap(0);// 获取视频设备
  Mat frame;// 定义一个矩阵
  while(cap.read(frame)){// read返回的是bool值,表示是否获取成功
    imshow("video",frame);// 展示图片
    if(waitKey(0)==32) break;// 设定退出条件
  }
  cap.release();// 释放资源
  destroyAllWindows();// 删除窗口
}
```

此处值得注意的是,readframe每次读一次摄像头的数据,所以上面的这个只有输入一个键以后(也就是要等`waitKey`这个事件结束后),才会继续

这个是因为`waitKey`写了0导致的,那么为了阻止这个问题,写入数字就行了,单位是毫秒

比如这样:

```C++
int main(){
  namedWindow("video",WINDOW_AUTOSIZE);
  VideoCapture cap(0);
  Mat frame;
  while(cap.read(frame)){
    imshow("video",frame);
    if(waitKey(10)==32) break;// fix
  }
  cap.release();
  destroyAllWindows();
}
```

这表示,输入只会等你10ms,过了就继续读取了,就不管你了,因此可以连续读取
## 从视频文件中读取

也是使用`VideoCapture`,参数填文件路径

要注意的是`waitKey`的参数设置,需要设置成和文件的数据一致

# 写入视频

```C++
int main(){
  namedWindow("video",WINDOW_NORMAL);
  VideoCapture cap(0);
  int width=static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
  int height=static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
  // 创建多媒体资源
  int fourcc=VideoWriter::fourcc('M','J','P','G');
  VideoWriter vw("out.avi",fourcc,25,Size(width,height),1);
  Mat frame;
  while(cap.read(frame)){
    resizeWindow("video",640,480);
    imshow("video",frame);
    vw.write(frame);// 写数据到多媒体数据
    if(waitKey(33)==32) break;
  }
  vw.release();// 释放资源
  cap.release();// 释放资源
  destroyAllWindows();// 删除窗口
}
```
## 注意点

`Size`要和你摄像头的参数一致,此处可以`debug`长宽来查看

把窗口大小修改放在显示之后,这样才能保证每次窗口大小都是正确的

一定要记得`release`~~你也不想内存泄露对吧~~
## fourcc参数详细解释

### 定义

`FourCC` 全称是 **Four Character Code（四字符代码）**。在视频编码领域，底层系统（如 FFmpeg、DirectShow）就是用这四个字母组成的代号，来识别**到底该用哪种视频压缩算法（编解码器）**。

### 参数

|FourCC 写法 (C++)|编码器名称|典型文件后缀|特点与场景|
|---|---|---|---|
|`'M', 'J', 'P', 'G'`|Motion JPEG|`.avi`|兼容性最强，文件大，适合做实验、逐帧分析|
|`'X', 'V', 'I', 'D'`|Xvid MPEG-4|`.avi`|早期非常流行的压缩格式，文件体积比 MJPG 小很多|
|`'m', 'p', '4', 'v'`|MPEG-4 Video|`.mp4`, `.avi`|比较老的 MP4 编码，容错率高|
|`'a', 'v', 'c', '1'`|H.264 / AVC|`.mp4`|**目前主流**，压缩率极高，画质好（注意：OpenCV 默认编译包有时不支持写入该格式）|
|`'H', '2', '6', '4'`|H.264 的另一种写法|`.mp4`|同上，有时取决于底层 FFmpeg 的版本|
|`'D', 'I', 'V', 'X'`|DivX MPEG-4|`.avi`|早期常见，现在较少用|
|`0`（整数0）|弹窗选择器|无|在某些系统下，传 0 会弹出一个对话框让你手动选编码器（不推荐，容易导致程序卡死）|
# 鼠标控制

```C++
setMouseCallback(winname,callback,userdata);
```

`setMouseCallback`: 窗口名称,回调函数,用户数据

其中,参数callback是自己写的一个自定义函数,作用是调试/完成一些其余事项

callback函数可以这么写:

```C++
void callback(int event,int x,int y,int flags,void* userdata){
cout<<event<<" "<<x<<" "<<y<<" "<<flags<<" "<<(char*)userdata<<endl;
}
```

注意到`userdata`的类型是`void*`

这个类型是无类型指针,下面是详细解释
## `void*`

### 先说区别

`void*` 是**无类型指针（通用数据指针）**，它指向的是**数据（内存地址）**，而不是函数。  
指向函数的指针有专门的写法，比如 `void (*funcPtr)()`。
### 定义

`void*` 是一种特殊的指针类型，它可以用来存放**任何数据类型**的地址（比如 `int*`、`char*`、结构体指针等）。

- **特性**：它不知道自己指向的内存里存的是什么类型的数据。因此，你**不能直接解引用它**（不能写 `*ptr`），也不能对它进行指针运算（不能写 `ptr++`），必须把它**强制转换**成具体的指针类型后才能使用。

`void*` 是**数据指针的万能容器**，而函数指针是**代码逻辑的入口地址**。在你的这段 OpenCV 代码中，`callback` 是函数指针，`(void*)"123"` 是利用 `void*` 传递的附加数据。
### 代码示例

```C++
void callback(int event,int x,int y,int flags,void*userdata){
    int value=*(int*)userdata;
    cout<<"传进来的整数是:"<<value<<endl;
}
int main(){
    int myNum=100;
    setMouseCallback("mouse",callback,(void*)&myNum);
}
```

## 完整示例

```C++
void callback(int event,int x,int y,int flags,void* userdata){
  cout<<event<<" "<<x<<" "<<y<<" "<<flags<<" "<<(char*)userdata<<endl;
}
int main(){
  Mat img=Mat(360,640,CV_8UC3);
  namedWindow("mouse",WINDOW_NORMAL);
  resizeWindow("mouse",640,360);
  setMouseCallback("mouse",callback,(void*)"123");
  while(1){
    imshow("mouse",img);
    if(waitKey(1)=='q') break;
  }
  destroyAllWindows();
}
```

# Trackbar

## 完整代码展示

```C++
void callback(int position,void*userdata){}
int main(){
  namedWindow("trackbar",WINDOW_NORMAL);
  createTrackbar("R","trackbar",0,255,callback);
  createTrackbar("G","trackbar",0,255,callback);
  createTrackbar("B","trackbar",0,255,callback);
  Mat img=Mat(640,360,CV_8UC3);
  while(1){
    int r=getTrackbarPos("R","trackbar");
    int g=getTrackbarPos("G","trackbar");
    int b=getTrackbarPos("B","trackbar");
    img.setTo(Scalar(b,g,r));
    imshow("trackbar",img);
    resizeWindow("trackbar",640,360);
    if(waitKey(1)=='q') break;
  }
  destroyAllWindows();
}
```

## `createTrackbar`

参数为:条的名称,条应用在的窗口,范围下界,范围上界,依旧是回调函数
## `getTrackbarPos`

获取具体值,并返回一个`int`类型的值

执行上面的程序,得到一个可以自己调整条的窗口,根据条变换窗口颜色
## `setTo`

C++中用于直接调整整个矩阵变为这个值的函数
## `Scalar`

三元组,设定颜色,顺序是B,G,R