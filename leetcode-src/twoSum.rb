def two_sum(nums, target)
	map = {}
	nums.each.with_index {|x, j| map[target - x] = j}
	nums.each.with_index {|x, j| return [map[x], j] if map[x] and j != map[x]}
end

def three_sum(nums)
	three = []
	nums.sort!.each.with_index do |x, i|
		next if !(i == 0 or (i > 0 and nums[i] != nums[i - 1]))
		l, h, sum= i + 1, nums.length - 1, -x
		while l < h
			if nums[l] + nums[h] == sum
				three << [nums[i], nums[l], nums[h]]
				l += 1 while l < h and nums[l + 1] == nums[l]
				h -= 1 while l < h and nums[h - 1] == nums[h]
				l += 1; h -= 1
			elsif nums[l] + nums[h] < sum
				l += 1
			else
				h -= 1
			end
		end
	end
	three
end


def four_sum(nums, target)
	four = []
	nums.sort!.each_index do |i|
		next unless i == 0 or (i > 0 and nums[i] != nums[i - 1])
		nums.each_index do |j|
			next unless j > i and (nums[j] != nums[j - 1] or i + 1 == j)

			sum, l, h = target - (nums[i] + nums[j]), j + 1, nums.length - 1
			while l < h
				if nums[l] + nums[h] == sum
					four << [nums[i], nums[j], nums[l], nums[h]]
					l += 1 while l < h and nums[l] == nums[l + 1]
					h -= 1 while l < h and nums[h] == nums[h - 1]
					l += 1; h -= 1
				elsif nums[l] + nums[h] < sum
					l += 1
				else
					h -= 1
				end
			end
		end
	end
	four
end
#print four_sum([0, 0, 0, 0], 0)

def four_sum_count(a, b, c, d)
	count, map = 0, {}
	c.each {|x| d.each {|y| map[x + y] ? map[x + y] += 1 : map[x + y] = 1}}
	a.each {|x| b.each {|y| count += map[-(x + y)] if map[-(x + y)]}}
	count
end

def three_sum_closest(nums, target)
	ans = nums[0] + nums[1] + nums[2]
	nums.sort!.each_index do |i|
		break if i > nums.length - 3
		l, h = i + 1, nums.length - 1
		while l < h
			sum = nums[i] + nums[l] + nums[h]	
			ans = sum if (target - ans).abs > (target - sum).abs
			sum > target ? h -= 1 : l += 1
		end
	end
	ans
end

print four_sum_count([1, 2], [-2, -2], [-1, 2], [0, 2])
