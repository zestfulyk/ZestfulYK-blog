---
title: java笔记2
date: 2026-10-19 15:04:27
tags: java
---
# Final关键字

## int

用在`int`,作用类似`const`

```java
final a=1;
```

## 数组

用在数组,表示的是不变的指针,一旦申请了内存,就不能再修改其指向

>**final 锁的是“数组引用”，不是“数组内容”。**

```C++
final int[] arr={1,2,3};
arr[0]=99;              //  可以改元素
arr=new int[]{4,5};     //  不能改引用
```

同样的,数组长度也是不能修改的,因为这也相当于修改数组的引用

## 类

表示之后不允许使用这个类来继承

# `toString`

输出一个对象的所有信息,可以自定义

比如

```java
public toString(){
	return super.toString()+"n\radius="+radius;
}
```

# super

继承的上一级,用于调用上一级的函数

比如:`super.XXX()`,`super()`,表示上一级的函数或者上一级的构造函数

如果使用的是构造函数,必须出现在子构造函数的第一行,且不能再用this来构造

同样的,也能访问上一级的成员变量的值

但是,注意必须要有实例才能使用super

因此,static函数中不允许使用super

例子:

```java
class Person{
	public Person(){
		System.out.println("hi!");
	}
	public Person(String s){
		this();// 调用自己的构造函数
		System.out.println("I am"+s);
	}
}
public class Who extends Person{
	public Who(){
		this("I am,Tony");
	}
	public Who(String s){
		super(s);
		System.out.println("How do you do?");
	}
	public static void main(String args[]){
		Who w= new Who("Tom");
	}
}
```


# 层级间的调用关系

特别注意不同包中protected的特殊访问方式

子类能调用父类中的`protected`,但是要是创建的是父类对象的就不能访问

```java
FatherClass a = new FatherClass();
a.protectedVariable = 0;// 这一行会报错
```

```java
ChildClassInAnotherPackage a2 = new ChildClassInAnotherPackage();
a2.protectedVariable = 0;// 这一行是合法的
```

注意这两种方法的区别

子类方法**不能缩小**父类方法的**访问权限**

同一包,放在同一个文件夹下的,并且包命名相同的类(`package`)

这么做的目的是为了更好的设定访问的边界,以及实现更高效的代码组织

|           | 同一类 | 同一包 | 不同包的子类 | 其他类 |
| --------- | --- | --- | ------ | --- |
| public    | 允许  | 允许  | 允许     | 允许  |
| protected | 允许  | 允许  | 允许     | 不允许 |
| defult    | 允许  | 允许  | 不允许    | 不允许 |
| private   | 允许  | 不允许 | 不允许    | 不允许 |

# 就近原则

在java中,因为全是类,所以类的操作被优化到了极值,

在这里根本不存在使用指针来实现多态,这里要是重名覆盖了,直接选择对应的

但是要是存在多个相同名字的函数,程序会逐层网上查找,找到第一个满足的作为结果使用

其实感觉这条性质也不是很重要,反正为了防止这个问题,总会加上`this`,`super`来访问的

# 构造函数注意点

java中的逻辑是,要是你写了带参数的构造函数,那么默认构造函数**必须自己手写**,要是都不写,系统才会分配默认构造函数

比如:

```java
class Member{
	int instanceVar;
	Member(){
		instanceVar=0;
	}
	Member(int i){
		instanceVar=i;
	}
}
class SubMember extends Member{
	SubMember(int j){
		Super(j);
		instanceVar=j;
	}
}
public class TestDefultConstructor{
	public static void main(String args[]){
		Member m1=new Member(1);
		SubMember m2=new SubMember(2);
	}
}
```

在这段程序中,要是删掉了第3行的构造函数,代码就不正确了,因为你写了带参数的,系统不负责帮你再分配一个

此外,子类在构造时**必须要调用**父类的构造函数,因此上述代码中的`Super(j)`是不可删除的