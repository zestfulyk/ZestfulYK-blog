---
title: ACM训练
date: 2025-12-7 22:15:00
tags: 算法
---
# 简单题

- 对于简单题目，最好还是仔细一点，或者使用最暴力的解法，而不是投机取巧，或者构造高级方法，通常样例数据都是片面的，常常会有坑。

[sleeping through classes](https://codeforces.com/contest/2173/problem/A)

比如这一题，数据没有包含i+k中间有1的情况，直接i+=k导致错误。


# 中等题目

- 中等题目就需要强观察力和trick技巧了

[Niko's Tactical Cards](https://codeforces.com/contest/2173/problem/B)

这一道题目是动态规划的变种，虽然要求每一步最优，但是可能发生最小值突然转变成最大值的情况，因此，计算最小值也是必要的。只要计算这两个值就行了。

[Kanade's Perfect Multiples](https://codeforces.com/contest/2173/problem/C)

这题希望我们构造一个满足要求的B，这个就有点类似于筛法求素数了，实际上两者的代码几乎是一样的，但是在做的时候要注意区分原始数据和v数组，一个一个遍历就行了，找不到就可以直接退出，因为不然当前确定的最小值就无法被覆盖了。

[Merging the Sets](https://codeforces.com/problemset/problem/2146/B)

你想选择其中的一些集合（可能一个都不选，也可能全部都选），使得 1 和 m 之间的每个整数都包含在**个所选集合中的至少一个**中。
思维误区，不用一边读入一边判断，因为数据保证$l\leq 2*10^5$所以先读入再判断就行了，此外，要方法合法需要这个集合不存在也合法，那么只要用桶来看看去掉会不会变0就行了。原先想到的覆盖才合法的思路不对的原因是前后都有可能覆盖。

[Abraham's Great Escape](https://codeforces.com/problemset/problem/2155/B)

要求构造一个方阵，每个位置一个箭头，满足有k个格子能沿箭头出去。
其实只要管最后一行，前面k个填U，后面的填D，最后一行填$RRR……RL$就行了
比如：
```C++
1
9 4
UUU
UDD
RRL
```
这样在最后一行产生循环，前面的不管。原来的做法是两个两个组合，产生循环，虽然也能做，但是不方便。

[Cake Assignment](https://codeforces.com/problemset/problem/2138/A)

这个题目的重要观察点是，当最后一步确定后，上一步的操作一定是确定的，于是我们就可以倒推

[XOR Array](https://codeforces.com/contest/2175/problem/B)

这题的要求是构造一个数组，满足仅在l到r上的异或和为0，其他位置全非0，
异或有一个特点，和前缀和一样，可以构建前缀异或和，因为$x\oplus y \oplus x==x$
此外非常容易陷入的一个点是，可能会想到之间填入1-n来构造，但是实际上，这么异或会产生很多的0，所以这个方法是不行的。（比如1，2，3）
因此，这里我们的操作是构造最终异或的结果，写一个前缀异或数组，最后再反推原数组就行了。
详细信息可以见异或的笔记部分