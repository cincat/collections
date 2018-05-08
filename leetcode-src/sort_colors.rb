def sort_colors(nums)
	i, front, tail = 0,  -1, nums.length
	while i < tail
		while nums[i] == 2 and i < tail
			tail -= 1 
			nums[i], nums[tail] = nums[tail], nums[i]
		end
		while nums[i] == 0 and i > front
			front += 1
			nums[i], nums[front] = nums[front], nums[i]
		end
		i += 1
	end
end

nums = [2, 1, 0]
sort_colors nums
pr
