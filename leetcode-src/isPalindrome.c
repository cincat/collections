#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
bool isPalindrome(int x) {
	const int N = 8;
	if(x < 0) return false;
	char *t = (char*)calloc(sizeof(int) * N, sizeof(char));
	char *p = t;
	while(x) {
		*(p++) = x % 10 + '0';
		x = x / 10;
	}
	p--;
	while(*p == *t) {
		p--; t++;
	}
	return t >= p ? true : false;
	if(x < 0) return false;
	long t = 0, y = x;
	while(x) {
		t = t * 10 + x % 10;
		x = x / 10;
	}
	return t == y;
}
*/


struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode *reverseList(struct ListNode *head) {
	struct ListNode *p = head, *t = head, * q = head;
	if(head == NULL) return NULL;
	t = p->next;
	while(t) {
		q = t->next;
		t->next = p;
		p = t;
		t = q;
	}
	head->next = NULL;
	return p;
}

bool isPalindrome(struct ListNode *head) {
	if(head == NULL || head->next == NULL) 
		return true;
	struct ListNode *slow = head, *fast = head;
	while(fast->next && fast->next->next) {
		slow = slow->next; fast = fast->next->next;
	}
	slow->next = reverseList(slow->next);
	slow = slow->next;

	while(slow && head) {
		if(slow->val != head->val)
			return false;
		slow = slow->next;
		head = head->next;
	}
	return true;
}



int main() {
		return 0;
}
