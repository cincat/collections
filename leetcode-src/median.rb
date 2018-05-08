def find_median_sorted_arrays(nums1, nums2)
	m, n = nums1.length, nums2.length

	i, j, k, half = 0, 0, 0, (m + n - 1) / 2
	while k < half
		if i < m and j < n and nums1[i] < nums2[j]
			k, i = k + 1, i + 1
		elsif i < m and j < n and nums[i] >= nums[j]
			k, j = k + 1, j + 1
		end
	end

	print [i, j, k]
	if i == m
		if(n + m) % 2 == 1
			return nums2[j]
		else
			return (nums2[j] + nums2[j - 1]) / 2
		end
	else
		if(n + m) % 2 == 1
			return nums1[i]
		else
			return (nums1[i] + nums1[i - 1]) / 2
		end
	end
end

print find_median_sorted_arrays([1, 2, 3], [5, 6])
