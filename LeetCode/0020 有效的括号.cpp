﻿#include "header.h"

/*

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：
左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。

示例 1：
输入：s = "()"
输出：true

示例 2：
输入：s = "()[]{}"
输出：true

示例 3：
输入：s = "(]"
输出：false

示例 4：
输入：s = "([)]"
输出：false

示例 5：
输入：s = "{[]}"
输出：true

提示：
1 <= s.length <= 10^4
s 仅由括号 '()[]{}' 组成

*/

class Solution {
public:
	bool isValid(string s) {
		stack<char> sta;
		for (auto c : s) {
			switch (c)
			{
			case '(':
				sta.push(')');
				break;
			case '{':
				sta.push('}');
				break;
			case '[':
				sta.push(']');
				break;
			default:
				if (sta.empty() || sta.top() != c) return false;
				else sta.pop();
				break;
			}
		}
		return sta.empty();
	}
};