def rotate(matrix)
	n = matrix.length
	(n/2).times do |i|
		(i...(n-1-i)).each do |j|
			t = matrix[i][j]
			xi, xj = i, j
			4.times do
				yi, yj = xj, n - 1 - xi
				t, matrix[yi][yj] = matrix[yi][yj], t	
				xi, xj = yi, yj
			end
		end
	end
	#matrix
end

#print rotate([[1, 2, 3],[4, 5, 6], [7, 8, 9]])
print rotate([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]])
