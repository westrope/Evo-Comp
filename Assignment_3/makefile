# It is important to note that what looks like leading sets of blanks
# are in fact tabs and MUST BE TABS.  Make is just that way.
#
SRC= rand.cpp ksat.cpp makefile westrope.pdf
HDRS= rand.h
LIBS= -lm
CC=g++
CFLAGS= -o
PFLAGS= -g -c -O3



ksat: ksat.o rand.o
	$(CC) $(CFLAGS) ksat ksat.o rand.o

localsearch.o: localsearch.cpp
	$(CC) $(PFLAGS) localsearch.cpp 

rand.o: rand.cpp rand.h
	$(CC) $(PFLAGS) rand.cpp 

clean:
	rm -f *.o *~

tar:
	tar -cvf pas3.tar $(SRC) $(HDRS)
	ls -l pas3.tar
