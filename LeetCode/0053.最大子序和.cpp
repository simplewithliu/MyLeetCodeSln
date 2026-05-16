#include "header.h"

/*

53. 最大子数组和

给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和
子数组是数组中的一个连续部分

示例 1：
输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6

示例 2：
输入：nums = [1]
输出：1

示例 3：
输入：nums = [5,4,-1,7,8]
输出：23

提示：
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4

进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解

*/

// O(n)时间复杂度
class Solution {
public:
	int maxSubArray(vector<int> &nums)
	{
		if (nums.empty()) return 0;
		int maxNum = INT_MIN;
		int len = nums.size();
		int temp = 0;
		for (int i = 0; i < len; ++i)
		{
			temp += nums[i];
			maxNum = max(temp, maxNum);
			if (temp < 0) temp = 0;
		}
		return maxNum;
	}
};

// 分治法 
class Solution1 {
public:
	int maxSubArray(vector<int> &nums) {
		int len = nums.size();
		return maxsub(nums, 0, len - 1);
	}
	int maxsub(vector<int> &nums, int lo, int hi) {
		if (lo == hi) return nums[lo];
		int mi = lo + (hi - lo) / 2;
		int leftsum = maxsub(nums, lo, mi);
		int rightsum = maxsub(nums, mi + 1, hi);
		int leftbordersum = 0, maxleftbordersum = nums[mi];
		for (int i = mi; i >= lo; --i) {
			leftbordersum += nums[i];
			maxleftbordersum = max(maxleftbordersum, leftbordersum);
		}
		int rightboardsum = 0, maxrightbordersum = nums[mi + 1];
		for (int i = mi + 1; i <= hi; ++i) {
			rightboardsum += nums[i];
			maxrightbordersum = max(maxrightbordersum, rightboardsum);
		}
		int ans =
			max(max(leftsum, rightsum), maxleftbordersum + maxrightbordersum);
		return ans;
	}
};


// 另一个分治，方法有些奇怪
struct res
{
	int l, r, m, s;
	res(int lMax, int rMax, int maxNum, int sum)
		:l(lMax), r(rMax), m(maxNum), s(sum) {}
};
class Solution2 {
public:
	int maxSubArray(vector<int> &nums)
	{
		if (nums.empty()) return 0;
		int len = nums.size();
		res obj = findMax(nums, 0, len);
		return obj.m;
	}
	res findMax(vector<int> &nums, int lo, int hi)
	{
		if (hi - lo < 2) return res(nums[lo], nums[lo], nums[lo], nums[lo]);
		int mi = (lo + hi) >> 1;
		res lhs = findMax(nums, lo, mi), rhs = findMax(nums, mi, hi);
		int l, r, m, s;
		l = max(lhs.l, lhs.s + rhs.l);
		r = max(rhs.r, lhs.r + rhs.s);
		m = max(lhs.r + rhs.l, max(lhs.m, rhs.m));
		s = lhs.s + rhs.s;
		return res(l, r, m, s);
	}
};
//Thanks for this Solution about divide and conquer approach.
//https://leetcode.com/problems/maximum-subarray/discuss/20200/Share-my-solutions-both-greedy-and-divide-and-conquer


