# It is important to note that what looks like leading sets of blanks
# are in fact tabs and MUST BE TABS.  Make is just that way.
#
SRC= rand.cpp bitHelpers.cpp localsearch.cpp mapFunctions.cpp func.cpp makefile westrope.pdf
HDRS= rand.h bitHelpers.h mapFunctions.h func.h
LIBS= -lm
CC=g++
CFLAGS= -o 
PFLAGS= -g -c -O3



sa: localsearch.o rand.o bitHelpers.o mapFunctions.o func.o
	$(CC) $(CFLAGS) sa localsearch.o rand.o bitHelpers.o mapFunctions.o func.o

localsearch.o: localsearch.cpp
	$(CC) $(PFLAGS) localsearch.cpp 

rand.o: rand.cpp rand.h
	$(CC) $(PFLAGS) rand.cpp 

bitHelpers.o: bitHelpers.cpp bitHelpers.h
	$(CC) $(PFLAGS) bitHelpers.cpp

mapFunctions.o: mapFunctions.cpp mapFunctions.h
	$(CC) $(PFLAGS) mapFunctions.cpp

func.o: func.cpp func.h
	$(CC) $(PFLAGS) func.cpp

clean:
	rm -f *.o *~

tar:
	tar -cvf pas1.tar $(SRC) $(HDRS)
	ls -l pas1.tar
