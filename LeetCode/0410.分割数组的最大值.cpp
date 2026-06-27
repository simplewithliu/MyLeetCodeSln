#include "header.h"

/*

410. 分割数组的最大值

给定一个非负整数数组 nums 和一个整数 k ，你需要将这个数组分成 k 个非空的连续子数组，使得这 k 个子数组各自和的最大值 最小。
返回分割后最小的和的最大值。
子数组 是数组中连续的部分。

示例 1：
输入：nums = [7,2,5,10,8], k = 2
输出：18
解释：
一共有四种方法将 nums 分割为 2 个子数组。
其中最好的方式是将其分为 [7,2,5] 和 [10,8] 。
因为此时这两个子数组各自的和的最大值为18，在所有情况中最小。

示例 2：
输入：nums = [1,2,3,4,5], k = 2
输出：9

示例 3：
输入：nums = [1,4,4], k = 3
输出：4

提示：
1 <= nums.length <= 1000
0 <= nums[i] <= 10^6
1 <= k <= min(50, nums.length)

*/

// 备忘录
class Solution {
public:
	int splitArray(vector<int> &nums, int k) {
		int len = nums.size();
		vector<vector<long long>> memo(len + 1, vector<long long>(k + 1, -1));
		vector<long long> preSum(len + 1, 0);
		for (int i = 1; i <= len; ++i) {
			preSum[i] = preSum[i - 1] + nums[i - 1];
		}
		return helper(len, k, preSum, memo);
	}

private:
	int helper(int i, int j, vector<long long> &preSum,
		vector<vector<long long>> &memo) {
		if (memo[i][j] != -1) return memo[i][j];
		if (j == 0) return i > 0 ? INT_MAX : 0;
		int minSum = INT_MAX;
		for (int k = j - 1; k < i; ++k) {
			int cur = max(helper(k, j - 1, preSum, memo),
				(int)(preSum[i] - preSum[k]));
			minSum = min(minSum, cur);
		}
		return memo[i][j] = minSum;
	}
};
// https://leetcode.cn/problems/split-array-largest-sum/solutions/345417/fen-ge-shu-zu-de-zui-da-zhi-by-leetcode-solution/
// @author https://leetcode.cn/u/leetcode-solution/



// 动态规划
class Solution1 {
public:
	int splitArray(vector<int> &nums, int k) {
		int len = nums.size();
		vector<vector<long long>> dp(len + 1,
			vector<long long>(k + 1, LLONG_MAX));

		vector<long long> preSum(len + 1, 0);
		for (int i = 1; i <= len; ++i) {
			preSum[i] = preSum[i - 1] + nums[i - 1];
		}

		dp[0][0] = 0;
		for (int i = 1; i <= len; ++i) {
			for (int j = 1; j <= k; ++j) {
				for (int p = j - 1; p < i; ++p) {
					dp[i][j] =
						min(dp[i][j], max(dp[p][j - 1], preSum[i] - preSum[p]));
				}
			}
		}
		return dp[len][k];
	}
};


// 二分查找
class Solution2 {
public:
	int splitArray(vector<int> &nums, int k) {
		int lo = *max_element(nums.begin(), nums.end());
		int hi = accumulate(nums.begin(), nums.end(), 0);
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			check(mi, nums, k) ? hi = mi : lo = mi + 1;
		}
		return lo;
	}
	bool check(int tar, vector<int> &nums, int k) {
		int cnt = 1, s = 0;
		for (int n : nums) {
			if (s + n <= tar) {
				s += n;
				continue;
			}
			if (cnt == k) return false;
			++cnt;
			s = n;
		}
		return true;
	}
};
// https://leetcode.cn/problems/split-array-largest-sum/solutions/2613046/er-fen-da-an-fu-ti-dan-pythonjavacgojsru-n5la/
// @author https://leetcode.cn/u/endlesscheng/
// https://leetcode.cn/problems/split-array-largest-sum/solutions/242909/er-fen-cha-zhao-by-liweiwei1419-4/
// @authors https://leetcode.cn/u/liweiwei1419/

