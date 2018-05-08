def min_window(s, t)
	max_int = (2 ** (0.size * 8 - 2) - 1)
	map = Hash.new(0)
	fast, slow, head, count, d = 0, 0, 0, 0, max_int
	t.each_char {|c| map[c] += 1; count += 1}

	while fast < s.length
		count -= 1 if map[s[fast]] > 0
		map[s[fast]] -= 1
		fast += 1
		while count == 0
			if fast - slow < d
				d = fast - slow
				head = slow
			end
			map[s[slow]] += 1
			count += 1 if map[s[slow]] > 0
			slow += 1
		end
	end

	d == max_int ? "" : s[head, d]
end

puts min_window("abba", "aa")
