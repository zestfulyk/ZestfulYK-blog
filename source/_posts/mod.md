---
title: 模运算性质总结
date: 2025-11-25 09:26:45
tags: 算法
mathjax: true
---
# 模运算（Mod）性质总结

## 定义

对于任意实数 $( x, y )$，有：

$$x \mod y = x - y \left\lfloor \frac{x}{y} \right\rfloor, \quad y \neq 0$$

模运算（在一些场合使用符号 % 表示）是一个二元运算。$( x \mod y )$ 的值范围如下：

- 当 $( y > 0 )$ 时：$( 0 \leq x \mod y < y )$
- 当 $( y < 0 )$ 时：$( 0 \geq x \mod y > y )$
- 当 $( y = 0 )$ 时：为避免除以零，定义 $( x \mod 0 = x )$

## 基本运算规则

模运算与基本四则运算类似（除法除外）：

1. **加法规则**：$((a + b) \mod p = (a \mod p + b \mod p) \mod p)$
2. **减法规则**：$((a - b) \mod p = (a \mod p - b \mod p) \mod p)$
3. **乘法规则**：$((a \times b) \mod p = (a \mod p \times b \mod p) \mod p)$
4. **幂运算规则**：$(a^b \mod p = ((a \mod p)^b) \mod p)$
5. **求和规则**：由第1个公式可推导出 $(\left(\sum_{i=1}^{n} x_i\right) \mod p = \left(\sum_{i=1}^{n} (x_i \mod p)\right) \mod p)$

## 运算律

### A. 结合律

$$((a + b) \mod p + c) \mod p = (a + (b + c) \mod p) \mod p$$

$$((a \times b) \mod p \times c) \mod p = (a \times (b \times c) \mod p) \mod p$$

### B. 交换律

$$(a + b) \mod p = (b + a) \mod p$$

$$(a \times b) \mod p = (b \times a) \mod p$$

### C. 分配律

$$(a + b) \mod p = (a \mod p + b \mod p) \mod p$$

$$((a + b) \mod p \times c) \mod p = ((a \times c) \mod p + (b \times c) \mod p) \mod p$$

## 补充性质

### 同余性质

- **反身性**：$(a \equiv a \pmod{m})$
- **对称性**：如果 $(a \equiv b \pmod{m})$，则 $(b \equiv a \pmod{m})$
- **传递性**：如果 $(a \equiv b \pmod{m})$ 且 $(b \equiv c \pmod{m})$，则 $(a \equiv c \pmod{m})$

### 模运算与除法

模运算与除法不直接兼容，但有以下性质：

- 如果 $(ac \equiv bc \pmod{m})$ 且 $(\gcd(c, m) = 1)$，则 $(a \equiv b \pmod{m})$
    
- **模逆元**：如果 $(\gcd(a, m) = 1)$，则存在整数 $(b)$ 使得 $(ab \equiv 1 \pmod{m})$，称 $(b)$ 为 $(a)$ 模 $(m)$ 的逆元
    
- **核心性质**：在模运算里除以一个数等于乘以这个数的逆元，即：$$c/a≡c×a^{−1} (modm)$$其中 $a^{-1}$ 是 $a$ 在模 $m$ 下的逆元。

**重要前提**：模逆元存在的**充分必要条件**是 $\gcd(a, m) = 1$（即 $a$ 与 $m$ 互质）。如果 $a$ 与 $m$ 不互质，则 $a$ 在模 $m$ 下没有逆元，除法操作无法进行。

---
#### 计算模逆元的方法

常用的计算模逆元的方法是**扩展欧几里得算法**，它不仅能求最大公约数，还能找到满足贝祖等式的系数。

示例代码;
```C++
#include <iostream>
using namespace std;

// 扩展欧几里得算法求逆元
long long mod_inverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;
    
    if (m == 1) return 0;
    
    while (a > 1) {
        long long q = a / m;
        long long t = m;
        
        m = a % m;
        a = t;
        t = y;
        
        y = x - q * y;
        x = t;
    }
    
    if (x < 0) x += m0;
    
    return (a == 1) ? x : -1; // 如果逆元不存在返回 -1
}

// 使用示例
int main() {
    long long a = 3, m = 7;
    long long inv = mod_inverse(a, m);
    if (inv != -1) {
        cout << a << " 在模 " << m << " 下的逆元是: " << inv << endl;
    } else {
        cout << a << " 在模 " << m << " 下没有逆元" << endl;
    }
    return 0;
}
```

#### 应用示例

计算 $6 / 3 \pmod{7}$：

1. 先求 $3^{-1} \pmod{7}$：$3 \times 5 = 15 \equiv 1 \pmod{7}$，所以逆元为 5
    
2. $6 / 3 \equiv 6 \times 5 = 30 \equiv 2 \pmod{7}$
    
3. 验证：$2 \times 3 = 6 \equiv 6 \pmod{7}$ ✓
    

这个性质在密码学、组合数学和算法竞赛中都有广泛应用。
### 模运算的周期性质

- 对于任意整数 $(k)$，有 $(a \mod m = (a + km) \mod m)$
- 模运算的结果具有周期性，周期为模数 $(m)$
