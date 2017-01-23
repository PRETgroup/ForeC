#!/usr/bin/python3

SIZE = 5
	
def main(output):
	output.write("\tint sum;\r\n")
	for i in range(SIZE):
		for j in range(SIZE):
			output.write("\tsum = 0;\r\n")
			for k in range (SIZE):
				output.write("\tsum += matrixA[" + str(i) + "][" + str(k) + "] * matrixB[" + str(k) + "][" + str(j) + "];\r\n")
			output.write("\tmatrixC[" + str(i) + "][" +  str(j) + "] = sum;\r\n")

if __name__ == '__main__':
	output = open("MatrixMultiplyLoopUnrolled.h", "wt");
	main(output)
	output.close()

