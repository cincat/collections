def divide(dividend, divisor)
	return 2**31 - 1 if divisor == 0
	neg = 1
	neg = -1 unless ((dividend < 0 and divisor < 0) or (dividend > 0 and divisor > 0))
	ans, t = 0, 0 
	dividend, divisor = dividend.abs, divisor.abs
	while t + divisor <= dividend
		t += divisor
		ans += 1
	end
	return neg * ans
end

print divide(-1, -1)
