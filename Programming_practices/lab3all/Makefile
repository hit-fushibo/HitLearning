CC	= gcc -m64 -w

#.. What optimization level for the compilers?
#COPT	= -O2
COPT	= -g


GRARC	 = sort.a
GRSRCS	 = swap.c selectSort.c insertsort.c bubblesort.c mergesort.c quicksort.c heapsort.c main.c
GROBJS	 = swap.o selectsort.o insertsort.o bubblesort.o mergesort.o quicksort.o heapsort.o main.o
HEADER   = sort.h

runsort: $(GROBJS)
	$(CC) $(COPT) -o runsort $(GROBJS) 

main.o: main.c sort.h
	$(CC) $(COPT) -c main.c -o main.o
swap.o: swap.c sort.h
	$(CC) $(COPT) -c swap.c -o swap.o
selectsort.o: selectSort.c sort.h
	$(CC) $(COPT) -c selectSort.c -o selectsort.o
insertsort.o: insertsort.c sort.h
	$(CC) $(COPT) -c insertsort.c -o insertsort.o
bubblesort.o: bubblesort.c sort.h
	$(CC) $(COPT) -c bubblesort.c -o bubblesort.o
mergesort.o:mergesort.c sort.h
	$(CC) $(COPT) -c mergesort.c -o mergesort.o
quicksort.o:quicksort.c sort.h
	$(CC) $(COPT) -c quicksort.c -o quicksort.o
heapsort.o:heapsort.c sort.h
	$(CC) $(COPT) -c heapsort.c -o heapsort.o



clean   :
	rm -f $(GROBJS) runsort
