---
title: java笔记1
date: 2026-10-16 22:59:32
tags: java
---

```java
public class Helloworld{
	public static void main(String[] args){//程序入口 
		String s="ZJUT";
		System.out.println(s);
	}
}
```

编译方式:

```bash
javac XXX.java
```

```bash
java XXX
```

下面那个不要后缀

# 命名规范

常量大写
变量方法小驼峰
类名接口大驼峰

# 类型空间

java的char16位
bool 8位(方便管理)

## 强制转换

若是大类型转小类型,比如long转int,得到低的位

例如:
```java
int a=260;
byte b=a;
```
取低8位,所以`b=4`

# 值的比较

```java
String str1=new String("1");
String str2=new String("1");
String str3=str1;
str3==str1// false
str2==str1// true
```

这里生成的叫做**引用**类型

要比较里面的内容的话,需要使用`equals`函数

```java
str1.equals(str2);
```

## 引用类型介绍

在java中,如果你看到一个变量被赋值为new什么什么,那么这个变量一定是引用类型

引用在本质上类似C++的指针,但是底层逻辑不一致,在java中,可以直接访问内部值,不需要再加一个`*`.

然后除此之外,java ban掉了指针运算,区别仅此而已,一定要仔细区别

## 引用类型在函数传值中的神秘考点

基本类型无影响,这和C++一样,
但是如果是引用类型,就会变化了,要是在函数内部改变了其指向,比如new了一下,那又不改变了
最后如果是神秘类型比如String,Integer这种,怎么都不会改变

举例:
```java
class A{
	int x=0;
	A(int n){
		x=n;
	}
	void change(A a){
		x=1;        // 可以改变
		a=new A(3);
		a.x=1;      // 没用了,指向变了
	}
	public void static main(String args[]){
		A a=new A(2);
		change(a);
	}
}
```

## 浮点数

注意不能直接比较是否相等,只能比大小,加个`eps=1e-6`就行

例如:
```java
for(double x=0.1;x!=1.0;x+=0.1);
```
会死循环

```java
double d1=0.5;
d1=0.1+d1;
d1=0.1+d1;
d1=0.1+d1;
System.out.println(d1);
```

输出是0.7999999,精度丢失

# 输出溢出处理

输出到文件

```bash
XXX.exe > a.txt
```

# 输入

## 使用主函数输入

```java
public static void main(String[]args){
	System.out.println(args[0]+args[1]);
}
```

这样写,后面运行时,就会自动在程序开始时读取参数了

## 使用Scanner输入

```java
Scanner scan = new Scanner(System.in);
int a=scan.nextInt();
```

## 使用输入流读取

```java
System.in.read(a);
// or
BufferedReader buf=new BufferedReader(new InputStreamReader(System.in));
buf.readLine();
```

下面那段屎山的作用是,首先获取键盘输入,然后转化成程序语言,然后再逐块读取,加速写入

# 逻辑运算短路

注意,只有**逻辑运算**,只有**逻辑运算**,只有**逻辑运算**,才有短路性质

比如位运算`&`,就没有这个性质,别被骗了

