---
title: 程C笔记
date: 2025-12-7 22:15:00
tags: 数学
mathjax: true
---
## 1. 头文件和命名空间
C++ 中的 string 类定义在头文件 string 中，通常使用 std 命名空间。

```c++
s3=strcat(s1,s2);//加在后面
int x=strcmp(s1,s2)//返回三种情况,见下面
cout<<strlen(s1)<<endl;//输出的是长度，等同于s1.length()
strcpy(s1+x1,s2+x2);//把前面的对应部分添加到前面去，完全覆盖之前的内容
memcpy(a+x1,b+x2,sizeof(int)*8);//也是把后面的放到前面，只不过需要规定放入的内容
sizeof(s1);//考虑后面的'\0'，比strlen大1.
```
$$ x=strcmp(s1,s2)= 
\begin{cases}
 -1  \ \ \ \ \ s1 \leq s2\\
0\ \ \ \ s1=s2\\
1\ \ \ \ s1 \geq s2
\end{cases}
$$
memcpy例子：
```C++
int a[8]={1,2,3,4,5,6,7,8};
int b[10]={10,9,8,7,6,5,4,3,2,1};
memcpy(b,a,sizeof(int)*8);
for(int i=0;i<10;i++)
    cout<<b[i];
```
输出：
```C++
1234567821
```

## 2.函数
```C++
int maxGap(int* p, int n)//传入p[0]的地址，能改变在主函数里的值
static int t;//静态局部变量，下次还是调用上次的值
//例如：
int cnm(int p,int q){
	static int t=0;
	t+=p+q;
	return t;
}
signed main(){
	cout<<cnm(1,2)<<cnm(2,3)<<endl;
}
```

- 局部变量，全局变量，如果多个声明，那么优先使用内部的数据
```C++
int a=5;
int main(){
	int a=10,b=20;
	for(int i=1;i<=3;i++){
		cout<<a++<<" "<<b<<endl;
		{
			static a=0;
			for(int j=1;j<=5;j++){
				a+=j;
			}
			b+=a;
		}
	}
}
```

- 要根据函数返回的类型来决定函数的类型
- 要根据函数内的使用变量来决定函数使用的参数值
```C++
//例如：
char* fun(int c){//程C一般不用string，自己写都行
	return "yes";
}
int* fun1(int c){
	int a[]={1,2,3};
	return a;
}
```

