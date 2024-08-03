#include "header.h"

/*

600. 不含连续1的非负整数

给定一个正整数 n ，请你统计在 [0, n] 范围的非负整数中，有多少个整数的二进制表示中不存在 连续的 1

示例 1:
输入: n = 5
输出: 5
解释: 
下面列出范围在 [0, 5] 的非负整数与其对应的二进制表示：
0 : 0
1 : 1
2 : 10
3 : 11
4 : 100
5 : 101
其中，只有整数 3 违反规则（有两个连续的 1），其他 5 个满足规则

示例 2:
输入: n = 1
输出: 2

示例 3:
输入: n = 2
输出: 3

提示:
1 <= n <= 10^9

*/


class Solution {
private:
	int len = 0;
	int num = 0;
	vector<vector<int>> memo;

public:
	int findIntegers(int n) {
		len = log2(n);
		num = n;
		memo.resize(len + 1, vector<int>(2));
		return helper(0, 0, true);
	}

private:
	int helper(int i, int pre, bool isLimit) {
		if (i == len + 1) return 1;
		if (!isLimit && memo[i][pre]) return memo[i][pre];
		int up = isLimit ? (num >> (len - i)) & 1 : 1;
		int res = 0;
		for (int cur = 0; cur <= up; ++cur) {
			if (!(pre == 1 && cur == 1)) {
				res += helper(i + 1, cur, isLimit && cur == up);
			}
		}
		return isLimit ? res : memo[i][pre] = res;
		return res;
	}
};
// https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/solutions/1900038/by-lfool-epqy/
// @author https://leetcode.cn/u/lfool/

// 该方法的状态定义不适合打表，无效状态太多，浪费空间
