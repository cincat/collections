def remove_nth_from_end(head, n)
	start = ListNode.new(0)
	slow, fast = start, head
	slow.next = head
	n.times {fast = fast.next}
	(slow = slow.next; fast = fast.next) while fast
	slow.next = slow.next.next
	start.next
end
