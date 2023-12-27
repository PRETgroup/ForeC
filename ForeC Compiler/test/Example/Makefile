all:
	forecc Example.forec Example.foreh
	gcc Example.c -o Example -pthread
	dot -T pdf Example.dot -o Example.pdf

