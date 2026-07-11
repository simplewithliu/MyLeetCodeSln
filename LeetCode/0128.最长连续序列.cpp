#include "header.h"

/*

128. 最长连续序列

给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

示例 1：
输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4

示例 2：
输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9

示例 3：
输入：nums = [1,0,1,2]
输出：3

提示：

0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

*/


class Solution {
public:
	int longestConsecutive(vector<int> &nums) {
		unordered_set<int> s(nums.begin(), nums.end());
		int ans = 0;
		for (int n : s) {
			if (s.count(n - 1)) continue;
			int next = n + 1;
			while (s.count(next)) ++next;
			ans = max(ans, next - n);
			if (ans * 2 >= s.size()) break;
		}
		return ans;
	}
};
// https://leetcode.cn/problems/longest-consecutive-sequence/solutions/3005726/ha-xi-biao-on-zuo-fa-pythonjavacgojsrust-whop/
// @author https://leetcode.cn/u/endlesscheng/


// 并查集
class UF {
private:
	vector<int> id;
	vector<int> size;

public:
	UF(int len) {
		for (int i = 0; i < len; ++i) {
			id.push_back(i);
			size.push_back(1);
		}
	}
	int find(int x) {
		if (id[x] != x) id[x] = find(id[x]);
		return id[x];
	}
	void unionpq(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot == qRoot) return;
		id[pRoot] = qRoot;
		size[qRoot] += size[pRoot];
	}
	int getMax() {
		int ans = 0;
		for (int i = 0; i < id.size(); ++i) {
			if (i == id[i]) ans = max(ans, size[i]);
		}
		return ans;
	}
};

class Solution1 {
public:
	int longestConsecutive(vector<int> &nums) {
		int len = nums.size();
		unordered_map<int, int> m;
		UF uf(len);
		for (int i = 0; i < len; ++i) {
			if (m.count(nums[i])) continue;
			if (m.count(nums[i] - 1)) uf.unionpq(i, m[nums[i] - 1]);
			if (m.count(nums[i] + 1)) uf.unionpq(i, m[nums[i] + 1]);
			m[nums[i]] = i;
		}
		return uf.getMax();
	}
};



// 使用m记录边界的连续长度，比如连续数字1、2、3、4、5，则m[1]和m[5]的值都为5
class Solution2 {
public:
	int longestConsecutive(vector<int> &nums)
	{
		int len = nums.size();
		if (len <= 1) return len;
		int res = 0;
		unordered_map<int, int> m;
		for (auto n : nums)
		{
			if (!m.count(n))
			{
				int left = m.count(n - 1) ? m[n - 1] : 0;
				int right = m.count(n + 1) ? m[n + 1] : 0;
				m[n] = left + right + 1;
				res = max(res, m[n]);
				m[n - left] = m[n];
				m[n + right] = m[n];
			}
			else
			{
				continue;
			}
		}
		return res;
	}
};
