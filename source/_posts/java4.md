---
title: java4
date: 2026-10-22 18:17:25
tags: java
---
# Java 笔记 4:接口、继承的坑、数组、String 与 Object

> 本篇由课堂速记整理扩写。主线是:**接口(interface)是「能力的规范」,继承是「代码的复用」,而数组/String/Object 是 Java 里最容易在 `==`、`null` 上翻车的三块基础设施。**

## 目录

- [接口 interface](#接口-interface)
- [implements:实现接口](#implements实现接口)
- [接口里的 default / static / private 方法](#接口里的-default--static--private-方法)
- [Comparable:最常用的内置接口](#comparable最常用的内置接口)
- [继承:三个经典问题](#继承三个经典问题)
- [数组](#数组)
- [String](#string)
- [Object:Java 的「宙斯」](#objectjava-的宙斯)
- [本篇易错点清单](#本篇易错点清单)

---

# 接口 interface

## 是什么

接口用来**定义一组方法(规范/契约)**,告诉外界「实现我的类一定具备这些能力」,但接口本身**不关心怎么实现**。

```java
public interface Flyable {
    void fly();          // 抽象方法,隐式 public abstract
}
```

课堂上说它「是一种抽象类」,这是**便于理解的类比,不是语法事实**:

| | 抽象类 `abstract class` | 接口 `interface` |
|---|---|---|
| 本质 | 是类,编译成 `.class` | 是接口,编译成 `.class`,但是独立类型 |
| 能否 `new` | 不能 | 不能 |
| 构造器 | 有(供子类 `super()` 调用) | **没有** |
| 实例字段 | 可以有 | **不能有**(只能有常量) |
| 方法 | 抽象方法 + 具体方法 | 抽象方法 + `default` / `static` / `private` 方法 |
| 继承 | 单继承 `extends` 一个类 | 多继承 `extends` 多个接口 |
| 实现 | `extends` | `implements`,可一次实现多个 |
| 语义 | 「是不是(is-a)」+ 部分复用 | 「能不能(has-ability)」,纯规范 |

一句话:**抽象类是「半成品」,接口是「说明书」**。

## 语法与成员规则

```java
[public] interface 接口名 [extends 接口1, 接口2, ...] {
    // 1. 常量:隐式 public static final,必须初始化
    double PI = 3.14159;

    // 2. 抽象方法:隐式 public abstract
    double area();

    // 3. 默认方法(Java 8+)
    default String describe() {
        return "面积 = " + area();
    }

    // 4. 静态方法(Java 8+)
    static double circleArea(double r) {
        return PI * r * r;
    }

    // 5. 私有方法(Java 9+),只给 default/static 方法内部复用
    private double round2(double x) {
        return Math.round(x * 100) / 100.0;
    }
}
```

要点:

- 接口里的字段**默认就是** `public static final`,所以**必须当场赋初值**,而且实现类拿到的是常量,不能改。
- 接口里的抽象方法默认 `public`,**写 `protected` 会编译报错**(接口方法不允许 protected/private,除非是 Java 9+ 的 private 辅助方法)。
- 接口**不能有构造器**,因为根本不会被 `new`。
- 接口名习惯用**形容词/能力**:`Comparable`、`Runnable`、`Cloneable`、`Serializable`。
- 接口可以继承接口,而且是**多继承**:

```java
interface A { void a(); }
interface B { void b(); }
interface C extends A, B { void c(); }   // C 有三个抽象方法
```

## 接口能干什么(为什么需要它)

1. **统一类型,实现多态**:`Flyable f = new Bird();` 之后只依赖 `Flyable` 的规范,不依赖具体类。
2. **解耦 / 面向接口编程**:调用方只认接口,替换实现不影响调用方。
3. **弥补单继承的不足**:Java 类只能 `extends` 一个类,但可以 `implements` 多个接口。
4. **充当「能力标签」**:`Serializable`、`Cloneable` 里一个方法都没有,只用来标记。

---

# implements:实现接口

```java
class Bird implements Flyable {
    @Override
    public void fly() {                 // 必须是 public
        System.out.println("扇翅膀");
    }
}
```

## 硬性规则

- **必须实现接口里所有的抽象方法**,否则该类必须声明为 `abstract`。
- **实现方法的访问权限不能比接口里的小**。接口方法是 `public`,所以实现方法**必须写 `public`**——这就是速记里「接口的实现得写成 public」的原因。漏写 `public` 会报「attempting to assign weaker access privileges」。
- 方法签名必须匹配;**返回类型允许协变**(子类型),Java 5+ 支持。
- 加 `@Override` 让编译器帮你检查「到底有没有真的重写」,强烈建议写。
- 一个类可以实现多个接口,接口之间用逗号隔开:

```java
class Duck implements Flyable, Swimmable, Comparable<Duck> {
    @Override public void fly() { }
    @Override public void swim() { }
    @Override public int compareTo(Duck o) { return 0; }
}
```

- 如果两个接口里有**同名同参数但返回类型不兼容**的方法,一个类无法同时实现它们,直接编译错误。

## 接口作为类型使用(多态)

```java
Flyable f = new Bird();   // 向上转型
f.fly();                  // 动态绑定到 Bird.fly()
// f.其他Bird特有方法 —— 编译不通过,因为 f 的静态类型是 Flyable
```

想调用子类特有的方法,得向下转型并判断:

```java
if (f instanceof Bird b) {     // Java 16+ 模式匹配
    b.sing();
}
```

---

# 接口里的 default / static / private 方法

## 为什么会有 default

Java 8 之前接口只能有抽象方法。一旦给已发布的接口**新增一个方法**,所有实现类都会编译失败。`default` 方法提供**默认实现**,让接口可以「向后兼容地进化」。

```java
interface Greeting {
    String name();

    default void hello() {                     // 实现类不写也能用
        System.out.println("Hello, " + name());
    }
}

class Person implements Greeting {
    @Override public String name() { return "Tom"; }
}

new Person().hello();       // Hello, Tom
```

实现类也可以**重写** default 方法,改成自己的逻辑。

## static 方法

`static` 方法**属于接口本身**,不能用实现类的实例去调,也不会被继承:

```java
interface MathUtil {
    static int square(int x) { return x * x; }
}

MathUtil.square(5);                 // 正确
// new SomeImpl().square(5);        // 编译错误:static 方法不参与继承
```

作用:把和接口相关的**工具方法**放在接口旁边,避免再单独建一个 `XxxUtils` 类。JDK 里 `Comparator.comparing(...)`、`Stream.of(...)` 都是这种用法。

## private 方法(Java 9+)

当多个 `default` 方法有重复逻辑时,抽成 `private` 方法,但**不对外暴露**:

```java
interface Report {
    default String shortForm()  { return build(10); }
    default String longForm()   { return build(100); }

    private String build(int limit) {          // 只服务于接口内部
        return "report:" + limit;
    }
}
```

## 多接口 default 冲突:三条优先级规则

**规则 1:类优先。** 父类里的具体方法 > 接口的 default 方法。

```java
class Base { public void hello() { System.out.println("Base"); } }
interface Greet { default void hello() { System.out.println("Greet"); } }

class Impl extends Base implements Greet { }
new Impl().hello();       // Base —— 类里的方法赢了,甚至不用重写
```

**规则 2:两个接口的 default 冲突时,实现类必须重写,并用 `接口名.super.方法()` 指定调用谁。**

```java
interface A { default void hello() { System.out.println("A"); } }
interface B { default void hello() { System.out.println("B"); } }

class C implements A, B {
    @Override
    public void hello() {          // 不重写会直接编译错误
        A.super.hello();           // 显式选择
        B.super.hello();
    }
}
```

**规则 3:如果两个接口继承自同一个父接口,而且中间没有重写,那就只有一份 default,不冲突。**

```java
interface Base2 { default void f() { System.out.println("Base2"); } }
interface X extends Base2 { }
interface Y extends Base2 { }

class Z implements X, Y { }        // 合法,没有二义性
new Z().f();                       // Base2
```

这三条规则就是 Java 用接口多继承时,躲开 C++ 菱形二义性的办法。

---

# Comparable:最常用的内置接口

`Comparable` 是 JDK 自带的接口,用来定义类的「**自然顺序**」 ,排序工具(`Arrays.sort`、`Collections.sort`、`TreeMap`、`TreeSet`)都依赖它。

```java
public interface Comparable<T> {
    int compareTo(T o);
}
```

## 返回值约定

| `compareTo` 返回 | 含义 |
|---|---|
| 负数 | `this < o`,this 排在前面 |
| 0 | 相等(排序时不区分先后) |
| 正数 | `this > o`,this 排在后面 |

**只保证符号有意义,不要依赖具体数值**(不要写 `return this.age - o.age` 这种,容易整型溢出)。

## 实现示例

```java
class Student implements Comparable<Student> {
    private final String name;
    private final int score;

    public Student(String name, int score) {
        this.name = name;
        this.score = score;
    }

    @Override
    public int compareTo(Student o) {
        return Integer.compare(this.score, o.score);   // 按分数升序
        // 降序:return Integer.compare(o.score, this.score);
        // 多关键字:先比分数,分数相同比名字
        // int c = Integer.compare(this.score, o.score);
        // return c != 0 ? c : this.name.compareTo(o.name);
    }

    @Override
    public String toString() { return name + ":" + score; }
}
```

使用:

```java
Student[] arr = { new Student("A", 90), new Student("B", 75) };
Arrays.sort(arr);                 // 直接用自然顺序
List<Student> list = new ArrayList<>(List.of(arr));
Collections.sort(list);           // 等价于 list.sort(null)
```

> 注意:实现 `Comparable<T>` 时**一定要写泛型参数**。写成 `implements Comparable`(裸类型)会退化成 `compareTo(Object)`,失去类型检查,还得自己强转。
>
> 另一个约定:`compareTo` 返回 0 的对象,最好 `equals` 也返回 `true`(与 `equals` 保持一致),否则 `TreeSet`/`TreeMap` 会出现「明明不相等却被当成重复元素」的怪现象。

## 与 Comparator 的区别

| | `Comparable` | `Comparator` |
|---|---|---|
| 所在包 | `java.lang` | `java.util` |
| 方法 | `int compareTo(T o)` | `int compare(T a, T b)` |
| 谁的接口 | **被排序的类自己**实现 | **外部**单独写比较器 |
| 排序规则 | 只能有一套「自然顺序」 | 可以有无数套,随时换 |
| 典型用法 | `Arrays.sort(arr)` | `Arrays.sort(arr, cmp)` |

`Comparator` 更灵活,常用链式写法:

```java
// 按分数降序,分数相同按名字升序
Comparator<Student> cmp = Comparator
        .comparingInt(Student::getScore).reversed()
        .thenComparing(Student::getName);

arr.sort(cmp);
```

结论:**类有天然的、唯一的顺序 → 用 `Comparable`;临时/多种排序 → 用 `Comparator`(Lambda 或方法引用)**。

---

# 继承:三个经典问题

先回顾继承的硬规则(Java 是**单继承**):

- `class 子类 extends 父类`,一个类**只能有一个直接父类**;不写 `extends` 时默认继承 `Object`。
- 构造器**不会被继承**;子类构造器第一行会隐式调用 `super()`,父类没有无参构造时必须手动 `super(参数)`,且必须在第一行。
- 重写(`@Override`)要求:方法名、参数列表相同;访问权限**不能变小**;返回类型可协变;`final` / `static` / `private` 方法不能被重写。
- `static` 方法属于类,是**静态绑定**,不参与多态。

继承很爽,但下面三个坑是设计层面必须知道的。

## 1. 方法污染

**定义**:子类被迫继承父类的一堆方法,其中有些方法在语义上**根本不该属于它**;或者子类为了复用一点代码,把不符合自身语义的行为也一起继承了。

经典例子:

```java
class Bird {
    public void fly() { System.out.println("飞"); }
}

class Penguin extends Bird { }     // 企鹅不会飞,却继承了 fly()
```

问题:

- `penguin.fly()` 能编译通过,运行时逻辑却是错的——**契约被污染了**。
- 只想复用 `eat()`、`sleep()`,结果连 `fly()` 一起打包带走。
- 更糟的是**强行重写**成 `throw new UnsupportedOperationException()`,调用方拿到一个「有这个方法但不能用」的对象,违反里氏替换原则(LSP)。

**解决**:

1. 把「会飞」抽成接口,只让需要的类实现:

```java
interface Flyable { void fly(); }
class Eagle extends Bird implements Flyable { public void fly() { } }
class Penguin extends Bird { }               // 干净,没有 fly()
```

2. 用**组合代替继承**(把能力当成成员对象,需要时才委托),这是《Effective Java》的第一条建议:**优先使用组合而非继承**。

> 继承是「白盒复用」:子类能看到并依赖父类实现细节,父类一改,子类可能静默出错。组合是「黑盒复用」,耦合更小。

## 2. 方法爆炸

**定义**:类层次设计不当,导致**子类数量爆炸**或**重复代码爆炸**——每加一个维度就要新增一整批子类,或者同一个方法要在几十个子类里重复实现。

典型场景:两个独立变化的维度被塞进继承树(颜色 × 形状)。

```text
Shape
├── RedCircle
├── BlueCircle
├── RedSquare
├── BlueSquare
├── RedTriangle
├── BlueTriangle
...
```

每增加一种颜色,就要为所有形状各写一个子类;每增加一种形状,又要为所有颜色各写一个子类 → **M × N 个类**。

另一种表现:父类有个 `abstract void draw()`,20 个子类里有 15 个实现完全一样,只有 5 个不同。这时改一次需求要改 15 个文件,漏一个就是 bug。

**解决**:

1. **拆维度**:形状用继承(或接口),颜色用**成员变量/策略对象**组合进来,类数从 M×N 降到 M+N。
2. 把公共实现放到父类的**具体方法**里,子类只重写真正不同的部分(模板方法模式)。
3. 用接口 + `default` 方法共享默认实现,避免每个实现类都抄一遍。

## 3. 菱形继承

**定义**:`D` 同时继承 `B` 和 `C`,而 `B`、`C` 又都继承 `A`,继承图形成菱形。此时 `A` 的成员在 `D` 中存在**两份副本**,调用 `A` 的方法/字段时产生**二义性**。

```text
      A
     / \
    B   C
     \ /
      D
```

C++ 允许多重继承,所以真的有这个问题(需要 `virtual` 虚继承来缓解);**Java 的类不支持多继承**,`class D extends B, C` 是语法错误,因此类的菱形继承问题在 Java 里**根本不会发生**。

但**接口可以多继承**,于是「菱形」以另一种形式回来了——只是**没有状态**(接口没有实例字段),所以只有 `default` 方法的二义性:

```java
interface A { default void f() { } }
interface B extends A { }
interface C extends A { }
class D implements B, C { }        // 合法:A.f 只有一份,没有二义性
```

只有当 `B`、`C` **各自重写了** `f()`,才会冲突,必须显式解决:

```java
interface B extends A { default void f() { System.out.println("B"); } }
interface C extends A { default void f() { System.out.println("C"); } }

class D implements B, C {
    @Override public void f() {
        B.super.f();       // 明确指定,消除二义性
    }
}
```

**总结**:Java 用「类单继承 + 接口多实现」换掉了 C++ 的多重继承,既避免了菱形继承的字段二义性,又保留了「一个类具备多种能力」的表达力。代价是接口不能有状态。

---

# 数组

## 数组是对象

- `int[] a = new int[5];` 中,`a` 是**引用**,指向堆上一块连续内存。
- 数组对象自带 `length` 字段(**是字段,不是方法,没有括号**)。
- 数组长度**一旦创建就不能改**;`a = new int[10]` 只是让 `a` 指向了新数组,原数组会被 GC 回收。
- 数组的父类是 `Object`,所以 `arr.toString()` 得到的是 `[I@1b6d3586` 这种鬼东西,想打印内容要用 `Arrays.toString(arr)`。

## 初值(默认值)

`new` 出来的数组元素会被自动赋默认值,**不会**是随机垃圾值:

| 元素类型 | 默认值 |
|---|---|
| `byte` / `short` / `int` / `long` | `0` |
| `float` / `double` | `0.0` |
| `char` | `'\u0000'`(空字符,打印出来是空白) |
| `boolean` | `false` |
| 引用类型(对象、数组、String) | `null` |

所以 `boolean[] flags = new boolean[3];` 里全是 `false`,`int[] cnt = new int[26];` 直接就能当计数桶用。

## 对象数组:每个元素都要自己 new

**这是最容易错的地方**:`new Student[3]` 只创建了**3 个装引用的槽位**,并没有创建 3 个 `Student` 对象,槽位里全是 `null`。

```java
Student[] a = new Student[3];   // a[0]、a[1]、a[2] 都是 null

a[0] = new Student();           // 必须逐个 new
a[1] = new Student();
a[2] = new Student();
```

如果直接写 `a[0].setName("Tom")` → **`NullPointerException`(空指针异常)**,因为 `a[0]` 还是 `null`。

用循环:

```java
for (int i = 0; i < a.length; i++) {
    a[i] = new Student();
}
```

`String[] s = new String[3];` 同理,三个都是 `null`,`s[0].length()` 直接 NPE。

## 二维数组:数组的数组

`int[][] m = new int[2][3];` 的真实结构是:**一个长度为 2 的数组,每个元素又是一个长度为 3 的 `int[]`**。所以二维数组**不要求是矩阵**,每行长度可以不同(锯齿数组 / jagged array)。

### 规则矩形(一次性 new 完)

```java
int[][] m = new int[2][3];      // 2 行 3 列,内层数组也一并创建好
m[0][0] = 1;
System.out.println(m.length);     // 2(行数)
System.out.println(m[0].length);  // 3(第 0 行的列数)
```

### 不规则二维数组(只 new 第一维)

```java
int[][] t = new int[2][];       // 只创建了外层,内层全是 null
t[0] = new int[3];
t[1] = new int[5];              // 第 1 行 5 列,完全合法
```

### 对象二维数组:内外都要 new

```java
Student[][] a = new Student[2][];   // 外层 2 个槽,内层还是 null
a[0] = new Student[3];              // 第 0 行 3 个槽
a[1] = new Student[3];              // 第 1 行 3 个槽

a[0][0] = new Student();            // 真正创建对象
a[0][1] = new Student();
a[0][2] = new Student();
a[1][0] = new Student();
a[1][1] = new Student();
a[1][2] = new Student();
```

注意速记里那段代码把 `new Student[2]` 和下标 `a[0][2]` 混用了:内层长度是 2 的话,**合法下标只有 0 和 1**,写 `a[0][2]` 就会越界。上面的版本把内层长度统一改成 3 才是自洽的。

顺序很重要:**先 new 内层,再往里放对象**。少了任何一步都是 NPE。

```java
Student[][] b = new Student[2][];
b[0][0] = new Student();    // NullPointerException:b[0] 是 null
```

## 两个必须分清的异常

| 异常 | 触发原因 | 典型代码 |
|---|---|---|
| `NullPointerException` | 对 `null` 引用调用方法 / 访问字段 / 取下标 | `Student[] a = new Student[3]; a[0].getName();` |
| `ArrayIndexOutOfBoundsException` | 下标 < 0 或 ≥ `length` | `int[] a = new int[3]; a[3] = 1;` |
| `NegativeArraySizeException` | `new int[-1]` | `new int[-1]` |

二维数组的 NPE 尤其隐蔽:

```java
int[][] t = new int[2][];
System.out.println(t[0].length);   // NPE:t[0] 是 null,不是"长度 0"
```

自己写代码时可以主动判断:

```java
if (a != null && a[i] != null) {
    // 安全访问
}
```

## 常用操作

```java
int[] a = {5, 2, 9};

a.length                          // 3,注意没有括号
Arrays.toString(a)                // "[5, 2, 9]"
Arrays.sort(a)                    // 原地升序
Arrays.fill(a, 0)                 // 全部填 0
Arrays.equals(a, b)               // 逐元素比较内容
Arrays.copyOf(a, 5)               // 复制成新数组,长度 5,不够补默认值
System.arraycopy(src, 0, dst, 0, n)  // 高效复制,支持重叠
a.clone()                         // 浅拷贝

for (int x : a) { }               // 增强 for,只读遍历(改 x 不影响数组)
```

> **`Arrays.equals` vs `a.equals(b)`**:数组没有重写 `equals`,所以 `a.equals(b)` 比的是**引用**,和 `==` 一样;想比内容必须用 `Arrays.equals`。二维数组要用 `Arrays.deepEquals`。

> **浅拷贝陷阱**:`Student[] copy = a.clone();` 只复制了引用,`copy[0]` 和 `a[0]` 还是**同一个对象**,改 `copy[0].score` 会影响 `a[0]`。需要真正独立时得逐个 `new` 并复制内容(深拷贝)。

---

# String

## 不可变类

`String` 是 `final` 类,**对象一旦创建内容就不能改**。所有看似「修改」的方法(`substring`、`replace`、`toUpperCase`、`concat`…)都是**返回一个新对象**,原对象纹丝不动。

```java
String s = "abc";
s.toUpperCase();          // 返回 "ABC",但没接收
System.out.println(s);    // 还是 abc

s = s.toUpperCase();      // 这才"看起来"改了,其实是 s 指向了新对象
```

好处:可以安全共享、天然线程安全、`hashCode` 可缓存(适合做 `HashMap` 的 key)。

需要频繁拼接时用 `StringBuilder`(单线程)或 `StringBuffer`(线程安全),避免在循环里 `s += x`(每次都会产生新对象,复杂度退化到 O(n²))。

## `==` 判地址,`equals` 判内容

这是最重要的一条:

- `==` 对引用类型比较的是**两个引用是否指向同一块内存**(身份 identity)。
- `equals` 是 `Object` 定义的方法,**`String` 重写了它**,逐字符比较内容。

```java
String a3 = "abc", a4 = "abc";
String a1 = new String("abc");
String a2 = new String("abc");

a3 == a4          // true  —— 字面量,同一个常量池对象
a1 == a2          // false —— new 出来的两个不同对象
a1 == a3          // false —— 一个在堆,一个在池
a1.equals(a2)     // true
a1.equals(a3)     // true
```

原因:**字符串常量池(String Pool)**。直接写 `"abc"` 时,JVM 先去池里找,有就复用同一个对象;`new String("abc")` 则是**强制在堆上新建一个对象**(可能还会复用池里的字符数组,但对象本身是新的)。

```java
// 验证:让 new 出来的对象也进池
String b = a1.intern();
b == a3           // true
```

## 编译期常量折叠

编译期就能确定值的字符串拼接,会被编译器直接合成一个字面量,依然走常量池:

```java
String s1 = "a" + "b";        // 编译期折叠成 "ab",在池中
s1 == "ab";                   // true

String x = "a";               // 普通变量,不是编译期常量
String s2 = x + "b";          // 运行期 StringBuilder 拼接,堆上新对象
s2 == "ab";                   // false
s2.equals("ab");              // true

final String y = "a";         // final + 字面量 = 编译期常量
String s3 = y + "b";          // 折叠成 "ab"
s3 == "ab";                   // true
```

最后那个例子说明:**是否发生折叠取决于变量是不是「编译期常量」(`final` 修饰 + 常量表达式)**,而不是它看起来简不简单。

## `equals` 在自定义类里的默认行为

- `Object.equals` 的默认实现**是 `==`**,也就是**比地址**。
- 所以自定义类不重写 `equals`,`new Student("Tom").equals(new Student("Tom"))` 是 **`false`**。
- **只有 `String`、包装类(`Integer` 等)、集合类等重写了 `equals`**,才是「判内容」。

```java
class Student {
    private String name;
    private int score;
    // 没有重写 equals
}

new Student("Tom", 90).equals(new Student("Tom", 90));   // false
```

正确重写:

```java
import java.util.Objects;

class Student {
    private String name;
    private int score;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;                        // 1. 地址相同,直接 true
        if (o == null || getClass() != o.getClass()) return false;  // 2. 类型必须一致
        Student s = (Student) o;
        return score == s.score && Objects.equals(name, s.name);
    }

    @Override
    public int hashCode() {                                // 3. equals 必须配 hashCode
        return Objects.hash(name, score);
    }
}
```

> **约定(必须遵守)**:`a.equals(b) == true` ⇒ `a.hashCode() == b.hashCode()`。只重写 `equals` 不重写 `hashCode`,`HashSet`/`HashMap` 里会出现「明明存在却查不到」的 bug。
>
> 注意参数类型必须是 `Object`,写成 `equals(Student o)` 是**重载**,不是重写,不会参与多态——这就是速记里说的「加 `@Override` 让系统检查」。

## 常用方法速查

| 方法 | 说明 |
|---|---|
| `length()` | 长度(**有括号**,和数组不同) |
| `charAt(i)` | 取第 i 个字符,越界抛 `StringIndexOutOfBoundsException` |
| `substring(b, e)` | 截取 `[b, e)`,**含头不含尾** |
| `indexOf(s)` / `lastIndexOf(s)` | 查找子串,找不到返回 `-1` |
| `contains(s)` | 是否包含 |
| `startsWith` / `endsWith` | 前缀 / 后缀 |
| `equalsIgnoreCase(s)` | 忽略大小写比较 |
| `compareTo(s)` | 字典序,返回负/0/正(和 `Comparable` 一致) |
| `trim()` / `strip()` | 去首尾空白(`strip` 支持 Unicode,Java 11+) |
| `split(regex)` | 按正则切分,返回 `String[]` |
| `replace(a, b)` / `replaceAll(regex, b)` | 替换(后者是正则) |
| `toCharArray()` | 转字符数组,方便逐字符处理 |
| `String.valueOf(x)` | 任意类型转字符串(比 `x + ""` 清晰) |
| `String.join(",", list)` | 拼接集合 |
| `String.format("%d", x)` | 格式化 |

## 判空与比较的坑

```java
String s = null;

// s.equals("abc")      → NPE,s 是 null
// s.length()           → NPE

// 正确写法 1:常量在前,天然不怕 null
"abc".equals(s);           // false,不抛异常

// 正确写法 2:先判 null
if (s != null && s.equals("abc")) { }

// 正确写法 3:JDK 工具
Objects.equals(s, "abc");  // null 安全
Objects.requireNonNull(s); // null 就抛 NPE,用于参数校验

// 判"空串" vs "全是空白"
s != null && s.isEmpty();          // 长度 0
s != null && s.isBlank();          // Java 11+,trim 后为空也算
```

---

# Object:Java 的「宙斯」

`java.lang.Object` 是所有类的根。**任何没有显式写 `extends` 的类,都隐式 `extends Object`**;接口虽然不继承 `Object`,但实现类仍然通过类继承链拥有 `Object` 的方法。

因此:**`Object` 类型的引用可以指向任何对象**,它是 Java 里最宽的「万能类型」。

```java
Object o1 = new Student();
Object o2 = "abc";
Object o3 = 123;          // 自动装箱成 Integer
Object o4 = new int[3];   // 数组也是对象
Object[] arr = { o1, o2, o3, o4 };   // 可以装一切
```

代价:通过 `Object` 引用只能调用 `Object` 里声明的方法,想用子类功能必须**向下转型**:

```java
Object o = "abc";
// o.length();               // 编译错误:Object 没有 length()
if (o instanceof String s) {
    System.out.println(s.length());   // 3
}

String s2 = (String) o;      // 强转,类型不对就抛 ClassCastException
```

> 现代 Java 里,「用 `Object` 装一切」的场景基本被**泛型**取代(`List<T>`),因为泛型有编译期类型检查,不用强转。

## Object 的方法

| 方法 | 作用 | 是否常重写 |
|---|---|---|
| `boolean equals(Object o)` | 判断是否「相等」,默认比地址 | 要重写 |
| `int hashCode()` | 哈希值,默认由地址推导 | **重写 equals 就必须重写它** |
| `String toString()` | 返回字符串表示,默认 `类名@十六进制hashCode` | 要重写 |
| `Class<?> getClass()` | 拿到运行时类对象,**final,不能重写** | 否 |
| `protected Object clone()` | 浅拷贝,类还必须实现 `Cloneable`,否则抛 `CloneNotSupportedException` | 按需 |
| `protected void finalize()` | GC 前调用,**已废弃(Java 9+ deprecated,18 起不建议)** | 不要用 |
| `wait()` / `notify()` / `notifyAll()` | 线程间协作,必须在 `synchronized` 块内调用 | 否 |

## `toString`

不重写时:

```java
System.out.println(new Student());   // Student@1b6d3586
```

重写后:

```java
@Override
public String toString() {
    return "Student{name=" + name + ", score=" + score + "}";
}
```

`String` 的 `+` 拼接、`println`、`String.valueOf`、日志打印对象时都会自动调用 `toString`,所以重写它调试体验提升巨大。IDE 一般能一键生成。

## `equals` / `hashCode` 契约(再强调一次)

1. **自反**:`x.equals(x)` 必须为 `true`。
2. **对称**:`x.equals(y)` 与 `y.equals(x)` 必须一致。
3. **传递**:`x.equals(y)` 且 `y.equals(z)` ⇒ `x.equals(z)`。
4. **一致**:只要对象状态没变,多次调用结果不变。
5. **非空**:`x.equals(null)` 必须为 `false`。
6. **哈希一致**:`equals` 为真 ⇒ `hashCode` 相同(反之不要求)。

违反第 2 条的经典错误:

```java
class A { }
class B extends A {
    @Override public boolean equals(Object o) { return o instanceof B; }
}
new A().equals(new B());   // false
new B().equals(new A());   // false —— 这次对称了
// 但如果 A 用 instanceof A 判断,就会出现 true/false 不对称
```

所以标准写法用 `getClass() != o.getClass()`(严格同类)或两边都用 `instanceof`(允许子类),不要混用。

## 自动装箱的 `==` 陷阱

`Object` 与包装类结合时有个著名坑:

```java
Integer a = 127, b = 127;
a == b;                 // true —— Integer 缓存 -128~127

Integer c = 128, d = 128;
c == d;                 // false —— 超出缓存范围,是两个对象
c.equals(d);            // true —— 永远用 equals 比包装类
```

所以:**比较包装类一律用 `equals`,或者先拆箱成基本类型再比**。

---

# 本篇易错点清单

- [ ] 接口**不是类**:不能 `new`,没有构造器,不能有实例字段(只有 `public static final` 常量)。
- [ ] 接口方法默认 `public abstract`,实现类的方法**必须写 `public`**,权限不能缩小。
- [ ] 接口里 `default` / `static` 需要 Java 8+,`private` 方法需要 Java 9+;`static` 方法只能 `接口名.方法()` 调用,不被继承。
- [ ] 两个接口的 `default` 冲突 → 必须重写,用 `A.super.hello()` 选择;父类具体方法优先级最高。
- [ ] `Comparable` 返回值只看**符号**;别写 `return a - b`(整型溢出);实现时记得带泛型 `Comparable<T>`。
- [ ] 继承的三大坑:**方法污染**(不该有的方法被继承)、**方法爆炸**(子类/重复代码疯长)、**菱形继承**(Java 类单继承已规避,接口靠显式 `super` 解决)。
- [ ] 数组默认值:数值 `0`、`char '\u0000'`、`boolean false`、引用 `null`。
- [ ] `new Student[3]` **不创建对象**,只创建 3 个 `null` 槽;每个元素都要 `new`。二维数组还要先 `new` 内层。
- [ ] `NullPointerException` ≠ `ArrayIndexOutOfBoundsException`:一个是 `null`,一个是下标越界。
- [ ] 数组 `.length` **没有括号**;`String.length()` **有括号**。
- [ ] `a.equals(b)` 对数组比的是地址,要比内容用 `Arrays.equals` / `Arrays.deepEquals`。
- [ ] `String` 的 `==` 比地址(`new String` 一定不同),`equals` 比内容;`intern()` 可以把堆上的字符串放进常量池。
- [ ] 自定义类不重写 `equals` 时,**默认比地址**(不是比内容);重写 `equals` 必须同时重写 `hashCode`。
- [ ] 包装类比较用 `equals`:`Integer` 只缓存 `-128~127`。
- [ ] 判空把常量写在前面:`"abc".equals(s)`,或 `Objects.equals(s, "abc")`。
