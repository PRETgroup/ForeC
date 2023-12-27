all:
	forecc abro.forec abro.foreh
	gcc abro.c -o abro
	dot -T pdf abro.dot -o abro.pdf

clean:
	rm -rf *.c *.dot *.txt *.xml abro
