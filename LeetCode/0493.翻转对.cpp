#include "header.h"

/*

493. 翻转对

给定一个数组 nums, 如果 i < j 且 nums[i] > 2 * nums[j], 我们就将 (i, j) 称作一个重要翻转对
你需要返回给定数组中的重要翻转对的数量

示例 1:
输入: [1,3,2,3,1]
输出: 2

示例 2:
输入: [2,4,3,5,1]
输出: 3

注意:
给定数组的长度不会超过50000
输入数组中的所有数字都在32位整数的表示范围内

*/

class Solution {
public:
	vector<int> temp;
	int count = 0;
	int reversePairs(vector<int> &nums) {
		int len = nums.size();
		temp.resize(len);
		mergeSort(nums, 0, len - 1);
		return count;
	}
	void mergeSort(vector<int> &nums, int lo, int hi) {
		if (lo == hi) return;
		int mi = lo + (hi - lo) / 2;
		mergeSort(nums, lo, mi);
		mergeSort(nums, mi + 1, hi);
		merge(nums, lo, mi, hi);
	}
	void merge(vector<int> &nums, int lo, int mi, int hi) {
		for (int i = lo; i <= hi; ++i) temp[i] = nums[i];
		int i = lo, j = mi + 1, k = lo;
		while (i <= mi && j <= hi) {
			if (nums[i] / 2.0 > nums[j]) {
				count += mi + 1 - i;
				++j;
			} else {
				++i;
			}
		}
		i = lo, j = mi + 1;
		while (i <= mi && j <= hi) {
			if (temp[i] <= nums[j]) nums[k++] = temp[i++];
			else nums[k++] = nums[j++];
		}
		while (i <= mi) nums[k++] = temp[i++];
	}
};


