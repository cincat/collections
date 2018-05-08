def str_str(haystack, needle)
	#n, m, i, j = haystack.length, needle.length, 0, 0
	#while i <= n - m
	#	j += 1 while j < m and haystack[i+j] == needle[j]
	#	return i if j == m
	#	i, j = i + 1, 0 
	#end
	#m == 0 ? 0 : -1
	
	m, n = haystack.length, needle.length
	i, j = 0, 0
	while i < m and j < n
		haystack[i] == needle[j] ?
			(i, j = i + 1, j + 1) :
			(i, j = i - j + 1, 0)
	end
	j == n ? i - j : -1
end

def str_strII(haystack, needle)
	array = get_next(needle)
	m, n = haystack.length, needle.length
	i, j = 0, 0
	while i < m and j < n
		(j == -1 or haystack[i] == needle[j]) ?
			(i, j = i + 1, j + 1) : 
			j = array[j];
	end
	j == n ? i - j : -1
end

def get_next(needle)
	array = Array.new(needle.length)
	array[0] = -1
	k, j = -1, 0
	while j < needle.length - 1
		if k == -1 or needle[j] == needle[k]
			k, j = k + 1, j + 1
			array[j] = k
		else
			k = array[k]
		end
	end
	array
end

print str_strII("bbc abcdab abcdabcdabde", "abcdabd")
