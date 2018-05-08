def letter_combinations(digits)
	map, ans = ["0", "1", "abc", "def", "ghi", "jkl",
		"mno", "pqrs", "tuv", "wxyz"], []

	return ans if digits.length == 0
	return map[digits.to_i].chars if digits.length == 1

	map[digits[0].to_i].each_char do |letter|
		letter_combinations(digits[1..digits.length]).
			each {|item| ans << letter + item}
	end
	ans
end

def read_binary_watch(num)
	#bitcount = ->(n) {
	#	c = 0
	#	while n > 0
	#		c += 1 if n & 1 != 0
	#		n = n >> 1
	#	end
	#	c
	#}
	##print bitcount.call(16)
	#ans = []
	#0.upto(11) do |hour|
	#	0.upto(59) do |minute|
	#		if bitcount.call(hour) + bitcount.call(minute) == num
	#			mm = minute < 10 ? "0#{minute}" : "#{minute}"
	#			ans << "#{hour}:#{mm}"
	#		end
	#	end
	#end
	#ans
	#0.upto(11) do |hour|
	#	0.upto(59) do |minute|
	#		ans << hour.to_s + ":%02d" % minute if (hour.to_s(2) + minute.to_s(2)).count('1') == num
	#	end
	#end

	ans = []
	0.upto(11) {|h| 0.upto(59){|m| ans << h.to_s + ":%02d"%m if (h.to_s(2) + m.to_s(2)).count("1") == num}}
	ans 
end
#print letter_combinations("23456789")

def hamming_weight(n)
	n.to_s(2).count("1")
end
print read_binary_watch 1
