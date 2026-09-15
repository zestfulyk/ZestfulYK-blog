---
title: D. Sequence 题解
date: 2026-09-10 12:42:22
tags: 算法
mathjax: true
---

这道题是一道非常经典的动态规划（DP）与二维偏序优化问题。我们可以通过前缀和将“段内红色棋子最多”的条件转化为二维坐标上的偏序关系，然后利用数据结构或 CDQ 分治进行优化。

### 题目分析

题意要求我们将长度为 $n$ 的序列划分为若干个连续段，使得满足“红棋子数量不少于黄棋子和蓝棋子”的段（红色段）的长度之和最大。
对于一个红色段 $[j, i]$，必须满足：

1. $R_i - R_{j-1} \ge Y_i - Y_{j-1} \implies R_i - Y_i \ge R_{j-1} - Y_{j-1}$
2. $R_i - R_{j-1} \ge B_i - B_{j-1} \implies R_i - B_i \ge R_{j-1} - B_{j-1}$

其中 $R, Y, B$ 分别表示红、黄、蓝棋子的前缀和。
我们令 $U_i = R_i - Y_i$，$V_i = R_i - B_i$。
那么段 $[j, i]$ 为红色段的充要条件是：**$U_{j-1} \le U_i$ 且 $V_{j-1} \le V_i$**。

### 动态规划建模

我们定义 $dp[i]$ 为前 $i$ 个位置中，所有红色段的长度之和的最大值。
状态转移有两种情况：

1. 第 $i$ 个元素不在任何红色段中，此时 $dp[i] = dp[i-1]$。
2. 第 $i$ 个元素在以 $j$ 为起点的红色段中，此时必须满足 $U_{j-1} \le U_i$ 且 $V_{j-1} \le V_i$。
转移方程为：$dp[i] = \max(dp[i], dp[j-1] + i - j + 1)$。

为了方便维护，我们可以变形一下第二种情况的式子：


$$dp[i] = \max_{j} \{ (dp[j-1] - (j - 1)) + i \}$$


令 $cost[k] = k - dp[k]$，实际上 $cost[k]$ 就表示在前 $k$ 个元素中**未被红色段覆盖的元素个数**。显然我们希望这个值越小越好。
原问题转化为求：


$$cost[i] = \min \left( cost[i-1] + 1, \min_{k < i, U_k \le U_i, V_k \le V_i} cost[k] \right)$$


最后答案即为 $n - cost[n]$。

### 算法优化：CDQ 分治 / 树状数组嵌套

因为有 $U_k \le U_i, V_k \le V_i$ 两个条件，这是一个典型的二维偏序问题，可以用带权值的二维前缀最小值来维护。但 $dp[i]$ 的计算是在线（动态）的，所以不能直接套用简单的排序。

**方案一：CDQ 分治解决在线 DP**
CDQ 分治通常用来解决离线问题，但稍微修改就可以解决 1D 动态规划问题：

1. 求解过程 `solve(L, R)`：如果 $L = R$，说明 $cost[L]$ 已经算出了，直接返回。
2. 令 $mid = (L + R) / 2$。
3. 递归解决左半部分 `solve(L, mid)`。
4. **处理左半部分对右半部分的贡献**：
将左半部分 $[L, mid]$ 和右半部分 $[mid+1, R]$ 分别按 $U$ 的值从小到大排序。
使用双指针，将左半部分中满足 $U_k \le U_i$ 的元素加入到一个树状数组（维护 $V$ 的前缀最小值）中。
对于右半部分的每个 $i$，在树状数组中查询 $V \le V_i$ 的最小 $cost$，去更新 $cost[i]$。
5. 递归解决右半部分 `solve(mid+1, R)`。（注意：右半部分在求解前必须按原下标顺序还原，或者在排序前复制一份数组）。

**时间复杂度**：$O(n \log^2 n)$，常数较小。在 $n = 10^6$ 且时限为 2 秒的情况下能够顺利通过。

**方案二：离散化 + 线段树套平衡树 / 动态开点二维线段树**
由于只要维护前缀最小值，我们可以把所有 $(U_k, V_k)$ 映射到坐标系上。由于在线，我们可以直接使用树状数组维护 $U$，其每个节点是一棵权值线段树维护 $V$。时间复杂度也是 $O(n \log^2 n)$，但空间复杂度较大，需要使用动态开点。

### 代码实现思路（基于 CDQ 分治）

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 1000005;

struct Point {
    int id, u, v, cost;
} a[MAXN], temp[MAXN];

int n;
int bit[MAXN * 3]; // 离散化后的 V 坐标范围，最大不超过 3*MAXN
int max_v;

// 树状数组维护前缀最小值
void update(int idx, int val) {
    for (; idx <= max_v; idx += idx & -idx)
        bit[idx] = min(bit[idx], val);
}

void clear(int idx) {
    for (; idx <= max_v; idx += idx & -idx)
        bit[idx] = INF;
}

int query(int idx) {
    int res = INF;
    for (; idx > 0; idx -= idx & -idx)
        res = min(res, bit[idx]);
    return res;
}

bool cmpU(const Point &p1, const Point &p2) {
    return p1.u < p2.u;
}

void cdq(int l, int r) {
    if (l == r) {
        if (l > 0) {
            a[l].cost = min(a[l].cost, a[l-1].cost + 1);
        }
        return;
    }
    int mid = (l + r) >> 1;
    cdq(l, mid);
    
    // 拷贝出来按照 U 排序
    for (int i = l; i <= r; ++i) temp[i] = a[i];
    sort(temp + l, temp + mid + 1, cmpU);
    sort(temp + mid + 1, temp + r + 1, cmpU);
    
    int j = l;
    for (int i = mid + 1; i <= r; ++i) {
        while (j <= mid && temp[j].u <= temp[i].u) {
            update(temp[j].v, temp[j].cost);
            j++;
        }
        int min_cost = query(temp[i].v);
        if (min_cost != INF) {
            a[temp[i].id].cost = min(a[temp[i].id].cost, min_cost);
        }
    }
    
    // 清空树状数组（千万不要 memset）
    for (int i = l; i < j; ++i) {
        clear(temp[i].v);
    }
    
    cdq(mid + 1, r);
}

```

### 复杂度评估

* **时间复杂度**：每一层分治排序和树状数组更新花费 $O(len \log (len))$。一共有 $\log n$ 层，总时间复杂度为 $O(n \log^2 n)$。
* **空间复杂度**：由于只需要离散化和常数个数组，空间占用约为 $O(n)$，远低于题目的 `1024 MB` 限制。