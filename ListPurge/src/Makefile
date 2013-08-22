all: arrayprog linkedlistprog

purgelist: PurgeList.cpp ArrayList.h LinkedList.h
	g++ -c PurgeList.cpp -o PurgeList.o

array: ArrayList.cpp ArrayList.h
	g++ -c ArrayList.cpp -o ArrayList.o

linkedlist: LinkedList.cpp LinkedList.h
	g++ -c LinkedList.cpp -o LinkedList.o

arrayprog: PurgeList.o ArrayList.o
	g++ PurgeList.o ArrayList.o -o array

linkedlistprog: PurgeList.o LinkedList.o
	g++ PurgeList.o ArrayList.o -o linkedlist

clean: 
	rm -rf array  linkedlist *.o
