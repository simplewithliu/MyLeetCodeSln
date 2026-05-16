#include "header.h"

/*

2642. 设计可以求最短路径的图类

给你一个有 n 个节点的 有向带权 图，节点编号为 0 到 n - 1
图中的初始边用数组 edges 表示，其中 edges[i] = [fromi, toi, edgeCosti] 表示从 fromi 到 toi 有一条代价为 edgeCosti 的边

请你实现一个 Graph 类：
Graph(int n, int[][] edges)
初始化图有 n 个节点，并输入初始边

addEdge(int[] edge)
向边集中添加一条边，其中 edge = [from, to, edgeCost]，数据保证添加这条边之前对应的两个节点之间没有有向边

int shortestPath(int node1, int node2)
返回从节点 node1 到 node2 的路径 最小 代价；如果路径不存在，返回 -1；一条路径的代价是路径中所有边代价之和

示例 1：
输入：
["Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"]
[[4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]], [3, 2], [0, 3], [[1, 3, 4]], [0, 3]]
输出：
[null, 6, -1, null, 6]
解释：
Graph g = new Graph(4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]);
g.shortestPath(3, 2); // 返回 6 。从 3 到 2 的最短路径如第一幅图所示：3 -> 0 -> 1 -> 2 ，总代价为 3 + 2 + 1 = 6
g.shortestPath(0, 3); // 返回 -1 。没有从 0 到 3 的路径
g.addEdge([1, 3, 4]); // 添加一条节点 1 到节点 3 的边，得到第二幅图
g.shortestPath(0, 3); // 返回 6 。从 0 到 3 的最短路径为 0 -> 1 -> 3 ，总代价为 2 + 4 = 6

提示：
1 <= n <= 100
0 <= edges.length <= n * (n - 1)
edges[i].length == edge.length == 3
0 <= fromi, toi, from, to, node1, node2 <= n - 1
1 <= edgeCosti, edgeCost <= 10^6
图中任何时候都不会有重边和自环
调用 addEdge 至多 100 次
调用 shortestPath 至多 100 次

*/

// BFS
class Graph {
public:
	vector<vector<pair<int, int>>> adj;
	Graph(int n, vector<vector<int>> &edges) {
		adj.resize(n);
		for (const auto &e : edges) adj[e[0]].push_back({ e[1], e[2] });
	}

	void addEdge(vector<int> edge) {
		adj[edge[0]].push_back({ edge[1], edge[2] });
	}

	int shortestPath(int node1, int node2) {
		int len = adj.size();
		vector<int> dis(len, INT_MAX);

		vector<char> inQueue(len, false);
		queue<int> q;
		dis[node1] = 0;
		q.push(node1);
		inQueue[node1] = true;

		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			inQueue[cur] = false;
			for (const auto &e : adj[cur]) {
				int next = e.first, w = e.second;
				if (dis[cur] + w < dis[next]) {
					dis[next] = dis[cur] + w;
					if (!inQueue[next]) {
						q.push(next);
						inQueue[next] = true;
					}
				}
			}
		}
		return dis[node2] == INT_MAX ? -1 : dis[node2];
	}
};
/**
* Your Graph object will be instantiated and called as such:
* Graph* obj = new Graph(n, edges);
* obj->addEdge(edge);
* int param_2 = obj->shortestPath(node1,node2);
*/

// 迪杰斯特拉最短路径
class Graph1 {
public:
	using pii = pair<int, int>;
	vector<vector<pii>> adj;
	Graph1(int n, vector<vector<int>> &edges) {
		adj.resize(n);
		for (const auto &e : edges) adj[e[0]].push_back({ e[1], e[2] });
	}

	void addEdge(vector<int> edge) {
		adj[edge[0]].push_back({ edge[1], edge[2] });
	}

	int shortestPath(int node1, int node2) {
		vector<int> dis(adj.size(), INT_MAX);
		dis[node1] = 0;
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		pq.push({ 0, node1 });
		while (!pq.empty()) {
			pii cur = pq.top();
			pq.pop();
			if (cur.second == node2) return cur.first;
			if (cur.first > dis[cur.second]) continue;
			for (const auto &p : adj[cur.second]) {
				if (p.second + cur.first < dis[p.first]) {
					dis[p.first] = p.second + cur.first;
					pq.push({ dis[p.first], p.first });
				}
			}
		}
		return -1;
	}
};
/**
* Your Graph object will be instantiated and called as such:
* Graph* obj = new Graph(n, edges);
* obj->addEdge(edge);
* int param_2 = obj->shortestPath(node1,node2);
*/
