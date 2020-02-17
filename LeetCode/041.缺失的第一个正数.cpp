﻿#include "header.h"

/*

给定一个未排序的整数数组，找出其中没有出现的最小的正整数。

示例 1:
输入: [1,2,0]
输出: 3

示例 2:
输入: [3,4,-1,1]
输出: 2

示例 3:
输入: [7,8,9,11,12]
输出: 1

说明:
你的算法的时间复杂度应为O(n)，并且只能使用常数级别的空间。

*/

class Solution {
public:
	int firstMissingPositive(int A[], int n)
	{
		for (int i = 0; i < n; ++i)
		{
			while (A[i] > 0 && A[i] <= n && A[i] != A[A[i] - 1])
				swap(A[i], A[A[i] - 1]);
		}
		for (int i = 0; i < n; ++i)
		{
			if (A[i] != i + 1)
				return i + 1;
		}
		return n + 1;
	}
};
//如果A[i]的值属于[1,n]，则将其值放在对应的A[i]-1下标中，这样可以形成一个简易桶排序，值与下标不对应的，则是最小的未出现正数。
