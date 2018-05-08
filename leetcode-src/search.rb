def search (nums, target)
	nums.each.with_index {|x, i| return true if target == x}
	false	
end

def find_min (nums)
	l, h, m = 0, nums.length - 1, 0
	while l < h
		return nums[l] if nums[l] < nums[h]
		m = (l + h) / 2
		nums[m] >= nums[l] ?
			l = m + 1 : h = m
	end
	nums[l]
end

def search_range (nums, target)
	i, j, ret = 0, nums.length - 1, [-1, -1]	

	while i < j
		m = (i + j) / 2
		if nums[m] >= target
			j = m	
		else
			i = m + 1	
		end
	end

	return ret if nums[i] != target
	ret[0] = i
	j = nums.length - 1

	while i < j
		m = (i + j) / 2 + 1
		if nums[m] > target
			j = m - 1
		else
			i = m
		end
	end
	ret[1] = j
	ret
end

#print search_range([5, 7, 7, 8, 8, 10], 8)

def search_insert (nums, target)
	i, j, m = 0, nums.length - 1, 0
	while i <= j
		m = (i + j) / 2
		if nums[m] == target then return m
		elsif nums[m] < target then i = m + 1
		else j = m - 1 end
	end
	return i
end

#t search_insert([1], 1)

def count_and_say (n)
	say = "1"
	(n - 1).times do
		asay = ""
		x, count = say[0], 0 
		say.each_char do |c|
			if c == x
				count += 1
			else
				asay << "#{count}#{x}"
				x, count = c, 1
			end
		end
		asay << "#{count}#{x}"
		say = asay
	end
	say
end

#print count_and_say(2)
10.times do |i|
	print i, ": ", count_and_say(i + 1), "\n"
end
