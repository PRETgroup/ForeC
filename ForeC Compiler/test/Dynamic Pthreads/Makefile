all:
	gcc SimpleP.c -o simple -lpthread
	gcc MMP.c -o mmp -lpthread
	clang MMPOMP.c -o mmpomp -fopenmp -lomp
	
clean:
	rm -f simple mmp mmpomp
