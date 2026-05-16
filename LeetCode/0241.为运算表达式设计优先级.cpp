#include "header.h"

/*

241. 为运算表达式设计优先级

给你一个由数字和运算符组成的字符串 expression ，按不同优先级组合数字和运算符，计算并返回所有可能组合的结果。你可以 按任意顺序 返回答案
生成的测试用例满足其对应输出值符合 32 位整数范围，不同结果的数量不超过 10^4

示例 1：
输入：expression = "2-1-1"
输出：[0,2]
解释：
((2-1)-1) = 0 
(2-(1-1)) = 2

示例 2：
输入：expression = "2*3-4*5"
输出：[-34,-14,-10,-10,10]
解释：
(2*(3-(4*5))) = -34 
((2*3)-(4*5)) = -14 
((2*(3-4))*5) = -10 
(2*((3-4)*5)) = -10 
(((2*3)-4)*5) = 10

提示：
1 <= expression.length <= 20
expression 由数字和算符 '+'、'-' 和 '*' 组成。
输入表达式中的所有整数值在范围 [0, 99] 
输入表达式中的所有整数都没有前导 '-' 或 '+' 表示符号。

*/

// 备忘录
class Solution {
public:
	vector<int> diffWaysToCompute(string expression) {
		unordered_map<string, vector<int>> memo;
		return helper(expression, memo);
	}
private:
	vector<int> helper(string input, unordered_map<string, vector<int>> &memo) {
		if (memo.count(input)) return memo[input];
		vector<int> res;
		int len = input.size();
		for (int i = 0; i < len; ++i) {
			if (input[i] == '+' || input[i] == '-' || input[i] == '*') {
				vector<int> left = helper(input.substr(0, i), memo);
				vector<int> right = helper(input.substr(i + 1), memo);
				for (auto l : left) {
					for (auto r : right) {
						switch (input[i])
						{
						case '+':res.push_back(l + r); break;
						case '-':res.push_back(l - r); break;
						case '*':res.push_back(l * r); break;
						default: break;
						}
					}
				}
			}
		}
		if (res.empty()) res.push_back(stoi(input));
		return memo[input] = res;
	}
};

// 自底而上的动态规划
class Solution1 {
public:
	vector<int> diffWaysToCompute(string expression) {
		vector<int> nums;
		vector<char> ops;
		int num = 0;
		char op = 0;
		istringstream ss(expression + "+");
		while (ss >> num&&ss >> op) {
			nums.push_back(num);
			ops.push_back(op);
		}
		int len = nums.size();
		vector<vector<vector<int>>> dp(len, vector<vector<int>>(len, vector<int>()));
		for (int i = 0; i < len; ++i) dp[i][i].push_back(nums[i]);
		for (int i = 1; i < len; ++i) {
			for (int j = i - 1; j >= 0; --j) {
				for (int k = j; k < i; ++k) {
					for (auto l : dp[j][k]) {
						for (auto r : dp[k + 1][i]) {
							switch (ops[k])
							{
							case '+':dp[j][i].push_back(l + r); break;
							case '-':dp[j][i].push_back(l - r); break;
							case '*':dp[j][i].push_back(l * r); break;
							default: break;
							}
						}
					}
				}
			}
		}
		return dp[0][len - 1];
	}
};

/*
 * https://leetcode.cn/problems/different-ways-to-add-parentheses/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-5-5/
 * @author https://leetcode.cn/u/windliang/
 */


// 分治法
class Solution2 {
public:
	vector<int> diffWaysToCompute(string expression) {
		vector<int> res;
		int len = expression.size();
		if (len <= 2) return{ stoi(expression) };
		for (int i = 0; i < len; ++i) {
			int c = expression[i];
			if (c == '+' || c == '-' || c == '*') {
				vector<int> left = diffWaysToCompute(expression.substr(0, i));
				vector<int> right = diffWaysToCompute(expression.substr(i + 1));
				for (int l : left) {
					for (int r : right) {
						switch (c) {
						case '+':
							res.push_back(l + r);
							break;
						case '-':
							res.push_back(l - r);
							break;
						case '*':
							res.push_back(l * r);
							break;
						}
					}
				}
			}
		}
		return res;
	}
};

