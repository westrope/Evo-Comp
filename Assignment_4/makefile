# It is important to note that what looks like leading sets of blanks
# are in fact tabs and MUST BE TABS.  Make is just that way.
#
SRC= rand.cpp main.cpp makefile westrope.pdf freq.txt
HDRS= rand.h
LIBS= -lm
CC=g++
CFLAGS= -o
PFLAGS= -g -c -O3



decipher: main.o rand.o
	$(CC) $(CFLAGS) decipher main.o rand.o

main.o: main.cpp rand.h
	$(CC) $(PFLAGS) -std=c++0x main.cpp 

rand.o: rand.cpp rand.h
	$(CC) $(PFLAGS) rand.cpp 

clean:
	rm -f *.o *~

tar:
	tar -cvf pas4.tar $(SRC) $(HDRS)
	ls -l pas4.tar
