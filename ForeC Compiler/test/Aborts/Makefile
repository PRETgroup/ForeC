all:
	forecc aborts.forec aborts.foreh
	gcc aborts.c -o aborts
	dot -T pdf aborts.dot -o aborts.pdf

clean:
	rm -rf *.c *.dot *.txt *.xml aborts
