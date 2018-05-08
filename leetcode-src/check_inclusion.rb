def check_inclusion(s1, s2)
	map = Hash.new(0)
	s1.each_char {|c| map[c] += 1}
	#print map
	i = 0
	while i <= s2.length - s1.length
		if map[s2[i]] == 0
			i += 1
			next
		end
		j = 0
		tmp_map = map.dup
		while j < s1.length 
			if tmp_map[s2[i + j]] == 0
				break
			else
				tmp_map[s2[i + j]] -= 1
			end
			j += 1
		end
		
		if j == s1.length
			#print [i, j], "\n"
			#print tmp_map
			return true
		else
			i = i + 1 
		end
	end
	return false
end

#print (check_inclusion("adc", "dcda") ? "true" : "false")

def is_anagram(s, t)
	map = Hash.new(0)
	return false if s.length != t.length
	0.upto(s.length) do |i|
		map[s[i]] += 1;
		map[t[i]] -= 1;
	end

	map.each_value {|v| return false if v != 0}
	return true;
end

#def all_zero(map) 
#	map.each_value {|v| return false if v != 0}
#	return true
#end

def find_anagrams(s, p)
	#p is non-empty
	all_zero = ->(map) do 
		map.each_value {|v| return false if v != 0}
		true;
	end
	map, arr= Hash.new(0), []
	p.each_char {|c| map[c] += 1}
	p.length.times {|i| map[s[i]] -= 1}
	arr.push 0 if all_zero.(map)

	p.length.upto(s.length) do |i|
		map[s[i]] -= 1
		map[s[i - p.length]] += 1
		arr.push(i - p.length + 1) if all_zero.call(map)
	end
	arr
end

#print find_anagrams("cbaebabacd", "abc")
#print find_anagrams("abab", "ab")

def find_substring(s, words)
	map = {}
	array = []
	l = words.first.length
	words.each.with_index {|w, i| map[w] = i}	

	(s.length - 2 * l).times do |i|
		x, y = s[i, l], s[i + l, l]
		next if map[x] == nil or map[y] == nil or map[x] == map[y]
		array.push i
	end
	array
end

print find_substring("barfoothefoobarman", ["foo", "bar"])
