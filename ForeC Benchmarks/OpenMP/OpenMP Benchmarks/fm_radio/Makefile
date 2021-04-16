TESTS = fmr_seq fmr_omp-str #fmr_omp-str_dp

GCC = gcc

all: $(TESTS)

.c:
	$(GCC) -fopenmp $< -lm -o $* -fdump-tree-ompexp-all

clean:
	rm -f $(TESTS) *~ *.c.* *.s *.raw a.out *.txt

