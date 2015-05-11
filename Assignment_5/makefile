# It is important to note that what looks like leading sets of blanks
# are in fact tabs and MUST BE TABS.  Make is just that way.
#
SRC= rand.cpp main.cpp makefile opList.cpp tree.cpp
HDRS= rand.h opList.h tree.h
LIBS= -lm
CC=g++
CFLAGS= -o
PFLAGS= -c -O3



func: main.o rand.o tree.o opList.o
	$(CC) $(CFLAGS) func main.o rand.o tree.o opList.o

main.o: main.cpp
	$(CC) $(PFLAGS) -std=c++0x main.cpp

tree.o: tree.cpp tree.h
	$(CC) $(PFLAGS) tree.cpp

rand.o: rand.cpp rand.h
	$(CC) $(PFLAGS) rand.cpp

opList.o: opList.cpp opList.h
	$(CC) $(PFLAGS) opList.cpp

clean:
	rm -f *.o *~ *.tar func

tar:
	tar -cvf pas6.tar $(SRC) $(HDRS)
	ls -l pas6.tar
