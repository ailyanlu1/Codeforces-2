//
//  main.cpp
//  Codeforces
//
//  Created by loyinglin.
//  Copyright loyinglin. All rights reserved.

/************************** 题解 **********************
 题目链接：http://codeforces.com/contest/818/problem/C
 题目大意：
 n个数字排成一行，现在需要选出若干个区间，要求：
 1、区间[l, r]如果包含数字x，那么所有数字x应该都在区间[l, r]内，并且区间与区间没有覆盖；
 2、区间的权值等于区间内所有数字的XOR（相同数字只XOR一次）；
  求能得到的最大权值。
 
   n (1 ≤ n ≤ 5000)
  (0 ≤ a[i] ≤ 5000)
 
 Examples
 input
 6
 4 4 2 5 2 3
 output
 14
 样例解释：: [4, 4] [2, 5, 2] [3] 权值和 = 4 + (2 xor 5) + 3 = 4 + 7 + 3 = 14
 
 
 题目解析：
 根据要求1，我们可以得知：
 每个数字x有三个信息要记录，分别是最左边x的位置、最右边x的位置、x的值；
 最左和最右可以通过遍历统计，存到x对应的位置。
 
 再由要求1，我们知道区间不能覆盖，那么满足无后效性；
 我们假设dp[i]表示前i个最优解，假如区间[k, i]可以满足要求1，那么有dp[i]=dp[k-1]+xor(k, i);
 同时dp[i]=max(dp[i], dp[i-1]);
 
 接下来就是如何快速求出所有区间[k, i] 以及 对xor(k, i)求和；
 容易知道,xor(k, i)遍历一遍方法即可，并且可以针对(k, i)进行缓存；
 
 状态数有O(N^2)，转移的复杂度在预处理xor(k, i)之后是O(1)，预处理的复杂度是O(N^2); 
 ************************* 题解 ***********************/
#include<cstdio>
#include<cmath>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<deque>
#include<string>
#include<utility>
#include<sstream>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long lld;
const int N = 5010, M = 3010100, inf = 0x7fffffff;
const lld llinf = 0x7fffffff7fffffffll;

struct Node {
    int first, second;
    
    bool operator<(const Node &tmp) const
    {
        if (first != tmp.first) return first < tmp.first;
        else return second < tmp.second;
    };
    Node(int first, int second):first(first), second(second){};
    Node(){};
}node[N];
int a[N], dp[N];
pair<int, int> p[N];
int vis[N], idVis;
int buf[N][N];

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int n;
    cin >> n;
    for (int i = 0; i < N; ++i) {
        p[i].first = p[i].second = -1;
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (p[a[i]].first == -1) {
            p[a[i]].first = i;
            p[a[i]].second = i;
        }
        else {
            p[a[i]].second = i;
        }
    }
    for (int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        int sum = 0;
        for (int j = i; j <= n; ++j) {
            if (!vis[a[j]]) {
                vis[a[j]] = 1;
                sum ^= a[j];
            }
            buf[i][j] = sum;
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1];
        if (p[a[i]].second == i) { // i是数字a[i]的最右边
            int cur = i;
            pair<int, int> range = p[a[i]];
            while (cur > 0) {
                if (p[a[cur]].second > range.second) {
                    break;
                }
                range.first = min(range.first, p[a[cur]].first);
                if (cur == range.first) {
                    dp[i] = max(dp[i], dp[range.first - 1] + buf[range.first][range.second]);
                }
                --cur;
            }
        }
    }
    
    cout << dp[n] << endl;
    
    return 0;
}
