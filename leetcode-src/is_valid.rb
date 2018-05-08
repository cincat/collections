def is_valid(s)
	stack = []
	left = ['(', '{', '[']
	right = [')', '}', ']']
	s.each_char do |x|
		if left.include? x
			stack << x
		elsif right.include? x
			return false if left.index(stack.last) != right.index(x)
			stack.pop
		end
	end
	stack.empty?
end

def generate_parenthesis(n)
	return ["()"] if n == 1
	ans = []	
	generate_parenthesis(n - 1).each do |item|
		ans << "()" + item 
		item.each_char.with_index do |c, i|
			ans << item[0..i] + "()" + item[(i+1)..-1] if c == "("
		end
	end
	ans.uniq
end

def longest_valid_parentheses(s)
	stack, l = [], 0 
	s.each_char.with_index do |c, i|
		if c == '('
			stack << i
		else
			if not stack.empty?
				s[stack.last] == '(' ? stack.pop : stack << i
			else
				stack << i
			end
		end
	end	
	return s.length if stack.empty?

	a, b = s.length, 0
	until stack.empty?
		b = stack.pop
		l = [l, a - b - 1].max
		a = b
	end
	[l, a].max
end
print longest_valid_parentheses("(()")
