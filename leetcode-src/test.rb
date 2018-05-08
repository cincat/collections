n = 11
c = 0
while n > 0
	c += 1 if n & 1
	n = n >> 1
end

print c
