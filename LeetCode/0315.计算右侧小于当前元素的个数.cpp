#include "header.h"

/*

315. 计算右侧小于当前元素的个数

给你一个整数数组 nums ，按要求返回一个新数组 counts
数组 counts 有该性质： counts[i] 的值是  nums[i] 右侧小于 nums[i] 的元素的数量

示例 1：
输入：nums = [5,2,6,1]
输出：[2,1,1,0]
解释：
5 的右侧有 2 个更小的元素 (2 和 1)
2 的右侧仅有 1 个更小的元素 (1)
6 的右侧有 1 个更小的元素 (1)
1 的右侧有 0 个更小的元素

示例 2：
输入：nums = [-1]
输出：[0]

示例 3：
输入：nums = [-1,-1]
输出：[0,0]

提示：
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4

*/

// 构造索引数组归并排序
class Solution {
public:
	vector<int> countSmaller(vector<int> &nums) {
		int len = nums.size();
		// 构造一个专用于归并的数组indexes，该数组中存放的是原数组的索引
		// 可以理解为当作哈希表中的key，根据值大小对key进行排序
		vector<int> indexes(len);
		vector<int> count(len);
		for (int i = 0; i < len; ++i) indexes[i] = i;
		mergeSort(indexes, 0, len - 1, count, nums);
		return count;
	}
	void mergeSort(vector<int> &indexes, int lo, int hi, vector<int> &count,
		vector<int> &nums) {
		if (lo == hi) return;
		int mi = lo + (hi - lo) / 2;
		mergeSort(indexes, lo, mi, count, nums);
		mergeSort(indexes, mi + 1, hi, count, nums);
		if (nums[indexes[mi]] <= nums[indexes[mi + 1]]) return;
		merge(indexes, lo, hi, mi, count, nums);
	}
	void merge(vector<int> &indexes, int lo, int hi, int mi, vector<int> &count,
		vector<int> &nums) {
		int j = mi + 1;
		for (int i = lo; i <= mi; ++i) {
			while (j <= hi && nums[indexes[i]] > nums[indexes[j]]) ++j;
			count[indexes[i]] += j - (mi + 1);
		}
		inplace_merge(indexes.begin() + lo, indexes.begin() + mi + 1,
			indexes.begin() + hi + 1,
			[&](int a, int b) { return nums[a] < nums[b]; });
	}
};
// https://leetcode.cn/problems/count-of-smaller-numbers-after-self/solutions/9082/gui-bing-pai-xu-suo-yin-shu-zu-python-dai-ma-java-/
// @author https://leetcode.cn/u/liweiwei1419/


// 构造线段树
struct Node {
	Node *left;
	Node *right;
	int val;
	int add;
	Node() : left(nullptr), right(nullptr), val(0), add(0) {}
};

class Solution1 {
public:
	vector<int> countSmaller(vector<int> &nums) {
		int len = nums.size();
		vector<int> count(len);
		int minNum = nums[0], maxNum = nums[0];
		for (int i = 1; i < len; ++i) {
			minNum = min(minNum, nums[i]);
			maxNum = max(maxNum, nums[i]);
		}
		Node *root = new Node();
		for (int i = len - 1; i >= 0; --i) {
			int cur = nums[i] - 1;
			count[i] = cur >= minNum ? query(root, minNum, maxNum, minNum, cur) : 0;
			update(root, minNum, maxNum, nums[i], nums[i], 1);
		}
		return count;
	}

private:
	void pushUp(Node *node) { node->val = node->left->val + node->right->val; }

	void pushDown(Node *node, int leftNum, int rightNum) {
		if (!node->left) node->left = new Node();
		if (!node->right) node->right = new Node();
		if (node->add == 0) return;
		node->left->val += node->add * leftNum;
		node->right->val += node->add * rightNum;
		node->left->add += node->add;
		node->right->add += node->add;
		node->add = 0;
	}

	void update(Node *node, int start, int end, int l, int r, int val) {
		if (l <= start && r >= end) {
			node->val += val * (end - start + 1);
			node->add += val;
			return;
		}
		int mi = start + (end - start) / 2;
		pushDown(node, mi - start + 1, end - mi);
		if (l <= mi) update(node->left, start, mi, l, r, val);
		if (r > mi) update(node->right, mi + 1, end, l, r, val);
		pushUp(node);
	}

	int query(Node *node, int start, int end, int l, int r) {
		if (l <= start && end <= r) return node->val;
		int mi = start + (end - start) / 2, ans = 0;
		pushDown(node, mi - start + 1, end - mi);
		if (l <= mi) ans = query(node->left, start, mi, l, r);
		if (r > mi) ans += query(node->right, mi + 1, end, l, r);
		return ans;
	}
};

// https://leetcode.cn/problems/my-calendar-i/solutions/1646079/by-lfool-xvpv/
// @author https://leetcode.cn/u/lfool/
// https://leetcode.cn/problems/count-of-smaller-numbers-after-self/solutions/127636/c-xian-duan-shu-jie-fa-by-dufre/
// @author https://leetcode.cn/u/dufre/


// 构造线段树，单点更新
class Solution2 {
public:
	void update(Node *node, int start, int end, int idx, int val) {
		if (start == end) {
			node->val += val;
			return;
		}
		int mi = start + (end - start) / 2;
		if (!node->left) node->left = new Node();
		if (!node->right) node->right = new Node();
		if (idx <= mi) update(node->left, start, mi, idx, val);
		else update(node->right, mi + 1, end, idx, val);
		node->val = node->left->val + node->right->val;
	}
	int query(Node *node, int start, int end, int l, int r) {
		if (!node) return 0;
		if (l <= start && r >= end) return node->val;
		int mi = start + (end - start) / 2, ans = 0;
		if (l <= mi) ans += query(node->left, start, mi, l, r);
		if (r > mi) ans += query(node->right, mi + 1, end, l, r);
		return ans;
	}
	vector<int> countSmaller(vector<int> &nums) {
		int len = nums.size();
		vector<int> count(len);
		int minNum = nums[0], maxNum = nums[0];
		for (int i = 1; i < len; ++i) {
			minNum = min(minNum, nums[i]);
			maxNum = max(maxNum, nums[i]);
		}
		Node *root = new Node();
		for (int i = len - 1; i >= 0; --i) {
			int cur = nums[i] - 1;
			count[i] = cur >= minNum ? query(root, minNum, maxNum, minNum, cur) : 0;
			update(root, minNum, maxNum, nums[i], 1);
		}
		return count;
	}
};

