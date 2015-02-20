# It is important to note that what looks like leading sets of blanks
# are in fact tabs and MUST BE TABS.  Make is just that way.
#
SRC= rand.cpp bitHelpers.cpp sa.cpp mapFunctions.cpp func.cpp makefile westrope.pdf westrope.tex
HDRS= rand.h bitHelpers.h mapFunctions.h func.h
LIBS= -lm
CC=g++
CFLAGS= -o 
PFLAGS= -g -c -O3



sa: sa.o rand.o bitHelpers.o mapFunctions.o func.o
	$(CC) $(CFLAGS) sa sa.o rand.o bitHelpers.o mapFunctions.o func.o

sa.o: sa.cpp
	$(CC) $(PFLAGS) sa.cpp 

rand.o: rand.cpp rand.h
	$(CC) $(PFLAGS) rand.cpp 

bitHelpers.o: bitHelpers.cpp bitHelpers.h
	$(CC) $(PFLAGS) bitHelpers.cpp

mapFunctions.o: mapFunctions.cpp mapFunctions.h
	$(CC) $(PFLAGS) mapFunctions.cpp

func.o: func.cpp func.h
	$(CC) $(PFLAGS) func.cpp

pdf: westrope.tex
	pdflatex westrope.tex

clean:
	rm -f *.o *~ sa *.tar *.aux *.log

tar:
	tar -cvf pas2.tar $(SRC) $(HDRS)
	ls -l pas2.tar
