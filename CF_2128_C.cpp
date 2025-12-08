#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <map>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <array>
#include <unordered_map>
#include <numeric>
#include <functional>
#include <iomanip>
#include <chrono>
using namespace std;
#define ll long long
#define int ll
#define endl '\n'
void solve(){

}
signed main(){
    ll T; cin>>T;
    while(T--) solve();
    return 0;
}
/*0.注意vector的size是size_t不能直接减去一个数，要类型转换
1.深呼吸，不要紧张，慢慢读题，读明白题，题目往往比你想的简单。
2.暴力枚举:枚举什么，是否可以使用一些技巧加快枚举速度（预处理、前缀和、数据结构、数论分块）。
3.贪心:需要排序或使用数据结构（pq）吗，这么贪心一定最优吗。
4.二分：满足单调性吗，怎么二分，如何确定二分函数返回值是什么。
5.位运算：按位贪心，还是与位运算本身的性质有关。
6.数学题：和最大公因数、质因子、取模是否有关。
7.dp：怎么设计状态，状态转移方程是什么，初态是什么，使用循环还是记搜转移。
8.搜索：dfs 还是 bfs ，搜索的时候状态是什么，需要记忆化吗。
9.树上问题：是树形dp、树上贪心、或者是在树上搜索。
10.图论：依靠什么样的关系建图，是求环统计结果还是最短路。
11.组合数学：有几种值，每种值如何被组成，容斥关系是什么。
12.交互题：log(n)次如何二分，2*n 次如何通过 n 次求出一些值，再根据剩余次数求答案。
13.如果以上几种都不是，多半是有一个 point 你没有注意到，记住正难则反.                                                                                                      
 ___________________
/__________________/\
|___________      / /
           /     / /
          /     / /
         /     / /
        /     / /
       /     / /                      
      /     / /         ____________ _______________
     /     / /         /            \  ____________|
    /     / /         |    _______  | |
   /     / /          |   |  ____|  | |____________
  /     / /___________|   | |_______|___________   |
 /     /_____________/|   |_________ ___________|  |
|____________________|/_____________|______________|
*/