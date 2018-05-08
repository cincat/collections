def find_substring(s, words)
	map, arr = Hash.new(0), []
	words.each {|word| map[word] += 1}
	l = words.first.length
	
	s.length.times do |i|
		break if i + words.length * l > s.length
		tmp_map, c = map.dup, 0
		words.length.times do |j|
			w = s[i + j * l, l]
			break if tmp_map[w] == 0
			tmp_map[w] -= 1
			c += 1
		end
		arr.push i if c == words.length
	end
	arr
end

f = File.open("input.txt", "r")
s = f.gets
words = []
f.gets.split(",").each {|word| word[-1] == "\n" ?
						words << word[1...-2]:
						words << word[1...-1]}
#print words
#print find_substring("barfoothefoobarman", ["foo", "bar"])
print find_substring(s, words)
