all:
	forecc -t1000000 NestedPar.forec NestedPar.foreh
	gcc NestedPar.c -o NestedPar -pthread

clean:
	rm -rf NestedPar *.c *.dot *.xml *.txt *.pdf
