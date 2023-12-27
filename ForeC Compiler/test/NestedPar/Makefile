all:
	forecc -t1000000 NestedPar.forec NestedPar.foreh
	gcc NestedPar.c -o NestedPar -pthread
	dot -T pdf NestedPar.dot -o NestedPar.pdf

clean:
	rm -rf NestedPar *.c *.dot *.xml *.txt *.pdf
