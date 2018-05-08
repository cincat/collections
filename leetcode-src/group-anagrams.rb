def group_anagrams(strs)
	is_anag = ->(s, t) do
		return false if s.length != t.length
		return s.chars.sort.eql? t.chars.sort
	end

	ans = Array.new() {Array.new}
	strs.each do |s|
		if ans.empty?
			ans << [s]
			next
		end

		flag = true
		ans.each_index do |i|
			if is_anag.call(ans[i].first, s)
				ans[i] << s
				flag = false
				break
			end
			
			#ans << [s] if i == ans.length - 1
		end
		ans << [s] if flag
		flag = true
	end
	ans 
end
def quick_group_anagrams(strs)
	map = Hash.new
	strs.each do |s|
		key = s.chars.sort
		map[key] ||= []
		map[key] << s
	end
	map.values
end
#group_anagrams(["eat", "tea", "tan", "ate", "nat", "bat"])
#print group_anagrams(["eat", "tea", "tan", "ate", "nat", "bat"])
quick_group_anagrams(["eat", "tea", "tan", "ate", "nat", "bat"]).each do |x|
	print x, "\n"
end
