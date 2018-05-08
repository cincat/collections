def hamming_distance(x, y)
	(x ^ y).to_s(2).count("1")
end

def total_hamming_distance(nums)
	#c = 0
	#for i in 0 ... nums.length
	#	for j in (i+1) ... nums.length
	#		c += (nums[i] ^ nums[j]).to_s(2).count("1")
	#	end
	#end
	#c
	c = 0
	for i in 0 ... 32
		count = nums.map {|num| num >> i & 1}.reduce(:+)
		c += count * (nums.length - count)
	end
	c
	#for i in 0 ...32
	#	t = 0
	#	nums.each {|x| t += (x >> i) & 1}
	#	c += t * (nums.length - t)
	#end
	#c 
end
#print hamming_distance(1, 4)
print total_hamming_distance([4, 14, 2])
