# @param {String[]} strs
# @return {String}

def longest_common_prefix(strs)
	return "" if strs.length == 0
	prefix, sample= "", strs.first
	sample.each_char do |c|
		strs.each {|str| return prefix if c != str[prefix.length]}
		prefix << c
	end
	prefix
end

puts longest_common_prefix(["aa", "ab"])
