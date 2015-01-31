# It is important to note that what looks like leading sets of blanks
# are in fact tabs and MUST BE TABS.  Make is just that way.
#
SRCS = rand.cpp
HDRS = rand.h
OBJS = rand.o
LIBS = -lm
CC=g++
CPPFLAGS = -g -Wall
CPPFLAGS = -O3


localsearch: localsearch.o $(OBJS)
	$(CC) $(CPPFLAGS) localsearch.o $(OBJS) $(LIBS) -o localsearch

clean:
	rm -f *.o *~

tar:
	tar -cvf pas1.tar $(SRCS) $(HDRS)  makefile localsearch.cpp 
	ls -l pas1.tar
