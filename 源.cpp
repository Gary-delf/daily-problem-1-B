#include <stdio.h>
#include <iostream>
#include <vector>  //引入 C++ 标准库中的 vector 容器,vector 是动态数组，可以自动扩容
using namespace std;

vector<int> g[100005];  //定义了一个数组，名叫 g,每个元素是一个 vector<int>（存放整数的动态数组）,
                        //把 g[a] 理解成：节点 a 的所有邻居节点列表，
                        // <int> 表示这个列表中存储的是整数类型的节点编号
int color[100005];  // 0: 未染色, 1: 黑色, -1: 白色
                    //全局变量，自动初始化为 0，表示所有节点初始状态为未染色
long long black = 0, white = 0;

void dfs(int u, int col) {  //最核心的部分
    color[u] = col;
    if (col == 1) black++;
    else white++;

    for (int v : g[u]) {  //意思是对于 g[u] 中的每个元素 v（即 u 的每个邻居节点 v），执行循环体内的代码
        if (!color[v]) {
            dfs(v, -col);  // 递归调用 dfs，染色相反的颜色
        }
    }
}

int main() {
    int n;
    cin>>n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin>>u>>v;
        g[u].push_back(v);  // 将 v 添加到 u 的邻居列表中
        g[v].push_back(u);  // 将 u 添加到 v 的邻居列表中，因为这是无向图
    }

    dfs(1, 1);  // 从节点1开始染色

    long long ans = black * white - (n - 1);  // 黑色节点数乘以白色节点数，任意不相邻且不同颜色的节点的连线均符合题意，
                                              // 等价于从每一个黑点出发，连接所有白点，再减去与其相邻的边数（n-1条边），
                                              // 显然黑点之间不相邻，所有与黑点相邻的边恰好覆盖这棵树的所有边
    cout<<ans;

    return 0;
}