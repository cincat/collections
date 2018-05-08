#@param {String} s
#@return {String}

def longest_palindrome(s)
	dp, arr= Array.new(s.length){Array.new(s.length){false}}, []
	#s.reverse.each_char.with_index do |x, i|
	#	s[i..-1].each_char.with_index do |y, j|
	#		dp[i][j] = (s[i] == s[j] && (j - i < 3 || dp[i+1][j-1]))
	#		arr = s[i..j] if(dp[i][j] && j - i + 1 > arr.length)
	#	end
	#end
	#arr
	s.each_char.with_index do |c, i|
			
	end
end

puts longest_palindrome("abb")
