all: main

main : Main.o Dictionary.o RBTree.o BSTree.o
	g++ -o dictionary Main.o Dictionary.o RBTree.o BSTree.o

clean:
	rm -f *.o dictionary