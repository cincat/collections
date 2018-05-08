def next_permutation(nums)
	j, k = -1, 0
	(nums.length - 1).downto(1) do |i|
		(j = i - 1; break) if nums[i - 1] < nums[i]
	end
	if j == -1
		nums.reverse!
	else
		(nums.length - 1).downto(j + 1) do |i|
			(k = i; break) if nums[i] > nums[j]
		end
		nums[k], nums[j] = nums[j], nums[k]
		nums[j+1...nums.length] = nums[j+1...nums.length].reverse
	end
	nums
end	

def permute(nums)
	return [nums] if nums.length == 1
	array = []
	permute(nums[1..-1]).each do |perm|
		(perm.length + 1).times do |i|
			perm.insert(i, nums[0])
			array << perm.dup
			perm.delete_at(i)
		end
	end
	array
end

def permute_unique(nums)
	return [nums] if nums.length == 1
	array = []

	permute(nums[1..-1]).each do |perm|
		(perm.length + 1).times do |i|
			next if nums[0] == perm[i]
			perm.insert(i, nums[0])
			array << perm.dup
			perm.delete_at(i)
		end
	end
	array
end

def get_permutation(n, k)
	get_next = ->(str) do
		s = str.dup
		j, k = -1, 0
		s.length.downto(1) do |i|
			(j = i - 1; break)if s[i-1].to_i < s[i].to_i
		end
		
		if j == -1
			return s.reverse
		else
			s.length.downto(j + 1) do |i|
				(k = i; break) if s[i].to_i > s[j].to_i
			end

			s[j], s[k] = s[k], s[j]
			s[j+1..-1] = s[j+1..-1].reverse
		end
		s
	end
	kperm = ""
	n.times {|i| kperm << "#{i + 1}"}
	(k - 1).times {kperm = get_next.(kperm)}
	kperm
end

#print get_permutation(9, 10000020)

def get_permutationII(n, k)
	str = ""
	num, fac, x= [], [1], 1
	1.upto(n) do |i|
		x *= i
		fac[i] = x
		num << i
	end
	#print "fac : #{fac}\n"
	#print "num : #{num}\n"
	k -= 1
	1.upto(n) do |i|
		ind = k / fac[n - i]
		#print "#{ind}, #{k}, #{fac[n-i]}\n"
		str << "#{num[ind]}"
		num.delete_at ind
		k -= ind * fac[n - i]
	end
	str
end

print get_permutationII(3, 1)
