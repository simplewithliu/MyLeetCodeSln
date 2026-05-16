#include "header.h"

/*

95. 不同的二叉搜索树 II

给你一个整数 n ，请你生成并返回所有由 n 个节点组成且节点值从 1 到 n 互不相同的不同 二叉搜索树
可以按 任意顺序 返回答案

示例 1：
输入：n = 3
输出：[[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]

示例 2：
输入：n = 1
输出：[[1]]

提示：
1 <= n <= 8

*/

class Solution {
public:
	vector<TreeNode *> generateTrees(int n)
	{
		return generate(1, n);
	}
	vector<TreeNode *> generate(int start, int end)
	{
		vector<TreeNode *> vec;
		if (start > end)
		{
			vec.push_back(nullptr);
			return vec;
		}
		for (int i = start; i <= end; ++i)
		{
			vector<TreeNode *> left = generate(start, i - 1);
			vector<TreeNode *> right = generate(i + 1, end);
			for (auto lNode : left)
				for (auto rNode : right)
				{
					TreeNode *root = new TreeNode(i);
					root->left = lNode;
					root->right = rNode;
					vec.push_back(root);
				}
		}
		return vec;
	}
};

// 分治法
map<pair<int, int>, vector<TreeNode *>> m;
class Solution1 {
public:
	vector<TreeNode *> generateTrees(int n) { return generate(1, n); }
	vector<TreeNode *> generate(int lo, int hi) {
		vector<TreeNode *> ans;
		if (lo > hi) {
			ans.push_back(nullptr);
			return ans;
		}
		if (m.count({ lo, hi })) return m[{lo, hi}];
		for (int i = lo; i <= hi; ++i) {
			vector<TreeNode *> left = generate(lo, i - 1);
			vector<TreeNode *> right = generate(i + 1, hi);
			for (TreeNode *l : left) {
				for (TreeNode *r : right) {
					TreeNode *root = new TreeNode(i);
					root->left = l;
					root->right = r;
					ans.push_back(root);
				}
			}
		}
		return m[{lo, hi}] = ans;
	}
};


// 动态规划(技巧性)
// https://leetcode.wang/leetCode-95-Unique-Binary-Search-TreesII.html
class Solution2 {
public:
	vector<TreeNode *> generateTrees(int n)
	{
		if (n == 0) return {};
		vector<vector<TreeNode *>> dp(n + 1);
		dp[0].push_back(nullptr);
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= i; ++j)
			{
				int leftNum = j - 1, rightNum = i - j;
				for (TreeNode *lt : dp[leftNum])
					for (TreeNode *rt : dp[rightNum])
					{
						TreeNode *root = new TreeNode(j);
						root->left = lt; // 小技巧，复用左子树指针
						root->right = clone(rt, j);
						dp[i].push_back(root);
					}
			}
		}
		return dp[n];
	}
	TreeNode * clone(TreeNode *node, int offset)
	{
		if (!node) return nullptr;
		TreeNode *root = new TreeNode(node->val + offset);
		root->left = clone(node->left, offset);
		root->right = clone(node->right, offset);
		return root;
	}
};

