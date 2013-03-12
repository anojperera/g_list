## Make file for testing generic class
## Sat Jul 24 18:51:26 BST 2010

CFLAGS1 = -g
CFLAGS2 = -O0
CFLAGS3 = -Wall
PROG = tmp
CCC = gcc
CCP = g++
OBJS = main.o alist.o blist.o gstack.o

$(PROG) : $(OBJS)
		$(CCC) $(CFLAGS1) $(CFLAGS2) $(CFLAGS3) -o $(PROG) $(OBJS)

main.o : main.c alist.h
		$(CCC) $(CFLAGS1) $(CFLAGS2) $(CFLAGS3) -c main.c

alist.o : alist.c alist.h 
		$(CCC) $(CFLAGS1) $(CFLAGS2) $(CFLAGS3) -c alist.c

blist.o : blist.c blist.h
		$(CCC) $(CFLAGS1) $(CFLAGS2) $(CFLAGS3) -c blist.c

gstack.o: gstack.c gstack.h
		$(CCC) $(CFLAGS1) $(CFLAGS2) $(CFLAGS3) -c gstack.c

clean : 
		rm  -fv *.o
