#include "header.h"

/*

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

示例 1:

输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出: 3
解释: 节点 5 和节点 1 的最近公共祖先是节点 3。
 
示例?2:

输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出: 5
解释: 节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。
 ?
说明:

所有节点的值都是唯一的。
p、q 为不同节点且均存在于给定的二叉树中。

*/

class Solution {
public:
	TreeNode * lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
	{
		if (!root || root == p || root == q) return root;
		TreeNode *left = lowestCommonAncestor(root->left, p, q);
		TreeNode *right = lowestCommonAncestor(root->right, p, q);
		if (left || right)
		{
			if (left&&right)
				return root;
			else
				return left ? left : right;
		}
		else
		{
			return nullptr;
		}
	}
};