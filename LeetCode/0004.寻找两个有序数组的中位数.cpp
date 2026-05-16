#include "header.h"

/*

4. 寻找两个正序数组的中位数

给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数
算法的时间复杂度应该为 O(log (m+n))

示例 1：
输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2

示例 2：
输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5

提示：
nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6

*/

class Solution {
public:
	double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
		int len1 = nums1.size(), len2 = nums2.size(), len = len1 + len2;
		if (len1 > len2) return findMedianSortedArrays(nums2, nums1);
		return len & 1 ? findK(nums1, nums2, (len / 2) + 1)
					   : (findK(nums1, nums2, len / 2) +
							findK(nums1, nums2, (len / 2) + 1)) / 2.0;
	}
	int findK(vector<int> &nums1, vector<int> &nums2, int k) {
		int len1 = nums1.size(), len2 = nums2.size();
		int lo = max(0, k - len2), hi = min(k, len1);
		while (lo < hi) {
			// 这里 i 和 j 表示索引, 以中位数为界，i - 1 和 j - 1 即前半部分最后的数（含中位数）
			int i = lo + (hi - lo) / 2;
			int j = k - i;
			// 二分查找法的本质是通过排除错误区间, 然后两边收缩逼近到目标数
			// 目标数的范围是 nums1[i-1] <= nums2[j] 与 nums2[j-1] <= nums1[i], 所以需要排除的区间是 nums1[i-1] > nums2[j] 与 nums2[j-1] > nums1[i]
			// 所以当 lo = i + 1 是收缩左区间, 因此可以排除 nums2[j-1] > nums1[i], 当 hi = i 时收缩右区间可以排除 nums1[i-1] > nums2[j]
			// 这里直接用else表示这种情况, else里同时包含了正确的情况, 所以不断通过对两侧错误区间的排除可以逼近正确的目标数
			nums1[i] < nums2[j - 1] ? lo = i + 1 : hi = i;
		}
		int max1 = lo == 0 ? INT_MIN : nums1[lo - 1];
		int max2 = lo == k ? INT_MIN : nums2[k - lo - 1];
		return max(max1, max2);
	}
};
// https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/jiang-qi-zhuan-wei-zhao-liang-ge-you-xu-shu-zu-de-/

class Solution1 {
public:
	double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
	{
		int len1 = nums1.size(), len2 = nums2.size();
		if (len1 > len2) return findMedianSortedArrays(nums2, nums1);
		int i = 0, j = 0;
		int lo = 0, hi = len1;
		//i + j == len1 - i + len2 - j(len1 + len2为偶数) 或 len1 - i + len2 - j + 1(len1 + len2为奇数)
		//2(i + j) == len1 + len2 或 len1 + len2 + 1，所以 i + j == (len1 + len2 + 1) >> 1
		int half = (len1 + len2 + 1) >> 1;
		while (lo <= hi)
		{
			i = lo + ((hi - lo) >> 1);
			j = half - i;
			if (i > 0 && j < len2 && nums1[i - 1] > nums2[j])
				lo = i - 1;
			else if (j > 0 && i < len1 && nums2[j - 1] > nums1[i])
				hi = i + 1;
			else
			{
				int left = 0, right = 0;
				if (i == 0)
					left = nums2[j - 1];
				else if (j == 0)
					left = nums1[i - 1];
				else
					left = max(nums1[i - 1], nums2[j - 1]);

				//如果长度为奇数，则不用考虑右半部分。
				if ((len1 + len2) & 1) return left;
				//如果长度为偶数，需要考虑右边部分。
				if (i == len1)
					right = nums2[j];
				else if (j == len2)
					right = nums1[i];
				else
					right = min(nums1[i], nums2[j]);
				return (left + right) / 2.0;
			}
		}
		return 0.0;
	}
};

// https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-shu-b/
// https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/he-bing-yi-hou-zhao-gui-bing-guo-cheng-zhong-zhao-/

