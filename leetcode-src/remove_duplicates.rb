class ListNode
	attr_accessor :val, :next
	def initialize(val)
		@val = val
		@next = nil
	end
end

def remove_elements(head, val)
	head = head.next while head and head.val == val
	head.next = remove_elements head.next, val if head
	head
end

def remove_elementsII(head, val) 
	node = ListNode.new(0)
	node.next = head
	head = node
	node.next.val == val ? node.next = node.next.next : node = node.next while node.next
	head.next
end

def move_zeros(nums)
	i = 0
	nums.each {|x| (nums[i] = x; i+= 1) if x != 0}
	nums.fill(0, i...nums.length)
end

def remove_duplicates(nums)
	nums.each_index{|i| nums.delete_at(i+1) while i+1<nums.length and nums[i+1]==nums[i]}
	nums.length
end

def remove_element(nums, val)
	n = 0
	while n < nums.length
		while nums[n] == val
			nums[n], nums[-1] = nums[-1], nums[n] 
			nums.delete_at(nums.length - 1)
		end
		n += 1
	end
	nums.length
end
#print remove_duplicates([])
print remove_element([1,2,2,3], 2)
