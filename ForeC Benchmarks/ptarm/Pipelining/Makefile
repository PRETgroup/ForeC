ifeq ($(shell uname), Linux)
	PTARM	= ptarm
else ifeq ($(shell uname), Darwin)
	PTARM	= ptarm
else
	PTARM	= ptarm.bat
endif

forec:
	forecc -d1 Pipelining.forec Pipelining.foreh
	
c:
	$(PTARM) create
	$(PTARM) make

execute:
	$(PTARM) execute

clean:
	rm -f Pipelining *.exe *.dot *.c *.txt *.pdf *.xml
	$(PTARM) clean
