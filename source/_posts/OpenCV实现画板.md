---
title: OpenCV实现画板
date: 2026-10-11 00:00:58
tags: OpenCV
---
# 键盘控制图像的切换

这个算最简单的一个部分了,只要使用`waitKey`大法获取就行

# callback

这里要注意的是,回调函数只有在鼠标状态变化时才会调用,所以清空这一步得写主函数里面

# 模拟画图

这里的实现方式是,存储旧的图,每次中间模拟的时候,都在旧的图上重新绘制

# event

这个是一个查询某一瞬间状态的变量,比如按下或者抬起

# flags

这个是一个状态压缩写的,查询所有状态的变量,但是不能获取瞬间事件

# 完整代码

```C++
#include<bits/stdc++.h>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
Point startpos;
int curshape=0;
Mat img,backup;
bool drawing=0;
void drawshape(Mat&canvas,int x,int y){
  if(curshape==0) line(canvas,startpos,Point(x,y),Scalar(0,0,255),2);
  if(curshape==1) rectangle(canvas,startpos,Point(x,y),Scalar(0,0,255),2);
  if(curshape==2){
    int r=(int)sqrt((x-startpos.x)*(x-startpos.x)+(y-startpos.y)*(y-startpos.y));
    circle(canvas,startpos,r,Scalar(0,0,255),2);
  }
}
void mouse_callback(int event,int x,int y,int flags,void*userdata){
  if(event==EVENT_LBUTTONDOWN){
    startpos=Point(x,y);
    drawing=1;
    backup.copyTo(img);
  }
  else if(flags&EVENT_FLAG_LBUTTON&&drawing){
    backup.copyTo(img);
    drawshape(img,x,y);
  }
  else if(flags&EVENT_FLAG_LBUTTON&&!drawing){
    backup.copyTo(img);
  }
  else if(event==EVENT_LBUTTONUP&&drawing){
    drawing=false;
    backup.copyTo(img);
    drawshape(img,x,y);
    img.copyTo(backup);
  }
}
int main(){
  namedWindow("drawshape",WINDOW_NORMAL);
  setMouseCallback("drawshape",mouse_callback,(void*)NULL);
  img=Mat::zeros(480,640,CV_8UC3);
  img.copyTo(backup);
  while(1){
    int now=waitKey(1);
    if(now=='q') break;
    if(now=='l') curshape=0;
    if(now=='r') curshape=1;
    if(now=='c') curshape=2;
    if(now==27){
      backup.copyTo(img);
      drawing=0;
    }
    imshow("drawshape",img);
  }
  destroyAllWindows();
}
```