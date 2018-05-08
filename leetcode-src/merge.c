#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct ListNode {
	int val;
	struct ListNode *next;
};

void merge(int *nums1, int m, int *nums2, int n) {
	int i = m - 1, j = n - 1, tail = m + n - 1;
	while(j >= 0)
		nums1[tail--] = nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
}

struct ListNode* mergeKLists(struct ListNode **lists, int listsSize) {
	if(listsSize == 0) return NULL;
	int min = INT_MAX, j = 0;
	for(int i = 0; i < listsSize; i++) {
		if(lists[i] && lists[i]->val < min) {
			min = lists[i]->val;
			j = i;
		}
	}

	struct ListNode *node = lists[j];
	if(lists[j]) {
		lists[j] = lists[j]->next;
		node->next = mergeKLists(lists, listsSize);
	}
	return node;
}

int main() {
	return 0;
}
