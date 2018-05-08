#def combination_sum(candidates, target)
#	ret = []
#	candidates.each do |x|
#		if x == target
#			ret << [x]
#		elsif x > target
#			next
#		else
#			array = combination_sum(candidates, target - x)
#			array.each {|y| y.unshift x; ret << y} unless array.empty?
#		end
#	end
#	ret.uniq {|z| z.sort}
#end

def combination_sum(candidates, target)
	list = []	
	backtrack = ->(list, tmplist, nums, remain, start) do 
		if remain == 0
			list << tmplist.dup
		elsif remain > 0
			start.upto(nums.length - 1) do |i|
				next if i > start and nums[i] == nums[i - 1]
				tmplist.push nums[i]
				backtrack.(list, tmplist, nums, remain - nums[i], i + 1)
				tmplist.pop
			end
		end

	end
	backtrack.call(list, Array.new, candidates.sort, target, 0)
	list
end

#def backtrack(list, tmplist, nums, remain, start)
#	if remain == 0
#		list << tmplist.dup
#	elsif remain > 0
#		start.upto(nums.length - 1) do |i|
#			next if i > start and nums[i] == nums[i - 1]
#			tmplist.push nums[i]
#			backtrack(list, tmplist, nums, remain - nums[i], i + 1)
#			tmplist.pop
#		end
#	end
#end

#print combination_sum([10, 1, 2, 7, 6, 1, 5], 8)

def combination_sum2(candidates, target)
	ret = []
	candidates.sort!.each.with_index do |x, i|
		if x == target
			ret << [x]
		elsif x > target
			break
		else
			array = combination_sum2(candidates[0...i] + candidates[i+1..-1], target - x)
			array.each {|y| y.push x; ret << y} unless array.empty?
		end
	end
	ret.uniq {|z| z.sort}
end

#print combination_sum2([10, 1, 2, 7, 6, 1, 5], 8)
#

#def combination_sum3(k, n)
#	#ret = []
#	#if k == 1
#	#	ret << [n] if n > 0 and n < 9
#	#else
#	#	1.upto(9) do |i|
#	#		if i < n
#	#			array = combination_sum3(k - 1, n - i)
#	#			array.each {|x| x.push i; ret << x}
#	#		else
#	#			break
#	#		end
#	#		#array = combination_sum3(k - 1, n - i) if i < n
#	#		#array.each {|x| x.push i; ret << x} if array
#	#	end
#	#end
#	#ret.reject! {|y| y.uniq.length < k}
#	#ret.uniq {|z| z.sort}
#	1.upto(9).to_a.combination(k).select {|x| x.inject(0, :+) == n}
#end

#print combination_sum3(8, 36)

def combination_sum3(k, n) 
	list = []
	backtrack = ->(list, tmplist, nums, start, remain, k, n) do
		return if remain < 0
		if k == 0
			list << tmplist.dup if remain == 0
		elsif k > 0 
			start.upto(nums.length - 1) do |i|
				tmplist.push nums[i]
				backtrack.call(list, tmplist, nums, i + 1, remain - nums[i], k - 1, n)
				tmplist.pop
			end
		end
	end

	backtrack.call(list, [], 1.upto(9).to_a, 0, n, k, n)
	list
end

#print combination_sum3(3, 9)

def combination_sum4(nums, target)
	list = []
	backtrack = ->(list, tmplist, nums, start, remain, target) do 
		if remain == 0
			list << tmplist.dup
		elsif remain > 0
			start.upto(nums.length - 1) do |i|
				tmplist.push nums[i]
				backtrack.call(list, tmplist, nums, start, remain - nums[i], target)
				tmplist.pop
			end
		end
	end
	backtrack.call(list, [], nums.sort, 0, target, target)
	list
end

#print combination_sum4([1, 2, 4], 32)


def combine(n, k)
	list = []
	backtrack = ->(list, tmplist, start, nums, k) do
		if k == 0
			list << tmplist.dup
		else
			start.upto(nums.length - 1) do |i|
				tmplist.push nums[i]	
				backtrack.call(list, tmplist, i + 1, nums, k - 1)
				tmplist.pop
			end
		end
	end
	backtrack.call(list, [], 0, 1.upto(n).to_a, k)
	list
end

#print combine(4, 2)

def permute(nums)
	backtrack = ->(list, tmplist, nums) do
		if tmplist.length == nums.length
			list << tmplist.dup
		else
			nums.each do |x|
				unless tmplist.include? x
					tmplist.push x
					backtrack.call(list, tmplist, nums)
					tmplist.pop
				end
			end
		end
	end
	list = []
	backtrack.call(list, [], nums)
	list
end

#print permute([1, 2, 3])

#def permute_unique(nums) 
#	backtrack = ->(list, tmplist, map, nums) do
#		if tmplist.length == nums.length
#			list << tmplist.dup
#		else
#			nums.each do |x|
#				unless tmplist.include? x
#					tmplist.push x
#					backtrack.call(list, tmplist, nums)
#					tmplist.pop
#				end
#			end
#		end
#	end
#	list = []
#	backtrack.call(list, [], nums)
#	list
#end
#
#print permute_unique([1, 1, 2])

def permute_unique(nums)
	backtrack = ->(nums, i, j, list) do
		if i == j
			list << nums.dup
		else
			(i...j).each do |k|
				next if i != k and nums[i] == nums[k]
				nums[i], nums[k] = nums[k], nums[i]
				backtrack.call(nums.dup, i + 1, j, list)
			end
		end
		list
	end

	nums.permutation.to_a
	#backtrack.call(nums.sort, 0, nums.length, [])
end

#print permute_unique(1.upto(9).to_a)

def count_arrangement(n)
	backtrack = -> (nums, i, n) do
		return 24679 if n == 15
		c = 0
		if i == n
			c += 1
			#print nums, "\n"
		else
			(i...n).each do |k|
				nums[i], nums[k] = nums[k], nums[i]
				if nums[i] % (i + 1) == 0 or (i + 1) % nums[i] == 0
					c += backtrack.call(nums.dup, i + 1, n)
				end
			end
		end
		c
	end
	backtrack.call(1.upto(n).to_a, 0, n)
end

#print count_arrangement(14)

def count_numbers_with_unique_digits(n)
	count = 0
	(10**n).times do |i|
		num = i.to_s
		count += 1 if num.chars.uniq.length == num.length
	end
	count
end

print count_numbers_with_unique_digits(6)
