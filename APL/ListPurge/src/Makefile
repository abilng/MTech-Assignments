all: array list

array:	ArrayList.o array_main
	g++ -o array PurgeList.o ArrayList.o 

list:	LinkedList.o list_main
	g++ -o list PurgeList.o LinkedList.o 

array_main: PurgeList.cpp ArrayList.h
	sed s_'#include ".*'_'#include "ArrayList.h"'_ -i PurgeList.cpp
	g++ -c PurgeList.cpp
list_main: PurgeList.cpp LinkedList.h
	sed s_'#include ".*'_'#include "LinkedList.h"'_ -i PurgeList.cpp
	g++ -c PurgeList.cpp
clean: 
	rm -rf list array *.o
