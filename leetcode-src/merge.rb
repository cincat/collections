class ListNode
	attr_accessor :val, :next
	def initialize(val)
		@val = val
		@next = nil
	end
end

def merge_two_lists(l1, l2)
	#point = ListNode.new(0)
	#head = point
	#while l1 and l2
	#	if l1.val < l2.val
	#		point.next = l1
	#		l1 = l1.next
	#	else
	#		point.next = l2
	#		l2 = l2.next
	#	end
	#	point = point.next
	#end
	#point.next = l1 || l2	
	#return head.next
	
	#return l1 || l2 if l1 == nil or l2 == nil
	#if(l1.val < l2.val)
	#	l1.next = merge_two_lists(l1.next, l2)
	#	return l1
	#else
	#	l2.next = merge_two_lists(l1, l2.next)
	#	return l2
	#end
end

def merge_k_lists(lists)
	return nil if lists.compact.empty?
	min, j = 2**31 - 1, 0
	lists.each.with_index do |x, i|
		if x and x.val < min
			min = x.val
			j = i
		end
	end

	head = lists[j]
	lists[j] = lists[j].next if lists[j]
	head.next = merge_k_lists(lists) if head
	head
end

def nth_ugly_number(n)
	ugly = [1]
	i2, i3, i5 = 0, 0, 0
	(n-1).times do
		u2, u3, u5 = ugly[i2] * 2, ugly[i3] * 3, ugly[i5] * 5
		min = [u2, u3, u5].min
		i2 += 1 if u2 == min
		i3 += 1 if u3 == min
		i5 += 1 if u5 == min

		ugly << min
	end
	ugly[n - 1]
end

print nth_ugly_number(7)

#for i in 1..10
#	print nth_ugly_number(i), " "
#end
def isUgly(num)
	(2..5).each {|x| num /= x while num % x == 0} if num > 0
	num == 1
end

#print isUgly(1)
def count_primes(n)
	prime, c = [], 0 
	n.times {prime << true}
	prime.each.with_index do |x, i|
		next if i < 2
		if prime[i] == true
			c += 1
			j = 2
			while i * j < n
				prime[i * j] = false
				j += 1
			end
		end
	end
	c
end

#print count_primes(1500000)
