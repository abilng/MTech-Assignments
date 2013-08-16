all:
array:	main ArrayList.o
	g++ -o main PurgeList.o ArrayList.o 

list:	main LinkedList.o
	g++ -o main PurgeList.o LinkedList.o 

main:	PurgeList.o ArrayList.h LinkedList.h

clean: 
	rm -rf main *.o
